#pragma once

#include <QWidget>
#include <QImageReader>
#include <QBuffer>
#include <QPainter>
//#include "ui_ImageWidge.h"

class ImageWidge : public QWidget
{
	Q_OBJECT

public:
	ImageWidge(QWidget* parent = Q_NULLPTR);
	~ImageWidge();

private:
	//Ui::ImageWidge ui;
protected:
	QPixmap* m_pix;
	QImage* m_img;
private:
	void Initialize();
public:
	void Load(QByteArray data, QString type);
	void Load(QString path);
	void Load(QString path, QString type);
protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void DrawImage(QPainter&, QRect);
};
