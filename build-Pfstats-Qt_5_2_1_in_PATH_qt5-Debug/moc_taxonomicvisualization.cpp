/****************************************************************************
** Meta object code from reading C++ file 'taxonomicvisualization.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Pfstats/taxonomicvisualization.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taxonomicvisualization.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TaxonomicVisualization_t {
    QByteArrayData data[13];
    char stringdata[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TaxonomicVisualization_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TaxonomicVisualization_t qt_meta_stringdata_TaxonomicVisualization = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 20),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 7),
QT_MOC_LITERAL(4, 53, 20),
QT_MOC_LITERAL(5, 74, 20),
QT_MOC_LITERAL(6, 95, 20),
QT_MOC_LITERAL(7, 116, 28),
QT_MOC_LITERAL(8, 145, 29),
QT_MOC_LITERAL(9, 175, 5),
QT_MOC_LITERAL(10, 181, 33),
QT_MOC_LITERAL(11, 215, 16),
QT_MOC_LITERAL(12, 232, 4)
    },
    "TaxonomicVisualization\0on_radioSun1_clicked\0"
    "\0checked\0on_radioSun2_clicked\0"
    "on_radioSun3_clicked\0on_radioSun4_clicked\0"
    "on_cmdSunburstFilter_clicked\0"
    "on_cmbSunburstTaxon_activated\0index\0"
    "on_lstSunburstTaxon_itemActivated\0"
    "QListWidgetItem*\0item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaxonomicVisualization[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08,
       4,    1,   52,    2, 0x08,
       5,    1,   55,    2, 0x08,
       6,    1,   58,    2, 0x08,
       7,    0,   61,    2, 0x08,
       8,    1,   62,    2, 0x08,
      10,    1,   65,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void TaxonomicVisualization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaxonomicVisualization *_t = static_cast<TaxonomicVisualization *>(_o);
        switch (_id) {
        case 0: _t->on_radioSun1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_radioSun2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_radioSun3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_radioSun4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_cmdSunburstFilter_clicked(); break;
        case 5: _t->on_cmbSunburstTaxon_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_lstSunburstTaxon_itemActivated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TaxonomicVisualization::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TaxonomicVisualization.data,
      qt_meta_data_TaxonomicVisualization,  qt_static_metacall, 0, 0}
};


const QMetaObject *TaxonomicVisualization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaxonomicVisualization::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TaxonomicVisualization.stringdata))
        return static_cast<void*>(const_cast< TaxonomicVisualization*>(this));
    return QDialog::qt_metacast(_clname);
}

int TaxonomicVisualization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
