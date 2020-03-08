#pragma once

#include <QObject>

class RobotEyes : public QObject
{
	Q_OBJECT

public:
	RobotEyes(QObject* parent);
	~RobotEyes();
public:
	// TODO 控制RobotEyes(摄像头)抬头的函数
	bool LookUp();
	// TODO 控制RobotEyes(摄像头)低头的函数
	bool LookDown();
	// TODO 控制RobotEyes(摄像头)左转的函数
	bool TurnLeft();
	// TODO 控制RobotEyes(摄像头)右转的函数
	bool TurnRight();
	// TODO 接收来自RobotEyes(摄影头)的图像信息
};
