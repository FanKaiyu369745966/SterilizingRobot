#include "RobotRemoteControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RobotRemoteControl w;
	w.show();
	return a.exec();
}
