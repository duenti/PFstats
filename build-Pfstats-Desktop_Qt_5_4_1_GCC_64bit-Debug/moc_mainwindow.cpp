/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Pfstats/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "inputAlignment_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "fetchPFAM_triggered"
QT_MOC_LITERAL(4, 57, 25), // "exportAlignment_triggered"
QT_MOC_LITERAL(5, 83, 25), // "on_cmdStartWizard_clicked"
QT_MOC_LITERAL(6, 109, 18), // "on_cmdMain_clicked"
QT_MOC_LITERAL(7, 128, 18), // "on_cmdBack_clicked"
QT_MOC_LITERAL(8, 147, 21), // "on_cmdAdvance_clicked"
QT_MOC_LITERAL(9, 169, 18), // "on_cmdOpen_clicked"
QT_MOC_LITERAL(10, 188, 19), // "on_cmdFetch_clicked"
QT_MOC_LITERAL(11, 208, 25), // "on_cmdApplyFilter_clicked"
QT_MOC_LITERAL(12, 234, 22), // "on_cmdFetchPDB_clicked"
QT_MOC_LITERAL(13, 257, 25), // "on_cmdPDBfromFile_clicked"
QT_MOC_LITERAL(14, 283, 26), // "on_cmdConservation_clicked"
QT_MOC_LITERAL(15, 310, 19), // "on_cmdMinss_clicked"
QT_MOC_LITERAL(16, 330, 23) // "on_cmdGraphPath_clicked"

    },
    "MainWindow\0inputAlignment_triggered\0"
    "\0fetchPFAM_triggered\0exportAlignment_triggered\0"
    "on_cmdStartWizard_clicked\0on_cmdMain_clicked\0"
    "on_cmdBack_clicked\0on_cmdAdvance_clicked\0"
    "on_cmdOpen_clicked\0on_cmdFetch_clicked\0"
    "on_cmdApplyFilter_clicked\0"
    "on_cmdFetchPDB_clicked\0on_cmdPDBfromFile_clicked\0"
    "on_cmdConservation_clicked\0"
    "on_cmdMinss_clicked\0on_cmdGraphPath_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->inputAlignment_triggered(); break;
        case 1: _t->fetchPFAM_triggered(); break;
        case 2: _t->exportAlignment_triggered(); break;
        case 3: _t->on_cmdStartWizard_clicked(); break;
        case 4: _t->on_cmdMain_clicked(); break;
        case 5: _t->on_cmdBack_clicked(); break;
        case 6: _t->on_cmdAdvance_clicked(); break;
        case 7: _t->on_cmdOpen_clicked(); break;
        case 8: _t->on_cmdFetch_clicked(); break;
        case 9: _t->on_cmdApplyFilter_clicked(); break;
        case 10: _t->on_cmdFetchPDB_clicked(); break;
        case 11: _t->on_cmdPDBfromFile_clicked(); break;
        case 12: _t->on_cmdConservation_clicked(); break;
        case 13: _t->on_cmdMinss_clicked(); break;
        case 14: _t->on_cmdGraphPath_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
