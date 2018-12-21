/****************************************************************************
** Meta object code from reading C++ file 'datetimeform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "datetimeform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datetimeform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DateTimeForm_t {
    QByteArrayData data[14];
    char stringdata[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DateTimeForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DateTimeForm_t qt_meta_stringdata_DateTimeForm = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 15),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 17),
QT_MOC_LITERAL(4, 48, 17),
QT_MOC_LITERAL(5, 66, 18),
QT_MOC_LITERAL(6, 85, 17),
QT_MOC_LITERAL(7, 103, 20),
QT_MOC_LITERAL(8, 124, 20),
QT_MOC_LITERAL(9, 145, 20),
QT_MOC_LITERAL(10, 166, 20),
QT_MOC_LITERAL(11, 187, 18),
QT_MOC_LITERAL(12, 206, 17),
QT_MOC_LITERAL(13, 224, 15)
    },
    "DateTimeForm\0on_home_clicked\0\0"
    "on_gonext_clicked\0on_goPrev_clicked\0"
    "on_mRightT_clicked\0on_mLeftT_clicked\0"
    "on_increaseT_clicked\0on_decreaseT_clicked\0"
    "on_increaseC_clicked\0on_decreaseC_clicked\0"
    "on_mRightC_clicked\0on_mLeftC_clicked\0"
    "on_save_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DateTimeForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DateTimeForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DateTimeForm *_t = static_cast<DateTimeForm *>(_o);
        switch (_id) {
        case 0: _t->on_home_clicked(); break;
        case 1: _t->on_gonext_clicked(); break;
        case 2: _t->on_goPrev_clicked(); break;
        case 3: _t->on_mRightT_clicked(); break;
        case 4: _t->on_mLeftT_clicked(); break;
        case 5: _t->on_increaseT_clicked(); break;
        case 6: _t->on_decreaseT_clicked(); break;
        case 7: _t->on_increaseC_clicked(); break;
        case 8: _t->on_decreaseC_clicked(); break;
        case 9: _t->on_mRightC_clicked(); break;
        case 10: _t->on_mLeftC_clicked(); break;
        case 11: _t->on_save_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DateTimeForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DateTimeForm.data,
      qt_meta_data_DateTimeForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *DateTimeForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DateTimeForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateTimeForm.stringdata))
        return static_cast<void*>(const_cast< DateTimeForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int DateTimeForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
