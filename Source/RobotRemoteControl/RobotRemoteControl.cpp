#include "RobotRemoteControl.h"

RobotRemoteControl::RobotRemoteControl(QWidget* parent)
	: QMainWindow(parent)
	, m_tab(nullptr)
{
	//ui.setupUi(this);
	Initialize();

	InitKeyboard();

	Load();
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

	m_mapCtrlKeys[Qt::Key::Key_I] = LookUp;
	m_mapCtrlKeys[Qt::Key::Key_K] = LookDown;
	m_mapCtrlKeys[Qt::Key::Key_J] = LookLeft;
	m_mapCtrlKeys[Qt::Key::Key_L] = LookRight;

	return;
}

void RobotRemoteControl::Initialize()
{
	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("地址："), this);					/*!< 服务端地址标签 */
	QLineEdit* _leditAddr = new QLineEdit(this);											/*!< 服务端地址编辑框 */
	QPushButton* _pbutConnect = new QPushButton(QString::fromLocal8Bit("连接"), this);		/*!< 服务端连接按钮 */

	QHBoxLayout* _laySrvAddr = new QHBoxLayout(this);										/*!< 服务端配置布局 */

	// 添加控件
	_laySrvAddr->addWidget(_labAddr);
	_laySrvAddr->addWidget(_leditAddr);
	_laySrvAddr->addWidget(_pbutConnect);

	QLabel* _labStatus = new QLabel(QString::fromLocal8Bit("状态："), this);				/*!< 服务端状态标签 */
	QLabel* _labDetail = new QLabel(QString::fromLocal8Bit("未连接"), this);				/*!< 服务端状态信息标签 */

	QHBoxLayout* _laySrvStauts = new QHBoxLayout(this);										/*!< 服务端状态布局 */

	// 添加控件
	_laySrvStauts->addWidget(_labStatus);
	_laySrvStauts->addWidget(_labDetail);

	QVBoxLayout* _laySrv = new QVBoxLayout(this);											/*!< 服务端布局 */

	// 添加布局
	_laySrv->addLayout(_laySrvAddr);
	_laySrv->addLayout(_laySrvStauts);

	QGroupBox* _groupSrv = new QGroupBox(QString::fromLocal8Bit("服务端"), this);			/*!< 服务端组合框 */

	// 设置布局
	_groupSrv->setLayout(_laySrv);

	QTableView* _table = new QTableView(this);												/*!< 机器人表单 */

	QGroupBox* _groupRobot = new QGroupBox(QString::fromLocal8Bit("机器人"), this);			/*!< 机器人组合框 */

	QVBoxLayout* _layRobot = new QVBoxLayout(this);											/*!< 机器人布局 */

	// 添加控件
	_layRobot->addWidget(_table);

	// 设置布局
	_groupRobot->setLayout(_layRobot);

	QVBoxLayout* _layFPage = new QVBoxLayout(this);											/*!< 首页布局 */

	// 添加控件
	_layFPage->addWidget(_groupSrv);
	_layFPage->addWidget(_groupRobot);

	QWidget* _wFristPag = new QWidget(this);												/*!< 首页控件 */

	// 设置布局
	_wFristPag->setLayout(_layFPage);

	QWidget* _wCtrlPage = new QWidget(this);												/*!< 控制器控件 */

	m_tab = new QTabWidget(this);

	// 添加分页
	m_tab->addTab(_wFristPag, QString::fromLocal8Bit("首页"));
	m_tab->addTab(_wCtrlPage, QString::fromLocal8Bit("控制器"));

	QWidget* _wCenter = new QWidget(this);													/*!< 中心控件 */

	QHBoxLayout* _layMain = new QHBoxLayout(this);											/*!< 中心布局 */

	// 添加控件
	_layMain->addWidget(m_tab);

	// 设置布局
	_wCenter->setLayout(_layMain);

	// 设置窗体样式
	this->setCentralWidget(_wCenter);

	this->setWindowTitle(QString::fromLocal8Bit("机器人远程控制系统"));

	// 设置分页样式
	m_tab->setTabPosition(QTabWidget::TabPosition::West);
	m_tab->setTabsClosable(true);

	QStandardItemModel* _model = new QStandardItemModel(this);							/*!< 机器人表单数据模型 */

	// 添加列头
	_model->setColumnCount(3);

	int _index = 0;
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("UUID"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("连接"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));

	_table->setModel(_model);
	_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 设置编辑框样式
	_leditAddr->setPlaceholderText(QString::fromLocal8Bit("IP:端口 例如：127.0.0.1:8080"));

	// 添加信号和槽
	QObject::connect(m_tab, &QTabWidget::tabCloseRequested, this, &RobotRemoteControl::RemoveSubTab);

	return;
}

void RobotRemoteControl::Save()
{
}

void RobotRemoteControl::Load()
{
}

void RobotRemoteControl::closeEvent(QCloseEvent* event)
{
	Save();

	event->accept();

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

	if (_title == QString::fromLocal8Bit("我"))
	{
		return;
	}

	qDebug() << "Remove Tab:" << _title;

	m_tab->removeTab(index);

	return;
}
