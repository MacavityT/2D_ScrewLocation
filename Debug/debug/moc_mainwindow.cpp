/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AQRVison0830/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "signal_setupDeviceData"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "x_coor"
QT_MOC_LITERAL(4, 42, 6), // "y_coor"
QT_MOC_LITERAL(5, 49, 8), // "complete"
QT_MOC_LITERAL(6, 58, 9), // "heartbeat"
QT_MOC_LITERAL(7, 68, 7), // "reserve"
QT_MOC_LITERAL(8, 76, 31), // "signal_heartbeat_sender_control"
QT_MOC_LITERAL(9, 108, 18), // "modbus_tcp_server*"
QT_MOC_LITERAL(10, 127, 12), // "m_tcpip_slot"
QT_MOC_LITERAL(11, 140, 3), // "mes"
QT_MOC_LITERAL(12, 144, 14), // "slot_read_data"
QT_MOC_LITERAL(13, 159, 11), // "screwdriver"
QT_MOC_LITERAL(14, 171, 5), // "screw"
QT_MOC_LITERAL(15, 177, 6), // "enable"
QT_MOC_LITERAL(16, 184, 7), // "receive"
QT_MOC_LITERAL(17, 192, 26), // "slot_connect_button_status"
QT_MOC_LITERAL(18, 219, 9), // "connected"
QT_MOC_LITERAL(19, 229, 29), // "on_pushButton_Connect_clicked"
QT_MOC_LITERAL(20, 259, 15), // "pushButton_Snap"
QT_MOC_LITERAL(21, 275, 12), // "on_menuParam"
QT_MOC_LITERAL(22, 288, 17), // "on_menuShapeModel"
QT_MOC_LITERAL(23, 306, 30), // "on_pushButton_TestItem_clicked"
QT_MOC_LITERAL(24, 337, 27), // "on_pushButton_Start_clicked"
QT_MOC_LITERAL(25, 365, 26) // "on_pushButton_Stop_clicked"

    },
    "MainWindow\0signal_setupDeviceData\0\0"
    "x_coor\0y_coor\0complete\0heartbeat\0"
    "reserve\0signal_heartbeat_sender_control\0"
    "modbus_tcp_server*\0m_tcpip_slot\0mes\0"
    "slot_read_data\0screwdriver\0screw\0"
    "enable\0receive\0slot_connect_button_status\0"
    "connected\0on_pushButton_Connect_clicked\0"
    "pushButton_Snap\0on_menuParam\0"
    "on_menuShapeModel\0on_pushButton_TestItem_clicked\0"
    "on_pushButton_Start_clicked\0"
    "on_pushButton_Stop_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   74,    2, 0x06 /* Public */,
       8,    1,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   88,    2, 0x0a /* Public */,
      12,    5,   91,    2, 0x0a /* Public */,
      17,    1,  102,    2, 0x0a /* Public */,
      19,    0,  105,    2, 0x08 /* Private */,
      20,    0,  106,    2, 0x08 /* Private */,
      21,    0,  107,    2, 0x08 /* Private */,
      22,    0,  108,    2, 0x08 /* Private */,
      23,    0,  109,    2, 0x08 /* Private */,
      24,    0,  110,    2, 0x08 /* Private */,
      25,    0,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9,    2,

 // slots: parameters
    QMetaType::Int, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   13,   14,   15,   16,    7,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_setupDeviceData((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 1: _t->signal_heartbeat_sender_control((*reinterpret_cast< modbus_tcp_server*(*)>(_a[1]))); break;
        case 2: { int _r = _t->m_tcpip_slot((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: _t->slot_read_data((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 4: _t->slot_connect_button_status((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_Connect_clicked(); break;
        case 6: _t->pushButton_Snap(); break;
        case 7: _t->on_menuParam(); break;
        case 8: _t->on_menuShapeModel(); break;
        case 9: _t->on_pushButton_TestItem_clicked(); break;
        case 10: _t->on_pushButton_Start_clicked(); break;
        case 11: _t->on_pushButton_Stop_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< modbus_tcp_server* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signal_setupDeviceData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(modbus_tcp_server * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signal_heartbeat_sender_control)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signal_setupDeviceData(float _t1, float _t2, float _t3, float _t4, float _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::signal_heartbeat_sender_control(modbus_tcp_server * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
