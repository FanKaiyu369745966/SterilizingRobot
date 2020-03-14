#pragma once

#include <QLineEdit>
#include <QKeyEvent>
//#include "ui_KeyEdit.h"

class KeyEdit : public QLineEdit
{
	Q_OBJECT

public:
	KeyEdit(QWidget* parent = Q_NULLPTR);
	~KeyEdit();

private:
	//Ui::KeyEdit ui;
private:
	int m_key;
private:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

public:
	static QString KeyToString(Qt::Key key);
	static Qt::Key StringToKey(QString str);
	Qt::Key GetKey() const { return (Qt::Key)m_key; }
	void SetKey(Qt::Key key);
};
