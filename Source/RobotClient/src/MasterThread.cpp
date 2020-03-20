#include "MasterThread.h"

MasterThread::MasterThread(QObject *parent) : QThread(parent)
{
    m_threadSwitch = true;
}

MasterThread::~MasterThread()
{
    m_threadSwitch = false;

    quit();
    wait();
    deleteLater();
}

void MasterThread::startRun(long userid, long channel)
{
    if(!isRunning())
    {
        m_userid = userid;
        m_channel = channel;

        start();
    }
}

void MasterThread::run()
{
    while(m_threadSwitch)
    {
        QString filename = "./images/";
        filename += QUuid::createUuid().toString();
        QByteArray fileName = filename.toLatin1();
        bool bCapSuccess = true;
        LPNET_DVR_JPEGPARA para;
        if(!NET_DVR_CaptureJPEGPicture(m_userid, m_channel, para, fileName.data()))
        {
            bCapSuccess = false;
            qDebug()<<"截取图片失败！";
        }

        if(bCapSuccess)
        {
            QByteArray ba = toBase64(filename);
            emit cameraCapture(filename, ba);
        }

        msleep(25);
    }

}


/**
 * @brief toBase64 图片转base64编码
 * @param imgPath 图片路径
 * @return base64数据
 */
QByteArray MasterThread::toBase64(QString imgPath)
{
    QImage image(imgPath);
    image = image.scaled(320, 180,Qt::AspectRatioMode::IgnoreAspectRatio, Qt::FastTransformation);
    QByteArray ba;
    QBuffer buf(&ba);
    image.save(&buf, "jpg");
    QByteArray base64 = ba.toBase64();
    buf.close();
    return base64;
}
