#include "KeyEdit.h"

KeyEdit::KeyEdit(QWidget* parent)
	: QLineEdit(parent)
	, m_key(Qt::Key_unknown)
{
	//ui.setupUi(this);
}

KeyEdit::~KeyEdit()
{
}

void KeyEdit::keyPressEvent(QKeyEvent* event)
{
	event->ignore();

	return;
}

void KeyEdit::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		return;
	}

	m_key = event->key();

	setText(KeyToString((Qt::Key)m_key));

	event->ignore();

	return;
}

QString KeyEdit::KeyToString(Qt::Key key)
{
	switch (key)
	{
	case Qt::Key_Escape:
		return "Esc";
	case Qt::Key_Tab:
		return "Tab";
	case Qt::Key_Backtab:
		break;
	case Qt::Key_Backspace:
		return "Backspace";
	case Qt::Key_Return:
		break;
	case Qt::Key_Enter:
		return "Enter";
	case Qt::Key_Insert:
		return "Ins";
	case Qt::Key_Delete:
		return "Del";
	case Qt::Key_Pause:
		return "PauBre";
	case Qt::Key_Print:
		break;
	case Qt::Key_SysReq:
		break;
	case Qt::Key_Clear:
		break;
	case Qt::Key_Home:
		return "Home";
	case Qt::Key_End:
		return "End";
	case Qt::Key_Left:
		return "Left";
	case Qt::Key_Up:
		return "Up";
	case Qt::Key_Right:
		return "Right";
	case Qt::Key_Down:
		return "Down";
	case Qt::Key_PageUp:
		return "PageUp";
	case Qt::Key_PageDown:
		return "PageDown";
	case Qt::Key_Shift:
		return "Shift";
	case Qt::Key_Control:
		return "Ctrl";
	case Qt::Key_Meta:
		break;
	case Qt::Key_Alt:
		return "Alt";
	case Qt::Key_CapsLock:
		return "CapsLock";
	case Qt::Key_NumLock:
		return "NumLock";
	case Qt::Key_ScrollLock:
		return "ScrollLock";
	case Qt::Key_F1:
		return "F1";
	case Qt::Key_F2:
		return "F2";
	case Qt::Key_F3:
		return "F3";
	case Qt::Key_F4:
		return "F4";
	case Qt::Key_F5:
		return "F5";
	case Qt::Key_F6:
		return "F6";
	case Qt::Key_F7:
		return "F7";
	case Qt::Key_F8:
		return "F8";
	case Qt::Key_F9:
		return "F9";
	case Qt::Key_F10:
		return "F10";
	case Qt::Key_F11:
		return "F11";
	case Qt::Key_F12:
		return "F12";
	case Qt::Key_F13:
		return "F13";
	case Qt::Key_F14:
		return "F14";
	case Qt::Key_F15:
		return "F15";
	case Qt::Key_F16:
		return "F16";
	case Qt::Key_F17:
		return "F17";
	case Qt::Key_F18:
		return "F18";
	case Qt::Key_F19:
		return "F19";
	case Qt::Key_F20:
		return "F20";
	case Qt::Key_F21:
		return "F21";
	case Qt::Key_F22:
		return "F22";
	case Qt::Key_F23:
		return "F23";
	case Qt::Key_F24:
		return "F24";
	case Qt::Key_F25:
		return "F25";
	case Qt::Key_F26:
		return "F26";
	case Qt::Key_F27:
		return "F27";
	case Qt::Key_F28:
		return "F28";
	case Qt::Key_F29:
		return "F29";
	case Qt::Key_F30:
		return "F30";
	case Qt::Key_F31:
		return "F31";
	case Qt::Key_F32:
		return "F32";
	case Qt::Key_F33:
		return "F33";
	case Qt::Key_F34:
		return "F34";
	case Qt::Key_F35:
		return "F35";
	case Qt::Key_Super_L:
		break;
	case Qt::Key_Super_R:
		break;
	case Qt::Key_Menu:
		break;
	case Qt::Key_Hyper_L:
		break;
	case Qt::Key_Hyper_R:
		break;
	case Qt::Key_Help:
		break;
	case Qt::Key_Direction_L:
		break;
	case Qt::Key_Direction_R:
		break;
	case Qt::Key_Space:
		return "Space";
		//case Qt::Key_Any:
		//	break;
	case Qt::Key_Exclam:
		return "!";
	case Qt::Key_QuoteDbl:
		return "\"";
	case Qt::Key_NumberSign:
		return "#";
	case Qt::Key_Dollar:
		return "$";
	case Qt::Key_Percent:
		return "%";
	case Qt::Key_Ampersand:
		return "&";
	case Qt::Key_Apostrophe:
		return "'";
	case Qt::Key_ParenLeft:
		return "(";
	case Qt::Key_ParenRight:
		return ")";
	case Qt::Key_Asterisk:
		return "*";
	case Qt::Key_Plus:
		return "+";
	case Qt::Key_Comma:
		return ",";
	case Qt::Key_Minus:
		return "-";
	case Qt::Key_Period:
		return ".";
	case Qt::Key_Slash:
		return "/";
	case Qt::Key_0:
		return "0";
	case Qt::Key_1:
		return "1";
	case Qt::Key_2:
		return "2";
	case Qt::Key_3:
		return "3";
	case Qt::Key_4:
		return "4";
	case Qt::Key_5:
		return "5";
	case Qt::Key_6:
		return "6";
	case Qt::Key_7:
		return "7";
	case Qt::Key_8:
		return "8";
	case Qt::Key_9:
		return "9";
	case Qt::Key_Colon:
		return ":";
	case Qt::Key_Semicolon:
		return ";";
	case Qt::Key_Less:
		return "<";
	case Qt::Key_Equal:
		return "=";
	case Qt::Key_Greater:
		return ">";
	case Qt::Key_Question:
		return "?";
	case Qt::Key_At:
		return "@";
	case Qt::Key_A:
		return "A";
	case Qt::Key_B:
		return "B";
	case Qt::Key_C:
		return "C";
	case Qt::Key_D:
		return "D";
	case Qt::Key_E:
		return "E";
	case Qt::Key_F:
		return "F";
	case Qt::Key_G:
		return "G";
	case Qt::Key_H:
		return "H";
	case Qt::Key_I:
		return "I";
	case Qt::Key_J:
		return "J";
	case Qt::Key_K:
		return "K";
	case Qt::Key_L:
		return "L";
	case Qt::Key_M:
		return "M";
	case Qt::Key_N:
		return "N";
	case Qt::Key_O:
		return "O";
	case Qt::Key_P:
		return "p";
	case Qt::Key_Q:
		return "Q";
	case Qt::Key_R:
		return "R";
	case Qt::Key_S:
		return "S";
	case Qt::Key_T:
		return "T";
	case Qt::Key_U:
		return "U";
	case Qt::Key_V:
		return "V";
	case Qt::Key_W:
		return "W";
	case Qt::Key_X:
		return "X";
	case Qt::Key_Y:
		return "Y";
	case Qt::Key_Z:
		return "Z";
	case Qt::Key_BracketLeft:
		return "[";
	case Qt::Key_Backslash:
		return "\\";
	case Qt::Key_BracketRight:
		return "]";
	case Qt::Key_AsciiCircum:
		return "^";
	case Qt::Key_Underscore:
		return "_";
	case Qt::Key_QuoteLeft:
		return "`";
	case Qt::Key_BraceLeft:
		return "{";
	case Qt::Key_Bar:
		return "|";
	case Qt::Key_BraceRight:
		return "}";
	case Qt::Key_AsciiTilde:
		return "~";
	case Qt::Key_nobreakspace:
		break;
	case Qt::Key_exclamdown:
		break;
	case Qt::Key_cent:
		break;
	case Qt::Key_sterling:
		break;
	case Qt::Key_currency:
		break;
	case Qt::Key_yen:
		break;
	case Qt::Key_brokenbar:
		break;
	case Qt::Key_section:
		break;
	case Qt::Key_diaeresis:
		break;
	case Qt::Key_copyright:
		break;
	case Qt::Key_ordfeminine:
		break;
	case Qt::Key_guillemotleft:
		break;
	case Qt::Key_notsign:
		break;
	case Qt::Key_hyphen:
		break;
	case Qt::Key_registered:
		break;
	case Qt::Key_macron:
		break;
	case Qt::Key_degree:
		break;
	case Qt::Key_plusminus:
		break;
	case Qt::Key_twosuperior:
		break;
	case Qt::Key_threesuperior:
		break;
	case Qt::Key_acute:
		break;
	case Qt::Key_mu:
		break;
	case Qt::Key_paragraph:
		break;
	case Qt::Key_periodcentered:
		break;
	case Qt::Key_cedilla:
		break;
	case Qt::Key_onesuperior:
		break;
	case Qt::Key_masculine:
		break;
	case Qt::Key_guillemotright:
		break;
	case Qt::Key_onequarter:
		break;
	case Qt::Key_onehalf:
		break;
	case Qt::Key_threequarters:
		break;
	case Qt::Key_questiondown:
		break;
	case Qt::Key_Agrave:
		break;
	case Qt::Key_Aacute:
		break;
	case Qt::Key_Acircumflex:
		break;
	case Qt::Key_Atilde:
		break;
	case Qt::Key_Adiaeresis:
		break;
	case Qt::Key_Aring:
		break;
	case Qt::Key_AE:
		break;
	case Qt::Key_Ccedilla:
		break;
	case Qt::Key_Egrave:
		break;
	case Qt::Key_Eacute:
		break;
	case Qt::Key_Ecircumflex:
		break;
	case Qt::Key_Ediaeresis:
		break;
	case Qt::Key_Igrave:
		break;
	case Qt::Key_Iacute:
		break;
	case Qt::Key_Icircumflex:
		break;
	case Qt::Key_Idiaeresis:
		break;
	case Qt::Key_ETH:
		break;
	case Qt::Key_Ntilde:
		break;
	case Qt::Key_Ograve:
		break;
	case Qt::Key_Oacute:
		break;
	case Qt::Key_Ocircumflex:
		break;
	case Qt::Key_Otilde:
		break;
	case Qt::Key_Odiaeresis:
		break;
	case Qt::Key_multiply:
		break;
	case Qt::Key_Ooblique:
		break;
	case Qt::Key_Ugrave:
		break;
	case Qt::Key_Uacute:
		break;
	case Qt::Key_Ucircumflex:
		break;
	case Qt::Key_Udiaeresis:
		break;
	case Qt::Key_Yacute:
		break;
	case Qt::Key_THORN:
		break;
	case Qt::Key_ssharp:
		break;
	case Qt::Key_division:
		break;
	case Qt::Key_ydiaeresis:
		break;
	case Qt::Key_AltGr:
		break;
	case Qt::Key_Multi_key:
		break;
	case Qt::Key_Codeinput:
		break;
	case Qt::Key_SingleCandidate:
		break;
	case Qt::Key_MultipleCandidate:
		break;
	case Qt::Key_PreviousCandidate:
		break;
	case Qt::Key_Mode_switch:
		break;
	case Qt::Key_Kanji:
		break;
	case Qt::Key_Muhenkan:
		break;
	case Qt::Key_Henkan:
		break;
	case Qt::Key_Romaji:
		break;
	case Qt::Key_Hiragana:
		break;
	case Qt::Key_Katakana:
		break;
	case Qt::Key_Hiragana_Katakana:
		break;
	case Qt::Key_Zenkaku:
		break;
	case Qt::Key_Hankaku:
		break;
	case Qt::Key_Zenkaku_Hankaku:
		break;
	case Qt::Key_Touroku:
		break;
	case Qt::Key_Massyo:
		break;
	case Qt::Key_Kana_Lock:
		break;
	case Qt::Key_Kana_Shift:
		break;
	case Qt::Key_Eisu_Shift:
		break;
	case Qt::Key_Eisu_toggle:
		break;
	case Qt::Key_Hangul:
		break;
	case Qt::Key_Hangul_Start:
		break;
	case Qt::Key_Hangul_End:
		break;
	case Qt::Key_Hangul_Hanja:
		break;
	case Qt::Key_Hangul_Jamo:
		break;
	case Qt::Key_Hangul_Romaja:
		break;
	case Qt::Key_Hangul_Jeonja:
		break;
	case Qt::Key_Hangul_Banja:
		break;
	case Qt::Key_Hangul_PreHanja:
		break;
	case Qt::Key_Hangul_PostHanja:
		break;
	case Qt::Key_Hangul_Special:
		break;
	case Qt::Key_Dead_Grave:
		break;
	case Qt::Key_Dead_Acute:
		break;
	case Qt::Key_Dead_Circumflex:
		break;
	case Qt::Key_Dead_Tilde:
		break;
	case Qt::Key_Dead_Macron:
		break;
	case Qt::Key_Dead_Breve:
		break;
	case Qt::Key_Dead_Abovedot:
		break;
	case Qt::Key_Dead_Diaeresis:
		break;
	case Qt::Key_Dead_Abovering:
		break;
	case Qt::Key_Dead_Doubleacute:
		break;
	case Qt::Key_Dead_Caron:
		break;
	case Qt::Key_Dead_Cedilla:
		break;
	case Qt::Key_Dead_Ogonek:
		break;
	case Qt::Key_Dead_Iota:
		break;
	case Qt::Key_Dead_Voiced_Sound:
		break;
	case Qt::Key_Dead_Semivoiced_Sound:
		break;
	case Qt::Key_Dead_Belowdot:
		break;
	case Qt::Key_Dead_Hook:
		break;
	case Qt::Key_Dead_Horn:
		break;
	case Qt::Key_Dead_Stroke:
		break;
	case Qt::Key_Dead_Abovecomma:
		break;
	case Qt::Key_Dead_Abovereversedcomma:
		break;
	case Qt::Key_Dead_Doublegrave:
		break;
	case Qt::Key_Dead_Belowring:
		break;
	case Qt::Key_Dead_Belowmacron:
		break;
	case Qt::Key_Dead_Belowcircumflex:
		break;
	case Qt::Key_Dead_Belowtilde:
		break;
	case Qt::Key_Dead_Belowbreve:
		break;
	case Qt::Key_Dead_Belowdiaeresis:
		break;
	case Qt::Key_Dead_Invertedbreve:
		break;
	case Qt::Key_Dead_Belowcomma:
		break;
	case Qt::Key_Dead_Currency:
		break;
	case Qt::Key_Dead_a:
		break;
	case Qt::Key_Dead_A:
		break;
	case Qt::Key_Dead_e:
		break;
	case Qt::Key_Dead_E:
		break;
	case Qt::Key_Dead_i:
		break;
	case Qt::Key_Dead_I:
		break;
	case Qt::Key_Dead_o:
		break;
	case Qt::Key_Dead_O:
		break;
	case Qt::Key_Dead_u:
		break;
	case Qt::Key_Dead_U:
		break;
	case Qt::Key_Dead_Small_Schwa:
		break;
	case Qt::Key_Dead_Capital_Schwa:
		break;
	case Qt::Key_Dead_Greek:
		break;
	case Qt::Key_Dead_Lowline:
		break;
	case Qt::Key_Dead_Aboveverticalline:
		break;
	case Qt::Key_Dead_Belowverticalline:
		break;
	case Qt::Key_Dead_Longsolidusoverlay:
		break;
	case Qt::Key_Back:
		break;
	case Qt::Key_Forward:
		break;
	case Qt::Key_Stop:
		break;
	case Qt::Key_Refresh:
		break;
	case Qt::Key_VolumeDown:
		break;
	case Qt::Key_VolumeMute:
		break;
	case Qt::Key_VolumeUp:
		break;
	case Qt::Key_BassBoost:
		break;
	case Qt::Key_BassUp:
		break;
	case Qt::Key_BassDown:
		break;
	case Qt::Key_TrebleUp:
		break;
	case Qt::Key_TrebleDown:
		break;
	case Qt::Key_MediaPlay:
		break;
	case Qt::Key_MediaStop:
		break;
	case Qt::Key_MediaPrevious:
		break;
	case Qt::Key_MediaNext:
		break;
	case Qt::Key_MediaRecord:
		break;
	case Qt::Key_MediaPause:
		break;
	case Qt::Key_MediaTogglePlayPause:
		break;
	case Qt::Key_HomePage:
		break;
	case Qt::Key_Favorites:
		break;
	case Qt::Key_Search:
		break;
	case Qt::Key_Standby:
		break;
	case Qt::Key_OpenUrl:
		break;
	case Qt::Key_LaunchMail:
		break;
	case Qt::Key_LaunchMedia:
		break;
	case Qt::Key_Launch0:
		break;
	case Qt::Key_Launch1:
		break;
	case Qt::Key_Launch2:
		break;
	case Qt::Key_Launch3:
		break;
	case Qt::Key_Launch4:
		break;
	case Qt::Key_Launch5:
		break;
	case Qt::Key_Launch6:
		break;
	case Qt::Key_Launch7:
		break;
	case Qt::Key_Launch8:
		break;
	case Qt::Key_Launch9:
		break;
	case Qt::Key_LaunchA:
		break;
	case Qt::Key_LaunchB:
		break;
	case Qt::Key_LaunchC:
		break;
	case Qt::Key_LaunchD:
		break;
	case Qt::Key_LaunchE:
		break;
	case Qt::Key_LaunchF:
		break;
	case Qt::Key_MonBrightnessUp:
		break;
	case Qt::Key_MonBrightnessDown:
		break;
	case Qt::Key_KeyboardLightOnOff:
		break;
	case Qt::Key_KeyboardBrightnessUp:
		break;
	case Qt::Key_KeyboardBrightnessDown:
		break;
	case Qt::Key_PowerOff:
		break;
	case Qt::Key_WakeUp:
		break;
	case Qt::Key_Eject:
		break;
	case Qt::Key_ScreenSaver:
		break;
	case Qt::Key_WWW:
		break;
	case Qt::Key_Memo:
		break;
	case Qt::Key_LightBulb:
		break;
	case Qt::Key_Shop:
		break;
	case Qt::Key_History:
		break;
	case Qt::Key_AddFavorite:
		break;
	case Qt::Key_HotLinks:
		break;
	case Qt::Key_BrightnessAdjust:
		break;
	case Qt::Key_Finance:
		break;
	case Qt::Key_Community:
		break;
	case Qt::Key_AudioRewind:
		break;
	case Qt::Key_BackForward:
		break;
	case Qt::Key_ApplicationLeft:
		break;
	case Qt::Key_ApplicationRight:
		break;
	case Qt::Key_Book:
		break;
	case Qt::Key_CD:
		break;
	case Qt::Key_Calculator:
		break;
	case Qt::Key_ToDoList:
		break;
	case Qt::Key_ClearGrab:
		break;
	case Qt::Key_Close:
		break;
	case Qt::Key_Copy:
		break;
	case Qt::Key_Cut:
		break;
	case Qt::Key_Display:
		break;
	case Qt::Key_DOS:
		break;
	case Qt::Key_Documents:
		break;
	case Qt::Key_Excel:
		break;
	case Qt::Key_Explorer:
		break;
	case Qt::Key_Game:
		break;
	case Qt::Key_Go:
		break;
	case Qt::Key_iTouch:
		break;
	case Qt::Key_LogOff:
		break;
	case Qt::Key_Market:
		break;
	case Qt::Key_Meeting:
		break;
	case Qt::Key_MenuKB:
		break;
	case Qt::Key_MenuPB:
		break;
	case Qt::Key_MySites:
		break;
	case Qt::Key_News:
		break;
	case Qt::Key_OfficeHome:
		break;
	case Qt::Key_Option:
		break;
	case Qt::Key_Paste:
		break;
	case Qt::Key_Phone:
		break;
	case Qt::Key_Calendar:
		break;
	case Qt::Key_Reply:
		break;
	case Qt::Key_Reload:
		break;
	case Qt::Key_RotateWindows:
		break;
	case Qt::Key_RotationPB:
		break;
	case Qt::Key_RotationKB:
		break;
	case Qt::Key_Save:
		break;
	case Qt::Key_Send:
		break;
	case Qt::Key_Spell:
		break;
	case Qt::Key_SplitScreen:
		break;
	case Qt::Key_Support:
		break;
	case Qt::Key_TaskPane:
		break;
	case Qt::Key_Terminal:
		break;
	case Qt::Key_Tools:
		break;
	case Qt::Key_Travel:
		break;
	case Qt::Key_Video:
		break;
	case Qt::Key_Word:
		break;
	case Qt::Key_Xfer:
		break;
	case Qt::Key_ZoomIn:
		break;
	case Qt::Key_ZoomOut:
		break;
	case Qt::Key_Away:
		break;
	case Qt::Key_Messenger:
		break;
	case Qt::Key_WebCam:
		break;
	case Qt::Key_MailForward:
		break;
	case Qt::Key_Pictures:
		break;
	case Qt::Key_Music:
		break;
	case Qt::Key_Battery:
		break;
	case Qt::Key_Bluetooth:
		break;
	case Qt::Key_WLAN:
		break;
	case Qt::Key_UWB:
		break;
	case Qt::Key_AudioForward:
		break;
	case Qt::Key_AudioRepeat:
		break;
	case Qt::Key_AudioRandomPlay:
		break;
	case Qt::Key_Subtitle:
		break;
	case Qt::Key_AudioCycleTrack:
		break;
	case Qt::Key_Time:
		break;
	case Qt::Key_Hibernate:
		break;
	case Qt::Key_View:
		break;
	case Qt::Key_TopMenu:
		break;
	case Qt::Key_PowerDown:
		break;
	case Qt::Key_Suspend:
		break;
	case Qt::Key_ContrastAdjust:
		break;
	case Qt::Key_LaunchG:
		break;
	case Qt::Key_LaunchH:
		break;
	case Qt::Key_TouchpadToggle:
		break;
	case Qt::Key_TouchpadOn:
		break;
	case Qt::Key_TouchpadOff:
		break;
	case Qt::Key_MicMute:
		break;
	case Qt::Key_Red:
		break;
	case Qt::Key_Green:
		break;
	case Qt::Key_Yellow:
		break;
	case Qt::Key_Blue:
		break;
	case Qt::Key_ChannelUp:
		break;
	case Qt::Key_ChannelDown:
		break;
	case Qt::Key_Guide:
		break;
	case Qt::Key_Info:
		break;
	case Qt::Key_Settings:
		break;
	case Qt::Key_MicVolumeUp:
		break;
	case Qt::Key_MicVolumeDown:
		break;
	case Qt::Key_New:
		break;
	case Qt::Key_Open:
		break;
	case Qt::Key_Find:
		break;
	case Qt::Key_Undo:
		break;
	case Qt::Key_Redo:
		break;
	case Qt::Key_MediaLast:
		break;
	case Qt::Key_Select:
		break;
	case Qt::Key_Yes:
		break;
	case Qt::Key_No:
		break;
	case Qt::Key_Cancel:
		break;
	case Qt::Key_Printer:
		break;
	case Qt::Key_Execute:
		break;
	case Qt::Key_Sleep:
		break;
	case Qt::Key_Play:
		break;
	case Qt::Key_Zoom:
		break;
	case Qt::Key_Exit:
		break;
	case Qt::Key_Context1:
		break;
	case Qt::Key_Context2:
		break;
	case Qt::Key_Context3:
		break;
	case Qt::Key_Context4:
		break;
	case Qt::Key_Call:
		break;
	case Qt::Key_Hangup:
		break;
	case Qt::Key_Flip:
		break;
	case Qt::Key_ToggleCallHangup:
		break;
	case Qt::Key_VoiceDial:
		break;
	case Qt::Key_LastNumberRedial:
		break;
	case Qt::Key_Camera:
		break;
	case Qt::Key_CameraFocus:
		break;
	case Qt::Key_unknown:
		break;
	default:
		break;
	}

	return QString();
}

Qt::Key KeyEdit::StringToKey(QString str)
{
	if (str == "Esc")
	{
		return Qt::Key_Escape;
	}
	if (str == "Tab")
	{
		return Qt::Key_Tab;
	}
	if (str == "Backspace")
	{
		return Qt::Key_Backspace;
	}
	if (str == "Enter")
	{
		return Qt::Key_Enter;
	}
	if (str == "Ins")
	{
		return Qt::Key_Insert;
	}
	if (str == "Del")
	{
		return Qt::Key_Delete;
	}
	if (str == "PauBre")
	{
		return Qt::Key_Pause;
	}
	if (str == "Home")
	{
		return Qt::Key_Home;
	}
	if (str == "End")
	{
		return Qt::Key_End;
	}
	if (str == "Left")
	{
		return Qt::Key_Left;
	}
	if (str == "Up")
	{
		return Qt::Key_Up;
	}
	if (str == "Right")
	{
		return Qt::Key_Right;
	}
	if (str == "Down")
	{
		return Qt::Key_Down;
	}
	if (str == "PageUp")
	{
		return Qt::Key_PageUp;
	}
	if (str == "PageDown")
	{
		return Qt::Key_PageDown;
	}
	if (str == "Shift")
	{
		return Qt::Key_Shift;
	}
	if (str == "Ctrl")
	{
		return Qt::Key_Control;
	}
	if (str == "Alt")
	{
		return Qt::Key_Alt;
	}
	if (str == "CapsLock")
	{
		return Qt::Key_CapsLock;
	}
	if (str == "NumLock")
	{
		return Qt::Key_NumLock;
	}
	if (str == "ScrollLock")
	{
		return Qt::Key_ScrollLock;
	}
	if (str == "F1")
	{
		return Qt::Key_F1;
	}
	if (str == "F2")
	{
		return Qt::Key_F2;
	}
	if (str == "F3")
	{
		return Qt::Key_F3;
	}
	if (str == "F4")
	{
		return Qt::Key_F4;
	}
	if (str == "F5")
	{
		return Qt::Key_F5;
	}
	if (str == "F6")
	{
		return Qt::Key_F6;
	}
	if (str == "F7")
	{
		return Qt::Key_F7;
	}
	if (str == "F8")
	{
		return Qt::Key_F8;
	}
	if (str == "F9")
	{
		return Qt::Key_F9;
	}
	if (str == "F10")
	{
		return Qt::Key_F10;
	}
	if (str == "F11")
	{
		return Qt::Key_F11;
	}
	if (str == "F12")
	{
		return Qt::Key_F12;
	}
	if (str == "F13")
	{
		return Qt::Key_F13;
	}
	if (str == "F14")
	{
		return Qt::Key_F14;
	}
	if (str == "F15")
	{
		return Qt::Key_F15;
	}
	if (str == "F16")
	{
		return Qt::Key_F16;
	}
	if (str == "F17")
	{
		return Qt::Key_F17;
	}
	if (str == "F18")
	{
		return Qt::Key_F18;
	}
	if (str == "F19")
	{
		return Qt::Key_F19;
	}
	if (str == "F20")
	{
		return Qt::Key_F20;
	}
	if (str == "F21")
	{
		return Qt::Key_F21;
	}
	if (str == "F22")
	{
		return Qt::Key_F22;
	}
	if (str == "F23")
	{
		return Qt::Key_F23;
	}
	if (str == "F24")
	{
		return Qt::Key_F24;
	}
	if (str == "F25")
	{
		return Qt::Key_F25;
	}
	if (str == "F26")
	{
		return Qt::Key_F26;
	}
	if (str == "F27")
	{
		return Qt::Key_F27;
	}
	if (str == "F28")
	{
		return Qt::Key_F28;
	}
	if (str == "F29")
	{
		return Qt::Key_F29;
	}
	if (str == "F30")
	{
		return Qt::Key_F30;
	}
	if (str == "F31")
	{
		return Qt::Key_F31;
	}
	if (str == "F32")
	{
		return Qt::Key_F32;
	}
	if (str == "F33")
	{
		return Qt::Key_F33;
	}
	if (str == "F34")
	{
		return Qt::Key_F34;
	}
	if (str == "F35")
	{
		return Qt::Key_F35;
	}
	if (str == "Space")
	{
		return Qt::Key_Space;
	}
	if (str == "!")
	{
		return Qt::Key_Exclam;
	}
	if (str == "\"")
	{
		return Qt::Key_QuoteDbl;
	}
	if (str == "#")
	{
		return Qt::Key_NumberSign;
	}
	if (str == "$")
	{
		return Qt::Key_Dollar;
	}
	if (str == "%")
	{
		return Qt::Key_Percent;
	}
	if (str == "&")
	{
		return Qt::Key_Ampersand;
	}
	if (str == "'")
	{
		return Qt::Key_Apostrophe;
	}
	if (str == "(")
	{
		return Qt::Key_ParenLeft;
	}
	if (str == ")")
	{
		return Qt::Key_ParenRight;
	}
	if (str == "*")
	{
		return Qt::Key_Asterisk;
	}
	if (str == "+")
	{
		return Qt::Key_Plus;
	}
	if (str == ",")
	{
		return Qt::Key_Comma;
	}
	if (str == "-")
	{
		return Qt::Key_Minus;
	}
	if (str == ".")
	{
		return Qt::Key_Period;
	}
	if (str == "/")
	{
		return Qt::Key_Slash;
	}
	if (str == "0")
	{
		return Qt::Key_0;
	}
	if (str == "1")
	{
		return Qt::Key_1;
	}
	if (str == "2")
	{
		return Qt::Key_2;
	}
	if (str == "3")
	{
		return Qt::Key_3;
	}
	if (str == "4")
	{
		return Qt::Key_4;
	}
	if (str == "5")
	{
		return Qt::Key_5;
	}
	if (str == "6")
	{
		return Qt::Key_6;
	}
	if (str == "7")
	{
		return Qt::Key_7;
	}
	if (str == "8")
	{
		return Qt::Key_8;
	}
	if (str == "9")
	{
		return Qt::Key_9;
	}
	if (str == ":")
	{
		return Qt::Key_Colon;
	}
	if (str == ";")
	{
		return Qt::Key_Semicolon;
	}
	if (str == "<")
	{
		return Qt::Key_Less;
	}
	if (str == "=")
	{
		return Qt::Key_Equal;
	}
	if (str == ">")
	{
		return Qt::Key_Greater;
	}
	if (str == "?")
	{
		return Qt::Key_Question;
	}
	if (str == "@")
	{
		return Qt::Key_At;
	}
	if (str == "A")
	{
		return Qt::Key_A;
	}
	if (str == "B")
	{
		return Qt::Key_B;
	}
	if (str == "C")
	{
		return Qt::Key_C;
	}
	if (str == "D")
	{
		return Qt::Key_D;
	}
	if (str == "E")
	{
		return Qt::Key_E;
	}
	if (str == "F")
	{
		return Qt::Key_F;
	}
	if (str == "G")
	{
		return Qt::Key_G;
	}
	if (str == "H")
	{
		return Qt::Key_H;
	}
	if (str == "I")
	{
		return Qt::Key_I;
	}
	if (str == "J")
	{
		return Qt::Key_J;
	}
	if (str == "K")
	{
		return Qt::Key_K;
	}
	if (str == "L")
	{
		return Qt::Key_L;
	}
	if (str == "M")
	{
		return Qt::Key_M;
	}
	if (str == "N")
	{
		return Qt::Key_N;
	}
	if (str == "O")
	{
		return Qt::Key_O;
	}
	if (str == "P")
	{
		return Qt::Key_P;
	}
	if (str == "Q")
	{
		return Qt::Key_Q;
	}
	if (str == "R")
	{
		return Qt::Key_R;
	}
	if (str == "S")
	{
		return Qt::Key_S;
	}
	if (str == "T")
	{
		return Qt::Key_T;
	}
	if (str == "U")
	{
		return Qt::Key_U;
	}
	if (str == "V")
	{
		return Qt::Key_V;
	}
	if (str == "W")
	{
		return Qt::Key_W;
	}
	if (str == "X")
	{
		return Qt::Key_X;
	}
	if (str == "Y")
	{
		return Qt::Key_Y;
	}
	if (str == "Z")
	{
		return Qt::Key_Z;
	}
	if (str == "[")
	{
		return Qt::Key_BracketLeft;
	}
	if (str == "\\")
	{
		return Qt::Key_Backslash;
	}
	if (str == "]")
	{
		return Qt::Key_BracketRight;
	}
	if (str == "^")
	{
		return Qt::Key_AsciiCircum;
	}
	if (str == "_")
	{
		return Qt::Key_Underscore;
	}
	if (str == "`")
	{
		return Qt::Key_QuoteLeft;
	}
	if (str == "{")
	{
		return Qt::Key_BraceLeft;
	}
	if (str == "|")
	{
		return Qt::Key_Bar;
	}
	if (str == "}")
	{
		return Qt::Key_BraceRight;
	}
	if (str == "~")
	{
		return Qt::Key_AsciiTilde;
	}

	return Qt::Key_unknown;
}

void KeyEdit::SetKey(Qt::Key key)
{
	m_key = key;

	setText(KeyToString((Qt::Key)m_key));

	return;
}
