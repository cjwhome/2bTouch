/****************************************************************************
** Meta object code from reading C++ file 'analogform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "analogform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analogform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AnalogForm_t {
    QByteArrayData data[8];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnalogForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnalogForm_t qt_meta_stringdata_AnalogForm = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 16),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 20),
QT_MOC_LITERAL(4, 50, 15),
QT_MOC_LITERAL(5, 66, 15),
QT_MOC_LITERAL(6, 82, 19),
QT_MOC_LITERAL(7, 102, 19)
    },
    "AnalogForm\0on_mNext_clicked\0\0"
    "on_mPrevious_clicked\0on_home_clicked\0"
    "on_save_clicked\0on_increase_clicked\0"
    "on_decrease_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnalogForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AnalogForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnalogForm *_t = static_cast<AnalogForm *>(_o);
        switch (_id) {
        case 0: _t->on_mNext_clicked(); break;
        case 1: _t->on_mPrevious_clicked(); break;
        case 2: _t->on_home_clicked(); break;
        case 3: _t->on_save_clicked(); break;
        case 4: _t->on_increase_clicked(); break;
        case 5: _t->on_decrease_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AnalogForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnalogForm.data,
      qt_meta_data_AnalogForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *AnalogForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalogForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnalogForm.stringdata))
        return static_cast<void*>(const_cast< AnalogForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnalogForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
