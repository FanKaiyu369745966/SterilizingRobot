#include "RobotRemoteControl.h"
#include <QApplication>

RobotRemoteControl::RobotRemoteControl(QWidget* parent)
	: QMainWindow(parent)
	, m_tab(nullptr)
	, m_wCtrlPage(nullptr)
	, m_gamepad(nullptr)
	, m_thread(nullptr)
	, m_bClose(nullptr)
	, m_table(nullptr)
	, m_leditUuid(nullptr)
	, m_leditAddr(nullptr)
	, m_pbutConnect(nullptr)
	, m_labDetail(nullptr)
	, m_bConnected(false)
	, m_robotUuid("")
	, m_mov(CtrlKeys::Unknow)
	, m_eyes(CtrlKeys::Unknow)
{
	qRegisterMetaType<CtrlKeys>();
	qRegisterMetaType<CtrlKeyArray>();
	qRegisterMetaType<CtrlKeyboard>();

	//ui.setupUi(this);
	Initialize();

	m_thread = new std::thread(&RobotRemoteControl::Thread, this);

	m_strUuid = QUuid::createUuid().toString();
	//qDebug() << m_strUuid;

	m_socket = new QTcpSocket(this);

	QObject::connect(m_socket, &QTcpSocket::connected, this, &RobotRemoteControl::ServerConnected);
	QObject::connect(m_socket, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &RobotRemoteControl::ServerError);
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &RobotRemoteControl::ReadData);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &RobotRemoteControl::ServerDisconnected);

	QObject::connect(this, &RobotRemoteControl::Send, this, &RobotRemoteControl::SendPackage);

	InitKeyboard();

	Load();
}

RobotRemoteControl::~RobotRemoteControl()
{
	if (m_thread->joinable())
	{
		m_bClose = true;

		m_thread->join();

		delete m_thread;
	}

	return;
}

void RobotRemoteControl::InitKeyboard()
{
	m_mapCtrlKeys[Qt::Key::Key_W] = MoveOn;
	m_mapCtrlKeys[Qt::Key::Key_S] = MoveBack;
	m_mapCtrlKeys[Qt::Key::Key_A] = TurnLeft;
	m_mapCtrlKeys[Qt::Key::Key_D] = TurnRight;

	m_mapCtrlKeys[Qt::Key::Key_Up] = LSpeedUp;
	m_mapCtrlKeys[Qt::Key::Key_Down] = LSpeedDown;
	m_mapCtrlKeys[Qt::Key::Key_Left] = ASpeedUp;
	m_mapCtrlKeys[Qt::Key::Key_Right] = ASpeedDown;

	m_mapCtrlKeys[Qt::Key::Key_1] = LightSwitch;
	m_mapCtrlKeys[Qt::Key::Key_2] = SpraySwitch;
	m_mapCtrlKeys[Qt::Key::Key_3] = ResetView;

	m_mapCtrlKeys[Qt::Key::Key_I] = LookUp;
	m_mapCtrlKeys[Qt::Key::Key_K] = LookDown;
	m_mapCtrlKeys[Qt::Key::Key_J] = LookLeft;
	m_mapCtrlKeys[Qt::Key::Key_L] = LookRight;

	return;
}

void RobotRemoteControl::Initialize()
{
	setMinimumHeight(480);				//设置绘图区域窗体的最小大小
	setMaximumHeight(720);				//设置绘图区域窗体的最小大小

	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("地址："), this);					/*!< 服务端地址标签 */
	m_leditAddr = new QLineEdit(this);														/*!< 服务端地址编辑框 */
	m_pbutConnect = new QPushButton(QString::fromLocal8Bit("连接"), this);		/*!< 服务端连接按钮 */
	QLabel* _labStatus = new QLabel(QString::fromLocal8Bit("状态："), this);				/*!< 服务端状态标签 */
	m_labDetail = new QLabel(QString::fromLocal8Bit("未连接"), this);					/*!< 服务端状态信息标签 */

	QGridLayout* _laySrvAddr = new QGridLayout();										/*!< 服务端配置布局 */

	// 添加控件
	_laySrvAddr->addWidget(_labAddr, 0, 0);
	_laySrvAddr->addWidget(m_leditAddr, 0, 1);
	_laySrvAddr->addWidget(m_pbutConnect, 0, 2);

	// 添加控件
	_laySrvAddr->addWidget(_labStatus, 1, 0);
	_laySrvAddr->addWidget(m_labDetail, 1, 1, 1, 2);

	QGroupBox* _groupSrv = new QGroupBox(QString::fromLocal8Bit("服务端"), this);			/*!< 服务端组合框 */

	// 设置布局
	_groupSrv->setLayout(_laySrvAddr);

	m_table = new QTableView(this);												/*!< 机器人表单 */

	QLabel* _labUuid = new QLabel(QString::fromLocal8Bit("Uuid："));
	m_leditUuid = new QLineEdit(this);
	QPushButton* _pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);
	QPushButton* _pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);

	QHBoxLayout* _layUuid = new QHBoxLayout();

	_layUuid->addWidget(_labUuid);
	_layUuid->addWidget(m_leditUuid);
	_layUuid->addWidget(_pbutAdd);
	_layUuid->addWidget(_pbutDel);

	QGroupBox* _groupRobot = new QGroupBox(QString::fromLocal8Bit("机器人"), this);			/*!< 机器人组合框 */

	QVBoxLayout* _layRobot = new QVBoxLayout();											/*!< 机器人布局 */

	// 添加控件
	_layRobot->addLayout(_layUuid);
	_layRobot->addWidget(m_table);

	// 设置布局
	_groupRobot->setLayout(_layRobot);

	QVBoxLayout* _layFPage = new QVBoxLayout();											/*!< 首页布局 */

	// 添加控件
	_layFPage->addWidget(_groupSrv);
	_layFPage->addWidget(_groupRobot);

	QWidget* _wFristPag = new QWidget(this);												/*!< 首页控件 */

	// 设置布局
	_wFristPag->setLayout(_layFPage);

	m_wCtrlPage = new KeyboardSettingsWidget(this);											/*!< 控制器控件 */

	m_tab = new QTabWidget(this);

	// 添加分页
	m_tab->addTab(_wFristPag, QString::fromLocal8Bit("首页"));
	m_tab->addTab(m_wCtrlPage, QString::fromLocal8Bit("设置"));
	//m_tab->addTab(new RobotClientWidget(this), QString::fromLocal8Bit("Robot:"));

	QWidget* _wCenter = new QWidget(this);													/*!< 中心控件 */

	QHBoxLayout* _layMain = new QHBoxLayout();											/*!< 中心布局 */

	// 添加控件
	_layMain->addWidget(m_tab);

	// 设置布局
	_wCenter->setLayout(_layMain);

	// 设置窗体样式
	this->setCentralWidget(_wCenter);

	this->setWindowTitle(QString::fromLocal8Bit("机器人远程控制系统"));

	this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	// 设置分页样式
	//m_tab->setTabPosition(QTabWidget::TabPosition::West);
	m_tab->setTabsClosable(true);

	m_model = new QStandardItemModel(this);							/*!< 机器人表单数据模型 */

	// 添加列头
	m_model->setColumnCount(6);

	int _index = 0;
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("UUID"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("电量"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("容量"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("喷雾开关"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("速度"));
	//m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("线速度(设定值)"));
	//m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("角速度(设定值)"));
	//m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("坐标"));

	m_table->setModel(m_model);
	m_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	m_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 设置编辑框样式
	m_leditAddr->setPlaceholderText(QString::fromLocal8Bit("IP:端口 例如：127.0.0.1:8080"));
	m_labDetail->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	// 添加信号和槽
	QObject::connect(m_tab, &QTabWidget::tabCloseRequested, this, &RobotRemoteControl::RemoveSubTab);
	QObject::connect(m_tab, &QTabWidget::currentChanged, this, &RobotRemoteControl::tabCurrentChanged);
	QObject::connect(m_wCtrlPage, &KeyboardSettingsWidget::KeyChanged, this, &RobotRemoteControl::SetCtrlKeyboard);
	QObject::connect(m_table, &QTableView::doubleClicked, this, &RobotRemoteControl::doubleClickTable);
	QObject::connect(m_table, &QTableView::clicked, this, &RobotRemoteControl::clickTable);
	QObject::connect(_pbutAdd, &QPushButton::pressed, this, &RobotRemoteControl::PressedAddRobotButton);
	QObject::connect(_pbutDel, &QPushButton::pressed, this, &RobotRemoteControl::PressedDeleteRobotButton);
	QObject::connect(m_pbutConnect, &QPushButton::pressed, this, &RobotRemoteControl::PressedConnectButton);

	m_gamepad = new QGamepad(-1, this);

	QObject::connect(m_gamepad, &QGamepad::axisLeftXChanged, this, &RobotRemoteControl::axisLeftXChanged);
	QObject::connect(m_gamepad, &QGamepad::axisLeftYChanged, this, &RobotRemoteControl::axisLeftYChanged);
	QObject::connect(m_gamepad, &QGamepad::axisRightXChanged, this, &RobotRemoteControl::axisRightXChanged);
	QObject::connect(m_gamepad, &QGamepad::axisRightYChanged, this, &RobotRemoteControl::axisRightYChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonAChanged, this, &RobotRemoteControl::buttonAChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonBChanged, this, &RobotRemoteControl::buttonBChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonCenterChanged, this, &RobotRemoteControl::buttonCenterChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonDownChanged, this, &RobotRemoteControl::buttonDownChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonGuideChanged, this, &RobotRemoteControl::buttonGuideChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonL1Changed, this, &RobotRemoteControl::buttonL1Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonL2Changed, this, &RobotRemoteControl::buttonL2Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonL3Changed, this, &RobotRemoteControl::buttonL3Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonLeftChanged, this, &RobotRemoteControl::buttonLeftChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonR1Changed, this, &RobotRemoteControl::buttonR1Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonR2Changed, this, &RobotRemoteControl::buttonR2Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonR3Changed, this, &RobotRemoteControl::buttonR3Changed);
	QObject::connect(m_gamepad, &QGamepad::buttonSelectChanged, this, &RobotRemoteControl::buttonSelectChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonRightChanged, this, &RobotRemoteControl::buttonRightChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonStartChanged, this, &RobotRemoteControl::buttonStartChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonUpChanged, this, &RobotRemoteControl::buttonUpChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonXChanged, this, &RobotRemoteControl::buttonXChanged);
	QObject::connect(m_gamepad, &QGamepad::buttonYChanged, this, &RobotRemoteControl::buttonYChanged);

	return;
}

void RobotRemoteControl::Save()
{
	// 创建子目录
	QDir _dir(".");
	QDir _dirConfig("Config");

	// 创建配置存放目录
	if (_dirConfig.exists() == false)
	{
		_dir.mkdir("Config");
	}

	QJsonObject	_jobjRoot, _jobjKeys;
	QJsonArray _jarrRobot;

	// 保存键盘映射
	for (CtrlKeyboard::iterator it = m_mapCtrlKeys.begin(); it != m_mapCtrlKeys.end(); ++it)
	{
		Qt::Key key = it.key();

		QString	_strKey = KeyEdit::KeyToString(key);

		switch (it.value())
		{
		case MoveOn:
			_jobjKeys.insert(_strKey, "MoveOn");
			break;
		case MoveBack:
			_jobjKeys.insert(_strKey, "MoveBack");
			break;
		case TurnLeft:
			_jobjKeys.insert(_strKey, "TurnLeft");
			break;
		case TurnRight:
			_jobjKeys.insert(_strKey, "TurnRight");
			break;
		case LSpeedUp:
			_jobjKeys.insert(_strKey, "LSpeedUp");
			break;
		case LSpeedDown:
			_jobjKeys.insert(_strKey, "LSpeedDown");
			break;
		case ASpeedUp:
			_jobjKeys.insert(_strKey, "ASpeedUp");
			break;
		case ASpeedDown:
			_jobjKeys.insert(_strKey, "ASpeedDown");
			break;
		case LightSwitch:
			_jobjKeys.insert(_strKey, "LightSwitch");
			break;
		case SpraySwitch:
			_jobjKeys.insert(_strKey, "SpraySwitch");
			break;
		case LookUp:
			_jobjKeys.insert(_strKey, "LookUp");
			break;
		case LookDown:
			_jobjKeys.insert(_strKey, "LookDown");
			break;
		case LookLeft:
			_jobjKeys.insert(_strKey, "LookLeft");
			break;
		case LookRight:
			_jobjKeys.insert(_strKey, "LookRight");
			break;
		case ResetView:
			_jobjKeys.insert(_strKey, "ResetView");
			break;
		}
	}

	// 保存机器人配置
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		_jarrRobot.push_back(_aItem->text());
	}

	// 保存服务端配置
	_jobjRoot.insert("Server", m_leditAddr->text());
	_jobjRoot.insert("Keyboard", _jobjKeys);
	_jobjRoot.insert("Robot", _jarrRobot);

	// 创建配置文件
	QFile _fileSrvConfig("Config/Client.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileSrvConfig.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		_fileSrvConfig.write(QJsonDocument(_jobjRoot).toJson());
	}

	return;
}

void RobotRemoteControl::Load()
{
	// 读取配置信息
	QString _srvAddr = "", _dbHost = "",/* _dbName = "",*/ _dbUser = "", _dbPwd = "";

	QFile _fileConfig("Config/Client.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileConfig.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QJsonDocument _jdoc = QJsonDocument::fromJson(_fileConfig.readAll());
		QJsonObject _jobjRoot = _jdoc.object();

		QJsonObject _jsonKeys = _jobjRoot.value("Keyboard").toObject();
		m_leditAddr->setText(_jobjRoot.value("Server").toString());

		QJsonArray _jsonRobots = _jobjRoot.value("Robot").toArray();

		CtrlKeyboard _board;

		QStringList _keys = _jsonKeys.keys();

		for (int i = 0; i < _keys.size(); ++i)
		{
			Qt::Key _key = KeyEdit::StringToKey(_keys.at(i));

			QString _strValue = _jsonKeys.value(_keys.at(i)).toString();

			if (_strValue == "MoveOn")
			{
				_board[_key] = MoveOn;
			}
			else if (_strValue == "MoveBack")
			{
				_board[_key] = MoveBack;
			}
			else if (_strValue == "TurnLeft")
			{
				_board[_key] = TurnLeft;
			}
			else if (_strValue == "TurnRight")
			{
				_board[_key] = TurnRight;
			}
			else if (_strValue == "LSpeedUp")
			{
				_board[_key] = LSpeedUp;
			}
			else if (_strValue == "LSpeedDown")
			{
				_board[_key] = LSpeedDown;
			}
			else if (_strValue == "ASpeedUp")
			{
				_board[_key] = ASpeedUp;
			}
			else if (_strValue == "ASpeedDown")
			{
				_board[_key] = ASpeedDown;
			}
			else if (_strValue == "LightSwitch")
			{
				_board[_key] = LightSwitch;
			}
			else if (_strValue == "SpraySwitch")
			{
				_board[_key] = SpraySwitch;
			}
			else if (_strValue == "LookUp")
			{
				_board[_key] = LookUp;
			}
			else if (_strValue == "LookDown")
			{
				_board[_key] = LookDown;
			}
			else if (_strValue == "LookLeft")
			{
				_board[_key] = LookLeft;
			}
			else if (_strValue == "LookRight")
			{
				_board[_key] = LookRight;
			}
			else if (_strValue == "ResetView")
			{
				_board[_key] = ResetView;
			}
		}

		if (_board.size() > 0)
		{
			m_mapCtrlKeys = _board;
		}

		for (QJsonArray::iterator it = _jsonRobots.begin(); it != _jsonRobots.end(); ++it)
		{
			AddRobot(it->toString());
		}

		if (m_leditAddr->text().isEmpty() == false)
		{
			PressedConnectButton();
		}

		_fileConfig.close();
	}

	m_wCtrlPage->SetKeyboard(m_mapCtrlKeys);

	return;
}

void RobotRemoteControl::closeEvent(QCloseEvent* event)
{
	if (m_socket && m_socket->isOpen())
	{
		m_socket->close();
		m_socket->waitForDisconnected();
	}

	Save();

	event->accept();

	return;
}

void RobotRemoteControl::keyPressEvent(QKeyEvent* event)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type == "Robot")
	{
		RobotClientWidget* _widget = (RobotClientWidget*)m_tab->currentWidget();

		if (m_mapCtrlKeys.find((Qt::Key)event->key()) == m_mapCtrlKeys.end())
		{
			return;
		}

		switch (m_mapCtrlKeys[(Qt::Key)event->key()])
		{
		case MoveOn:
			axisLeftYChanged(-1.0);
			break;/*!< 前进按键 */
		case MoveBack:
			axisLeftYChanged(1.0);
			break;/*!< 后退按键 */
		case TurnLeft:
			axisLeftXChanged(-1.0);
			break;/*!< 左转按键 */
		case TurnRight:
			axisLeftXChanged(1.0);
			break;/*!< 右转按键 */
		case LSpeedUp:
			buttonUpChanged(true);
			break;/*!< 线速度加速按键 */
		case LSpeedDown:
			buttonDownChanged(true);
			break;/*!< 线速度减速按键 */
		case ASpeedUp:
			buttonLeftChanged(true);
			break;/*!< 角速度加速按键 */
		case ASpeedDown:
			buttonRightChanged(true);
			break;/*!< 角速度减速按键 */
		case LightSwitch:
			buttonL1Changed(true);
			break;/*!< 辅助灯开关 */
		case SpraySwitch:
			buttonR1Changed(true);
			break;/*!< 喷雾开关 */
		case LookUp:
			axisRightYChanged(-1.0);
			break;/*!< 摄像头抬起按键 */
		case LookDown:
			axisRightYChanged(1.0);
			break;/*!< 摄像头低下按键 */
		case LookLeft:
			axisRightXChanged(-1.0);
			break;/*!< 摄像头左转按键 */
		case LookRight:
			axisRightXChanged(1.0);
			break;/*!< 摄像头右转按键 */
		case ResetView:
			buttonR3Changed(true);
			break;/*!< 摄像头右转按键 */
		}
	}

	return;
}

void RobotRemoteControl::keyReleaseEvent(QKeyEvent* event)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type == "Robot")
	{
		RobotClientWidget* _widget = (RobotClientWidget*)m_tab->currentWidget();

		if (m_mapCtrlKeys.find((Qt::Key)event->key()) == m_mapCtrlKeys.end())
		{
			return;
		}

		switch (m_mapCtrlKeys[(Qt::Key)event->key()])
		{
		case MoveOn:
			axisLeftYChanged(0);
			break;/*!< 前进按键 */
		case MoveBack:
			axisLeftYChanged(0);
			break;/*!< 后退按键 */
		case TurnLeft:
			axisLeftXChanged(0);
			break;/*!< 左转按键 */
		case TurnRight:
			axisLeftXChanged(0);
			break;/*!< 右转按键 */
		case LSpeedUp:
			buttonUpChanged(false);
			break;/*!< 线速度加速按键 */
		case LSpeedDown:
			buttonDownChanged(false);
			break;/*!< 线速度减速按键 */
		case ASpeedUp:
			buttonLeftChanged(false);
			break;/*!< 角速度加速按键 */
		case ASpeedDown:
			buttonRightChanged(false);
			break;/*!< 角速度减速按键 */
		case LightSwitch:
			buttonL1Changed(false);
			break;/*!< 辅助灯开关 */
		case SpraySwitch:
			buttonR1Changed(false);
			break;/*!< 喷雾开关 */
		case LookUp:
			axisRightYChanged(0);
			break;/*!< 摄像头抬起按键 */
		case LookDown:
			axisRightYChanged(0);
			break;/*!< 摄像头低下按键 */
		case LookLeft:
			axisRightXChanged(0);
			break;/*!< 摄像头左转按键 */
		case LookRight:
			axisRightXChanged(0);
			break;/*!< 摄像头右转按键 */
		case ResetView:
			buttonR3Changed(false);
			break;/*!< 摄像头右转按键 */
		}
	}

	return;
}

void RobotRemoteControl::SetCtrlKeyboard(CtrlKeyboard keys)
{
	m_mapCtrlKeys = keys;

	QMessageBox::information(this, QString::fromLocal8Bit("按键设置"), QString::fromLocal8Bit("按键设置成功!"));

	return;
}

void RobotRemoteControl::RemoveSubTab(int index)
{
	QString _title = m_tab->tabBar()->tabText(index);

	if (_title == QString::fromLocal8Bit("首页"))
	{
		return;
	}

	if (_title == QString::fromLocal8Bit("控制器"))
	{
		return;
	}

	if (_title == QString::fromLocal8Bit("设置"))
	{
		return;
	}

	if (_title == QString::fromLocal8Bit("我"))
	{
		return;
	}

	qDebug() << "Remove Tab:" << _title;

	m_tab->removeTab(index);

	return;
}

void RobotRemoteControl::axisLeftXChanged(double value)
{
	if (value == 1.0)
	{// 向右
		m_mov = CtrlKeys::TurnRight;
	}
	else if (value == -1.0)
	{// 向左
		m_mov = CtrlKeys::TurnLeft;
	}
	else if (value == 0.0)
	{// 停止
		if (m_mov == TurnLeft || m_mov == TurnRight)
		{
			m_mov = CtrlKeys::Unknow;
		}
	}

	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->axisLeftXChanged(value);

	return;
}

void RobotRemoteControl::axisLeftYChanged(double value)
{
	if (value == 1.0)
	{// 向右
		m_mov = CtrlKeys::MoveBack;
	}
	else if (value == -1.0)
	{// 向左
		m_mov = CtrlKeys::MoveOn;
	}
	else if (value == 0.0)
	{// 停止
		if (m_mov == MoveBack || m_mov == MoveOn)
		{
			m_mov = CtrlKeys::Unknow;
		}
	}

	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->axisLeftYChanged(value);

	return;
}

void RobotRemoteControl::axisRightXChanged(double value)
{
	if (value > 0)
	{// 向右
		m_eyes = CtrlKeys::LookRight;
	}
	else if (value < 0)
	{// 向左
		m_eyes = CtrlKeys::LookLeft;
	}
	else
	{// 停止
		if (m_eyes == LookRight || m_eyes == LookLeft)
		{
			m_eyes = CtrlKeys::Unknow;
		}
	}

	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->axisRightXChanged(value);

	return;
}

void RobotRemoteControl::axisRightYChanged(double value)
{
	if (value > 0)
	{// 向右
		m_eyes = CtrlKeys::LookUp;
	}
	else if (value < 0)
	{// 向左
		m_eyes = CtrlKeys::LookDown;
	}
	else
	{// 停止
		if (m_eyes == LookUp || m_eyes == LookDown)
		{
			m_eyes = CtrlKeys::Unknow;
		}
	}

	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->axisRightYChanged(value);

	return;
}

void RobotRemoteControl::buttonAChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonAChanged(value);

	return;
}

void RobotRemoteControl::buttonBChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonBChanged(value);

	return;
}

void RobotRemoteControl::buttonCenterChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonCenterChanged(value);

	return;
}

void RobotRemoteControl::buttonDownChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonDownChanged(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	if (_widget->LineSpeed() - 5 < 0)
	{
		return;
	}

	_jCtrl.insert("LSpeed", _widget->LineSpeed() - 5);

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonGuideChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonGuideChanged(value);

	return;
}

void RobotRemoteControl::buttonL1Changed(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonL1Changed(value);

	return;
}

void RobotRemoteControl::buttonL2Changed(double value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonL2Changed(value);

	return;
}

void RobotRemoteControl::buttonL3Changed(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonL3Changed(value);

	return;
}

void RobotRemoteControl::buttonLeftChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonLeftChanged(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	if (_widget->ArcSpeed() + 5 > 100)
	{
		_jCtrl.insert("ASpeed", 100);
	}
	else
	{
		_jCtrl.insert("ASpeed", _widget->ArcSpeed() + 5);
	}

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonR1Changed(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonR1Changed(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	if (_widget->SparySwitch())
	{
		_jCtrl.insert("Spray", false);
	}
	else
	{
		_jCtrl.insert("Spray", true);
	}

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonR2Changed(double value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonR2Changed(value);

	return;
}

void RobotRemoteControl::buttonR3Changed(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonR3Changed(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	_jCtrl.insert("Eyes", "Reset");

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonRightChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonRightChanged(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	if (_widget->ArcSpeed() - 5 < 0)
	{
		return;
	}

	_jCtrl.insert("ASpeed", _widget->ArcSpeed() - 5);

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonSelectChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonSelectChanged(value);

	return;
}

void RobotRemoteControl::buttonStartChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonStartChanged(value);

	return;
}

void RobotRemoteControl::buttonUpChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());
	_widget->m_wCtrlbox->buttonUpChanged(value);

	if (_widget->IsConnected() == false)
	{
		return;
	}

	QJsonObject _jCmd, _jCtrl;

	if (_widget->LineSpeed() + 5 > 100)
	{
		_jCtrl.insert("LSpeed", 100);
	}
	else
	{
		_jCtrl.insert("LSpeed", _widget->LineSpeed() + 5);
	}

	_jCmd.insert("Control", _jCtrl);

	SendPackage(CreatePackage("", _jCmd));

	return;
}

void RobotRemoteControl::buttonXChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonXChanged(value);

	return;
}

void RobotRemoteControl::buttonYChanged(bool value)
{
	QString _title = m_tab->tabBar()->tabText(m_tab->currentIndex());

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	if (_type != "Robot")
	{
		return;
	}

	((RobotClientWidget*)m_tab->currentWidget())->m_wCtrlbox->buttonYChanged(value);

	return;
}

void RobotRemoteControl::doubleClickTable(const QModelIndex& index)
{
	if (index.isValid())
	{
		QString _title = QString::fromLocal8Bit("Robot:%1").arg(m_model->item(index.row(), 0)->text());

		for (int i = 0; i < m_tab->count(); ++i)
		{
			QString	_pag = m_tab->tabBar()->tabText(i);

			if (_pag == _title)
			{
				return;
			}
		}

		QString _uuid = m_model->item(index.row(), 0)->text();

		// 显示分页
		if (m_mapRobotWidgets.find(_uuid) != m_mapRobotWidgets.end())
		{
			int n = m_tab->addTab(m_mapRobotWidgets[_uuid], _title);
			m_tab->setCurrentIndex(n);
		}
	}

	return;
}

void RobotRemoteControl::clickTable(const QModelIndex& index)
{
	if (index.isValid())
	{
		m_leditUuid->setText(m_model->item(index.row(), 0)->text());
	}

	return;
}

void RobotRemoteControl::PressedAddRobotButton()
{
	if (m_leditUuid->text().isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加机器人"), QString::fromLocal8Bit("添加机器人失败!请填写机器人的UUID."));
		return;
	}

	QString _uuid = m_leditUuid->text();

	if (AddRobot(_uuid) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加机器人"), QString::fromLocal8Bit("添加机器人失败!已存在相同的UUID."));
	}

	return;
}

void RobotRemoteControl::PressedDeleteRobotButton()
{
	if (m_leditUuid->text().isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("删除机器人"), QString::fromLocal8Bit("删除机器人失败!请填写机器人的UUID,"));
		return;
	}

	if (m_socket->peerAddress().isNull() == false)
	{
		// 申请取消订阅

		QJsonObject	jCmd;
		QJsonArray jUuids;
		jUuids.push_back(m_leditUuid->text());
		jCmd.insert("Remove", jUuids);

		SendPackage(CreatePackage("", jCmd));
	}
	else
	{
		DeleteRobot(m_leditUuid->text());
	}

	return;
}

void RobotRemoteControl::PressedConnectButton()
{
	if (m_socket->peerAddress().isNull() == false)
	{
		m_socket->close();

		return;
	}

	if (m_leditAddr->text().isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("连接服务器"), QString::fromLocal8Bit("连接服务器失败!请填写服务器地址信息."));
		return;
	}

	QString _addr = m_leditAddr->text();

	quint16 _port = _addr.section(':', -1, -1).toInt();
	QString _ip = _addr.section(':', 0, -2);

	QHostAddress _host;
	if (_host.setAddress(_ip) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("连接服务器"), QString::fromLocal8Bit("连接服务器失败!无效的服务器地址."));
		return;
	}

	if (_port <= 0 || _port > 65535)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("连接服务器"), QString::fromLocal8Bit("连接服务器失败!无效的服务器端口."));
		return;
	}

	m_socket->connectToHost(_host, _port);

	m_pbutConnect->setEnabled(false);
	m_labDetail->setText(QString::fromLocal8Bit("连接中"));
	m_leditAddr->setReadOnly(true);

	return;
}

void RobotRemoteControl::ServerError(QAbstractSocket::SocketError error)
{
	m_labDetail->setText(m_socket->errorString());
	m_pbutConnect->setEnabled(true);
	m_pbutConnect->setText(QString::fromLocal8Bit("连接"));
	m_leditAddr->setReadOnly(false);

	return;
}

void RobotRemoteControl::ServerConnected()
{
	m_pbutConnect->setText(QString::fromLocal8Bit("中断"));
	m_labDetail->setText(QString::fromLocal8Bit("已连接"));
	m_pbutConnect->setEnabled(true);
	m_leditAddr->setReadOnly(true);

	return;
}

void RobotRemoteControl::ServerDisconnected()
{
	m_pbutConnect->setText(QString::fromLocal8Bit("连接"));
	m_labDetail->setText(QString::fromLocal8Bit("未连接"));
	m_pbutConnect->setEnabled(true);
	m_leditAddr->setReadOnly(false);

	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		m_model->item(i, 1)->setText(QString::fromLocal8Bit("未连接"));
	}

	return;
}

void RobotRemoteControl::ReadData()
{
	if (m_socket->isReadable() == false)
	{
		return;
	}

	m_buf += m_socket->readAll();

	QByteArrayList _list = m_buf.split('|');

	m_buf.clear();

	QByteArrayList _listPkg;

	for (int i = 0; i != _list.size(); ++i)
	{
		QByteArray _pkg = _list.at(i);

		//qDebug() << _pkg << endl;

		QJsonParseError	_error;
		QJsonDocument _doc = QJsonDocument::fromJson(_pkg, &_error);

		if (_error.error != QJsonParseError::NoError)
		{
			//qDebug() << _error.errorString();

			if (i + 1 < _list.size())
			{
				continue;
			}

			m_buf = _list.at(i);

			return;
		}

		QJsonObject _jobj = _doc.object();

		QString _uuid = _jobj.value("From").toString();
		QString _self = _jobj.value("To").toString();

		QJsonObject	_jobjCmd = _jobj.value("Cmd").toObject();

		QStringList _keys = _jobjCmd.keys();

		for (QStringList::iterator itK = _keys.begin(); itK != _keys.end(); ++itK)
		{
			if (*itK == "Hand" && _self.isEmpty())
			{
				SendPackage(CreatePackage(_uuid, _jobjCmd).toLatin1());
			}
			else if (*itK == "Take")
			{
				QJsonObject	_jobjResult = _jobj.value("Result").toObject();

				QStringList _uuids = _jobjResult.keys();

				for (QStringList::iterator itU = _uuids.begin(); itU != _uuids.end(); ++itU)
				{
					bool _connected = _jobjResult.value(*itU).toBool();

					// 更新机器人状态
					UpdateRobot(*itU, _connected);
				}
			}
			else if (*itK == "Remove")
			{
				QJsonObject	_jobjResult = _jobj.value("Result").toObject();

				QStringList _uuids = _jobjResult.keys();

				for (QStringList::iterator itU = _uuids.begin(); itU != _uuids.end(); ++itU)
				{
					bool _removeed = _jobjResult.value(*itU).toBool();

					// 释放机器人资源
					if (_removeed)
					{
						DeleteRobot(*itU);
					}
				}
			}
			else if (*itK == "Camera")
			{
				QByteArray img = QByteArray::fromBase64(_jobjCmd.value(*itK).toString().toLatin1());

				UpdateRobot(_uuid, img);
			}
			else if (*itK == "Device")
			{
				// 更新机器人数据
				int _lSpeed = 0, _aSpeed = 0, _battery = 0, _residual = 0;
				bool _spray = false;

				QJsonObject jStatus = _jobjCmd.value(*itK).toObject();
				_lSpeed = jStatus.value("LSpeed").toInt();
				_aSpeed = jStatus.value("ASpeed").toInt();
				_spray = jStatus.value("Spray").toBool();
				_battery = jStatus.value("Electric").toInt();
				_residual = jStatus.value("Water").toInt();

				UpdateRobot(_uuid, _battery, _residual, _spray, 0, _lSpeed, _aSpeed, 0, 0);
			}
		}
	}

	return;
}

void RobotRemoteControl::tabCurrentChanged(int index)
{
	QString _title = m_tab->tabBar()->tabText(index);

	QString _uuid = _title.section(':', -1, -1);
	QString _type = _title.section(':', 0, -2);

	// 获取机器人UUID
	if (_type != "Robot")
	{
		m_robotUuid = "";
		return;
	}

	RobotClientWidget* _widget = ((RobotClientWidget*)m_tab->currentWidget());

	if (_widget->IsConnected())
	{
		m_robotUuid = _uuid;
	}

	return;
}

void RobotRemoteControl::SendPackage(QString package)
{
	m_mutex.lock();

	m_socket->write(package.toLatin1());
	m_socket->flush();

	m_mutex.unlock();

	return;
}

void RobotRemoteControl::Thread()
{
	QGamepadManager* _manager = QGamepadManager::instance();
	QList<int> _devices;

	std::chrono::steady_clock::time_point _tp = std::chrono::steady_clock::now();

	while (m_bClose == false)
	{
		if (m_gamepad->isConnected() == false)
		{// 加载手柄
			qApp->processEvents();
			_devices = _manager->connectedGamepads();

			if (_devices.isEmpty() == false)
			{
				m_gamepad->setDeviceId(_devices.first());

				qDebug() << _devices.first() << ":" << _manager->gamepadName(_devices.first());
			}
		}

		if (m_socket->peerAddress().isNull() == false)
		{
			// 循环请求订阅

			QJsonObject _jCmd, _jCtrl;
			QJsonArray _array;

			for (int i = 0; i < m_model->rowCount(); ++i)
			{
				QStandardItem* _aItem = m_model->item(i, 1);

				if (_aItem->text() != QString::fromLocal8Bit("未连接"))
				{
					continue;
				}

				_array.push_back(m_model->item(i, 0)->text());
			}

			if (m_robotUuid.isEmpty() == false)
			{
				/*qDebug() << "Move:" << m_mov;
				qDebug() << "Eyes:" << m_eyes;*/
				if (m_mov != CtrlKeys::Unknow)
				{
					switch (m_mov)
					{
					case MoveOn:
						_jCtrl.insert("Base", "MoveOn");
						break;
					case MoveBack:
						_jCtrl.insert("Base", "MoveBack");
						break;
					case TurnLeft:
						_jCtrl.insert("Base", "TurnLeft");
						break;
					case TurnRight:
						_jCtrl.insert("Base", "TurnRight");
						break;
					}
				}

				if (m_eyes != CtrlKeys::Unknow)
				{
					switch (m_eyes)
					{
					case LookUp:
						_jCtrl.insert("Eyes", "LookUp");
						break;
					case LookDown:
						_jCtrl.insert("Eyes", "LookDown");
						break;
					case LookLeft:
						_jCtrl.insert("Eyes", "LookLeft");
						break;
					case LookRight:
						_jCtrl.insert("Eyes", "LookRight");
						break;
					}
				}

				if (_jCtrl.isEmpty() == false)
				{
					_jCmd.insert("Control", _jCtrl);
				}
			}

			if (_array.size() > 0)
			{
				_jCmd.insert("Take", _array);
			}

			if (_jCmd.isEmpty() == false)
			{
				std::chrono::milliseconds dis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _tp);

				if (dis.count() > 300)
				{
					emit Send(CreatePackage("", _jCmd));

					_tp = std::chrono::steady_clock::now();
				}
			}
		}
		else
		{
			_tp = std::chrono::steady_clock::now();
		}

		Sleep(1);
	}

	return;
}

bool RobotRemoteControl::AddRobot(QString uuid)
{
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text() == uuid)
		{
			return false;
		}
	}

	QList<QStandardItem*> _list;
	_list.push_back(new QStandardItem(uuid));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("未连接")));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("0%")));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("0%")));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("关")));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("0%")));

	m_model->appendRow(_list);

	for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		(*it)->setEditable(false);
		(*it)->setToolTip((*it)->text());
	}

	// 创建RobotClient
	m_mapRobotWidgets[uuid] = new RobotClientWidget(uuid, this);
	m_mapRobotWidgets[uuid]->hide();

	QObject::connect(m_gamepad, &QGamepad::connectedChanged, m_mapRobotWidgets[uuid]->m_wCtrlbox, &ControlBoxWidget::connectedChanged);

	return true;
}

void RobotRemoteControl::DeleteRobot(QString uuid)
{
	if (uuid.isEmpty())
	{
		return;
	}

	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text() != uuid)
		{
			continue;
		}

		m_model->removeRow(i);

		break;
	}

	QString _title = QString::fromLocal8Bit("Robot:%1").arg(uuid);

	for (int i = 0; i < m_tab->count(); ++i)
	{
		QString	_pag = m_tab->tabBar()->tabText(i);

		if (_pag == _title)
		{
			m_tab->removeTab(i);

			break;
		}
	}

	// 释放资源
	if (m_mapRobotWidgets.find(uuid) != m_mapRobotWidgets.end())
	{
		m_mapRobotWidgets[uuid]->deleteLater();
	}

	return;
}

QString RobotRemoteControl::CreatePackage(QString to, QJsonObject cmd)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", m_strUuid);
	_jPkg.insert("To", to);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", cmd);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotRemoteControl::CreatePackage(QString to, QJsonArray cmd)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", m_strUuid);
	_jPkg.insert("To", to);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", cmd);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotRemoteControl::CreatePackage(QString to, QJsonObject cmd, QJsonObject result)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", m_strUuid);
	_jPkg.insert("To", to);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", cmd);
	_jPkg.insert("Result", result);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotRemoteControl::CreatePackage(QString to, QJsonArray cmd, QJsonObject result)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", m_strUuid);
	_jPkg.insert("To", to);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", cmd);
	_jPkg.insert("Result", result);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotRemoteControl::CreatePackage(QString to, QJsonArray cmd, QJsonArray result)
{
	QJsonObject _jPkg;

	_jPkg.insert("From", m_strUuid);
	_jPkg.insert("To", to);
	_jPkg.insert("Date", GetDate());
	_jPkg.insert("Cmd", cmd);
	_jPkg.insert("Result", result);

	return "|" + QString(QJsonDocument(_jPkg).toJson());
}

QString RobotRemoteControl::GetDate()
{
	using namespace std;

	chrono::system_clock::time_point tpCur = chrono::system_clock::now();

	time_t tt = chrono::system_clock::to_time_t(tpCur);
	tm* t = localtime(&tt);

	auto timeNow = chrono::duration_cast<chrono::milliseconds>(tpCur.time_since_epoch());

	QString str = QString("%1/%2/%3 %4:%5:%6")
		.arg(t->tm_year + 1900, 4, 10, QLatin1Char('0'))
		.arg(t->tm_mon + 1, 2, 10, QLatin1Char('0'))
		.arg(t->tm_mday, 2, 10, QLatin1Char('0'))
		.arg(t->tm_hour, 2, 10, QLatin1Char('0'))
		.arg(t->tm_min, 2, 10, QLatin1Char('0'))
		.arg(t->tm_sec, 2, 10, QLatin1Char('0'));

	return str;
}

void RobotRemoteControl::UpdateRobot(QString uuid, bool connected)
{
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text() != uuid)
		{
			continue;
		}

		if (connected)
		{
			m_model->item(i, 1)->setText(QString::fromLocal8Bit("已连接"));
		}
		else
		{
			m_model->item(i, 1)->setText(QString::fromLocal8Bit("未连接"));
		}

		m_model->item(i, 1)->setToolTip(m_model->item(i, 1)->text());
	}

	if (m_mapRobotWidgets.find(uuid) != m_mapRobotWidgets.end())
	{
		// 更新机器人连接状态
		m_mapRobotWidgets[uuid]->Update(connected);
	}

	return;
}

void RobotRemoteControl::UpdateRobot(QString uuid, int battery, int residual, bool spray, int speed, int lspeed, int aspeed, int x, int y)
{
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text() != uuid)
		{
			continue;
		}

		m_model->item(i, 2)->setText(QString::fromLocal8Bit("%1").arg(battery));
		m_model->item(i, 3)->setText(QString::fromLocal8Bit("%1").arg(residual));

		if (spray)
		{
			m_model->item(i, 4)->setText(QString::fromLocal8Bit("开"));
		}
		else
		{
			m_model->item(i, 4)->setText(QString::fromLocal8Bit("关"));
		}

		m_model->item(i, 5)->setText(QString::fromLocal8Bit("%1").arg(speed));

		m_model->item(i, 2)->setToolTip(m_model->item(i, 2)->text());
		m_model->item(i, 3)->setToolTip(m_model->item(i, 3)->text());
		m_model->item(i, 4)->setToolTip(m_model->item(i, 4)->text());
		m_model->item(i, 5)->setToolTip(m_model->item(i, 5)->text());
	}

	if (m_mapRobotWidgets.find(uuid) != m_mapRobotWidgets.end())
	{
		// 更新机器人连接状态
		m_mapRobotWidgets[uuid]->Update(battery, residual, spray, speed, lspeed, aspeed, x, y);
	}

	return;
}

void RobotRemoteControl::UpdateRobot(QString uuid, QByteArray img)
{
	if (m_mapRobotWidgets.find(uuid) != m_mapRobotWidgets.end())
	{
		// 更新机器人连接状态
		//m_mapRobotWidgets[uuid]->m_wImage->Load(img, "JPG");
		m_mapRobotWidgets[uuid]->m_wCtrlbox->Load(img, "JPG");
	}

	return;
}
