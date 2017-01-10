#ifndef FILTER_H
#define FILTER_H

#include "network.h"
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
#include <QTreeWidgetItem>

using namespace std;

class Filter
{
private:
    vector<Network*> networks;
    string name;
    string alphabet;
    int type; //9 - Full Alignment; 8 - Full ALignment with another alphabet; 7 - Subalignment of the full alignmet; 0 - HMM Filter; 1 - refSeqFilter; 2 - Henikof Weights; 3 - Communities subalignment
    string refSeq;
    string taxon;
    float minOcc;
    float minId;
    float maxId;
    float cons_alpha;
    float cons_beta;
    string cons_pdb;
    float cons_min;
    string conservedPDBpath;
    QTreeWidgetItem *treeItem;
    vector<string> refseqs;
    vector<long double> dG;       // deltaG (size of sequence alignment)
    vector<float> consDG;
    vector<vector<int> > consvfreq;
    vector<vector<float> > consfreqPerc;
    vector<string> conservedresidues;
    vector<int> SortOrder;
    vector<vector<int> > subsetfrequencies;
    vector<int> subalignmentseqs;
    vector<float> minssData;
    int referencesequence;
    vector<int> referencevector; // Vector containing the positions for a reference sequence
    long double meanf[21];    // mean amino acid frequencies for all proteins
    vector<float> weights;
    string refSeqName = ""; //REMOVER DEPOIS - NUNCA USADA
    vector<string> split(string text, char sep);
    unsigned int freqmatrixposition(char c);
    char num2aa(int n);
    bool isaa(char c);
    bool isaax(char c);
    unsigned int GetOffsetFromSeqName (string seqname);
    long double lnfact(int x);
    long double stirling(int x);
    long double lnbdf (int N, int nx, float px);
    int countAA(char aa, int col);
    string typeToString();
    int blosum_indexes(char c);
    int BLOSUM62(char c1, char c2);

public:
    vector<string> sequences;
    vector<string> sequencenames;
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
    float getConsMin();
    void setConsMin(float value);
    int getConsRefseq();
    string getStrConsRefseq();
    void setConsRefseq(int seq);
    void setConsRefseq(string seq);
    void setConsPDBPath(string path);
    string getConsPDBPath();
    float getConsAlpha();
    void setConsAlpha(float alpha);
    float getConsBeta();
    void setConsBeta(float beta);
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
    unsigned int AlignNumbering2Sequence2(int seqnumber, int position, vector<string> fullSequences);// Seqnumber starts with 1
    void printRefSeqs();
    void CalculateFrequencies();
    string getAAList(string alphabet);
    void dGCalculation(float alpha, float beta);
    void dGCalculation();
    void dGWrite();
    void FreqWrite();
    vector<float> ShannonEntropy(int repetitions, int cores);
    void alignment2UpperCase();
    void CalculateReferenceVector(int seqnumber); // Seqnumber starts with 1
    unsigned int sequencenumbering2alignment(int seqnumber, int position); //seqnumber starts with 1
    void setSorOrder(vector<int> order);
    vector<vector<int> > getSubsetFrequencies();
    void setSubsetFrequencies(vector<vector<int> > subset);
    vector<int> getConsFreqRow(int i);
    unsigned int getConsFreqSize();
    unsigned int getConsFreqPercSize();
    vector<float> getConsFreqPercRow(int i);
    vector<string> getConsRes();
    vector<float> getConservedDGs();
    string getNoGAPSequence(int refseq);
    string getNoGAPSequence(string refseq);
    vector<float> createConservationVector(int refseq);
    vector<tuple<int,float> > createConservationVectorDG(int refseq);
    unsigned int getRefSeqOffset();
    void applyAlphabetReduction(vector<string> oldChars, vector<char> newChars);
    void exportFilteredAlignment(QString filename, int type); //TYPE: 0-PFAM, 1-TXT, 2-XML
    void exportRefs(QString filename, int type); //TYPE: 0-TXT, 1-XML
    void exportFreq(QString filename, int type, bool perc=false); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML //PERC: TRUE = In %
    void exportConsRes(QString filename, int type, float mincons, vector<int> refSeqs,vector<string> fullAlignment, vector<string> fullSequences); //TYPE: 0-TXT, 1-XML, 2-HTML
    unsigned int getMinssVectorSize();
    string getRefSeqName();
    void setRefSeqName(string ref);
    string getSequence(string seqname);
    string generateXML();
    bool henikoffWeights();
    void addConsFreqRow(vector<int> row);
    void addConsFreqPercRow(vector<float> row);
    void printConsFreq();
    void printConsFreqPerc();
    void setConsDG(vector<float> dg);
    int getDGsize();
    float getDGPosition(int i);
    void setMinss(vector<float> data);
    void updateSequencesData();
    vector<string> getReducedSequences(string alphabet);
    char getReducedAminoAcid(char c, string alphabet);
    float getResidueFrequence(char aa, int pos, string alphabet);
    bool containsSequence(string seq);
    int getSequenceIndex(string refseq);
    void convertLowerDots();
    int getWeightsSize();
    vector<float> getWeights();
    void setWeights(vector<float> ws);
    void addNetwork(Network *net);
    int countNetworks();
    Network* getNetwork(int i);
    Network* getNetworkByName(string n);
    bool networkExists(string name);
    void removeNetwork(string name);
    void setQtreeWidgetItem(QTreeWidgetItem *item);
    QTreeWidgetItem* getQTreeWidgetItem(); //IF NULL => FULL ALIGNMENT
    vector<string> getRefSeqs();
};

#endif // FILTER_H
