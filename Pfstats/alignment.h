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
    vector<float> minssData; //Resetando
    vector<float> consDG;//Resetando
    vector<string> consParams;
    vector<string> consRefSeqs;
    vector<vector<int> > consvfreq;//Resetando
    vector<vector<float> > consfreqPerc;//Resetando
    vector<tuple<string,string,int> > corrGraph;//Resetando
    vector<vector<string> > comunidades;//Resetando
    vector<string> corrRefSeqs;//Resetando
    vector<vector<string> > residuesComm;//Resetando
    vector<vector<string> > residuesCommPs;//Resetando
    vector<vector<vector<float> > > communityX;//Resetando
    vector<vector<float> > communityXAll;//Resetando
    vector<vector<vector<int> > > communityXps;//Resetando
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
    void clear();
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
    void removeFilterItem(int pos);
    string getFilterName(int i,int j);
    int getFilterSize();
    void addSequence();
    vector<tuple<string,string,int> > getCorrelationGraph();
    tuple<string,string,int> getCorrelationEdge(int i);
    int getCorrelationGraphSize();
    void addCorrRefSeq(string seq);
    string getCorrRefSeq(int i);
    void clearCorrRefSeq();
    int getCorrRefSeqsSize();
    void addCommunity(vector<string> comm);
    void clearCommunity();
    void printCorrGraph();
    void printCommunity();
    void addFilterSequence(vector<string> align);
    void addFilterSequence(vector<string> names, vector<string> sequences);
    void setConsDG(vector<float> dg);
    void addConsFreqRow(vector<int> consfreq);
    void addConsFreqPercRow(vector<float> cfreqperc);
    void clearConsRefs();
    void addConsRef(string ref);
    int getConsRefsSize();
    string getConsref(int i);
    void setMinssVector(vector<float> minss);
    void addCorrGraphEdge(string v1, string v2, int e);
    void addResiduesComm(vector<string> comm);
    void addResiduesCommPs(vector<string> comm);
    void addCommXAll(vector<float> comm);
    void addCommX(vector<vector<float> > comm);
    void addCommXps(vector<vector<int> > comm);
    void printConsFreq();
    void printConsFreqPerc();
    void printCorrRefSeqs();
    void printResiduesComm();
    void printResiduesCommPs();
    void printFrequencies();
    void loadFullAlignment();
    void addParameter(string tag, string filter, int refSeq, int offset, char chain, float minCons);//Conservation
    void addParameter(string tag, string filter, int repetitions);//Minss
    void addParameter(string tag, string filter, int minlog, float minssfraction, float mindeltafreq); //Correlation
    vector<vector<int> > createBlankIntMatrix(int i1, int j1, int v);
    void createBlankComunityVector(int x, int y, int z, float v);
    void createBlankComunityPsVector(int x, int y, int z, int v);
    //vector<string> getFilterParameters();
    vector<string> getConservationParameters();
    vector<string> getMinssParameters();
    vector<string> getCorrelationParameters();
    vector<string> getFullAlignment();
    vector<string> getFullSequences();
    int getConsFreqSize();
    int getConsFreqPercSize();
    int getCorrGraphSize();
    int getCommListSize();
    int getNumOfUtilComms();
    vector<int> getConsFreqRow(int i);
    vector<float> getConsFreqPercRow(int i);
    tuple<string,string,int> getCorrGraphTuple(int i);
    vector<string> getCommunitie(int i);
    vector<float> getCommXRow(int c, int i);
    vector<float> getCommAll(int c);
    vector<int> getCommPsRow(int c, int i);
    vector<string> getResiduesComm(int c);
    vector<string> getResiduesCommPs(int c);
    void updateFullAlignment();
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
    void IdentityTrimming(float maxid, float minocc, float minid, int refseq, string refseqName, string refSeq, bool intermediate = true, string newalignmentfilename="");//[OK]
    void IdentityMinimum(float minid, int refseq, float minocc, string refSeqName, string refSeq, bool intermediate = true, string newalignmentfilename="");//[OK]
    void AlignmentTrimming(float minocc, int refseq, string refseqName, string refSeq,bool intermediate = true, string newalignmentfilename="");//[OK]
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
    void writeCommtoPDB(string PDBfilename, string commPDBfilename, int initres, char chain, int seqnumber);
    void SubAlignmentIndices(char aa,int pos); //[OK]
    int SubAlignmentFrequency(char aa,int pos); //[OK]
    int Singlepvalue(char aa1,int pos1, char aa2, int pos2); //[OK]
    void SympvalueCalculation (int minlogp, float minssfraction, float mindeltafreq);//[OK]
    void pvalueCalculation(string outputgraph, int minlogp, float minssfraction, bool writefullgraph, float mindeltafreq, bool signedgraph);
    void GetCommunitiesFromFile(string clusterfilename); //[OK]
    void getCommunitiesFromRAM();
    void DeltaCommunitiesCalculation(void); //[OK]
    void DeltaCommunitiesOutput(string deltaoutputfilename); //[OK]
    void ElementRanking(string path, bool renumber, int seqnumber,int offset); //[OK]
    void SelfCorrelationMatrixCalculation(const std::vector <char> &aalist, const std::vector <int> &poslist); //[OK]
    void SCM2HTML(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist, bool renumber, int seqnumber, int offset); //[OK]
    void Write_SCM(string scmfilename,const std::vector <char> &aalist, const std::vector <int> &poslist); //[OK]
    void pMatrix2HTML(string path, bool renumber, int seqnumber); //[OK]
    void pMatrix2HTMLRAM(bool renumber, int seqnumber); //[OK]
    float PSA(int seqnumber, int communitynumber); //[OK]
    int ADH_count(int seqnumber,int communitynumber);
    void CalculateHighlyConservedPositions();
    void SuccessiveRandomElimination(string outputfilename, int step, int repetitions, int endvalue=100);
    vector<float> DTRandomElimination(int repetitions, int max, int min, int step); //[OK]
    void calculateShenkin(int numseqs);
    vector<float> ShenkinEntropy(int repetitions, int gapFilter);
    void Cluster2SCM(string clusterfilename, string path, bool renumber, int seqnumber, int offset, bool html, bool text); //[OK]
    void Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset); //[10%]
    void Cluster2PymolScript(string clusterfilename, string familyID, int seqnumber, int offset);
    void AlignmentWrite(string outputfilename); //[OK]
    vector<string> getSequencesName(); //[OK]
    string getSequence(string seqname);
    void exportAlignment(QString filename, string filter, int type); //TYPE: 0-PFAM, 1-TXT, 2-XML
    void exportFreq(QString filename, int type, bool perc=false); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML //PERC: TRUE = In %
    void exportConsRes(QString filename, int type, float mincons, vector<int> refSeqs); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportCorrGraph(QString filename, int type); //TYPE: 0-TXT 1-CSV 2-XML
    void exportCommList(QString filename, int type); //TYPE: 0-TXT 1-XML
    void exportCorrTable(QString filename, int type, bool perc=true); //TYPE: 0-TXT, 1-XML, 2-HTML
    void exportAdh(QString filename, int type); //TYPE: 0-TXT, 1-CSV, 2-XML, 3-HTML
    void exportResComm(QString filename, int type, vector<int> refSeqs); //TYPE: 0-TXT, 1-XML, 2-HTML
};

#endif // ALIGNMENT_H
