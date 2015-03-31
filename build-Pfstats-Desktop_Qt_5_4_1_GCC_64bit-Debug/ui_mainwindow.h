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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMethod;
    QMenu *menuHelp;
    QMenu *menuShow;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(814, 486);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 814, 20));
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
        MainWindow->insertToolBarBreak(mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMethod->menuAction());
        menuBar->addAction(menuShow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionInput_Alignment);
        menuFile->addAction(actionFetch_From_PFAM);
        menuFile->addAction(actionExport_Alignment);
        menuMethod->addAction(actionFilter_Alignment);
        menuMethod->addAction(actionCalculate_Minimum_Sub_Alignment_Size);
        menuMethod->addAction(actionCalculate_Correlation_Scores);
        menuMethod->addAction(actionDecompose_Network);
        menuMethod->addAction(actionAnalyze_Conservation_Sets);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

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
