#include "KeyboardSettingsWidget.h"
#include <QDebug>

KeyboardSettingsWidget::KeyboardSettingsWidget(QWidget* parent)
	: QWidget(parent)
	, m_leditMo(nullptr)
	, m_leditMb(nullptr)
	, m_leditTl(nullptr)
	, m_leditTr(nullptr)
	, m_leditLu(nullptr)
	, m_leditLd(nullptr)
	, m_leditLl(nullptr)
	, m_leditLr(nullptr)

	, m_leditSs(nullptr)
	, m_leditLs(nullptr)
	, m_leditRv(nullptr)

	, m_leditLsu(nullptr)
	, m_leditLsd(nullptr)

	, m_leditAsu(nullptr)
	, m_leditAsd(nullptr)
{
	//ui.setupUi(this);
	Initialize();
}

KeyboardSettingsWidget::~KeyboardSettingsWidget()
{
}

void KeyboardSettingsWidget::Initialize()
{
	QGroupBox* _box = new QGroupBox(QString::fromLocal8Bit("键盘"), this);

	QLabel* _labMo = new QLabel(QString::fromLocal8Bit("前进："), this);
	QLabel* _labMb = new QLabel(QString::fromLocal8Bit("后退："), this);
	QLabel* _labTl = new QLabel(QString::fromLocal8Bit("左转："), this);
	QLabel* _labTr = new QLabel(QString::fromLocal8Bit("右转："), this);

	QLabel* _labLu = new QLabel(QString::fromLocal8Bit("摄像头抬起："), this);
	QLabel* _labLd = new QLabel(QString::fromLocal8Bit("摄像头低下："), this);
	QLabel* _labLl = new QLabel(QString::fromLocal8Bit("摄像头左转："), this);
	QLabel* _labLr = new QLabel(QString::fromLocal8Bit("摄像头右转："), this);

	QLabel* _labLs = new QLabel(QString::fromLocal8Bit("灯开关："), this);
	QLabel* _labSs = new QLabel(QString::fromLocal8Bit("喷雾开关："), this);
	QLabel* _labRv = new QLabel(QString::fromLocal8Bit("重置视图："), this);

	QLabel* _labLsu = new QLabel(QString::fromLocal8Bit("移动加速："), this);
	QLabel* _labLsd = new QLabel(QString::fromLocal8Bit("移动减速："), this);

	QLabel* _labAsu = new QLabel(QString::fromLocal8Bit("转向加速："), this);
	QLabel* _labAsd = new QLabel(QString::fromLocal8Bit("转向减速："), this);

	m_leditMo = new KeyEdit(this);
	m_leditMb = new KeyEdit(this);
	m_leditTl = new KeyEdit(this);
	m_leditTr = new KeyEdit(this);

	m_leditLu = new KeyEdit(this);
	m_leditLd = new KeyEdit(this);
	m_leditLl = new KeyEdit(this);
	m_leditLr = new KeyEdit(this);

	m_leditLs = new KeyEdit(this);
	m_leditSs = new KeyEdit(this);
	m_leditRv = new KeyEdit(this);

	m_leditLsu = new KeyEdit(this);
	m_leditLsd = new KeyEdit(this);

	m_leditAsu = new KeyEdit(this);
	m_leditAsd = new KeyEdit(this);

	QGridLayout* _layBox = new QGridLayout();

	QPushButton* _pbutSet = new QPushButton(QString::fromLocal8Bit("设置"), this);
	QPushButton* _pbutReset = new QPushButton(QString::fromLocal8Bit("初始化"), this);

	int r = 0, c = 0;

	_layBox->addWidget(_labMo, r, c++);
	_layBox->addWidget(m_leditMo, r, c++);
	_layBox->addWidget(_labLs, r, c++);
	_layBox->addWidget(m_leditLs, r++, c++);

	c = 0;
	_layBox->addWidget(_labMb, r, c++);
	_layBox->addWidget(m_leditMb, r, c++);
	_layBox->addWidget(_labSs, r, c++);
	_layBox->addWidget(m_leditSs, r++, c++);
	c = 0;

	_layBox->addWidget(_labTl, r, c++);
	_layBox->addWidget(m_leditTl, r, c++);
	_layBox->addWidget(_labRv, r, c++);
	_layBox->addWidget(m_leditRv, r++, c++);
	c = 0;

	_layBox->addWidget(_labTr, r, c++);
	_layBox->addWidget(m_leditTr, r, c++);
	_layBox->addWidget(_labLsu, r, c++);
	_layBox->addWidget(m_leditLsu, r++, c++);
	c = 0;

	_layBox->addWidget(_labLu, r, c++);
	_layBox->addWidget(m_leditLu, r, c++);
	_layBox->addWidget(_labLsd, r, c++);
	_layBox->addWidget(m_leditLsd, r++, c++);
	c = 0;

	_layBox->addWidget(_labLd, r, c++);
	_layBox->addWidget(m_leditLd, r, c++);
	_layBox->addWidget(_labAsu, r, c++);
	_layBox->addWidget(m_leditAsu, r++, c++);
	c = 0;

	_layBox->addWidget(_labLl, r, c++);
	_layBox->addWidget(m_leditLl, r, c++);
	_layBox->addWidget(_labAsd, r, c++);
	_layBox->addWidget(m_leditAsd, r++, c++);
	c = 0;

	_layBox->addWidget(_labLr, r, c++);
	_layBox->addWidget(m_leditLr, r++, c++);


	_layBox->addWidget(_pbutSet, r, 0, 1, 2);
	_layBox->addWidget(_pbutReset, r, 2, 1, 2);

	_box->setLayout(_layBox);

	QHBoxLayout* _layMain = new QHBoxLayout();
	_layMain->addWidget(_box);

	setLayout(_layMain);

	m_leditMo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditMb->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditTl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditTr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_leditLu->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditLd->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditLl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditLr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_leditLs->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditSs->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditRv->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_leditLsu->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditLsd->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_leditAsu->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_leditAsd->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	_labMo->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labMb->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labTl->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labTr->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labLu->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labLd->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labLl->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labLr->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labLs->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labSs->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labRv->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labLsu->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labLsd->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	_labAsu->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	_labAsd->setAlignment(Qt::AlignHCenter | Qt::AlignRight);

	QObject::connect(_pbutSet, &QPushButton::pressed, this, &KeyboardSettingsWidget::PressedSetButton);
	QObject::connect(_pbutReset, &QPushButton::pressed, this, &KeyboardSettingsWidget::PressedResetButton);

	return;
}

void KeyboardSettingsWidget::PressedSetButton()
{
	CtrlKeyboard _keys;

	_keys[m_leditMo->GetKey()] = MoveOn;
	_keys[m_leditMb->GetKey()] = MoveBack;
	_keys[m_leditTl->GetKey()] = TurnLeft;
	_keys[m_leditTr->GetKey()] = TurnRight;

	_keys[m_leditLu->GetKey()] = LookUp;
	_keys[m_leditLd->GetKey()] = LookDown;
	_keys[m_leditLl->GetKey()] = LookLeft;
	_keys[m_leditLr->GetKey()] = LookRight;

	_keys[m_leditLs->GetKey()] = LightSwitch;
	_keys[m_leditSs->GetKey()] = SpraySwitch;
	_keys[m_leditRv->GetKey()] = ResetView;

	_keys[m_leditLsu->GetKey()] = LSpeedUp;
	_keys[m_leditLsd->GetKey()] = LSpeedDown;

	_keys[m_leditAsu->GetKey()] = ASpeedUp;
	_keys[m_leditAsd->GetKey()] = ASpeedDown;

	emit KeyChanged(_keys);
	return;
}

void KeyboardSettingsWidget::PressedResetButton()
{
	m_leditMo->SetKey(Qt::Key_W);
	m_leditMb->SetKey(Qt::Key_S);
	m_leditTl->SetKey(Qt::Key_A);
	m_leditTr->SetKey(Qt::Key_D);

	m_leditLu->SetKey(Qt::Key_I);
	m_leditLd->SetKey(Qt::Key_K);
	m_leditLl->SetKey(Qt::Key_J);
	m_leditLr->SetKey(Qt::Key_L);

	m_leditLs->SetKey(Qt::Key_1);
	m_leditSs->SetKey(Qt::Key_2);
	m_leditRv->SetKey(Qt::Key_3);

	m_leditLsu->SetKey(Qt::Key_Up);
	m_leditLsd->SetKey(Qt::Key_Down);

	m_leditAsu->SetKey(Qt::Key_Left);
	m_leditAsd->SetKey(Qt::Key_Right);

	PressedSetButton();
	return;
}

void KeyboardSettingsWidget::SetKeyboard(CtrlKeyboard keys)
{
	for (CtrlKeyboard::iterator it = keys.begin(); it != keys.end(); ++it)
	{
		Qt::Key key = it.key();

		switch (it.value())
		{
		case MoveOn:
			m_leditMo->SetKey(key);
			break;
		case MoveBack:
			m_leditMb->SetKey(key);
			break;
		case TurnLeft:
			m_leditTl->SetKey(key);
			break;
		case TurnRight:
			m_leditTr->SetKey(key);
			break;
		case LSpeedUp:
			m_leditLsu->SetKey(key);
			break;
		case LSpeedDown:
			m_leditLsd->SetKey(key);
			break;
		case ASpeedUp:
			m_leditAsu->SetKey(key);
			break;
		case ASpeedDown:
			m_leditAsd->SetKey(key);
			break;
		case LightSwitch:
			m_leditLs->SetKey(key);
			break;
		case SpraySwitch:
			m_leditSs->SetKey(key);
			break;
		case LookUp:
			m_leditLu->SetKey(key);
			break;
		case LookDown:
			m_leditLd->SetKey(key);
			break;
		case LookLeft:
			m_leditLl->SetKey(key);
			break;
		case LookRight:
			m_leditLr->SetKey(key);
			break;
		case ResetView:
			m_leditRv->SetKey(key);
			break;
		}
	}
	return;
}
