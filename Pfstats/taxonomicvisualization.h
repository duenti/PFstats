#ifndef TAXONOMICVISUALIZATION_H
#define TAXONOMICVISUALIZATION_H

#include <QDialog>
#include "filter.h"
#include "alignment.h"
#include <QWebFrame>
#include <QListWidgetItem>

using namespace std;

namespace Ui {
class TaxonomicVisualization;
}

class TaxonomicVisualization : public QDialog
{
    Q_OBJECT

    template <typename T1, typename T2>
    struct less_second {
        typedef pair<T1, T2> type;
        bool operator ()(type const& a, type const& b) const {
            return a.second > b.second;
        }
    };

public:
    explicit TaxonomicVisualization(QWidget *parent = 0, Filter* filter=NULL, Network* network=NULL, string lib="", Alignment* align=NULL);
    ~TaxonomicVisualization();

private slots:
    void on_radioSun1_clicked(bool checked);

    void on_radioSun2_clicked(bool checked);

    void on_radioSun3_clicked(bool checked);

    void on_radioSun4_clicked(bool checked);

    void on_cmdSunburstFilter_clicked();

    void on_cmbSunburstTaxon_activated(int index);

    void on_lstSunburstTaxon_itemActivated(QListWidgetItem *item);

private:
    Ui::TaxonomicVisualization *ui;
    Filter* currentFilter;
    Network* currentNetwork;
    string libpath;
    map<string,string> mapPreTaxons;
    map<string,string> taxonomy;

    vector<string> split(string text, char sep);
    bool generateSunburst(vector<string> sequencenames);
};

#endif // TAXONOMICVISUALIZATION_H
