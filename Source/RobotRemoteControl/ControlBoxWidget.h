#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QtMath>
#include "ImageWidge.h"
//#include "ui_ControlBoxWidget.h"

enum CtrlKeys;

class ControlBoxWidget : public ImageWidge
{
	Q_OBJECT

public:
	ControlBoxWidget(QWidget* parent = Q_NULLPTR);
	~ControlBoxWidget();

private:
	//Ui::ControlBoxWidget ui;
private:
	double m_axisLeftX;		/*!< 左摇杆X坐标 -1.0 to 1.0 */
	double m_axisLeftY;		/*!< 左摇杆Y左边 -1.0 to 1.0 */
	double m_axisRightX;	/*!< 右摇杆X坐标 -1.0 to 1.0 */
	double m_axisRightY;	/*!< 右摇杆Y坐标 -1.0 to 1.0 */
	bool m_buttonL1;		/*!< L1/LB 按键状态 */
	double m_buttonL2;		/*!< L2/LT 按键状态 0.0 to 1.0 */
	bool m_buttonL3;		/*!< L3 按键状态 */
	bool m_buttonR1;		/*!< R1/RB 按键状态 */
	double m_buttonR2;		/*!< R2/RT 按键状态 0.0 to 1.0 */
	bool m_buttonR3;		/*!< R3 按键状态 */
	bool m_buttonA;			/*!< A 按键状态 */
	bool m_buttonB;			/*!< B 按键状态 */
	bool m_buttonX;			/*!< X 按键状态 */
	bool m_buttonY;			/*!< Y 按键状态 */
	bool m_buttonUp;		/*!< 上键 按键状态 */
	bool m_buttonDown;		/*!< 下键 按键状态 */
	bool m_buttonLeft;		/*!< 左键 按键状态 */
	bool m_buttonRight;		/*!< 右键 按键状态 */

	bool m_buttonCenter;
	bool m_buttonGuide;
	bool m_buttonStart;
	bool m_buttonSelect;

	bool m_bConnected;		/*!< 游戏板的连接状态 */
private:
	/*!
	 * @brief 初始化控件
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 创建子控件，并为子空间布局
	 */
	void Initialize();
private:
	/*!
	 * @brief 绘制控制器图形
	 * @arg QPainter
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制控制器按键图形，以及分布布局
	 */
	void Draw(QPainter&);
	/*!
	 * @brief 绘制左摇杆
	 * @arg QPainter
	 * @arg QRect
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制左摇杆的图形
	 */
	void DrawAxisLeft(QPainter&, QRect);
	/*!
	 * @brief 绘制右摇杆
	 * @arg QPainter
	 * @arg QRect
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制右摇杆的图形
	 */
	void DrawAxisRight(QPainter&, QRect);
	/*!
	 * @brief 绘制摇杆
	 * @arg QPainter
	 * @arg QRect
	 * @arg double
	 * @arg double
	 * @arg bool
	 * @arg QString
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制左右摇杆的图形
	 */
	void DrawAxis(QPainter&, QRect, double, double, bool, QString);
	/*!
	 * @brief 绘制十字方向键
	 * @arg QPainter
	 * @arg QRect
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制十字方向键以及键外的圆圈
	 */
	void DrawCross(QPainter&, QRect);
	/*!
	 * @brief 绘制十字方向键中的单个按键
	 * @arg QPainter
	 * @arg QRect
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制十字方向键单一方向的图形
	 */
	void DrawCrossKey(QPainter&, QRect, bool);
	/*!
	 * @brief 绘制X\Y\A\B功能键
	 * @arg QPainter
	 * @arg QRect
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制X、Y、A、B按键
	 */
	void DrawButtonXYAB(QPainter&, QRect);
	/*!
	 * @brief 绘制单个的功能按键
	 * @arg QPainter
	 * @arg QRect
	 * @arg bool
	 * @arg QString
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制单个的功能按键
	 */
	void DrawButton(QPainter&, QRect, bool, QString);
	/*!
	 * @brief 绘制LR左肩键以及右肩键
	 * @arg QPainter
	 * @arg QRect
	 * @arg bool
	 * @arg double
	 * @arg QString
	 * @arg QString
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制左右肩键
	 */
	void DrawButtonLR(QPainter&, QRect, bool, double, QString, QString);
	/*!
	 * @brief 绘制控制器的状态信息
	 * @arg QPainter
	 * @arg QRect
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 绘制控制器的状态信息
	 */
	void DrawCtrlerStatus(QPainter&, QRect);
	/*!
	 * @brief 获取小圆的中心坐标
	 * @arg QPoint 大圆的中心坐标
	 * @arg QPoint 小圆的中心坐标
	 * @arg double 大圆的半径
	 * @return QPoint 矫正后的小圆中心坐标
	 * @since 2020/3/12 FanKaiyu
	 * 当小圆的中心坐标超出大圆时，对小圆的中心坐标进行矫正，使得小圆的圆心在大圆的边缘上
	 */
	QPoint GetEllipse(QPoint out, QPoint in, double R);
private:
	/*!
	 * @brief 绘图事件
	 * @arg QPaintEvent *
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 当控件界面发生改变时触发的事件
	 */
	void paintEvent(QPaintEvent* event);
	/*!
	 * @brief 尺寸变更事件
	 * @arg QResizeEvent *
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 当控件尺寸发生改变时触发的函数
	 */
	void resizeEvent(QResizeEvent* event);
public:
	/*!
	 * @brief 获取左摇杆X坐标
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回左摇杆X坐标的值
	 */
	double axisLeftX() const { return m_axisLeftX; }
	/*!
	 * @brief 获取左摇杆Y坐标
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回左摇杆Y坐标的值
	 */
	double axisLeftY() const { return m_axisLeftY; }
	/*!
	 * @brief 获取右摇杆X坐标
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回右摇杆X坐标的值
	 */
	double axisRightX() const { return m_axisRightX; }
	/*!
	 * @brief 获取右摇杆Y坐标
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回右摇杆Y坐标的值
	 */
	double axisRightY() const { return m_axisRightY; }
	/*!
	 * @brief 获取A键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回A键的值
	 */
	bool buttonA() const { return m_buttonA; }
	/*!
	 * @brief 获取B键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回B键的值
	 */
	bool buttonB() const { return m_buttonB; }
	bool buttonCenter() const { return m_buttonCenter; }
	/*!
	 * @brief 获取下方向键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回下方向键的值
	 */
	bool buttonDown() const { return m_buttonDown; }
	bool buttonGuide() const { return m_buttonGuide; }
	/*!
	 * @brief 获取L1/LB键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回L1键的状态
	 */
	bool buttonL1() const { return m_buttonL1; }
	/*!
	 * @brief 获取L2/LT键的状态
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回L2键的值
	 */
	double buttonL2() const { return m_buttonL2; }
	/*!
	 * @brief 获取L3键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回L3键的值
	 */
	bool buttonL3() const { return m_buttonL3; }
	/*!
	 * @brief 获取左方向键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回左方向键的值
	 */
	bool buttonLeft() const { return m_buttonLeft; }
	/*!
	 * @brief 获取R1/RB键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回R1键的值
	 */
	bool buttonR1() const { return m_buttonR1; }
	/*!
	 * @brief 获取R2/RT键的状态
	 * @return double
	 * @since 2020/3/19 FanKaiyu
	 * 返回R2键的值
	 */
	double buttonR2() const { return m_buttonR2; }
	/*!
	 * @brief 获取R3键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回R3键的值
	 */
	bool buttonR3() const { return m_buttonR3; }
	/*!
	 * @brief 获取右方向键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回右方向键的值
	 */
	bool buttonRight() const { return m_buttonRight; }
	bool buttonSelect() const { return m_buttonSelect; }
	bool buttonStart() const { return m_buttonStart; }
	/*!
	 * @brief 获取上方向键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回上方向键的值
	 */
	bool buttonUp() const { return m_buttonUp; }
	/*!
	 * @brief 获取X键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回X键的值
	 */
	bool buttonX() const { return m_buttonX; }
	/*!
	 * @brief 获取Y键的状态
	 * @return bool
	 * @since 2020/3/19 FanKaiyu
	 * 返回Y键的值
	 */
	bool buttonY() const { return m_buttonY; }
public slots:
	/*!
	 * @brief 左摇杆X坐标发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 左摇杆X坐标发生改变时触发的函数
	 */
	void axisLeftXChanged(double value);
	/*!
	 * @brief 左摇杆Y坐标发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 左摇杆Y坐标发生改变时触发的函数
	 */
	void axisLeftYChanged(double value);
	/*!
	 * @brief 右摇杆X坐标发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 右摇杆X坐标发生改变时触发的函数
	 */
	void axisRightXChanged(double value);
	/*!
	 * @brief 右摇杆Y坐标发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 右摇杆Y坐标发生改变时触发的函数
	 */
	void axisRightYChanged(double value);
	/*!
	 * @brief A键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * A键状态发生改变时触发的函数
	 */
	void buttonAChanged(bool value);

	/*!
	 * @brief B键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * B键状态发生改变时触发的函数
	 */
	void buttonBChanged(bool value);
	void buttonCenterChanged(bool value);
	/*!
	 * @brief 下方向键发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 下方向键发生改变时触发的函数
	 */
	void buttonDownChanged(bool value);
	void buttonGuideChanged(bool value);
	/*!
	 * @brief L1/LB键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * L1/LB键发生改变时触发的函数
	 */
	void buttonL1Changed(bool value);
	/*!
	 * @brief L2/LT键状态发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * L2/LT键状态发生改变时触发的函数
	 */
	void buttonL2Changed(double value);
	/*!
	 * @brief L3键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * L3键状态发生改变时触发的函数
	 */
	void buttonL3Changed(bool value);
	/*!
	 * @brief 左方向键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 左方向键状态发生改变时触发的函数
	 */
	void buttonLeftChanged(bool value);
	/*!
	 * @brief R1/RB键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * R1/RB键状态发生改变时触发的函数
	 */
	void buttonR1Changed(bool value);
	/*!
	 * @brief R2/RT键状态发生改变
	 * @arg double
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * R2/RT键状态发生改变时触发的函数
	 */
	void buttonR2Changed(double value);
	/*!
	 * @brief R3键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * R3键状态发生改变时触发的函数
	 */
	void buttonR3Changed(bool value);
	/*!
	 * @brief 右方向键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 右方向键状态发生改变时触发的函数
	 */
	void buttonRightChanged(bool value);
	void buttonSelectChanged(bool value);
	void buttonStartChanged(bool value);
	/*!
	 * @brief 上方向键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * 上方向键状态发生改变时触发的函数
	 */
	void buttonUpChanged(bool value);
	/*!
	 * @brief X键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * X键状态发生改变时触发的函数
	 */
	void buttonXChanged(bool value);
	/*!
	 * @brief Y键状态发生改变
	 * @arg bool
	 * @return void
	 * @since 2020/3/19 FanKaiyu
	 * Y键状态发生改变时触发的函数
	 */
	void buttonYChanged(bool value);
	void connectedChanged(bool value);
	//void deviceIdChanged(int value);
	//void nameChanged(QString value);
};
