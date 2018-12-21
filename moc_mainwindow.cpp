/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 12),
QT_MOC_LITERAL(4, 40, 11),
QT_MOC_LITERAL(5, 52, 5),
QT_MOC_LITERAL(6, 58, 13),
QT_MOC_LITERAL(7, 72, 14),
QT_MOC_LITERAL(8, 87, 12),
QT_MOC_LITERAL(9, 100, 15),
QT_MOC_LITERAL(10, 116, 9),
QT_MOC_LITERAL(11, 126, 4),
QT_MOC_LITERAL(12, 131, 8),
QT_MOC_LITERAL(13, 140, 11),
QT_MOC_LITERAL(14, 152, 28),
QT_MOC_LITERAL(15, 181, 5),
QT_MOC_LITERAL(16, 187, 15),
QT_MOC_LITERAL(17, 203, 13),
QT_MOC_LITERAL(18, 217, 5),
QT_MOC_LITERAL(19, 223, 12),
QT_MOC_LITERAL(20, 236, 14),
QT_MOC_LITERAL(21, 251, 11),
QT_MOC_LITERAL(22, 263, 12),
QT_MOC_LITERAL(23, 276, 17),
QT_MOC_LITERAL(24, 294, 12)
    },
    "MainWindow\0validDataReady\0\0receivedData\0"
    "newDataLine\0dLine\0parseDataLine\0"
    "displayBigPlot\0displayStats\0displaySettings\0"
    "writeData\0data\0readData\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "closeSerialPort\0updateAverage\0value\0"
    "usbTimerTick\0errorTimerTick\0getCpuUsage\0"
    "getFreeSpace\0updateMainDisplay\0"
    "showSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  106,    2, 0x0a /* Public */,
       6,    1,  109,    2, 0x0a /* Public */,
       7,    0,  112,    2, 0x0a /* Public */,
       8,    0,  113,    2, 0x0a /* Public */,
       9,    0,  114,    2, 0x0a /* Public */,
      10,    1,  115,    2, 0x0a /* Public */,
      12,    0,  118,    2, 0x0a /* Public */,
      13,    1,  119,    2, 0x0a /* Public */,
      16,    0,  122,    2, 0x0a /* Public */,
      17,    1,  123,    2, 0x0a /* Public */,
      19,    0,  126,    2, 0x0a /* Public */,
      20,    0,  127,    2, 0x0a /* Public */,
      21,    0,  128,    2, 0x0a /* Public */,
      22,    0,  129,    2, 0x0a /* Public */,
      23,    1,  130,    2, 0x0a /* Public */,
      24,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->validDataReady(); break;
        case 1: _t->receivedData(); break;
        case 2: _t->newDataLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { bool _r = _t->parseDataLine((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->displayBigPlot(); break;
        case 5: _t->displayStats(); break;
        case 6: _t->displaySettings(); break;
        case 7: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 8: _t->readData(); break;
        case 9: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 10: _t->closeSerialPort(); break;
        case 11: _t->updateAverage((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->usbTimerTick(); break;
        case 13: _t->errorTimerTick(); break;
        case 14: { QString _r = _t->getCpuUsage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QString _r = _t->getFreeSpace();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: _t->updateMainDisplay((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 17: _t->showSettings(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::validDataReady)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::receivedData)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::validDataReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::receivedData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
