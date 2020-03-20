#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include "public/public.h"
#include "public/common.h"
#include "MasterThread.h"
#include "Net.h"
#include "Config.h"
#include "SerialPort.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonLeft_clicked();
    void on_pushButtonRight_clicked();

/**************************************************网络*************************************************************/
private:
    Net *m_net;
    QString m_serverIP;
    int m_serverPort;

private slots:

    /**
     * @brief onConnectFail 连接服务器失败
     */
    void onConnectFail();
    /**
     * @brief onHandFinish 响应握手完成信号
     */
    void onHandFinish();

    /**
     * @brief onUnderpanMove  响应底盘移动信号
     * @param speedL        左轮速度
     * @param speedR        右轮速度
     */
    void onUnderpanMove(int speedL, int speedR);

    /**
     * @brief onUnderpanSpray   响应底盘喷雾信号
     * @param isSpray 喷雾开关 true 开， false 关
     */
    void onUnderpanSpray(bool isSpray);

/**************************************************摄像头*************************************************************/
private:
    int m_rpCurrentRealHandle;
    int m_ptzSwitchUp;
    int m_ptzSwitchDown;
    int m_ptzSwitchLeft;
    int m_ptzSwitchRight;
    long m_userID;
    MasterThread *m_thread;

    QTimer *m_cameraCtrlTimer;
    QString m_preOrientation;


private:
    /**
     * @brief 
     */
    void clearImages();
    /**
     * @brief ptzControlRealPlay 云台控制
     * @param command 云台控制命令
     * @param flag 云台停止动作或开始动作:0- 开始,1- 停止
     */
    void ptzControlRealPlay(int command, int flag);


    /**
     * @brief ctrlCameraOrientation 控制摄像头方向
     * @param orientation 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
     */
    void ctrlCameraOrientation(QString orientation);


    /**
     * @brief ctrlCameraOrientation 控制摄像头方向
     * @param orientation 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
     * @param flag 0 开， 1 停止
     */
    void ctrlCameraOrientation(QString orientation, int flag);


    /**
     * @brief getSDKVersion 获取摄像头SDK版本
     * @return
     */
    void getSDKVersion();


    /**
     * @brief initCamera 初始化摄像头
     */
    void initCamera();

private slots:
    /**
     * @brief onCameraCapture   响应摄像头截图信号
     * @param fileName  图片文件
     * @param imagesData 图片编码
     */
    void onCameraCapture(QString fileName, QByteArray imagesData);

    /**
     * @brief onCameraCtrl 响应摄像头云台控制信号
     * @param camera 控制方向   LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
     */
    void onCameraCtrl(QString camera);


    /**
     * @brief onCameraCtrlTimeout 响应摄像头控制超时
     */
    void onCameraCtrlTimeout();

/**************************************************串口*************************************************************/
private:
     SerialPort *m_serailPort;

private slots:

    /**
     * @brief onOpenSerialPortResult 打开串口结果
     * @param bResult true 成功， false 失败
     */
    void onOpenSerialPortResult(bool bResult);


    /**
     * @brief onUnderpanState 响应底盘状态信号
     * @param spray          喷雾器状态
     * @param electric       电量
     * @param water          水量
     * @param obsta          避障
     */
    void onUnderpanState(bool spray, int electric, int water, int obsta);

    void on_pushButtonSetPoint_clicked();

    void on_pushButtonGoPoint_clicked();

signals:
    /**
     * @brief openSerialPort 打开串口
     */
    void openSerialPort(QString, int, int, int);

    /**
     * @brief sendSerialPort 发送串口数据
     */
    void sendSerialPort(QByteArray);

};
#endif // MAINWINDOW_H
