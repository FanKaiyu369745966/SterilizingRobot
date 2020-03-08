#include "RobotBase.h"

RobotBase::RobotBase(QObject* parent)
	: QObject(parent)
	, m_byBattery(0)
	, m_byLineSpeed(0)
	, m_byArcSpeed(0)
	, m_bySpeed(0)
{
}

RobotBase::~RobotBase()
{
}
