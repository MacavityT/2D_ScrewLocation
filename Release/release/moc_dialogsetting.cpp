/****************************************************************************
** Meta object code from reading C++ file 'dialogsetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AQRVison/dialogsetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogsetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogSetting_t {
    QByteArrayData data[8];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogSetting_t qt_meta_stringdata_DialogSetting = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DialogSetting"
QT_MOC_LITERAL(1, 14, 22), // "signal_setupDeviceData"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 14), // "slot_read_data"
QT_MOC_LITERAL(4, 53, 25), // "on_TcpAddress_textChanged"
QT_MOC_LITERAL(5, 79, 4), // "arg1"
QT_MOC_LITERAL(6, 84, 24), // "on_TcpServer_textChanged"
QT_MOC_LITERAL(7, 109, 27) // "on_HeartBeatControl_clicked"

    },
    "DialogSetting\0signal_setupDeviceData\0"
    "\0slot_read_data\0on_TcpAddress_textChanged\0"
    "arg1\0on_TcpServer_textChanged\0"
    "on_HeartBeatControl_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    5,   50,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void DialogSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogSetting *_t = static_cast<DialogSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_setupDeviceData((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 1: _t->slot_read_data((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 2: _t->on_TcpAddress_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_TcpServer_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_HeartBeatControl_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogSetting::*_t)(float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogSetting::signal_setupDeviceData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DialogSetting::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogSetting.data,
      qt_meta_data_DialogSetting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogSetting.stringdata0))
        return static_cast<void*>(const_cast< DialogSetting*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DialogSetting::signal_setupDeviceData(float _t1, float _t2, float _t3, float _t4, float _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
