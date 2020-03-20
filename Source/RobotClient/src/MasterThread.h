#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QBuffer>

#include "public/public.h"
#include "public/common.h"

class MasterThread : public QThread
{
    Q_OBJECT
public:
    explicit MasterThread(QObject *parent = nullptr);
    ~MasterThread();

    void startRun(long userid, long channel);

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

    void cameraCapture(QString, QByteArray);
private:
    void run() override;

private:
    long m_userid;
    long m_channel;
    LPNET_DVR_JPEGPARA m_para;


    bool m_threadSwitch;


private:
    /**
     * @brief toBase64 图片转base64编码
     * @param imgPath 图片路径
     * @return base64数据
     */
    QByteArray toBase64(QString imgPath);
};

#endif // MASTERTHREAD_H
