#include "RobotClientWidget.h"

RobotClientWidget::RobotClientWidget(QString uuid, QWidget* parent)
	: QWidget(parent)
	, m_wSlam(nullptr)
	, m_wCtrlbox(nullptr)
	//, m_wImage(nullptr)
	, m_leditUuid(nullptr)
	, m_leditStatus(nullptr)
	, m_leditBattery(nullptr)
	, m_leditResidual(nullptr)
	, m_leditSpray(nullptr)
	, m_leditSpeed(nullptr)
	, m_leditLSpeed(nullptr)
	, m_leditASpeed(nullptr)
	, m_leditPosX(nullptr)
	, m_leditPosY(nullptr)
	, m_nLSpeed(0)
	, m_nASpeed(0)
	, m_bSpray(false)
{
	//ui.setupUi(this);
	Initialize();

	m_leditUuid->setText(uuid);
	m_leditStatus->setText(QString::fromLocal8Bit("未连接"));
	m_leditBattery->setText(QString::fromLocal8Bit("0%"));
	m_leditResidual->setText(QString::fromLocal8Bit("0%"));
	m_leditSpray->setText(QString::fromLocal8Bit("关"));
	m_leditSpeed->setText(QString::fromLocal8Bit("0%"));
	m_leditLSpeed->setText(QString::fromLocal8Bit("%1%").arg(m_nLSpeed));
	m_leditASpeed->setText(QString::fromLocal8Bit("%1%").arg(m_nASpeed));
	m_leditPosX->setText(QString::fromLocal8Bit("0"));
	m_leditPosY->setText(QString::fromLocal8Bit("0"));
}

RobotClientWidget::~RobotClientWidget()
{
}

void RobotClientWidget::Initialize()
{
	m_wSlam = new SLAMMapWidget(this);
	m_wCtrlbox = new ControlBoxWidget(this);
	//m_wImage = new ImageWidge(this);

	QLabel* _labUuid = new QLabel(QString::fromLocal8Bit("Uuid："), this);
	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("状态："), this);
	QLabel* _labBattery = new QLabel(QString::fromLocal8Bit("电量："), this);
	QLabel* _labResidual = new QLabel(QString::fromLocal8Bit("容量："), this);
	QLabel* _labSpray = new QLabel(QString::fromLocal8Bit("喷雾开关："), this);
	QLabel* _labSpeed = new QLabel(QString::fromLocal8Bit("速度："), this);
	QLabel* _labLSpeed = new QLabel(QString::fromLocal8Bit("线速度(设定值)："), this);
	QLabel* _labASpeed = new QLabel(QString::fromLocal8Bit("角速度(设定值)："), this);
	QLabel* _labPosX = new QLabel(QString::fromLocal8Bit("X坐标："), this);
	QLabel* _labPosY = new QLabel(QString::fromLocal8Bit("Y坐标："), this);

	m_leditUuid = new QLineEdit(this);
	m_leditStatus = new QLineEdit(this);
	m_leditBattery = new QLineEdit(this);
	m_leditResidual = new QLineEdit(this);
	m_leditSpray = new QLineEdit(this);
	m_leditSpeed = new QLineEdit(this);
	m_leditLSpeed = new QLineEdit(this);
	m_leditASpeed = new QLineEdit(this);
	m_leditPosX = new QLineEdit(this);
	m_leditPosY = new QLineEdit(this);

	QGridLayout* _layAttr = new QGridLayout();

	int nIndex = 0;

	_layAttr->addWidget(_labUuid, nIndex, 0);
	_layAttr->addWidget(m_leditUuid, nIndex++, 1);
	_layAttr->addWidget(_labAddr, nIndex, 0);
	_layAttr->addWidget(m_leditStatus, nIndex++, 1);
	_layAttr->addWidget(_labBattery, nIndex, 0);
	_layAttr->addWidget(m_leditBattery, nIndex++, 1);
	_layAttr->addWidget(_labResidual, nIndex, 0);
	_layAttr->addWidget(m_leditResidual, nIndex++, 1);
	_layAttr->addWidget(_labSpray, nIndex, 0);
	_layAttr->addWidget(m_leditSpray, nIndex++, 1);
	_layAttr->addWidget(_labSpeed, nIndex, 0);
	_layAttr->addWidget(m_leditSpeed, nIndex++, 1);
	_layAttr->addWidget(_labLSpeed, nIndex, 0);
	_layAttr->addWidget(m_leditLSpeed, nIndex++, 1);
	_layAttr->addWidget(_labASpeed, nIndex, 0);
	_layAttr->addWidget(m_leditASpeed, nIndex++, 1);
	_layAttr->addWidget(_labPosX, nIndex, 0);
	_layAttr->addWidget(m_leditPosX, nIndex++, 1);
	_layAttr->addWidget(_labPosY, nIndex, 0);
	_layAttr->addWidget(m_leditPosY, nIndex++, 1);

	QGroupBox* _groupAttr = new QGroupBox(QString::fromLocal8Bit("状态"), this);
	QGroupBox* _groupImge = new QGroupBox(QString::fromLocal8Bit("图像"), this);
	QGroupBox* _groupSlam = new QGroupBox(QString::fromLocal8Bit("扫描图"), this);
	//QGroupBox* _groupCtrlbox = new QGroupBox(QString::fromLocal8Bit("控制器"), this);
	QGroupBox* _groupPath = new QGroupBox(QString::fromLocal8Bit("路线以及工作计划"), this);

	QHBoxLayout* _layImage = new QHBoxLayout();
	_layImage->addWidget(m_wCtrlbox);

	QHBoxLayout* _laySlam = new QHBoxLayout();
	_laySlam->addWidget(m_wSlam);

	//QHBoxLayout* _layCtrlbox = new QHBoxLayout();
	//_layCtrlbox->addWidget(m_wCtrlbox);

	_groupImge->setLayout(_layImage);
	_groupSlam->setLayout(_laySlam);
	//_groupCtrlbox->setLayout(_layCtrlbox);
	_groupAttr->setLayout(_layAttr);

	QGridLayout* _layMain = new QGridLayout();

	_layMain->addWidget(_groupAttr, 0, 0, 2, 1);
	_layMain->addWidget(_groupImge, 0, 1, 2, 1);
	_layMain->addWidget(_groupSlam, 0, 2);
	//_layMain->addWidget(_groupCtrlbox, 1, 1);
	_layMain->addWidget(_groupPath, 1, 2);

	//_layMain->setColumnStretch(1, 2);

	setLayout(_layMain);

	_labUuid->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labAddr->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labBattery->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labResidual->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labSpray->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labLSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labASpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labPosX->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labPosY->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	m_leditUuid->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditStatus->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditBattery->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditResidual->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	m_leditSpray->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditLSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditASpeed->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	m_leditPosX->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	m_leditPosY->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	m_leditUuid->setReadOnly(true);
	m_leditStatus->setReadOnly(true);
	m_leditBattery->setReadOnly(true);
	m_leditResidual->setReadOnly(true);

	m_leditSpray->setReadOnly(true);
	m_leditSpeed->setReadOnly(true);
	m_leditLSpeed->setReadOnly(true);
	m_leditASpeed->setReadOnly(true);

	m_leditPosX->setReadOnly(true);
	m_leditPosY->setReadOnly(true);

	return;
}

void RobotClientWidget::Update(bool connected)
{
	if (connected)
	{
		m_leditStatus->setText(QString::fromLocal8Bit("已连接"));
	}
	else
	{
		m_leditStatus->setText(QString::fromLocal8Bit("未连接"));
	}

	return;
}

void RobotClientWidget::Update(int battery, int residual, bool spray, int speed, int lspeed, int aspeed, int x, int y)
{
	m_leditBattery->setText(QString::fromLocal8Bit("%1%").arg(battery));
	m_leditResidual->setText(QString::fromLocal8Bit("%1%").arg(residual));

	m_bSpray = spray;
	if (m_bSpray)
	{
		m_leditSpray->setText(QString::fromLocal8Bit("开"));
	}
	else
	{
		m_leditSpray->setText(QString::fromLocal8Bit("关"));
	}

	m_leditSpeed->setText(QString::fromLocal8Bit("%1%").arg(speed));

	m_nLSpeed = lspeed;
	m_nASpeed = aspeed;

	m_leditLSpeed->setText(QString::fromLocal8Bit("%1%").arg(m_nLSpeed));
	m_leditASpeed->setText(QString::fromLocal8Bit("%1%").arg(m_nASpeed));

	m_leditPosX->setText(QString::fromLocal8Bit("%1").arg(x));
	m_leditPosY->setText(QString::fromLocal8Bit("%1").arg(y));

	return;
}

bool RobotClientWidget::IsConnected() const
{
	if (m_leditStatus->text() == QString::fromLocal8Bit("未连接"))
	{
		return false;
	}
	return true;
}
