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
    QByteArrayData data[71];
    char stringdata[1459];
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
QT_MOC_LITERAL(5, 83, 18), // "Open_XML_triggered"
QT_MOC_LITERAL(6, 102, 20), // "exportAlignment_PFAM"
QT_MOC_LITERAL(7, 123, 19), // "exportAlignment_TXT"
QT_MOC_LITERAL(8, 143, 19), // "exportAlignment_XML"
QT_MOC_LITERAL(9, 163, 13), // "exportFreqTXT"
QT_MOC_LITERAL(10, 177, 13), // "exportFreqCSV"
QT_MOC_LITERAL(11, 191, 13), // "exportFreqXML"
QT_MOC_LITERAL(12, 205, 14), // "exportFreqHTML"
QT_MOC_LITERAL(13, 220, 17), // "exportFreqPercTXT"
QT_MOC_LITERAL(14, 238, 17), // "exportFreqPercCSV"
QT_MOC_LITERAL(15, 256, 17), // "exportFreqPercXML"
QT_MOC_LITERAL(16, 274, 18), // "exportFreqPercHTML"
QT_MOC_LITERAL(17, 293, 16), // "exportConsResTXT"
QT_MOC_LITERAL(18, 310, 16), // "exportConsResXML"
QT_MOC_LITERAL(19, 327, 17), // "exportConsResHTML"
QT_MOC_LITERAL(20, 345, 17), // "exportCorrListTXT"
QT_MOC_LITERAL(21, 363, 17), // "exportCorrListCSV"
QT_MOC_LITERAL(22, 381, 17), // "exportCorrListXML"
QT_MOC_LITERAL(23, 399, 14), // "exportCommsTXT"
QT_MOC_LITERAL(24, 414, 14), // "exportCommsXML"
QT_MOC_LITERAL(25, 429, 22), // "exportCorrTablePercTXT"
QT_MOC_LITERAL(26, 452, 22), // "exportCorrTablePercXML"
QT_MOC_LITERAL(27, 475, 23), // "exportCorrTablePercHTML"
QT_MOC_LITERAL(28, 499, 18), // "exportCorrTableTXT"
QT_MOC_LITERAL(29, 518, 18), // "exportCorrTableXML"
QT_MOC_LITERAL(30, 537, 19), // "exportCorrTableHTML"
QT_MOC_LITERAL(31, 557, 12), // "exportAdhTXT"
QT_MOC_LITERAL(32, 570, 12), // "exportAdhCSV"
QT_MOC_LITERAL(33, 583, 12), // "exportAdhXML"
QT_MOC_LITERAL(34, 596, 13), // "exportAdhHTML"
QT_MOC_LITERAL(35, 610, 16), // "exportResCommTXT"
QT_MOC_LITERAL(36, 627, 16), // "exportResCommXML"
QT_MOC_LITERAL(37, 644, 17), // "exportResCommHTML"
QT_MOC_LITERAL(38, 662, 25), // "on_cmdStartWizard_clicked"
QT_MOC_LITERAL(39, 688, 18), // "on_cmdMain_clicked"
QT_MOC_LITERAL(40, 707, 18), // "on_cmdBack_clicked"
QT_MOC_LITERAL(41, 726, 21), // "on_cmdAdvance_clicked"
QT_MOC_LITERAL(42, 748, 18), // "on_cmdOpen_clicked"
QT_MOC_LITERAL(43, 767, 19), // "on_cmdFetch_clicked"
QT_MOC_LITERAL(44, 787, 25), // "on_cmdApplyFilter_clicked"
QT_MOC_LITERAL(45, 813, 22), // "on_cmdFetchPDB_clicked"
QT_MOC_LITERAL(46, 836, 25), // "on_cmdPDBfromFile_clicked"
QT_MOC_LITERAL(47, 862, 26), // "on_cmdConservation_clicked"
QT_MOC_LITERAL(48, 889, 19), // "on_cmdMinss_clicked"
QT_MOC_LITERAL(49, 909, 25), // "on_cmdCorrelation_clicked"
QT_MOC_LITERAL(50, 935, 23), // "on_listWidget_activated"
QT_MOC_LITERAL(51, 959, 5), // "index"
QT_MOC_LITERAL(52, 965, 22), // "on_cmbRefSeq_activated"
QT_MOC_LITERAL(53, 988, 24), // "on_cmbRefSeq_2_activated"
QT_MOC_LITERAL(54, 1013, 24), // "on_cmbRefSeq_3_activated"
QT_MOC_LITERAL(55, 1038, 36), // "on_lstRefSeqs_2_itemSelection..."
QT_MOC_LITERAL(56, 1075, 25), // "on_cmdSaveResults_clicked"
QT_MOC_LITERAL(57, 1101, 24), // "on_listWidget2_activated"
QT_MOC_LITERAL(58, 1126, 25), // "on_cmdShowResults_clicked"
QT_MOC_LITERAL(59, 1152, 18), // "on_cmdShow_clicked"
QT_MOC_LITERAL(60, 1171, 32), // "on_lstProteinsFiltered_activated"
QT_MOC_LITERAL(61, 1204, 22), // "on_cmdNextComm_clicked"
QT_MOC_LITERAL(62, 1227, 22), // "on_cmdBackComm_clicked"
QT_MOC_LITERAL(63, 1250, 24), // "on_cmdNextComm_2_clicked"
QT_MOC_LITERAL(64, 1275, 24), // "on_cmdBackComm_2_clicked"
QT_MOC_LITERAL(65, 1300, 24), // "on_cmdNextResult_clicked"
QT_MOC_LITERAL(66, 1325, 24), // "on_cmdBackResult_clicked"
QT_MOC_LITERAL(67, 1350, 25), // "on_cmdNextResComm_clicked"
QT_MOC_LITERAL(68, 1376, 25), // "on_cmdBackResComm_clicked"
QT_MOC_LITERAL(69, 1402, 26), // "on_cmdRemoveFilter_clicked"
QT_MOC_LITERAL(70, 1429, 29) // "on_cmdRemoveAlignment_clicked"

    },
    "MainWindow\0inputAlignment_triggered\0"
    "\0fetchPFAM_triggered\0exportAlignment_triggered\0"
    "Open_XML_triggered\0exportAlignment_PFAM\0"
    "exportAlignment_TXT\0exportAlignment_XML\0"
    "exportFreqTXT\0exportFreqCSV\0exportFreqXML\0"
    "exportFreqHTML\0exportFreqPercTXT\0"
    "exportFreqPercCSV\0exportFreqPercXML\0"
    "exportFreqPercHTML\0exportConsResTXT\0"
    "exportConsResXML\0exportConsResHTML\0"
    "exportCorrListTXT\0exportCorrListCSV\0"
    "exportCorrListXML\0exportCommsTXT\0"
    "exportCommsXML\0exportCorrTablePercTXT\0"
    "exportCorrTablePercXML\0exportCorrTablePercHTML\0"
    "exportCorrTableTXT\0exportCorrTableXML\0"
    "exportCorrTableHTML\0exportAdhTXT\0"
    "exportAdhCSV\0exportAdhXML\0exportAdhHTML\0"
    "exportResCommTXT\0exportResCommXML\0"
    "exportResCommHTML\0on_cmdStartWizard_clicked\0"
    "on_cmdMain_clicked\0on_cmdBack_clicked\0"
    "on_cmdAdvance_clicked\0on_cmdOpen_clicked\0"
    "on_cmdFetch_clicked\0on_cmdApplyFilter_clicked\0"
    "on_cmdFetchPDB_clicked\0on_cmdPDBfromFile_clicked\0"
    "on_cmdConservation_clicked\0"
    "on_cmdMinss_clicked\0on_cmdCorrelation_clicked\0"
    "on_listWidget_activated\0index\0"
    "on_cmbRefSeq_activated\0on_cmbRefSeq_2_activated\0"
    "on_cmbRefSeq_3_activated\0"
    "on_lstRefSeqs_2_itemSelectionChanged\0"
    "on_cmdSaveResults_clicked\0"
    "on_listWidget2_activated\0"
    "on_cmdShowResults_clicked\0on_cmdShow_clicked\0"
    "on_lstProteinsFiltered_activated\0"
    "on_cmdNextComm_clicked\0on_cmdBackComm_clicked\0"
    "on_cmdNextComm_2_clicked\0"
    "on_cmdBackComm_2_clicked\0"
    "on_cmdNextResult_clicked\0"
    "on_cmdBackResult_clicked\0"
    "on_cmdNextResComm_clicked\0"
    "on_cmdBackResComm_clicked\0"
    "on_cmdRemoveFilter_clicked\0"
    "on_cmdRemoveAlignment_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      68,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  354,    2, 0x08 /* Private */,
       3,    0,  355,    2, 0x08 /* Private */,
       4,    0,  356,    2, 0x08 /* Private */,
       5,    0,  357,    2, 0x08 /* Private */,
       6,    0,  358,    2, 0x08 /* Private */,
       7,    0,  359,    2, 0x08 /* Private */,
       8,    0,  360,    2, 0x08 /* Private */,
       9,    0,  361,    2, 0x08 /* Private */,
      10,    0,  362,    2, 0x08 /* Private */,
      11,    0,  363,    2, 0x08 /* Private */,
      12,    0,  364,    2, 0x08 /* Private */,
      13,    0,  365,    2, 0x08 /* Private */,
      14,    0,  366,    2, 0x08 /* Private */,
      15,    0,  367,    2, 0x08 /* Private */,
      16,    0,  368,    2, 0x08 /* Private */,
      17,    0,  369,    2, 0x08 /* Private */,
      18,    0,  370,    2, 0x08 /* Private */,
      19,    0,  371,    2, 0x08 /* Private */,
      20,    0,  372,    2, 0x08 /* Private */,
      21,    0,  373,    2, 0x08 /* Private */,
      22,    0,  374,    2, 0x08 /* Private */,
      23,    0,  375,    2, 0x08 /* Private */,
      24,    0,  376,    2, 0x08 /* Private */,
      25,    0,  377,    2, 0x08 /* Private */,
      26,    0,  378,    2, 0x08 /* Private */,
      27,    0,  379,    2, 0x08 /* Private */,
      28,    0,  380,    2, 0x08 /* Private */,
      29,    0,  381,    2, 0x08 /* Private */,
      30,    0,  382,    2, 0x08 /* Private */,
      31,    0,  383,    2, 0x08 /* Private */,
      32,    0,  384,    2, 0x08 /* Private */,
      33,    0,  385,    2, 0x08 /* Private */,
      34,    0,  386,    2, 0x08 /* Private */,
      35,    0,  387,    2, 0x08 /* Private */,
      36,    0,  388,    2, 0x08 /* Private */,
      37,    0,  389,    2, 0x08 /* Private */,
      38,    0,  390,    2, 0x08 /* Private */,
      39,    0,  391,    2, 0x08 /* Private */,
      40,    0,  392,    2, 0x08 /* Private */,
      41,    0,  393,    2, 0x08 /* Private */,
      42,    0,  394,    2, 0x08 /* Private */,
      43,    0,  395,    2, 0x08 /* Private */,
      44,    0,  396,    2, 0x08 /* Private */,
      45,    0,  397,    2, 0x08 /* Private */,
      46,    0,  398,    2, 0x08 /* Private */,
      47,    0,  399,    2, 0x08 /* Private */,
      48,    0,  400,    2, 0x08 /* Private */,
      49,    0,  401,    2, 0x08 /* Private */,
      50,    1,  402,    2, 0x08 /* Private */,
      52,    1,  405,    2, 0x08 /* Private */,
      53,    1,  408,    2, 0x08 /* Private */,
      54,    1,  411,    2, 0x08 /* Private */,
      55,    0,  414,    2, 0x08 /* Private */,
      56,    0,  415,    2, 0x08 /* Private */,
      57,    1,  416,    2, 0x08 /* Private */,
      58,    0,  419,    2, 0x08 /* Private */,
      59,    0,  420,    2, 0x08 /* Private */,
      60,    1,  421,    2, 0x08 /* Private */,
      61,    0,  424,    2, 0x08 /* Private */,
      62,    0,  425,    2, 0x08 /* Private */,
      63,    0,  426,    2, 0x08 /* Private */,
      64,    0,  427,    2, 0x08 /* Private */,
      65,    0,  428,    2, 0x08 /* Private */,
      66,    0,  429,    2, 0x08 /* Private */,
      67,    0,  430,    2, 0x08 /* Private */,
      68,    0,  431,    2, 0x08 /* Private */,
      69,    0,  432,    2, 0x08 /* Private */,
      70,    0,  433,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   51,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   51,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   51,
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
        case 3: _t->Open_XML_triggered(); break;
        case 4: _t->exportAlignment_PFAM(); break;
        case 5: _t->exportAlignment_TXT(); break;
        case 6: _t->exportAlignment_XML(); break;
        case 7: _t->exportFreqTXT(); break;
        case 8: _t->exportFreqCSV(); break;
        case 9: _t->exportFreqXML(); break;
        case 10: _t->exportFreqHTML(); break;
        case 11: _t->exportFreqPercTXT(); break;
        case 12: _t->exportFreqPercCSV(); break;
        case 13: _t->exportFreqPercXML(); break;
        case 14: _t->exportFreqPercHTML(); break;
        case 15: _t->exportConsResTXT(); break;
        case 16: _t->exportConsResXML(); break;
        case 17: _t->exportConsResHTML(); break;
        case 18: _t->exportCorrListTXT(); break;
        case 19: _t->exportCorrListCSV(); break;
        case 20: _t->exportCorrListXML(); break;
        case 21: _t->exportCommsTXT(); break;
        case 22: _t->exportCommsXML(); break;
        case 23: _t->exportCorrTablePercTXT(); break;
        case 24: _t->exportCorrTablePercXML(); break;
        case 25: _t->exportCorrTablePercHTML(); break;
        case 26: _t->exportCorrTableTXT(); break;
        case 27: _t->exportCorrTableXML(); break;
        case 28: _t->exportCorrTableHTML(); break;
        case 29: _t->exportAdhTXT(); break;
        case 30: _t->exportAdhCSV(); break;
        case 31: _t->exportAdhXML(); break;
        case 32: _t->exportAdhHTML(); break;
        case 33: _t->exportResCommTXT(); break;
        case 34: _t->exportResCommXML(); break;
        case 35: _t->exportResCommHTML(); break;
        case 36: _t->on_cmdStartWizard_clicked(); break;
        case 37: _t->on_cmdMain_clicked(); break;
        case 38: _t->on_cmdBack_clicked(); break;
        case 39: _t->on_cmdAdvance_clicked(); break;
        case 40: _t->on_cmdOpen_clicked(); break;
        case 41: _t->on_cmdFetch_clicked(); break;
        case 42: _t->on_cmdApplyFilter_clicked(); break;
        case 43: _t->on_cmdFetchPDB_clicked(); break;
        case 44: _t->on_cmdPDBfromFile_clicked(); break;
        case 45: _t->on_cmdConservation_clicked(); break;
        case 46: _t->on_cmdMinss_clicked(); break;
        case 47: _t->on_cmdCorrelation_clicked(); break;
        case 48: _t->on_listWidget_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 49: _t->on_cmbRefSeq_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->on_cmbRefSeq_2_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->on_cmbRefSeq_3_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_lstRefSeqs_2_itemSelectionChanged(); break;
        case 53: _t->on_cmdSaveResults_clicked(); break;
        case 54: _t->on_listWidget2_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 55: _t->on_cmdShowResults_clicked(); break;
        case 56: _t->on_cmdShow_clicked(); break;
        case 57: _t->on_lstProteinsFiltered_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 58: _t->on_cmdNextComm_clicked(); break;
        case 59: _t->on_cmdBackComm_clicked(); break;
        case 60: _t->on_cmdNextComm_2_clicked(); break;
        case 61: _t->on_cmdBackComm_2_clicked(); break;
        case 62: _t->on_cmdNextResult_clicked(); break;
        case 63: _t->on_cmdBackResult_clicked(); break;
        case 64: _t->on_cmdNextResComm_clicked(); break;
        case 65: _t->on_cmdBackResComm_clicked(); break;
        case 66: _t->on_cmdRemoveFilter_clicked(); break;
        case 67: _t->on_cmdRemoveAlignment_clicked(); break;
        default: ;
        }
    }
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
        if (_id < 68)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 68;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 68)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 68;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
