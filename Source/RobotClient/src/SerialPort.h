#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>


class SerialPort: public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = nullptr);
    ~SerialPort();

private:
    QSerialPort m_serialPort;   // 串口类对象


public slots:
    /**
     * @brief onSerialPortRecv 接收串口数据信号槽
     */
    void onSerialPortRecv();


    /**
     * @brief onOpenSerialPort 打开串口
     * @param com       串口号
     * @param baud      波特率
     * @param databit   数据位
     * @param stopbit   停止位
     */
    void onOpenSerialPort(QString com, int baud, int databit, int stopbit);

    /**
     * @brief onSendSerialPort 响应发送串口
     * @param data 发送数据
     */
    void onSendSerialPort(QByteArray data);


signals:
    /**
     * @brief openSerialPortResult 打开串口结果
     * @param bResult true 成功， false 失败
     */
    void openSerialPortResult(bool bResult);

    /**
     * @brief underpanState 底盘状态信号
     * @param spray         喷雾器状态
     * @param electric      电量
     * @param water         水量
     * @param obsta         避障
     */
    void underpanState(bool spray, int electric, int water, int obsta);
};

#endif // SERIALPORT_H
