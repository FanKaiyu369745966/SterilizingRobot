#include "ImageWidge.h"
#include <QDebug>

ImageWidge::ImageWidge(QWidget* parent)
	: QWidget(parent)
	, m_pix(nullptr)
{
	// ui.setupUi(this);
	Initialize();
}

ImageWidge::~ImageWidge()
{

}

void ImageWidge::Initialize()
{
	setAutoFillBackground(true);			//自动设定背景颜色
	setPalette(QPalette(Qt::gray));		//设置调色板的颜色为灰色
	m_pix = new QPixmap(size());			//这个pixmap对象用来接受准备绘制到空间的内容
	m_pix->fill(Qt::gray);					//填充这个图片的背景是灰色

	return;
}

void ImageWidge::Load(QByteArray data, QString type)
{
	QBuffer buffer(&data);
	buffer.open(QIODevice::ReadOnly);

	QImageReader _reader(&buffer, type.toLatin1());

	*m_pix = QPixmap::fromImageReader(&_reader);

	m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::Load(QString path)
{
	QImage img(path);

	*m_pix = QPixmap::fromImage(img);

	m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::Load(QString path, QString type)
{
	QImageReader _reader;
	_reader.setFileName(path);
	_reader.setFormat(type.toLatin1());

	*m_pix = QPixmap::fromImageReader(&_reader);
	m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);						//得到当前控件绘制工具

	painter.drawPixmap(this->rect(), *m_pix);     //重0,0开始绘制这个图片

	return;
}

void ImageWidge::resizeEvent(QResizeEvent* event)
{
	qDebug() << m_pix->width() << ":" << m_pix->height();

	double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}
