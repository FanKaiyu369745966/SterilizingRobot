#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RobotRemoteControl.h"

class RobotRemoteControl : public QMainWindow
{
	Q_OBJECT

public:
	RobotRemoteControl(QWidget *parent = Q_NULLPTR);

private:
	Ui::RobotRemoteControlClass ui;
};
