#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include "SLAMMapWidget.h"
#include "ControlBoxWidget.h"
//#include "ImageWidge.h"
//#include "ui_RobotClientWidget.h"

class RobotClientWidget : public QWidget
{
	Q_OBJECT

public:
	RobotClientWidget(QString uuid, QWidget* parent = Q_NULLPTR);
	~RobotClientWidget();

private:
	//Ui::RobotClientWidget ui;
public:
	SLAMMapWidget* m_wSlam;
	ControlBoxWidget* m_wCtrlbox;
	//ImageWidge* m_wImage;
private:
	QLineEdit* m_leditUuid;
	QLineEdit* m_leditStatus;
	QLineEdit* m_leditBattery;
	QLineEdit* m_leditResidual;
	QLineEdit* m_leditSpray;
	QLineEdit* m_leditSpeed;
	QLineEdit* m_leditLSpeed;
	QLineEdit* m_leditASpeed;
	QLineEdit* m_leditPosX;
	QLineEdit* m_leditPosY;
private:
	int m_nLSpeed;
	int m_nASpeed;
	bool m_bSpray;
private:
	void Initialize();
public:
	void Update(bool connected);
	void Update(int battery, int residual, bool spray, int speed, int lspeed, int aspeed, int x, int y);
	int	LineSpeed() const { return m_nLSpeed; }
	int	ArcSpeed() const { return m_nASpeed; }
	bool SparySwitch() const { return m_bSpray; }
	bool IsConnected() const;
};
