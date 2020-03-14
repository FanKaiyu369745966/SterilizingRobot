#include "RobotClient.h"

RobotClient::RobotClient(QTcpSocket* socket, QObject* parent)
	: QObject(parent)
	, m_strUuid("")
	, m_socket(socket)
	, m_thread(nullptr)
	, m_bClose(false)
{
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &RobotClient::ReadData);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &RobotClient::disconnected);

	//m_timer.setInterval(1000);
	//moveToThread(&m_thread);
	//m_thread.start();

	m_thread = new std::thread(&RobotClient::Thread, this);
}

RobotClient::~RobotClient()
{
	//m_thread.quit();
	//m_thread.wait();
	//m_timer.stop();

	if (m_thread->joinable())
	{
		m_bClose = true;
		m_thread->join();
		delete m_thread;
	}

	if (m_socket->isOpen())
	{
		m_socket->close();
	}
}

QString RobotClient::GetDate()
{
	using namespace std;

	chrono::system_clock::time_point tpCur = chrono::system_clock::now();

	time_t tt = chrono::system_clock::to_time_t(tpCur);
	tm* t = localtime(&tt);

	auto timeNow = chrono::duration_cast<chrono::milliseconds>(tpCur.time_since_epoch());

	QString str = QString("%1/%2/%3 %4:%5:%6")
		.arg(t->tm_year + 1900, 4, 10, QLatin1Char('0'))
		.arg(t->tm_mon + 1, 2, 10, QLatin1Char('0'))
		.arg(t->tm_mday, 2, 10, QLatin1Char('0'))
		.arg(t->tm_hour, 2, 10, QLatin1Char('0'))
		.arg(t->tm_min, 2, 10, QLatin1Char('0'))
		.arg(t->tm_sec, 2, 10, QLatin1Char('0'));

	return str;
}

QString RobotClient::GetAddress() const
{
	if (m_socket == nullptr)
	{
		return QString();
	}

	return QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
}

void RobotClient::disconnected()
{
	emit Disconnected();

	return;
}

void RobotClient::SubscriberBreak()
{
	RobotClient* _subscriber = (RobotClient*)sender();

	// 返回结果
	QJsonObject _jResult, _jobjCmd;

	_jobjCmd.insert("Take", "");
	_jResult.insert(_subscriber->GetUuid(), false);

	m_mutex.lock();

	QString	_result = CreatePackage("", m_strUuid, _jobjCmd, _jResult);

	m_socket->write(_result.toLatin1());
	m_socket->flush();

	m_mutex.unlock();

	emit Record("Client", m_strUuid, GetAddress(), "Send", _result);

	return;
}

void RobotClient::Thread()
{
	while (m_bClose == false)
	{
		if (m_strUuid.isEmpty())
		{
			std::chrono::seconds ts = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::time_point() - m_tpClock);

			if (ts.count() != 0)
			{
				std::chrono::steady_clock::time_point _tNow = std::chrono::steady_clock::now();

				ts = std::chrono::duration_cast<std::chrono::seconds>(_tNow - m_tpClock);

				if (ts.count() > 10)
				{
					//m_socket->close();
					deleteLater();
					break;
				}
			}
			else
			{
				m_tpClock = std::chrono::steady_clock::now();
			}

			QJsonObject _jobjCmd;

			_jobjCmd.insert("Hand", "");

			m_mutex.lock();

			QString	_result = CreatePackage("", m_strUuid, _jobjCmd);

			m_socket->write(_result.toLatin1());
			m_socket->flush();

			m_mutex.unlock();

			emit Record("Client", m_strUuid, GetAddress(), "Send", _result);

			_sleep(1000);

			continue;
		}

		break;
	}

	return;
}

QString RobotClient::CreatePackage(QString fUuid, QString tUuid, QJsonObject jCmd)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", fUuid);
	_jPkg.insert("To", tUuid);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", jCmd);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotClient::CreatePackage(QString fUuid, QString tUuid, QJsonObject jCmd, QJsonObject jResult)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", fUuid);
	_jPkg.insert("To", tUuid);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", jCmd);
	_jPkg.insert("Result", jResult);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

void RobotClient::SendPackage(QByteArrayList list)
{
	QString	_result = "";

	for (QByteArrayList::iterator it = list.begin(); it != list.end(); it = list.erase(it))
	{
		QJsonParseError	_error;
		QJsonDocument _doc = QJsonDocument::fromJson(*it, &_error);

		if (_error.error != QJsonParseError::NoError)
		{
			qDebug() << _error.errorString();

			continue;
		}

		QJsonObject _jobj = _doc.object();

		QString _uuid = _jobj.value("To").toString();

		if (_uuid.isEmpty() == false && _uuid != m_strUuid)
		{
			continue;
		}

		_result += *it;
		_result += "|";
	}

	m_mutex.lock();

	m_socket->write(_result.toLatin1());
	m_socket->flush();

	m_mutex.unlock();

	return;
}

void RobotClient::ReadData()
{
	if (m_socket->isReadable())
	{
		QByteArray _buf = m_socket->readAll();

		QByteArrayList _list = _buf.split('|');

		_buf.clear();

		QByteArrayList _listPkg;

		qDebug() << _list.size();

		for (QByteArrayList::iterator it = _list.begin(); it != _list.end(); it = _list.erase(it))
		{
			QJsonParseError	_error;
			QJsonDocument _doc = QJsonDocument::fromJson(*it, &_error);

			if (_error.error != QJsonParseError::NoError)
			{
				//qDebug() << _error.errorString();

				continue;
			}

			QJsonObject _jobj = _doc.object();

			QString _uuid = _jobj.value("From").toString();

			emit Record("Client", m_strUuid, GetAddress(), "Receive", _doc.toJson());

			QJsonObject	_jobjCmd = _jobj.value("Cmd").toObject();

			QStringList _keys = _jobjCmd.keys();

			QJsonObject	_jobjOther;

			// 返回订阅结果
			QJsonObject _jResult;

			for (QStringList::iterator itK = _keys.begin(); itK != _keys.end(); ++itK)
			{
				if (*itK == "Hand" || *itK == "Heart")
				{
					if (m_strUuid.isEmpty())
					{
						// 注册UUID
						m_strUuid = _uuid;

						emit Recognition(_uuid);
					}
				}
				else if (*itK == "Take")
				{
					QJsonArray _arry = _jobjCmd.value(*itK).toArray();

					// 订阅客户端信息
					RobotUuidArray _uuidArray;

					for (int i = 0; i < _arry.size(); ++i)
					{
						_uuidArray.push_back(RobotUuid(_arry.at(i).toString()));
					}

					emit Subscribe(_uuidArray);

					for (int i = 0; i < _uuidArray.size(); ++i)
					{
						_jResult.insert(_uuidArray.at(i).m_uuid, _uuidArray.at(i).m_result);
					}
				}
				else if (*itK == "Remove")
				{
					QJsonArray _arry = _jobjCmd.value(*itK).toArray();

					// 取消订阅客户端信息
					RobotUuidArray _uuidArray;

					for (int i = 0; i < _arry.size(); ++i)
					{
						_uuidArray.push_back(RobotUuid(_arry.at(i).toString()));
					}

					emit Unsubscribe(_uuidArray);

					// 返回结果
					QJsonObject _jResult;

					for (int i = 0; i < _uuidArray.size(); ++i)
					{
						_jResult.insert(_uuidArray.at(i).m_uuid, _uuidArray.at(i).m_result);
					}
				}
				else
				{
					_jobjCmd.remove(*itK);
					_jobjOther.insert(*itK, _jobjCmd.value(*itK));
				}
			}

			if (_jobjCmd.isEmpty() == false)
			{
				_sleep(1);

				m_mutex.lock();

				QString _result = CreatePackage("", m_strUuid, _jobjCmd, _jResult);

				m_socket->write(_result.toLatin1());
				m_socket->flush();

				m_mutex.unlock();

				emit Record("Client", m_strUuid, GetAddress(), "Send", _result);
			}

			if (_jobjOther.isEmpty() == false)
			{
				_jobj.insert("Cmd", _jobjOther);
				_listPkg.push_back(QJsonDocument(_jobj).toJson());
			}
		}

		//qDebug() << _list.size();

		if (_listPkg.size() > 0)
		{
			// 发送信息至订阅的客户端
			emit NewPackages(_listPkg);
		}
	}

	return;
}
