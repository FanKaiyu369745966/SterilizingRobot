#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QHostAddress>
#include <QMutex>
#include <QMetaType>
#include <chrono>
#include <cstdio>
#include <thread>

struct RobotUuid
{
	QString	m_uuid;
	bool m_result;

	RobotUuid()
	{
		m_uuid = "";
		m_result = false;
	}

	RobotUuid(QString uuid)
	{
		m_uuid = uuid;
		m_result = false;
	}

	operator QVariant() const
	{
		return QVariant::fromValue(*this);
	}
};


typedef	QList<RobotUuid> RobotUuidArray;

Q_DECLARE_METATYPE(RobotUuid)
Q_DECLARE_METATYPE(RobotUuidArray)

class RobotClient : public QObject
{
	Q_OBJECT

public:
	RobotClient(QTcpSocket* socket, QObject* parent);
	~RobotClient();

private:
	QString	m_strUuid;		/*!< 唯一识别码 */
private:
	QTcpSocket* m_socket;	/*!< 客户端指针 */
	//QByteArray m_buf;
	//QThread	m_thread;
	//QTimer m_timer;
	QMutex m_mutex;
	std::thread* m_thread;
	bool m_bClose;
	std::chrono::steady_clock::time_point m_tpClock;
	QByteArray m_buf;
public:
	/*!
	 * @brief 获取当前时间日期
	 * @return QT_NAMESPACE::QString
	 * @since 2020/3/8 FanKaiyu
	 * 获取当前时间日期 格式为 YYYY/MM/DD hh:mm:ss
	 */
	static QString GetDate();
	/*!
	 * @brief 获取客户端地址
	 * @return QT_NAMESPACE::QString
	 * @since 2020/3/8 FanKaiyu
	 * 获取客户端地址信息，格式为 IP:端口
	 */
	QString GetAddress() const;
	/*!
	 * @brief 获取识别码
	 * @return QT_NAMESPACE::QString
	 * @since 2020/3/8 FanKaiyu
	 * 获取唯一识别码uuid
	 */
	QString GetUuid() const { return m_strUuid; }
signals:
	/*!
	 * @brief 接收到新的数据包
	 * @arg QByteArrayList 数据包列表
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端接收到新的数据包时发送此信号
	 */
	void NewPackages(QByteArrayList);

	/*!
	 * @brief 注册
	 * @arg QString 唯一识别码uuid
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端表明身份，注册信息时发送此信号
	 */
	void Recognition(QString uuid);

	/*!
	 * @brief 记录
	 * @arg QString 用户信息
	 * @arg QString 唯一识别码
	 * @arg QString	地址西悉尼
	 * @arg QString 内容类型
	 * @arg QString	内容文本
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端需要记录内容至数据库时发送此信号
	 */
	void Record(QString user, QString uuid, QString addr, QString type, QString text);

	/*!
	 * @brief 连接中断
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端连接中断时发出此信号
	 */
	void Disconnected();

	/*!
	 * @brief 订阅
	 * @arg RobotUuidArray
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端申请订阅其他客户端发送的信息时发送此信号
	 */
	void Subscribe(RobotUuidArray&);

	/*!
	 * @brief 取消订阅
	 * @arg RobotUuidArray
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端申请取消订阅其他客户端发送的信息时发送此信号
	 */
	void Unsubscribe(RobotUuidArray&);
private slots:
	/*!
	 * @brief 读取数据
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当有可以读取的数据时发送此函数
	 */
	void ReadData();

	/*!
	 * @brief 连接中断
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端连接中断时调用此函数
	 */
	void disconnected();
public slots:
	/*!
	 * @brief 发送数据包
	 * @arg QByteArrayList
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当客户端有数据包可以发送时调用此函数
	 */
	void SendPackage(QByteArrayList);

	/*!
	 * @brief 订阅客户端中断
	 * @return void
	 * @since 2020/3/8 FanKaiyu
	 * 当订阅的客户端中断连接时发送调用此函数
	 */
	void SubscriberBreak();
private:
	void Thread();
	QString CreatePackage(QString fUuid, QString tUuid, QJsonObject jCmd);
	QString CreatePackage(QString fUuid, QString tUuid, QJsonObject jCmd, QJsonObject jResult);
};
