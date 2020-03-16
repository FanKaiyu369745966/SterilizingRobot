#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "KeyEdit.h"
//#include "ui_KeyboardSettingsWidget.h"

enum CtrlKeys
{
	Unknow,			/*!< 未知按键 */
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
	ResetView,		/*!< 重置视图方向 */
};

typedef	QMap< Qt::Key, CtrlKeys> CtrlKeyboard;
typedef QSet<CtrlKeys> CtrlKeyArray;

Q_DECLARE_METATYPE(CtrlKeys)
Q_DECLARE_METATYPE(CtrlKeyArray)
Q_DECLARE_METATYPE(CtrlKeyboard)

class KeyboardSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	KeyboardSettingsWidget(QWidget* parent = Q_NULLPTR);
	~KeyboardSettingsWidget();

private:
	//Ui::KeyboardSettingsWidget ui;
private:
	KeyEdit* m_leditMo;
	KeyEdit* m_leditMb;
	KeyEdit* m_leditTl;
	KeyEdit* m_leditTr;

	KeyEdit* m_leditLu;
	KeyEdit* m_leditLd;
	KeyEdit* m_leditLl;
	KeyEdit* m_leditLr;

	KeyEdit* m_leditSs;
	KeyEdit* m_leditLs;
	KeyEdit* m_leditRv;

	KeyEdit* m_leditLsu;
	KeyEdit* m_leditLsd;

	KeyEdit* m_leditAsu;
	KeyEdit* m_leditAsd;
private:
	void Initialize();
signals:
	void KeyChanged(CtrlKeyboard keys);
private slots:
	void PressedSetButton();
	void PressedResetButton();
public:
	void SetKeyboard(CtrlKeyboard keys);
};
