#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "alignment.h"
#include "qcustomplot.h"
#include <stdio.h>
#include <stdlib.h>
#include "pdb.h"
#include <QCompleter>

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
    void Open_XML_triggered();
    void exportAlignment_PFAM();
    void exportAlignment_TXT();
    void exportAlignment_XML();
    void exportRefSeqTXT();
    void exportRefSeqXML();
    void exportFreqTXT();
    void exportFreqCSV();
    void exportFreqXML();
    void exportFreqHTML();
    void exportFreqPercTXT();
    void exportFreqPercCSV();
    void exportFreqPercXML();
    void exportFreqPercHTML();
    void exportConsResTXT();
    void exportConsResXML();
    void exportConsResHTML();
    void exportCorrListTXT();
    void exportCorrListCSV();
    void exportCorrListXML();
    void exportCommsTXT();
    void exportCommsXML();
    void exportCorrTablePercTXT();
    void exportCorrTablePercXML();
    void exportCorrTablePercHTML();
    void exportCorrTableTXT();
    void exportCorrTableXML();
    void exportCorrTableHTML();
    void exportAdhTXT();
    void exportAdhCSV();
    void exportAdhXML();
    void exportAdhHTML();
    void exportResCommTXT();
    void exportResCommXML();
    void exportResCommHTML();
    void exportLookProtTXT();
    void exportLookProtCSV();
    void exportLookProtXML();
    void exportLookProtHTML();
    void exportLookCommTXT();
    void exportLookCommCSV();
    void exportLookCommXML();
    void exportLookCommHTML();
    void startWizard();
    void changetoFilterStack();
    void changeToRefSeqs();
    void changeToLoadPDBs();
    void changeToConservationStack();
    void changetoMinssStack();
    void changetoCorrelationStack();
    void changetoShowResultsStack();
    void changeToUniprotLookingTool();
    void saveResults();
    void closeAlignment();
    void showAbout();
    void changeToCreateCommunity();
    void changeToListOfSequences();
    void changeToConservationFrequence();
    void changeToConservationPercentage();
    void changeToConservedResidues();
    void changetoCorrelationList();
    void changeToCommunitiesList();
    void changeToCorrelationInPerc();
    void changeToCorrelationInLogP();
    void changeToAdherenceMatrix();
    void changeToResiduesOfCommunities();
    void changeToULGroupedByProteins();
    void changeToULGroupedByComms();
    void changeToCorrelationGraph();
    void changeToCommunitiesGraphs();
    void changeToCorrelationBetweenComms();
    void changeToPDBVisualization();
    void changeToPDBVisualization2();
    void setLibPath();
    void changeToAlphabetReduction();
    void graphClicked(QCPAbstractPlottable* plot,QMouseEvent* mouse);

    void on_cmdStartWizard_clicked();
    void on_cmdMain_clicked();
    void on_cmdBack_clicked();
    void on_cmdAdvance_clicked();
    void on_cmdOpen_clicked();
    void on_cmdFetch_clicked();
    void on_cmdApplyFilter_clicked();
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

    void on_cmdRemoveFilter_clicked();

    void on_cmdRemoveAlignment_clicked();

    void on_cmdUploadConsRefsSeqs_clicked();

    void on_cmdLook_clicked();

    void on_cmdLookNone_clicked();

    void on_cmdLookAll_clicked();

    void on_lstProteinsMined_activated(const QModelIndex &index);

    void on_treeMinerComms_clicked(const QModelIndex &index);

    void on_cmbComm_currentIndexChanged(int index);

    void on_cmdAddResComm_clicked();

    void on_cmdDelResComm_clicked();

    void on_cmdNewComm_clicked();

    void on_cmdAddFileRefSeq_clicked();

    void on_cmdAddAllRefSeq_clicked();

    void on_cmdRemoveAllRefSeq_clicked();

    void on_cmdAddOneRefSeq_clicked();

    void on_cmdRemoveOneRefSeq_clicked();

    void on_cmdSaveRefSeqs_clicked();

    void on_cmdUpdateComms_clicked();

    void on_txtMinssFraction_editingFinished();

    void on_cmdHideShowAntiCorr_clicked();

    void on_cmdNexCommGraph_clicked();

    void on_cmdBackCommGraph_clicked();

    void on_txtGraphCutoff_editingFinished();

    void on_cmdCorrCommCutoff_clicked();

    void on_chkApplyMinCover_clicked(bool checked);

    void on_chkApplyMinId_clicked(bool checked);

    void on_chkApplyMaxId_clicked(bool checked);

    void on_cmbAlphabetList_currentIndexChanged(int index);

    void on_radioAlphabetCurrent_clicked(bool checked);

    void on_radioAlphabetNew_clicked(bool checked);

    void on_cmdApplyAlphabetReduction_clicked();

    void on_cmbRefSeq_2_activated(const QString &arg1);

    void on_lstRecomendedPDBs_itemActivated(QListWidgetItem *item);

    void on_chkRemoveContactResidues_clicked(bool checked);

    void on_cmbRefSeq_3_activated(const QString &arg1);

    void on_lstPDBsLoaded_2_itemActivated(QListWidgetItem *item);

    void on_cmbRefSeq_4_activated(const QString &arg1);

    void on_lstRecommendedPDBs_itemActivated(QListWidgetItem *item);

    void on_cmdPDBFile_clicked();

    void on_cmdPDBFetch_clicked();

    void on_cmdLoadPDB_clicked();

    void on_chkGenerateConsPDB_clicked(bool checked);

    void on_chkCommVisualization_clicked(bool checked);

    void on_chkApplyTaxonFilter_clicked(bool checked);

    void on_cmbFilterRefseq_activated(int index);

    void on_cmdFilterRefSeqs_clicked();

private:
    Ui::MainWindow *ui;
    Alignment *currentAlign;
    string currentPDBContent;
    QString CONFIG = "PF_CONFIG.conf";
    void changeWizardCmds(bool bl);
    void resetObjects();
    string libpath;
    bool wizard;
    string pdbweb = "";
    QCompleter* taxonsCompleter;
    int stackBeforeShowResults = 0;
    int currentStackPos = 0;
    vector<int> resultsStackList;
    QCPItemText *minssLabel;
    bool compareLocalWebPDB(string local, string web);
    vector<Alignment> alinhamentos;
    vector<Pdb*> pdbs;
    void addAlignment(string path);
    bool checkfile(const string& name);
    vector<string> split(string text, char sep);
    string makeNewPath(string oldPath, string fileSufix);
    char num2aa(int n);
    int GetOffsetFromSeqName (string seqname);
    void alignfilter(float occupancy, float minId, float maxId, int refseq, bool filter1=true, bool filter2=true, bool filter3=true, bool taxfilter=false);
    void conservation(int refseq, int offset, char chain, float minCons, string pdbid = "");
    void conservedresidues(float minconservation);
    vector<float> minss(int repetitions); //from 100 to 1;
    void pcalc(int minlogp, float minssfraction, float mindeltafreq);
    void trivcomm();
    void output(int seqnumber, int offset);
    void adherence(Alignment align, string communitiesfilename, string outputfilename);
    void comm2seqrenumbering(Alignment align, string communitiesfilename, vector<int> referencesequences, string path);
    //Show Results
    void listSequences();
    void tableFreq();
    void tableFreqPerc();
    //void conservResidues();
    void correlationList();
    void createCorrelationJSON();
    void communitiesGraphs();
    void corrBetweenComms();
    void consVisualization();
    void commVisualization();
    void communitiesList();
    void corrTable1();
    void corrTable2();
    void adh();
    void showConservedResidues();
    void showResiduesComm();
    void showUniprotGroupByProteins();
    void showUniprotGroupByComms();
    bool isaa(char c);
    bool isInt(string v);
    void updateResultsViews();
    bool isFloat(string myString);
    string makeVisPDBHTML(string PDB);
    void loadConfigurationFile();
};

#endif // MAINWINDOW_H
