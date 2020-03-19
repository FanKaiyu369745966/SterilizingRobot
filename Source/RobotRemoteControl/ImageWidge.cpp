#include "ImageWidge.h"
#include <QDebug>

ImageWidge::ImageWidge(QWidget* parent)
	: QWidget(parent)
	, m_img(nullptr)
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
	//m_pix = new QPixmap(size());			//这个pixmap对象用来接受准备绘制到空间的内容
	//m_pix->fill(Qt::gray);					//填充这个图片的背景是灰色

	m_img = new QImage();
	m_img->fill(Qt::gray);

	return;
}

void ImageWidge::Load(QByteArray data, QString type)
{
	QBuffer buffer(&data);
	buffer.open(QIODevice::ReadOnly);

	QImageReader _reader(&buffer, type.toLatin1());

	*m_img = _reader.read();

	//qDebug() << data.size();

	*m_img = m_img->scaled(320, 180).scaled(this->size(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
	//m_img->scaled(this->size(), Qt::KeepAspectRatio, Qt::TransformationMode::FastTransformation);

	//qDebug() << m_img->size();

	double scal = (double)(m_img->width()) / (double)(m_img->height());

	//*m_pix = QPixmap::fromImage(_reader.read());

	//m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	//double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::Load(QString path)
{
	*m_img = QImage(path);

	*m_img = m_img->scaled(320, 180).scaled(this->size(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);

	double scal = (double)(m_img->width()) / (double)(m_img->height());

	//*m_pix = QPixmap::fromImage(img);

	//m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	//double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::Load(QString path, QString type)
{
	QImageReader _reader;
	_reader.setFileName(path);
	_reader.setFormat(type.toLatin1());

	*m_img = _reader.read();

	*m_img = m_img->scaled(320, 180).scaled(this->size(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);

	double scal = (double)(m_img->width()) / (double)(m_img->height());

	//*m_pix = QPixmap::fromImageReader(&_reader);
	//m_pix->scaled(this->size(), Qt::KeepAspectRatioByExpanding);

	//double scal = (double)(m_pix->width()) / (double)(m_pix->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);						//得到当前控件绘制工具

	//painter.drawPixmap(this->rect(), *m_pix);     //重0,0开始绘制这个图片

	DrawImage(painter, rect());

	return;
}

void ImageWidge::resizeEvent(QResizeEvent* event)
{
	//qDebug() << m_pix->width() << ":" << m_pix->height();

	//double scal = (double)(m_pix->width()) / (double)(m_pix->height());
	double scal = (double)(m_img->width()) / (double)(m_img->height());

	setFixedWidth(scal * height());

	update();

	return;
}

void ImageWidge::DrawImage(QPainter& painter, QRect rect)
{
	//painter.drawPixmap(rect, QPixmap::fromImage(*m_img));
	painter.drawImage(rect, *m_img);

	return;
}
