#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <vector>
#include <string>
#include <QObject>
#include <QProgressDialog>

using namespace std;


class Alignment
{

private:
    string filepath;
    string refSeqName;
    vector<int> subalignmentseqs;
    vector<int> referencevector; // Vector containing the positions for a reference sequence
    vector<int> SortOrder;
    struct community {
           vector<int> pos;
           vector<char> aa;
           };
    community tempcommunity;
    void resetCommunities();
    bool validstartcharacter(char c);
    bool validposition(char c);
    int freqmatrixposition(char c);
    int getresn(string line);
    bool isaa(char c);
    bool isaax(char c);
    char num2aa(int n);
    long double lnbdf (int N, int nx, float px);
    long double lnfact(int x);
    long double stirling(int x);
    string outputBfactor(string line, float Bf);


public:
    Alignment();
    Alignment(string path);
    ~Alignment();
    vector<string> split(string text, char sep);
    string getFilepath();
    void setFilepath(string path);
    string getRefSeqName();
    void setRefSeqName(string ref);
    int getRefSeqOffset();
    vector<string> sequences;
    vector<string> sequencenames;
    vector<vector<int> > frequencies;
    vector<vector<int> > subsetfrequencies;
    vector<vector<float> > Deltas; // Delta parameter for community pairs
    vector<community> Communities;
    // SUBSET FREQUENCY MATRIX INITIALIZATION
              // aminoacid frequence matrix in the MSA
              // row (variable): position on the alignment, plus
              //                 one row for totals
              // column (0-20): number of counts in that position for
              //              each amino acid type.
              //              The first position (index 0) stores
              //              alignment gaps (- or .) and unidentified
              //              aminoacids (X) in that position

    vector<vector<int> > AASpecificConservation;
           // line: alignment positions
           // rows: aminoacids 1-20
    vector<long double> dG;       // deltaG (size of sequence alignment)
    vector<long double> dGDT;     // Dima-Thirumalai deltaG (size of sequence alignment)
    vector<float> normalizeddG;
    vector<int> hiconservedpos; //highly conserved positions
    long double meanf[21];    // mean amino acid frequencies for all proteins
    vector<vector<short int> > minuslogpvalues;
              //  minuslogpvalues[i][j] stores the values of -log(P) for all aa+position pairs
              //  minuslogpvalues[0][20] correspond to -log(P) for the probability of having an
              //  alanine in position 2 when an alanine is present in position 1
    vector<vector<float> > selfcorrelationmatrix;
    vector<vector<float> > identitymatrix;
    int referencesequence;
    bool GetFromFile(); //[OK]
    bool getFromStd(string text); //[10%]
    char positions(int i, int j);
    void CalculateFrequencies(); //[OK]
    void CalculateAASpecificConservation();
    void WriteAASpecificConservation(string outputfilename);
    float Identity(int seq1, int seq2); //[OK]
    int SeqSize(int seq); //[OK]
    void IdentityMatrixCalculation();
    void IdentityTrimming(float maxid, string newalignmentfilename="");//[OK]
    void IdentityMinimum(float minid, int refseq, string newalignmentfilename="");//[OK]
    void AlignmentTrimming(float minocc, int refseq, string newalignmentfilename="");//[OK]
    void UniprotList(string uniprotlistfilename, string newalignmentfilename);
    void IdentityStatistics(string familyid);
    void dGCalculation();//[OK]
    void dGWrite();//[OK]
    void dGDTCalculation(int numseqs);
    void FreqWrite(); //[OK]
    void CalculateReferenceVector(int seqnumber); // Seqnumber starts with 1 [OK]
    int AlignNumbering2Sequence(int seqnumber, int position); // Seqnumber starts with 1
    void NormalizedG(); //[OK]
    int seqcode2seqint (string refseqcode); //[OK]
    void writedGtoPDB(string PDBfilename, string dgPDBfilename,int initres,char chain,int seqnumber);//[OK]
    void SubAlignmentIndices(char aa,int pos);
    int SubAlignmentFrequency(char aa,int pos);
    int Singlepvalue(char aa1,int pos1, char aa2, int pos2);
    void SympvalueCalculation (string outputgraph, int minlogp, float minssfraction, bool writefullgraph, float mindeltafreq);
    void pvalueCalculation(string outputgraph, int minlogp, float minssfraction, bool writefullgraph, float mindeltafreq, bool signedgraph);
    void GetCommunitiesFromFile(string clusterfilename);
    void DeltaCommunitiesCalculation(void);
    void DeltaCommunitiesOutput(string deltaoutputfilename);
    void ElementRanking(string familyID, bool renumber, int seqnumber,int offset);
    void SelfCorrelationMatrixCalculation(const std::vector <char> &aalist, const std::vector <int> &poslist);
    void SCM2HTML(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist, bool renumber, int seqnumber, int offset);
    void Write_SCM(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist);
    void pMatrix2HTML(string familyID, bool renumber, int seqnumber);
    float PSA(int seqnumber, int communitynumber);
    int ADH_count(int seqnumber,int communitynumber);
    void CalculateHighlyConservedPositions();
    void SuccessiveRandomElimination(string outputfilename, int step, int repetitions, int endvalue=100);
    void DTRandomElimination(string outputfilename, int repetitions, int max, int min, int step);
    void Cluster2SCM(string clusterfilename, string familyID, bool renumber, int seqnumber, int offset, bool html, bool text);
    void Cluster2PymolScript(string clusterfilename, string familyID, int seqnumber, int offset);
    void AlignmentWrite(string outputfilename); //[OK]
    vector<string> getSequencesName(); //[OK]
};

#endif // ALIGNMENT_H
