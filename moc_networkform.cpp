/****************************************************************************
** Meta object code from reading C++ file 'networkform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "networkform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetworkForm_t {
    QByteArrayData data[10];
    char stringdata[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkForm_t qt_meta_stringdata_NetworkForm = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 16),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 15),
QT_MOC_LITERAL(4, 46, 16),
QT_MOC_LITERAL(5, 63, 18),
QT_MOC_LITERAL(6, 82, 18),
QT_MOC_LITERAL(7, 101, 22),
QT_MOC_LITERAL(8, 124, 4),
QT_MOC_LITERAL(9, 129, 9)
    },
    "NetworkForm\0on_mPrev_clicked\0\0"
    "on_home_clicked\0on_mNext_clicked\0"
    "on_connect_clicked\0changePasswordEdit\0"
    "changeBackPasswordEdit\0test\0cPassword"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    2,   60,    2, 0x08 /* Private */,
       9,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void NetworkForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkForm *_t = static_cast<NetworkForm *>(_o);
        switch (_id) {
        case 0: _t->on_mPrev_clicked(); break;
        case 1: _t->on_home_clicked(); break;
        case 2: _t->on_mNext_clicked(); break;
        case 3: _t->on_connect_clicked(); break;
        case 4: _t->changePasswordEdit(); break;
        case 5: _t->changeBackPasswordEdit(); break;
        case 6: _t->test((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->cPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NetworkForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NetworkForm.data,
      qt_meta_data_NetworkForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *NetworkForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkForm.stringdata))
        return static_cast<void*>(const_cast< NetworkForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int NetworkForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
