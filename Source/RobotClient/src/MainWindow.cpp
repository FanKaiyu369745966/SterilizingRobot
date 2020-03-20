#include "MainWindow.h"
#include "ui_MainWindow.h"

// 摄像头异常回调
void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    qDebug("ExceptionCallBack lUserID:%d, handle:%d, user data:%p", lUserID, lHandle, pUser);

    switch(dwType)
    {
    case EXCEPTION_AUDIOEXCHANGE:		//Audio exchange exception
        qDebug()<<"Audio exchange exception!";
        //TODO: close audio exchange
        break;
        // Alarm
    case EXCEPTION_ALARM:			   //Alarm exception
        qDebug()<<"Alarm exception!";
        //TODO: close alarm update
        break;
    case EXCEPTION_ALARMRECONNECT:  //Alarm reconnect
        qDebug()<<"Alarm reconnect.";
        break;
    case ALARM_RECONNECTSUCCESS:      //Alarm reconnect success
        qDebug()<<"Alarm reconnect success.";
        break;
    case EXCEPTION_SERIAL:			           //Serial exception
        qDebug()<<"Serial exception!";
        //TODO: close exception
        break;
        // Preview
    case EXCEPTION_PREVIEW:			     //Preview exception
        qDebug()<<"Preview exception!";
        //TODO: close preview
        break;
    case EXCEPTION_RECONNECT:			 //preview reconnect
        qDebug()<<"preview reconnecting.";
        break;
    case PREVIEW_RECONNECTSUCCESS: //Preview reconnect success
        qDebug()<<"Preview reconncet success.";
        break;
    default:
        break;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 清空无效图片
    clearImages();

    // 摄像头截图
    m_thread = new MasterThread(this);
    connect(m_thread, SIGNAL(cameraCapture(QString, QByteArray)), this, SLOT(onCameraCapture(QString, QByteArray)));

    // 摄像头
    initCamera();

    // 网络
    m_net = new Net(this);
    connect(m_net, SIGNAL(connectFail()), this, SLOT(onConnectFail())); // 网络连接失败
    connect(m_net, SIGNAL(handFinish()), this, SLOT(onHandFinish()));   // 握手完成
    connect(m_net, SIGNAL(underpanMove(int, int)), this, SLOT(onUnderpanMove(int, int)));   // 底盘移动
    connect(m_net, SIGNAL(underpanSpray(bool)), this, SLOT(onUnderpanSpray(bool)));   // 底盘喷雾
    connect(m_net, SIGNAL(cameraCtrl(QString)), this, SLOT(onCameraCtrl(QString))); // 摄像头控制
    Config config("./config/config.ini");
    m_serverIP = config.get("Server", "ip").toString();
    m_serverPort = config.get("Server", "port").toInt();
    m_net->connectServer(m_serverIP, m_serverPort);


    // 初始化串口
    m_serailPort = new SerialPort(this);
    connect(this, SIGNAL(openSerialPort(QString, int, int, int)), m_serailPort, SLOT(onOpenSerialPort(QString, int, int, int))); // 打开串口
    connect(m_serailPort, SIGNAL(openSerialPortResult(bool)), this, SLOT(onOpenSerialPortResult(bool)));  // 打开串口结果
    connect(this, SIGNAL(sendSerialPort(QByteArray)), m_serailPort, SLOT(onSendSerialPort(QByteArray)));        // 写串口数据
    connect(m_serailPort, SIGNAL(underpanState(bool, int, int, int)), this, SLOT(onUnderpanState(bool, int, int, int)));  // 底盘状态
}

MainWindow::~MainWindow()
{
    //    //关闭预览
    //    NET_DVR_StopRealPlay(m_rpCurrentRealHandle);
    //    //注销用户
    //    NET_DVR_Logout(m_userID);
    //    NET_DVR_Cleanup();

    delete ui;
}

/**
 * @brief clearImages clear images
 */
void MainWindow::clearImages()
{
    QDir dir("./images");
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        //if(mfi.isFile() && mfi.suffix()=="jpg")
        dir.remove(mfi.fileName());
    }
}
/**************************************************摄像头*************************************************************/
/**
 * @brief initCamera 初始化摄像头
 */
void MainWindow::initCamera()
{
    m_cameraCtrlTimer = new QTimer(this);
    connect(m_cameraCtrlTimer, SIGNAL(timeout()), this, SLOT(onCameraCtrlTimeout()));
    m_preOrientation = "";

    m_userID = -1;
    m_ptzSwitchUp = 0;
    m_ptzSwitchDown = 0;
    m_ptzSwitchLeft = 0;
    m_ptzSwitchRight = 0;

    // 初始化SDK
    if (!NET_DVR_Init())
    {
        qDebug()<<"Init camera sdk faile! info:"<<QString("SDK_LAST_ERROR=%1").arg(NET_DVR_GetLastError());
        return;
    }
    qDebug()<<"Init camera sdk success.";

    // 日志
    bool bRet = NET_DVR_SetLogToFile(3, "./sdkLog", false);
    NET_DVR_SetLogPrint(true);
    qDebug()<<QString("set camera log file result: %1").arg(bRet);

    // 设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    // 注册设备
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.2.64", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "brain123", NAME_LEN);

    m_userID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (m_userID == -1)
    {
        qDebug()<<QString("注册设备失败：%1").arg(NET_DVR_GetLastError());
        return;
    }
    qDebug()<<QString("注册设备成功！");


    // 设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL, ExceptionCallBack, NULL);

    //启动预览并设置回调数据流
    LONG lRealPlayHandle;
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd = (HWND)ui->frame->winId(); //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    struPlayInfo.lChannel = 1; //预览通道号
    struPlayInfo.dwStreamType = 0; //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 1; //0- 非阻塞取流,1- 阻塞取流


    lRealPlayHandle = NET_DVR_RealPlay_V40(m_userID, &struPlayInfo, NULL, NULL);
    if (lRealPlayHandle < 0)
    {
        qDebug()<<"NET_DVR_RealPlay_V40 error!";
        NET_DVR_Logout(m_userID);
        NET_DVR_Cleanup();
        return;
    }
    m_rpCurrentRealHandle = lRealPlayHandle;

    // 获取版本
    //getSDKVersion();

}

/**
 * @brief ptzControlRealPlay 云台控制
 * @param command 云台控制命令
 * @param flag 云台停止动作或开始动作:0- 开始,1- 停止
 */
void MainWindow::ptzControlRealPlay(int command, int flag)
{
    if (!NET_DVR_PTZControlWithSpeed(m_rpCurrentRealHandle, command, flag, 5))
    {
        qDebug()<<QString("云台控制错误：%1").arg(NET_DVR_GetLastError());
    }

    // 当摄像头为开始旋转时，1s后停止旋转
    if(flag == 0)
    {
        m_cameraCtrlTimer->start(500);
    }
}

/**
 * @brief ctrlCameraOrientation 控制摄像头方向
 * @param orientation LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
 */
void MainWindow::ctrlCameraOrientation(QString orientation)
{
    if(orientation=="LookUp")
    {
        if (m_ptzSwitchDown == 0)
        {
            m_ptzSwitchDown = 1;
        }
        else
        {
            m_ptzSwitchDown = 0;
        }
        ptzControlRealPlay(TILT_DOWN, m_ptzSwitchDown);
    }
    else if(orientation=="LookDown")
    {
        if (m_ptzSwitchUp == 0)
        {
            m_ptzSwitchUp = 1;
        }
        else
        {
            m_ptzSwitchUp = 0;
        }
        ptzControlRealPlay(TILT_UP, m_ptzSwitchUp);
    }
    else if(orientation=="LookLeft")
    {
        if (m_ptzSwitchRight == 0)
        {
            m_ptzSwitchRight = 1;
        }
        else
        {
            m_ptzSwitchRight = 0;
        }
        ptzControlRealPlay(PAN_RIGHT, m_ptzSwitchRight);
    }
    else if(orientation=="LookRight")
    {
        if (m_ptzSwitchLeft == 0)
        {
            m_ptzSwitchLeft = 1;
        }
        else
        {
            m_ptzSwitchLeft = 0;
        }
        ptzControlRealPlay(PAN_LEFT, m_ptzSwitchLeft);
    }
    else
    {
        if(!NET_DVR_PTZPreset_Other(m_userID, 1, GOTO_PRESET, 1))
        {
            qDebug()<<"去预设点失败!";
        }
    }
}

/**
 * @brief ctrlCameraOrientation 控制摄像头方向
 * @param orientation 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
 * @param flag 0 开， 1 停止
 */
void MainWindow::ctrlCameraOrientation(QString orientation, int flag)
{
    // 当收到摄像头旋转控制时停止超时响应，并保存方向
    m_cameraCtrlTimer->stop();
    if(!orientation.isEmpty())
    {
        m_preOrientation = orientation;
    }

    if(orientation=="LookUp")
    {
        ptzControlRealPlay(TILT_DOWN, flag);
    }
    else if(orientation=="LookDown")
    {
        ptzControlRealPlay(TILT_UP, flag);
    }
    else if(orientation=="LookLeft")
    {
        ptzControlRealPlay(PAN_RIGHT, flag);
    }
    else if(orientation=="LookRight")
    {
        ptzControlRealPlay(PAN_LEFT, flag);
    }
    else
    {
        if(!NET_DVR_PTZPreset_Other(m_userID, 1, GOTO_PRESET, 1))
        {
            qDebug()<<"去预设点失败!";
        }
    }
}

void MainWindow::on_pushButtonUp_clicked()
{
    //ctrlCameraOrientation("LookUp");
    ctrlCameraOrientation("LookUp", 0);
}

void MainWindow::on_pushButtonDown_clicked()
{
    //ctrlCameraOrientation("LookDown");
    ctrlCameraOrientation("LookDown", 0);
}

void MainWindow::on_pushButtonLeft_clicked()
{
    //ctrlCameraOrientation("LookLeft");
    ctrlCameraOrientation("LookLeft", 0);
}

void MainWindow::on_pushButtonRight_clicked()
{
    //ctrlCameraOrientation("LookRight");
    ctrlCameraOrientation("LookRight", 0);
}

void MainWindow::on_pushButtonSetPoint_clicked()
{
    if(!NET_DVR_PTZPreset_Other(m_userID, 1, SET_PRESET, 1))
    {
        qDebug()<<"set preset fail";
    }
}

void MainWindow::on_pushButtonGoPoint_clicked()
{
    if(!NET_DVR_PTZPreset_Other(m_userID, 1, GOTO_PRESET, 1))
    {
        qDebug()<<"goto preset fail";
    }
}

/**
 * @brief getSDKVersion 获取摄像头SDK版本
 * @return
 */
void MainWindow::getSDKVersion()
{
    DWORD dwVersion = NET_DVR_GetSDKBuildVersion();
    QString strHCNetSDK;
    strHCNetSDK.sprintf("HCNetSDK V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
                        (0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));
    qDebug()<<strHCNetSDK;

    dwVersion = PlayM4_GetSdkVersion();
    QString strPlaySDKVersion;
    strPlaySDKVersion.sprintf("PlayCtrl V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
                              (0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));
    qDebug()<<strPlaySDKVersion;
}

/**
 * @brief onCameraCapture   响应摄像头截图信号
 * @param fileName  图片文件
 * @param imagesData 图片编码
 */
void MainWindow::onCameraCapture(QString fileName, QByteArray imagesData)
{
    m_net->sendCameraData(imagesData);

    // 删除已处理的图片
    QFile file(fileName);
    if(!file.remove())
    {
        qDebug()<<"删除图片文件失败，图片路径："<<fileName;
    }
}

/**
 * @brief onCameraCtrl 响应摄像头云台控制信号
 * @param camera 控制方向   LookUp 摄像头向上转 LookDown 摄像头向下转 LookLeft 摄像头向左转 LookRight 摄像头向右转
 */
void MainWindow::onCameraCtrl(QString camera)
{
    //ctrlCameraOrientation(camera);
    ctrlCameraOrientation(camera, 0);
}

/**
 * @brief onCameraCtrlTimeout 响应摄像头控制超时
 */
void MainWindow::onCameraCtrlTimeout()
{
    ctrlCameraOrientation(m_preOrientation, 1);     // 停止摄像头旋转
    m_cameraCtrlTimer->stop();                      // 停止摄像头控制超时定时器
}

/**************************************************网络*************************************************************/
/**
 * @brief onConnectFail 连接服务器失败
 */
void MainWindow::onConnectFail()
{
    qDebug()<<"尝试连接服务器...";
    m_net->connectServer(m_serverIP, m_serverPort);
}
/**
 * @brief onHandFinish 响应握手完成信号
 */
void MainWindow::onHandFinish()
{
    qDebug()<<"握手完成.";

    // 开启截图线程
    m_thread->startRun(m_userID, 1);

    // 打开串口
    Config config("./config/config.ini");
    QString com = config.get("SerialPort", "com").toString();
    int baud = config.get("SerialPort", "baud").toInt();
    int databit = config.get("SerialPort", "databit").toInt();
    int stopbit = config.get("SerialPort", "stopbit").toInt();
    emit openSerialPort(com, baud, databit, stopbit);
}


/**
 * @brief onUnderpanMove  响应底盘移动信号
 * @param speedL        左轮速度
 * @param speedR        右轮速度
 */
void MainWindow::onUnderpanMove(int speedL, int speedR)
{
    // 封装底盘移动json
    QVariantHash jsonData;
    QVariantHash moveData;
    moveData.insert("SPeedL", speedL);
    moveData.insert("SPeedR", speedR);
    jsonData.insert("Mov", moveData);
    QJsonObject obj = QJsonObject::fromVariantHash(jsonData);
    QString strMove = QJsonDocument(obj).toJson();

    // 发送底盘移动指令给底盘
    QByteArray data = strMove.toUtf8();
    emit sendSerialPort(data);
}

/**
 * @brief onUnderpanSpray   响应底盘喷雾信号
 * @param isSpray 喷雾开关 true 开， false 关
 */
void MainWindow::onUnderpanSpray(bool isSpray)
{
    // 封装底盘移动json
    QVariantHash jsonData;
    QVariantHash ctrlData;
    ctrlData.insert("Spray", isSpray ? 1 : 0);
    jsonData.insert("Ctrl", ctrlData);
    QJsonObject obj = QJsonObject::fromVariantHash(jsonData);
    QString strMove = QJsonDocument(obj).toJson();

    // 发送底盘喷雾指令给底盘
    QByteArray data = strMove.toUtf8();
    emit sendSerialPort(data);
}
/**************************************************串口*************************************************************/
/**
 * @brief onOpenSerialPortResult 打开串口结果
 * @param bResult true 成功， false 失败
 */
void MainWindow::onOpenSerialPortResult(bool bResult)
{
    if(!bResult)
    {
        qDebug()<<"串口打开失败！";
        return;
    }

}

/**
 * @brief onUnderpanState 响应底盘状态信号
 * @param spray          喷雾器状态
 * @param electric       电量
 * @param water          水量
 * @param obsta          避障
 */
void MainWindow::onUnderpanState(bool spray, int electric, int water, int obsta)
{
    m_net->sendUnderpanState(spray, electric, water, obsta);
}

