/****************************************************************************
** Meta object code from reading C++ file 'modbus_tcp_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AQRVison/modbus_tcp_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbus_tcp_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_modbus_tcp_server_t {
    QByteArrayData data[25];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_modbus_tcp_server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_modbus_tcp_server_t qt_meta_stringdata_modbus_tcp_server = {
    {
QT_MOC_LITERAL(0, 0, 17), // "modbus_tcp_server"
QT_MOC_LITERAL(1, 18, 28), // "signal_connect_button_status"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 9), // "connected"
QT_MOC_LITERAL(4, 58, 16), // "signal_read_data"
QT_MOC_LITERAL(5, 75, 11), // "screwdriver"
QT_MOC_LITERAL(6, 87, 5), // "screw"
QT_MOC_LITERAL(7, 93, 6), // "enable"
QT_MOC_LITERAL(8, 100, 7), // "receive"
QT_MOC_LITERAL(9, 108, 7), // "reserve"
QT_MOC_LITERAL(10, 116, 13), // "updateWidgets"
QT_MOC_LITERAL(11, 130, 29), // "QModbusDataUnit::RegisterType"
QT_MOC_LITERAL(12, 160, 5), // "table"
QT_MOC_LITERAL(13, 166, 7), // "address"
QT_MOC_LITERAL(14, 174, 4), // "size"
QT_MOC_LITERAL(15, 179, 14), // "onStateChanged"
QT_MOC_LITERAL(16, 194, 5), // "state"
QT_MOC_LITERAL(17, 200, 17), // "handleDeviceError"
QT_MOC_LITERAL(18, 218, 20), // "QModbusDevice::Error"
QT_MOC_LITERAL(19, 239, 8), // "newError"
QT_MOC_LITERAL(20, 248, 15), // "setupDeviceData"
QT_MOC_LITERAL(21, 264, 6), // "x_coor"
QT_MOC_LITERAL(22, 271, 6), // "y_coor"
QT_MOC_LITERAL(23, 278, 8), // "complete"
QT_MOC_LITERAL(24, 287, 9) // "heartbeat"

    },
    "modbus_tcp_server\0signal_connect_button_status\0"
    "\0connected\0signal_read_data\0screwdriver\0"
    "screw\0enable\0receive\0reserve\0updateWidgets\0"
    "QModbusDataUnit::RegisterType\0table\0"
    "address\0size\0onStateChanged\0state\0"
    "handleDeviceError\0QModbusDevice::Error\0"
    "newError\0setupDeviceData\0x_coor\0y_coor\0"
    "complete\0heartbeat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_modbus_tcp_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    5,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    3,   58,    2, 0x08 /* Private */,
      15,    1,   65,    2, 0x08 /* Private */,
      17,    1,   68,    2, 0x08 /* Private */,
      20,    5,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    5,    6,    7,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   21,   22,   23,   24,    9,

       0        // eod
};

void modbus_tcp_server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        modbus_tcp_server *_t = static_cast<modbus_tcp_server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_connect_button_status((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->signal_read_data((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 2: _t->updateWidgets((*reinterpret_cast< QModbusDataUnit::RegisterType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->onStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->handleDeviceError((*reinterpret_cast< QModbusDevice::Error(*)>(_a[1]))); break;
        case 5: { int _r = _t->setupDeviceData((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QModbusDataUnit::RegisterType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (modbus_tcp_server::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&modbus_tcp_server::signal_connect_button_status)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (modbus_tcp_server::*_t)(float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&modbus_tcp_server::signal_read_data)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject modbus_tcp_server::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_modbus_tcp_server.data,
      qt_meta_data_modbus_tcp_server,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *modbus_tcp_server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *modbus_tcp_server::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_modbus_tcp_server.stringdata0))
        return static_cast<void*>(const_cast< modbus_tcp_server*>(this));
    return QObject::qt_metacast(_clname);
}

int modbus_tcp_server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void modbus_tcp_server::signal_connect_button_status(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void modbus_tcp_server::signal_read_data(float _t1, float _t2, float _t3, float _t4, float _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
