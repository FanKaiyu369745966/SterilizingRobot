#pragma once

#include <QWidget>

//#include "ui_SLAMMapWidget.h"
#include "ImageWidge.h"

class SLAMMapWidget : public ImageWidge
{
	Q_OBJECT

public:
	SLAMMapWidget(QWidget* parent = Q_NULLPTR);
	~SLAMMapWidget();

private:
	//Ui::SLAMMapWidget ui;

};
