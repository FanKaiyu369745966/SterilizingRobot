/****************************************************************************
** Meta object code from reading C++ file 'SerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/SerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialPort_t {
    QByteArrayData data[17];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPort_t qt_meta_stringdata_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialPort"
QT_MOC_LITERAL(1, 11, 20), // "openSerialPortResult"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "bResult"
QT_MOC_LITERAL(4, 41, 13), // "underpanState"
QT_MOC_LITERAL(5, 55, 5), // "spray"
QT_MOC_LITERAL(6, 61, 8), // "electric"
QT_MOC_LITERAL(7, 70, 5), // "water"
QT_MOC_LITERAL(8, 76, 5), // "obsta"
QT_MOC_LITERAL(9, 82, 16), // "onSerialPortRecv"
QT_MOC_LITERAL(10, 99, 16), // "onOpenSerialPort"
QT_MOC_LITERAL(11, 116, 3), // "com"
QT_MOC_LITERAL(12, 120, 4), // "baud"
QT_MOC_LITERAL(13, 125, 7), // "databit"
QT_MOC_LITERAL(14, 133, 7), // "stopbit"
QT_MOC_LITERAL(15, 141, 16), // "onSendSerialPort"
QT_MOC_LITERAL(16, 158, 4) // "data"

    },
    "SerialPort\0openSerialPortResult\0\0"
    "bResult\0underpanState\0spray\0electric\0"
    "water\0obsta\0onSerialPortRecv\0"
    "onOpenSerialPort\0com\0baud\0databit\0"
    "stopbit\0onSendSerialPort\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    4,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   51,    2, 0x0a /* Public */,
      10,    4,   52,    2, 0x0a /* Public */,
      15,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QByteArray,   16,

       0        // eod
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openSerialPortResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->underpanState((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->onSerialPortRecv(); break;
        case 3: _t->onOpenSerialPort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->onSendSerialPort((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialPort::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::openSerialPortResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialPort::*)(bool , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialPort::underpanState)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialPort::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SerialPort.data,
    qt_meta_data_SerialPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SerialPort::openSerialPortResult(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialPort::underpanState(bool _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
