#pragma once

#include <QObject>
#include "RobotBase.h"
#include "RobotEyes.h"
#include "Spray.h"

class Robot : public QObject
{
	Q_OBJECT

public:
	Robot(QObject* parent);
	~Robot();
public:
	// TODO 控制RobotLight(辅助灯)开关的函数
	bool LightSwitch(bool);
	// TODO 接收来自Robot的图像信息
};
