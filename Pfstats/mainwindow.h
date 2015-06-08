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
    void Open_XML_triggered();

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
    //void on_cmdGraphPath_clicked();
    void on_cmdCorrelation_clicked();

    void on_listWidget_activated(const QModelIndex &index);

    void on_cmbRefSeq_activated(int index);

    void on_cmbRefSeq_2_activated(int index);

    void on_cmbRefSeq_3_activated(int index);

    //void on_lstRefSeqs_itemSelectionChanged();

    void on_lstRefSeqs_2_itemSelectionChanged();

    void on_cmdSaveResults_clicked();

    void on_listWidget2_activated(const QModelIndex &index);

    void on_cmdShowResults_clicked();

    void on_cmdShow_clicked();

    void on_lstProteinsFiltered_activated(const QModelIndex &index);

    void on_cmdNextComm_clicked();
    
    void on_cmdBackComm_clicked();
    
    void on_cmdNextComm_2_clicked();

    void on_cmdBackComm_2_clicked();

    void on_cmdNextResult_clicked();

    void on_cmdBackResult_clicked();

    void on_cmdNextResComm_clicked();

    void on_cmdBackResComm_clicked();

private:
    Ui::MainWindow *ui;
    void changeWizardCmds(bool bl);
    void resetObjects();
    bool wizard;
    string pdbweb = "";
    int stackBeforeShowResults = 0;
    int currentStackPos = 0;
    vector<int> resultsStackList;
    bool compareLocalWebPDB(string local, string web);
    vector<Alignment> alinhamentos;
    void addAlignment(string path);
    bool checkfile(const string& name);
    vector<string> split(string text, char sep);
    string makeNewPath(string oldPath, string fileSufix);
    char num2aa(int n);
    int GetOffsetFromSeqName (string seqname);
    void alignfilter(string alignPath, float occupancy, float minId, float maxId, int refseq, string refseqName);
    void conservation(int ai, int refseq, int offset, char chain, float minCons, string pdbfile = "");
    void conservedresidues(int ai, vector<int> referencesequences, float minconservation);
    vector<float> minss(int ai, int repetitions); //from 100 to 1;
    void pcalc(int ai, int minlogp, float minssfraction, float mindeltafreq);
    void trivcomm(int ai);
    void output(int ai, int seqnumber, int offset);
    void adherence(Alignment align, string communitiesfilename, string outputfilename);
    void comm2seqrenumbering(Alignment align, string communitiesfilename, vector<int> referencesequences, string path);
    //Show Results
    void listSequences(int ai);
    void tableFreq(int ai);
    void tableFreqPerc(int ai);
    void conservResidues(int ai);
    void correlationList(int ai);
    void communitiesList(int ai);
    void corrTable1(int ai);
    void corrTable2(int ai);
    void adh(int ai);
    void showConservedResidues(int ai);
    void showResiduesComm(int ai);
};

#endif // MAINWINDOW_H
