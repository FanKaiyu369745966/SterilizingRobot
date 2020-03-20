#ifndef NET_H
#define NET_H

#include <QTcpSocket>
#include <QHostAddress>

#define ROBOTCLIENT_UUID "1001"

namespace Ui {
class Net;
}

class Net : public QTcpSocket
{
    Q_OBJECT

public:
    explicit Net(QObject *parent = 0);
    ~Net();

public:
    /**
     * @brief connectServer 连接服务器
     * @param ip 网络地址
     * @param port 端口
     */
    void connectServer(QString ip, int port);

    /**
     * @brief disConnectServer 断开与服务器之间的连接
     */
    void disConnectServer();

    /**
     * @brief sendData 发送数据
     * @param data 数据
     */
    void sendData(QString data);

private slots:

    /**
     * @brief onReadData 响应接收信号
     */
    void onReadData();

    /**
     * @brief onReadError 相应接收错误信号
     */
    void onReadError(QAbstractSocket::SocketError);

signals:
    /**
     * @brief connectFail   连接服务器失败
     */
    void connectFail();

    /**
     * @brief handFinish 握手完成信号
     * @details 发送给主窗口，让其处理剩余网络操作
     */
    void handFinish();

    /**
     * @brief underpanMove  底盘移动信号
     * @param speedL        左轮速度
     * @param speedR        右轮速度
     */
    void underpanMove(int speedL, int speedR);

    /**
     * @brief underpanSpray 底盘喷雾信号
     * @param isSpray       喷雾开关 true 开， false 关
     */
    void underpanSpray(bool isSpray);


    /**
     * @brief cameraCtrl 摄像头云台控制信号
     * @param camera 控制方向   LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
     */
    void cameraCtrl(QString camera);

private:
    /**
     * @brief dealData  处理接收到的数据
     * @param data 接收的数据
     */
    void dealData(QByteArray data);

    /**
     * @brief sendHandMakesure 发送握手确认指令给服务器
     */
    void sendHandMakesure();

public:
    /**
     * @brief sendCameraData 发送摄像头图片编码数据
     * @param data 图片编码
     */
    void sendCameraData(QByteArray data);

    /**
     * @brief sendUnderpanState 发送底盘状态
     * @param spray          喷雾器状态
     * @param electric       电量
     * @param water          水量
     * @param obsta          避障
     */
    void sendUnderpanState(bool spray, int electric, int water, int obsta);

private:
    int m_reconnTimes;
    QString m_move;   // MoveOn 底盘向前移动 MoveBack 底盘后退 TurnLeft 左转 TurnRight 右转
    int m_speedLine;  // 移动时的线速度百分比
    int m_speedArc;   // 转向时的角速度百分比

    bool m_spray;     //  喷雾器状态


    int m_speedL;     // 左轮速度
    int m_speedR;     // 右轮速度
};

#endif // NET_H
