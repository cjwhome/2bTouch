/****************************************************************************
** Meta object code from reading C++ file 'serialhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serialhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SerialHandler_t {
    QByteArrayData data[17];
    char stringdata[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialHandler_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialHandler_t qt_meta_stringdata_SerialHandler = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 8),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 5),
QT_MOC_LITERAL(4, 30, 13),
QT_MOC_LITERAL(5, 44, 9),
QT_MOC_LITERAL(6, 54, 8),
QT_MOC_LITERAL(7, 63, 3),
QT_MOC_LITERAL(8, 67, 10),
QT_MOC_LITERAL(9, 78, 9),
QT_MOC_LITERAL(10, 88, 1),
QT_MOC_LITERAL(11, 90, 9),
QT_MOC_LITERAL(12, 100, 12),
QT_MOC_LITERAL(13, 113, 8),
QT_MOC_LITERAL(14, 122, 4),
QT_MOC_LITERAL(15, 127, 14),
QT_MOC_LITERAL(16, 142, 13)
    },
    "SerialHandler\0finished\0\0error\0"
    "dataAvailable\0writeSync\0QString*\0dat\0"
    "writeAsync\0writeChar\0c\0dataReady\0"
    "netDataReady\0readData\0data\0updateSettings\0"
    "newConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   74,    2, 0x0a /* Public */,
       8,    1,   77,    2, 0x0a /* Public */,
       9,    1,   80,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x0a /* Public */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Char,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SerialHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialHandler *_t = static_cast<SerialHandler *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error(); break;
        case 2: _t->dataAvailable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->writeSync((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 4: _t->writeAsync((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 5: _t->writeChar((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 6: _t->dataReady(); break;
        case 7: _t->netDataReady(); break;
        case 8: _t->readData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->updateSettings(); break;
        case 10: _t->newConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SerialHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialHandler::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (SerialHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialHandler::error)) {
                *result = 1;
            }
        }
        {
            typedef void (SerialHandler::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialHandler::dataAvailable)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SerialHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialHandler.data,
      qt_meta_data_SerialHandler,  qt_static_metacall, 0, 0}
};


const QMetaObject *SerialHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialHandler.stringdata))
        return static_cast<void*>(const_cast< SerialHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SerialHandler::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SerialHandler::error()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SerialHandler::dataAvailable(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
