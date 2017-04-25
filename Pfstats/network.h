#ifndef NETWORK_H
#define NETWORK_H

#include "colors.h"
#include <string>
#include <vector>
#include <tuple>
#include <math.h>
#include <QMessageBox>
#include <QProgressDialog>
#include <QApplication>
#include "string"
#include <set>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <QtNetwork>
#include "feature.h"
#include "uniprot.h"

using namespace std;

class Network
{
private:
    string name;
    vector<vector<int> > frequencies;

    Colors *c;
    struct community {
           vector<int> pos;
           vector<char> aa;
           };
    community tempcommunity;
    string corr_pdb;
    int min_score;
    float minss;
    float minDelta;
    int refseq;
    string commPDBPath;
    vector<tuple<string,string,int> > corrGraph;
    vector<int> subalignmentseqs;
    vector<vector<string> > comunidades;
    vector<vector<string> > residuesComm;
    vector<vector<string> > residuesCommPs;
    vector<vector<vector<float> > > communityX;
    vector<vector<float> > communityXAll;
    vector<vector<vector<int> > > communityXps;
    vector<vector<float> > selfcorrelationmatrix;
    vector<vector<float> > Deltas; // Delta parameter for community pairs
    vector<Uniprot*> uniprotMined;
    long double lnfact(int x);
    long double stirling(int x);
    long double lnbdf (int N, int nx, float px);
    vector<vector<int> > createBlankIntMatrix(int i1, int j1, int v);
    long eto10(long double x);
    long double cbd_tietjen(int N, int n, float freq, bool right);
    int cbd(int N, int n, float freq, bool right);
    unsigned int freqmatrixposition(char c);
    char num2aa(int n);
    bool isaax(char c);
    vector<string> split(string text, char sep);
    Feature* parseFeature(string feature);
    unsigned int GetOffsetFromSeqName (string seqname);
    unsigned int AlignNumbering2Sequence2(int seqnumber, int position, vector<string> fullSequences);// Seqnumber starts with 1
    int seqname2seqint2(string refseqcode, vector<string> fullAlignment);
    vector<int> getRefSeqCodes(vector<string> fullAlignment, vector<string> refseqs);

public:
    Network();
    Network(vector<string> *seq, vector<string> *seqname);
    Network(vector<string> *seq, vector<string> *seqname, int logp, float minssfrac, float delta);
    Network(vector<string> *seq, vector<string> *seqname, Network *net);
    ~Network();
    vector<community> Communities;
    vector<string> *sequences; //TESTAR MUDAR VALOR NO ORIGINAL
    vector<string> *sequencenames; //TESTAR MUDAR VALOR NO ORIGINAL

    void clear();
    string getName();
    void setName(string n);
    string getPDB();
    void setPDB(string pdb);
    int getMinScore();
    void setMinScore(int value);
    float getMinssFraction();
    void setMinssFraction(float value);
    float getMinDelta();
    void setMinDelta(float value);
    void setRefSeq(string seq);
    int getRefSeq();
    void setCommPDBPath(string path);
    string getCommPDBPath();
    vector<vector<int> > getFrequencies();
    unsigned int getCommListSize();
    unsigned int getGraphSize();
    tuple<string,string,int> getGraphTuple(int i);
    vector<vector<string> > getComunidades();
    vector<string> getCommunitie(int i);
    vector<string> getResiduesComm(int c);
    vector<string> getResiduesCommPs(int c);
    vector<float> getCommAll(int c);
    vector<float> getCommXRow(int c, int i);
    int getCommXRowSize(int c);
    vector<int> getCommPsRow(int c, int i);
    int getCommPsRowSize(int c);
    int Singlepvalue(char aa1,int pos1, char aa2, int pos2);
    void SympvalueCalculation (int minlogp, float minssfraction, float mindeltafreq);
    void henikoffpvalueCalculation(int minlogp, float minssfraction, float mindeltafreq, vector<float> weights);
    void SubAlignmentIndices(char aa,int pos);
    vector<int> subalignmentIndicesW(char aa, int pos);
    void CalculateFrequencies();
    void clearCommunity();
    void resetCommunities();
    tuple<string,string,int> getCorrelationEdge(int i);
    unsigned int getCorrelationGraphSize();
    void addCommunity(vector<string> comm);
    void addToCommunity(string res, int i);
    unsigned int getDeltasSize();
    float getDeltaValue(int i, int j);
    void addDeltaLine(vector<float> line);
    vector<vector<string> > getResiduesComm();
    vector<vector<string> > getResiduesCommPs();
    vector<vector<vector<float> > > getCommunityX();
    vector<vector<float> > getCommunityXAll();
    vector<vector<vector<int> > > getCommunityXPs();
    vector<vector<float> > getSelfCorrelationMatrix();
    vector<vector<float> > getDeltas();
    void addCorrEdge(string v1, string v2, int score);
    void addResiduesComm(vector<string> residues);
    void addCommXAll(vector<float> resAll);
    void addCommX(vector<vector<float> > commX);
    void addResiduesCommPs(vector<string> residuesPs);
    void addCommXPs(vector<vector<int> > commXPs);
    void updateCommunitiesData();
    string getResidueColor(string residue);
    void getCommunitiesFromRAM();
    void Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset);
    int getEdge(string v1, string v2); //0 if doesnt exists
    void DeltaCommunitiesCalculation(void);
    void pMatrix2HTMLRAM(bool renumber, int seqnumber);
    unsigned int getNumOfUtilComms();
    vector<tuple<int,float> > createCommuntitiesVector();
    void SelfCorrelationMatrixCalculation(const std::vector <char> &aalist, const std::vector <int> &poslist);
    float PSA(int seqnumber, int communitynumber);
    vector<int> CalculateReferenceVector(int seqnumber); // Seqnumber starts with 1
    unsigned int AlignNumbering2Sequence(int seqnumber, int position); // Seqnumber starts with 1
    int SubAlignmentFrequency(char aa,int pos, vector<int> subalignmentseqs);
    vector<tuple<string,string,int> > getCorrelationGraph();
    set<string> getCorrelationNodes();
    map<string,int> getNodesHubs();
    set<string> getPositiveCorrelationNodes();
    map<string,int> getPositiveNodeHubs();
    vector<tuple<string,string,int> > getEdgesByComm(int comm);
    vector<tuple<string,string,float> > getDeltasEdges(float cutoff);
    void removeItemOfCommunity(int comm, int item);
    void addItemToCommunity(string res, int commindex);
    void setCommunityItems(int comm, vector<string> residues);
    void sortCommunitiesVector();
    void alignment2UpperCase();
    bool uniprotLook(bool cons, bool comms, vector<string> proteins, vector<int> idproteins, vector<string> conserved, vector<string> fullAlignment, vector<string> fullSequences, bool hasproxy, QNetworkProxy proxy);
    unsigned int getUniprotMinedSize();
    string getUniprotEntryName(int i);
    unsigned int getUniprotEntryNofFeatures(int i);
    int getResidueFeaturesByCommCount(string res);
    vector<Uniprot*> getAllResidueFeatures(string res);
    string getUniprotFunction(int i);
    Feature* getUniprotFeature(int i, int j);
    void exportCorrGraph(QString filename, int type); //TYPE: 0-TXT 1-CSV 2-XML
    void exportCommList(QString filename, int type); //TYPE: 0-TXT 1-XML
    void exportCorrTable(QString filename, int type, bool perc=true); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportAdh(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    void exportResComm(QString filename, int type, vector<string> fullAlignment, vector<string> fullSequences,vector<string> refseqs); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportLookProt(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    void exportLookComm(QString filename, int type, vector<string> conserved); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML

};

#endif // NETWORK_H
