/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(463, 333);
        label = new QLabel(About);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 411, 281));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Dialog", 0));
        label->setText(QApplication::translate("About", "<html><head/><body><p><span style=\" font-size:18pt;\">PFStats v0.96</span><br/></p><p>Developed by Lucas Blecher and N\303\251li Fonseca<br/></p><p>Programa de P\303\263s Gradua\303\247\303\243o em Bioinform\303\241tica<br/>Instituto de Ci\303\252ncias Biol\303\263gicas<br/>Universidade Federal de Minas Gerais<br/></p><p>If you have any sugestion or find any bug, contact us:</p><p><br/></p><p align=\"center\"><span style=\" font-style:italic;\">nelifonseca@ufmg.br</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
