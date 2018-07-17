/****************************************************************************
** Meta object code from reading C++ file 'dialogshapemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AQRVison/dialogshapemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogshapemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogShapeModel_t {
    QByteArrayData data[13];
    char stringdata0[285];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogShapeModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogShapeModel_t qt_meta_stringdata_DialogShapeModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DialogShapeModel"
QT_MOC_LITERAL(1, 17, 17), // "ClickButtonPicOne"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 27), // "ClickButtonCreateShapeModel"
QT_MOC_LITERAL(4, 64, 21), // "on_listView_activated"
QT_MOC_LITERAL(5, 86, 5), // "index"
QT_MOC_LITERAL(6, 92, 28), // "on_pushButton_delete_clicked"
QT_MOC_LITERAL(7, 121, 26), // "on_pushButton_name_clicked"
QT_MOC_LITERAL(8, 148, 25), // "on_listView_doubleClicked"
QT_MOC_LITERAL(9, 174, 28), // "on_pushButtonSnapOne_clicked"
QT_MOC_LITERAL(10, 203, 27), // "on_combo_ShangStd_activated"
QT_MOC_LITERAL(11, 231, 23), // "on_combo_Type_activated"
QT_MOC_LITERAL(12, 255, 29) // "on_pushButton_confirm_clicked"

    },
    "DialogShapeModel\0ClickButtonPicOne\0\0"
    "ClickButtonCreateShapeModel\0"
    "on_listView_activated\0index\0"
    "on_pushButton_delete_clicked\0"
    "on_pushButton_name_clicked\0"
    "on_listView_doubleClicked\0"
    "on_pushButtonSnapOne_clicked\0"
    "on_combo_ShangStd_activated\0"
    "on_combo_Type_activated\0"
    "on_pushButton_confirm_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogShapeModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    1,   75,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void DialogShapeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogShapeModel *_t = static_cast<DialogShapeModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->ClickButtonPicOne();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->ClickButtonCreateShapeModel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: _t->on_listView_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_delete_clicked(); break;
        case 4: _t->on_pushButton_name_clicked(); break;
        case 5: _t->on_listView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_pushButtonSnapOne_clicked(); break;
        case 7: _t->on_combo_ShangStd_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_combo_Type_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_confirm_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject DialogShapeModel::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogShapeModel.data,
      qt_meta_data_DialogShapeModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogShapeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogShapeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogShapeModel.stringdata0))
        return static_cast<void*>(const_cast< DialogShapeModel*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogShapeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
