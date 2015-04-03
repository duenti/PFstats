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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
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
#include <QtWidgets/QToolBar>
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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *cmdMain;
    QPushButton *cmdBack;
    QPushButton *cmdAdvance;
    QListWidget *listWidget;
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
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QComboBox *cmbRefSeq;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *txtMinCover;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *txtMinId;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *txtMaxId;
    QPushButton *cmdApplyFilter;
    QWidget *page_4;
    QLabel *label_14;
    QGroupBox *groupBox_3;
    QPushButton *cmdPDBfromFile;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_15;
    QLineEdit *txtPDBfilepath;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_16;
    QLineEdit *txtPDBName;
    QPushButton *cmdFetchPDB;
    QGroupBox *groupBox_4;
    QPushButton *cmdConservation;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_17;
    QComboBox *cmbRefSeq_2;
    QListWidget *lstRefSeqs;
    QLabel *label_20;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_18;
    QLineEdit *txtOffset;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_19;
    QLineEdit *txtChain;
    QWidget *page_5;
    QLabel *label_21;
    QCustomPlot *graficMinss;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_22;
    QSpinBox *txtNoAlignments;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *cmdMinss;
    QWidget *page_6;
    QLabel *label_23;
    QLabel *label_27;
    QPushButton *cmdCorrelation;
    QWidget *widget;
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
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_23;
    QLineEdit *txtGraphPath;
    QPushButton *cmdGraphPath;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMethod;
    QMenu *menuHelp;
    QMenu *menuShow;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(937, 595);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        cmdMain = new QPushButton(centralWidget);
        cmdMain->setObjectName(QStringLiteral("cmdMain"));
        cmdMain->setEnabled(true);
        cmdMain->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdMain);

        cmdBack = new QPushButton(centralWidget);
        cmdBack->setObjectName(QStringLiteral("cmdBack"));
        cmdBack->setEnabled(true);
        cmdBack->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdBack);

        cmdAdvance = new QPushButton(centralWidget);
        cmdAdvance->setObjectName(QStringLiteral("cmdAdvance"));
        cmdAdvance->setEnabled(true);
        cmdAdvance->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_9->addWidget(cmdAdvance);


        gridLayout->addLayout(horizontalLayout_9, 1, 1, 1, 1);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
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
        groupBox->setGeometry(QRect(50, 110, 121, 81));
        cmdOpen = new QPushButton(groupBox);
        cmdOpen->setObjectName(QStringLiteral("cmdOpen"));
        cmdOpen->setGeometry(QRect(20, 40, 80, 23));
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(200, 110, 331, 301));
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
        layoutWidget_2 = new QWidget(page_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(130, 130, 272, 136));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        cmbRefSeq = new QComboBox(layoutWidget_2);
        cmbRefSeq->setObjectName(QStringLiteral("cmbRefSeq"));

        horizontalLayout_10->addWidget(cmbRefSeq);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_11->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        txtMinCover = new QLineEdit(layoutWidget_2);
        txtMinCover->setObjectName(QStringLiteral("txtMinCover"));

        horizontalLayout_11->addWidget(txtMinCover);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);

        txtMinId = new QLineEdit(layoutWidget_2);
        txtMinId->setObjectName(QStringLiteral("txtMinId"));
        txtMinId->setMaximumSize(QSize(108, 16777215));

        horizontalLayout_12->addWidget(txtMinId);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_13 = new QLabel(layoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_13->addWidget(label_13);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);

        txtMaxId = new QLineEdit(layoutWidget_2);
        txtMaxId->setObjectName(QStringLiteral("txtMaxId"));
        txtMaxId->setMaximumSize(QSize(108, 16777215));

        horizontalLayout_13->addWidget(txtMaxId);


        verticalLayout_4->addLayout(horizontalLayout_13);

        cmdApplyFilter = new QPushButton(page_3);
        cmdApplyFilter->setObjectName(QStringLiteral("cmdApplyFilter"));
        cmdApplyFilter->setGeometry(QRect(220, 270, 80, 23));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_14 = new QLabel(page_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, -10, 491, 131));
        label_14->setWordWrap(true);
        groupBox_3 = new QGroupBox(page_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(50, 130, 511, 111));
        cmdPDBfromFile = new QPushButton(groupBox_3);
        cmdPDBfromFile->setObjectName(QStringLiteral("cmdPDBfromFile"));
        cmdPDBfromFile->setGeometry(QRect(350, 30, 131, 23));
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 70, 471, 29));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_14->addWidget(label_15);

        txtPDBfilepath = new QLineEdit(layoutWidget2);
        txtPDBfilepath->setObjectName(QStringLiteral("txtPDBfilepath"));
        txtPDBfilepath->setMinimumSize(QSize(400, 0));
        txtPDBfilepath->setReadOnly(true);

        horizontalLayout_14->addWidget(txtPDBfilepath);

        layoutWidget3 = new QWidget(groupBox_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 30, 302, 29));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget3);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_15->addWidget(label_16);

        txtPDBName = new QLineEdit(layoutWidget3);
        txtPDBName->setObjectName(QStringLiteral("txtPDBName"));

        horizontalLayout_15->addWidget(txtPDBName);

        cmdFetchPDB = new QPushButton(layoutWidget3);
        cmdFetchPDB->setObjectName(QStringLiteral("cmdFetchPDB"));

        horizontalLayout_15->addWidget(cmdFetchPDB);

        layoutWidget->raise();
        layoutWidget->raise();
        cmdPDBfromFile->raise();
        groupBox_4 = new QGroupBox(page_4);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(50, 230, 511, 231));
        cmdConservation = new QPushButton(groupBox_4);
        cmdConservation->setObjectName(QStringLiteral("cmdConservation"));
        cmdConservation->setGeometry(QRect(410, 190, 80, 23));
        layoutWidget4 = new QWidget(groupBox_4);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 40, 339, 29));
        horizontalLayout_16 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget4);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_16->addWidget(label_17);

        cmbRefSeq_2 = new QComboBox(layoutWidget4);
        cmbRefSeq_2->setObjectName(QStringLiteral("cmbRefSeq_2"));
        cmbRefSeq_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_16->addWidget(cmbRefSeq_2);

        lstRefSeqs = new QListWidget(groupBox_4);
        lstRefSeqs->setObjectName(QStringLiteral("lstRefSeqs"));
        lstRefSeqs->setGeometry(QRect(180, 80, 151, 141));
        lstRefSeqs->setSelectionMode(QAbstractItemView::MultiSelection);
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 90, 161, 91));
        layoutWidget5 = new QWidget(groupBox_4);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(370, 110, 121, 66));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_18 = new QLabel(layoutWidget5);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_17->addWidget(label_18);

        txtOffset = new QLineEdit(layoutWidget5);
        txtOffset->setObjectName(QStringLiteral("txtOffset"));

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

        horizontalLayout_18->addWidget(txtChain);


        verticalLayout_5->addLayout(horizontalLayout_18);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_21 = new QLabel(page_5);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(50, -10, 491, 131));
        label_21->setWordWrap(true);
        graficMinss = new QCustomPlot(page_5);
        graficMinss->setObjectName(QStringLiteral("graficMinss"));
        graficMinss->setGeometry(QRect(40, 180, 541, 291));
        layoutWidget6 = new QWidget(page_5);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(50, 140, 390, 29));
        horizontalLayout_19 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(layoutWidget6);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_19->addWidget(label_22);

        txtNoAlignments = new QSpinBox(layoutWidget6);
        txtNoAlignments->setObjectName(QStringLiteral("txtNoAlignments"));
        txtNoAlignments->setMinimumSize(QSize(60, 0));
        txtNoAlignments->setMaximum(10000);
        txtNoAlignments->setValue(100);

        horizontalLayout_19->addWidget(txtNoAlignments);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_8);

        cmdMinss = new QPushButton(layoutWidget6);
        cmdMinss->setObjectName(QStringLiteral("cmdMinss"));

        horizontalLayout_19->addWidget(cmdMinss);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        label_23 = new QLabel(page_6);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(50, -10, 491, 131));
        label_23->setWordWrap(true);
        label_27 = new QLabel(page_6);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(60, 270, 161, 17));
        cmdCorrelation = new QPushButton(page_6);
        cmdCorrelation->setObjectName(QStringLiteral("cmdCorrelation"));
        cmdCorrelation->setGeometry(QRect(470, 370, 99, 27));
        widget = new QWidget(page_6);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 150, 193, 101));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_24 = new QLabel(widget);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_20->addWidget(label_24);

        txtMinScore = new QSpinBox(widget);
        txtMinScore->setObjectName(QStringLiteral("txtMinScore"));
        txtMinScore->setMaximumSize(QSize(70, 16777215));
        txtMinScore->setValue(10);

        horizontalLayout_20->addWidget(txtMinScore);


        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_25 = new QLabel(widget);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_21->addWidget(label_25);

        txtMinssFraction = new QDoubleSpinBox(widget);
        txtMinssFraction->setObjectName(QStringLiteral("txtMinssFraction"));
        txtMinssFraction->setMaximumSize(QSize(70, 16777215));
        txtMinssFraction->setMinimum(0.01);
        txtMinssFraction->setMaximum(1);
        txtMinssFraction->setSingleStep(0.01);
        txtMinssFraction->setValue(0.2);

        horizontalLayout_21->addWidget(txtMinssFraction);


        verticalLayout_6->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_26 = new QLabel(widget);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_22->addWidget(label_26);

        txtMinDeltaFreq = new QDoubleSpinBox(widget);
        txtMinDeltaFreq->setObjectName(QStringLiteral("txtMinDeltaFreq"));
        txtMinDeltaFreq->setMinimum(0.01);
        txtMinDeltaFreq->setMaximum(1);
        txtMinDeltaFreq->setSingleStep(0.01);
        txtMinDeltaFreq->setValue(0.3);

        horizontalLayout_22->addWidget(txtMinDeltaFreq);


        verticalLayout_6->addLayout(horizontalLayout_22);

        widget1 = new QWidget(page_6);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(50, 300, 443, 29));
        horizontalLayout_23 = new QHBoxLayout(widget1);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        txtGraphPath = new QLineEdit(widget1);
        txtGraphPath->setObjectName(QStringLiteral("txtGraphPath"));
        txtGraphPath->setMinimumSize(QSize(350, 0));
        txtGraphPath->setReadOnly(true);

        horizontalLayout_23->addWidget(txtGraphPath);

        cmdGraphPath = new QPushButton(widget1);
        cmdGraphPath->setObjectName(QStringLiteral("cmdGraphPath"));

        horizontalLayout_23->addWidget(cmdGraphPath);

        stackedWidget->addWidget(page_6);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 937, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuMethod = new QMenu(menuBar);
        menuMethod->setObjectName(QStringLiteral("menuMethod"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuShow = new QMenu(menuBar);
        menuShow->setObjectName(QStringLiteral("menuShow"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMethod->menuAction());
        menuBar->addAction(menuShow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionInput_Alignment);
        menuFile->addAction(actionExport_Alignment);
        menuFile->addAction(actionFetch_From_PFAM);
        menuFile->addAction(actionClose_Alignment);
        menuMethod->addAction(actionFilter_Alignment);
        menuMethod->addAction(actionCalculate_Minimum_Sub_Alignment_Size);
        menuMethod->addAction(actionCalculate_Correlation_Scores);
        menuMethod->addAction(actionDecompose_Network);
        menuMethod->addAction(actionAnalyze_Conservation_Sets);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
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
        cmdMain->setText(QApplication::translate("MainWindow", "Main", 0));
        cmdBack->setText(QApplication::translate("MainWindow", "Back", 0));
        cmdAdvance->setText(QApplication::translate("MainWindow", "Advance", 0));
        label->setText(QApplication::translate("MainWindow", "<h1>PFstats</h1>\n"
"<p>PFstats contains a set of functions that you can use to analyze correlation and conservation in protein sequences.</p>\n"
"<p>You can choose navigate through these functions in the menu bar or just start the wizard at the bottom of this window.</p>", 0));
        cmdStartWizard->setText(QApplication::translate("MainWindow", "Start Wizard", 0));
        label_2->setText(QApplication::translate("MainWindow", "<h1>Step 1 - Getting An Alignment</h1>\n"
"<p>You can Choose from get an Alignment from your own computer or directly from PFAM</p>", 0));
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
        label_9->setText(QApplication::translate("MainWindow", "<h1>Step 2 - Filtering Alignment</h1>\n"
"<p>Even high quality alignments such as those available in PFAM usually need some filtering in order to eliminate or minimize known problems.</p>", 0));
        label_10->setText(QApplication::translate("MainWindow", "Reference Sequence:", 0));
        label_11->setText(QApplication::translate("MainWindow", "Minimum Coverage:", 0));
        label_12->setText(QApplication::translate("MainWindow", "Minimu Identy:", 0));
        label_13->setText(QApplication::translate("MainWindow", "Maximum Identy:", 0));
        cmdApplyFilter->setText(QApplication::translate("MainWindow", "Apply", 0));
        label_14->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Step 3 - Conservation</span></p><p>A series of simple frequency-based calculations are done using conservation.</p><p>At this step, you might need a PDB file, you can get one by visiting <span style=\" font-style:italic;\">pdb.org</span> or fetching from here.</p></body></html>", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "PDB File", 0));
        cmdPDBfromFile->setText(QApplication::translate("MainWindow", "Choose from file", 0));
        label_15->setText(QApplication::translate("MainWindow", "File Path:", 0));
        label_16->setText(QApplication::translate("MainWindow", "PDB Name:", 0));
        cmdFetchPDB->setText(QApplication::translate("MainWindow", "Fetch from internet", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Conservation", 0));
        cmdConservation->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_17->setText(QApplication::translate("MainWindow", "Main Reference Sequence:", 0));
        label_20->setText(QApplication::translate("MainWindow", "Secundary reference<br> sequences for calculate<br> conserved residues:", 0));
        label_18->setText(QApplication::translate("MainWindow", "Offset:", 0));
        label_19->setText(QApplication::translate("MainWindow", "Chain:", 0));
        label_21->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Step 4 - Minss</span></p>\n"
"<p>\n"
"This module implements the procedure described in (Dima and Thirumalai 2006). It calculates the average conservation for the full alignment and then for multiple sub-alignments with decreasing sizes.\n"
"</p>\n"
"\n"
"</body></html>", 0));
        label_22->setText(QApplication::translate("MainWindow", "Number of sub-alignments:", 0));
        cmdMinss->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_23->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:xx-large; font-weight:600;\">Step 5 - Correlation</span></p>\n"
"<p>\n"
"This will calculate a set of correlation scores for the full alignment, using the cutoffs provided by the user.\n"
"</p>\n"
"\n"
"</body></html>", 0));
        label_27->setText(QApplication::translate("MainWindow", "Output graph file path:", 0));
        cmdCorrelation->setText(QApplication::translate("MainWindow", "Calculate", 0));
        label_24->setText(QApplication::translate("MainWindow", "Minimum Score:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Minss Fraction:", 0));
        label_26->setText(QApplication::translate("MainWindow", "Minumum Delta:", 0));
        cmdGraphPath->setText(QApplication::translate("MainWindow", "Choose", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuMethod->setTitle(QApplication::translate("MainWindow", "Methods", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuShow->setTitle(QApplication::translate("MainWindow", "Show", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
