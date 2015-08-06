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
    QByteArrayData data[77];
    char stringdata[1589];
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
QT_MOC_LITERAL(38, 662, 17), // "exportConsRefsTXT"
QT_MOC_LITERAL(39, 680, 17), // "exportConsRefsXML"
QT_MOC_LITERAL(40, 698, 17), // "exportCorrRefsTXT"
QT_MOC_LITERAL(41, 716, 17), // "exportCorrRefsXML"
QT_MOC_LITERAL(42, 734, 25), // "on_cmdStartWizard_clicked"
QT_MOC_LITERAL(43, 760, 18), // "on_cmdMain_clicked"
QT_MOC_LITERAL(44, 779, 18), // "on_cmdBack_clicked"
QT_MOC_LITERAL(45, 798, 21), // "on_cmdAdvance_clicked"
QT_MOC_LITERAL(46, 820, 18), // "on_cmdOpen_clicked"
QT_MOC_LITERAL(47, 839, 19), // "on_cmdFetch_clicked"
QT_MOC_LITERAL(48, 859, 25), // "on_cmdApplyFilter_clicked"
QT_MOC_LITERAL(49, 885, 22), // "on_cmdFetchPDB_clicked"
QT_MOC_LITERAL(50, 908, 25), // "on_cmdPDBfromFile_clicked"
QT_MOC_LITERAL(51, 934, 26), // "on_cmdConservation_clicked"
QT_MOC_LITERAL(52, 961, 19), // "on_cmdMinss_clicked"
QT_MOC_LITERAL(53, 981, 25), // "on_cmdCorrelation_clicked"
QT_MOC_LITERAL(54, 1007, 23), // "on_listWidget_activated"
QT_MOC_LITERAL(55, 1031, 5), // "index"
QT_MOC_LITERAL(56, 1037, 22), // "on_cmbRefSeq_activated"
QT_MOC_LITERAL(57, 1060, 24), // "on_cmbRefSeq_2_activated"
QT_MOC_LITERAL(58, 1085, 24), // "on_cmbRefSeq_3_activated"
QT_MOC_LITERAL(59, 1110, 36), // "on_lstRefSeqs_2_itemSelection..."
QT_MOC_LITERAL(60, 1147, 25), // "on_cmdSaveResults_clicked"
QT_MOC_LITERAL(61, 1173, 24), // "on_listWidget2_activated"
QT_MOC_LITERAL(62, 1198, 25), // "on_cmdShowResults_clicked"
QT_MOC_LITERAL(63, 1224, 18), // "on_cmdShow_clicked"
QT_MOC_LITERAL(64, 1243, 32), // "on_lstProteinsFiltered_activated"
QT_MOC_LITERAL(65, 1276, 22), // "on_cmdNextComm_clicked"
QT_MOC_LITERAL(66, 1299, 22), // "on_cmdBackComm_clicked"
QT_MOC_LITERAL(67, 1322, 24), // "on_cmdNextComm_2_clicked"
QT_MOC_LITERAL(68, 1347, 24), // "on_cmdBackComm_2_clicked"
QT_MOC_LITERAL(69, 1372, 24), // "on_cmdNextResult_clicked"
QT_MOC_LITERAL(70, 1397, 24), // "on_cmdBackResult_clicked"
QT_MOC_LITERAL(71, 1422, 25), // "on_cmdNextResComm_clicked"
QT_MOC_LITERAL(72, 1448, 25), // "on_cmdBackResComm_clicked"
QT_MOC_LITERAL(73, 1474, 26), // "on_cmdRemoveFilter_clicked"
QT_MOC_LITERAL(74, 1501, 29), // "on_cmdRemoveAlignment_clicked"
QT_MOC_LITERAL(75, 1531, 32), // "on_cmdUploadConsRefsSeqs_clicked"
QT_MOC_LITERAL(76, 1564, 24) // "on_cmdCorRefSeqs_clicked"

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
    "exportResCommHTML\0exportConsRefsTXT\0"
    "exportConsRefsXML\0exportCorrRefsTXT\0"
    "exportCorrRefsXML\0on_cmdStartWizard_clicked\0"
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
    "on_cmdRemoveAlignment_clicked\0"
    "on_cmdUploadConsRefsSeqs_clicked\0"
    "on_cmdCorRefSeqs_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      74,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  384,    2, 0x08 /* Private */,
       3,    0,  385,    2, 0x08 /* Private */,
       4,    0,  386,    2, 0x08 /* Private */,
       5,    0,  387,    2, 0x08 /* Private */,
       6,    0,  388,    2, 0x08 /* Private */,
       7,    0,  389,    2, 0x08 /* Private */,
       8,    0,  390,    2, 0x08 /* Private */,
       9,    0,  391,    2, 0x08 /* Private */,
      10,    0,  392,    2, 0x08 /* Private */,
      11,    0,  393,    2, 0x08 /* Private */,
      12,    0,  394,    2, 0x08 /* Private */,
      13,    0,  395,    2, 0x08 /* Private */,
      14,    0,  396,    2, 0x08 /* Private */,
      15,    0,  397,    2, 0x08 /* Private */,
      16,    0,  398,    2, 0x08 /* Private */,
      17,    0,  399,    2, 0x08 /* Private */,
      18,    0,  400,    2, 0x08 /* Private */,
      19,    0,  401,    2, 0x08 /* Private */,
      20,    0,  402,    2, 0x08 /* Private */,
      21,    0,  403,    2, 0x08 /* Private */,
      22,    0,  404,    2, 0x08 /* Private */,
      23,    0,  405,    2, 0x08 /* Private */,
      24,    0,  406,    2, 0x08 /* Private */,
      25,    0,  407,    2, 0x08 /* Private */,
      26,    0,  408,    2, 0x08 /* Private */,
      27,    0,  409,    2, 0x08 /* Private */,
      28,    0,  410,    2, 0x08 /* Private */,
      29,    0,  411,    2, 0x08 /* Private */,
      30,    0,  412,    2, 0x08 /* Private */,
      31,    0,  413,    2, 0x08 /* Private */,
      32,    0,  414,    2, 0x08 /* Private */,
      33,    0,  415,    2, 0x08 /* Private */,
      34,    0,  416,    2, 0x08 /* Private */,
      35,    0,  417,    2, 0x08 /* Private */,
      36,    0,  418,    2, 0x08 /* Private */,
      37,    0,  419,    2, 0x08 /* Private */,
      38,    0,  420,    2, 0x08 /* Private */,
      39,    0,  421,    2, 0x08 /* Private */,
      40,    0,  422,    2, 0x08 /* Private */,
      41,    0,  423,    2, 0x08 /* Private */,
      42,    0,  424,    2, 0x08 /* Private */,
      43,    0,  425,    2, 0x08 /* Private */,
      44,    0,  426,    2, 0x08 /* Private */,
      45,    0,  427,    2, 0x08 /* Private */,
      46,    0,  428,    2, 0x08 /* Private */,
      47,    0,  429,    2, 0x08 /* Private */,
      48,    0,  430,    2, 0x08 /* Private */,
      49,    0,  431,    2, 0x08 /* Private */,
      50,    0,  432,    2, 0x08 /* Private */,
      51,    0,  433,    2, 0x08 /* Private */,
      52,    0,  434,    2, 0x08 /* Private */,
      53,    0,  435,    2, 0x08 /* Private */,
      54,    1,  436,    2, 0x08 /* Private */,
      56,    1,  439,    2, 0x08 /* Private */,
      57,    1,  442,    2, 0x08 /* Private */,
      58,    1,  445,    2, 0x08 /* Private */,
      59,    0,  448,    2, 0x08 /* Private */,
      60,    0,  449,    2, 0x08 /* Private */,
      61,    1,  450,    2, 0x08 /* Private */,
      62,    0,  453,    2, 0x08 /* Private */,
      63,    0,  454,    2, 0x08 /* Private */,
      64,    1,  455,    2, 0x08 /* Private */,
      65,    0,  458,    2, 0x08 /* Private */,
      66,    0,  459,    2, 0x08 /* Private */,
      67,    0,  460,    2, 0x08 /* Private */,
      68,    0,  461,    2, 0x08 /* Private */,
      69,    0,  462,    2, 0x08 /* Private */,
      70,    0,  463,    2, 0x08 /* Private */,
      71,    0,  464,    2, 0x08 /* Private */,
      72,    0,  465,    2, 0x08 /* Private */,
      73,    0,  466,    2, 0x08 /* Private */,
      74,    0,  467,    2, 0x08 /* Private */,
      75,    0,  468,    2, 0x08 /* Private */,
      76,    0,  469,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   55,
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
        case 36: _t->exportConsRefsTXT(); break;
        case 37: _t->exportConsRefsXML(); break;
        case 38: _t->exportCorrRefsTXT(); break;
        case 39: _t->exportCorrRefsXML(); break;
        case 40: _t->on_cmdStartWizard_clicked(); break;
        case 41: _t->on_cmdMain_clicked(); break;
        case 42: _t->on_cmdBack_clicked(); break;
        case 43: _t->on_cmdAdvance_clicked(); break;
        case 44: _t->on_cmdOpen_clicked(); break;
        case 45: _t->on_cmdFetch_clicked(); break;
        case 46: _t->on_cmdApplyFilter_clicked(); break;
        case 47: _t->on_cmdFetchPDB_clicked(); break;
        case 48: _t->on_cmdPDBfromFile_clicked(); break;
        case 49: _t->on_cmdConservation_clicked(); break;
        case 50: _t->on_cmdMinss_clicked(); break;
        case 51: _t->on_cmdCorrelation_clicked(); break;
        case 52: _t->on_listWidget_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 53: _t->on_cmbRefSeq_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->on_cmbRefSeq_2_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->on_cmbRefSeq_3_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->on_lstRefSeqs_2_itemSelectionChanged(); break;
        case 57: _t->on_cmdSaveResults_clicked(); break;
        case 58: _t->on_listWidget2_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 59: _t->on_cmdShowResults_clicked(); break;
        case 60: _t->on_cmdShow_clicked(); break;
        case 61: _t->on_lstProteinsFiltered_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 62: _t->on_cmdNextComm_clicked(); break;
        case 63: _t->on_cmdBackComm_clicked(); break;
        case 64: _t->on_cmdNextComm_2_clicked(); break;
        case 65: _t->on_cmdBackComm_2_clicked(); break;
        case 66: _t->on_cmdNextResult_clicked(); break;
        case 67: _t->on_cmdBackResult_clicked(); break;
        case 68: _t->on_cmdNextResComm_clicked(); break;
        case 69: _t->on_cmdBackResComm_clicked(); break;
        case 70: _t->on_cmdRemoveFilter_clicked(); break;
        case 71: _t->on_cmdRemoveAlignment_clicked(); break;
        case 72: _t->on_cmdUploadConsRefsSeqs_clicked(); break;
        case 73: _t->on_cmdCorRefSeqs_clicked(); break;
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
        if (_id < 74)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 74;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 74)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 74;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
