#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>
#include <QString>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <set>
#include <QMessageBox>
#include <QProgressDialog>
#include <QApplication>
#include <QFileDialog>
#include <QtNetwork>
#include "feature.h"
#include "uniprot.h"
#include "colors.h"

using namespace std;

class Filter
{
private:
    Colors *c;
    struct community {
           vector<int> pos;
           vector<char> aa;
           };
    community tempcommunity;

    string name;
    string alphabet;
    int type; //9 - Full Alignment; 8 - Full ALignment with another alphabet; 7 - Subalignment of the full alignmet; 0 - HMM Filter; 1 - refSeqFilter; 2 - Henikof Weights; 3 - Communities subalignment
    string refSeq;
    string taxon;
    float minOcc;
    float minId;
    float maxId;
    string cons_pdb;
    int cons_offset;
    float cons_min;
    int cons_refseq;
    string corr_pdb;
    int corr_min_score;
    float corr_minssfraction;
    float corr_min_delta;
    int corr_offset;
    int corr_refseq;
    string conservedPDBpath;
    string commPDBPath;
    vector<string> refseqs;
    vector<long double> dG;       // deltaG (size of sequence alignment)
    vector<float> consDG;
    vector<vector<int> > consvfreq;
    vector<vector<float> > consfreqPerc;
    vector<int> SortOrder;
    vector<vector<int> > subsetfrequencies;
    vector<float> minssData;
    vector<tuple<string,string,int> > corrGraph;
    vector<int> subalignmentseqs;
    //map<string,string> sunburstData;
    int referencesequence;
    vector<int> referencevector; // Vector containing the positions for a reference sequence
    vector<vector<string> > comunidades;
    vector<vector<string> > residuesComm;
    vector<vector<string> > residuesCommPs;
    vector<vector<vector<float> > > communityX;
    vector<vector<float> > communityXAll;
    vector<vector<vector<int> > > communityXps;
    vector<vector<float> > selfcorrelationmatrix;
    vector<vector<float> > Deltas; // Delta parameter for community pairs
    long double meanf[21];    // mean amino acid frequencies for all proteins
    vector<float> weights;
    vector<Uniprot*> uniprotMined;
    string refSeqName = ""; //REMOVER DEPOIS - NUNCA USADA

    vector<string> split(string text, char sep);
    unsigned int freqmatrixposition(char c);
    long double lnfact(int x);
    long double stirling(int x);
    long double lnbdf (int N, int nx, float px);
    char num2aa(int n);
    bool isaax(char c);
    vector<vector<int> > createBlankIntMatrix(int i1, int j1, int v);
    unsigned int GetOffsetFromSeqName (string seqname);
    int seqname2seqint2(string refseqcode, vector<string> fullAlignment);
    vector<int> getRefSeqCodes(vector<string> fullAlignment);
    long eto10(long double x);
    long double cbd_tietjen(int N, int n, float freq, bool right);
    int cbd(int N, int n, float freq, bool right);
    Feature* parseFeature(string feature);
    int countAA(char aa, int col);
    string typeToString();

public:
    vector<string> sequences;
    vector<string> sequencenames;
    vector<community> Communities;
    vector<vector<int> > frequencies;


    Filter();
    Filter(string name, string alphabet, int type);
    ~Filter();
    void clear();
    string getName();
    void setName(string name);
    string getAlphabet();
    void setAlphabet(string alp);
    int getType();
    void setType(int type);
    string getRefSeq();
    void setRefSeq(string refSeq);
    string getTaxon();
    void setTaxon(string tax);
    float getMinOcc();
    void setMinOcc(float occ);
    float getMinId();
    void setMinId(float id);
    float getMaxId();
    void setMaxId(float id);
    string getConsPDB();
    void setConsPDB(string pdb);
    int getConsOffset();
    void setConsOffset(int offset);
    float getConsMin();
    void setConsMin(float value);
    int getConsRefseq();
    string getStrConsRefseq();
    void setConsRefseq(int seq);
    void setConsRefseq(string seq);
    string getCorrPDB();
    void setCorrPDB(string pdb);
    int getCorrMinScore();
    void setCorrMinScore(int value);
    float getCorrMinssFraction();
    void setCorrMinssFraction(float value);
    float getCorrMinDelta();
    void setCorrMinDelta(float value);
    int getCorrOffset();
    void setCorrOffset(int value);
    int getCorrRefseq();
    string getStrCorrRefseq();
    void setCorrRefSeq(int seq);
    void setCorrRefSeq(string seq);
    void setConsPDBPath(string path);
    string getConsPDBPath();
    void setCommPDBPath(string path);
    string getCommPDBPath();
    bool addSequences(vector<string> names, vector<string> seqs);
    void addSequences(string protName, string protSequence);
    vector<string> getSequences();
    vector<string> getSequenceNames();
    int getSequencesCount();
    string getSequence(int i);
    string getSequenceName(int i);
    void addRefSeq(string seq);
    string getRefSeq(int i);
    void clearRefSeq();
    unsigned int getRefSeqsSize();
    unsigned int AlignNumbering2Sequence2(int seqnumber, int position, vector<string> fullSequences);
    void printRefSeqs();
    void CalculateFrequencies();
    void dGCalculation();
    void dGWrite();
    void FreqWrite();
    vector<float> ShannonEntropy(int repetitions);
    void alignment2UpperCase();
    void SubAlignmentIndices(char aa,int pos);
    int Singlepvalue(char aa1,int pos1, char aa2, int pos2);
    void SympvalueCalculation (int minlogp, float minssfraction, float mindeltafreq);
    vector<string> filterCorrGraph(vector<tuple<string,string> > tup, int refseq);
    void CalculateReferenceVector(int seqnumber); // Seqnumber starts with 1
    unsigned int AlignNumbering2Sequence(int seqnumber, int position); // Seqnumber starts with 1
    void clearCommunity();
    void resetCommunities();
    tuple<string,string,int> getCorrelationEdge(int i);
    unsigned int getCorrelationGraphSize();
    void addCommunity(vector<string> comm);
    void getCommunitiesFromRAM();
    int SubAlignmentFrequency(char aa,int pos);
    void SelfCorrelationMatrixCalculation(const std::vector <char> &aalist, const std::vector <int> &poslist);
    void Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset);
    void DeltaCommunitiesCalculation(void);
    void pMatrix2HTMLRAM(bool renumber, int seqnumber);
    unsigned int getNumOfUtilComms();
    vector<float> createCommuntitiesVector(int refseq);
    void setSorOrder(vector<int> order);
    vector<vector<int> > getSubsetFrequencies();
    void setSubsetFrequencies(vector<vector<int> > subset);
    unsigned int getCommListSize();
    vector<int> getConsFreqRow(int i);
    unsigned int getConsFreqSize();
    unsigned int getConsFreqPercSize();
    vector<float> getConsFreqPercRow(int i);
    vector<string> getConsRes(float minCons);
    unsigned int getCorrGraphSize();
    tuple<string,string,int> getCorrGraphTuple(int i);
    vector<string> getCommunitie(int i);
    vector<string> getResiduesComm(int c);
    vector<string> getResiduesCommPs(int c);
    vector<float> getCommAll(int c);
    vector<float> getCommXRow(int c, int i);
    vector<int> getCommPsRow(int c, int i);
    float PSA(int seqnumber, int communitynumber);
    unsigned int getUniprotMinedSize();
    string getUniprotEntryName(int i);
    unsigned int getUniprotEntryNofFeatures(int i);
    int getResidueFeaturesByCommCount(string res);
    vector<tuple<string,string,int> > getCorrelationGraph();
    set<string> getCorrelationNodes();
    map<string,int> getNodesHubs();
    set<string> getPositiveCorrelationNodes();
    map<string,int> getPositiveNodeHubs();
    vector<tuple<string,string,int> > getEdgesByComm(int comm);
    vector<tuple<string,string,float> > getDeltasEdges(float cutoff);
    string getNoGAPSequence(int refseq);
    vector<float> createConservationVector(int refseq);
    bool uniprotLook(bool cons, bool comms, vector<string> proteins, vector<int> idproteins, float minCons, vector<string> fullAlignment, vector<string> fullSequences);
    void removeItemOfCommunity(int comm, int item);
    void addItemToCommunity(string res, int commindex);
    unsigned int getRefSeqOffset();
    void applyAlphabetReduction(vector<string> oldChars, vector<char> newChars);
    void exportFilteredAlignment(QString filename, int type); //TYPE: 0-PFAM, 1-TXT, 2-XML
    void exportRefs(QString filename, int type); //TYPE: 0-TXT, 1-XML
    void exportFreq(QString filename, int type, bool perc=false); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML //PERC: TRUE = In %
    void exportConsRes(QString filename, int type, float mincons, vector<int> refSeqs,vector<string> fullAlignment, vector<string> fullSequences); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportCorrGraph(QString filename, int type); //TYPE: 0-TXT 1-CSV 2-XML
    void exportCommList(QString filename, int type); //TYPE: 0-TXT 1-XML
    void exportCorrTable(QString filename, int type, bool perc=true); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportAdh(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    void exportResComm(QString filename, int type, vector<string> fullAlignment, vector<string> fullSequences); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportLookProt(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    void exportLookComm(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    vector<Uniprot*> getAllResidueFeatures(string res);
    unsigned int getMinssVectorSize();
    string getRefSeqName();
    void setRefSeqName(string ref);
    string getSequence(string seqname);
    string getUniprotFunction(int i);
    Feature* getUniprotFeature(int i, int j);
    unsigned int getDeltasSize();
    void addDeltaLine(vector<float> line);
    string generateXML();
    bool henikoffWeights();
    void addConsFreqRow(vector<int> row);
    void addConsFreqPercRow(vector<float> row);
    void printConsFreq();
    void printConsFreqPerc();
    void setConsDG(vector<float> dg);
    void setMinss(vector<float> data);
    void addCorrEdge(string v1, string v2, int score);
    void addResiduesComm(vector<string> residues);
    void addCommXAll(vector<float> resAll);
    void addCommX(vector<vector<float> > commX);
    void addResiduesCommPs(vector<string> residuesPs);
    void addCommXPs(vector<vector<int> > commXPs);
    void updateCommunitiesData();
    void updateSequencesData();
    string getResidueColor(string residue);
};

#endif // FILTER_H
