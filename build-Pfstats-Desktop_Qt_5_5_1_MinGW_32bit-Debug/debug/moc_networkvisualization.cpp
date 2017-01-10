/****************************************************************************
** Meta object code from reading C++ file 'networkvisualization.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Devloping_Pfstats/Pfstats/networkvisualization.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkvisualization.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetworkVisualization_t {
    QByteArrayData data[8];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkVisualization_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkVisualization_t qt_meta_stringdata_NetworkVisualization = {
    {
QT_MOC_LITERAL(0, 0, 20), // "NetworkVisualization"
QT_MOC_LITERAL(1, 21, 20), // "on_cmdReload_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 34), // "on_chkHideAntiCorrelations_cl..."
QT_MOC_LITERAL(4, 78, 7), // "checked"
QT_MOC_LITERAL(5, 86, 23), // "on_chkScaleHubs_clicked"
QT_MOC_LITERAL(6, 110, 30), // "on_chkCommunitiesColor_clicked"
QT_MOC_LITERAL(7, 141, 29) // "on_chkScaleEdgesScore_clicked"

    },
    "NetworkVisualization\0on_cmdReload_clicked\0"
    "\0on_chkHideAntiCorrelations_clicked\0"
    "checked\0on_chkScaleHubs_clicked\0"
    "on_chkCommunitiesColor_clicked\0"
    "on_chkScaleEdgesScore_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkVisualization[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void NetworkVisualization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkVisualization *_t = static_cast<NetworkVisualization *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cmdReload_clicked(); break;
        case 1: _t->on_chkHideAntiCorrelations_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_chkScaleHubs_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_chkCommunitiesColor_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_chkScaleEdgesScore_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NetworkVisualization::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetworkVisualization.data,
      qt_meta_data_NetworkVisualization,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetworkVisualization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkVisualization::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkVisualization.stringdata0))
        return static_cast<void*>(const_cast< NetworkVisualization*>(this));
    return QDialog::qt_metacast(_clname);
}

int NetworkVisualization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
