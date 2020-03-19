#include "ControlBoxWidget.h"
#include "KeyboardSettingsWidget.h"
#include <QDebug>


ControlBoxWidget::ControlBoxWidget(QWidget* parent)
	: ImageWidge(parent)
	, m_axisLeftX(0)
	, m_axisLeftY(0)
	, m_axisRightX(0)
	, m_axisRightY(0)
	, m_buttonL1(false)
	, m_buttonL2(0)
	, m_buttonL3(false)
	, m_buttonR1(false)
	, m_buttonR2(0)
	, m_buttonR3(false)
	, m_buttonA(false)
	, m_buttonB(false)
	, m_buttonX(false)
	, m_buttonY(false)
	, m_buttonUp(false)
	, m_buttonDown(false)
	, m_buttonLeft(false)
	, m_buttonRight(false)

	, m_buttonCenter(false)
	, m_buttonGuide(false)
	, m_buttonStart(false)
	, m_buttonSelect(false)
	, m_bConnected(false)
{
	//ui.setupUi(this);
	Initialize();
}

ControlBoxWidget::~ControlBoxWidget()
{
}

void ControlBoxWidget::Initialize()
{
	setAutoFillBackground(true);			//自动设定背景颜色
	setPalette(QPalette(Qt::black));		//设置调色板的颜色为黑色

	setMinimumSize(640, 480);				//设置绘图区域窗体的最小大小
	setMaximumSize(1280, 720);				//设置绘图区域窗体的最小大小

	return;
}

void ControlBoxWidget::Draw(QPainter& painter)
{
	QSize _win = size();	/*!< 屏幕尺寸 */

	if (_win.width() == 0 || _win.height() == 0)
	{
		return;
	}

	float _fWidth = _win.width() / 8.0f;
	//float _fHeight = _win.height() / 2;

	//DrawImage(painter, QRect(_fWidth, 0, _fWidth * 2, _win.height() - _fWidth));
	DrawImage(painter, QRect(0, 0, _win.width(), _win.height()));

	DrawButtonLR(painter, QRect(0, 0, _fWidth, _fWidth * 2), m_buttonL1, m_buttonL2, "LB", "LT");

	DrawCtrlerStatus(painter, QRect(_fWidth * 3, _win.height() - _fWidth, _fWidth * 2, _fWidth));

	DrawButtonLR(painter, QRect(_fWidth * 7, 0, _fWidth, _fWidth * 2), m_buttonR1, m_buttonR2, "RB", "RT");

	DrawCross(painter, QRect(0, _win.height() - _fWidth, _fWidth, _fWidth));

	DrawAxisLeft(painter, QRect(_fWidth * 2, _win.height() - _fWidth, _fWidth, _fWidth));

	DrawAxisRight(painter, QRect(_fWidth * 5, _win.height() - _fWidth, _fWidth, _fWidth));

	DrawButtonXYAB(painter, QRect(_fWidth * 7, _win.height() - _fWidth, _fWidth, _fWidth));

	return;
}

void ControlBoxWidget::DrawAxisLeft(QPainter& painter, QRect rect)
{
	return DrawAxis(painter, rect, m_axisLeftX, m_axisLeftY, m_buttonL3, "L");
}

void ControlBoxWidget::DrawAxisRight(QPainter& painter, QRect rect)
{
	return DrawAxis(painter, rect, m_axisRightX, m_axisRightY, m_buttonR3, "R");
}

void ControlBoxWidget::DrawAxis(QPainter& painter, QRect rect, double axisX, double axisY, bool button, QString text)
{
	float _outCircleR = rect.width() / 3.0;	/*!< 左右摇杆大圆半径 (OR+IR)*2 = width; IR = OR/2; (OR*3/2)*2 = width;*/

	float _inCircleR = _outCircleR / 2.0;	/*!< 左右摇杆小圆半径 */

	QPoint _axis;		/*!< 摇杆的中心点 */

	_axis.setX(rect.x() + rect.width() / 2.0f);
	_axis.setY(rect.y() + rect.width() / 2.0f);

	QPoint _button;		/*!< L3/R3键中心点 */

	_button.setX(_axis.x() + _outCircleR * axisX);
	_button.setY(_axis.y() + _outCircleR * axisY);

	// 获取小圆的中心坐标
	_button = GetEllipse(_axis, _button, _outCircleR);

	// 绘制摇杆大圆
	painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
	painter.drawEllipse(_axis, (int)_outCircleR, (int)_outCircleR);

	painter.setPen(Qt::NoPen);

	// 绘制小圆按钮
	if (button)
	{
		painter.setBrush(Qt::blue);
	}
	else
	{
		painter.setBrush(Qt::white);
	}

	painter.drawEllipse(_button, (int)_inCircleR, (int)_inCircleR);

	// 绘制文字
	painter.setBrush(Qt::NoBrush);

	painter.setPen(Qt::black);

	QFont _oldFont = painter.font();

	QFont font;
	font.setPointSize(_inCircleR);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	painter.drawText(QRect(_button.x() - _inCircleR, _button.y() - _inCircleR, _inCircleR * 2, _inCircleR * 2), Qt::AlignCenter, text);

	painter.setFont(_oldFont);

	painter.setPen(Qt::NoPen);

	return;
}

void ControlBoxWidget::DrawCross(QPainter& painter, QRect rect)
{
	float _outCircleR = rect.width() / 2.0;	/*!< 大圆半径 */

	QPoint _center;							/*!< 中心坐标 */
	_center.setX(rect.x() + rect.width() / 2.0f);
	_center.setY(rect.y() + rect.width() / 2.0f);

	// 绘制大圆
	painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
	painter.drawEllipse(_center, (int)_outCircleR, (int)_outCircleR);

	painter.setPen(Qt::NoPen);

	double a = _outCircleR / 3.0f;

	double b = sqrt(pow(_outCircleR, 2) - pow(a, 2));

	// 绘制十字按键
	DrawCrossKey(painter, QRect(_center.x() - a, _center.y() - b, a * 2, b), m_buttonUp);
	DrawCrossKey(painter, QRect(_center.x() - a, _center.y(), a * 2, b), m_buttonDown);
	DrawCrossKey(painter, QRect(_center.x() - b, _center.y() - a, b, a * 2), m_buttonLeft);
	DrawCrossKey(painter, QRect(_center.x(), _center.y() - a, b, a * 2), m_buttonRight);

	// 绘制中心黑圆
	painter.setBrush(Qt::black);
	painter.drawEllipse(_center, (int)(_outCircleR / 4.0f), (int)(_outCircleR / 4.0f));

	painter.setBrush(Qt::NoBrush);

	return;
}

void ControlBoxWidget::DrawCrossKey(QPainter& painter, QRect rect, bool button)
{
	if (button)
	{
		painter.setBrush(Qt::blue);
	}
	else
	{
		painter.setBrush(Qt::white);
	}

	painter.drawRect(rect);

	painter.setBrush(Qt::NoBrush);

	return;
}

void ControlBoxWidget::DrawButtonXYAB(QPainter& painter, QRect rect)
{
	float _inCircleR = rect.width() / 6.0f;

	DrawButton(painter, QRect(rect.x(), rect.y() + 2 * _inCircleR, _inCircleR * 2, _inCircleR * 2), m_buttonX, "X");
	DrawButton(painter, QRect(rect.x() + 2 * _inCircleR, rect.y(), _inCircleR * 2, _inCircleR * 2), m_buttonY, "Y");
	DrawButton(painter, QRect(rect.x() + 2 * _inCircleR, rect.y() + 4 * _inCircleR, _inCircleR * 2, _inCircleR * 2), m_buttonA, "A");
	DrawButton(painter, QRect(rect.x() + 4 * _inCircleR, rect.y() + 2 * _inCircleR, _inCircleR * 2, _inCircleR * 2), m_buttonB, "B");

	return;
}

void ControlBoxWidget::DrawButton(QPainter& painter, QRect rect, bool button, QString text)
{
	if (button)
	{
		painter.setBrush(Qt::blue);
	}
	else
	{
		painter.setBrush(Qt::white);
	}

	float _outCircleR = rect.width() / 2.0f;

	QPointF center(rect.x() + _outCircleR, rect.y() + _outCircleR);

	painter.drawEllipse(center, (int)_outCircleR, (int)_outCircleR);

	painter.setBrush(Qt::NoBrush);

	// 绘制文字
	painter.setPen(Qt::black);

	QFont _oldFont = painter.font();

	QFont font;
	font.setPointSize(_outCircleR * 1.5);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	painter.drawText(rect, Qt::AlignCenter, text);

	painter.setFont(_oldFont);

	painter.setPen(Qt::NoPen);

	return;
}

void ControlBoxWidget::DrawButtonLR(QPainter& painter, QRect rect, bool button1, double button2, QString text1, QString text2)
{
	// 绘制L2/R2键
	painter.setPen(Qt::NoPen);

	float _fHeight = rect.height() / 3;
	QRect rectL2(rect.x() + 10, rect.y() + 10, rect.width() - 20, _fHeight);

	if (button2 > 0.0)
	{
		painter.setBrush(Qt::blue);
	}
	else
	{
		painter.setBrush(Qt::white);
	}

	painter.drawRect(rectL2);

	painter.setBrush(Qt::NoBrush);

	// 绘制L1/R1键
	QRect rectL1(rectL2.x(), rect.y() + _fHeight + 30, rect.width() - 20, _fHeight);

	if (button1)
	{
		painter.setBrush(Qt::blue);
	}
	else
	{
		painter.setBrush(Qt::white);
	}

	painter.drawRect(rectL1);

	painter.setBrush(Qt::NoBrush);

	painter.setPen(QPen(Qt::white, 4));

	painter.drawLine(QPoint(rectL2.x(), rect.y() + _fHeight + 20), QPoint(rectL2.x() + (1 - button2) * rectL2.width(), rect.y() + _fHeight + 20));

	painter.setPen(Qt::NoPen);

	// 绘制文字
	painter.setPen(Qt::black);

	QFont _oldFont = painter.font();

	QFont font;
	font.setPointSize(_fHeight / 2);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	painter.drawText(rectL1, Qt::AlignCenter, text1);
	painter.drawText(rectL2, Qt::AlignCenter, text2);

	painter.setFont(_oldFont);

	painter.setPen(Qt::NoPen);

	return;
}

void ControlBoxWidget::DrawCtrlerStatus(QPainter& painter, QRect rect)
{
	painter.setPen(Qt::white);

	QFont _oldFont = painter.font();

	QFont font;
	font.setPointSize(rect.width() / 15);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	if (m_bConnected)
	{
		painter.drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, QString::fromLocal8Bit("控制器：键盘、手柄"));
	}
	else
	{
		painter.drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, QString::fromLocal8Bit("控制器：键盘"));
	}

	painter.setFont(_oldFont);

	painter.setPen(Qt::NoPen);

	return;
}

QPoint ControlBoxWidget::GetEllipse(QPoint out, QPoint in, double R)
{
	double ix, iy, ox, oy;
	ix = in.x();
	iy = in.y();
	ox = out.x();
	oy = out.y();
	double a = abs(ix - ox);
	double b = abs(iy - oy);
	double c = sqrt(pow(a, 2) + pow(b, 2));

	double si = b / c;
	double co = a / c;

	if (c > R)
	{
		c = R;
		a = co * c;
		b = si * c;

		if (ix - ox < 0)
		{
			a = -a;
		}

		if (iy - oy < 0)
		{
			b = -b;
		}

		return QPoint(ox + a, oy + b);
	}

	return in;
}

void ControlBoxWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);						//得到当前控件绘制工具

	Draw(painter);

	return;
}

void ControlBoxWidget::resizeEvent(QResizeEvent* event)
{
	QSize _win = size();	/*!< 屏幕尺寸 */

	float _fWidth = _win.width() / 4.0f;

	setMinimumHeight(_fWidth * 2);

	update();

	return;
}

void ControlBoxWidget::axisLeftXChanged(double value)
{
	m_axisLeftX = value;

	if (m_axisLeftX == 1.5259e-05)
	{
		m_axisLeftX = 0;
	}

	update();

	return;
}

void ControlBoxWidget::axisLeftYChanged(double value)
{
	m_axisLeftY = value;

	if (m_axisLeftY == 1.5259e-05)
	{
		m_axisLeftY = 0;
	}

	update();

	return;
}

void ControlBoxWidget::axisRightXChanged(double value)
{
	m_axisRightX = value;

	if (m_axisRightX == 1.5259e-05)
	{
		m_axisRightX = 0;
	}

	update();

	return;
}

void ControlBoxWidget::axisRightYChanged(double value)
{
	m_axisRightY = value;

	if (m_axisRightY == 1.5259e-05)
	{
		m_axisRightY = 0;
	}

	update();

	return;
}

void ControlBoxWidget::buttonAChanged(bool value)
{
	m_buttonA = value;

	update();

	return;
}

void ControlBoxWidget::buttonBChanged(bool value)
{
	m_buttonB = value;

	update();

	return;
}

void ControlBoxWidget::buttonCenterChanged(bool value)
{
	m_buttonCenter = value;

	update();

	return;
}

void ControlBoxWidget::buttonDownChanged(bool value)
{
	m_buttonDown = value;

	update();

	return;
}

void ControlBoxWidget::buttonGuideChanged(bool value)
{
	m_buttonGuide = value;

	update();

	return;
}

void ControlBoxWidget::buttonL1Changed(bool value)
{
	m_buttonL1 = value;

	update();

	return;
}

void ControlBoxWidget::buttonL2Changed(double value)
{
	m_buttonL2 = value;

	update();

	return;
}

void ControlBoxWidget::buttonL3Changed(bool value)
{
	m_buttonL3 = value;

	update();

	return;
}

void ControlBoxWidget::buttonLeftChanged(bool value)
{
	m_buttonLeft = value;

	update();

	return;
}

void ControlBoxWidget::buttonR1Changed(bool value)
{
	m_buttonR1 = value;

	update();

	return;
}

void ControlBoxWidget::buttonR2Changed(double value)
{
	m_buttonR2 = value;

	update();

	return;
}

void ControlBoxWidget::buttonR3Changed(bool value)
{
	m_buttonR3 = value;

	update();

	return;
}

void ControlBoxWidget::buttonRightChanged(bool value)
{
	m_buttonRight = value;

	update();

	return;
}

void ControlBoxWidget::buttonSelectChanged(bool value)
{
	m_buttonSelect = value;

	update();

	return;
}

void ControlBoxWidget::buttonStartChanged(bool value)
{
	m_buttonStart = value;

	update();

	return;
}

void ControlBoxWidget::buttonUpChanged(bool value)
{
	m_buttonUp = value;

	update();

	return;
}

void ControlBoxWidget::buttonXChanged(bool value)
{
	m_buttonX = value;

	update();

	return;
}

void ControlBoxWidget::buttonYChanged(bool value)
{
	m_buttonY = value;

	update();

	return;
}

void ControlBoxWidget::connectedChanged(bool value)
{
	m_bConnected = value;

	return;
}
