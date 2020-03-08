#pragma once

#include <QObject>

class RobotBase : public QObject
{
	Q_OBJECT

public:
	RobotBase(QObject* parent);
	~RobotBase();
public:
	quint8 m_byBattery;		/*!< 剩余电量的值,此值是一个代表剩余电量百分比的一个正整数 */
	quint8 m_byLineSpeed;	/*!< 当前线速度的值,此值是一个代表当前线速度百分比的一个正整数 */
	quint8 m_byArcSpeed;	/*!< 当前角速度的值,此值是一个代表当前角速度百分比的一个正整数 */
	quint8 m_bySpeed;		/*!< 当前速度的值,此值是一个代表当前底盘移动速度百分比的一个正整数 */
public:
	// TODO 控制RobotBase(底盘)前移的函数
	bool MoveOn();
	// TODO 控制RobotBase(底盘)后移的函数
	bool MoveBack();
	// TODO 控制RobotBase(底盘)左转的函数
	bool TurnLeft();
	// TODO 控制RobotBase(底盘)右转的函数
	bool TurnRight();
	// TODO 控制RoboBase(底盘)的移动速度
	bool ControlLineSpeed(quint8);
	// TODO 控制RoboBase(底盘)的转动速度
	bool ControlArcSpeed(quint8);
};
