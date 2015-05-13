#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <vector>
#include <string>
#include <tuple>
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
    vector<string> fullAlignment;
    vector<string> fullSequences;

    //XML Variables
    string localdir = "";
    string webdir = "";
    string localpdbdir = "";
    string webpdbdir = "";
    vector<vector<string> > filtersList; //Primeiro itém de cada vector interno se refere aos parâmetros, seguido da lista de proteínas
    vector<vector<string> > filterSequences; //"        "            "                "                  "           "
    vector<float> minssData;
    vector<float> consDG;
    vector<string> consParams;
    vector<vector<int> > consvfreq;
    vector<vector<float> > consfreqPerc;
    vector<tuple<string,string,int> > corrGraph;
    vector<vector<string> > comunidades;
    vector<string> refSeqs;
    vector<vector<int> > communityX;
    vector<vector<int> > communityXps;
    vector<string> parameters;
    //function_tag,parameters.

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
    int GetOffsetFromSeqName (string seqname);
    bool isaa(char c);
    bool isaax(char c);
    char num2aa(int n);
    long double lnbdf (int N, int nx, float px);
    long double lnfact(int x);
    long double stirling(int x);
    long eto10(long double x);
    long double cbd_tietjen(int N, int n, float freq, bool right);
    int cbd(int N, int n, float freq, bool right);
    string outputBfactor(string line, float Bf);


public:
    Alignment();
    Alignment(string path);
    ~Alignment();
    vector<string> split(string text, char sep);
    string getFilepath();
    string getDir();
    void setFilepath(string path);
    string getRefSeqName();
    void setRefSeqName(string ref);
    int getRefSeqOffset();
    string getLocalDir();
    void setLocalDir(string dir);
    string getWebDir();
    void setWebDir(string dir);
    string getLocalPDBDir();
    void setLocalPDBDir(string dir);
    string getWebPDBDir();
    void setWebPDBDir(string dir);
    vector<vector<string> > getAllFilters();
    vector<vector<string> > getAllSequences();
    void addFilterSequence(vector<string> align);
    void loadFullAlignment();
    void addParameter(string tag, string filter, int refSeq, int offset, char chain, string pdb);//Conservation
    void addParameter(string tag, string filter, int repetitions);//Minss
    void addParameter(string tag, string filter, int minlog, float minssfraction, float mindeltafreq); //Correlation
    vector<string> getConservationParameters();
    vector<string> getMinssParameters();
    vector<string> getCorrelationParameters();
    vector<string> getFullAlignment();
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
    void generateXML(string outputXML); //[1%]
    bool GetFromFile(); //[OK]
    bool getFromStd(string text); //[10%]
    char positions(int i, int j);
    void CalculateFrequencies(); //[OK]
    void CalculateAASpecificConservation();
    void WriteAASpecificConservation(string outputfilename);
    float Identity(int seq1, int seq2); //[OK]
    int SeqSize(int seq); //[OK]
    void IdentityMatrixCalculation();
    void IdentityTrimming(float maxid, float minocc, float minid, int refseq, string refseqName, string newalignmentfilename="");//[OK]
    void IdentityMinimum(float minid, int refseq, float minocc, string refSeqName, string newalignmentfilename="");//[OK]
    void AlignmentTrimming(float minocc, int refseq, string refseqName, string newalignmentfilename="");//[OK]
    void UniprotList(string uniprotlistfilename, string newalignmentfilename);
    void IdentityStatistics(string familyid);
    void dGCalculation();//[OK]
    void dGWrite();//[OK]
    void dGDTCalculation(int numseqs); //[OK]
    void FreqWrite(); //[OK]
    void CalculateReferenceVector(int seqnumber); // Seqnumber starts with 1 [OK]
    int AlignNumbering2Sequence(int seqnumber, int position); // Seqnumber starts with 1 [OK]
    void NormalizedG(); //[OK]
    int seqcode2seqint (string refseqcode); //[OK]
    void writedGtoPDB(string PDBfilename, string dgPDBfilename,int initres,char chain,int seqnumber);//[OK]
    void SubAlignmentIndices(char aa,int pos); //[OK]
    int SubAlignmentFrequency(char aa,int pos); //[OK]
    int Singlepvalue(char aa1,int pos1, char aa2, int pos2); //[OK]
    void SympvalueCalculation (int minlogp, float minssfraction, float mindeltafreq);//[OK]
    void pvalueCalculation(string outputgraph, int minlogp, float minssfraction, bool writefullgraph, float mindeltafreq, bool signedgraph);
    void GetCommunitiesFromFile(string clusterfilename); //[OK]
    void DeltaCommunitiesCalculation(void); //[OK]
    void DeltaCommunitiesOutput(string deltaoutputfilename); //[OK]
    void ElementRanking(string path, bool renumber, int seqnumber,int offset); //[OK]
    void SelfCorrelationMatrixCalculation(const std::vector <char> &aalist, const std::vector <int> &poslist); //[OK]
    void SCM2HTML(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist, bool renumber, int seqnumber, int offset); //[OK]
    void Write_SCM(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist); //[OK]
    void pMatrix2HTML(string path, bool renumber, int seqnumber); //[OK]
    float PSA(int seqnumber, int communitynumber); //[OK]
    int ADH_count(int seqnumber,int communitynumber);
    void CalculateHighlyConservedPositions();
    void SuccessiveRandomElimination(string outputfilename, int step, int repetitions, int endvalue=100);
    vector<float> DTRandomElimination(int repetitions, int max, int min, int step); //[OK]
    void Cluster2SCM(string clusterfilename, string path, bool renumber, int seqnumber, int offset, bool html, bool text); //[OK]
    void Cluster2PymolScript(string clusterfilename, string familyID, int seqnumber, int offset);
    void AlignmentWrite(string outputfilename); //[OK]
    vector<string> getSequencesName(); //[OK]
};

#endif // ALIGNMENT_H
