/********************************************************************************
** Form generated from reading UI file 'taxonomicvisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAXONOMICVISUALIZATION_H
#define UI_TAXONOMICVISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TaxonomicVisualization
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioSun1;
    QHBoxLayout *horizontalLayout_98;
    QRadioButton *radioSun3;
    QComboBox *cmbSunburstCommunity;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_97;
    QRadioButton *radioSun2;
    QComboBox *cmbSunburstEdges;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioSun4;
    QLineEdit *txtSunburstResidue;
    QPushButton *cmdSunburstFilter;
    QSpacerItem *horizontalSpacer;
    QWebView *webTaxons;
    QVBoxLayout *verticalLayout;
    QComboBox *cmbSunburstTaxon;
    QListWidget *lstSunburstTaxon;

    void setupUi(QDialog *TaxonomicVisualization)
    {
        if (TaxonomicVisualization->objectName().isEmpty())
            TaxonomicVisualization->setObjectName(QStringLiteral("TaxonomicVisualization"));
        TaxonomicVisualization->resize(806, 589);
        TaxonomicVisualization->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(TaxonomicVisualization);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioSun1 = new QRadioButton(TaxonomicVisualization);
        radioSun1->setObjectName(QStringLiteral("radioSun1"));
        radioSun1->setChecked(true);

        verticalLayout_2->addWidget(radioSun1);

        horizontalLayout_98 = new QHBoxLayout();
        horizontalLayout_98->setObjectName(QStringLiteral("horizontalLayout_98"));
        radioSun3 = new QRadioButton(TaxonomicVisualization);
        radioSun3->setObjectName(QStringLiteral("radioSun3"));

        horizontalLayout_98->addWidget(radioSun3);

        cmbSunburstCommunity = new QComboBox(TaxonomicVisualization);
        cmbSunburstCommunity->setObjectName(QStringLiteral("cmbSunburstCommunity"));
        cmbSunburstCommunity->setEnabled(false);

        horizontalLayout_98->addWidget(cmbSunburstCommunity);


        verticalLayout_2->addLayout(horizontalLayout_98);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_97 = new QHBoxLayout();
        horizontalLayout_97->setObjectName(QStringLiteral("horizontalLayout_97"));
        radioSun2 = new QRadioButton(TaxonomicVisualization);
        radioSun2->setObjectName(QStringLiteral("radioSun2"));

        horizontalLayout_97->addWidget(radioSun2);

        cmbSunburstEdges = new QComboBox(TaxonomicVisualization);
        cmbSunburstEdges->setObjectName(QStringLiteral("cmbSunburstEdges"));
        cmbSunburstEdges->setEnabled(false);
        cmbSunburstEdges->setMinimumSize(QSize(160, 0));

        horizontalLayout_97->addWidget(cmbSunburstEdges);


        verticalLayout_3->addLayout(horizontalLayout_97);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radioSun4 = new QRadioButton(TaxonomicVisualization);
        radioSun4->setObjectName(QStringLiteral("radioSun4"));

        horizontalLayout_5->addWidget(radioSun4);

        txtSunburstResidue = new QLineEdit(TaxonomicVisualization);
        txtSunburstResidue->setObjectName(QStringLiteral("txtSunburstResidue"));
        txtSunburstResidue->setEnabled(false);

        horizontalLayout_5->addWidget(txtSunburstResidue);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout_3);

        cmdSunburstFilter = new QPushButton(TaxonomicVisualization);
        cmdSunburstFilter->setObjectName(QStringLiteral("cmdSunburstFilter"));

        horizontalLayout->addWidget(cmdSunburstFilter);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        webTaxons = new QWebView(TaxonomicVisualization);
        webTaxons->setObjectName(QStringLiteral("webTaxons"));
        webTaxons->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webTaxons, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cmbSunburstTaxon = new QComboBox(TaxonomicVisualization);
        cmbSunburstTaxon->setObjectName(QStringLiteral("cmbSunburstTaxon"));

        verticalLayout->addWidget(cmbSunburstTaxon);

        lstSunburstTaxon = new QListWidget(TaxonomicVisualization);
        lstSunburstTaxon->setObjectName(QStringLiteral("lstSunburstTaxon"));
        lstSunburstTaxon->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(lstSunburstTaxon);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);


        retranslateUi(TaxonomicVisualization);

        cmbSunburstTaxon->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(TaxonomicVisualization);
    } // setupUi

    void retranslateUi(QDialog *TaxonomicVisualization)
    {
        TaxonomicVisualization->setWindowTitle(QApplication::translate("TaxonomicVisualization", "Taxonomic Visualization", 0));
        radioSun1->setText(QApplication::translate("TaxonomicVisualization", "Full", 0));
        radioSun3->setText(QApplication::translate("TaxonomicVisualization", "Community", 0));
        radioSun2->setText(QApplication::translate("TaxonomicVisualization", "Edges", 0));
        radioSun4->setText(QApplication::translate("TaxonomicVisualization", "Residue", 0));
        cmdSunburstFilter->setText(QApplication::translate("TaxonomicVisualization", "Filter", 0));
        cmbSunburstTaxon->clear();
        cmbSunburstTaxon->insertItems(0, QStringList()
         << QApplication::translate("TaxonomicVisualization", "Super Kingdom", 0)
         << QApplication::translate("TaxonomicVisualization", "Kingdom", 0)
         << QApplication::translate("TaxonomicVisualization", "Phylum", 0)
         << QApplication::translate("TaxonomicVisualization", "Class", 0)
         << QApplication::translate("TaxonomicVisualization", "Order", 0)
         << QApplication::translate("TaxonomicVisualization", "Family", 0)
         << QApplication::translate("TaxonomicVisualization", "Genus", 0)
         << QApplication::translate("TaxonomicVisualization", "Species", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class TaxonomicVisualization: public Ui_TaxonomicVisualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAXONOMICVISUALIZATION_H
