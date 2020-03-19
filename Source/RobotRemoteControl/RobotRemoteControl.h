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
#include <QMessageBox>
#include <QTcpSocket>
#include <QtGamepad>
#include <QUuid>
#include <QMap>
#include <QDebug>
#include <QGamepad>
#include <QGamepadManager>
#include <thread>
#include <QMutex>
#include <QHostaddress> 
#include <chrono>
#include <QScrollArea>
#include "KeyboardSettingsWidget.h"
#include "RobotClientWidget.h"
//#include "ui_RobotRemoteControl.h"

class RobotRemoteControl : public QMainWindow
{
	Q_OBJECT

public:
	RobotRemoteControl(QWidget* parent = Q_NULLPTR);
	~RobotRemoteControl();

private:
	//Ui::RobotRemoteControlClass ui;
private:
	QTabWidget* m_tab;						/*!< 分页控件 */
	KeyboardSettingsWidget* m_wCtrlPage;	/*!< 按键设置控件 */
	QStandardItemModel* m_model;
	QTableView* m_table;
	QLineEdit* m_leditUuid;
	QLineEdit* m_leditAddr;
	QPushButton* m_pbutConnect;
	QLabel* m_labDetail;
	QMap<QString, RobotClientWidget*> m_mapRobotWidgets;
private:
	CtrlKeyboard m_mapCtrlKeys;				/*!< 键盘控制按键表 */
private:
	QTcpSocket* m_socket;
	QGamepad* m_gamepad;
	std::thread* m_thread;
	bool m_bClose;
	QMutex m_mutex;
	QString m_strUuid;
	bool m_bConnected;
	QString	m_robotUuid;
	CtrlKeys m_mov;
	CtrlKeys m_eyes;
	QByteArray m_buf;
private:
	void InitKeyboard();
	void Initialize();
private:
	void Save();
	void Load();
	void Thread();
	bool AddRobot(QString uuid);
	void DeleteRobot(QString uuid);
	QString CreatePackage(QString to, QJsonObject cmd);
	QString CreatePackage(QString to, QJsonArray cmd);
	QString CreatePackage(QString to, QJsonObject cmd, QJsonObject result);
	QString CreatePackage(QString to, QJsonArray cmd, QJsonObject result);
	QString CreatePackage(QString to, QJsonArray cmd, QJsonArray result);
	static QString GetDate();
	void UpdateRobot(QString uuid, bool connected);
	void UpdateRobot(QString uuid, int battery, int residual, bool spray, int obs, int speed, int lspeed, int aspeed, int x, int y);
	void UpdateRobot(QString uuid, QByteArray img);
private:
	/*!
	 * @brief 窗口关闭事件
	 * @arg QCloseEvent *
	 * @return void
	 * @since 2020/3/10 FanKaiyu
	 * 当窗口关闭前触发的函数
	 */
	void closeEvent(QCloseEvent* event);

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

signals:
	void Send(QString);

private slots:
	/*!
	 * @brief 移除页签
	 * @arg int
	 * @return void
	 * @since 2020/3/10 FanKaiyu
	 * 当页签关闭前触发此函数
	 */
	void RemoveSubTab(int index);

	void SetCtrlKeyboard(CtrlKeyboard keys);

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
	//void connectedChanged(bool value);
	//void deviceIdChanged(int value);
	//void nameChanged(QString value);

	void doubleClickTable(const QModelIndex& index);
	void clickTable(const QModelIndex& index);

	void PressedAddRobotButton();
	void PressedDeleteRobotButton();
	void PressedConnectButton();

	void ServerError(QAbstractSocket::SocketError error);
	void ServerConnected();
	void ServerDisconnected();
	void ReadData();

	void tabCurrentChanged(int index);

	void SendPackage(QString);
};
