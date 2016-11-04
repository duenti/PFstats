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
#include <QWebFrame>
#include <ctype.h>
#include "networkvisualization.h"
#include "taxonomicvisualization.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startStacked();

private slots:
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
    void changeToOpenAlignment();
    void changetoFilterStack();
    void changeToRefSeqs();
    void changeToLoadPDBs();
    void changeToConservationStack();
    void changetoMinssStack();
    void changetoCorrelationStack();
    void changeToUniprotLookingTool();
    void saveResults();
    void closeAlignment();
    void showAbout();
    void changeToCreateCommunity();
    void changeToListOfSequences();
    void changeToTaxonomicView();
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
    void changeToFullAlignment();
    void changeToAddSequence();
    void setLibPath();
    void changeToAlphabetReduction();
    void changeToGenSubAlignments();
    void changeToMutationAnalysis();
    void graphClicked(QCPAbstractPlottable* plot,QMouseEvent* mouse);
    void renameFilter();
    void removeFilter();

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

    void on_cmdSaveResults_clicked();

    void on_lstProteinsFiltered_activated(const QModelIndex &index);

    void on_cmdNextComm_clicked();

    void on_cmdBackComm_clicked();

    void on_cmdNextComm_2_clicked();

    void on_cmdBackComm_2_clicked();

    void on_cmdNextResComm_clicked();

    void on_cmdBackResComm_clicked();

    void on_cmdRemoveFilter_clicked();

    void on_cmdRemoveAlignment_clicked();

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

    void on_cmbLookingFilter_activated(int index);

    void on_cmdLookingFilter_clicked();

    void on_cmdApplyViewAlignment_clicked();

    void on_cmbFilterMethod_activated(int index);

    void on_listWidget2_itemActivated(QListWidgetItem *item);

    void on_txtSecRefSeqs_editingFinished();

    void on_txtSelectedSecRefseqs_editingFinished();

    void on_cmdSubAlignAddRes_clicked();

    void on_cmdGenerateSubAlignment_clicked();

    void on_cmbAddSeq1_activated(const QString &arg1);

    void on_cmbAddSeq2_activated(const QString &arg1);

    void on_cmdAddSeq_clicked();

    void on_cmdExpandNetworkVisualization_clicked();

    void on_cmdExpandTaxonomy_clicked();

    void on_cmdCalculateMutations_clicked();

    void on_radioMutationAlignment_clicked(bool checked);

    void on_radioMutationSequence_clicked(bool checked);

    void on_radioMutationPDB_clicked(bool checked);

private:
    enum Constants{
        STACK_MAIN = 0,
        STACK_ALIGNMENT = 1,
        STACK_FILTER = 2,
        STACK_REFSEQS = 3,
        STACK_PDB = 4,
        STACK_CONSERVATION = 5,
        STACK_MINSS = 6,
        STACK_CORRELATION = 7,
        STACK_RESULTS = 8,
        STACK_UNIPROT = 9,
        STACK_MANAGE_COMMS = 10,
        STACK_ALPHABET = 11,
        STACK_SUBALIGN = 12,
        STACK_ADDSEQ = 13,
        STACK_MUTATION = 14,
        STACK_RESULT_SEQLIST = 1,
        STACK_RESULT_CONSFREQ = 2,
        STACK_RESULT_FREQPERC = 3,
        STACK_RESULT_CONSRES = 4,
        STACK_RESULT_CORRLIST = 5,
        STACK_RESULT_COMMLIST = 6,
        STACK_RESULT_CORRPERC = 7,
        STACK_RESULT_CORRLOG = 8,
        STACK_RESULT_ADHERENCE = 9,
        STACK_RESULT_RESCOMM = 10,
        STACK_RESULT_UNIPROT_PROTEINS = 11,
        STACK_RESULT_UNIPROT_COMMS = 12,
        STACK_RESULT_CORRGRAPH = 13,
        STACK_RESULT_COMMGRAPH = 14,
        STACK_RESULT_DELTAGRAPH = 15,
        STACK_RESULT_CONSPDB = 16,
        STACK_RESULT_COMMPDB = 17,
        STACK_RESULT_FULLALIGN = 18,
        STACK_RESULT_TAXVIEW = 19
    };

    Ui::MainWindow *ui;
    Alignment *currentAlign;
    Filter *currentFilter;
    string currentPDBContent;
    string exportPath = "";
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
    vector<Alignment> alinhamentos;
    vector<Pdb*> pdbs;
    void addAlignment(string path);
    vector<string> split(string text, char sep);
    char num2aa(int n);
    int GetOffsetFromSeqName (string seqname);
    void alignfilter(float occupancy, float minId, float maxId, int refseq, bool filter1=true, bool filter2=true, bool filter3=true, bool taxfilter=false);
    void alignfilter(float occupancy,float maxId,bool filterOcc = true, bool filterMaxId=true, bool filterTaxon = false);
    void applyHenikoffFilter();
    void conservation(int refseq, int offset, char chain, float minCons, string pdbid = "");
    vector<float> minss(int repetitions); //from 100 to 1;
    void pcalc(int minlogp, float minssfraction, float mindeltafreq);
    bool trivcomm();
    void output(int seqnumber, int offset);
    //Show Results
    void listSequences();
    bool generateSunburst(vector<string> sequencenames);//csv
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
    void showFullAlignment(int colorIndex, int columnsIndex);
    bool isaa(char c);
    bool isInt(string v);
    void updateResultsViews();
    bool isFloat(string myString);
    string makeVisPDBHTML(string PDB);
    void loadConfigurationFile();
    vector<float> generateAMCL(int alfabetIndex);//Alfabetical Conservative Maximum List
    string findCurrentAlphabet();
    string getDirectory(string path);
    void comm2Align();
    void updateRefSeqsCompleters();
    void freeMem();
};

#endif // MAINWINDOW_H
