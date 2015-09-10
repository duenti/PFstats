/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInput_Alignment;
    QAction *actionFetch_From_PFAM;
    QAction *actionExport_Alignment;
    QAction *actionFilter_Alignment;
    QAction *actionCalculate_Minimum_Sub_Alignment_Size;
    QAction *actionCalculate_Correlation_Scores;
    QAction *actionDecompose_Network;
    QAction *actionAnalyze_Conservation_Sets;
    QAction *actionAbout;
    QAction *actionClose_Alignment;
    QAction *actionOpen_XML;
    QAction *actionAlignmentPFAM;
    QAction *actionAlignmentTXT;
    QAction *actionAlignmentXML;
    QAction *actionFreqTXT;
    QAction *actionFreqCSV;
    QAction *actionFreqXML;
    QAction *actionFreqHTML;
    QAction *actionFreqPercTXT;
    QAction *actionFreqPercCSV;
    QAction *actionFreqPercXML;
    QAction *actionFreqPercHTML;
    QAction *actionResults_Table;
    QAction *actionConservation_Scatterplot;
    QAction *actionCommunities_Graph;
    QAction *actionConserved_Residues_in_Structure;
    QAction *actionConsResXML;
    QAction *actionConsResHTML;
    QAction *actionConsResTXT;
    QAction *actionCorrListTXT;
    QAction *actionCorrListCSV;
    QAction *actionCorrListXML;
    QAction *actionCommTXT;
    QAction *actionCommXML;
    QAction *actionCorrTablePercTXT;
    QAction *actionCorrTablePercXML;
    QAction *actionCorrTablePercHTML;
    QAction *actionCorrTableTXT;
    QAction *actionCorrTableXML;
    QAction *actionCorrTableHTML;
    QAction *actionAdhTXT;
    QAction *actionAdhCSV;
    QAction *actionAdhXML;
    QAction *actionAdhHTML;
    QAction *actionResCommTXT;
    QAction *actionResCommXML;
    QAction *actionResCommHTML;
    QAction *actionConsRefsTXT;
    QAction *actionConsRefsXML;
    QAction *actionCorrRefsTXT;
    QAction *actionCorrRefsXML;
    QAction *actionConservation;
    QAction *actionMinss;
    QAction *actionCorrelation;
    QAction *actionShow_Results;
    QAction *actionSave_Results;
    QAction *actionStart_Wizard;
    QAction *actionUniprotLooking;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdStartWizard;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_2;
    QLabel *label_2;
    QGroupBox *groupBox;
    QPushButton *cmdOpen;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *txtAccession;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cmdFetch;
    QSpacerItem *horizontalSpacer_4;
    QWidget *page_3;
    QLabel *label_9;
    QPushButton *cmdApplyFilter;
    QLabel *label_27;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QComboBox *cmbRefSeq;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *txtMinCover;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *txtMinId;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_7;
    QDoubleSpinBox *txtMaxId;
    QCheckBox *chkIntermediateFilter;
    QWidget *page_4;
    QLabel *label_14;
    QGroupBox *groupBox_3;
    QPushButton *cmdPDBfromFile;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_15;
    QLineEdit *txtPDBfilepath;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_16;
    QLineEdit *txtPDBName;
    QPushButton *cmdFetchPDB;
    QGroupBox *groupBox_4;
    QPushButton *cmdConservation;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_18;
    QLineEdit *txtOffset;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_19;
    QLineEdit *txtChain;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_28;
    QDoubleSpinBox *txtMinConserv;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_17;
    QComboBox *cmbRefSeq_2;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_44;
    QPushButton *cmdUploadConsRefsSeqs;
    QListWidget *lstRefSeqs;
    QWidget *page_5;
    QLabel *label_21;
    QCustomPlot *graficMinss;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_18;
    QLabel *lblNseq;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_22;
    QSpinBox *txtNoAlignments;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *cmdMinss;
    QWidget *page_6;
    QLabel *label_23;
    QPushButton *cmdCorrelation;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_24;
    QSpinBox *txtMinScore;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_25;
    QDoubleSpinBox *txtMinssFraction;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_26;
    QDoubleSpinBox *txtMinDeltaFreq;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_30;
    QLineEdit *txtOffset_2;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_29;
    QComboBox *cmbRefSeq_3;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_31;
    QPushButton *cmdCorRefSeqs;
    QListWidget *lstRefSeqs_2;
    QWidget *page_7;
    QLabel *label_32;
    QStackedWidget *stackedWidget2;
    QWidget *page_8;
    QGroupBox *groupBox_5;
    QPushButton *cmdShow;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_27;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *checkResults1;
    QCheckBox *checkResults2;
    QCheckBox *checkResults3;
    QCheckBox *checkResults4;
    QCheckBox *checkResults5;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *checkResults6;
    QCheckBox *checkResults7;
    QCheckBox *checkResults8;
    QCheckBox *checkResults9;
    QCheckBox *checkResults10;
    QLabel *lblHidden;
    QWidget *page_9;
    QLabel *label_20;
    QListWidget *lstProteinsFiltered;
    QLabel *label_33;
    QTextEdit *txtSequence;
    QLabel *label_34;
    QLabel *lblRefSeq1;
    QLabel *lblOccupancy;
    QLabel *lblMinId;
    QLabel *lblMaxId;
    QWidget *page_10;
    QLabel *label_35;
    QTableWidget *tableFreq;
    QLabel *lblFilter;
    QLabel *lblRefSeq;
    QLabel *lblOffset;
    QLabel *lblChain;
    QWidget *page_11;
    QLabel *lblRefSeq_2;
    QLabel *lblChain_2;
    QLabel *lblFilter_2;
    QLabel *lblOffset_2;
    QLabel *label_36;
    QTableWidget *tableFreqPerc;
    QWidget *page_12;
    QLabel *label_37;
    QTableWidget *tableConsRes;
    QLabel *lblFilter_8;
    QLabel *lblMinCons;
    QWidget *page_13;
    QLabel *label_38;
    QTreeWidget *treeCorrelation;
    QLabel *lblFilter_3;
    QLabel *lblMinLogP;
    QLabel *lblMinss;
    QLabel *lblDeltaFreq;
    QWidget *page_14;
    QLabel *label_39;
    QLabel *lblFilter_4;
    QLabel *lblMinLogP_2;
    QTreeWidget *treeCorrelationComm;
    QLabel *lblDeltaFreq_2;
    QLabel *lblMinss_2;
    QWidget *page_15;
    QLabel *label_40;
    QLabel *lblFilter_5;
    QLabel *lblMinLogP_3;
    QLabel *lblMinss_3;
    QLabel *lblDeltaFreq_3;
    QLabel *lblComunidade;
    QTableWidget *tableComm1;
    QPushButton *cmdNextComm;
    QPushButton *cmdBackComm;
    QWidget *page_16;
    QLabel *label_41;
    QLabel *lblMinss_4;
    QPushButton *cmdBackComm_2;
    QLabel *lblDeltaFreq_4;
    QLabel *lblComunidade_2;
    QPushButton *cmdNextComm_2;
    QLabel *lblMinLogP_4;
    QLabel *lblFilter_6;
    QTableWidget *tableComm2;
    QWidget *page_17;
    QLabel *label_42;
    QLabel *lblFilter_7;
    QTableWidget *tableAdherence;
    QWidget *page_18;
    QLabel *label_43;
    QTableWidget *tableResiduesComm;
    QPushButton *cmdNextResComm;
    QPushButton *cmdBackResComm;
    QLabel *lblComunidade_3;
    QLabel *lblFilter_9;
    QPushButton *cmdNextResult;
    QPushButton *cmdBackResult;
    QWidget *page_19;
    QLabel *label_47;
    QGroupBox *groupBox_6;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_29;
    QCheckBox *chkConserveds;
    QCheckBox *chkComm;
    QGroupBox *groupBox_7;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_30;
    QRadioButton *radioGroupBy1;
    QRadioButton *radioGroupBy2;
    QLabel *label_48;
    QPushButton *cmdLook;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *cmdMain;
    QPushButton *cmdBack;
    QPushButton *cmdAdvance;
    QPushButton *cmdSaveResults;
    QPushButton *cmdShowResults;
    QWidget *layoutWidget12;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_45;
    QPushButton *cmdRemoveAlignment;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_46;
    QPushButton *cmdRemoveFilter;
    QListWidget *listWidget2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMethod;
    QMenu *menuHelp;
    QMenu *menuShow;
    QMenu *menuExport;
    QMenu *menuAlignment;
    QMenu *menuFrequence_Conservation;
    QMenu *menuFrequence_Conservation_2;
    QMenu *menuConserved_Residues;
    QMenu *menuCorrelation_List;
    QMenu *menuCommunities;
    QMenu *menuCorrelation_Tables;
    QMenu *menuCorrelation_Tables_Log_P;
    QMenu *menuAdherence_Matrix;
    QMenu *menuResidues_Of_Communities;
    QMenu *menuConservation_Reference_Sequences;
    QMenu *menuCorrelation_Reference_Sequences;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(983, 645);
        actionInput_Alignment = new QAction(MainWindow);
        actionInput_Alignment->setObjectName(QStringLiteral("actionInput_Alignment"));
        actionFetch_From_PFAM = new QAction(MainWindow);
        actionFetch_From_PFAM->setObjectName(QStringLiteral("actionFetch_From_PFAM"));
        actionExport_Alignment = new QAction(MainWindow);
        actionExport_Alignment->setObjectName(QStringLiteral("actionExport_Alignment"));
        actionFilter_Alignment = new QAction(MainWindow);
        actionFilter_Alignment->setObjectName(QStringLiteral("actionFilter_Alignment"));
        actionCalculate_Minimum_Sub_Alignment_Size = new QAction(MainWindow);
        actionCalculate_Minimum_Sub_Alignment_Size->setObjectName(QStringLiteral("actionCalculate_Minimum_Sub_Alignment_Size"));
        actionCalculate_Correlation_Scores = new QAction(MainWindow);
        actionCalculate_Correlation_Scores->setObjectName(QStringLiteral("actionCalculate_Correlation_Scores"));
        actionDecompose_Network = new QAction(MainWindow);
        actionDecompose_Network->setObjectName(QStringLiteral("actionDecompose_Network"));
        actionAnalyze_Conservation_Sets = new QAction(MainWindow);
        actionAnalyze_Conservation_Sets->setObjectName(QStringLiteral("actionAnalyze_Conservation_Sets"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionClose_Alignment = new QAction(MainWindow);
        actionClose_Alignment->setObjectName(QStringLiteral("actionClose_Alignment"));
        actionOpen_XML = new QAction(MainWindow);
        actionOpen_XML->setObjectName(QStringLiteral("actionOpen_XML"));
        actionAlignmentPFAM = new QAction(MainWindow);
        actionAlignmentPFAM->setObjectName(QStringLiteral("actionAlignmentPFAM"));
        actionAlignmentTXT = new QAction(MainWindow);
        actionAlignmentTXT->setObjectName(QStringLiteral("actionAlignmentTXT"));
        actionAlignmentXML = new QAction(MainWindow);
        actionAlignmentXML->setObjectName(QStringLiteral("actionAlignmentXML"));
        actionFreqTXT = new QAction(MainWindow);
        actionFreqTXT->setObjectName(QStringLiteral("actionFreqTXT"));
        actionFreqCSV = new QAction(MainWindow);
        actionFreqCSV->setObjectName(QStringLiteral("actionFreqCSV"));
        actionFreqXML = new QAction(MainWindow);
        actionFreqXML->setObjectName(QStringLiteral("actionFreqXML"));
        actionFreqHTML = new QAction(MainWindow);
        actionFreqHTML->setObjectName(QStringLiteral("actionFreqHTML"));
        actionFreqPercTXT = new QAction(MainWindow);
        actionFreqPercTXT->setObjectName(QStringLiteral("actionFreqPercTXT"));
        actionFreqPercCSV = new QAction(MainWindow);
        actionFreqPercCSV->setObjectName(QStringLiteral("actionFreqPercCSV"));
        actionFreqPercXML = new QAction(MainWindow);
        actionFreqPercXML->setObjectName(QStringLiteral("actionFreqPercXML"));
        actionFreqPercHTML = new QAction(MainWindow);
        actionFreqPercHTML->setObjectName(QStringLiteral("actionFreqPercHTML"));
        actionResults_Table = new QAction(MainWindow);
        actionResults_Table->setObjectName(QStringLiteral("actionResults_Table"));
        actionResults_Table->setEnabled(false);
        actionConservation_Scatterplot = new QAction(MainWindow);
        actionConservation_Scatterplot->setObjectName(QStringLiteral("actionConservation_Scatterplot"));
        actionConservation_Scatterplot->setEnabled(false);
        actionCommunities_Graph = new QAction(MainWindow);
        actionCommunities_Graph->setObjectName(QStringLiteral("actionCommunities_Graph"));
        actionCommunities_Graph->setEnabled(false);
        actionConserved_Residues_in_Structure = new QAction(MainWindow);
        actionConserved_Residues_in_Structure->setObjectName(QStringLiteral("actionConserved_Residues_in_Structure"));
        actionConserved_Residues_in_Structure->setEnabled(false);
        actionConsResXML = new QAction(MainWindow);
        actionConsResXML->setObjectName(QStringLiteral("actionConsResXML"));
        actionConsResHTML = new QAction(MainWindow);
        actionConsResHTML->setObjectName(QStringLiteral("actionConsResHTML"));
        actionConsResTXT = new QAction(MainWindow);
        actionConsResTXT->setObjectName(QStringLiteral("actionConsResTXT"));
        actionCorrListTXT = new QAction(MainWindow);
        actionCorrListTXT->setObjectName(QStringLiteral("actionCorrListTXT"));
        actionCorrListCSV = new QAction(MainWindow);
        actionCorrListCSV->setObjectName(QStringLiteral("actionCorrListCSV"));
        actionCorrListXML = new QAction(MainWindow);
        actionCorrListXML->setObjectName(QStringLiteral("actionCorrListXML"));
        actionCommTXT = new QAction(MainWindow);
        actionCommTXT->setObjectName(QStringLiteral("actionCommTXT"));
        actionCommXML = new QAction(MainWindow);
        actionCommXML->setObjectName(QStringLiteral("actionCommXML"));
        actionCorrTablePercTXT = new QAction(MainWindow);
        actionCorrTablePercTXT->setObjectName(QStringLiteral("actionCorrTablePercTXT"));
        actionCorrTablePercXML = new QAction(MainWindow);
        actionCorrTablePercXML->setObjectName(QStringLiteral("actionCorrTablePercXML"));
        actionCorrTablePercHTML = new QAction(MainWindow);
        actionCorrTablePercHTML->setObjectName(QStringLiteral("actionCorrTablePercHTML"));
        actionCorrTableTXT = new QAction(MainWindow);
        actionCorrTableTXT->setObjectName(QStringLiteral("actionCorrTableTXT"));
        actionCorrTableXML = new QAction(MainWindow);
        actionCorrTableXML->setObjectName(QStringLiteral("actionCorrTableXML"));
        actionCorrTableHTML = new QAction(MainWindow);
        actionCorrTableHTML->setObjectName(QStringLiteral("actionCorrTableHTML"));
        actionAdhTXT = new QAction(MainWindow);
        actionAdhTXT->setObjectName(QStringLiteral("actionAdhTXT"));
        actionAdhCSV = new QAction(MainWindow);
        actionAdhCSV->setObjectName(QStringLiteral("actionAdhCSV"));
        actionAdhXML = new QAction(MainWindow);
        actionAdhXML->setObjectName(QStringLiteral("actionAdhXML"));
        actionAdhHTML = new QAction(MainWindow);
        actionAdhHTML->setObjectName(QStringLiteral("actionAdhHTML"));
        actionResCommTXT = new QAction(MainWindow);
        actionResCommTXT->setObjectName(QStringLiteral("actionResCommTXT"));
        actionResCommXML = new QAction(MainWindow);
        actionResCommXML->setObjectName(QStringLiteral("actionResCommXML"));
        actionResCommHTML = new QAction(MainWindow);
        actionResCommHTML->setObjectName(QStringLiteral("actionResCommHTML"));
        actionConsRefsTXT = new QAction(MainWindow);
        actionConsRefsTXT->setObjectName(QStringLiteral("actionConsRefsTXT"));
        actionConsRefsXML = new QAction(MainWindow);
        actionConsRefsXML->setObjectName(QStringLiteral("actionConsRefsXML"));
        actionCorrRefsTXT = new QAction(MainWindow);
        actionCorrRefsTXT->setObjectName(QStringLiteral("actionCorrRefsTXT"));
        actionCorrRefsXML = new QAction(MainWindow);
        actionCorrRefsXML->setObjectName(QStringLiteral("actionCorrRefsXML"));
        actionConservation = new QAction(MainWindow);
        actionConservation->setObjectName(QStringLiteral("actionConservation"));
        actionMinss = new QAction(MainWindow);
        actionMinss->setObjectName(QStringLiteral("actionMinss"));
        actionCorrelation = new QAction(MainWindow);
        actionCorrelation->setObjectName(QStringLiteral("actionCorrelation"));
        actionShow_Results = new QAction(MainWindow);
        actionShow_Results->setObjectName(QStringLiteral("actionShow_Results"));
        actionSave_Results = new QAction(MainWindow);
        actionSave_Results->setObjectName(QStringLiteral("actionSave_Results"));
        actionStart_Wizard = new QAction(MainWindow);
        actionStart_Wizard->setObjectName(QStringLiteral("actionStart_Wizard"));
        actionUniprotLooking = new QAction(MainWindow);
        actionUniprotLooking->setObjectName(QStringLiteral("actionUniprotLooking"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(280, 9, 691, 521));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 38, 292, 142));
        label->setWordWrap(true);
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 230, 174, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdStartWizard = new QPushButton(layoutWidget);
        cmdStartWizard->setObjectName(QStringLiteral("cmdStartWizard"));

        horizontalLayout->addWidget(cmdStartWizard);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, -10, 491, 131));
        label_2->setWordWrap(true);
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 110, 141, 81));
        cmdOpen = new QPushButton(groupBox);
        cmdOpen->setObjectName(QStringLiteral("cmdOpen"));
        cmdOpen->setGeometry(QRect(20, 40, 80, 23));
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 110, 401, 321));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 30, 368, 266));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        txtAccession = new QLineEdit(layoutWidget1);
        txtAccession->setObjectName(QStringLiteral("txtAccession"));

        horizontalLayout_6->addWidget(txtAccession);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        radioButton = new QRadioButton(layoutWidget1);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(false);

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget1);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        radioButton_3 = new QRadioButton(layoutWidget1);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        horizontalLayout_3->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(layoutWidget1);
        buttonGroup_2->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        radioButton_5 = new QRadioButton(layoutWidget1);
        buttonGroup_3 = new QButtonGroup(MainWindow);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(radioButton_5);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        horizontalLayout_4->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(layoutWidget1);
        buttonGroup_3->addButton(radioButton_6);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setChecked(true);

        horizontalLayout_4->addWidget(radioButton_6);


        verticalLayout->addLayout(horizontalLayout_4);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radioButton_7 = new QRadioButton(layoutWidget1);
        buttonGroup_4 = new QButtonGroup(MainWindow);
        buttonGroup_4->setObjectName(QStringLiteral("buttonGroup_4"));
        buttonGroup_4->addButton(radioButton_7);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setChecked(true);

        horizontalLayout_5->addWidget(radioButton_7);

        radioButton_8 = new QRadioButton(layoutWidget1);
        buttonGroup_4->addButton(radioButton_8);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));

        horizontalLayout_5->addWidget(radioButton_8);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        radioButton_9 = new QRadioButton(layoutWidget1);
        buttonGroup_4->addButton(radioButton_9);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));

        horizontalLayout_7->addWidget(radioButton_9);

        radioButton_10 = new QRadioButton(layoutWidget1);
        buttonGroup_4->addButton(radioButton_10);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));

        horizontalLayout_7->addWidget(radioButton_10);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        cmdFetch = new QPushButton(layoutWidget1);
        cmdFetch->setObjectName(QStringLiteral("cmdFetch"));

        horizontalLayout_8->addWidget(cmdFetch);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_2);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_9 = new QLabel(page_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(50, -10, 491, 131));
        label_9->setWordWrap(true);
        cmdApplyFilter = new QPushButton(page_3);
        cmdApplyFilter->setObjectName(QStringLiteral("cmdApplyFilter"));
        cmdApplyFilter->setGeometry(QRect(220, 310, 80, 23));
        label_27 = new QLabel(page_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(410, 140, 121, 17));
        layoutWidget2 = new QWidget(page_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(130, 130, 262, 166));
        verticalLayout_19 = new QVBoxLayout(layoutWidget2);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        cmbRefSeq = new QComboBox(layoutWidget2);
        cmbRefSeq->setObjectName(QStringLiteral("cmbRefSeq"));

        horizontalLayout_10->addWidget(cmbRefSeq);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_11->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        txtMinCover = new QDoubleSpinBox(layoutWidget2);
        txtMinCover->setObjectName(QStringLiteral("txtMinCover"));
        txtMinCover->setMinimum(0.01);
        txtMinCover->setSingleStep(0.01);
        txtMinCover->setValue(0.8);

        horizontalLayout_11->addWidget(txtMinCover);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);

        txtMinId = new QDoubleSpinBox(layoutWidget2);
        txtMinId->setObjectName(QStringLiteral("txtMinId"));
        txtMinId->setMinimum(0.01);
        txtMinId->setSingleStep(0.01);
        txtMinId->setValue(0.15);

        horizontalLayout_12->addWidget(txtMinId);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_13->addWidget(label_13);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);

        txtMaxId = new QDoubleSpinBox(layoutWidget2);
        txtMaxId->setObjectName(QStringLiteral("txtMaxId"));
        txtMaxId->setMinimum(0.01);
        txtMaxId->setSingleStep(0.01);
        txtMaxId->setValue(0.8);

        horizontalLayout_13->addWidget(txtMaxId);


        verticalLayout_4->addLayout(horizontalLayout_13);


        verticalLayout_19->addLayout(verticalLayout_4);

        chkIntermediateFilter = new QCheckBox(layoutWidget2);
        chkIntermediateFilter->setObjectName(QStringLiteral("chkIntermediateFilter"));
        chkIntermediateFilter->setChecked(false);

        verticalLayout_19->addWidget(chkIntermediateFilter);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_14 = new QLabel(page_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, 10, 491, 131));
        label_14->setWordWrap(true);
        groupBox_3 = new QGroupBox(page_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(50, 150, 511, 111));
        cmdPDBfromFile = new QPushButton(groupBox_3);
        cmdPDBfromFile->setObjectName(QStringLiteral("cmdPDBfromFile"));
        cmdPDBfromFile->setGeometry(QRect(350, 30, 131, 23));
        layoutWidget3 = new QWidget(groupBox_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 70, 471, 29));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget3);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_14->addWidget(label_15);

        txtPDBfilepath = new QLineEdit(layoutWidget3);
        txtPDBfilepath->setObjectName(QStringLiteral("txtPDBfilepath"));
        txtPDBfilepath->setMinimumSize(QSize(400, 0));
        txtPDBfilepath->setReadOnly(true);

        horizontalLayout_14->addWidget(txtPDBfilepath);

        layoutWidget4 = new QWidget(groupBox_3);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(30, 30, 302, 29));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget4);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_15->addWidget(label_16);

        txtPDBName = new QLineEdit(layoutWidget4);
        txtPDBName->setObjectName(QStringLiteral("txtPDBName"));

        horizontalLayout_15->addWidget(txtPDBName);

        cmdFetchPDB = new QPushButton(layoutWidget4);
        cmdFetchPDB->setObjectName(QStringLiteral("cmdFetchPDB"));

        horizontalLayout_15->addWidget(cmdFetchPDB);

        layoutWidget->raise();
        layoutWidget->raise();
        cmdPDBfromFile->raise();
        groupBox_4 = new QGroupBox(page_4);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(50, 260, 671, 241));
        cmdConservation = new QPushButton(groupBox_4);
        cmdConservation->setObjectName(QStringLiteral("cmdConservation"));
        cmdConservation->setGeometry(QRect(80, 210, 80, 23));
        layoutWidget5 = new QWidget(groupBox_4);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 30, 251, 163));
        verticalLayout_15 = new QVBoxLayout(layoutWidget5);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_18 = new QLabel(layoutWidget5);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_17->addWidget(label_18);

        txtOffset = new QLineEdit(layoutWidget5);
        txtOffset->setObjectName(QStringLiteral("txtOffset"));
        txtOffset->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_17->addWidget(txtOffset);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_19 = new QLabel(layoutWidget5);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_18->addWidget(label_19);

        txtChain = new QLineEdit(layoutWidget5);
        txtChain->setObjectName(QStringLiteral("txtChain"));
        txtChain->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_18->addWidget(txtChain);


        verticalLayout_5->addLayout(horizontalLayout_18);


        verticalLayout_7->addLayout(verticalLayout_5);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_28 = new QLabel(layoutWidget5);
        label_28->setObjectName(QStringLiteral("label_28"));

        horizontalLayout_24->addWidget(label_28);

        txtMinConserv = new QDoubleSpinBox(layoutWidget5);
        txtMinConserv->setObjectName(QStringLiteral("txtMinConserv"));
        txtMinConserv->setMaximumSize(QSize(60, 16777215));
        txtMinConserv->setMaximum(1);
        txtMinConserv->setSingleStep(0.01);
        txtMinConserv->setValue(0.8);

        horizontalLayout_24->addWidget(txtMinConserv);


        verticalLayout_7->addLayout(horizontalLayout_24);


        verticalLayout_15->addLayout(verticalLayout_7);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_17 = new QLabel(layoutWidget5);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_14->addWidget(label_17);

        cmbRefSeq_2 = new QComboBox(layoutWidget5);
        cmbRefSeq_2->setObjectName(QStringLiteral("cmbRefSeq_2"));
        cmbRefSeq_2->setMinimumSize(QSize(150, 0));

        verticalLayout_14->addWidget(cmbRefSeq_2);


        verticalLayout_15->addLayout(verticalLayout_14);

        layoutWidget6 = new QWidget(groupBox_4);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(321, 10, 258, 222));
        verticalLayout_16 = new QVBoxLayout(layoutWidget6);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_44 = new QLabel(layoutWidget6);
        label_44->setObjectName(QStringLiteral("label_44"));

        horizontalLayout_25->addWidget(label_44);

        cmdUploadConsRefsSeqs = new QPushButton(layoutWidget6);
        cmdUploadConsRefsSeqs->setObjectName(QStringLiteral("cmdUploadConsRefsSeqs"));
        cmdUploadConsRefsSeqs->setMaximumSize(QSize(20, 20));

        horizontalLayout_25->addWidget(cmdUploadConsRefsSeqs);


        verticalLayout_16->addLayout(horizontalLayout_25);

        lstRefSeqs = new QListWidget(layoutWidget6);
        lstRefSeqs->setObjectName(QStringLiteral("lstRefSeqs"));
        lstRefSeqs->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_16->addWidget(lstRefSeqs);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_21 = new QLabel(page_5);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(50, -10, 491, 131));
        label_21->setWordWrap(true);
        graficMinss = new QCustomPlot(page_5);
        graficMinss->setObjectName(QStringLiteral("graficMinss"));
        graficMinss->setGeometry(QRect(40, 190, 541, 291));
        layoutWidget7 = new QWidget(page_5);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(50, 120, 406, 54));
        verticalLayout_18 = new QVBoxLayout(layoutWidget7);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        lblNseq = new QLabel(layoutWidget7);
        lblNseq->setObjectName(QStringLiteral("lblNseq"));

        verticalLayout_18->addWidget(lblNseq);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_22 = new QLabel(layoutWidget7);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_19->addWidget(label_22);

        txtNoAlignments = new QSpinBox(layoutWidget7);
        txtNoAlignments->setObjectName(QStringLiteral("txtNoAlignments"));
        txtNoAlignments->setMinimumSize(QSize(60, 0));
        txtNoAlignments->setMaximum(10000);
        txtNoAlignments->setValue(100);

        horizontalLayout_19->addWidget(txtNoAlignments);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_8);

        cmdMinss = new QPushButton(layoutWidget7);
        cmdMinss->setObjectName(QStringLiteral("cmdMinss"));

        horizontalLayout_19->addWidget(cmdMinss);


        verticalLayout_18->addLayout(horizontalLayout_19);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        label_23 = new QLabel(page_6);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(50, -10, 491, 131));
        label_23->setWordWrap(true);
        cmdCorrelation = new QPushButton(page_6);
        cmdCorrelation->setObjectName(QStringLiteral("cmdCorrelation"));
        cmdCorrelation->setGeometry(QRect(90, 390, 99, 27));
        layoutWidget8 = new QWidget(page_6);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(50, 150, 187, 198));
        verticalLayout_17 = new QVBoxLayout(layoutWidget8);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_24 = new QLabel(layoutWidget8);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_20->addWidget(label_24);

        txtMinScore = new QSpinBox(layoutWidget8);
        txtMinScore->setObjectName(QStringLiteral("txtMinScore"));
        txtMinScore->setMaximumSize(QSize(60, 16777215));
        txtMinScore->setValue(10);

        horizontalLayout_20->addWidget(txtMinScore);


        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_25 = new QLabel(layoutWidget8);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_21->addWidget(label_25);

        txtMinssFraction = new QDoubleSpinBox(layoutWidget8);
        txtMinssFraction->setObjectName(QStringLiteral("txtMinssFraction"));
        txtMinssFraction->setMaximumSize(QSize(60, 16777215));
        txtMinssFraction->setMinimum(0.01);
        txtMinssFraction->setMaximum(1);
        txtMinssFraction->setSingleStep(0.01);
        txtMinssFraction->setValue(0.2);

        horizontalLayout_21->addWidget(txtMinssFraction);


        verticalLayout_6->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_26 = new QLabel(layoutWidget8);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_22->addWidget(label_26);

        txtMinDeltaFreq = new QDoubleSpinBox(layoutWidget8);
        txtMinDeltaFreq->setObjectName(QStringLiteral("txtMinDeltaFreq"));
        txtMinDeltaFreq->setMaximumSize(QSize(60, 16777215));
        txtMinDeltaFreq->setMinimum(0.01);
        txtMinDeltaFreq->setMaximum(1);
        txtMinDeltaFreq->setSingleStep(0.01);
        txtMinDeltaFreq->setValue(0.3);

        horizontalLayout_22->addWidget(txtMinDeltaFreq);


        verticalLayout_6->addLayout(horizontalLayout_22);


        verticalLayout_8->addLayout(verticalLayout_6);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_30 = new QLabel(layoutWidget8);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_26->addWidget(label_30);

        txtOffset_2 = new QLineEdit(layoutWidget8);
        txtOffset_2->setObjectName(QStringLiteral("txtOffset_2"));
        txtOffset_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_26->addWidget(txtOffset_2);


        verticalLayout_8->addLayout(horizontalLayout_26);


        verticalLayout_17->addLayout(verticalLayout_8);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_29 = new QLabel(layoutWidget8);
        label_29->setObjectName(QStringLiteral("label_29"));

        verticalLayout_10->addWidget(label_29);

        cmbRefSeq_3 = new QComboBox(layoutWidget8);
        cmbRefSeq_3->setObjectName(QStringLiteral("cmbRefSeq_3"));
        cmbRefSeq_3->setMinimumSize(QSize(150, 0));
        cmbRefSeq_3->setMaximumSize(QSize(150, 16777215));

        verticalLayout_10->addWidget(cmbRefSeq_3);


        verticalLayout_17->addLayout(verticalLayout_10);

        layoutWidget9 = new QWidget(page_6);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(292, 151, 281, 351));
        verticalLayout_9 = new QVBoxLayout(layoutWidget9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_31 = new QLabel(layoutWidget9);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayout_28->addWidget(label_31);

        cmdCorRefSeqs = new QPushButton(layoutWidget9);
        cmdCorRefSeqs->setObjectName(QStringLiteral("cmdCorRefSeqs"));
        cmdCorRefSeqs->setMaximumSize(QSize(20, 20));

        horizontalLayout_28->addWidget(cmdCorRefSeqs);


        verticalLayout_9->addLayout(horizontalLayout_28);

        lstRefSeqs_2 = new QListWidget(layoutWidget9);
        lstRefSeqs_2->setObjectName(QStringLiteral("lstRefSeqs_2"));
        lstRefSeqs_2->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_9->addWidget(lstRefSeqs_2);

        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QStringLiteral("page_7"));
        label_32 = new QLabel(page_7);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(50, -10, 491, 131));
        label_32->setWordWrap(true);
        stackedWidget2 = new QStackedWidget(page_7);
        stackedWidget2->setObjectName(QStringLiteral("stackedWidget2"));
        stackedWidget2->setGeometry(QRect(30, 80, 631, 391));
        page_8 = new QWidget();
        page_8->setObjectName(QStringLiteral("page_8"));
        groupBox_5 = new QGroupBox(page_8);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 30, 601, 351));
        cmdShow = new QPushButton(groupBox_5);
        cmdShow->setObjectName(QStringLiteral("cmdShow"));
        cmdShow->setGeometry(QRect(480, 310, 99, 27));
        layoutWidget10 = new QWidget(groupBox_5);
        layoutWidget10->setObjectName(QStringLiteral("layoutWidget10"));
        layoutWidget10->setGeometry(QRect(20, 50, 561, 181));
        horizontalLayout_27 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        checkResults1 = new QCheckBox(layoutWidget10);
        checkResults1->setObjectName(QStringLiteral("checkResults1"));

        verticalLayout_12->addWidget(checkResults1);

        checkResults2 = new QCheckBox(layoutWidget10);
        checkResults2->setObjectName(QStringLiteral("checkResults2"));

        verticalLayout_12->addWidget(checkResults2);

        checkResults3 = new QCheckBox(layoutWidget10);
        checkResults3->setObjectName(QStringLiteral("checkResults3"));

        verticalLayout_12->addWidget(checkResults3);

        checkResults4 = new QCheckBox(layoutWidget10);
        checkResults4->setObjectName(QStringLiteral("checkResults4"));
        checkResults4->setEnabled(true);

        verticalLayout_12->addWidget(checkResults4);

        checkResults5 = new QCheckBox(layoutWidget10);
        checkResults5->setObjectName(QStringLiteral("checkResults5"));

        verticalLayout_12->addWidget(checkResults5);


        horizontalLayout_27->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        checkResults6 = new QCheckBox(layoutWidget10);
        checkResults6->setObjectName(QStringLiteral("checkResults6"));

        verticalLayout_13->addWidget(checkResults6);

        checkResults7 = new QCheckBox(layoutWidget10);
        checkResults7->setObjectName(QStringLiteral("checkResults7"));

        verticalLayout_13->addWidget(checkResults7);

        checkResults8 = new QCheckBox(layoutWidget10);
        checkResults8->setObjectName(QStringLiteral("checkResults8"));

        verticalLayout_13->addWidget(checkResults8);

        checkResults9 = new QCheckBox(layoutWidget10);
        checkResults9->setObjectName(QStringLiteral("checkResults9"));

        verticalLayout_13->addWidget(checkResults9);

        checkResults10 = new QCheckBox(layoutWidget10);
        checkResults10->setObjectName(QStringLiteral("checkResults10"));
        checkResults10->setEnabled(true);

        verticalLayout_13->addWidget(checkResults10);


        horizontalLayout_27->addLayout(verticalLayout_13);

        lblHidden = new QLabel(groupBox_5);
        lblHidden->setObjectName(QStringLiteral("lblHidden"));
        lblHidden->setGeometry(QRect(450, 10, 67, 17));
        stackedWidget2->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QStringLiteral("page_9"));
        label_20 = new QLabel(page_9);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 10, 301, 17));
        lstProteinsFiltered = new QListWidget(page_9);
        lstProteinsFiltered->setObjectName(QStringLiteral("lstProteinsFiltered"));
        lstProteinsFiltered->setGeometry(QRect(20, 60, 161, 301));
        label_33 = new QLabel(page_9);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(30, 40, 67, 17));
        txtSequence = new QTextEdit(page_9);
        txtSequence->setObjectName(QStringLiteral("txtSequence"));
        txtSequence->setGeometry(QRect(200, 190, 421, 171));
        txtSequence->setReadOnly(true);
        label_34 = new QLabel(page_9);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(210, 170, 81, 17));
        lblRefSeq1 = new QLabel(page_9);
        lblRefSeq1->setObjectName(QStringLiteral("lblRefSeq1"));
        lblRefSeq1->setGeometry(QRect(210, 50, 351, 17));
        lblOccupancy = new QLabel(page_9);
        lblOccupancy->setObjectName(QStringLiteral("lblOccupancy"));
        lblOccupancy->setGeometry(QRect(210, 80, 161, 17));
        lblMinId = new QLabel(page_9);
        lblMinId->setObjectName(QStringLiteral("lblMinId"));
        lblMinId->setGeometry(QRect(210, 110, 191, 17));
        lblMaxId = new QLabel(page_9);
        lblMaxId->setObjectName(QStringLiteral("lblMaxId"));
        lblMaxId->setGeometry(QRect(210, 140, 191, 17));
        stackedWidget2->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName(QStringLiteral("page_10"));
        label_35 = new QLabel(page_10);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(10, 10, 231, 17));
        tableFreq = new QTableWidget(page_10);
        if (tableFreq->columnCount() < 22)
            tableFreq->setColumnCount(22);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(16, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(17, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(18, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(19, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(20, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableFreq->setHorizontalHeaderItem(21, __qtablewidgetitem21);
        tableFreq->setObjectName(QStringLiteral("tableFreq"));
        tableFreq->setGeometry(QRect(20, 90, 601, 291));
        tableFreq->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableFreq->setSortingEnabled(true);
        lblFilter = new QLabel(page_10);
        lblFilter->setObjectName(QStringLiteral("lblFilter"));
        lblFilter->setGeometry(QRect(300, 10, 281, 17));
        lblRefSeq = new QLabel(page_10);
        lblRefSeq->setObjectName(QStringLiteral("lblRefSeq"));
        lblRefSeq->setGeometry(QRect(10, 40, 281, 17));
        lblOffset = new QLabel(page_10);
        lblOffset->setObjectName(QStringLiteral("lblOffset"));
        lblOffset->setGeometry(QRect(300, 40, 91, 17));
        lblChain = new QLabel(page_10);
        lblChain->setObjectName(QStringLiteral("lblChain"));
        lblChain->setGeometry(QRect(450, 40, 91, 17));
        stackedWidget2->addWidget(page_10);
        page_11 = new QWidget();
        page_11->setObjectName(QStringLiteral("page_11"));
        lblRefSeq_2 = new QLabel(page_11);
        lblRefSeq_2->setObjectName(QStringLiteral("lblRefSeq_2"));
        lblRefSeq_2->setGeometry(QRect(10, 40, 281, 17));
        lblChain_2 = new QLabel(page_11);
        lblChain_2->setObjectName(QStringLiteral("lblChain_2"));
        lblChain_2->setGeometry(QRect(450, 40, 91, 17));
        lblFilter_2 = new QLabel(page_11);
        lblFilter_2->setObjectName(QStringLiteral("lblFilter_2"));
        lblFilter_2->setGeometry(QRect(300, 10, 281, 17));
        lblOffset_2 = new QLabel(page_11);
        lblOffset_2->setObjectName(QStringLiteral("lblOffset_2"));
        lblOffset_2->setGeometry(QRect(300, 40, 91, 17));
        label_36 = new QLabel(page_11);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(10, 10, 251, 17));
        tableFreqPerc = new QTableWidget(page_11);
        if (tableFreqPerc->columnCount() < 21)
            tableFreqPerc->setColumnCount(21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(7, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(8, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(9, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(10, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(11, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(12, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(13, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(14, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(15, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(16, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(17, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(18, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(19, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableFreqPerc->setHorizontalHeaderItem(20, __qtablewidgetitem42);
        tableFreqPerc->setObjectName(QStringLiteral("tableFreqPerc"));
        tableFreqPerc->setGeometry(QRect(20, 90, 601, 291));
        tableFreqPerc->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableFreqPerc->setSortingEnabled(true);
        stackedWidget2->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName(QStringLiteral("page_12"));
        label_37 = new QLabel(page_12);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(10, 10, 151, 17));
        tableConsRes = new QTableWidget(page_12);
        tableConsRes->setObjectName(QStringLiteral("tableConsRes"));
        tableConsRes->setGeometry(QRect(20, 90, 601, 291));
        lblFilter_8 = new QLabel(page_12);
        lblFilter_8->setObjectName(QStringLiteral("lblFilter_8"));
        lblFilter_8->setGeometry(QRect(300, 10, 281, 17));
        lblMinCons = new QLabel(page_12);
        lblMinCons->setObjectName(QStringLiteral("lblMinCons"));
        lblMinCons->setGeometry(QRect(300, 40, 251, 17));
        stackedWidget2->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName(QStringLiteral("page_13"));
        label_38 = new QLabel(page_13);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(10, 10, 281, 17));
        treeCorrelation = new QTreeWidget(page_13);
        treeCorrelation->setObjectName(QStringLiteral("treeCorrelation"));
        treeCorrelation->setGeometry(QRect(20, 50, 311, 311));
        lblFilter_3 = new QLabel(page_13);
        lblFilter_3->setObjectName(QStringLiteral("lblFilter_3"));
        lblFilter_3->setGeometry(QRect(350, 70, 251, 17));
        lblMinLogP = new QLabel(page_13);
        lblMinLogP->setObjectName(QStringLiteral("lblMinLogP"));
        lblMinLogP->setGeometry(QRect(350, 110, 201, 17));
        lblMinss = new QLabel(page_13);
        lblMinss->setObjectName(QStringLiteral("lblMinss"));
        lblMinss->setGeometry(QRect(350, 150, 191, 17));
        lblDeltaFreq = new QLabel(page_13);
        lblDeltaFreq->setObjectName(QStringLiteral("lblDeltaFreq"));
        lblDeltaFreq->setGeometry(QRect(350, 190, 221, 17));
        stackedWidget2->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QStringLiteral("page_14"));
        label_39 = new QLabel(page_14);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(10, 10, 151, 17));
        lblFilter_4 = new QLabel(page_14);
        lblFilter_4->setObjectName(QStringLiteral("lblFilter_4"));
        lblFilter_4->setGeometry(QRect(350, 70, 251, 17));
        lblMinLogP_2 = new QLabel(page_14);
        lblMinLogP_2->setObjectName(QStringLiteral("lblMinLogP_2"));
        lblMinLogP_2->setGeometry(QRect(350, 110, 201, 17));
        treeCorrelationComm = new QTreeWidget(page_14);
        treeCorrelationComm->setObjectName(QStringLiteral("treeCorrelationComm"));
        treeCorrelationComm->setGeometry(QRect(20, 50, 311, 311));
        lblDeltaFreq_2 = new QLabel(page_14);
        lblDeltaFreq_2->setObjectName(QStringLiteral("lblDeltaFreq_2"));
        lblDeltaFreq_2->setGeometry(QRect(350, 190, 221, 17));
        lblMinss_2 = new QLabel(page_14);
        lblMinss_2->setObjectName(QStringLiteral("lblMinss_2"));
        lblMinss_2->setGeometry(QRect(350, 150, 191, 17));
        stackedWidget2->addWidget(page_14);
        page_15 = new QWidget();
        page_15->setObjectName(QStringLiteral("page_15"));
        label_40 = new QLabel(page_15);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(10, 10, 241, 17));
        lblFilter_5 = new QLabel(page_15);
        lblFilter_5->setObjectName(QStringLiteral("lblFilter_5"));
        lblFilter_5->setGeometry(QRect(10, 40, 251, 17));
        lblMinLogP_3 = new QLabel(page_15);
        lblMinLogP_3->setObjectName(QStringLiteral("lblMinLogP_3"));
        lblMinLogP_3->setGeometry(QRect(250, 40, 201, 17));
        lblMinss_3 = new QLabel(page_15);
        lblMinss_3->setObjectName(QStringLiteral("lblMinss_3"));
        lblMinss_3->setGeometry(QRect(420, 40, 191, 17));
        lblDeltaFreq_3 = new QLabel(page_15);
        lblDeltaFreq_3->setObjectName(QStringLiteral("lblDeltaFreq_3"));
        lblDeltaFreq_3->setGeometry(QRect(420, 70, 221, 17));
        lblComunidade = new QLabel(page_15);
        lblComunidade->setObjectName(QStringLiteral("lblComunidade"));
        lblComunidade->setGeometry(QRect(10, 70, 151, 17));
        tableComm1 = new QTableWidget(page_15);
        tableComm1->setObjectName(QStringLiteral("tableComm1"));
        tableComm1->setGeometry(QRect(10, 100, 621, 291));
        tableComm1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableComm1->horizontalHeader()->setCascadingSectionResizes(false);
        tableComm1->verticalHeader()->setStretchLastSection(false);
        cmdNextComm = new QPushButton(page_15);
        cmdNextComm->setObjectName(QStringLiteral("cmdNextComm"));
        cmdNextComm->setGeometry(QRect(320, 70, 31, 27));
        cmdBackComm = new QPushButton(page_15);
        cmdBackComm->setObjectName(QStringLiteral("cmdBackComm"));
        cmdBackComm->setGeometry(QRect(280, 70, 31, 27));
        stackedWidget2->addWidget(page_15);
        page_16 = new QWidget();
        page_16->setObjectName(QStringLiteral("page_16"));
        label_41 = new QLabel(page_16);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(10, 10, 251, 17));
        lblMinss_4 = new QLabel(page_16);
        lblMinss_4->setObjectName(QStringLiteral("lblMinss_4"));
        lblMinss_4->setGeometry(QRect(420, 40, 191, 17));
        cmdBackComm_2 = new QPushButton(page_16);
        cmdBackComm_2->setObjectName(QStringLiteral("cmdBackComm_2"));
        cmdBackComm_2->setGeometry(QRect(280, 70, 31, 27));
        lblDeltaFreq_4 = new QLabel(page_16);
        lblDeltaFreq_4->setObjectName(QStringLiteral("lblDeltaFreq_4"));
        lblDeltaFreq_4->setGeometry(QRect(420, 70, 221, 17));
        lblComunidade_2 = new QLabel(page_16);
        lblComunidade_2->setObjectName(QStringLiteral("lblComunidade_2"));
        lblComunidade_2->setGeometry(QRect(10, 70, 151, 17));
        cmdNextComm_2 = new QPushButton(page_16);
        cmdNextComm_2->setObjectName(QStringLiteral("cmdNextComm_2"));
        cmdNextComm_2->setGeometry(QRect(320, 70, 31, 27));
        lblMinLogP_4 = new QLabel(page_16);
        lblMinLogP_4->setObjectName(QStringLiteral("lblMinLogP_4"));
        lblMinLogP_4->setGeometry(QRect(250, 40, 201, 17));
        lblFilter_6 = new QLabel(page_16);
        lblFilter_6->setObjectName(QStringLiteral("lblFilter_6"));
        lblFilter_6->setGeometry(QRect(10, 40, 251, 17));
        tableComm2 = new QTableWidget(page_16);
        tableComm2->setObjectName(QStringLiteral("tableComm2"));
        tableComm2->setGeometry(QRect(10, 100, 621, 291));
        tableComm2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableComm2->horizontalHeader()->setCascadingSectionResizes(false);
        tableComm2->verticalHeader()->setStretchLastSection(false);
        stackedWidget2->addWidget(page_16);
        page_17 = new QWidget();
        page_17->setObjectName(QStringLiteral("page_17"));
        label_42 = new QLabel(page_17);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(10, 10, 141, 17));
        lblFilter_7 = new QLabel(page_17);
        lblFilter_7->setObjectName(QStringLiteral("lblFilter_7"));
        lblFilter_7->setGeometry(QRect(10, 40, 251, 17));
        tableAdherence = new QTableWidget(page_17);
        tableAdherence->setObjectName(QStringLiteral("tableAdherence"));
        tableAdherence->setGeometry(QRect(10, 70, 621, 291));
        tableAdherence->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableAdherence->setSortingEnabled(true);
        tableAdherence->horizontalHeader()->setVisible(false);
        tableAdherence->horizontalHeader()->setCascadingSectionResizes(false);
        tableAdherence->verticalHeader()->setStretchLastSection(false);
        stackedWidget2->addWidget(page_17);
        page_18 = new QWidget();
        page_18->setObjectName(QStringLiteral("page_18"));
        label_43 = new QLabel(page_18);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(10, 10, 191, 17));
        tableResiduesComm = new QTableWidget(page_18);
        tableResiduesComm->setObjectName(QStringLiteral("tableResiduesComm"));
        tableResiduesComm->setGeometry(QRect(10, 80, 621, 311));
        cmdNextResComm = new QPushButton(page_18);
        cmdNextResComm->setObjectName(QStringLiteral("cmdNextResComm"));
        cmdNextResComm->setGeometry(QRect(320, 50, 31, 27));
        cmdBackResComm = new QPushButton(page_18);
        cmdBackResComm->setObjectName(QStringLiteral("cmdBackResComm"));
        cmdBackResComm->setGeometry(QRect(280, 50, 31, 27));
        lblComunidade_3 = new QLabel(page_18);
        lblComunidade_3->setObjectName(QStringLiteral("lblComunidade_3"));
        lblComunidade_3->setGeometry(QRect(10, 50, 151, 17));
        lblFilter_9 = new QLabel(page_18);
        lblFilter_9->setObjectName(QStringLiteral("lblFilter_9"));
        lblFilter_9->setGeometry(QRect(300, 10, 261, 17));
        stackedWidget2->addWidget(page_18);
        cmdNextResult = new QPushButton(page_7);
        cmdNextResult->setObjectName(QStringLiteral("cmdNextResult"));
        cmdNextResult->setGeometry(QRect(370, 480, 101, 27));
        cmdBackResult = new QPushButton(page_7);
        cmdBackResult->setObjectName(QStringLiteral("cmdBackResult"));
        cmdBackResult->setGeometry(QRect(248, 480, 101, 27));
        stackedWidget->addWidget(page_7);
        page_19 = new QWidget();
        page_19->setObjectName(QStringLiteral("page_19"));
        label_47 = new QLabel(page_19);
        label_47->setObjectName(QStringLiteral("label_47"));
        label_47->setGeometry(QRect(50, -10, 491, 131));
        label_47->setWordWrap(true);
        groupBox_6 = new QGroupBox(page_19);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(40, 170, 481, 81));
        widget = new QWidget(groupBox_6);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 40, 237, 24));
        horizontalLayout_29 = new QHBoxLayout(widget);
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 0, 0, 0);
        chkConserveds = new QCheckBox(widget);
        chkConserveds->setObjectName(QStringLiteral("chkConserveds"));
        chkConserveds->setChecked(false);

        horizontalLayout_29->addWidget(chkConserveds);

        chkComm = new QCheckBox(widget);
        chkComm->setObjectName(QStringLiteral("chkComm"));

        horizontalLayout_29->addWidget(chkComm);

        groupBox_7 = new QGroupBox(page_19);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(40, 290, 481, 81));
        widget1 = new QWidget(groupBox_7);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 40, 242, 24));
        horizontalLayout_30 = new QHBoxLayout(widget1);
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        radioGroupBy1 = new QRadioButton(widget1);
        radioGroupBy1->setObjectName(QStringLiteral("radioGroupBy1"));

        horizontalLayout_30->addWidget(radioGroupBy1);

        radioGroupBy2 = new QRadioButton(widget1);
        radioGroupBy2->setObjectName(QStringLiteral("radioGroupBy2"));

        horizontalLayout_30->addWidget(radioGroupBy2);

        label_48 = new QLabel(page_19);
        label_48->setObjectName(QStringLiteral("label_48"));
        label_48->setGeometry(QRect(50, 80, 381, 41));
        cmdLook = new QPushButton(page_19);
        cmdLook->setObjectName(QStringLiteral("cmdLook"));
        cmdLook->setGeometry(QRect(380, 410, 99, 27));
        stackedWidget->addWidget(page_19);
        layoutWidget11 = new QWidget(centralWidget);
        layoutWidget11->setObjectName(QStringLiteral("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(417, 540, 531, 29));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        cmdMain = new QPushButton(layoutWidget11);
        cmdMain->setObjectName(QStringLiteral("cmdMain"));
        cmdMain->setEnabled(true);
        cmdMain->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdMain);

        cmdBack = new QPushButton(layoutWidget11);
        cmdBack->setObjectName(QStringLiteral("cmdBack"));
        cmdBack->setEnabled(true);
        cmdBack->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdBack);

        cmdAdvance = new QPushButton(layoutWidget11);
        cmdAdvance->setObjectName(QStringLiteral("cmdAdvance"));
        cmdAdvance->setEnabled(true);
        cmdAdvance->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdAdvance);

        cmdSaveResults = new QPushButton(layoutWidget11);
        cmdSaveResults->setObjectName(QStringLiteral("cmdSaveResults"));

        horizontalLayout_9->addWidget(cmdSaveResults);

        cmdShowResults = new QPushButton(layoutWidget11);
        cmdShowResults->setObjectName(QStringLiteral("cmdShowResults"));

        horizontalLayout_9->addWidget(cmdShowResults);

        layoutWidget12 = new QWidget(centralWidget);
        layoutWidget12->setObjectName(QStringLiteral("layoutWidget12"));
        layoutWidget12->setGeometry(QRect(11, 10, 258, 551));
        verticalLayout_11 = new QVBoxLayout(layoutWidget12);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_45 = new QLabel(layoutWidget12);
        label_45->setObjectName(QStringLiteral("label_45"));

        horizontalLayout_23->addWidget(label_45);

        cmdRemoveAlignment = new QPushButton(layoutWidget12);
        cmdRemoveAlignment->setObjectName(QStringLiteral("cmdRemoveAlignment"));
        cmdRemoveAlignment->setMinimumSize(QSize(20, 20));
        cmdRemoveAlignment->setMaximumSize(QSize(20, 20));

        horizontalLayout_23->addWidget(cmdRemoveAlignment);


        verticalLayout_11->addLayout(horizontalLayout_23);

        listWidget = new QListWidget(layoutWidget12);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(300, 150));

        verticalLayout_11->addWidget(listWidget);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_46 = new QLabel(layoutWidget12);
        label_46->setObjectName(QStringLiteral("label_46"));

        horizontalLayout_16->addWidget(label_46);

        cmdRemoveFilter = new QPushButton(layoutWidget12);
        cmdRemoveFilter->setObjectName(QStringLiteral("cmdRemoveFilter"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdRemoveFilter->sizePolicy().hasHeightForWidth());
        cmdRemoveFilter->setSizePolicy(sizePolicy);
        cmdRemoveFilter->setMinimumSize(QSize(20, 20));
        cmdRemoveFilter->setMaximumSize(QSize(20, 20));

        horizontalLayout_16->addWidget(cmdRemoveFilter);


        verticalLayout_11->addLayout(horizontalLayout_16);

        listWidget2 = new QListWidget(layoutWidget12);
        listWidget2->setObjectName(QStringLiteral("listWidget2"));

        verticalLayout_11->addWidget(listWidget2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 983, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuMethod = new QMenu(menuBar);
        menuMethod->setObjectName(QStringLiteral("menuMethod"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuShow = new QMenu(menuBar);
        menuShow->setObjectName(QStringLiteral("menuShow"));
        menuExport = new QMenu(menuBar);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuAlignment = new QMenu(menuExport);
        menuAlignment->setObjectName(QStringLiteral("menuAlignment"));
        menuFrequence_Conservation = new QMenu(menuExport);
        menuFrequence_Conservation->setObjectName(QStringLiteral("menuFrequence_Conservation"));
        menuFrequence_Conservation_2 = new QMenu(menuExport);
        menuFrequence_Conservation_2->setObjectName(QStringLiteral("menuFrequence_Conservation_2"));
        menuConserved_Residues = new QMenu(menuExport);
        menuConserved_Residues->setObjectName(QStringLiteral("menuConserved_Residues"));
        menuCorrelation_List = new QMenu(menuExport);
        menuCorrelation_List->setObjectName(QStringLiteral("menuCorrelation_List"));
        menuCommunities = new QMenu(menuExport);
        menuCommunities->setObjectName(QStringLiteral("menuCommunities"));
        menuCorrelation_Tables = new QMenu(menuExport);
        menuCorrelation_Tables->setObjectName(QStringLiteral("menuCorrelation_Tables"));
        menuCorrelation_Tables_Log_P = new QMenu(menuExport);
        menuCorrelation_Tables_Log_P->setObjectName(QStringLiteral("menuCorrelation_Tables_Log_P"));
        menuAdherence_Matrix = new QMenu(menuExport);
        menuAdherence_Matrix->setObjectName(QStringLiteral("menuAdherence_Matrix"));
        menuResidues_Of_Communities = new QMenu(menuExport);
        menuResidues_Of_Communities->setObjectName(QStringLiteral("menuResidues_Of_Communities"));
        menuConservation_Reference_Sequences = new QMenu(menuExport);
        menuConservation_Reference_Sequences->setObjectName(QStringLiteral("menuConservation_Reference_Sequences"));
        menuCorrelation_Reference_Sequences = new QMenu(menuExport);
        menuCorrelation_Reference_Sequences->setObjectName(QStringLiteral("menuCorrelation_Reference_Sequences"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMethod->menuAction());
        menuBar->addAction(menuExport->menuAction());
        menuBar->addAction(menuShow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_XML);
        menuFile->addSeparator();
        menuFile->addAction(actionInput_Alignment);
        menuFile->addAction(actionClose_Alignment);
        menuFile->addSeparator();
        menuFile->addAction(actionShow_Results);
        menuFile->addAction(actionSave_Results);
        menuMethod->addAction(actionStart_Wizard);
        menuMethod->addSeparator();
        menuMethod->addAction(actionFilter_Alignment);
        menuMethod->addAction(actionConservation);
        menuMethod->addAction(actionMinss);
        menuMethod->addAction(actionCorrelation);
        menuMethod->addSeparator();
        menuMethod->addAction(actionUniprotLooking);
        menuHelp->addAction(actionAbout);
        menuShow->addAction(actionResults_Table);
        menuShow->addAction(actionConservation_Scatterplot);
        menuShow->addAction(actionConserved_Residues_in_Structure);
        menuShow->addAction(actionCommunities_Graph);
        menuExport->addAction(menuAlignment->menuAction());
        menuExport->addSeparator();
        menuExport->addAction(menuFrequence_Conservation->menuAction());
        menuExport->addAction(menuFrequence_Conservation_2->menuAction());
        menuExport->addAction(menuConserved_Residues->menuAction());
        menuExport->addAction(menuConservation_Reference_Sequences->menuAction());
        menuExport->addSeparator();
        menuExport->addAction(menuCorrelation_List->menuAction());
        menuExport->addAction(menuCommunities->menuAction());
        menuExport->addAction(menuCorrelation_Tables->menuAction());
        menuExport->addAction(menuCorrelation_Tables_Log_P->menuAction());
        menuExport->addAction(menuAdherence_Matrix->menuAction());
        menuExport->addAction(menuResidues_Of_Communities->menuAction());
        menuExport->addAction(menuCorrelation_Reference_Sequences->menuAction());
        menuAlignment->addAction(actionAlignmentPFAM);
        menuAlignment->addAction(actionAlignmentTXT);
        menuAlignment->addAction(actionAlignmentXML);
        menuFrequence_Conservation->addSeparator();
        menuFrequence_Conservation->addAction(actionFreqTXT);
        menuFrequence_Conservation->addAction(actionFreqCSV);
        menuFrequence_Conservation->addAction(actionFreqXML);
        menuFrequence_Conservation->addAction(actionFreqHTML);
        menuFrequence_Conservation_2->addAction(actionFreqPercTXT);
        menuFrequence_Conservation_2->addAction(actionFreqPercCSV);
        menuFrequence_Conservation_2->addAction(actionFreqPercXML);
        menuFrequence_Conservation_2->addAction(actionFreqPercHTML);
        menuConserved_Residues->addAction(actionConsResTXT);
        menuConserved_Residues->addAction(actionConsResXML);
        menuConserved_Residues->addAction(actionConsResHTML);
        menuCorrelation_List->addAction(actionCorrListTXT);
        menuCorrelation_List->addAction(actionCorrListCSV);
        menuCorrelation_List->addAction(actionCorrListXML);
        menuCommunities->addAction(actionCommTXT);
        menuCommunities->addAction(actionCommXML);
        menuCorrelation_Tables->addAction(actionCorrTablePercTXT);
        menuCorrelation_Tables->addAction(actionCorrTablePercXML);
        menuCorrelation_Tables->addAction(actionCorrTablePercHTML);
        menuCorrelation_Tables_Log_P->addAction(actionCorrTableTXT);
        menuCorrelation_Tables_Log_P->addAction(actionCorrTableXML);
        menuCorrelation_Tables_Log_P->addAction(actionCorrTableHTML);
        menuAdherence_Matrix->addAction(actionAdhTXT);
        menuAdherence_Matrix->addAction(actionAdhCSV);
        menuAdherence_Matrix->addAction(actionAdhXML);
        menuAdherence_Matrix->addAction(actionAdhHTML);
        menuResidues_Of_Communities->addAction(actionResCommTXT);
        menuResidues_Of_Communities->addAction(actionResCommXML);
        menuResidues_Of_Communities->addAction(actionResCommHTML);
        menuConservation_Reference_Sequences->addAction(actionConsRefsTXT);
        menuConservation_Reference_Sequences->addAction(actionConsRefsXML);
        menuCorrelation_Reference_Sequences->addAction(actionCorrRefsTXT);
        menuCorrelation_Reference_Sequences->addAction(actionCorrRefsXML);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(7);
        stackedWidget2->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PFStats", 0));
        actionInput_Alignment->setText(QApplication::translate("MainWindow", "Input Alignment", 0));
        actionFetch_From_PFAM->setText(QApplication::translate("MainWindow", "Fetch From PFAM", 0));
        actionExport_Alignment->setText(QApplication::translate("MainWindow", "Export Alignment", 0));
        actionFilter_Alignment->setText(QApplication::translate("MainWindow", "Filter Alignment", 0));
        actionCalculate_Minimum_Sub_Alignment_Size->setText(QApplication::translate("MainWindow", "Calculate Minimum Sub-Alignment Size", 0));
        actionCalculate_Correlation_Scores->setText(QApplication::translate("MainWindow", "Calculate Correlation Scores", 0));
        actionDecompose_Network->setText(QApplication::translate("MainWindow", "Decompose Network", 0));
        actionAnalyze_Conservation_Sets->setText(QApplication::translate("MainWindow", "Analyze Conservation Sets", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionClose_Alignment->setText(QApplication::translate("MainWindow", "Close Alignment", 0));
        actionOpen_XML->setText(QApplication::translate("MainWindow", "Open XML", 0));
        actionAlignmentPFAM->setText(QApplication::translate("MainWindow", "PFAM", 0));
        actionAlignmentTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionAlignmentXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionFreqTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionFreqCSV->setText(QApplication::translate("MainWindow", "CSV", 0));
        actionFreqXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionFreqHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionFreqPercTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionFreqPercCSV->setText(QApplication::translate("MainWindow", "CSV", 0));
        actionFreqPercXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionFreqPercHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionResults_Table->setText(QApplication::translate("MainWindow", "Results Table", 0));
        actionConservation_Scatterplot->setText(QApplication::translate("MainWindow", "Conservation Scatterplot", 0));
        actionCommunities_Graph->setText(QApplication::translate("MainWindow", "Communities Graph", 0));
        actionConserved_Residues_in_Structure->setText(QApplication::translate("MainWindow", "Conserved Residues in Structure", 0));
        actionConsResXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionConsResHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionConsResTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCorrListTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCorrListCSV->setText(QApplication::translate("MainWindow", "CSV", 0));
        actionCorrListXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionCommTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCommXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionCorrTablePercTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCorrTablePercXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionCorrTablePercHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionCorrTableTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCorrTableXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionCorrTableHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionAdhTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionAdhCSV->setText(QApplication::translate("MainWindow", "CSV", 0));
        actionAdhXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionAdhHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionResCommTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionResCommXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionResCommHTML->setText(QApplication::translate("MainWindow", "HTML", 0));
        actionConsRefsTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionConsRefsXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionCorrRefsTXT->setText(QApplication::translate("MainWindow", "TXT", 0));
        actionCorrRefsXML->setText(QApplication::translate("MainWindow", "XML", 0));
        actionConservation->setText(QApplication::translate("MainWindow", "Conservation", 0));
        actionMinss->setText(QApplication::translate("MainWindow", "Minss", 0));
        actionCorrelation->setText(QApplication::translate("MainWindow", "Correlation", 0));
        actionShow_Results->setText(QApplication::translate("MainWindow", "Show Results", 0));
        actionSave_Results->setText(QApplication::translate("MainWindow", "Save Results", 0));
        actionStart_Wizard->setText(QApplication::translate("MainWindow", "Start Wizard", 0));
        actionUniprotLooking->setText(QApplication::translate("MainWindow", "Uniprot Looking Tool", 0));
        label->setText(QApplication::translate("MainWindow", "<h1>PFstats</h1>\n"
"<p>PFstats contains a set of functions that you can use to analyze correlation and conservation in protein sequences.</p>\n"
"<p>You can choose navigate through these functions in the menu bar or just start the wizard at the bottom of this window.</p>", 0));
        cmdStartWizard->setText(QApplication::translate("MainWindow", "Start Wizard", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Getting An Alignment</span></p><p>You can Choose from get an Alignment from your own computer or directly from PFAM</p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Get from desktop", 0));
        cmdOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Get from PFAM", 0));
        label_6->setText(QApplication::translate("MainWindow", "Fetch data from PFAM:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Accession:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Alignment:", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Seed", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Full", 0));
        label_4->setText(QApplication::translate("MainWindow", "Order:", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Tree", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Alphabetical", 0));
        label_7->setText(QApplication::translate("MainWindow", "Sequence:", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Inserts lower case", 0));
        radioButton_6->setText(QApplication::translate("MainWindow", "All upper case", 0));
        label_8->setText(QApplication::translate("MainWindow", "Gaps:", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "Dashes (-)", 0));
        radioButton_8->setText(QApplication::translate("MainWindow", "Dots (.)", 0));
        radioButton_9->setText(QApplication::translate("MainWindow", "Mixed (- or .)", 0));
        radioButton_10->setText(QApplication::translate("MainWindow", "No gaps", 0));
        cmdFetch->setText(QApplication::translate("MainWindow", "Fetch", 0));
        label_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Filtering Alignment</span></p><p>Even high quality alignments such as those available in PFAM usually need some filtering in order to eliminate or minimize known problems.</p></body></html>", 0));
        cmdApplyFilter->setText(QApplication::translate("MainWindow", "Apply", 0));
        label_27->setText(QApplication::translate("MainWindow", "(Full Alignment)", 0));
        label_10->setText(QApplication::translate("MainWindow", "Reference Sequence:", 0));
        label_11->setText(QApplication::translate("MainWindow", "Minimum Coverage:", 0));
        label_12->setText(QApplication::translate("MainWindow", "Minimu Identy:", 0));
        label_13->setText(QApplication::translate("MainWindow", "Maximum Identy:", 0));
        chkIntermediateFilter->setText(QApplication::translate("MainWindow", "Generate intermediate filters", 0));
        label_14->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Conservation</span></p><p>A series of simple frequency-based calculations are done using conservation.</p><p>At this step, you might need a PDB file, you can get one by visiting <span style=\" font-style:italic;\">pdb.org</span> or fetching from here.</p></body></html>", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "PDB File", 0));
        cmdPDBfromFile->setText(QApplication::translate("MainWindow", "Choose from file", 0));
        label_15->setText(QApplication::translate("MainWindow", "File Path:", 0));
        label_16->setText(QApplication::translate("MainWindow", "PDB Name:", 0));
        cmdFetchPDB->setText(QApplication::translate("MainWindow", "Fetch from internet", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Conservation", 0));
        cmdConservation->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_18->setText(QApplication::translate("MainWindow", "Offset:", 0));
        txtOffset->setText(QApplication::translate("MainWindow", "0", 0));
        label_19->setText(QApplication::translate("MainWindow", "Chain:", 0));
        txtChain->setText(QApplication::translate("MainWindow", "A", 0));
        label_28->setText(QApplication::translate("MainWindow", "Minumum Conservation:", 0));
        label_17->setText(QApplication::translate("MainWindow", "Main Reference Sequence:", 0));
        label_44->setText(QApplication::translate("MainWindow", "Secundary Reference Sequences:", 0));
        cmdUploadConsRefsSeqs->setText(QApplication::translate("MainWindow", "+", 0));
        label_21->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Minss</span></p><p>This module implements the procedure described in (Dima and Thirumalai 2006). It calculates the average conservation for the full alignment and then for multiple sub-alignments with decreasing sizes. </p></body></html>", 0));
        lblNseq->setText(QApplication::translate("MainWindow", "Number of sequences in the alignment: ", 0));
        label_22->setText(QApplication::translate("MainWindow", "Number of sub-alignments:", 0));
        cmdMinss->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_23->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Correlation</span></p><p>This will calculate a set of correlation scores for the full alignment, using the cutoffs provided by the user. </p></body></html>", 0));
        cmdCorrelation->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_24->setText(QApplication::translate("MainWindow", "Minimum Score:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Minss Fraction:", 0));
        label_26->setText(QApplication::translate("MainWindow", "Minumum Delta:", 0));
        label_30->setText(QApplication::translate("MainWindow", "Offset:", 0));
        txtOffset_2->setText(QApplication::translate("MainWindow", "0", 0));
        label_29->setText(QApplication::translate("MainWindow", "Reference Sequence:", 0));
        label_31->setText(QApplication::translate("MainWindow", "Secundary Reference Sequences:", 0));
        cmdCorRefSeqs->setText(QApplication::translate("MainWindow", "+", 0));
        label_32->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Results</span></p>\n"
"</body></html>", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Check the results that you want to visualize", 0));
        cmdShow->setText(QApplication::translate("MainWindow", "Show", 0));
        checkResults1->setText(QApplication::translate("MainWindow", "List of sequences after filter", 0));
        checkResults2->setText(QApplication::translate("MainWindow", "Table of frequence conservation", 0));
        checkResults3->setText(QApplication::translate("MainWindow", "Table of percentage conservation", 0));
        checkResults4->setText(QApplication::translate("MainWindow", "Conserved Residues", 0));
        checkResults5->setText(QApplication::translate("MainWindow", "Correlation and Anti-Correlation list", 0));
        checkResults6->setText(QApplication::translate("MainWindow", "List of Communities", 0));
        checkResults7->setText(QApplication::translate("MainWindow", "Correlation Tables (Percentage)", 0));
        checkResults8->setText(QApplication::translate("MainWindow", "Correlation Tables (Log P scores)", 0));
        checkResults9->setText(QApplication::translate("MainWindow", "Adherence matrix", 0));
        checkResults10->setText(QApplication::translate("MainWindow", "Residues of communities", 0));
        lblHidden->setText(QApplication::translate("MainWindow", "0", 0));
        label_20->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">List of sequences after filters</span></p></body></html>", 0));
        label_33->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Proteins:</span></p></body></html>", 0));
        label_34->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Sequence:</span></p></body></html>", 0));
        lblRefSeq1->setText(QApplication::translate("MainWindow", "Reference Sequence:", 0));
        lblOccupancy->setText(QApplication::translate("MainWindow", "Occupancy: ", 0));
        lblMinId->setText(QApplication::translate("MainWindow", "Minimum Identity: ", 0));
        lblMaxId->setText(QApplication::translate("MainWindow", "Maximum Identity: ", 0));
        label_35->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Table of frequence conservation</span></p></body></html>", 0));
        QTableWidgetItem *___qtablewidgetitem = tableFreq->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Pos", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableFreq->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "GAP", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableFreq->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "ALA", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableFreq->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "CYS", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableFreq->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "ASP", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableFreq->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "GLU", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableFreq->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "PHE", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableFreq->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "GLY", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableFreq->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "HIS", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableFreq->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "ILE", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableFreq->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "LYS", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableFreq->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "LEU", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableFreq->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "MET", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableFreq->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "ASN", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableFreq->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "PRO", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableFreq->horizontalHeaderItem(15);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "GLN", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableFreq->horizontalHeaderItem(16);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "ARG", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableFreq->horizontalHeaderItem(17);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "SER", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableFreq->horizontalHeaderItem(18);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "THR", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableFreq->horizontalHeaderItem(19);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "VAL", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableFreq->horizontalHeaderItem(20);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "TRP", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableFreq->horizontalHeaderItem(21);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "TYR", 0));
        lblFilter->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblRefSeq->setText(QApplication::translate("MainWindow", "Reference Sequence: ", 0));
        lblOffset->setText(QApplication::translate("MainWindow", "Offset: ", 0));
        lblChain->setText(QApplication::translate("MainWindow", "Chain: ", 0));
        lblRefSeq_2->setText(QApplication::translate("MainWindow", "Reference Sequence: ", 0));
        lblChain_2->setText(QApplication::translate("MainWindow", "Chain: ", 0));
        lblFilter_2->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblOffset_2->setText(QApplication::translate("MainWindow", "Offset: ", 0));
        label_36->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Table of percentage conservation</span></p></body></html>", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableFreqPerc->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "Pos", 0));
        QTableWidgetItem *___qtablewidgetitem23 = tableFreqPerc->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "ALA", 0));
        QTableWidgetItem *___qtablewidgetitem24 = tableFreqPerc->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "CYS", 0));
        QTableWidgetItem *___qtablewidgetitem25 = tableFreqPerc->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "ASP", 0));
        QTableWidgetItem *___qtablewidgetitem26 = tableFreqPerc->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "GLU", 0));
        QTableWidgetItem *___qtablewidgetitem27 = tableFreqPerc->horizontalHeaderItem(5);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "PHE", 0));
        QTableWidgetItem *___qtablewidgetitem28 = tableFreqPerc->horizontalHeaderItem(6);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "GLY", 0));
        QTableWidgetItem *___qtablewidgetitem29 = tableFreqPerc->horizontalHeaderItem(7);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "HIS", 0));
        QTableWidgetItem *___qtablewidgetitem30 = tableFreqPerc->horizontalHeaderItem(8);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "ILE", 0));
        QTableWidgetItem *___qtablewidgetitem31 = tableFreqPerc->horizontalHeaderItem(9);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "LYS", 0));
        QTableWidgetItem *___qtablewidgetitem32 = tableFreqPerc->horizontalHeaderItem(10);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "LEU", 0));
        QTableWidgetItem *___qtablewidgetitem33 = tableFreqPerc->horizontalHeaderItem(11);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "MET", 0));
        QTableWidgetItem *___qtablewidgetitem34 = tableFreqPerc->horizontalHeaderItem(12);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "ASN", 0));
        QTableWidgetItem *___qtablewidgetitem35 = tableFreqPerc->horizontalHeaderItem(13);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "PRO", 0));
        QTableWidgetItem *___qtablewidgetitem36 = tableFreqPerc->horizontalHeaderItem(14);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "GLN", 0));
        QTableWidgetItem *___qtablewidgetitem37 = tableFreqPerc->horizontalHeaderItem(15);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "ARG", 0));
        QTableWidgetItem *___qtablewidgetitem38 = tableFreqPerc->horizontalHeaderItem(16);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "SER", 0));
        QTableWidgetItem *___qtablewidgetitem39 = tableFreqPerc->horizontalHeaderItem(17);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "THR", 0));
        QTableWidgetItem *___qtablewidgetitem40 = tableFreqPerc->horizontalHeaderItem(18);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "VAL", 0));
        QTableWidgetItem *___qtablewidgetitem41 = tableFreqPerc->horizontalHeaderItem(19);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "TRP", 0));
        QTableWidgetItem *___qtablewidgetitem42 = tableFreqPerc->horizontalHeaderItem(20);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "TYR", 0));
        label_37->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Conserved Residues</span></p></body></html>", 0));
        lblFilter_8->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblMinCons->setText(QApplication::translate("MainWindow", "Minimum Conservation: ", 0));
        label_38->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Correlation and Anti-Correlation list</span></p></body></html>", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeCorrelation->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Score", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Residue 2", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Residue 1", 0));
        lblFilter_3->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblMinLogP->setText(QApplication::translate("MainWindow", "Minimum Score: ", 0));
        lblMinss->setText(QApplication::translate("MainWindow", "Minss Fraction: ", 0));
        lblDeltaFreq->setText(QApplication::translate("MainWindow", "Delta Frequence: ", 0));
        label_39->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">List of Communities</span></p></body></html>", 0));
        lblFilter_4->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblMinLogP_2->setText(QApplication::translate("MainWindow", "Minimum Score: ", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = treeCorrelationComm->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Communities", 0));
        lblDeltaFreq_2->setText(QApplication::translate("MainWindow", "Delta Frequence: ", 0));
        lblMinss_2->setText(QApplication::translate("MainWindow", "Minss Fraction: ", 0));
        label_40->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Correlation Tables (Percentage)</span></p></body></html>", 0));
        lblFilter_5->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        lblMinLogP_3->setText(QApplication::translate("MainWindow", "Minimum Score: ", 0));
        lblMinss_3->setText(QApplication::translate("MainWindow", "Minss Fraction: ", 0));
        lblDeltaFreq_3->setText(QApplication::translate("MainWindow", "Delta Frequence: ", 0));
        lblComunidade->setText(QApplication::translate("MainWindow", "Comunidade ", 0));
        cmdNextComm->setText(QApplication::translate("MainWindow", ">", 0));
        cmdBackComm->setText(QApplication::translate("MainWindow", "<", 0));
        label_41->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Correlation Tables (Log P scores)</span></p></body></html>", 0));
        lblMinss_4->setText(QApplication::translate("MainWindow", "Minss Fraction: ", 0));
        cmdBackComm_2->setText(QApplication::translate("MainWindow", "<", 0));
        lblDeltaFreq_4->setText(QApplication::translate("MainWindow", "Delta Frequence: ", 0));
        lblComunidade_2->setText(QApplication::translate("MainWindow", "Comunidade ", 0));
        cmdNextComm_2->setText(QApplication::translate("MainWindow", ">", 0));
        lblMinLogP_4->setText(QApplication::translate("MainWindow", "Minimum Score: ", 0));
        lblFilter_6->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        label_42->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Adherence matrix</span></p></body></html>", 0));
        lblFilter_7->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        label_43->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Residues of communities</span></p></body></html>", 0));
        cmdNextResComm->setText(QApplication::translate("MainWindow", ">", 0));
        cmdBackResComm->setText(QApplication::translate("MainWindow", "<", 0));
        lblComunidade_3->setText(QApplication::translate("MainWindow", "Comunidade ", 0));
        lblFilter_9->setText(QApplication::translate("MainWindow", "Filter: ", 0));
        cmdNextResult->setText(QApplication::translate("MainWindow", "Next Result", 0));
        cmdBackResult->setText(QApplication::translate("MainWindow", "Back Result", 0));
        label_47->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Uniprot Looking Tool</span></p></body></html>", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Target Residues", 0));
        chkConserveds->setText(QApplication::translate("MainWindow", "Conserveds", 0));
        chkComm->setText(QApplication::translate("MainWindow", "Communities", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Group By", 0));
        radioGroupBy1->setText(QApplication::translate("MainWindow", "Residues", 0));
        radioGroupBy2->setText(QApplication::translate("MainWindow", "Proteins", 0));
        label_48->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">This method requires internet connection.</span></p></body></html>", 0));
        cmdLook->setText(QApplication::translate("MainWindow", "Search", 0));
        cmdMain->setText(QApplication::translate("MainWindow", "Main", 0));
        cmdBack->setText(QApplication::translate("MainWindow", "Back", 0));
        cmdAdvance->setText(QApplication::translate("MainWindow", "Advance", 0));
        cmdSaveResults->setText(QApplication::translate("MainWindow", "Save Results", 0));
        cmdShowResults->setText(QApplication::translate("MainWindow", "Show Results", 0));
        label_45->setText(QApplication::translate("MainWindow", "Alignment:", 0));
        cmdRemoveAlignment->setText(QApplication::translate("MainWindow", "-", 0));
        label_46->setText(QApplication::translate("MainWindow", "Filter:", 0));
        cmdRemoveFilter->setText(QApplication::translate("MainWindow", "-", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuMethod->setTitle(QApplication::translate("MainWindow", "Methods", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuShow->setTitle(QApplication::translate("MainWindow", "Visualize", 0));
        menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0));
        menuAlignment->setTitle(QApplication::translate("MainWindow", "Alignment", 0));
        menuFrequence_Conservation->setTitle(QApplication::translate("MainWindow", "Frequence Conservation", 0));
        menuFrequence_Conservation_2->setTitle(QApplication::translate("MainWindow", "Frequence Conservation (%)", 0));
        menuConserved_Residues->setTitle(QApplication::translate("MainWindow", "Conserved Residues", 0));
        menuCorrelation_List->setTitle(QApplication::translate("MainWindow", "Correlation List", 0));
        menuCommunities->setTitle(QApplication::translate("MainWindow", "Communities", 0));
        menuCorrelation_Tables->setTitle(QApplication::translate("MainWindow", "Correlation Tables (%)", 0));
        menuCorrelation_Tables_Log_P->setTitle(QApplication::translate("MainWindow", "Correlation Tables (Log P)", 0));
        menuAdherence_Matrix->setTitle(QApplication::translate("MainWindow", "Adherence Matrix", 0));
        menuResidues_Of_Communities->setTitle(QApplication::translate("MainWindow", "Residues Of Communities", 0));
        menuConservation_Reference_Sequences->setTitle(QApplication::translate("MainWindow", "Conservation Reference Sequences", 0));
        menuCorrelation_Reference_Sequences->setTitle(QApplication::translate("MainWindow", "Correlation Reference Sequences", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
