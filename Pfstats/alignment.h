#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <QObject>
#include <QProgressDialog>
#include "uniprot.h"
#include "filter.h"

using namespace std;


class Alignment
{

private:
    string BIOCOMP_ADRESS = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/";
    string filepath = "";
    int type; //ALINHAMENTO SUBIDO PELO PFAM (0) OU ARQUIVO(1), -1 PARA NÃO CARREGADO

    vector<Filter*> filters;
    vector<tuple<string,string,char,string> > recommendPdbs; //Resetando -protein,pdb,chain,interval
    vector<int> hmmpositions;
    //function_tag,parameters.
    unsigned int freqmatrixposition(char c);
    bool validstartcharacter(char c);//ok
    bool validposition(char c);//ok
    unsigned int GetOffsetFromSeqName (string seqname);//ok
    bool isaa(char c);//ok
    bool isaa(char c, bool casesensitive);//ok
    void readPFAM();//OK
    void readPFAM(vector<string> pfam);//OK
    void readSTO();//OK
    void readSTO(vector<string> pfam);//OK
    vector<string> split(string text, char sep);
    bool isHMMposition(char c);

public:
    vector<string> sequences;
    vector<string> sequencenames;
    Alignment();
    Alignment(string path);
    ~Alignment();
    int getType();
    void setType(int t);
    void clear();
    string getFilepath();
    void setFilepath(string path);
    void addSequence();//ok
    void convertLowerDots();//ok
    vector<string> getFullAlignment();//ok
    vector<string> getFullSequences();//ok
    void generateXML(string outputXML);//ok
    Filter* getFullFilter();
    bool GetFromFile(); //[OK]
    bool getFromStd(string text); //[OK]
    float Identity(int seq1, int seq2);//ok
    unsigned int SeqSize(int seq);//ok
    void taxonTrimming(string taxon, string refseqName, string refSeq);//ok
    void hmmCoverageTrimmimg(float occ);//ok
    void IdentityTrimming(float maxid);//ok
    void IdentityMinimum(float minid, int refseq);//ok
    void AlignmentTrimming(float minocc, int refseq);//ok
    void AlignmentTrimming(float minocc, int refseq, string refSeq, string firstrefseqname, bool caseSesitive);//ok
    int seqname2seqint2(string refseqcode);//ok
    vector<string> getSequencesName();//ok
    vector<string> getSequences();//ok
    vector<string> getRecommendsPDBs(string protein);//ok
    string getPDBInterval(string pdbid);//ok
    int getKindOfAlignment();//ok
    void dots2dashs();//ok
    void addFilter(Filter *filter);//ok
    void removeFilter(string name);//ok
    vector<Filter*> getFilters();//ok
    int countFilters();//ok
    Filter* getFilterByName(string name);//ok
    void addSequences(vector<string> seqs, vector<string> names);//ok
    void defineHMMpositions();
    void updateFiltersData();
};

#endif // ALIGNMENT_H
