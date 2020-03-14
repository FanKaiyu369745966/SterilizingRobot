#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QtMath>
//#include "ui_ControlBoxWidget.h"

enum CtrlKeys;

class ControlBoxWidget : public QWidget
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

	bool m_bConnected;
private:
	void Initialize();
private:
	void Draw(QPainter&);
	void DrawAxisLeft(QPainter&, QRect);
	void DrawAxisRight(QPainter&, QRect);
	void DrawAxis(QPainter&, QRect, double, double, bool, QString);
	void DrawCross(QPainter&, QRect);
	void DrawCrossKey(QPainter&, QRect, bool);
	void DrawButtonXYAB(QPainter&, QRect);
	void DrawButton(QPainter&, QRect, bool, QString);
	void DrawButtonLR(QPainter&, QRect, bool, double, QString, QString);
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
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
public:
	double axisLeftX() const { return m_axisLeftX; }
	double axisLeftY() const { return m_axisLeftY; }
	double axisRightX() const { return m_axisRightX; }
	double axisRightY() const { return m_axisRightY; }
	bool buttonA() const { return m_buttonA; }
	bool buttonB() const { return m_buttonB; }
	bool buttonCenter() const { return m_buttonCenter; }
	bool buttonDown() const { return m_buttonDown; }
	bool buttonGuide() const { return m_buttonGuide; }
	bool buttonL1() const { return m_buttonL1; }
	double buttonL2() const { return m_buttonL2; }
	bool buttonL3() const { return m_buttonL3; }
	bool buttonLeft() const { return m_buttonLeft; }
	bool buttonR1() const { return m_buttonR1; }
	double buttonR2() const { return m_buttonR2; }
	bool buttonR3() const { return m_buttonR3; }
	bool buttonRight() const { return m_buttonRight; }
	bool buttonSelect() const { return m_buttonSelect; }
	bool buttonStart() const { return m_buttonStart; }
	bool buttonUp() const { return m_buttonUp; }
	bool buttonX() const { return m_buttonX; }
	bool buttonY() const { return m_buttonY; }
public slots:
	void axisLeftXChanged(double value);
	void axisLeftYChanged(double value);
	void axisRightXChanged(double value);
	void axisRightYChanged(double value);
	void buttonAChanged(bool value);
	void buttonBChanged(bool value);
	void buttonCenterChanged(bool value);
	void buttonDownChanged(bool value);
	void buttonGuideChanged(bool value);
	void buttonL1Changed(bool value);
	void buttonL2Changed(double value);
	void buttonL3Changed(bool value);
	void buttonLeftChanged(bool value);
	void buttonR1Changed(bool value);
	void buttonR2Changed(double value);
	void buttonR3Changed(bool value);
	void buttonRightChanged(bool value);
	void buttonSelectChanged(bool value);
	void buttonStartChanged(bool value);
	void buttonUpChanged(bool value);
	void buttonXChanged(bool value);
	void buttonYChanged(bool value);
	void connectedChanged(bool value);
	//void deviceIdChanged(int value);
	//void nameChanged(QString value);
};
