/****************************************************************************
** Meta object code from reading C++ file 'Net.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/Net.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Net.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Net_t {
    QByteArrayData data[14];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Net_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Net_t qt_meta_stringdata_Net = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Net"
QT_MOC_LITERAL(1, 4, 11), // "connectFail"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 10), // "handFinish"
QT_MOC_LITERAL(4, 28, 12), // "underpanMove"
QT_MOC_LITERAL(5, 41, 6), // "speedL"
QT_MOC_LITERAL(6, 48, 6), // "speedR"
QT_MOC_LITERAL(7, 55, 13), // "underpanSpray"
QT_MOC_LITERAL(8, 69, 7), // "isSpray"
QT_MOC_LITERAL(9, 77, 10), // "cameraCtrl"
QT_MOC_LITERAL(10, 88, 6), // "camera"
QT_MOC_LITERAL(11, 95, 10), // "onReadData"
QT_MOC_LITERAL(12, 106, 11), // "onReadError"
QT_MOC_LITERAL(13, 118, 28) // "QAbstractSocket::SocketError"

    },
    "Net\0connectFail\0\0handFinish\0underpanMove\0"
    "speedL\0speedR\0underpanSpray\0isSpray\0"
    "cameraCtrl\0camera\0onReadData\0onReadError\0"
    "QAbstractSocket::SocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Net[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    2,   51,    2, 0x06 /* Public */,
       7,    1,   56,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   62,    2, 0x08 /* Private */,
      12,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,

       0        // eod
};

void Net::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Net *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectFail(); break;
        case 1: _t->handFinish(); break;
        case 2: _t->underpanMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->underpanSpray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->cameraCtrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onReadData(); break;
        case 6: _t->onReadError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Net::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Net::connectFail)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Net::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Net::handFinish)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Net::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Net::underpanMove)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Net::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Net::underpanSpray)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Net::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Net::cameraCtrl)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Net::staticMetaObject = { {
    &QTcpSocket::staticMetaObject,
    qt_meta_stringdata_Net.data,
    qt_meta_data_Net,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Net::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Net::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Net.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int Net::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Net::connectFail()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Net::handFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Net::underpanMove(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Net::underpanSpray(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Net::cameraCtrl(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
