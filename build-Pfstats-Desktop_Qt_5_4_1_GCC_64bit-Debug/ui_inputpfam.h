/********************************************************************************
** Form generated from reading UI file 'inputpfam.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTPFAM_H
#define UI_INPUTPFAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputPFAM
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *txtAccession;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFetch;
    QSpacerItem *horizontalSpacer_2;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;

    void setupUi(QDialog *InputPFAM)
    {
        if (InputPFAM->objectName().isEmpty())
            InputPFAM->setObjectName(QStringLiteral("InputPFAM"));
        InputPFAM->resize(400, 300);
        widget = new QWidget(InputPFAM);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 20, 301, 249));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        txtAccession = new QLineEdit(widget);
        txtAccession->setObjectName(QStringLiteral("txtAccession"));

        horizontalLayout_6->addWidget(txtAccession);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radioButton = new QRadioButton(widget);
        buttonGroup = new QButtonGroup(InputPFAM);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(false);

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setChecked(true);

        horizontalLayout->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        radioButton_3 = new QRadioButton(widget);
        buttonGroup_2 = new QButtonGroup(InputPFAM);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        horizontalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(widget);
        buttonGroup_2->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        radioButton_5 = new QRadioButton(widget);
        buttonGroup_3 = new QButtonGroup(InputPFAM);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(radioButton_5);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        horizontalLayout_3->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(widget);
        buttonGroup_3->addButton(radioButton_6);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_6);


        verticalLayout->addLayout(horizontalLayout_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        radioButton_7 = new QRadioButton(widget);
        buttonGroup_4 = new QButtonGroup(InputPFAM);
        buttonGroup_4->setObjectName(QStringLiteral("buttonGroup_4"));
        buttonGroup_4->addButton(radioButton_7);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setChecked(true);

        horizontalLayout_4->addWidget(radioButton_7);

        radioButton_8 = new QRadioButton(widget);
        buttonGroup_4->addButton(radioButton_8);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));

        horizontalLayout_4->addWidget(radioButton_8);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radioButton_9 = new QRadioButton(widget);
        buttonGroup_4->addButton(radioButton_9);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));

        horizontalLayout_5->addWidget(radioButton_9);

        radioButton_10 = new QRadioButton(widget);
        buttonGroup_4->addButton(radioButton_10);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));

        horizontalLayout_5->addWidget(radioButton_10);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        btnFetch = new QPushButton(widget);
        btnFetch->setObjectName(QStringLiteral("btnFetch"));

        horizontalLayout_7->addWidget(btnFetch);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout_2);

        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        radioButton_4->raise();
        radioButton_5->raise();
        radioButton_6->raise();
        radioButton_7->raise();
        radioButton_8->raise();
        radioButton_9->raise();
        radioButton_10->raise();
        label_5->raise();
        txtAccession->raise();
        btnFetch->raise();
        label_6->raise();

        retranslateUi(InputPFAM);

        QMetaObject::connectSlotsByName(InputPFAM);
    } // setupUi

    void retranslateUi(QDialog *InputPFAM)
    {
        InputPFAM->setWindowTitle(QApplication::translate("InputPFAM", "Dialog", 0));
        label_6->setText(QApplication::translate("InputPFAM", "Fetch data from PFAM:", 0));
        label_5->setText(QApplication::translate("InputPFAM", "Accession:", 0));
        label->setText(QApplication::translate("InputPFAM", "Alignment:", 0));
        radioButton->setText(QApplication::translate("InputPFAM", "Seed", 0));
        radioButton_2->setText(QApplication::translate("InputPFAM", "Full", 0));
        label_2->setText(QApplication::translate("InputPFAM", "Order:", 0));
        radioButton_3->setText(QApplication::translate("InputPFAM", "Tree", 0));
        radioButton_4->setText(QApplication::translate("InputPFAM", "Alphabetical", 0));
        label_3->setText(QApplication::translate("InputPFAM", "Sequence:", 0));
        radioButton_5->setText(QApplication::translate("InputPFAM", "Inserts lower case", 0));
        radioButton_6->setText(QApplication::translate("InputPFAM", "All upper case", 0));
        label_4->setText(QApplication::translate("InputPFAM", "Gaps:", 0));
        radioButton_7->setText(QApplication::translate("InputPFAM", "Dashes (-)", 0));
        radioButton_8->setText(QApplication::translate("InputPFAM", "Dots (.)", 0));
        radioButton_9->setText(QApplication::translate("InputPFAM", "Mixed (- or .)", 0));
        radioButton_10->setText(QApplication::translate("InputPFAM", "No gaps", 0));
        btnFetch->setText(QApplication::translate("InputPFAM", "Fetch", 0));
    } // retranslateUi

};

namespace Ui {
    class InputPFAM: public Ui_InputPFAM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTPFAM_H
