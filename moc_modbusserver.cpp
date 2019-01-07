/****************************************************************************
** Meta object code from reading C++ file 'modbusserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modbusserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbusserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModbusServer_t {
    QByteArrayData data[18];
    char stringdata[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModbusServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModbusServer_t qt_meta_stringdata_ModbusServer = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 7),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 3),
QT_MOC_LITERAL(4, 26, 13),
QT_MOC_LITERAL(5, 40, 13),
QT_MOC_LITERAL(6, 54, 9),
QT_MOC_LITERAL(7, 64, 11),
QT_MOC_LITERAL(8, 76, 4),
QT_MOC_LITERAL(9, 81, 23),
QT_MOC_LITERAL(10, 105, 14),
QT_MOC_LITERAL(11, 120, 3),
QT_MOC_LITERAL(12, 124, 23),
QT_MOC_LITERAL(13, 148, 14),
QT_MOC_LITERAL(14, 163, 8),
QT_MOC_LITERAL(15, 172, 5),
QT_MOC_LITERAL(16, 178, 7),
QT_MOC_LITERAL(17, 186, 14)
    },
    "ModbusServer\0sendMsg\0\0msg\0newConnection\0"
    "readAvailable\0parseData\0QByteArray*\0"
    "data\0read_multiple_registers\0"
    "modbusRequest*\0req\0write_multiple_register\0"
    "updateRegister\0position\0value\0address\0"
    "deleteRegister"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModbusServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   72,    2, 0x0a /* Public */,
       5,    0,   73,    2, 0x0a /* Public */,
       6,    1,   74,    2, 0x0a /* Public */,
       9,    2,   77,    2, 0x0a /* Public */,
      12,    2,   82,    2, 0x0a /* Public */,
      13,    2,   87,    2, 0x0a /* Public */,
      13,    2,   92,    2, 0x0a /* Public */,
      13,    2,   97,    2, 0x0a /* Public */,
      13,    2,  102,    2, 0x0a /* Public */,
      17,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 7, 0x80000000 | 7,    8,
    0x80000000 | 7, 0x80000000 | 10, 0x80000000 | 7,   11,    8,
    0x80000000 | 7, 0x80000000 | 10, 0x80000000 | 7,   11,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   16,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   16,   15,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void ModbusServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModbusServer *_t = static_cast<ModbusServer *>(_o);
        switch (_id) {
        case 0: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->newConnection(); break;
        case 2: _t->readAvailable(); break;
        case 3: { QByteArray* _r = _t->parseData((*reinterpret_cast< QByteArray*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray**>(_a[0]) = _r; }  break;
        case 4: { QByteArray* _r = _t->read_multiple_registers((*reinterpret_cast< modbusRequest*(*)>(_a[1])),(*reinterpret_cast< QByteArray*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray**>(_a[0]) = _r; }  break;
        case 5: { QByteArray* _r = _t->write_multiple_register((*reinterpret_cast< modbusRequest*(*)>(_a[1])),(*reinterpret_cast< QByteArray*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray**>(_a[0]) = _r; }  break;
        case 6: _t->updateRegister((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray*(*)>(_a[2]))); break;
        case 7: _t->updateRegister((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->updateRegister((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->updateRegister((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 10: _t->deleteRegister((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModbusServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModbusServer::sendMsg)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ModbusServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModbusServer.data,
      qt_meta_data_ModbusServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *ModbusServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusServer.stringdata))
        return static_cast<void*>(const_cast< ModbusServer*>(this));
    return QObject::qt_metacast(_clname);
}

int ModbusServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ModbusServer::sendMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
