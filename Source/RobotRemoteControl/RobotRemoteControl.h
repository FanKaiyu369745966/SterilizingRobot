#pragma once

#include <QtWidgets/QMainWindow>
#include <QTabWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QtGamepad>
#include <QMap>
#include <QThread>
#include <QDebug>
//#include "ui_RobotRemoteControl.h"

class RobotRemoteControl : public QMainWindow
{
	Q_OBJECT

public:
	RobotRemoteControl(QWidget* parent = Q_NULLPTR);

private:
	//Ui::RobotRemoteControlClass ui;
private:
	QTabWidget* m_tab;	/*!< 分页控件 */
public:
	enum CtrlKeys
	{
		MoveOn,			/*!< 前进按键 */
		MoveBack,		/*!< 后退按键 */
		TurnLeft,		/*!< 左转按键 */
		TurnRight,		/*!< 右转按键 */
		LSpeedUp,		/*!< 线速度加速按键 */
		LSpeedDown,		/*!< 线速度减速按键 */
		ASpeedUp,		/*!< 角速度加速按键 */
		ASpeedDown,		/*!< 角速度减速按键 */
		LightSwitch,	/*!< 辅助灯开关 */
		SpraySwitch,	/*!< 喷雾开关 */
		LookUp,			/*!< 摄像头抬起按键 */
		LookDown,		/*!< 摄像头低下按键 */
		LookLeft,		/*!< 摄像头左转按键 */
		LookRight,		/*!< 摄像头右转按键 */
	};
private:
	QMap< Qt::Key, CtrlKeys> m_mapCtrlKeys;	/*!< 键盘控制按键表 */
private:
	QTcpSocket* m_socket;
private:
	void InitKeyboard();
	void Initialize();

private:
	void Save();
	void Load();
private:
	/*!
	 * @brief 窗口关闭事件
	 * @arg QCloseEvent *
	 * @return void
	 * @since 2020/3/10 FanKaiyu
	 * 当窗口关闭前触发的函数
	 */
	void closeEvent(QCloseEvent* event);
private slots:
	/*!
	 * @brief 移除页签
	 * @arg int
	 * @return void
	 * @since 2020/3/10 FanKaiyu
	 * 当页签关闭前触发此函数
	 */
	void RemoveSubTab(int index);
};
