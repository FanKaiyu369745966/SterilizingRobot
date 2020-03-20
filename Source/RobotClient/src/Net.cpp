#include "Net.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <QTimer>
#include "Config.h"

Net::Net(QObject *parent) : QTcpSocket(parent)
{
    m_reconnTimes = 0;
    m_move = "";
    m_speedL = m_speedR = 0;

    Config config("./config/config.ini");
    m_speedLine = config.get("RobotSpeed", "SpeedLine").toInt();
    m_speedArc = config.get("RobotSpeed", "SpeedArc").toInt();

    abort();
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadData()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onReadError(QAbstractSocket::SocketError)));
}

Net::~Net()
{
    Config config("./config/config.ini");
    config.set("RobotSpeed", "SpeedLine", m_speedLine);
    config.set("RobotSpeed", "SpeedArc", m_speedArc);
}

/**
 * @brief connectServer 连接服务器
 * @param ip 网络地址
 * @param port 端口
 */
void Net::connectServer(QString ip, int port)
{
    this->connectToHost(ip, port);
    if (!this->waitForConnected(5000))
    {
        qDebug()<<"连接服务器失败!";
        emit connectFail();
    }

    return;
}

/**
 * @brief disConnectServer 断开与服务器之间的连接
 */
void Net::disConnectServer()
{
    this->disconnectFromHost();
    if (this->state() == QAbstractSocket::UnconnectedState || this->waitForDisconnected(1000))
    {
        qDebug()<<"断开连接成功.";
    }
    else
    {
        qDebug()<<"断开连接失败.";
    }

    return;
}

/**
 * @brief sendData 发送数据
 * @param data 数据
 */
void Net::sendData(QString data)
{
    if(!data.isEmpty())
    {
        int len = this->write(data.toLatin1());
        this->flush();
        qDebug()<<"发送至服务器数据长度: "<<len;

        // 长度=-1，说明与服务器的连接中断，重连服务器
        if(len == -1)
        {
            emit connectFail();
        }
    }

    return;
}

/**
 * @brief onReadData 响应接收信号
 */
void Net::onReadData()
{
    QByteArray buffer = this->readAll();
    if(!buffer.isEmpty())
    {
        dealData(buffer);
    }

    return;
}

/**
 * @brief onReadError 响应接收错误信号
 */
void Net::onReadError(QAbstractSocket::SocketError error)
{
    disConnectServer();
    qDebug()<<QString("接收错误描述:%1").arg(this->errorString());

    return;
}


/**
 * @brief dealData  处理接收到的数据
 * @param data 接收的数据
 */
void Net::dealData(QByteArray data)
{
    QString recvData = data;
    QStringList list = recvData.split("|");

    for(int i=0; i<list.size(); i++)
    {
        QString strJson = list[i];

        QJsonObject obj;
        QJsonParseError jsonError;
        QJsonDocument doc(QJsonDocument::fromJson(strJson.toUtf8(), &jsonError));

        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug()<<"form server json error:"<<jsonError.error;
            continue;
        }
        if(doc.isObject())
        {
            qDebug()<<"-------------------------------------recv server.";
            obj = doc.object();
            QJsonValue value;
            value = obj.take("From");
            QString strFrom = value.toString();
            value = obj.take("To");
            QString strTo = value.toString();
            value = obj.take("Date");
            QString strDate = value.toString();
            value = obj.take("Cmd");
            QJsonObject objCmd = value.toObject();
            if(objCmd.isEmpty())
            {
                qDebug()<<"指令为空.";
                return;
            }

            QJsonArray cmdTake = objCmd.value("Take").toArray();
            QJsonArray cmdRemove = objCmd.value("Remove").toArray();
            int cmdHeart = objCmd.value("Heart").toInt();

            /*********************************握手***************************************/
            if(objCmd.contains("Hand"))
            {
                int cmdHand = objCmd.value("Hand").toInt();

                // 服务器第一条握手询问指令
                if(strFrom.isEmpty() && strTo.isEmpty() && cmdHand == 0)
                {
                    qDebug()<<"收到服务器的第一条握手指令，日期："<<strDate;
                    sendHandMakesure();
                    return;
                }
                // 服务器第二条握手确认指令
                if(strFrom.isEmpty() && strTo == ROBOTCLIENT_UUID && cmdHand == 0)
                {
                    qDebug()<<"收到服务器第二条握手确认指令，日期："<<strDate;
                    qDebug()<<"网络连接成功，开始发送图像...";
                    emit handFinish();
                    return;
                }

                return;
            }

            /*********************************控制***************************************/
            qDebug()<<"收到服务器的控制指令，日期："<<strDate;
            if(objCmd.contains("Control"))
            {
                QJsonObject cmdCtrl = objCmd.value("Control").toObject();
                if(!cmdCtrl.isEmpty())
                {
                    QStringList listCmdCtrl = cmdCtrl.keys();
                    for(int i=0; i<listCmdCtrl.size(); i++)
                    {
                        if(listCmdCtrl[i]=="Base")
                        {
                            QString orientation = cmdCtrl.value(listCmdCtrl[i]).toString();     // MoveOn 底盘向前移动 MoveBack 底盘后退 TurnLeft 左转 TurnRight 右转

                            m_move = orientation;

                            // 前进 线速度
                            if(orientation == "MoveOn")
                            {
                                m_speedL = m_speedR = m_speedLine;
                            }
                            // 后退 线速度
                            else if(orientation == "MoveBack")
                            {
                                m_speedL = m_speedR = -m_speedLine;
                            }
                            // 左转 角速度
                            else if(orientation == "TurnLeft")
                            {
                                m_speedL = -m_speedArc;
                                m_speedR = m_speedArc;
                            }
                            // 右转 角速度
                            else if(orientation == "TurnRight")
                            {
                                m_speedL = m_speedArc;
                                m_speedR = -m_speedArc;
                            }

                            // 发送底盘移动信号
                            emit underpanMove(m_speedL, m_speedR);
                        }
                        if(listCmdCtrl[i]=="Spray")
                        {
                            m_spray = cmdCtrl.value(listCmdCtrl[i]).toBool();

                            // 发送底盘喷雾信号
                            emit underpanSpray(m_spray);
                        }

                        if(listCmdCtrl[i]=="LSpeed")
                        {
                            m_speedLine = cmdCtrl.value(listCmdCtrl[i]).toInt();
                        }
                        if(listCmdCtrl[i]=="ASpeed")
                        {
                            m_speedArc = cmdCtrl.value(listCmdCtrl[i]).toInt();
                        }

                        if(listCmdCtrl[i]=="Eyes")
                        {
                            // 发送摄像头云台控制信号
                            emit cameraCtrl(cmdCtrl.value(listCmdCtrl[i]).toString());
                        }
                    }

                    //bool light = cmdCtrl.value("LightSwitch").toBool();       // 辅助灯开关 true为开，false为关
                }
            }
        }
    }

    return;
}

/**
 * @brief sendHandMakesure 发送握手确认指令给服务器
 */
void Net::sendHandMakesure()
{
    QVariantHash data;
    data.insert("From", ROBOTCLIENT_UUID);
    data.insert("To", "");
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString strDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss");
    data.insert("Date", strDate);
    QVariantHash childData;
    childData.insert("Hand", 0);
    data.insert("Cmd", childData);
    QJsonObject obj = QJsonObject::fromVariantHash(data);
    QString strHandCmd = QJsonDocument(obj).toJson();
    sendData(strHandCmd);

    return;
}

/**
 * @brief sendCameraData 发送摄像头图片编码数据
 * @param data 图片编码
 */
void Net::sendCameraData(QByteArray data)
{
    QString strData = data;

    QVariantHash jsonData;
    jsonData.insert("From", ROBOTCLIENT_UUID);
    jsonData.insert("To", "");
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString strDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss");
    jsonData.insert("Date", strDate);
    QVariantHash childData;
    childData.insert("Camera", data);
    jsonData.insert("Cmd", childData);
    QJsonObject obj = QJsonObject::fromVariantHash(jsonData);
    QString strCameraCmd = QJsonDocument(obj).toJson();

    sendData("|"+strCameraCmd);

    return;
}

/**
 * @brief sendUnderpanState 发送底盘状态
 * @param spray          喷雾器状态
 * @param electric       电量
 * @param water          水量
 * @param obsta          避障
 */
void Net::sendUnderpanState(bool spray, int electric, int water, int obsta)
{
    QVariantHash jsonData;
    jsonData.insert("From", ROBOTCLIENT_UUID);
    jsonData.insert("To", "");
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString strDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss");
    jsonData.insert("Date", strDate);

    QVariantHash objDevice;
    objDevice.insert("Base", m_move);
    objDevice.insert("LSpeed", m_speedLine);
    objDevice.insert("ASpeed", m_speedArc);
    objDevice.insert("Spray", spray);
    objDevice.insert("Electric", electric);
    objDevice.insert("Water", water);
    objDevice.insert("Obsta", obsta);

    QVariantHash objCmd;
    objCmd.insert("Device", objDevice);
    jsonData.insert("Cmd", objCmd);

    QJsonObject obj = QJsonObject::fromVariantHash(jsonData);
    QString strData = QJsonDocument(obj).toJson();

    sendData(strData);
}
