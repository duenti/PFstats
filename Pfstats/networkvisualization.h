#ifndef NETWORKVISUALIZATION_H
#define NETWORKVISUALIZATION_H

#include <QDialog>
#include <QMessageBox>
#include "filter.h"
#include "colors.h"
#include <QWebFrame>

namespace Ui {
class NetworkVisualization;
}

class NetworkVisualization : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkVisualization(QWidget *parent = 0, Filter* filter=NULL, string lib="");
    ~NetworkVisualization();

private slots:
    void on_cmdReload_clicked();

    void on_chkHideAntiCorrelations_clicked(bool checked);

    void on_chkScaleHubs_clicked(bool checked);

    void on_chkCommunitiesColor_clicked(bool checked);

    void on_chkScaleEdgesScore_clicked(bool checked);

private:
    Ui::NetworkVisualization *ui;
    Filter* currentFilter;
    string libpath;
    void createVisualization(bool hideanticorr, bool commcolor, bool scaleEdges);
};

#endif // NETWORKVISUALIZATION_H
