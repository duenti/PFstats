/********************************************************************************
** Form generated from reading UI file 'filteralignment.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERALIGNMENT_H
#define UI_FILTERALIGNMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterAlignment
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbRefSeq;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *txtMinCover;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *txtMinId;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *txtMaxId;
    QLabel *label_5;

    void setupUi(QDialog *FilterAlignment)
    {
        if (FilterAlignment->objectName().isEmpty())
            FilterAlignment->setObjectName(QStringLiteral("FilterAlignment"));
        FilterAlignment->resize(400, 300);
        buttonBox = new QDialogButtonBox(FilterAlignment);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(FilterAlignment);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 80, 341, 120));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        cmbRefSeq = new QComboBox(layoutWidget);
        cmbRefSeq->setObjectName(QStringLiteral("cmbRefSeq"));

        horizontalLayout->addWidget(cmbRefSeq);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        txtMinCover = new QLineEdit(layoutWidget);
        txtMinCover->setObjectName(QStringLiteral("txtMinCover"));

        horizontalLayout_2->addWidget(txtMinCover);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        txtMinId = new QLineEdit(layoutWidget);
        txtMinId->setObjectName(QStringLiteral("txtMinId"));

        horizontalLayout_3->addWidget(txtMinId);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        txtMaxId = new QLineEdit(layoutWidget);
        txtMaxId->setObjectName(QStringLiteral("txtMaxId"));

        horizontalLayout_4->addWidget(txtMaxId);


        verticalLayout->addLayout(horizontalLayout_4);

        label_5 = new QLabel(FilterAlignment);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 50, 101, 16));

        retranslateUi(FilterAlignment);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterAlignment, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterAlignment, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterAlignment);
    } // setupUi

    void retranslateUi(QDialog *FilterAlignment)
    {
        FilterAlignment->setWindowTitle(QApplication::translate("FilterAlignment", "Dialog", 0));
        label->setText(QApplication::translate("FilterAlignment", "Reference Sequence:", 0));
        label_2->setText(QApplication::translate("FilterAlignment", "Minimum Coverage:", 0));
        label_3->setText(QApplication::translate("FilterAlignment", "Minimu Identy:", 0));
        label_4->setText(QApplication::translate("FilterAlignment", "Maximum Identy:", 0));
        label_5->setText(QApplication::translate("FilterAlignment", "Filter Alignment:", 0));
    } // retranslateUi

};

namespace Ui {
    class FilterAlignment: public Ui_FilterAlignment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERALIGNMENT_H
