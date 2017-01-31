/********************************************************************************
** Form generated from reading UI file 'networkvisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKVISUALIZATION_H
#define UI_NETWORKVISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkVisualization
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkHideAntiCorrelations;
    QCheckBox *chkScaleHubs;
    QCheckBox *chkScaleEdgesScore;
    QCheckBox *chkCommunitiesColor;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *txtRandomSeed;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbLayout;
    QPushButton *cmdReload;

    void setupUi(QDialog *NetworkVisualization)
    {
        if (NetworkVisualization->objectName().isEmpty())
            NetworkVisualization->setObjectName(QStringLiteral("NetworkVisualization"));
        NetworkVisualization->resize(806, 589);
        NetworkVisualization->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(NetworkVisualization);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        webView = new QWebView(NetworkVisualization);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 1);

        groupBox = new QGroupBox(NetworkVisualization);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(240, 0));
        groupBox->setMaximumSize(QSize(250, 16777215));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 60, 257, 234));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chkHideAntiCorrelations = new QCheckBox(layoutWidget);
        chkHideAntiCorrelations->setObjectName(QStringLiteral("chkHideAntiCorrelations"));

        verticalLayout->addWidget(chkHideAntiCorrelations);

        chkScaleHubs = new QCheckBox(layoutWidget);
        chkScaleHubs->setObjectName(QStringLiteral("chkScaleHubs"));

        verticalLayout->addWidget(chkScaleHubs);

        chkScaleEdgesScore = new QCheckBox(layoutWidget);
        chkScaleEdgesScore->setObjectName(QStringLiteral("chkScaleEdgesScore"));

        verticalLayout->addWidget(chkScaleEdgesScore);

        chkCommunitiesColor = new QCheckBox(layoutWidget);
        chkCommunitiesColor->setObjectName(QStringLiteral("chkCommunitiesColor"));

        verticalLayout->addWidget(chkCommunitiesColor);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        txtRandomSeed = new QSpinBox(layoutWidget);
        txtRandomSeed->setObjectName(QStringLiteral("txtRandomSeed"));

        horizontalLayout_2->addWidget(txtRandomSeed);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        cmbLayout = new QComboBox(layoutWidget);
        cmbLayout->setObjectName(QStringLiteral("cmbLayout"));

        horizontalLayout->addWidget(cmbLayout);


        verticalLayout->addLayout(horizontalLayout);

        cmdReload = new QPushButton(layoutWidget);
        cmdReload->setObjectName(QStringLiteral("cmdReload"));

        verticalLayout->addWidget(cmdReload);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);


        retranslateUi(NetworkVisualization);

        QMetaObject::connectSlotsByName(NetworkVisualization);
    } // setupUi

    void retranslateUi(QDialog *NetworkVisualization)
    {
        NetworkVisualization->setWindowTitle(QApplication::translate("NetworkVisualization", "Network Visualization", 0));
        groupBox->setTitle(QApplication::translate("NetworkVisualization", "Configuration", 0));
        chkHideAntiCorrelations->setText(QApplication::translate("NetworkVisualization", "Hide Anti-Correlations", 0));
        chkScaleHubs->setText(QApplication::translate("NetworkVisualization", "Scale nodes by hubs size", 0));
        chkScaleEdgesScore->setText(QApplication::translate("NetworkVisualization", "Scale edges by score", 0));
        chkCommunitiesColor->setText(QApplication::translate("NetworkVisualization", "Color nodes by communities", 0));
        label_2->setText(QApplication::translate("NetworkVisualization", "Layout:", 0));
        label_3->setText(QApplication::translate("NetworkVisualization", "Random Seed:", 0));
        label->setText(QApplication::translate("NetworkVisualization", "Method", 0));
        cmbLayout->clear();
        cmbLayout->insertItems(0, QStringList()
         << QApplication::translate("NetworkVisualization", "Components", 0)
         << QApplication::translate("NetworkVisualization", "Hierarchical UD", 0)
         << QApplication::translate("NetworkVisualization", "Hierarchical DU", 0)
        );
        cmdReload->setText(QApplication::translate("NetworkVisualization", "Reload Network", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkVisualization: public Ui_NetworkVisualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKVISUALIZATION_H
