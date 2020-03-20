#include "SerialPort.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

SerialPort::SerialPort(QWidget *parent) : QWidget(parent)
{

}

SerialPort::~SerialPort()
{

}

/**
 * @brief onOpenSerialPort 打开串口
 * @param com       串口号
 * @param baud      波特率
 * @param databit   数据位
 * @param stopbit   停止位
 */
void SerialPort::onOpenSerialPort(QString com, int baud, int databit, int stopbit)
{
    // 判断串口当前状态， 如果打开则将之关闭
    if(m_serialPort.isOpen())
    {
        m_serialPort.clear();
        m_serialPort.close();
    }

    // 串口
    m_serialPort.setPortName(com);

    // 打开串口失败
    if(! m_serialPort.open(QIODevice::ReadWrite))
    {
        emit openSerialPortResult(false);
        return;
    }
    // 打开串口成功
    m_serialPort.setBaudRate(baud, QSerialPort::AllDirections);         // 波特率
    m_serialPort.setDataBits(QSerialPort::DataBits(databit));           // 数据位
    m_serialPort.setParity(QSerialPort::Parity(QSerialPort::NoParity)); // 校验位
    m_serialPort.setStopBits(QSerialPort::StopBits(stopbit));           // 停止位
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);            // 流控制

    // 接收槽
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortRecv()));

    emit openSerialPortResult(true);
}


/**
 * @brief onSerialPortRecv 接收串口数据信号槽
 */
void SerialPort::onSerialPortRecv()
{
    bool ok = m_serialPort.waitForReadyRead(10);
    if(!ok)
    {
        qDebug()<<"串口等待准备读取超时!";
        return;
    }

    QString readData = m_serialPort.readAll();
    while(1)
    {
        ok = m_serialPort.waitForReadyRead(10);
        if(!ok)
        {
            break;
        }

        readData += m_serialPort.readAll();
    }

    QStringList listData = readData.split("|");
    for(int i=0; i<listData.size(); i++)
    {
        QString data = listData[i];

        if(data.length() < 10)
        {
            continue;
        }

        // 解析json数据
        QJsonObject obj;
        QJsonParseError jsonError;
        QJsonDocument doc(QJsonDocument::fromJson(data.toUtf8(), &jsonError));

        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug()<<"from underpan json error:"<<jsonError.error<<jsonError.errorString();
            continue;
        }
        if(doc.isObject())
        {
            qDebug()<<"************************************recv underpan.";
            obj = doc.object();
            QJsonValue value;
            int spray = 0;
            int electric = 0;
            int water = 0;
            int obsta = 0;
            QString orientation;
            if(obj.contains("State"))
            {
                value = obj.take("State");
                QJsonObject objState = value.toObject();
                if(objState.contains("Spray"))
                {
                    spray = objState.value("Spray").toInt();
                }
                if(objState.contains("Obsta"))
                {
                   obsta = objState.value("Obsta").toInt();
                }
            }
            if(obj.contains("Data"))
            {
                value = obj.take("Data");
                QJsonObject objData = value.toObject();
                if(objData.contains("Electric"))
                {
                   electric = objData.value("Electric").toInt();
                }
                if(objData.contains("Water"))
                {
                    water = objData.value("Water").toInt();
                }
            }

            qDebug()<<spray<<electric<<water<<obsta;
            // 发送底盘状态信号
            emit underpanState(spray, electric, water, obsta);
        }
    }
}

/**
 * @brief onSendSerialPort 响应发送串口
 * @param data 发送数据
 */
void SerialPort::onSendSerialPort(QByteArray data)
{
    if(!data.isEmpty())
    {
        qDebug()<<"send underpan: "<<data;
        m_serialPort.write(data);
    }
}
