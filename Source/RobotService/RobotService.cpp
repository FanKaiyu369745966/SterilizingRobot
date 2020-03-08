#include "RobotService.h"

RobotService::RobotService(QWidget* parent)
	: QMainWindow(parent)
	, m_server(nullptr)
	, m_db(QSqlDatabase::addDatabase("QODBC3"))
	//	, m_combSource(nullptr)
	, m_leditHost(nullptr)
	, m_leditUser(nullptr)
	, m_leditPwd(nullptr)
	, m_pbutLink(nullptr)
	, m_leidtAddr(nullptr)
	, m_pbutListen(nullptr)
	, m_modelClnt(nullptr)
{
	//ui.setupUi(this);

	Initialize();

	qRegisterMetaType<RobotUuid>();
	qRegisterMetaType<RobotUuidArray>();
}

void RobotService::Initialize()
{
	setWindowTitle(QString::fromLocal8Bit("博乐恩机器人服务"));

	// 数据库
//	QLabel* _lableSource = new QLabel(QString::fromLocal8Bit("数据库源："));
	QLabel* _lableHost = new QLabel(QString::fromLocal8Bit("主机名："));
	QLabel* _lableUser = new QLabel(QString::fromLocal8Bit("用户名："));
	QLabel* _lablePwd = new QLabel(QString::fromLocal8Bit("密码"));
	//	m_combSource = new QComboBox(this);
	m_leditHost = new QLineEdit(this);
	m_leditUser = new QLineEdit(this);
	m_leditPwd = new QLineEdit(this);
	m_pbutLink = new QPushButton(QString::fromLocal8Bit("连接"), this);
	QCheckBox* _checkPwd = new QCheckBox(QString::fromLocal8Bit("显示"), this);
	QGroupBox* _groupDB = new QGroupBox(QString::fromLocal8Bit("数据库"), this);
	QHBoxLayout* _layDB = new QHBoxLayout(this);

	// 设置控件布局
//	_layDB->addWidget(_lableSource);
//	_layDB->addWidget(m_combSource);
	_layDB->addWidget(_lableHost);
	_layDB->addWidget(m_leditHost);
	_layDB->addWidget(_lableUser);
	_layDB->addWidget(m_leditUser);
	_layDB->addWidget(_lablePwd);
	_layDB->addWidget(m_leditPwd);
	_layDB->addWidget(_checkPwd);
	_layDB->addWidget(m_pbutLink);
	_groupDB->setLayout(_layDB);

	// 服务端
	QLabel* _lableAddr = new QLabel(QString::fromLocal8Bit("地址："), this);			/*!< 服务端地址标签 */
	m_leidtAddr = new QLineEdit(this);													/*!< 服务端地址编辑框 */
	m_pbutListen = new QPushButton(QString::fromLocal8Bit("监听"), this);				/*!< 服务端监听按钮 */
	QGroupBox* _groupSrv = new QGroupBox(QString::fromLocal8Bit("服务端"), this);		/*!< 服务端组合框 */
	QHBoxLayout* _laySrv = new QHBoxLayout(this);										/*!< 服务端控件布局 */

	// 设置控件样式
	m_leidtAddr->setPlaceholderText(QString::fromLocal8Bit("IP:端口 例如：127.0.0.1:8080"));
	m_leditPwd->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

	//	_combSource->insertItem(0, "SQL Server");
	//	_combSource->insertItem(1, "MySQL");
	//	_combSource->insertItem(2, "SQLite");
	//	_combSource->insertItem(3, "SQLite2");

	// 设置布局
	_laySrv->addWidget(_lableAddr);
	_laySrv->addWidget(m_leidtAddr);
	_laySrv->addWidget(m_pbutListen);
	_groupSrv->setLayout(_laySrv);

	// 客户端
	QGroupBox* _groupClnt = new QGroupBox(QString::fromLocal8Bit("客户端"), this);		/*!< 客户端组合框 */
	QHBoxLayout* _layClnt = new QHBoxLayout(this);										/*!< 客户端控件布局 */
	QTableView* _tableClnt = new QTableView(this);										/*!< 客户端表单 */
	m_modelClnt = new QStandardItemModel(this);

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_modelClnt->setColumnCount(3);
	m_modelClnt->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("地址"));
	m_modelClnt->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("UUID"));
	m_modelClnt->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("订阅"));

	// 设置控件样式
	_tableClnt->setModel(m_modelClnt);
	_tableClnt->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_tableClnt->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	_tableClnt->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 设置布局
	_layClnt->addWidget(_tableClnt);
	_groupClnt->setLayout(_layClnt);

	// 全局
	QWidget* _wCenter = new QWidget(this);												/*!< 中心控件 */
	QVBoxLayout* _layMain = new QVBoxLayout(this);										/*!< 中心控件布局 */

	// 设置控件布局
	_layMain->addWidget(_groupDB);
	_layMain->addWidget(_groupSrv);
	_layMain->addWidget(_groupClnt);
	_wCenter->setLayout(_layMain);

	setCentralWidget(_wCenter);

	m_server = new QTcpServer(this);

	// 添加信号和槽
	QObject::connect(m_pbutLink, &QPushButton::pressed, this, &RobotService::PressedLinkButton);
	QObject::connect(_checkPwd, &QCheckBox::toggled, this, &RobotService::OnClickShowPasswordButton);
	QObject::connect(m_pbutListen, &QPushButton::pressed, this, &RobotService::PressedListenButton);

	QObject::connect(m_server, &QTcpServer::newConnection, this, &RobotService::NewConnection);
	QObject::connect(m_server, &QTcpServer::acceptError, this, &RobotService::AcceptError);

	Load();

	return;
}

void RobotService::InitDatabase()
{
	if (m_db.isOpen() == false)
	{
		return;
	}

	QSqlQuery _query(m_db);

	// 创建数据库
	if (_query.exec("create database RobotServiceDB") == false)
	{
		qDebug() << _query.lastError().text();
	}

	m_db.setDatabaseName(m_db.databaseName() + QString("DATABASE=RobotServiceDB;"));

	m_db.close();

	if (m_db.open() == false)
	{
		m_pbutLink->setText(QString::fromLocal8Bit("连接"));

		m_leditHost->setReadOnly(false);
		m_leditUser->setReadOnly(false);
		m_leditPwd->setReadOnly(false);

		return;
	}

	// 创建数据表
	QString	_sql = "";

	/*!
	 * @表明 Service_log
	 * @字段 log_time datetime not null dafault getdate() 记录日志的时间
	 * @字段 log_addr varchar(100) 记录产生的地址
	 * @字段 log_uuid varchar(255) 记录产生的uuid
	 * @字段 log_user varchar(255) 记录产生的用户
	 * @字段 log_text varchar(65535) 记录的内容
	 * @字段 log_type varchar(255) 记录的类型
	*/
	_sql += QString("create table Service_log(\
log_time datetime not null default getdate(),\
log_addr varchar(100) not null,\
log_uuid varchar(255) not null,\
log_user varchar(255) not null,\
log_text varchar(max) not null,\
log_type varchar(255) not null\
)");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	// 创建主键、约束
	_sql = "Alter Table Service_log ";
	_sql += QString("ADD CONSTRAINT pk_logTime PRIMARY KEY (log_time)");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	return;
}

void RobotService::PressedLinkButton()
{
	if (m_db.isOpen())
	{
		m_db.close();

		m_pbutLink->setText(QString::fromLocal8Bit("连接"));

		m_leditHost->setReadOnly(false);
		m_leditUser->setReadOnly(false);
		m_leditPwd->setReadOnly(false);

		return;
	}

	if (m_leditHost->text().isEmpty() || m_leditUser->text().isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("连接数据库"), QString::fromLocal8Bit("连接数据库失败!原因:\n主机名、用户名不能为空"));

		return;
	}

	m_db.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;"
		//"DATABASE=%2;"
		"UID=%2;"
		"PWD=%3;")
		.arg(m_leditHost->text())
		//.arg(m_wDatabase->m_strUser)
		.arg(m_leditUser->text())
		.arg(m_leditPwd->text()));

	if (m_db.open())
	{
		m_pbutLink->setText(QString::fromLocal8Bit("中断"));

		m_leditHost->setReadOnly(true);
		m_leditUser->setReadOnly(true);
		m_leditPwd->setReadOnly(true);

		InitDatabase();

		return;
	}

	QMessageBox::critical(this, QString::fromLocal8Bit("连接数据库"), QString::fromLocal8Bit("连接数据库失败!原因:\n%1").arg(m_db.lastError().text()));

	return;
}

void RobotService::Load()
{
	// 读取配置信息
	QString _srvAddr = "", _dbHost = "",/* _dbName = "",*/ _dbUser = "", _dbPwd = "";

	QFile _fileConfig("Config/Config.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileConfig.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QJsonDocument _jdoc = QJsonDocument::fromJson(_fileConfig.readAll());
		QJsonObject _jobjRoot = _jdoc.object();

		QJsonObject _jobjSrv = _jobjRoot.value("Server").toObject();
		QJsonObject _jobjDb = _jobjRoot.value("Database").toObject();

		_srvAddr = _jobjSrv.value("Address").toString();
		_dbHost = _jobjDb.value("Host").toString();
		//_dbName = _jobjDb.value("DatabaseName").toString();
		_dbUser = _jobjDb.value("User").toString();
		_dbPwd = _jobjDb.value("Password").toString();

		_fileConfig.close();
	}

	m_leditHost->setText(_dbHost);
	m_leditUser->setText(_dbUser);
	m_leditPwd->setText(_dbPwd);
	m_leidtAddr->setText(_srvAddr);

	if (_dbHost.isEmpty() == false && _dbUser.isEmpty() == false)
	{
		PressedLinkButton();
	}

	if (_srvAddr.isEmpty() == false)
	{
		PressedListenButton();
	}

	return;
}

void RobotService::Save()
{
	// 创建子目录
	QDir _dir(".");
	QDir _dirConfig("Config");

	// 创建配置存放目录
	if (_dirConfig.exists() == false)
	{
		_dir.mkdir("Config");
	}

	QJsonObject	_jobjRoot, _jobjSrv, _jobjDb;

	_jobjSrv.insert("Address", m_leidtAddr->text());

	_jobjDb.insert("Host", m_leditHost->text());
	//_jobjDb.insert("DatabaseName", m_wDatabase->m_strDbName);
	_jobjDb.insert("User", m_leditUser->text());
	_jobjDb.insert("Password", m_leditPwd->text());

	_jobjRoot.insert("Server", _jobjSrv);
	_jobjRoot.insert("Database", _jobjDb);

	// 创建配置文件
	QFile _fileSrvConfig("Config/Config.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileSrvConfig.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		_fileSrvConfig.write(QJsonDocument(_jobjRoot).toJson());
	}

	return;
}

void RobotService::AddNewClient(QString addr)
{
	QList<QStandardItem*> _list;
	_list.push_back(new QStandardItem(addr));
	_list.push_back(new QStandardItem(""));
	_list.push_back(new QStandardItem(""));

	m_modelClnt->appendRow(_list);

	for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		(*it)->setEditable(false);
		(*it)->setToolTip((*it)->text());
	}

	return;
}

void RobotService::UpdateClient(QString addr, QString uuid)
{
	for (int i = 0; i < m_modelClnt->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_modelClnt->item(i);

		if (_aItem->text() != addr)
		{
			continue;
		}

		m_modelClnt->item(i, 1)->setText(uuid);
	}

	return;
}

void RobotService::UpdateClient(QString addr, QStringList takeList)
{
	QString _takes = "";

	if (takeList.size() > 0)
	{
		QStringList::iterator it = takeList.begin();

		_takes = *it;

		it = takeList.erase(it);

		for (; it != takeList.end(); it = takeList.erase(it))
		{
			_takes += "," + *it;
		}
	}

	for (int i = 0; i < m_modelClnt->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_modelClnt->item(i);

		if (_aItem->text() != addr)
		{
			continue;
		}

		m_modelClnt->item(i, 2)->setText(_takes);
	}

	return;
}

void RobotService::DeleteClient(QString addr)
{
	for (int i = 0; i < m_modelClnt->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_modelClnt->item(i);

		if (_aItem->text() != addr)
		{
			continue;
		}

		m_modelClnt->removeRow(i);
	}

	return;
}

void RobotService::DeleteSubscriber(QString addr, QStringList takeList)
{
	for (int i = 0; i < m_modelClnt->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_modelClnt->item(i);

		if (_aItem->text() != addr)
		{
			continue;
		}

		QStringList	_list = m_modelClnt->item(i, 2)->text().split(',');

		for (QStringList::iterator it = _list.begin(); it != _list.end();)
		{
			bool _bRemove = false;

			for (int i = 0; i < takeList.size(); ++i)
			{
				if (*it == takeList.at(i))
				{
					it = _list.erase(it);

					_bRemove = true;

					break;
				}
			}

			if (_bRemove == false)
			{
				++it;
			}
		}

		QString _takes = "";

		if (_list.size() > 0)
		{
			QStringList::iterator it = _list.begin();

			_takes = *it;

			it = _list.erase(it);

			for (; it != _list.end(); it = _list.erase(it))
			{
				_takes += "," + *it;
			}
		}

		m_modelClnt->item(i, 2)->setText(_takes);
	}

	return;
}

void RobotService::closeEvent(QCloseEvent* event)
{
	if (m_server->isListening())
	{
		Record("Server",
			"",
			QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
			"Error",
			QString::fromLocal8Bit("监听停止"));

		m_server->close();
	}

	Save();
	event->accept();

	return;
}

void RobotService::OnClickShowPasswordButton(bool checked)
{
	if (checked)
	{
		m_leditPwd->setEchoMode(QLineEdit::EchoMode::Normal);
		return;
	}

	m_leditPwd->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

	return;
}

void RobotService::PressedListenButton()
{
	if (m_server->isListening())
	{
		Record("Server",
			"",
			QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
			"Error",
			QString::fromLocal8Bit("监听停止"));

		m_server->close();

		m_pbutListen->setText(QString::fromLocal8Bit("监听"));
		m_leidtAddr->setReadOnly(false);

		return;
	}

	QString _addr = m_leidtAddr->text();

	QString _ip = _addr.section(':', 0, -2);
	quint16 _port = static_cast<quint16>(_addr.section(':', -1, -1).toUInt());

	QHostAddress _host;

	if (_host.setAddress(_ip) == false || _port == 0 || _port > 65535)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("服务端监听"), QString::fromLocal8Bit("监听启动失败！无效的地址信息"));

		return;
	}

	// 向服务端日志中填写日志
	if (m_server->listen(_host, _port))
	{
		m_pbutListen->setText(QString::fromLocal8Bit("停止"));
		m_leidtAddr->setReadOnly(true);

		Record("Server",
			"",
			QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
			"Error",
			QString::fromLocal8Bit("监听启动."));
	}
	else
	{
		Record("Server",
			"",
			QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
			"Error",
			QString::fromLocal8Bit("监听启动失败!原因:%1").arg(m_server->errorString()));
	}

	return;
}

void RobotService::NewConnection()
{
	while (m_server->hasPendingConnections())
	{
		QTcpSocket* _socket = m_server->nextPendingConnection();

		// 向服务端日志中填写日志
		Record("Server",
			"",
			QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
			"Normal",
			QString::fromLocal8Bit("客户端【%1:%2】接入").arg(_socket->peerAddress().toString()).arg(_socket->peerPort()));

		RobotClient* client = new RobotClient(_socket, nullptr);

		QObject::connect(client, &RobotClient::Record, this, &RobotService::Record);
		QObject::connect(client, &RobotClient::Disconnected, this, &RobotService::Disconnected);
		QObject::connect(client, &RobotClient::Recognition, this, &RobotService::RecognitionClient);

		QObject::connect(client, &RobotClient::Subscribe, this, &RobotService::Subscribe);
		QObject::connect(client, &RobotClient::Unsubscribe, this, &RobotService::Unsubscribe);

		AddNewClient(client->GetAddress());
	}

	return;
}

void RobotService::AcceptError(QAbstractSocket::SocketError error)
{
	// 向服务端日志中填写日志
	Record("Server",
		"",
		QString("%1:%2").arg(m_server->serverAddress().toString()).arg(m_server->serverPort()),
		"Error",
		QString::fromLocal8Bit("%1").arg(m_server->errorString()));

	m_server->close();

	m_pbutListen->setText(QString::fromLocal8Bit("监听"));
	m_leidtAddr->setReadOnly(false);

	//switch (error)
	//{
	//case QAbstractSocket::ConnectionRefusedError:
	//	break;
	//case QAbstractSocket::RemoteHostClosedError:
	//	break;
	//case QAbstractSocket::HostNotFoundError:
	//	break;
	//case QAbstractSocket::SocketAccessError:
	//	break;
	//case QAbstractSocket::SocketResourceError:
	//	break;
	//case QAbstractSocket::SocketTimeoutError:
	//	break;
	//case QAbstractSocket::DatagramTooLargeError:
	//	break;
	//case QAbstractSocket::NetworkError:
	//	break;
	//case QAbstractSocket::AddressInUseError:
	//	break;
	//case QAbstractSocket::SocketAddressNotAvailableError:
	//	break;
	//case QAbstractSocket::UnsupportedSocketOperationError:
	//	break;
	//case QAbstractSocket::UnfinishedSocketOperationError:
	//	break;
	//case QAbstractSocket::ProxyAuthenticationRequiredError:
	//	break;
	//case QAbstractSocket::SslHandshakeFailedError:
	//	break;
	//case QAbstractSocket::ProxyConnectionRefusedError:
	//	break;
	//case QAbstractSocket::ProxyConnectionClosedError:
	//	break;
	//case QAbstractSocket::ProxyConnectionTimeoutError:
	//	break;
	//case QAbstractSocket::ProxyNotFoundError:
	//	break;
	//case QAbstractSocket::ProxyProtocolError:
	//	break;
	//case QAbstractSocket::OperationError:
	//	break;
	//case QAbstractSocket::SslInternalError:
	//	break;
	//case QAbstractSocket::SslInvalidUserDataError:
	//	break;
	//case QAbstractSocket::TemporaryError:
	//	break;
	//case QAbstractSocket::UnknownSocketError:
	//	break;
	//}

	return;
}

void RobotService::Record(QString user, QString uuid, QString addr, QString type, QString text)
{
	if (m_db.isOpen() == false)
	{
		return;
	}

	QString	_sql = QString::fromLocal8Bit("insert into Service_log(log_addr,log_uuid,log_user,log_text,log_type) values('%1','%2','%3','%4','%5')")
		.arg(addr).arg(uuid).arg(user).arg(text).arg(type);

	QSqlQuery _query(m_db);

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	return;
}

void RobotService::RecognitionClient(QString uuid)
{
	RobotClient* _client = (RobotClient*)sender();

	m_mapUuids[uuid] = _client;

	UpdateClient(_client->GetAddress(), uuid);

	return;
}

void RobotService::Disconnected()
{
	RobotClient* _client = (RobotClient*)sender();

	Record("Client", _client->GetUuid(), _client->GetAddress(), "Normal", QString::fromLocal8Bit("客户端退出连接"));

	DeleteClient(_client->GetAddress());

	if (m_mapUuids.find(_client->GetUuid()) != m_mapUuids.end())
	{
		m_mapUuids.erase(m_mapUuids.find(_client->GetUuid()));
	}

	// 销毁客户端对象
	_client->deleteLater();

	return;
}

void RobotService::Subscribe(RobotUuidArray& _array)
{
	RobotClient* _client = (RobotClient*)sender();

	QStringList _sub;

	for (RobotUuidArray::iterator it = _array.begin(); it != _array.end(); ++it)
	{
		_sub.push_back(it->m_uuid);

		if (m_mapUuids.find(it->m_uuid) == m_mapUuids.end())
		{
			it->m_result = false;

			continue;
		}

		QObject::connect(_client, &RobotClient::NewPackages, m_mapUuids[it->m_uuid], &RobotClient::SendPackage);
		QObject::connect(m_mapUuids[it->m_uuid], &RobotClient::NewPackages, _client, &RobotClient::SendPackage);
		QObject::connect(m_mapUuids[it->m_uuid], &RobotClient::Disconnected, _client, &RobotClient::SubscriberBreak);

		it->m_result = true;
	}

	UpdateClient(_client->GetAddress(), _sub);

	return;
}

void RobotService::Unsubscribe(RobotUuidArray& _array)
{
	RobotClient* _client = (RobotClient*)sender();

	QStringList _sub;

	for (RobotUuidArray::iterator it = _array.begin(); it != _array.end(); ++it)
	{
		_sub.push_back(it->m_uuid);

		if (m_mapUuids.find(it->m_uuid) == m_mapUuids.end())
		{
			it->m_result = true;

			continue;
		}

		QObject::disconnect(_client, &RobotClient::NewPackages, m_mapUuids[it->m_uuid], &RobotClient::SendPackage);
		QObject::disconnect(m_mapUuids[it->m_uuid], &RobotClient::NewPackages, _client, &RobotClient::SendPackage);
		QObject::disconnect(m_mapUuids[it->m_uuid], &RobotClient::Disconnected, _client, &RobotClient::SubscriberBreak);

		it->m_result = true;
	}

	DeleteSubscriber(_client->GetAddress(), _sub);

	return;
}
