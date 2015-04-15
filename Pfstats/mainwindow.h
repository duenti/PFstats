#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "alignment.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startStacked();

private slots:
    void inputAlignment_triggered();
    void fetchPFAM_triggered();
    void exportAlignment_triggered();

    void on_cmdStartWizard_clicked();
    void on_cmdMain_clicked();
    void on_cmdBack_clicked();
    void on_cmdAdvance_clicked();
    void on_cmdOpen_clicked();
    void on_cmdFetch_clicked();
    void on_cmdApplyFilter_clicked();
    void on_cmdFetchPDB_clicked();
    void on_cmdPDBfromFile_clicked();
    void on_cmdConservation_clicked();
    void on_cmdMinss_clicked();
    void on_cmdGraphPath_clicked();
    void on_cmdCorrelation_clicked();

    void on_listWidget_activated(const QModelIndex &index);

    void on_cmbRefSeq_activated(int index);

    void on_cmbRefSeq_2_activated(int index);

private:
    Ui::MainWindow *ui;
    void changeWizardCmds(bool bl);
    void resetObjects();
    bool wizard;
    vector<Alignment> alinhamentos;
    void addAlignment(string path);
    bool checkfile(const string& name);
    vector<string> split(string text, char sep);
    string makeNewPath(string oldPath, string fileSufix);
    char num2aa(int n);
    int GetOffsetFromSeqName (string seqname);
    void alignfilter(Alignment align, float occupancy, float minId, float maxId, int refseq);
    void conservation(Alignment align, int refseq, int offset, char chain, string pdbfile = "");
    void conservedresidues(Alignment align, vector<int> referencesequences, string outputFile, float minconservation);
};

#endif // MAINWINDOW_H
