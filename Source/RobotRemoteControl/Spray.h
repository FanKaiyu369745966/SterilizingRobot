#pragma once

#include <QObject>

class Spray : public QObject
{
	Q_OBJECT

public:
	Spray(QObject* parent);
	~Spray();
public:
	quint8 m_byStatus;	/*!< 喷雾器的当前状态 */
	float m_fResiduals;	/*!< 消毒液的剩余容量，应当是保留了小数点后1位的百分比数值。eg：99.1。 %*/
	// TODO 应通过多次在同一区域内喷洒，统计出最大的消毒液消耗量，从而确保剩余的消毒液体足够完成巡逻计划。
public:
	// TODO 控制Spray(喷雾器)的开关
	bool Switch(bool);
	// TODO 控制Spray(喷雾器)定时喷雾
	bool Timing(quint32);
};
