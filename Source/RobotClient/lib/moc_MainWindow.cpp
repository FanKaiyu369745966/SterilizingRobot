/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[30];
    char stringdata0[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "openSerialPort"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "sendSerialPort"
QT_MOC_LITERAL(4, 42, 23), // "on_pushButtonUp_clicked"
QT_MOC_LITERAL(5, 66, 25), // "on_pushButtonDown_clicked"
QT_MOC_LITERAL(6, 92, 25), // "on_pushButtonLeft_clicked"
QT_MOC_LITERAL(7, 118, 26), // "on_pushButtonRight_clicked"
QT_MOC_LITERAL(8, 145, 13), // "onConnectFail"
QT_MOC_LITERAL(9, 159, 12), // "onHandFinish"
QT_MOC_LITERAL(10, 172, 14), // "onUnderpanMove"
QT_MOC_LITERAL(11, 187, 6), // "speedL"
QT_MOC_LITERAL(12, 194, 6), // "speedR"
QT_MOC_LITERAL(13, 201, 15), // "onUnderpanSpray"
QT_MOC_LITERAL(14, 217, 7), // "isSpray"
QT_MOC_LITERAL(15, 225, 15), // "onCameraCapture"
QT_MOC_LITERAL(16, 241, 8), // "fileName"
QT_MOC_LITERAL(17, 250, 10), // "imagesData"
QT_MOC_LITERAL(18, 261, 12), // "onCameraCtrl"
QT_MOC_LITERAL(19, 274, 6), // "camera"
QT_MOC_LITERAL(20, 281, 19), // "onCameraCtrlTimeout"
QT_MOC_LITERAL(21, 301, 22), // "onOpenSerialPortResult"
QT_MOC_LITERAL(22, 324, 7), // "bResult"
QT_MOC_LITERAL(23, 332, 15), // "onUnderpanState"
QT_MOC_LITERAL(24, 348, 5), // "spray"
QT_MOC_LITERAL(25, 354, 8), // "electric"
QT_MOC_LITERAL(26, 363, 5), // "water"
QT_MOC_LITERAL(27, 369, 5), // "obsta"
QT_MOC_LITERAL(28, 375, 29), // "on_pushButtonSetPoint_clicked"
QT_MOC_LITERAL(29, 405, 28) // "on_pushButtonGoPoint_clicked"

    },
    "MainWindow\0openSerialPort\0\0sendSerialPort\0"
    "on_pushButtonUp_clicked\0"
    "on_pushButtonDown_clicked\0"
    "on_pushButtonLeft_clicked\0"
    "on_pushButtonRight_clicked\0onConnectFail\0"
    "onHandFinish\0onUnderpanMove\0speedL\0"
    "speedR\0onUnderpanSpray\0isSpray\0"
    "onCameraCapture\0fileName\0imagesData\0"
    "onCameraCtrl\0camera\0onCameraCtrlTimeout\0"
    "onOpenSerialPortResult\0bResult\0"
    "onUnderpanState\0spray\0electric\0water\0"
    "obsta\0on_pushButtonSetPoint_clicked\0"
    "on_pushButtonGoPoint_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   99,    2, 0x06 /* Public */,
       3,    1,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  111,    2, 0x08 /* Private */,
       5,    0,  112,    2, 0x08 /* Private */,
       6,    0,  113,    2, 0x08 /* Private */,
       7,    0,  114,    2, 0x08 /* Private */,
       8,    0,  115,    2, 0x08 /* Private */,
       9,    0,  116,    2, 0x08 /* Private */,
      10,    2,  117,    2, 0x08 /* Private */,
      13,    1,  122,    2, 0x08 /* Private */,
      15,    2,  125,    2, 0x08 /* Private */,
      18,    1,  130,    2, 0x08 /* Private */,
      20,    0,  133,    2, 0x08 /* Private */,
      21,    1,  134,    2, 0x08 /* Private */,
      23,    4,  137,    2, 0x08 /* Private */,
      28,    0,  146,    2, 0x08 /* Private */,
      29,    0,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   16,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,   24,   25,   26,   27,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openSerialPort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->sendSerialPort((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->on_pushButtonUp_clicked(); break;
        case 3: _t->on_pushButtonDown_clicked(); break;
        case 4: _t->on_pushButtonLeft_clicked(); break;
        case 5: _t->on_pushButtonRight_clicked(); break;
        case 6: _t->onConnectFail(); break;
        case 7: _t->onHandFinish(); break;
        case 8: _t->onUnderpanMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->onUnderpanSpray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onCameraCapture((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 11: _t->onCameraCtrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->onCameraCtrlTimeout(); break;
        case 13: _t->onOpenSerialPortResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->onUnderpanState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 15: _t->on_pushButtonSetPoint_clicked(); break;
        case 16: _t->on_pushButtonGoPoint_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::openSerialPort)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendSerialPort)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::openSerialPort(QString _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendSerialPort(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
