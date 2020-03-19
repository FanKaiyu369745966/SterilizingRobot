#pragma once

#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCloseEvent>
#include <QDir>
#include <QFile>
//#include "ui_RobotService.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QMessageBox>
#include <QCheckBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "RobotClient.h"

class RobotService : public QMainWindow
{
	Q_OBJECT

public:
	RobotService(QWidget* parent = Q_NULLPTR);

private:
	//Ui::RobotServiceClass ui;
private:
	QTcpServer* m_server;
	QSqlDatabase m_db;
	QMap<QString, RobotClient*>m_mapUuids;
	bool m_bClose;
private:
	//QComboBox* m_combSource;
	QLineEdit* m_leditHost;
	QLineEdit* m_leditUser;
	QLineEdit* m_leditPwd;
	QPushButton* m_pbutLink;

	QLineEdit* m_leidtAddr;
	QPushButton* m_pbutListen;

	QStandardItemModel* m_modelClnt;
private:
	void Initialize();
	void InitDatabase();

private:
	void Load();
	void Save();
	void AddNewClient(QString addr);
	void UpdateClient(QString addr, QString uuid);
	void UpdateClient(QString addr, QStringList takeList);
	void DeleteClient(QString addr);
	void DeleteSubscriber(QString addr, QStringList takeList);

private:
	void closeEvent(QCloseEvent* event);

private slots:
	void PressedLinkButton();
	void OnClickShowPasswordButton(bool checked);
	void PressedListenButton();
	void NewConnection();
	void AcceptError(QAbstractSocket::SocketError);
	void Record(QString user, QString uuid, QString addr, QString type, QString text);
	void RecognitionClient(QString uuid);
	void Disconnected();
	void Subscribe(RobotUuidArray&);
	void Unsubscribe(RobotUuidArray&);
};
