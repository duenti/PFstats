#include "alignment.h"
#include <omp.h>
#include <fstream>
#include <math.h>
#include "uniprot.h"
#include <cstdlib>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QFileDialog>
#include <QtNetwork>
#include <set>

Alignment::Alignment()
{
    refSeqName = "";
    minCons = 0.8;
}

Alignment::Alignment(string path){
    this->filepath = path;
    this->GetFromFile();
    refSeqName = "";
    minCons = 0.8;
}

Alignment::~Alignment()
{

}

void Alignment::setMinsCons(float v){
    minCons = v;
}

void Alignment::clear(){
    filepath.clear();
    filepath.shrink_to_fit();
    refSeqName.clear();
    refSeqName.shrink_to_fit();
    subalignmentseqs.clear();
    subalignmentseqs.shrink_to_fit();
    referencevector.clear();
    referencevector.shrink_to_fit();
    SortOrder.clear();
    SortOrder.shrink_to_fit();
    fullAlignment.clear();
    fullAlignment.shrink_to_fit();
    fullSequences.clear();
    fullSequences.shrink_to_fit();
    localdir = "";
    localdir.shrink_to_fit();
    webdir = "";
    webdir.shrink_to_fit();
    localpdbdir = "";
    localpdbdir.shrink_to_fit();
    webpdbdir = "";
    webpdbdir.shrink_to_fit();

    for(int i = 0; i < filtersList.size(); i++){
        filtersList[i].clear();
        filtersList[i].shrink_to_fit();
        filterSequences[i].clear();
        filterSequences[i].shrink_to_fit();
    }
    filtersList.clear();
    filtersList.shrink_to_fit();
    filterSequences.clear();
    filterSequences.shrink_to_fit();

    minssData.clear();
    minssData.shrink_to_fit();
    consDG.clear();
    consDG.shrink_to_fit();
    consParams.clear();
    consParams.shrink_to_fit();

    for(int i = 0; i < consvfreq.size(); i++){
        consvfreq[i].clear();
        consvfreq[i].shrink_to_fit();
        consfreqPerc[i].clear();
        consfreqPerc[i].shrink_to_fit();
    }
    consvfreq.clear();
    consvfreq.shrink_to_fit();
    consfreqPerc.clear();
    consfreqPerc.shrink_to_fit();

    corrGraph.clear();
    corrGraph.shrink_to_fit();

    for(int i = 0; i < comunidades.size(); i++){
        comunidades[i].clear();
        comunidades[i].shrink_to_fit();
    }
    comunidades.clear();
    comunidades.shrink_to_fit();

    refSeqs.clear();
    refSeqs.shrink_to_fit();

    for(int i = 0; i < residuesComm.size(); i++){
        residuesComm[i].clear();
        residuesComm[i].shrink_to_fit();
        residuesCommPs[i].clear();
        residuesCommPs[i].shrink_to_fit();
    }
    residuesComm.clear();
    residuesComm.shrink_to_fit();
    residuesCommPs.clear();
    residuesCommPs.shrink_to_fit();

    for(int i = 0; i < communityXAll.size(); i++){
        communityXAll[i].clear();
        communityXAll[i].shrink_to_fit();
    }
    communityXAll.clear();
    communityXAll.shrink_to_fit();

    for(int i = 0; i < communityX.size(); i++){
        for(int j = 0; j < communityX[i].size(); j++){
            communityX[i][j].clear();
            communityX[i][j].shrink_to_fit();
            communityXps[i][j].clear();
            communityXps[i][j].shrink_to_fit();
        }
        communityX[i].clear();
        communityX[i].shrink_to_fit();
        communityXps[i].clear();
        communityXps[i].shrink_to_fit();
    }
    communityX.clear();
    communityX.shrink_to_fit();
    communityXps.clear();
    communityXps.shrink_to_fit();

    parameters.clear();
    parameters.shrink_to_fit();
    sequences.clear();
    sequences.shrink_to_fit();
    sequencenames.clear();
    sequencenames.shrink_to_fit();

    for(int i = 0; i < frequencies.size(); i++){
        frequencies[i].clear();
        frequencies[i].shrink_to_fit();
    }
    frequencies.clear();
    frequencies.shrink_to_fit();

    for(int i = 0; i < subsetfrequencies.size(); i++){
        subsetfrequencies[i].clear();
        subsetfrequencies[i].shrink_to_fit();
    }
    subsetfrequencies.clear();
    subsetfrequencies.shrink_to_fit();

    for(int i = 0; i < Deltas.size(); i++){
        Deltas[i].clear();
        Deltas[i].shrink_to_fit();
    }
    Deltas.clear();
    Deltas.shrink_to_fit();

    Communities.clear();
    Communities.shrink_to_fit();

    for(int i = 0; i < AASpecificConservation.size(); i++){
        AASpecificConservation[i].clear();
        AASpecificConservation[i].shrink_to_fit();
    }
    AASpecificConservation.clear();
    AASpecificConservation.shrink_to_fit();

    dG.clear();
    dG.shrink_to_fit();
    dGDT.clear();
    dGDT.shrink_to_fit();
    normalizeddG.clear();
    normalizeddG.shrink_to_fit();
    hiconservedpos.clear();
    hiconservedpos.shrink_to_fit();

    for(int i = 0; i < minuslogpvalues.size(); i++){
        minuslogpvalues[i].clear();
        minuslogpvalues[i].shrink_to_fit();
    }
    minuslogpvalues.clear();
    minuslogpvalues.shrink_to_fit();

    for(int i = 0; i < selfcorrelationmatrix.size(); i++){
        selfcorrelationmatrix[i].clear();
        selfcorrelationmatrix[i].shrink_to_fit();
    }
    selfcorrelationmatrix.clear();
    selfcorrelationmatrix.shrink_to_fit();

    for(int i = 0; i < identitymatrix.size(); i++){
        identitymatrix[i].clear();
        identitymatrix[i].shrink_to_fit();
    }
    identitymatrix.clear();
    identitymatrix.shrink_to_fit();
}

string Alignment::getFilepath(){
    return this->filepath;
}

string Alignment::getLocalDir(){
    return this->localdir;
}

void Alignment::setLocalDir(string dir){
    this->localdir = dir;
}

string Alignment::getWebDir(){
    return this->webdir;
}

void Alignment::setWebDir(string dir){
    this->webdir = dir;
}

string Alignment::getLocalPDBDir(){
    return this->localpdbdir;
}

void Alignment::setLocalPDBDir(string dir){
    this->localpdbdir = dir;
}

string Alignment::getWebPDBDir(){
    return this->webpdbdir;
}

void Alignment::setWebPDBDir(string dir){
    this->webpdbdir = dir;
}

vector<vector<string> > Alignment::getAllFilters(){
    return this->filtersList;
}

vector<vector<string> > Alignment::getAllSequences(){
    return this->filterSequences;
}

void Alignment::removeFilterItem(int pos){
    filtersList[pos].clear();
    filtersList[pos].shrink_to_fit();
    filtersList.erase(filtersList.begin() + pos);

    filterSequences[pos].clear();
    filterSequences[pos].shrink_to_fit();
    filterSequences.erase(filterSequences.begin() + pos);
}

string Alignment::getFilterName(int i, int j){
    return this->filtersList[i][j];
}

int Alignment::getFilterSize(){
    return this->filtersList.size();
}

vector<tuple<string,string,int> > Alignment::getCorrelationGraph(){
    return this->corrGraph;
}

void Alignment::addRefSeq(string seq){
    this->refSeqs.push_back(seq);
}

string Alignment::getRefSeq(int i){
    return refSeqs[i];
}

void Alignment::clearRefSeq(){
    this->refSeqs.clear();
}

int Alignment::getRefSeqsSize(){
    return refSeqs.size();
}

tuple<string,string,int> Alignment::getCorrelationEdge(int i){
    return corrGraph[i];
}

int Alignment::getCorrelationGraphSize(){
    return corrGraph.size();
}

void Alignment::addCommunity(vector<string> comm){
    comunidades.push_back(comm);
}

void Alignment::addItemToCommunity(string res, int commindex){
    comunidades[commindex].push_back(res);
}

void Alignment::removeItemOfCommunity(int comm, int item){
    //QString text = "COMM: " + QString::number(comm) + " /ITEM: " + QString::number(item);
    //QMessageBox::information(NULL,"a",text);
    comunidades[comm].erase(comunidades[comm].begin() + item);
}

void Alignment::clearCommunity(){
    comunidades.clear();
}

void Alignment::printCorrGraph(){
    for(int i = 0; i < this->corrGraph.size(); i++){
        string v1 = std::get<0>(corrGraph[i]);
        string v2 = std::get<1>(corrGraph[i]);
        int value = std::get<2>(corrGraph[i]);

        printf("%s,%s: %d\n",v1.c_str(),v2.c_str(),value);
    }
}

void Alignment::printCommunity(){
    for(int i = 0; i < comunidades.size(); i++){
        printf("Comunidade %d:\n",i);
        for(int j = 0; j < comunidades[i].size(); j++){
            printf("%s\n",comunidades[i][j].c_str());
        }
        printf("\n");
    }
}

vector<string> Alignment::getFullAlignment(){
    //printf("\n%d\n",fullAlignment.size());
    return this->fullAlignment;
}

vector<string> Alignment::getFullSequences(){
    return this->fullSequences;
}

int Alignment::getSequencesSize(){
    return sequences.size();
}

int Alignment::getConsFreqSize(){
    return this->consvfreq.size();
}

int Alignment::getConsFreqPercSize(){
    return this->consfreqPerc.size();
}

int Alignment::getCorrGraphSize(){
    return this->corrGraph.size();
}

int Alignment::getCommListSize(){
    return this->comunidades.size();
}

int Alignment::getNumOfUtilComms(){
    return this->communityX.size();
}

vector<int> Alignment::getConsFreqRow(int i){
    return this->consvfreq[i];
}

vector<float> Alignment::getConsFreqPercRow(int i){
    return this->consfreqPerc[i];
}

tuple<string,string,int> Alignment::getCorrGraphTuple(int i){
    return this->corrGraph[i];
}

vector<string> Alignment::getCommunitie(int i){
    return this->comunidades[i];
}

vector<float> Alignment::getCommXRow(int c, int i){
    return this->communityX[c][i];
}

vector<int> Alignment::getCommPsRow(int c, int i){
    return this->communityXps[c][i];
}

vector<float> Alignment::getCommAll(int c){
    return this->communityXAll[c];
}

vector<string> Alignment::getResiduesComm(int c){
    return this->residuesComm[c];
}

vector<string> Alignment::getResiduesCommPs(int c){
    return this->residuesCommPs[c];
}

void Alignment::addFilterSequence(vector<string> align){
    this->filterSequences.push_back(align);
}

void Alignment::addFilterSequence(vector<string> names, vector<string> sequences){
    if(names[0] == "0 0 0 0"){
        if(fullAlignment.size() == 0){
            for(int i = 1; i < names.size(); i++){
                this->fullAlignment.push_back(names[i]);
                this->fullSequences.push_back(sequences[i]);
            }
        }
    }
    this->filtersList.push_back(names);
    this->filterSequences.push_back(sequences);
}

void Alignment::setConsDG(vector<float> dg){
    this->consDG = dg;
}

void Alignment::addConsFreqRow(vector<int> consfreq){
    this->consvfreq.push_back(consfreq);
}

void Alignment::addConsFreqPercRow(vector<float> cfreqperc){
    this->consfreqPerc.push_back(cfreqperc);
}

int Alignment::getUniprotMinedSize(){
    return uniprotMined.size();
}

void Alignment::addUniprotEntry(Uniprot *entry){
    uniprotMined.push_back(entry);
}

string Alignment::getUniprotEntryName(int i){
    return uniprotMined[i]->getName();
}

int Alignment::getUniprotEntryNofFeatures(int i){
    return uniprotMined[i]->countFeatures();
}

Feature* Alignment::getUniprotFeature(int i, int j){
    return uniprotMined[i]->getFeature(j);
}

string Alignment::uniprotEntryToString(int i){
    return uniprotMined[i]->toString();
}

void Alignment::setMinssVector(vector<float> minss){
    this->minssData = minss;
}

void Alignment::addCorrGraphEdge(string v1, string v2, int e){
    tuple<string,string,int> tup;
    std::get<0>(tup) = v1;
    std::get<1>(tup) = v2;
    std::get<2>(tup) = e;

    this->corrGraph.push_back(tup);
}

void Alignment::addResiduesComm(vector<string> comm){
    this->residuesComm.push_back(comm);
}

void Alignment::addResiduesCommPs(vector<string> comm){
    this->residuesCommPs.push_back(comm);
}

void Alignment::addCommXAll(vector<float> comm){
    this->communityXAll.push_back(comm);

    //printf("COMUNIDADE\n");
    //for(int i = 0; i < comm.size(); i++) printf("%f\n",comm[i]);
}

void Alignment::addCommX(vector<vector<float> > comm){
    this->communityX.push_back(comm);

    /*
    printf("COMUNIDADE\n");
    for(int i = 0; i < comm.size(); i++){
        for(int j = 0; j < comm[i].size(); j++){
            printf(" %f ",comm[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */
}

void Alignment::addCommXps(vector<vector<int> > comm){
    this->communityXps.push_back(comm);

    /*
    printf("COMUNIDADE\n");
    for(int i = 0; i < comm.size(); i++){
        for(int j = 0; j < comm[i].size(); j++){
            printf(" %d ",comm[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */
}

void Alignment::printConsFreq(){
    for(int i = 0; i < consvfreq.size(); i++){
        for(int j = 0; j < consvfreq[i].size(); j++){
            printf(" %d ",consvfreq[i][j]);
        }
        printf("\n");
    }
}

void Alignment::printConsFreqPerc(){
    for(int i = 0; i < consfreqPerc.size(); i++){
        for(int j = 0; j < consfreqPerc[i].size(); j++){
            printf(" %f ",consfreqPerc[i][j]);
        }
        printf("\n");
    }
}

void Alignment::printRefSeqs(){
    for(int i = 0; i < refSeqs.size(); i++){
        printf("%s\n",refSeqs[i].c_str());
    }
}

void Alignment::printResiduesComm(){
    for(int i = 0; i < this->residuesComm.size(); i++){
        printf("COMUNIDADE %d:\n",i);
        for(int j = 0; j < this->residuesComm[i].size(); j++){
            printf("%s\n",residuesComm[i][j].c_str());
        }
    }
}

void Alignment::printResiduesCommPs(){
    for(int i = 0; i < this->residuesCommPs.size(); i++){
        printf("COMUNIDADE %d:\n",i);
        for(int j = 0; j < this->residuesCommPs[i].size(); j++){
            printf("%s\n",residuesCommPs[i][j].c_str());
        }
    }
}

void Alignment::printFrequencies(){
    for(int i = 0; i < frequencies.size(); i++){
        for(int j = 0; j < frequencies[i].size(); j++){
            printf(" %d ",frequencies[i][j]);
        }
        printf("\n");
    }
}

void Alignment::loadFullAlignment(){
    this->sequences.clear();
    this->sequencenames.clear();

    for(int i = 0; i < this->fullAlignment.size(); i++){
        sequences.push_back(this->fullSequences[i]);
        sequencenames.push_back(this->fullAlignment[i]);
    }
}

void Alignment::addParameter(string tag, string filter, int refSeq, int offset, char chain, float minCons){
    string parameter = tag + "," + filter + "," + QString::number(refSeq).toStdString() + "," + QString::number(offset).toStdString() + "," + chain + "," + QString::number(minCons).toStdString();
    parameters.push_back(parameter);
    //QMessageBox::information(NULL,"Add Conservation",QString::number(parameters.size()));
}

void Alignment::addParameter(string tag, string filter, int repetitions){
    string parameter = tag + "," + filter + "," + QString::number(repetitions).toStdString();
    parameters.push_back(parameter);
}

void Alignment::addParameter(string tag, string filter, int minlog, float minssfraction, float mindeltafreq){
    string parameter = tag + "," + filter + "," + QString::number(minlog).toStdString() + "," + QString::number(minssfraction).toStdString() + "," + QString::number(mindeltafreq).toStdString();
    parameters.push_back(parameter);
}

vector<vector<int> > Alignment::createBlankIntMatrix(int i1, int j1, int v){
    vector<vector<int> > matrix;

    for(int i = 0; i < i1; i++){
        vector<int> vec
                ;
        for(int j = 0; j < j1; j++){
            vec.push_back(v);
        }
        matrix.push_back(vec);
    }

    return matrix;
}

vector<string> Alignment::getConservationParameters(){
    for(int i = 0; i < parameters.size(); i++){
        vector<string> splitVec = split(parameters[i],',');
        //QMessageBox::information(NULL,"ok",splitVec[0].c_str());
        if(splitVec[0] == "conservation") return splitVec;
    }

    vector<string> vecnull;
    return vecnull;
}

vector<string> Alignment::getMinssParameters(){
    for(int i = 0; i < parameters.size(); i++){
        vector<string> splitVec = split(parameters[i],',');
        if(splitVec[0] == "minss") return splitVec;
    }

    vector<string> vecnull;
    return vecnull;
}

vector<string> Alignment::getCorrelationParameters(){
    for(int i = 0; i < parameters.size(); i++){
        vector<string> splitVec = split(parameters[i],',');
        if(splitVec[0] == "correlation") return splitVec;
    }

    vector<string> vecnull;
    return vecnull;
}

string Alignment::getDir(){
    string path = "";
    vector<string> tmpVec = this->split(filepath,'/');

    for(int i = 0; i < tmpVec.size()-1; i++){
        path += tmpVec[i] + "/";
    }

    return path;
}

void Alignment::setFilepath(string path){
    this->filepath = path;
}

void Alignment::resetCommunities(){
    if (Communities.size()>0){
        for (int c1=0;c1<=Communities.size()-1;c1++){
            Communities[c1].pos.clear();
            Communities[c1].aa.clear();
        }
        Communities.clear();
    }

    tempcommunity.pos.clear();
    tempcommunity.aa.clear();
}

bool Alignment::validposition(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
        (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y')||
        (c=='X')||(c=='x')||(c=='.')||(c=='-')) return (true);
    else return(false);
}

bool Alignment::validstartcharacter(char c){
    if ((c=='a')||(c=='b')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='j')||(c=='k')||(c=='l')||(c=='m')||
        (c=='n')||(c=='o')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='u')||(c=='v')||(c=='w')||(c=='x')||(c=='y')||
        (c=='z')||(c=='A')||(c=='B')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='J')||(c=='K')||
        (c=='L')||(c=='M')||(c=='N')||(c=='O')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='U')||(c=='V')||(c=='W')||(c=='X')||
        (c=='Y')||(c=='Z')||(c=='0')||(c=='1')||(c=='2')||(c=='3')||(c=='4')||(c=='5')||(c=='6')||(c=='7')||(c=='8')||(c=='9')) return(true);
    else return(false);
}

int Alignment::freqmatrixposition(char c){
    if((c=='a')||(c=='A')) return 1;
    if((c=='c')||(c=='C')) return 2;
    if((c=='d')||(c=='D')) return 3;
    if((c=='e')||(c=='E')) return 4;
    if((c=='f')||(c=='F')) return 5;
    if((c=='g')||(c=='G')) return 6;
    if((c=='h')||(c=='H')) return 7;
    if((c=='i')||(c=='I')) return 8;
    if((c=='k')||(c=='K')) return 9;
    if((c=='l')||(c=='L')) return 10;
    if((c=='m')||(c=='M')) return 11;
    if((c=='n')||(c=='N')) return 12;
    if((c=='p')||(c=='P')) return 13;
    if((c=='q')||(c=='Q')) return 14;
    if((c=='r')||(c=='R')) return 15;
    if((c=='s')||(c=='S')) return 16;
    if((c=='t')||(c=='T')) return 17;
    if((c=='v')||(c=='V')) return 18;
    if((c=='w')||(c=='W')) return 19;
    if((c=='y')||(c=='Y')) return 20;
    if((c=='x')||(c=='X')||(c=='.')||(c=='-')) return 0;
    return 0;
}

int Alignment::getresn(string line){
    line=line.substr(22,4);
    for(int c1=3;c1>=0;c1--) if(line[c1]==' ') line.erase(c1,1);
    return atoi(line.c_str());
}

int Alignment::GetOffsetFromSeqName(string seqname){
    bool found=false;
    string offsetstr;
    int c1=0;

    while (c1<seqname.length()){
        if(seqname[c1]=='/'){
            found=true;
            c1++;
            break;
        }
        c1++;
    }

    if (!found) return 0;

    while (c1<seqname.length()){
        if(seqname[c1]=='-') break;
        else offsetstr+=seqname[c1];
        c1++;
    }

    return(atoi(offsetstr.c_str())-1);
}

bool Alignment::isaa(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
       (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
       (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
       (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y'))
            return (true);
    else return false;
}

bool Alignment::isaax(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
        (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y')||(c=='X'))
         return true;
    else return false;
}

char Alignment::num2aa(int n){
    if(n==1) return ('A');
    if(n==2) return ('C');
    if(n==3) return ('D');
    if(n==4) return ('E');
    if(n==5) return ('F');
    if(n==6) return ('G');
    if(n==7) return ('H');
    if(n==8) return ('I');
    if(n==9) return ('K');
    if(n==10) return ('L');
    if(n==11) return ('M');
    if(n==12) return ('N');
    if(n==13) return ('P');
    if(n==14) return ('Q');
    if(n==15) return ('R');
    if(n==16) return ('S');
    if(n==17) return ('T');
    if(n==18) return ('V');
    if(n==19) return ('W');
    if(n==20) return ('Y');
    return('-');
}

long double Alignment::lnbdf(int N, int nx, float px){
    if(N==nx) return ((long double)N*logl((long double)px));
    if(nx==0) return ((long double)N*logl((long double)(1.0-px)));
    return (stirling(N)-stirling(nx)-stirling(N-nx)+((long double)nx)*logl((long double)px)+((long double)(N-nx))*logl(1-(long double)(px)));
}

long double Alignment::lnfact(int x){
    long double result=1.0;
    if ((x==0)||(x==1)) return(0.0);
    else for (int i=1;i<=x;i++) result=result*((long double)i);
    return (logl(result));
}

long double Alignment::stirling(int x){
    if(x<=8) return(lnfact(x));
    return ((((long double)x)+0.5)*logl((long double)x)-x+0.918938533205);
}

long Alignment::eto10(long double x){
    return (x/((long double)2.30258509299));
}

long double Alignment::cbd_tietjen(int N, int n, float freq, bool right){
    long double a=pow(1-freq,N);

    if((!right)&&(n==0)) return a;
    if((right)&&(n==0)) return 1;

    long double sum=0;
    if(!right) sum=a;

    float u=freq/(1-freq);

    for(int i=2;i<=N+1;i++){
        a=a*u*((float)(N+2-i))/((float)(i-1));
        if(((!right)&&(i<=n+1))||((right)&&(i-1>=n)))
            sum+=a;
    }

    return sum;
}

int Alignment::cbd(int N, int n, float freq, bool right){
    if(pow(1-freq,N)!=0) return ((int)ceil(log10(cbd_tietjen(N,n,freq,right))));
    float minP;
    float sum=0;
    float *Ps = new float [(N-n)+1];
    float *lPs = new float [n+1];

    if ((!Ps)||(!lPs)){
        QMessageBox::critical(NULL,"ERROR","Insuficient memory");
        return 1;
    }

    minP=(float)eto10(lnbdf(N,n,freq));
    if(right){
        for (int i=n;i<=N;i++){
            Ps[i-n]=(float)eto10(lnbdf(N,i,freq));
            if(Ps[i-n]>minP) minP=Ps[i-n];
        }

        for (int i=n;i<=N;i++){
            sum+=pow(10,Ps[i-n]-floor(minP));
        }
    }else{
        for (int i=0;i<=n;i++){
            lPs[i]=(float)eto10(lnbdf(N,i,freq));

            if(lPs[i]>minP) minP=lPs[i];

            for (int i=0;i<=n;i++)
                sum+=pow(10,lPs[i]-floor(minP));
        }
    }
    delete Ps;
    delete lPs;

    return(int(floor(logl(sum))+floor(minP)));
}

string Alignment::outputBfactor(string line, float Bf){
    char Bfchar[10];
    string Bfstring;
    int bsize;

    sprintf(Bfchar,"%-5.1f",Bf);
    Bfstring=(string)Bfchar;
    for(int i = 0; i < Bfstring.length(); i++){
        if(Bfstring[i] == ',') Bfstring[i] = '.';
    }
    bsize=Bfstring.size();
    if(Bfstring.size()<6) for (int c1=1;c1<=6-bsize;c1++) Bfstring=" "+Bfstring;
    return(line.substr(0,60)+Bfstring+line.substr(66));
}

vector<string> Alignment::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

string Alignment::getRefSeqName(){
    return refSeqName;
}

void Alignment::setRefSeqName(string ref){
    refSeqName = ref;
}

int Alignment::getRefSeqOffset(){
    if(refSeqName == "") return 0;

    vector<string> tokens = split(refSeqName,'/');
    string range = tokens[1];
    //printf("\nRANGE: %s\n",range.c_str());
    vector<string> tokens2 = split(range,'-');
    QString qoffset = QString::fromStdString(tokens2[0]);
    //printf("\nQOffset: %s\n",qoffset.toStdString().c_str());
    bool ok;
    int offset = qoffset.toInt(&ok);
    //printf("\nOffset: %d\n",offset);

    if(ok) return offset -1;
    return 0;
}

void Alignment::generateXML(string outputXML){
    QFile f(outputXML.c_str());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);

    out << "<?xml version=\"1.0\"?>\n\n";
    out << "<PFStats>\n";
    out << "<file>\n";
    if(this->localdir != "")
        out << "   <local>" << this->localdir.c_str() << "</local>\n";
    if(this->webdir != "")
        out << "   <web>" << this->webdir.c_str() << "</web>\n";
    if(this->localpdbdir != "")
        out << "   <pdb>" << this->localpdbdir.c_str() << "</pdb>\n";
    out << "</file>\n";

    //QMessageBox::warning(NULL,"teste",QString::number(this->filtersList.size()));

    if(filtersList.size() > 0){

        out << "<filters>\n";

        for(int i = 0; i < filtersList.size(); i++){
            string parameters = filtersList[i][0];
            vector<string> parsVec = this->split(parameters,' ');
            string occ = parsVec[0];
            string minid = parsVec[1];
            string maxid = parsVec[2];
            string refseq = parsVec[3];

            out << "<filter occ='" << occ.c_str() << "' minid='" << minid.c_str() << "' maxid='" << maxid.c_str() << "' refseq='" << refseq.c_str() << "' >\n";
            for(int j = 1; j < filtersList[i].size(); j++){
                vector<string> vecSplit = this->split(filtersList[i][j],'/');
                out << "   <entry id='" << j-1 << "' offset='" << vecSplit[1].c_str() << "' name='" << vecSplit[0].c_str() << "'>" << filterSequences[i][j].c_str() << "</entry>\n";
            }
            out << "</filter>\n";
        }

        out << "</filters>\n";
    }

    if(refSeqs.size() > 0){
        out << "<references>\n";

        for(int i = 0; i < refSeqs.size(); i++){
            out << "   <protein>" << refSeqs[i].c_str() << "</protein>\n";
        }

        out << "</references>\n";
    }

    if(consDG.size() > 0){
        out << "<conservation>\n";

        vector<string> consPars = this->getConservationParameters();
        if(consPars.size() > 0){
            out << "   <parameters>\n";

            if(consPars.size() >4){
                out << "      <filter>" << consPars[1].c_str() << "</filter>\n";
                out << "      <refseq>" << consPars[2].c_str() << "</refseq>\n";
                out << "      <offset>" << consPars[3].c_str() << "</offset>\n";
                out << "      <chain>" << consPars[4].c_str() << "</chain>\n";
            }

            out << "   </parameters>\n";
        }
        out << "   <positions>\n";
        for(int i = 0; i < consDG.size(); i++){
            out << "   <pos id='" << i+1 << "'>\n";
            out << "      <deltaG>" << consDG[i] << "</deltaG>\n";
            out << "      <GAP>\n";
            out << "         <frequence>" << consvfreq[i][0] << "</frequence>\n";
            out << "      </GAP>\n";
            out << "      <ALA>\n";
            out << "         <frequence>" << consvfreq[i][1] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][0] << "</percent>\n";
            out << "      </ALA>\n";
            out << "      <CYS>\n";
            out << "         <frequence>" << consvfreq[i][2] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][1] << "</percent>\n";
            out << "      </CYS>\n";
            out << "      <ASP>\n";
            out << "         <frequence>" << consvfreq[i][3] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][2] << "</percent>\n";
            out << "      </ASP>\n";
            out << "      <GLU>\n";
            out << "         <frequence>" << consvfreq[i][4] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][3] << "</percent>\n";
            out << "      </GLU>\n";
            out << "      <PHE>\n";
            out << "         <frequence>" << consvfreq[i][5] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][4] << "</percent>\n";
            out << "      </PHE>\n";
            out << "      <GLY>\n";
            out << "         <frequence>" << consvfreq[i][6] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][5] << "</percent>\n";
            out << "      </GLY>\n";
            out << "      <HIS>\n";
            out << "         <frequence>" << consvfreq[i][7] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][6] << "</percent>\n";
            out << "      </HIS>\n";
            out << "      <ILE>\n";
            out << "         <frequence>" << consvfreq[i][8] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][7] << "</percent>\n";
            out << "      </ILE>\n";
            out << "      <LYS>\n";
            out << "         <frequence>" << consvfreq[i][9] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][8] << "</percent>\n";
            out << "      </LYS>\n";
            out << "      <LEU>\n";
            out << "         <frequence>" << consvfreq[i][10] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][9] << "</percent>\n";
            out << "      </LEU>\n";
            out << "      <MET>\n";
            out << "         <frequence>" << consvfreq[i][11] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][10] << "</percent>\n";
            out << "      </MET>\n";
            out << "      <ASN>\n";
            out << "         <frequence>" << consvfreq[i][12] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][11] << "</percent>\n";
            out << "      </ASN>\n";
            out << "      <PRO>\n";
            out << "         <frequence>" << consvfreq[i][13] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][12] << "</percent>\n";
            out << "      </PRO>\n";
            out << "      <GLN>\n";
            out << "         <frequence>" << consvfreq[i][14] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][13] << "</percent>\n";
            out << "      </GLN>\n";
            out << "      <ARG>\n";
            out << "         <frequence>" << consvfreq[i][15] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][14] << "</percent>\n";
            out << "      </ARG>\n";
            out << "      <SER>\n";
            out << "         <frequence>" << consvfreq[i][16] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][15] << "</percent>\n";
            out << "      </SER>\n";
            out << "      <THR>\n";
            out << "         <frequence>" << consvfreq[i][17] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][16] << "</percent>\n";
            out << "      </THR>\n";
            out << "      <VAL>\n";
            out << "         <frequence>" << consvfreq[i][18] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][17] << "</percent>\n";
            out << "      </VAL>\n";
            out << "      <TRP>\n";
            out << "         <frequence>" << consvfreq[i][19] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][18] << "</percent>\n";
            out << "      </TRP>\n";
            out << "      <TYR>\n";
            out << "         <frequence>" << consvfreq[i][20] << "</frequence>\n";
            out << "         <percent>" << consfreqPerc[i][19] << "</percent>\n";
            out << "      </TYR>\n";
            out << "   </pos>\n";
        }
        out << "   </positions>\n";

        out << "</conservation>\n";
    }

    vector<string> minssParam = this->getMinssParameters();
    if(minssParam.size() > 0){

        out << "<minss>\n";

        out << "   <parameters>\n";



        if(minssParam.size() > 2){
            out << "      <filter>" << minssParam[1].c_str() << "</filter>\n";
            out << "      <repetitions>" << minssParam[2].c_str() << "</repetitions>\n";
        }

        out << "   </parameters>\n";

        for(int i = 0; i < this->minssData.size(); i++){
            out << "   <data id='" << i+1 << "'>" << minssData[99-i] << "</data>\n";
        }

        out << "</minss>\n";
    }

    vector<string> corrParam = this->getCorrelationParameters();
    if(corrParam.size() > 0){

        out << "<correlation>\n";
        out << "   <parameters>\n";



        if(corrParam.size() > 4){
            out << "      <filter>" << corrParam[1].c_str() << "</filter>\n";
            out << "      <minlog>" << corrParam[2].c_str() << "</minlog>\n";
            out << "      <minss>" << corrParam[3].c_str() << "</minss>\n";
            out << "      <deltafreq>" << corrParam[4].c_str() << "</deltafreq>\n";
        }

        out << "   </parameters>\n";

        if(corrGraph.size() > 0){

            out << "   <corrgraph>\n";

            for(int i = 0; i < corrGraph.size(); i++){
                string v1 = std::get<0>(corrGraph[i]);
                string v2 = std::get<1>(corrGraph[i]);
                int val = std::get<2>(corrGraph[i]);

                out << "      <edge v1='" << v1.c_str() << "' v2='" << v2.c_str() << "'>" << QString::number(val) << "</edge>\n";
            }

            out << "   </corrgraph>\n";
        }

        if(comunidades.size() > 0){

            out << "   <communities>\n";

            for(int i = 0; i < comunidades.size(); i++){
                out << "      <community id='" << i+1 << "'>\n";

                for(int j = 0; j < comunidades[i].size(); j++){
                    out << "         <node>" << comunidades[i][j].c_str() << "</node>\n";
                //QMessageBox::information(NULL,QString::number(i),comunidades[i][j].c_str());
                }
                out << "      </community>\n";
            }

            out << "   </communities>\n";
        }


        if(communityX.size() > 0 || communityXps.size() > 0){

            out << "   <output>\n";

            for(int i = 0; i < this->communityX.size(); i++){
                out << "      <community id='" << i + 1 << "'>\n";


                out << "         <table>\n";

                out << "            <column>ALL</column>\n";
                for(int j = 0; j < this->residuesComm[i].size(); j++){
                    out << "            <column>" << this->residuesComm[i][j].c_str() << "</column>\n";
                }

                out << "         </table>\n";

                out << "         <table_data>\n";

                for(int j = 0; j < this->communityX[i].size(); j++){
                    out << "            <row id='" << j << "' c0='" << this->communityXAll[i][j] << "' ";
                    for(int k = 0; k < this->communityX[i][j].size(); k++){
                        if(j==k) out << "c" << k+1 << "='X' ";
                        else out << "c" << k+1 << "='" << this->communityX[i][j][k]*100 << "' ";
                    }
                    out << "/>\n";
                }

                out << "         </table_data>\n";

                out << "      </community>\n";
            }

            //printf("CXPS: %d / CXPSSIZE: %d", this->communityXps.size(), residuesCommPs.size());

            for(int i = 0; i < this->communityXps.size(); i++){
                out << "      <logP c='" << i+1 << "'>\n";

                out << "         <table>\n";

                for(int j = 0; j < this->residuesCommPs[i].size(); j++){
                    out << "            <column>" << this->residuesCommPs[i][j].c_str() << "</column>\n";
                }

                out << "         </table>\n";

                out << "         <table_data>\n";

                for(int j = 0; j < this->communityXps[i].size(); j++){
                    out << "            <row id='" << j << "' ";
                    for(int k = 0; k < this->communityXps[i][j].size(); k++){
                        if(j==k) out << "c" << k << "='X' ";
                        else out << "c" << k << "='" << this->communityXps[i][j][k] << "' ";
                    }
                    out << "/>\n";
                }

                out << "         </table_data>\n";

                out << "      </logP>\n";
            }

            out << "   </output>\n";
        }

        out << "</correlation>\n";
    }

    if(uniprotMined.size() > 0){
        //Getting proteins names
        set<string> proteins;

        for(int i = 0; i < uniprotMined.size(); i++)
                proteins.insert(uniprotMined[i]->getName());


        out << "<uniprot>\n";

        for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
            string protName = *it;

            out << "   <protein name=\"" << protName.c_str() << "\" ";

            for(int i = 0; i < uniprotMined.size(); i++){
                Uniprot* entryprot = uniprotMined[i];

                if(protName == entryprot->getName()){
                    if(entryprot->getDataset() == 0) out << "dataset=\"Swiss-Prot\">\n";
                    else out << "dataset=\"TrEMBL\">\n";
                    break;
                }
            }

            for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature *f = entryprot->getFeature(j);

                            if(f->getAgregate() == 0) out << "      <feature agregate=\"CONS\" ";
                            else out << "      <feature agregate=\"" << f->getAgregate() << "\" ";

                            if(f->getResidueColigated() != "")
                                out << "seqResidue=\"" << f->getResidueColigated().c_str() << "\" ";
                            if(f->getAlignResidue() != "")
                                out << "alignResidue=\"" << f->getAlignResidue().c_str() << "\" ";
                            if(f->getType() != "")
                                out << "type=\"" << f->getType().c_str() << "\" ";
                            if(f->getDescription() != "")
                                out << "description=\"" << f->getDescription().c_str() << "\" ";
                            if(f->getId() != "")
                                out << "id=\"" << f->getId().c_str() << "\" ";
                            out << ">\n";

                            if(f->getOriginal() != "")
                                out << "         <original>" << f->getOriginal().c_str() << "</original>\n";
                            if(f->getVariation() != "")
                                out << "         <variation>" << f->getVariation().c_str() << "</variation>\n";

                            if(f->getBegin() != -1 || f->getPosition() != -1){
                                out << "         <location>\n";

                                if(f->getPosition() != -1)
                                    out << "            <position position=\"" << f->getPosition() << "\"/>\n";

                                if(f->getBegin() != -1 && f->getEnd() != -1){
                                    out << "            <begin position=\"" << f->getBegin() << "\"/>\n";
                                    out << "            <end position=\"" << f->getEnd() << "\"/>\n";
                                }

                                out << "         </location>\n";
                            }

                            out << "      </feature>\n";
                        }

                    }
                }

                out << "   </protein>\n";
        }

        out << "</uniprot>\n";
    }

    out << "</PFStats>";
    f.close();
}

bool Alignment::GetFromFile(){
    fstream alignmentfile;
    string line;
    bool flag1;      // 0 when still in sequence name
    bool flag2;      // 0 when still before sequence start
    int c1,c2;
    //string fseqname; // temporary sequence name from file

    if (sequences.size()>0) for(c1=0;c1<=sequences.size()-1;c1++) sequences[c1]="";
    sequences.clear();
    if (sequencenames.size()>0) for(c1=0;c1<=sequencenames.size()-1;c1++) sequencenames[c1]="";
    sequencenames.clear();

    alignmentfile.open(this->filepath.c_str());
    while(!alignmentfile.eof()){
        getline(alignmentfile,line);
        //printf("%s\n",line.c_str());
        flag1=0;
        flag2=0;
        //fseqname="";
        if(validstartcharacter(line[0])){
            //printf("%s\n",line.c_str());
            sequencenames.push_back("");
            sequences.push_back("");
            for (int c1=0;c1<=line.size()-1;c1++){
                 if(flag2) sequences[sequences.size()-1]+=line.substr(c1,1);
                 if((flag1)&&(!flag2)){
                    if (validposition(line[c1])){
                        sequences[sequences.size()-1]+=line.substr(c1,1);
                        flag2=true;
                    }
                 }
                 if((!flag1)&&(!flag2)){
                    //c=line.c_str()[i];
                    if (((char)line.c_str()[c1]==' ')||((char)line.c_str()[c1]=='\t')) flag1=true;
                    else sequencenames[sequencenames.size()-1]+=line.substr(c1,1);
                 }
            }
        }
    }
    alignmentfile.close();
    // CHECKS ALIGNMENT CONSISTENCY
    SortOrder.clear();
    if (subsetfrequencies.size()>0) for(c1=0;c1<=subsetfrequencies.size()-1;c1++)
        subsetfrequencies[c1].clear();
        subsetfrequencies.clear();
    if(sequences.size()>0){
        for(c1=1;c1<=sequences.size()-1;c1++)
        if(sequences[0].size()!=sequences[c1].size() || sequences[c1].size() == 0){
            printf("Sequence #%d (%s) does not has the same size of the first sequence. Please check your alignment file",c1+1,sequencenames[c1].c_str());
            return false;
        }

        for (c1=0;c1<=sequences.size()-1;c1++) SortOrder.push_back(c1);
        for(c1=0;c1<=sequences[0].size();c1++){ // total positions: sequencesize + 1 (positions + totals)
            subsetfrequencies.push_back( vector<int>(21) );
            for(c2=0; c2<=20; c2++)
                subsetfrequencies[c1].push_back(0);
        }

        for(int i = 0; i < sequencenames.size(); i++){
            this->fullAlignment.push_back(sequencenames[i]);
            this->fullSequences.push_back(sequences[i]);
        }

        return true;
    }

    return false;
}

bool Alignment::checkConsistency(){
    int c1,c2;

    SortOrder.clear();
    if (subsetfrequencies.size()>0) for(c1=0;c1<=subsetfrequencies.size()-1;c1++)
        subsetfrequencies[c1].clear();
        subsetfrequencies.clear();
    if(sequences.size()>0){
        for(c1=1;c1<=sequences.size()-1;c1++)
        if(sequences[0].size()!=sequences[c1].size()){
            printf("Sequence #%d (%s) does not has the same size of the first sequence. Please check your alignment file",c1+1,sequencenames[c1].c_str());
            return false;
        }

        for (c1=0;c1<=sequences.size()-1;c1++) SortOrder.push_back(c1);
        for(c1=0;c1<=sequences[0].size();c1++){ // total positions: sequencesize + 1 (positions + totals)
            subsetfrequencies.push_back( vector<int>(21) );
            for(c2=0; c2<=20; c2++)
                subsetfrequencies[c1].push_back(0);
        }
    }

    this->fullAlignment.clear();
    this->fullSequences.clear();
    for(int i = 0; i < sequencenames.size(); i++){
        this->fullAlignment.push_back(sequencenames[i]);
        this->fullSequences.push_back(sequences[i]);
    }
}

void Alignment::updateFullAlignment(){
    sequences.clear();
    sequencenames.clear();

    for(int i = 1; i < filtersList[0].size(); i++){
        sequences.push_back(this->filterSequences[0][i]);
        //printf("%s\n",filtersList[0][i].c_str());
        sequencenames.push_back(this->filtersList[0][i]);
    }
}

bool Alignment::getFromStd(string text){
    //Implementar
}

vector<string> Alignment::getSequencesName(){
    /*
    vector<string> names;
    ifstream sequenceFile(this->filepath.c_str());
    string line = "";

    if (sequenceFile.is_open()){
        while ( getline (sequenceFile,line) ){
            string prefix = "";

            for(int i = 0; i < line.length(); i++){
                if(line[i] == '/') break;
                    prefix += line[i];
            }
            names.push_back(prefix);
        }
    }
    return names;
    */

    return sequencenames;
}

string Alignment::getSequence(string seqname){
/*
    for(int i = 0; i < this->sequencenames.size(); i++){
        vector<string> splitVec = this->split(sequencenames[i].c_str(),'/');
        //printf("%s\n",splitVec[0].c_str());

        if(splitVec[0] == seqname)
            return this->sequences[i];
    }

    return "Error! Sequence not found";
    */

    for(int i = 0; i < sequencenames.size(); i++){
        if(sequencenames[i] == seqname) return sequences[i];
    }
}

void Alignment::CalculateFrequencies(){
    long double partialresult;
    int c1,c2;

    frequencies.clear();

    // FREQUENCE MATRIX INITIALIZATION
    for(c1=0;c1<=sequences[0].size();c1++){ // total positions: sequencesize + 1 (positions + totals)
        frequencies.push_back( vector<int>(21) );
        for(c2=0; c2<=20; c2++)
            frequencies[c1].push_back(0);
    }

    // INSERT AMINO ACID FREQUENCES ON EACH POSITION OF THE ALIGNMENT
    for(c1=0;c1<=sequences.size()-1;c1++){
        for(c2=0;c2<=sequences[0].size()-1;c2++){
            frequencies[c2][freqmatrixposition(sequences[c1][c2])]++;
            frequencies[sequences[0].size()][freqmatrixposition(sequences[c1][c2])]++;
        }
    }

    for (c1=1;c1<=20;c1++){
        partialresult=(long double)(frequencies[sequences[0].size()][c1]);
        partialresult=partialresult/((long double)((sequences.size()*sequences[0].size())-frequencies[sequences[0].size()][0]));
        meanf[c1]=partialresult;
    }
}

int Alignment::SeqSize(int seq){
    int size=0;
    for (int i=0;i<=sequences[seq].size()-1;i++)
        if(isaa(sequences[seq][i])) size++;

    return size;
}

float Alignment::Identity(int seq1, int seq2){
    int identcount=0;
    int seqbegin=0,seqend=sequences[0].size()-1,c3;
    int alignsize=0;

    while(true){
        if (((freqmatrixposition(sequences[seq1][seqbegin])>0)&&(freqmatrixposition(sequences[seq2][seqbegin])>0))||(seqbegin==sequences[0].size()-1)) break;
        else seqbegin++;
    }

    while(true){
        if (((freqmatrixposition(sequences[seq1][seqend])>0)&&(freqmatrixposition(sequences[seq2][seqend])>0))||(seqend==1)) break;
        else seqend--;
    }

    for(c3=seqbegin;c3<=seqend;c3++){
        if((sequences[seq1][c3]==sequences[seq2][c3])&&(isaa(sequences[seq1][c3]))){
            identcount++;
            alignsize++;
        }else{
            if(isaa(sequences[seq1][c3])) alignsize++;
        }
    }

    return((float)identcount/(float)alignsize);
}

int Alignment::seqcode2seqint(string refseqcode){
    short int maxcompare;
    int c1,c2;
    bool seqfound;

    for(c1=0;c1<=sequencenames.size()-1;c1++){
        seqfound=true;
        if(sequencenames[c1].size()>=(refseqcode).size()) maxcompare=(refseqcode).size();
        else maxcompare=sequencenames[c1].size();

        for(c2=0;c2<=maxcompare-1;c2++){
            if(sequencenames[c1][c2]!=refseqcode[c2]){
                seqfound=false;
                break;
            }
        }
        if (seqfound) return c1;
    }
    return -1;
}

int Alignment::seqname2seqint(string refseqcode){
    for(int i = 0; i < sequencenames.size(); i++){
        vector<string> vecSplit = this->split(sequencenames[i],'/');
        if(vecSplit[0] == refseqcode) return i;
    }
    return 0;
}

void Alignment::AlignmentTrimming(float minocc, int refseq, string refseqName, string refSeq, bool intermediate, string newalignmentfilename){
    //printf("%d",sequences.size());
    QProgressDialog progress("Trimming Alignment...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    int c1,c2,totalseq,totalaln;

    for(c1=0; c1<sequences.size()-1;c1++){
        progress.setValue(c1);

        if(progress.wasCanceled()) break;

        if(c1 != refseq){
            totalseq = 0;
            totalaln = 0;
            for (c2=0;c2<=sequences[c1].size()-1;c2++){
                if(isaa(sequences[refseq][c2])){
                    totalseq++;
                    if(isaa(sequences[c1][c2])) totalaln++;
                }
            }
            if (((float)totalaln)/((float)totalseq)<minocc){
                sequences[c1].clear();
                sequencenames[c1].clear();
                sequences.erase(sequences.begin()+c1);
                sequencenames.erase(sequencenames.begin()+c1);
                if (c1>0) c1--;
            }
        }
    }

    if(intermediate){
        vector<string> filterVec;
        string parameters = QString::number(minocc).toStdString() + " 0 0 " + refseqName;
        filterVec.push_back(parameters);
        filterVec.push_back(refseqName);
        for(int i = 0; i < sequencenames.size(); i++){
            if(sequencenames[i] != refseqName)
                filterVec.push_back(sequencenames[i]);
        }

        vector<string> sequenceVec;
        sequenceVec.push_back(parameters);
        sequenceVec.push_back(refSeq);
        for(int i = 0; i < sequences.size(); i++){
            if(sequencenames[i] != refseqName)
                sequenceVec.push_back(sequences[i]);
        }

        filtersList.push_back(filterVec);
        filterSequences.push_back(sequenceVec);
    }

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);

}

void Alignment::IdentityMinimum(float minid, int refseq, float minocc, string refSeqName, string refSeq, bool intermediate, string newalignmentfilename){
    //printf("%d",sequences.size());
    QProgressDialog progress("Culling Minimum Identity...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    int c1;

    for (c1=0;c1<=sequences.size()-1;c1++){
        //printf("%d\n",c1);
        progress.setValue(c1);

        if(progress.wasCanceled()) break;

        if(c1!=refseq){
            if (Identity(c1,refseq)<minid){
                sequences[c1].clear();
                sequencenames[c1].clear();
                sequences.erase(sequences.begin()+c1);
                sequencenames.erase(sequencenames.begin()+c1);
                if (c1>0) c1--;
            }
        }
    }

    if(intermediate){
        vector<string> filterVec;
        string parameters = QString::number(minocc).toStdString() + " " + QString::number(minid).toStdString() + " 0 " + refSeqName;
        filterVec.push_back(parameters);
        filterVec.push_back(refSeqName);
        for(int i = 0; i < sequencenames.size(); i++){
            if(sequencenames[i] != refSeqName)
                filterVec.push_back(sequencenames[i]);
        }

        vector<string> sequenceVec;
        sequenceVec.push_back(parameters);
        sequenceVec.push_back(refSeq);
        for(int i = 0; i < sequences.size(); i++){
            if(sequencenames[i] != refSeqName)
                sequenceVec.push_back(sequences[i]);
        }

        filtersList.push_back(filterVec);
        filterSequences.push_back(sequenceVec);
    }

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);
}

void Alignment::IdentityTrimming(float maxid, float minocc, float minid, int refseq, string refseqName, string refSeq, bool intermediate, string newalignmentfilename){
    //printf("%d",sequences.size());
    QProgressDialog progress("Trimming Identity...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    int seq1,seq2,c1,c2;
    seq1=0;
    printf("%d",sequences.size());
    while(true){ //for(seq1=0;seq1<=sequences.size()-2;seq1++)
        progress.setValue(seq1);
        progress.setMaximum(sequences.size());
        //printf("%d\n",seq1);
        if(progress.wasCanceled()) break;

        if(seq1>=sequences.size()-2) break;

        seq2=seq1+1;
        while(true){
            if(seq2>=sequences.size()-1) break;
            if(Identity(seq1,seq2)>maxid){
                if(SeqSize(seq2)<=SeqSize(seq1)){
                    sequences[seq2].clear();
                    sequencenames[seq2].clear();
                    sequences.erase(sequences.begin()+seq2);
                    sequencenames.erase(sequencenames.begin()+seq2);
                }else{
                    sequences[seq1].clear();
                    sequencenames[seq1].clear();
                    sequences.erase(sequences.begin()+seq1);
                    sequencenames.erase(sequencenames.begin()+seq1);
                    if(seq1>=sequences.size()-2) break;
                }

            }else seq2++;
        }
        seq1++;
    }

    if(intermediate){
        vector<string> filterVec;
        string parameters = QString::number(minocc).toStdString() + " " + QString::number(minid).toStdString() + " " + QString::number(maxid).toStdString() + " " + refseqName;
        filterVec.push_back(parameters);
        filterVec.push_back(refseqName);
        for(int i = 0; i < sequencenames.size(); i++){
            if(sequencenames[i] != refseqName)
                filterVec.push_back(sequencenames[i]);
        }

        vector<string> sequenceVec;
        sequenceVec.push_back(parameters);
        sequenceVec.push_back(refSeq);
        for(int i = 0; i < sequences.size(); i++){
            if(sequencenames[i] != refseqName)
                sequenceVec.push_back(sequences[i]);
        }

        filtersList.push_back(filterVec);
        filterSequences.push_back(sequenceVec);
    }

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);
}

void Alignment::AlignmentWrite(string outputfilename){
    //FILE *outputfile;
    int c1;

    QFile f(outputfilename.c_str());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);


    //printf("SeqName: %d, Seq: %d", sequencenames.size(),sequences.size());

    for(c1=0;c1<=sequencenames.size()-1;c1++){
        out << sequencenames[c1].c_str() << "   " << sequences[c1].c_str() << "\n";
        //printf("%s   %s\n", sequencenames[c1].c_str(),sequences[c1].c_str());
        //fprintf(outputfile,"%s   %s\n", sequencenames[c1].c_str(),sequences[c1].c_str());
    }

    f.close();
}

void Alignment::dGCalculation(){
    int c1,c2;
    long double partialresult;
    for(c1=0;c1<=sequences[0].size()-1;c1++){
        partialresult=0;
        for(c2=1; c2<=20; c2++){
            //partialresult+=pow(lnbdf(sequences.size()-frequencies[c1][0],frequencies[c1][c2],meanf[c2])-lnbdf(sequences.size()-frequencies[c1][0],(int)(((long double)frequencies[sequences[0].size()][c2])/(long double)sequences[0].size()),meanf[c2]),2);
            partialresult+=pow(lnbdf(sequences.size(),frequencies[c1][c2],meanf[c2])-lnbdf(sequences.size(),(int)(((long double)frequencies[sequences[0].size()][c2])/(long double)sequences[0].size()),meanf[c2]),2);
        }
        dG.push_back(sqrt(partialresult));
    }
}

void Alignment::dGWrite(){
    /*
    string outputfilename;
    vector<string> vecPath = split(this->getFilepath(),'.');

    for(int i = 0; i < vecPath.size()-1; i++){
        outputfilename += vecPath[i];
    }
    outputfilename += "_DG.dat";
    //printf("\n%s\n",outputfilename.c_str());

    QFile f(outputfilename.c_str());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);

    int c1;
    for(c1=0;c1<=sequences[0].size()-1;c1++){
        out << c1+1 << "\t" << (float)dG[c1] << "\n";
    }

    f.close();
    */

    consDG.clear();
    for(int i = 0; i<sequences[0].size()-1;i++){
        consDG.push_back(float(dG[i]));
    }
}

void Alignment::FreqWrite(){
    /*
    int i,j;
    string path = "";
    string freqpath, freqpercpath;
    vector<string> vecPath = split(this->getFilepath(),'.');

    for(i=0;i<vecPath.size()-1;i++){
        path += vecPath[i];
    }

    freqpath = path + "_FREQ.dat";
    freqpercpath = path + "_FREQPERC.dat";

    QFile f1(freqpath.c_str());
    if (!f1.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QFile f2(freqpercpath.c_str());
    if (!f2.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out1(&f1);
    out1.setFieldAlignment(QTextStream::AlignLeft);


    out1 << "pos  GAP   ALA   CYS   ASP   GLU   PHE   GLY   HIS   ILE   LYS   LEU   MET   ASN   PRO   GLN   ARG   SER   THR   VAL   TRP   TYR\n";
    for (i=0;i<=sequences[0].size();i++){
        if(i<sequences[0].size()){
            out1.setFieldWidth(5);
            out1 << i+1;
        }
        else out1 << "ALL  ";
        for (j=0;j<=20;j++){
            out1.setFieldWidth(6);
            out1 << frequencies[i][j];
        }
        out1 << qSetFieldWidth(0) << "\n";
    }

    f1.close();

    QTextStream out2(&f2);
    out2.setRealNumberPrecision(1);
    out2.setFieldAlignment(QTextStream::AlignLeft);
    out2.setRealNumberNotation(QTextStream::FixedNotation);
     out2 << "pos  ALA  CYS  ASP  GLU  PHE  GLY  HIS  ILE  LYS  LEU  MET  ASN  PRO  GLN  ARG  SER  THR  VAL  TRP  TYR\n";
     for (i=0;i<=sequences[0].size();i++){
         if(i<sequences[0].size()){
             out2.setFieldWidth(5);
             out2 << i+1;
             for (j=1;j<=20;j++){
                 if(frequencies[i][j]!=sequences.size()){
                    out2.setFieldWidth(5);
                    out2 << 100.0*(float)frequencies[i][j]/((float)sequences.size());
                 }else out2 << "100. ";
             }
         }else{
             out2 << "ALL ";
             for (j=1;j<=20;j++){
                 if(frequencies[i][j]!=sequences.size()*sequences[0].size()){
                     out2.setFieldWidth(5);
                     out2 << 100.0*(float)frequencies[i][j]/(((float)(sequences.size()*sequences[0].size())));
                 }else out2 << "100. ";
             }
         }
         out2 << qSetFieldWidth(0) << "\n";
     }

    f2.close();
    */
    consfreqPerc.clear();
    consvfreq.clear();
    for (int i=0;i<=sequences[0].size()-1;i++){//-1 para não incluir o ALL
        vector<int> freqs;
        for (int j=0;j<=20;j++){
            freqs.push_back(frequencies[i][j]);
        }
        consvfreq.push_back(freqs);
    }

     for (int i=0;i<=sequences[0].size();i++){
         vector<float> freqpercs;
         for (int j=1;j<=20;j++){
             if(frequencies[i][j]!=sequences.size()){
                freqpercs.push_back(100.0*(float)frequencies[i][j]/((float)sequences.size()));
             }else freqpercs.push_back(100.00);
         }
         consfreqPerc.push_back(freqpercs);
     }
}

void Alignment::CalculateReferenceVector(int seqnumber){
    int c1;
    //QMessageBox::information(NULL,"ok",QString::number(seqnumber));
    referencesequence=seqnumber;
    if(referencevector.size()>0) referencevector.clear();
    for(c1=0;c1<=sequences[0].size()-1;c1++)
        if(isaax(sequences[seqnumber-1][c1])) referencevector.push_back(c1);
}

int Alignment::AlignNumbering2Sequence(int seqnumber, int position){
    this->CalculateReferenceVector(seqnumber);
    for(int c1=0;c1<=referencevector.size()-1;c1++)
        if (referencevector[c1]==position) return(c1+1);
    return 0;
}

void Alignment::NormalizedG(){
    int c1;
    float maxdG=-1;

    if(normalizeddG.size()>0) normalizeddG.clear();

    for(c1=0;c1<=dG.size()-1;c1++)
        if((float)dG[c1]>maxdG) maxdG=dG[c1];

    for(c1=0;c1<=dG.size()-1;c1++) normalizeddG.push_back(100*((float)dG[c1])/maxdG);
}

void Alignment::writedGtoPDB(string PDBfilename, string dgPDBfilename, int initres, char chain, int seqnumber){
    initres++; // THIS IS USED SO THAT THE ROUTINE IS CALLED AS AN OFFSET SUCH AS WITH OUTPUT
    string line, newline;

    CalculateReferenceVector(seqnumber);
    NormalizedG();

    QFile pdbfile(PDBfilename.c_str());
    if (!pdbfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QFile dgpdbfile(dgPDBfilename.c_str());
    if (!dgpdbfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;


    QTextStream out(&dgpdbfile);

    while(!pdbfile.atEnd()){
        line = pdbfile.readLine().toStdString();
        if((line.substr(0,4).compare((string)"ATOM")==0)&&(line.substr(21,1).c_str()[0]==chain)){
            if((getresn(line)<initres)||(getresn(line)>initres+referencevector.size()-1)) newline=outputBfactor(line,0);
            else newline=outputBfactor(line,normalizeddG[referencevector[getresn(line)-initres]]);
        }else newline = line;
        out << newline.c_str();
    }

    pdbfile.close();
    dgpdbfile.close();
}

void Alignment::dGDTCalculation(int numseqs){
    int c1,c2,c3,c4, Ci;
    if (dGDT.size()>0) dGDT.clear();
    long double partialresult;

    for (c1=0;c1<=subsetfrequencies.size()-1;c1++)
        for(c2=0;c2<=subsetfrequencies[0].size()-1;c2++)
            subsetfrequencies[c1][c2]=0;

    for(c3=0;c3<=numseqs-1;c3++){
        for(c4=0;c4<=sequences[0].size()-1;c4++){
            subsetfrequencies[c4][freqmatrixposition(sequences[SortOrder[c3]][c4])]++;
            subsetfrequencies[sequences[0].size()][freqmatrixposition(sequences[SortOrder[c3]][c4])]++;
        }
    }

    for(c1=0;c1<=sequences[0].size()-1;c1++){
        Ci=0;
        partialresult=0;

        for(c2=1; c2<=20; c2++){
            if(subsetfrequencies[c1][c2]>0) Ci++;
            if(subsetfrequencies[c1][c2]>0)
                partialresult += pow(((long double)subsetfrequencies[c1][c2]/((long double)numseqs)) * log(((long double)subsetfrequencies[c1][c2]/((long double)numseqs))/(meanf[c2])),2);
        }
        //printf("numseq: %d - partial: %f\n",numseqs,partialresult);
        if(Ci>0) dGDT.push_back(sqrt(partialresult/((float) Ci)));
        else dGDT.push_back(0);
    }
}

void Alignment::calculateShenkin(int numseqs){
    //long double partialSum = 0;
    for (int i = 0; i < subsetfrequencies.size(); i++)
        for(int j = 0; j < subsetfrequencies[0].size(); j++)
            subsetfrequencies[i][j]=0;

    for(int i = 0; i < numseqs; i++){
        for(int j = 0; j < sequences[0].size(); j++){
            subsetfrequencies[j][freqmatrixposition(sequences[SortOrder[i]][j])]++;
            subsetfrequencies[sequences[0].size()][freqmatrixposition(sequences[SortOrder[i]][j])]++;
        }
    }

}

vector<float> Alignment::DTRandomElimination(int repetitions, int max, int min, int step){
    int c1,c3;
    long double partialresult=0;
    long double partialsum=0;
    //vector<int> SortOrder;
    vector<int> populatedpos;
    vector<float> outputVec;
    int currentsize; // current size of sub-alignment
    int i;

    //progress.setValue(0);
    //QMessageBox::information(NULL,"a",QString::number(min));

    populatedpos.clear();
    for (i=0;i<=sequences[0].size()-1;i++){
        if(((float)frequencies[i][0])/((float)sequences.size())<=1) populatedpos.push_back(i);
    }

    /*
    QFile sucelimfile(outputfilename.c_str());
    if (!sucelimfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return outputVec;
    QTextStream out(&sucelimfile);
    */

    dGDTCalculation(sequences.size());

    for(i=0;i<=populatedpos.size()-1;i++)
        partialresult+=dGDT[populatedpos[i]];

    //out << "100\t" << float(partialresult/((long double)populatedpos.size())) << "\n";
    outputVec.push_back(float(partialresult/((long double)populatedpos.size())));

    for (c1=0;c1<=sequences.size()-1;c1++) SortOrder.push_back(c1);

    QProgressDialog progress("Calculating...", "Abort", 0,100-min);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    for(i=100-max;i<=100-min;i=i+step){
        progress.setValue(i);
         QApplication::processEvents();

        if(progress.wasCanceled()) break;

        partialsum=0;
        currentsize=sequences.size()-((i*sequences.size())/(100));
        if (currentsize<=0) break;

        omp_set_num_threads(1);
        #pragma omp parallel for shared(partialsum)
        for(c1=1;c1<=repetitions;c1++){
            random_shuffle(SortOrder.begin(),SortOrder.end());
            dGDTCalculation(currentsize);
            //#pragma omp parallel for reduction (+:partialsum)
            for (c3=0;c3<=populatedpos.size()-1;c3++){
                partialsum+=dGDT[populatedpos[c3]];
            }
            //printf("%f\n",partialsum);
        }
        //printf("%f - %d\n",(float)partialsum,populatedpos.size());
        //out << 100-i << "\t" << (float)(partialsum/((long double)(populatedpos.size()*repetitions))) << "\n";
        outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()*repetitions))));
    }
    //sucelimfile.close();

    minssData.clear();
    for(int i = 0; i < outputVec.size(); i++){
        this->minssData.push_back(outputVec.at(i));
    }

    return outputVec;

}

vector<float> Alignment::ShenkinEntropy(int repetitions, int gapFilter){
    vector<int> populatedpos;
    vector<float> outputVec;
    vector<vector<int> > subsetTemp;
    double partialsum=0;
    int tamanhoSeq = 0;
    int currentsize = sequences.size();
    for(int i = 0; i < frequencies[0].size(); i++)
        tamanhoSeq += frequencies[0][i];

    //Filtro por GAP
    populatedpos.clear();
    for(int i = 0; i < frequencies.size(); i++){
        //if (frequencies[i][0]/tamanhoSeq <= gapFilter)
            populatedpos.push_back(i);
    }

    //Primeira Iteração
    for(int k = 0; k < populatedpos.size() -1; k++){
        for(int l = 0; l <= 20; l++){
            double subsetfreq = (double)frequencies[k][l]/(double)currentsize;
            if(subsetfreq > 0)
                partialsum += (subsetfreq* log(subsetfreq));
        }
    }
    partialsum = partialsum * -1;
    outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()))));

    //Cria sortOrder
    SortOrder.clear();
    for(int i = 0; i < sequences.size()-1; i++)
        SortOrder.push_back(i);

    //Populaciona subsetlocal
    for(int i = 0; i < subsetfrequencies.size(); i++){
        vector<int> temp;
        for(int j = 0; j < subsetfrequencies[0].size(); j++){
            temp.push_back(0);
        }
        subsetTemp.push_back(temp);
    }

    QProgressDialog progress("Calculating...", "Abort", 0,99);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(int i = 1; i < 100; i++){
        progress.setValue(i);
        QApplication::processEvents();

        if(progress.wasCanceled()) break;

        partialsum = 0;
        currentsize=sequences.size()-((i*sequences.size())/(100));

        if (currentsize<=0) break;



        omp_set_num_threads(8);
        #pragma omp parallel for firstprivate(subsetTemp) reduction (+:partialsum)
        //Teste sem filtro
        for(int j = 0; j < repetitions; j++){
            random_shuffle(SortOrder.begin(),SortOrder.end());

            /*
            //Calcula frequência do subalinhamento
            for (int i1 = 0; i1 < subsetfrequencies.size(); i1++)
                for(int j1 = 0; j1 < subsetfrequencies[0].size(); j1++)
                    subsetfrequencies[i1][j1]=0;

            for(int i1 = 0; i1 < currentsize; i1++){
                for(int j1 = 0; j1 < sequences[0].size(); j1++){
                    subsetfrequencies[j1][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                    subsetfrequencies[sequences[0].size()][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                }
            }*/

            //Calcula frequência do subalinhamento
            for (int i1 = 0; i1 < subsetTemp.size(); i1++)
                for(int j1 = 0; j1 < subsetTemp[0].size(); j1++)
                    subsetTemp[i1][j1]=0;

            for(int i1 = 0; i1 < currentsize; i1++){
                for(int j1 = 0; j1 < sequences[0].size(); j1++){
                    subsetTemp[j1][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                    subsetTemp[sequences[0].size()][freqmatrixposition(sequences[SortOrder[i1]][j1])]++;
                }
            }

            for(int k = 0; k < populatedpos.size() - 1; k++){
                for(int l = 0; l <= 20; l++){
                    double subsetfreq = (double)subsetTemp[k][l]/(double)currentsize;
                    //printf("%d / %d = %f\n",subsetfrequencies[k][l],currentsize,subsetfreq);
                    if(subsetfreq > 0){
                        if(subsetfreq* log(subsetfreq) < 0) partialsum += (subsetfreq* log(subsetfreq) * -1);
                        else partialsum += (subsetfreq* log(subsetfreq));
                        //printf("%f * %f = %f\n",subsetfreq,log(subsetfreq),partialsum);
                    }
                }
            }
            //partialsum = partialsum * -1;
            //printf("TOTAL = %f\n",partialsum);

        }
        outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()*repetitions))));
    }

    minssData.clear();
    for(int i = 0; i < outputVec.size(); i++){
        //printf("%f\n",outputVec[i]);
        this->minssData.push_back(outputVec.at(i));
    }

    return outputVec;
}

void Alignment::SubAlignmentIndices(char aa, int pos){
    int c1;

    if(subalignmentseqs.size()>0) subalignmentseqs.clear();

    for (c1=0;c1<=sequences.size()-1;c1++)
        if(sequences[c1][pos]==aa)
            subalignmentseqs.push_back(c1);
}

int Alignment::SubAlignmentFrequency(char aa, int pos){
    int c1;
    int result = 0;

    if(subalignmentseqs.size()==0) return -1;

    for(c1=0;c1<=subalignmentseqs.size()-1;c1++)
        if(sequences[subalignmentseqs[c1]][pos]==aa) result++;

    return result;
}

int Alignment::Singlepvalue(char aa1, int pos1, char aa2, int pos2){
    int aa2pos2count=0;
    int c2;
    //QMessageBox::information(NULL,"a",QString::number(frequencies.size()));
    if(pos1==pos2) return 0;
    SubAlignmentIndices(aa1,pos1);

    if (subalignmentseqs.size()>0){
        for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
            if (sequences[subalignmentseqs[c2]][pos2]==aa2) aa2pos2count++;

        if ((((float)aa2pos2count)/((float)subalignmentseqs.size()))!=((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size()))){
            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())))
                return(-cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())),true));
            else
                return(cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size())),false));
        }else return 0;
    }else return 0;
}

void Alignment::SympvalueCalculation(int minlogp, float minssfraction, float mindeltafreq){
    int c2,pos1,pos2,aa1,aa2,aa2pos2count,aa1pos1count;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();

    QProgressDialog progress("Calculating...", "Abort", 0,sequences[0].size()-2);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences[0].size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()) break;

        for (aa1=1;aa1<=20;aa1++){
            if(frequencies[pos1][aa1]>minssfraction*((float)sequences.size()))
                for(pos2=pos1+1;pos2<=sequences[0].size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        if(frequencies[pos2][aa2]>minssfraction*((float)sequences.size())){
                            SubAlignmentIndices(num2aa(aa1),pos1);
                            aa2pos2count=0;

                            for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                if (sequences[subalignmentseqs[c2]][pos2]==num2aa(aa2)) aa2pos2count++;

                            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences.size()))){
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++){
                                        if (sequences[subalignmentseqs[c2]][pos1]==num2aa(aa1)) aa1pos1count++;
                                    }

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }else{
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())<(mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                        if (sequences[subalignmentseqs[c2]][pos1]==num2aa(aa1)) aa1pos1count++;

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }
                            if(mindeltafreqok){
                                pvalue1=Singlepvalue(num2aa(aa1),pos1,num2aa(aa2),pos2);
                                pvalue2=Singlepvalue(num2aa(aa2),pos2,num2aa(aa1),pos1);

                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }
}


void Alignment::GetCommunitiesFromFile(string clusterfilename){
    int c1,c2;
    int nclusters;
    int nelements;
    char tempstring[500];
    FILE *clusterfile;
    clusterfile=fopen(clusterfilename.c_str(),"r+");

    resetCommunities();

    fscanf(clusterfile,"%d",&nclusters);
    fgets(tempstring, 255, clusterfile); // endline

    for(c1=1;c1<=nclusters;c1++){
        fscanf(clusterfile,"%d",&nelements);
        fgets(tempstring, 255, clusterfile);

        for(c2=1;c2<=nelements;c2++){
            fgets(tempstring, 255, clusterfile);
            tempcommunity.aa.push_back(tempstring[0]);
            tempcommunity.pos.push_back(atoi(((string)tempstring).substr(1,((string)tempstring).size()).c_str())-1);
        }

        if(nelements > 0){
            Communities.push_back(tempcommunity);
        }

        tempcommunity.aa.clear();
        tempcommunity.pos.clear();
    }

    fclose(clusterfile);
}

void Alignment::getCommunitiesFromRAM(){
    this->resetCommunities();

    for(int i = 0; i < comunidades.size(); i++){
        for(int j = 0; j < comunidades[i].size(); j++){
            string node = comunidades[i][j];

            tempcommunity.aa.push_back(node[0]);

            string tempPos = node.substr(1);

            tempcommunity.pos.push_back(atoi(tempPos.c_str())-1);
        }

        if(comunidades[i].size() > 0)
            Communities.push_back(tempcommunity);

        tempcommunity.aa.clear();
        tempcommunity.pos.clear();
    }

}

void Alignment::DeltaCommunitiesCalculation(){
    float Delta;
    int c1,c2,c3,c4;

    if(Deltas.size()>0){
        for (c1=0;c1<=Deltas.size()-1;c1++)
            Deltas[c1].clear();
        Deltas.clear();
    }

    for(c1=0;c1<=Communities.size()-1;c1++){
        Deltas.push_back( vector<float>(Communities.size()) );
        for (c2=0;c2<=Communities.size()-1;c2++)
            Deltas[c1].push_back(0);
    }

    if(Communities.size()>0){
        for(c1=0;c1<=Communities.size()-1;c1++){
            for(c2=0;c2<=Communities.size()-1;c2++){
                Delta=0;
                for(c3=0;c3<=Communities[c1].aa.size()-1;c3++){
                    for(c4=0;c4<=Communities[c2].aa.size()-1;c4++){
                        Delta+=(float)Singlepvalue(Communities[c1].aa[c3],Communities[c1].pos[c3],Communities[c2].aa[c4],Communities[c2].pos[c4]);
                    }
                }
                Deltas[c1][c2]=((float)Delta)/((float)(Communities[c1].aa.size()*Communities[c2].aa.size()));
            }
        }
    }
}

void Alignment::DeltaCommunitiesOutput(string deltaoutputfilename){
    int c1,c2;

    if(Deltas.size()>0){
        FILE *deltafile;
        deltafile=fopen(deltaoutputfilename.c_str(),"w+");

        fprintf(deltafile,"<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th>Community</th>\n");

        for(c1=0;c1<=Communities.size()-1;c1++)
            fprintf(deltafile,"<th>%d</th>\n",c1+1);

        fprintf(deltafile,"</tr>\n");

        for(c1=0;c1<=Communities.size()-1;c1++){
            fprintf(deltafile,"<tr>\n<td><b>%d</b></td>\n",c1+1);

            for(c2=0;c2<=Communities.size()-1;c2++)
                fprintf(deltafile,"<td>%f</td>\n",Deltas[c1][c2]);

            fprintf(deltafile,"<tr>\n");
        }
        fprintf(deltafile,"</center>\n</table>\n</body>\n</html>\n");
        fclose(deltafile);
    }
}

void Alignment::ElementRanking(string path, bool renumber, int seqnumber, int offset){
    int c1,c2,c3,c4;
    int worseelement;
    float worseelementdeviation;
    vector <float> elementdeviation;
    float sum;
    char outputrankfilename[50];
    FILE *outputrankfile;

    for(c1=0;c1<=Communities.size()-1;c1++){
        sprintf(outputrankfilename,"%srank%d.html",path.c_str(),c1+1);
        tempcommunity.aa.clear();
        tempcommunity.pos.clear();

        if (Communities[c1].aa.size()>2){
            outputrankfile=fopen(outputrankfilename,"w+");
            fprintf(outputrankfile,"<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th><b>Element</b></th><th>Mean score</th>\n");

            for(c2=0;c2<=Communities[c1].aa.size()-1;c2++){
                tempcommunity.aa.push_back(Communities[c1].aa[c2]);
                tempcommunity.pos.push_back(Communities[c1].pos[c2]);
            }

            while (tempcommunity.aa.size()>2){
                elementdeviation.clear();

                for (c2=0;c2<=tempcommunity.aa.size()-1;c2++){
                    sum=0;

                    for(c3=0;c3<=tempcommunity.aa.size()-1;c3++){
                        if(c2!=c3) sum+=Singlepvalue(tempcommunity.aa[c3],tempcommunity.pos[c3],tempcommunity.aa[c2],tempcommunity.pos[c2])+Singlepvalue(tempcommunity.aa[c2],tempcommunity.pos[c2],tempcommunity.aa[c3],tempcommunity.pos[c3]);
                    }

                    elementdeviation.push_back(sum/(float)((tempcommunity.aa.size()-1)*2));
                }
                worseelement=0;
                worseelementdeviation=elementdeviation[0];

                for (c2=1;c2<=elementdeviation.size()-1;c2++){
                    if (elementdeviation[c2]<worseelementdeviation){
                        worseelement=c2;
                        worseelementdeviation=elementdeviation[c2];
                    }
                }

                if(!renumber) fprintf(outputrankfile,"<tr><td><b>%c%d</b></td><td>%f</td></tr>\n",tempcommunity.aa[worseelement],tempcommunity.pos[worseelement]+1,worseelementdeviation);
                else fprintf(outputrankfile,"<tr><td><b>%c%d (%d)</b></td><td>%f</td></tr>\n",tempcommunity.aa[worseelement],AlignNumbering2Sequence(seqnumber,tempcommunity.pos[worseelement])+offset,tempcommunity.pos[worseelement]+1,worseelementdeviation);

                tempcommunity.aa.erase(tempcommunity.aa.begin()+worseelement);
                tempcommunity.pos.erase(tempcommunity.pos.begin()+worseelement);
            }
            worseelementdeviation=((float)(Singlepvalue(tempcommunity.aa[0],tempcommunity.pos[0],tempcommunity.aa[1],tempcommunity.pos[1])+Singlepvalue(tempcommunity.aa[1],tempcommunity.pos[1],tempcommunity.aa[0],tempcommunity.pos[0])))/2.0;

            if(!renumber)
                fprintf(outputrankfile,"<tr><td><b>%c%d ",tempcommunity.aa[0],tempcommunity.pos[0]+1);
            else
                fprintf(outputrankfile,"<tr><td><b>%c%d (%d) ",tempcommunity.aa[0],AlignNumbering2Sequence(seqnumber,tempcommunity.pos[0])+offset,tempcommunity.pos[0]+1);

            if(!renumber)
                fprintf(outputrankfile,"%c%d</b></td><td>%f</td></tr>\n",tempcommunity.aa[1],tempcommunity.pos[1]+1,worseelementdeviation);
            else
                fprintf(outputrankfile,"%c%d (%d)</b></td><td>%f</td></tr>\n",tempcommunity.aa[1],AlignNumbering2Sequence(seqnumber,tempcommunity.pos[1])+offset,tempcommunity.pos[1]+1,worseelementdeviation);

            fprintf(outputrankfile,"</center>\n</table>\n</body>\n</html>\n");

            fclose(outputrankfile);
        }
    }
}

void Alignment::SelfCorrelationMatrixCalculation(const std::vector<char> &aalist, const std::vector<int> &poslist){
    int i, j;

    if(selfcorrelationmatrix.size()!=0){
        for (i=0;i<=selfcorrelationmatrix.size()-1;i++){
            selfcorrelationmatrix[i].clear();
        }
        selfcorrelationmatrix.clear();
    }

    for (i=0;i<=aalist.size()-1;i++){
        selfcorrelationmatrix.push_back( vector<float> (aalist.size())) ;
        //for (j=0;j<=aalist.size()-1;j++) selfcorrelationmatrix[i].push_back(0);
    }

    for (j=0;j<=aalist.size()-1;j++){
        SubAlignmentIndices(aalist[j],poslist[j]);

        for (i=0;i<=aalist.size()-1;i++){
            //printf("%d\n",subalignmentseqs.size());
            if(i==j) selfcorrelationmatrix[i][j]=-1;
            else{
                selfcorrelationmatrix[i][j]=((float)SubAlignmentFrequency(aalist[i],poslist[i]))/((float)subalignmentseqs.size());
                //printf("%f / %d = %f \n",(float)SubAlignmentFrequency(aalist[i],poslist[i]),subalignmentseqs.size(),selfcorrelationmatrix[i][j]);
            }
        }
    }
}

void Alignment::SCM2HTML(string scmfilename, const std::vector<char> &aalist, const std::vector<int> &poslist, bool renumber, int seqnumber, int offset){
    int i,j;
    FILE *scmfile;

    scmfile=fopen(scmfilename.c_str(),"w+");

    fprintf(scmfile,"<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th>POS</th>\n<th>ALL</th>\n");

    for(j=0;j<=aalist.size()-1;j++){
        if (!renumber) fprintf(scmfile,"<th>%c%d</th>\n",aalist[j],poslist[j]+1);
        else if (AlignNumbering2Sequence(seqnumber,poslist[j])!=0) fprintf(scmfile,"<th>%c%d</th>\n",aalist[j],AlignNumbering2Sequence(seqnumber,poslist[j])+offset);
        else fprintf(scmfile,"<th>%cX(%d)</th>\n",aalist[j],poslist[j]+1);
    }

    fprintf(scmfile,"</tr>\n");

    for(i=0;i<=aalist.size()-1;i++){
        if (!renumber) fprintf(scmfile,"<tr>\n<td><b>%c%d</b></td>\n<td>%-5.1f</td>\n",aalist[i],(poslist[i])+1,(float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size()));
        else if (AlignNumbering2Sequence(seqnumber,poslist[i])!=0) fprintf(scmfile,"<tr>\n<td><b>%c%d</b></td>\n<td>%-5.1f</td>\n",aalist[i],AlignNumbering2Sequence(seqnumber,poslist[i])+offset,(float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size()));
        else fprintf(scmfile,"<tr>\n<td><b>%cX(%d)</b></td>\n<td>%-5.1f</td>\n",aalist[i],(poslist[i])+1,(float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size()));

        for (j=0;j<=aalist.size()-1;j++){
            if(i==j) fprintf(scmfile,"<td>X</td>\n");
            else{
                if(fabs((float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size())-100*selfcorrelationmatrix[i][j])<15) fprintf(scmfile,"<td>%-5.1f</td>\n",100*selfcorrelationmatrix[i][j]);
                else{
                    if(fabs((float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size())>100*selfcorrelationmatrix[i][j])) fprintf(scmfile,"<td><font color=#FF0000>%-5.1f</font></td>\n",100*selfcorrelationmatrix[i][j]);
                    else fprintf(scmfile,"<td><font color=#00FF00>%-5.1f</font></td>\n",100*selfcorrelationmatrix[i][j]);
                }
            }
        }
        fprintf(scmfile,"<tr>\n");
    }
    fprintf(scmfile,"</center>\n</table>\n</body>\n</html>\n");
    fclose(scmfile);
}

void Alignment::Write_SCM(string scmfilename, const std::vector<char> &aalist, const std::vector<int> &poslist){
    int i,j;

    FILE *scmfile;
    scmfile=fopen(scmfilename.c_str(),"w+");

    fprintf(scmfile,"POS\tALL");

    for(j=0;j<=aalist.size()-1;j++){
        fprintf(scmfile,"\t%c%d",aalist[j],poslist[j]+1);
    }
    fprintf(scmfile,"\n");
    for(i=0;i<=aalist.size()-1;i++){
        fprintf(scmfile,"%c%d\t%-5.1f",aalist[i],(poslist[i])+1,(float)100*frequencies[poslist[i]][freqmatrixposition(aalist[i])]/((float)sequences.size()));

        for (j=0;j<=aalist.size()-1;j++){
            if(i==j) fprintf(scmfile,"\tX");
            else fprintf(scmfile,"\t%-5.1f",100*selfcorrelationmatrix[i][j]);
        }
        fprintf(scmfile,"\n");
    }
    fclose(scmfile);
}

void Alignment::pMatrix2HTML(string path, bool renumber, int seqnumber){
    char pmfilename[50];
    int i,j,c1;
    FILE *pmfile;

    for(c1=0;c1<=Communities.size()-1;c1++){
        if(Communities[c1].aa.size()>1){
            sprintf(pmfilename,"%scommunity%dps.html",path.c_str(),c1+1);
            pmfile=fopen(pmfilename,"w+");
            fprintf(pmfile,"<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th>POS</th>\n");

            for(j=0;j<=Communities[c1].aa.size()-1;j++){
                if (!renumber) fprintf(pmfile,"<th>%c%d</th>\n",Communities[c1].aa[j],Communities[c1].pos[j]+1);
                else if (AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j])!=0) fprintf(pmfile,"<th>%c%d</th>\n",Communities[c1].aa[j],AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j]));
                else fprintf(pmfile,"<th>%cX(%d)</th>\n",Communities[c1].aa[j],Communities[c1].pos[j]+1);
            }
            fprintf(pmfile,"</tr>\n");

            for(i=0;i<=Communities[c1].aa.size()-1;i++){
                if (!renumber) fprintf(pmfile,"<tr>\n<td><b>%c%d</b></td>\n",Communities[c1].aa[i],(Communities[c1].pos[i])+1);
                else if (AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j])!=0) fprintf(pmfile,"<tr>\n<td><b>%c%d</b></td>\n",Communities[c1].aa[i],AlignNumbering2Sequence(seqnumber,Communities[c1].pos[i]));
                else fprintf(pmfile,"<tr>\n<td><b>%cX(%d)</b></td>\n",Communities[c1].aa[i],(Communities[c1].pos[i])+1);

                for (j=0;j<=Communities[c1].aa.size()-1;j++){
                    if(i==j) fprintf(pmfile,"<td>X</td>\n");
                    else
                        printf("%c%d e %c%d\n",Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]);
                        fprintf(pmfile,"<td>%d</td>\n",Singlepvalue(Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]));
                }
                fprintf(pmfile,"<tr>\n");
            }
            fprintf(pmfile,"</center>\n</table>\n</body>\n</html>\n");
            fclose(pmfile);
        }
    }
}

void Alignment::pMatrix2HTMLRAM(bool renumber, int seqnumber){
    this->communityXps.clear();
    this->residuesCommPs.clear();

    for(int c1 = 0; c1 < Communities.size(); c1++){
        if(Communities[c1].aa.size() > 1){

            vector<vector<int> > matrix = this->createBlankIntMatrix(Communities[c1].aa.size(),Communities[c1].aa.size(),-1);
            vector<string> clustersResidues;
            for(int j = 0; j < Communities[c1].aa.size(); j++){
                string residue;
                if(!renumber) residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                else if(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j]) != 0) residue = Communities[c1].aa[j] + QString::number(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j])).toStdString();
                else residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                clustersResidues.push_back(residue);
            }
            residuesCommPs.push_back(clustersResidues);

            for(int i = 0; i < Communities[c1].aa.size(); i++){
                for(int j = 0; j < Communities[c1].aa.size(); j++){
                    if(i != j){
                        matrix[i][j] = Singlepvalue(Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]);
                        //printf("%c%d e %c%d\n",Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]);
                        //printf("i=%d, j=%d, value=%d\n",i,j,matrix[i][j]);
                    }
                }
            }

            this->communityXps.push_back(matrix);
        }
    }
/*
    for(int i = 0; i < communityXps.size(); i++){
        printf("Comunidade %d:\n",i);
        for(int j = 0; j < communityXps[i].size(); j++){
            for(int k = 0; k < communityXps[i][j].size(); k++){
                printf("%d ", communityXps[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
*/
}

float Alignment::PSA(int seqnumber, int communitynumber){
    int i,j;
    float sum=0;

    //QMessageBox::information(NULL,"a",QString::number(sequences.size()));

    if(Communities[communitynumber].aa.size()>1)
        for (i=0;i<=Communities[communitynumber].aa.size()-1;i++){
            for(j=0;j<=Communities[communitynumber].aa.size()-1;j++){
                if(((Communities[communitynumber].aa[i]==sequences[seqnumber][Communities[communitynumber].pos[i]])&&(Communities[communitynumber].aa[j]==sequences[seqnumber][Communities[communitynumber].pos[j]]))&&(Communities[communitynumber].pos[i]!=Communities[communitynumber].pos[j])){
                    //QMessageBox::information(NULL,"a","OK");
                    sum+=Singlepvalue(Communities[communitynumber].aa[i],Communities[communitynumber].pos[i],Communities[communitynumber].aa[j],Communities[communitynumber].pos[j]);
                    //QMessageBox::information(NULL,"a","OK");
                }
            }
        }
    //QMessageBox::information(NULL,"a","FIM PSA");
    return(sum/(float)(Communities[communitynumber].aa.size()*(Communities[communitynumber].aa.size()-1)));
}

void Alignment::Cluster2SCM(string clusterfilename, string path, bool renumber, int seqnumber, int offset, bool html, bool text){
    int c1,c2;
    int nclusters;
    int nelements;
    char tempstring[500];
    char filename[50];
    vector<char> aalist;
    vector<int> poslist;
    FILE *clusterfile;

    clusterfile=fopen(clusterfilename.c_str(),"r+");
    fscanf(clusterfile,"%d",&nclusters);
    fgets(tempstring, 255, clusterfile); // endline

    for(c1=1;c1<=nclusters;c1++){
        aalist.clear();
        poslist.clear();
        fscanf(clusterfile,"%d",&nelements);
        fgets(tempstring, 255, clusterfile);

        for(c2=1;c2<=nelements;c2++){
            fgets(tempstring, 255, clusterfile);
            aalist.push_back(tempstring[0]);
            poslist.push_back(atoi(((string)tempstring).substr(1,((string)tempstring).size()).c_str())-1);
        }

        if(nelements>1){
            sprintf(filename,"%scommunity%d.html",path.c_str(),c1);
            SelfCorrelationMatrixCalculation(aalist, poslist);
            if (html) SCM2HTML((string)filename,aalist,poslist,renumber,seqnumber,offset);

            if (text){
                sprintf(filename,"%s_community%d.txt",path.c_str(),c1);
                Write_SCM((string)filename,aalist,poslist);
            }
        }
    }
    fclose(clusterfile);
}

void Alignment::Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset){
    int nclusters = comunidades.size();
    //nclusters = 1;
    vector<char> aalist;
    vector<int> poslist;
    this->communityX.clear();
    this->communityXAll.clear();
    this->residuesComm.clear();


    for(int i = 0; i < nclusters; i++){
        aalist.clear();
        poslist.clear();
        vector<float> clusterXAll;

        for(int j = 0; j < comunidades[i].size(); j++){
            string temp = comunidades[i][j];
            aalist.push_back(temp[0]);
            poslist.push_back(atoi(temp.substr(1).c_str())-1);
        }
/*
        for(int j = 0; j < aalist.size(); j++){
            printf("%c%d\n",aalist[j],poslist[j]);
        }
*/
        if(comunidades[i].size() > 1){
            SelfCorrelationMatrixCalculation(aalist,poslist);

            //ESCRITA SCM2HTML*RAM
            vector<string> clustersResidues;
            for(int j = 0; j < aalist.size(); j++){
                string residue;
                if(!renumber){
                    residue = aalist[j] + QString::number(poslist[j]+1).toStdString();
                }else if (AlignNumbering2Sequence(seqnumber,poslist[j])!=0){
                    residue = aalist[j] + QString::number(AlignNumbering2Sequence(seqnumber,poslist[j])+offset).toStdString();
                }else{
                    //residue = string(aalist[j]).c_str() + "X(";// + QString::number(poslist[j] + 1).toStdString() + ")";
                    char test[50];
                    sprintf(test,"%cX(%d)",aalist[j],poslist[j] + 1);
                    residue = test;
                }
                clustersResidues.push_back(residue);
            }
            residuesComm.push_back(clustersResidues);

            for(int j = 0; j < aalist.size(); j++){
                clusterXAll.push_back((float)100*frequencies[poslist[j]][freqmatrixposition(aalist[j])]/((float)sequences.size()));
            }

/*
            //printf("SCM SIZE = %d\n",selfcorrelationmatrix.size());
            for(int j = 0; j < residuesComm.size(); j++){
                //printf("i = %d, SIZE = %d\n", j, aalist.size());
                for(int k = 0; k < residuesComm[j].size(); k++){
                    printf(" %s ",residuesComm[j][k].c_str());
                }
                printf("\n");
            }
*/
            this->communityX.push_back(selfcorrelationmatrix);
            this->communityXAll.push_back(clusterXAll);
        }
    }

}

void Alignment::Cluster2PymolScript(string clusterfilename, string path, int seqnumber, int offset){
    int c1,c2;
    int nclusters;
    int nelements;
    char tempstring[500];
    char filename[50];
    vector<char> aalist;
    vector<int> poslist;
    FILE *clusterfile;
    FILE *pymolscriptfile;

    clusterfile=fopen(clusterfilename.c_str(),"r+");

    fscanf(clusterfile,"%d",&nclusters);
    fgets(tempstring, 255, clusterfile); // endline
    sprintf(filename,"%ssets.py",path.c_str());

    pymolscriptfile=fopen(filename,"w+");

    for(c1=1;c1<=nclusters;c1++){
        aalist.clear();
        poslist.clear();

        fscanf(clusterfile,"%d",&nelements);
        fgets(tempstring, 255, clusterfile);
        fprintf(pymolscriptfile,"create set%d,(",c1);

        for(c2=1;c2<=nelements;c2++){
            fgets(tempstring, 255, clusterfile);

            aalist.push_back(tempstring[0]);
            poslist.push_back(atoi(((string)tempstring).substr(1,((string)tempstring).size()).c_str())-1);
        }

        for(c2=1;c2<=nelements-1;c2++)
            fprintf(pymolscriptfile,"(resi %d)or",AlignNumbering2Sequence(seqnumber,poslist[c2-1])+offset);
        fprintf(pymolscriptfile,"(resi %d))\n\n",AlignNumbering2Sequence(seqnumber,poslist[poslist.size()-1])+offset);
    }
    fclose(clusterfile);
    fclose(pymolscriptfile);
}

void Alignment::exportAlignment(QString filename, string filter, int type){
    int ai = -2;
    for(int i = 0; i < this->filtersList.size(); i++){
        if(filtersList[i][0] == filter){
            ai = i;
            break;
        }
    }
    if(filter == "Full Alignment") ai = -1;
    else if(ai == -2){
        QMessageBox::critical(NULL,"Error","Alignment not found.");
        return;
    }

    switch(type){
        case 0://PFAM
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "pfam" && tempFN[tempFN.size()-1] != "PFAM")
                filename += ".pfam";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            if(ai >= 0){
                for(int i = 1; i < filtersList[ai].size(); i++){
                    out << filtersList[ai][i].c_str() << " " << filterSequences[ai][i].c_str() << "\n";
                }
            }else if(ai == -1){
                for(int i = 0; i < fullAlignment.size(); i++){
                    out << fullAlignment[i].c_str() << " " << fullSequences[i].c_str() << "\n";
                }
            }

            f.close();
            break;
        }
        case 1://TXT
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            if(ai >= 0){
                for(int i = 1; i < filtersList[ai].size(); i++){
                    out << filtersList[ai][i].c_str() << " " << filterSequences[ai][i].c_str() << "\n";
                }
            }else if(ai == -1){
                for(int i = 0; i < fullAlignment.size(); i++){
                    out << fullAlignment[i].c_str() << " " << fullSequences[i].c_str() << "\n";
                }
            }

            f.close();
            break;
        }
        case 2://XML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            out << "<?xml version=\"1.0\"?>\n\n";
            out << "<PFStats>\n";
            out << "   <filters>\n";

            if(ai >= 0){
                vector<string> parsVec = this->split(filter,' ');
                string occ = parsVec[0];
                string minid = parsVec[1];
                string maxid = parsVec[2];
                string refseq = parsVec[3];

                out << "      <filter occ='" << occ.c_str() << "' minid='" << minid.c_str() << "' maxid='" << maxid.c_str() << "' refseq='" << refseq.c_str() << "' >\n";
                for(int i = 1; i < filtersList[ai].size(); i++){
                    vector<string> vecSplit = this->split(filtersList[ai][i],'/');
                    out << "         <entry id='" << i-1 << "' offset='" << vecSplit[1].c_str() << "' name='" << vecSplit[0].c_str() << "'>" << filterSequences[ai][i].c_str() << "</entry>\n";
                }
            }else if(ai == -1){
                out << "      <filter occ='0' minid='0' maxid='0' refseq='0' >\n";

                for(int i = 0; i < fullAlignment.size(); i++){
                    vector<string> vecSplit = this->split(fullAlignment[i],'/');
                    out << "         <entry id='" << i << "' offset='" << vecSplit[1].c_str() << "' name='" << vecSplit[0].c_str() << "'>" << fullSequences[i].c_str() << "</entry>\n";
                }
            }

            out << "      </filter>\n";
            out << "   </filters>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this alignment.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Alignment","Alignment saved succesfully.");
}

void Alignment::exportFreq(QString filename, int type, bool perc){
    vector<string> consPars = this->getConservationParameters();
    if(consPars.size() == 0){
        QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
        return;
    }

    string filter = consPars[1].c_str();
    string refseq = consPars[2].c_str();
    string offset = consPars[3].c_str();
    string chain = consPars[4].c_str();

    switch(type){
        case 0://TXT
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "#FILTER(3) REFSEQ OFFSET CHAIN\n";
            out << "#" << filter.c_str() << " " << offset.c_str() << " " << chain.c_str() << "\n";

            if(perc){
                out.setRealNumberPrecision(1);
                out.setFieldAlignment(QTextStream::AlignLeft);
                out.setRealNumberNotation(QTextStream::FixedNotation);
                out << "pos  ALA  CYS  ASP  GLU  PHE  GLY  HIS  ILE  LYS  LEU  MET  ASN  PRO  GLN  ARG  SER  THR  VAL  TRP  TYR\n";
                for(int i = 0; i < consfreqPerc.size()-1; i++){
                    out.setFieldWidth(5);
                    out << i+1;
                    for(int j = 0; j < consfreqPerc[i].size(); j++){
                        out.setFieldWidth(5);
                        out << consfreqPerc[i][j];
                    }
                    out << qSetFieldWidth(0) << "\n";
                }
            }else{
                out << "pos  ALA   CYS   ASP   GLU   PHE   GLY   HIS   ILE   LYS   LEU   MET   ASN   PRO   GLN   ARG   SER   THR   VAL   TRP   TYR\n";
                for(int i = 0; i < consvfreq.size(); i++){
                    if(i >= 0 && i <= 8)
                        out << i+1 << "    ";
                    else if(i >=9 && i <= 98)
                        out << i+1 << "   ";
                    else if(i > 99)
                        out << i+1 << "  ";
                    for(int j = 0; j < consvfreq[i].size(); j++){
                        if(consvfreq[i][j] >= 0 && consvfreq[i][j] <= 9)
                            out << consvfreq[i][j] << "     ";
                        else if(consvfreq[i][j] >= 10 && consvfreq[i][j] <= 99)
                            out << consvfreq[i][j] << "    ";
                        else if(consvfreq[i][j] > 99)
                            out << consvfreq[i][j] << "   ";
                    }
                    out << "\n";
                }
            }

            f.close();
            break;
        }
        case 1://CSV
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            if(perc){
                for(int i = 0; i < consfreqPerc.size(); i++){
                    out << i+1 << ",";
                    for(int j = 0; j < consfreqPerc[i].size()-1; j++)
                        out << consfreqPerc[i][j] << ",";
                    out << consfreqPerc[i][consfreqPerc[i].size()-1] << "\n";
                }
            }else{
                for(int i = 0; i < consvfreq.size(); i++){
                    out << i+1 << ",";
                    for(int j = 0; j < consvfreq[i].size()-1; j++)
                        out << consvfreq[i][j] << ",";
                    out << consvfreq[i][consvfreq[i].size()-1] << "\n";
                }
            }

            f.close();
            break;
        }
        case 2://XML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n\n";
            out << "<PFStats>\n";
            out << "   <conservation>\n";

            out << "      <parameters>\n";

            out << "         <filter>" << filter.c_str() << "</filter>\n";
            out << "         <refseq>" << refseq.c_str() << "</refseq>\n";
            out << "         <offset>" << offset.c_str() << "</offset>\n";
            out << "         <chain>" << chain.c_str() << "</chain>\n";

            out << "      </parameters>\n";

            out << "   <positions>\n";

            if(perc){
                for(int i = 0; i < consfreqPerc.size(); i++){
                    out << "      <pos id='" << i+1 << "'>\n";
                    out << "         <ALA>\n";
                    out << "            <percent>" << consfreqPerc[i][0] << "</percent>\n";
                    out << "         </ALA>\n";
                    out << "         <CYS>\n";
                    out << "            <percent>" << consfreqPerc[i][1] << "</percent>\n";
                    out << "         </CYS>\n";
                    out << "         <ASP>\n";
                    out << "            <percent>" << consfreqPerc[i][2] << "</percent>\n";
                    out << "         </ASP>\n";
                    out << "         <GLU>\n";
                    out << "            <percent>" << consfreqPerc[i][3] << "</percent>\n";
                    out << "         </GLU>\n";
                    out << "         <PHE>\n";
                    out << "            <percent>" << consfreqPerc[i][4] << "</percent>\n";
                    out << "         </PHE>\n";
                    out << "         <GLY>\n";
                    out << "            <percent>" << consfreqPerc[i][5] << "</percent>\n";
                    out << "         </GLY>\n";
                    out << "         <HIS>\n";
                    out << "            <percent>" << consfreqPerc[i][6] << "</percent>\n";
                    out << "         </HIS>\n";
                    out << "         <ILE>\n";
                    out << "            <percent>" << consfreqPerc[i][7] << "</percent>\n";
                    out << "         </ILE>\n";
                    out << "         <LYS>\n";
                    out << "            <percent>" << consfreqPerc[i][8] << "</percent>\n";
                    out << "         </LYS>\n";
                    out << "         <LEU>\n";
                    out << "            <percent>" << consfreqPerc[i][9] << "</percent>\n";
                    out << "         </LEU>\n";
                    out << "         <MET>\n";
                    out << "            <percent>" << consfreqPerc[i][10] << "</percent>\n";
                    out << "         </MET>\n";
                    out << "         <ASN>\n";
                    out << "            <percent>" << consfreqPerc[i][11] << "</percent>\n";
                    out << "         </ASN>\n";
                    out << "         <PRO>\n";
                    out << "            <percent>" << consfreqPerc[i][12] << "</percent>\n";
                    out << "         </PRO>\n";
                    out << "         <GLN>\n";
                    out << "            <percent>" << consfreqPerc[i][13] << "</percent>\n";
                    out << "         </GLN>\n";
                    out << "         <ARG>\n";
                    out << "            <percent>" << consfreqPerc[i][14] << "</percent>\n";
                    out << "         </ARG>\n";
                    out << "         <SER>\n";
                    out << "            <percent>" << consfreqPerc[i][15] << "</percent>\n";
                    out << "         </SER>\n";
                    out << "         <THR>\n";
                    out << "            <percent>" << consfreqPerc[i][16] << "</percent>\n";
                    out << "         </THR>\n";
                    out << "         <VAL>\n";
                    out << "            <percent>" << consfreqPerc[i][17] << "</percent>\n";
                    out << "         </VAL>\n";
                    out << "         <TRP>\n";
                    out << "            <percent>" << consfreqPerc[i][18] << "</percent>\n";
                    out << "         </TRP>\n";
                    out << "         <TYR>\n";
                    out << "            <percent>" << consfreqPerc[i][19] << "</percent>\n";
                    out << "         </TYR>\n";
                    out << "      </pos>\n";
                }
            }else{
                for(int i = 0; i < consvfreq.size(); i++){
                    out << "      <pos id='" << i+1 << "'>\n";
                    out << "         <GAP>\n";
                    out << "            <frequence>" << consvfreq[i][0] << "</frequence>\n";
                    out << "         </GAP>\n";
                    out << "         <ALA>\n";
                    out << "            <frequence>" << consvfreq[i][1] << "</frequence>\n";
                    out << "         </ALA>\n";
                    out << "         <CYS>\n";
                    out << "            <frequence>" << consvfreq[i][2] << "</frequence>\n";
                    out << "         </CYS>\n";
                    out << "         <ASP>\n";
                    out << "            <frequence>" << consvfreq[i][3] << "</frequence>\n";
                    out << "         </ASP>\n";
                    out << "         <GLU>\n";
                    out << "            <frequence>" << consvfreq[i][4] << "</frequence>\n";
                    out << "         </GLU>\n";
                    out << "         <PHE>\n";
                    out << "            <frequence>" << consvfreq[i][5] << "</frequence>\n";
                    out << "         </PHE>\n";
                    out << "         <GLY>\n";
                    out << "            <frequence>" << consvfreq[i][6] << "</frequence>\n";
                    out << "         </GLY>\n";
                    out << "         <HIS>\n";
                    out << "            <frequence>" << consvfreq[i][7] << "</frequence>\n";
                    out << "         </HIS>\n";
                    out << "         <ILE>\n";
                    out << "            <frequence>" << consvfreq[i][8] << "</frequence>\n";
                    out << "         </ILE>\n";
                    out << "         <LYS>\n";
                    out << "            <frequence>" << consvfreq[i][9] << "</frequence>\n";
                    out << "         </LYS>\n";
                    out << "         <LEU>\n";
                    out << "            <frequence>" << consvfreq[i][10] << "</frequence>\n";
                    out << "         </LEU>\n";
                    out << "         <MET>\n";
                    out << "            <frequence>" << consvfreq[i][11] << "</frequence>\n";
                    out << "         </MET>\n";
                    out << "         <ASN>\n";
                    out << "            <frequence>" << consvfreq[i][12] << "</frequence>\n";
                    out << "         </ASN>\n";
                    out << "         <PRO>\n";
                    out << "            <frequence>" << consvfreq[i][13] << "</frequence>\n";
                    out << "         </PRO>\n";
                    out << "         <GLN>\n";
                    out << "            <frequence>" << consvfreq[i][14] << "</frequence>\n";
                    out << "         </GLN>\n";
                    out << "         <ARG>\n";
                    out << "            <frequence>" << consvfreq[i][15] << "</frequence>\n";
                    out << "         </ARG>\n";
                    out << "         <SER>\n";
                    out << "            <frequence>" << consvfreq[i][16] << "</frequence>\n";
                    out << "         </SER>\n";
                    out << "         <THR>\n";
                    out << "            <frequence>" << consvfreq[i][17] << "</frequence>\n";
                    out << "         </THR>\n";
                    out << "         <VAL>\n";
                    out << "            <frequence>" << consvfreq[i][18] << "</frequence>\n";
                    out << "         </VAL>\n";
                    out << "         <TRP>\n";
                    out << "            <frequence>" << consvfreq[i][19] << "</frequence>\n";
                    out << "         </TRP>\n";
                    out << "         <TYR>\n";
                    out << "            <frequence>" << consvfreq[i][20] << "</frequence>\n";
                    out << "         </TYR>\n";
                    out << "      </pos>\n";
                }
            }

            out << "   </positions>\n";
            out << "   </conservation>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        case 3://HTML
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<!DOCTYPE html>\n";
            out << "<html>\n";
            out << "<body>\n";
            out << "<table border='1'>\n";
            out << "\t<tr>\n";
            out << "\t\t" << filter.c_str() << "\n";
            out << "\t</tr>\n";
            out << "\t<tr>\n";
            out << "\t\tOffset: " << offset.c_str() <<"\n";
            out << "\t\tChain: " << chain.c_str() << "\n";
            out << "\t</tr>\n";
            out << "\t<tr>\n";
            out << "\t\t<td><b>POS</b></td>\n";
            if(!perc) out << "\t\t<td><b>GAP</b></td>\n";
            out << "\t\t<td><b>ALA</b></td>\n";
            out << "\t\t<td><b>CYS</b></td>\n";
            out << "\t\t<td><b>ASP</b></td>\n";
            out << "\t\t<td><b>GLU</b></td>\n";
            out << "\t\t<td><b>PHE</b></td>\n";
            out << "\t\t<td><b>GLY</b></td>\n";
            out << "\t\t<td><b>HIS</b></td>\n";
            out << "\t\t<td><b>ILE</b></td>\n";
            out << "\t\t<td><b>LYS</b></td>\n";
            out << "\t\t<td><b>LEU</b></td>\n";
            out << "\t\t<td><b>MET</b></td>\n";
            out << "\t\t<td><b>ASN</b></td>\n";
            out << "\t\t<td><b>PRO</b></td>\n";
            out << "\t\t<td><b>GLN</b></td>\n";
            out << "\t\t<td><b>ARG</b></td>\n";
            out << "\t\t<td><b>SER</b></td>\n";
            out << "\t\t<td><b>THR</b></td>\n";
            out << "\t\t<td><b>VAL</b></td>\n";
            out << "\t\t<td><b>TRP</b></td>\n";
            out << "\t\t<td><b>TYR</b></td>\n";
            out << "\t</tr>\n";

            if(perc){
                for(int i = 0; i < consfreqPerc.size(); i++){
                    out << "\t<tr>\n";
                    out << "\t\t<td>" << i+1 << "</td>\n";
                    for(int j = 0; j < consfreqPerc[i].size(); j++){
                        out << "\t\t<td>" << consfreqPerc[i][j] << "</td>\n";
                    }
                    out << "</tr>\n";
                }
            }else{
                for(int i = 0; i < consvfreq.size(); i++){
                    out << "\t<tr>\n";
                    out << "\t\t<td>" << i+1 << "</td>\n";
                    for(int j = 0; j < consvfreq[i].size(); j++){
                        out << "\t\t<td>" << consvfreq[i][j] << "</td>\n";
                    }
                    out << "</tr>\n";
                }
            }

            out << "</table>\n";
            out << "</body>\n";
            out << "</html>\n";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Conservation data was exported.");
}

void Alignment::exportConsRes(QString filename, int type, float mincons, vector<int> refSeqs){
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;

    this->CalculateFrequencies();

    for(int i = 0; i < frequencies.size()-2; i++){
        for(int j = 1; j <= 20; j++){
            float freq = frequencies[i][j]/((float)sequences.size());
            //printf("freq=%f / minCons=%f\n",freq,minCons);
            if(freq >= mincons){
                conservedaa.push_back(num2aa(j));
                conservedpos.push_back(i);
                conservedfreq.push_back(100.0*freq);
            }
        }
    }


    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "Sequence ";
            for(int i = 0; i < conservedaa.size(); i++)
                out <<  conservedaa[i] << conservedpos[i]+1 << " (" << QString::number(conservedfreq[i],'f',1) << ") ";
            out << "\n";

            for(int i = 0; i < refSeqs.size(); i++){
                out << sequencenames[refSeqs[i]].c_str() << " ";
                for(int j = 0; j < conservedaa.size(); j++){
                    if(AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) == 0) out << "- ";
                    else{
                        if(sequences[refSeqs[i]][conservedpos[j]]==conservedaa[j])
                            out << conservedaa[j] << AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) + GetOffsetFromSeqName(sequencenames[refSeqs[i]]) << " ";
                        else
                            out << sequences[refSeqs[i]][conservedpos[j]] << AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) + GetOffsetFromSeqName(sequencenames[refSeqs[i]]) << " ";
                    }
                }
                out << "\n";
            }
            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<conservedResidues>\n";

            for(int i = 0; i < conservedaa.size(); i++){
                out << "\t\t<residue alignN=\"" << conservedaa[i] << conservedpos[i]+1 << "\" freq=\"" << QString::number(conservedfreq[i],'f',1) << "\">\n";

                for(int j = 0; j < refSeqs.size(); j++){
                    out << "\t\t\t<entry protein=\"" << sequencenames[refSeqs[j]].c_str() << "\" ";
                    if(AlignNumbering2Sequence(refSeqs[j]+1,conservedpos[i]) == 0)
                        out << "seqN=\"-\" conserv=\"false\"/>\n";
                    else{
                        if(sequences[refSeqs[j]][conservedpos[i]]==conservedaa[i]){
                            out << "seqN=\"" << conservedaa[i] << AlignNumbering2Sequence(refSeqs[j]+1,conservedpos[i]) + GetOffsetFromSeqName(sequencenames[refSeqs[j]]);
                            out << "\" conserv=\"true\"/>\n";
                        }else{
                            out << "seqN=\"" << sequences[refSeqs[j]][conservedpos[i]] << AlignNumbering2Sequence(refSeqs[j]+1,conservedpos[i]) + GetOffsetFromSeqName(sequencenames[refSeqs[j]]);
                            out << "\" conserv=\"false\"/>\n";
                        }
                    }
                }

                out << "\t\t</residue>\n";
            }

            out << "\t</conservedResidues>\n";
            out << "</PFStats>\n";
            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);
            out.setFieldAlignment(QTextStream::AlignLeft);
            out.setRealNumberNotation(QTextStream::FixedNotation);
            out.setRealNumberPrecision(1);

            out << "<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th><b>Sequence</b></th>";

            for (int c1=0;c1<=conservedaa.size()-1;c1++){
                out << "<th><b>" << conservedaa[c1] << conservedpos[c1]+1 << " (" << conservedfreq[c1] <<")</b></th>";
            }
            out << "</tr>\n";
            for (int c1=0;c1<=refSeqs.size()-1;c1++){
                out << "<tr><th><b>" << sequencenames[refSeqs[c1]].c_str();
                for (int c2=0;c2<=conservedaa.size()-1;c2++){
                    if(AlignNumbering2Sequence(refSeqs[c1]+1,conservedpos[c2]) ==0){
                        out << "<th><font color=#FF0000>-</font></th>";
                    }else{
                        if (sequences[refSeqs[c1]][conservedpos[c2]]==conservedaa[c2])
                            out << "<th>" << conservedaa[c2] << AlignNumbering2Sequence(refSeqs[c1]+1,conservedpos[c2]) + GetOffsetFromSeqName(sequencenames[refSeqs[c1]]) << "</th>";
                        else
                            out << "<th><font color=#FF0000>" << sequences[refSeqs[c1]][conservedpos[c2]] << AlignNumbering2Sequence(refSeqs[c1]+1,conservedpos[c2])+GetOffsetFromSeqName(sequencenames[refSeqs[c1]]) << "</font></th>";
                    }
                }
                out << "</tr>\n";
            }
            f.close();

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Conserved residues data was exported.");
}

void Alignment::exportRefs(QString filename, int type){
    switch(type){
    case 0:
    {
        vector<string> tempFN = split(filename.toStdString(),'.');
        if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
            filename += ".txt";

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }

        QTextStream out(&f);

        for(int i = 0; i < refSeqs.size(); i++){
            out << refSeqs[i].c_str() << "\n";
        }

        f.close();
        break;
    }
    case 1:
    {
        vector<string> tempFN = split(filename.toStdString(),'.');
        if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
            filename += ".xml";

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }

        QTextStream out(&f);

        out << "<?xml version=\"1.0\"?>\n";
        out << "<PFStats>\n";
        out << "<references>\n";

        for(int i = 0; i < refSeqs.size(); i++){
            out << "<sequence>" << refSeqs[i].c_str() << "</sequence>\n";
        }

        out << "</references>\n";
        out << "</PFStats>\n";

        f.close();
        break;
        break;
    }
    default:
    {
        QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
        return;
    }
    }
    QMessageBox::information(NULL,"Exporting Data","References sequences was exported.");
}

void Alignment::exportCorrGraph(QString filename, int type){
    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            vector<string> corrPars = this->getCorrelationParameters();

            if(corrPars.size() == 0){
                QMessageBox::warning(NULL,"Warning","Some data might corrupted. Try run correlation again");
                return;
            }

            out << "#FILTER: " << corrPars[1].c_str() << "\n";
            out << "#MIN SCORE: " << corrPars[2].c_str() << "\n";
            out << "#MINSS FRACTION: " << corrPars[3].c_str() << "\n";
            out << "#DELTA FREQ: " << corrPars[4].c_str() << "\n";

            for(int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << std::get<0>(tupCorr).c_str() << " " << std::get<1>(tupCorr).c_str() << " " << std::get<2>(tupCorr) << "\n";
            }

            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            for(int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << std::get<0>(tupCorr).c_str() << "," << std::get<1>(tupCorr).c_str() << "," << std::get<2>(tupCorr) << "\n";
            }
            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            vector<string> corrPars = this->getCorrelationParameters();

            if(corrPars.size() == 0){
                QMessageBox::warning(NULL,"Warning","Some data might corrupted. Try run correlation again");
                return;
            }

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<correlation>\n";
            out << "\t\t<parameters>\n";

            out << "\t\t\t<filter>" << corrPars[1].c_str() << "</filter>\n";
            out << "\t\t\t<minScore>" << corrPars[2].c_str() << "</minScore>\n";
            out << "\t\t\t<minss>" << corrPars[3].c_str() << "</minss>\n";
            out << "\t\t\t<delta>" << corrPars[4].c_str() << "</delta>\n";

            out << "\t\t</parameters>\n";

            out << "\t\t<graph>\n";

            for(int i = 0; i < this->corrGraph.size(); i++){
                tuple<string,string,int> tupCorr = corrGraph[i];

                out << "\t\t\t<entry res1=\"" << std::get<0>(tupCorr).c_str() << "\" res2=\"" << std::get<1>(tupCorr).c_str() << "\" value=\"" << std::get<2>(tupCorr) << "\" />\n";
            }

            out << "\t\t</graph>\n";
            out << "\t</correlation>\n";
            out << "</PFStats>\n";
            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Correlation list data was exported.");
}

void Alignment::exportCommList(QString filename, int type){

    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << comunidades.size() << " communities\n";

            for(int i = 0; i < comunidades.size(); i++){
                out << comunidades[i].size() << " nodes in community " << i+1 << "\n";
                for(int j = 0; j < comunidades[i].size(); j++){
                    out << comunidades[i][j].c_str() << "\n";
                }
            }
            f.close();

            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<communities>\n";

            for(int i = 0; i < comunidades.size(); i++){
                out << "\t\t<community id=\"" << i+1 << "\">\n";

                for(int j = 0; j < comunidades[i].size(); j++){
                    out << "\t\t\t<node>" << comunidades[i][j].c_str() << "</node>\n";
                }

                out << "\t\t</community>\n";
            }

            out << "\t</communities>\n";
            out << "</PFStats>";
            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Correlation list data was exported.");
}

void Alignment::exportCorrTable(QString filename, int type, bool perc){
    if(perc){
        switch(type){
            case 0:
            {
                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "ALL ";
                    for(int j = 0; j < residuesComm[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(int j = 0; j < communityX[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " " << QString::number(communityXAll[i][j],'f',2) << " ";

                        for(int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == -1) out << "X ";
                            else out << QString::number(communityX[i][j][k]*100,'f',4) << " ";
                        }
                        out << "\n";
                    }

                    f.close();
                }

                break;
            }
            case 1:
            {
                vector<string> tempFN = split(filename.toStdString(),'.');
                if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                    filename += ".xml";

                //Salva em arquivo
                QFile f(filename);
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<?xml version=\"1.0\"?>\n";
                out << "<PFStats>\n";

                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    out << "<column>ALL</column>\n";
                    for(int j = 0; j < residuesComm[i].size(); j++){
                        out << "<column>" << residuesComm[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(int j = 0; j < communityX[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" c0=\"" << QString::number(communityXAll[i][j],'f',2) << "\" ";

                        for(int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == 0)
                                out << "c" << k+1 << "=\"X\" ";
                            else
                                out << "c" << k+1 << "=\"" << QString::number(communityX[i][j][k]*100,'f',4) << "\" ";
                        }
                        out << "/>\n";
                    }

                    out << "\t\t</table_data>\n";

                    out << "\t</community>\n";
                }

                out << "</PFStats>";

                f.close();
                break;
            }
            case 2:
            {
                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n";
                    out << "<body>\n";

                    out << "<table border=1>\n";
                    out << "<center>\n";

                    out << "<tr>\n";
                    out << "<th>POS</th>\n<th>ALL</th>\n";

                    for(int j = 0; j < residuesComm[i].size(); j++){
                        out << "<th>" << residuesComm[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(int j = 0; j < communityX[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesComm[i][j].c_str() << "</b></td>\n";
                        out << "<td>" << QString::number(communityXAll[i][j],'f',1) << "</td>\n";

                        for(int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == 0)
                                out << "<td>X</td>\n";
                            else
                                if(communityX[i][j][k]*100 - communityXAll[i][j] > 15)
                                    out << "<td><font color=#00FF00>" << QString::number(communityX[i][j][k]*100,'f',1) << "</td>\n";
                                else out << "<td>" << QString::number(communityX[i][j][k]*100,'f',1) << "</td>\n";
                        }
                        out << "</tr>";
                    }


                    out << "</body>\n";
                    out << "</html>";
                    f.close();
                }

                break;
            }
            default:
            {
                QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
                return;
            }
        }
    }else{
        switch(type){
            case 0:
            {
                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    for(int j = 0; j < residuesCommPs[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(int j = 0; j < communityXps[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";

                        for(int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == -1) out << "X ";
                            else out << QString::number(communityXps[i][j][k]) << " ";
                        }
                        out << "\n";
                    }

                    f.close();
                }
                break;
            }
            case 1:
            {
                vector<string> tempFN = split(filename.toStdString(),'.');
                if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                    filename += ".xml";

                //Salva em arquivo
                QFile f(filename);
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<?xml version=\"1.0\"?>\n";
                out << "<PFStats>\n";

                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    for(int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<column>" << residuesCommPs[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(int j = 0; j < communityXps[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" ";

                        for(int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == 0)
                                out << "c" << k << "=\"X\" ";
                            else
                                out << "c" << k << "=\"" << QString::number(communityXps[i][j][k]) << "\" ";
                        }
                        out << "/>\n";
                    }

                    out << "\t\t</table_data>\n";

                    out << "\t</community>\n";
                }

                out << "</PFStats>";

                f.close();
                break;
            }
            case 2:
            {
                for(int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(int j = 0; j < tempFN.size()-1; j++){
                            path +=tempFN[j];
                        }
                    }
                    path += "_comm" + QString::number(i+1).toStdString() + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n";
                    out << "<body>\n";

                    out << "<table border=1>\n";
                    out << "<center>\n";

                    out << "<tr>\n";
                    out << "<th>POS</th>\n";

                    for(int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<th>" << residuesCommPs[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(int j = 0; j < communityXps[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesCommPs[i][j].c_str() << "</b></td>\n";

                        for(int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == 0)
                                out << "<td>X</td>\n";
                            else
                                out << "<td>" << QString::number(communityXps[i][j][k]) << "</td>\n";
                        }
                        out << "</tr>";
                    }


                    out << "</table>\n";
                    out << "</body>\n";
                    out << "</html>";
                    f.close();
                }
                break;
            }
            default:
            {
                QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
                return;
            }
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Correlation table data was exported.");
}

void Alignment::exportAdh(QString filename, int type){
    switch(type){
        case 0:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "txt" && tempFN[tempFN.size()-1] != "TXT")
                filename += ".txt";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "PROTEIN_SEQUENCE\t";
            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "Comm" << i+1 << " (" << residuesComm[i].size() << ")\t";
            }
            out << "\n";

            for(int i = 0; i < sequences.size()-1; i++){
                out << sequencenames[i].c_str() << "\t";

                for(int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << QString::number(psa,'f',6) << "\t";
                    }
                }
                out << "\n";
            }

            f.close();
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "csv" && tempFN[tempFN.size()-1] != "CSV")
                filename += ".csv";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            for(int i = 0; i < sequences.size()-1; i++){
                out << sequencenames[i].c_str();

                for(int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << "," << QString::number(psa,'f',6);
                    }
                }
                out << "\n";
            }

            f.close();
            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "<adherence>\n";

            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                if(Communities[i].aa.size() > 1){
                    out << "\t<community id=\"" << i+1 << "\">\n";

                    for(int j = 0; j < sequences.size()-1; j++){
                        float psa = this->PSA(j,i);

                        out << "\t\t<protein value=\"" << QString::number(psa,'f',6) << "\">" << sequencenames[j].c_str() << "</protein>\n";
                    }
                    out << "\t</community>\n";
                }
            }

            out << "</adherence>\n";
            out << "</PFStats>\n";

            f.close();
            break;
        }
        case 3:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "html" && tempFN[tempFN.size()-1] != "HTML")
                filename += ".html";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<html>\n";
            out << "<body>\n";

            out << "<table border=1>\n";
            out << "<center>\n";

            out << "<tr>\n";
            out << "<th>PROTEIN SEQUENCE</th>\n";

            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "<th>Comm" << i+1 << " (" << residuesComm[i].size() << ")</th>\n";
            }
            out << "</tr>\n";

            for(int i = 0; i < sequences.size()-1; i++){
                out << "<tr>\n<td><b>" << sequencenames[i].c_str() << "</b></td>\n";

                for(int j = 0; j < this->getNumOfUtilComms(); j++){
                    if(Communities[j].aa.size() > 1){
                        float psa = this->PSA(i,j);

                        out << "<td>" << QString::number(psa,'f',6) << "</td>\n";
                    }
                }
                out << "</tr>\n";
            }

            out << "</table></body>\n</html>";

            f.close();
            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }
    QMessageBox::information(NULL,"Exporting Data","Adherence data was exported.");
}

vector<int> Alignment::getRefSeqCodes(){
    vector<int> codes;
    for(int i = 0; i < refSeqs.size(); i++){
        codes.push_back(seqname2seqint(refSeqs[i]));
    }

    return codes;
}

void Alignment::exportResComm(QString filename, int type){
    vector<int> refCodes = getRefSeqCodes();

    switch(type){
        case 0:
        {
            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(int j = 0; j < tempFN.size()-1; j++){
                        path +=tempFN[j];
                    }
                }
                path += "_comm" + QString::number(i+1).toStdString() + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);


                out << "Sequence";

                for(int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t" << textCab.c_str();
                }
                out << "\n";

                for(int j = 0; j < refSeqs.size(); j++){
                    out << sequencenames[refCodes[j]].c_str();

                    for(int k = 0; k < Communities[i].pos.size(); k++){
                        if(sequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence(refCodes[j]+1,Communities[i].pos[k])+GetOffsetFromSeqName(sequencenames[refCodes[j]])).toStdString();

                            out << "\t" << textItem.c_str();
                        }else{
                            if(sequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "\t - ";
                            else{
                                string textItem = sequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence(refCodes[j]+1,Communities[i].pos[k])+GetOffsetFromSeqName(sequencenames[refCodes[j]])).toStdString();

                                out << "\t" << textItem.c_str();
                            }
                        }
                    }
                    out << "\n";
                }
                f.close();
            }
            break;
        }
        case 1:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "<commRes>\n";

            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t\t<residue alignNumber=\"" << textCab.c_str() << "\">\n";


                    for(int k = 0; k < refSeqs.size(); k++){
                        if(sequences[refCodes[k]][Communities[i].pos[j]] == Communities[i].aa[j]){
                            string textItem = Communities[i].aa[j] + QString::number(AlignNumbering2Sequence(refCodes[k]+1,Communities[i].pos[j])+GetOffsetFromSeqName(sequencenames[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"true\">" << sequencenames[refCodes[k]].c_str() << "</sequence>\n";
                        }else if(sequences[refCodes[k]][Communities[i].pos[j]] != '-'){
                            string textItem = sequences[refCodes[k]][Communities[i].pos[j]] + QString::number(AlignNumbering2Sequence(refCodes[k]+1,Communities[i].pos[j])+GetOffsetFromSeqName(sequencenames[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"false\">" << sequencenames[refCodes[k]].c_str() << "</sequence>\n";
                        }
                    }

                    out << "\t\t</residue>\n";
                }

                out << "\t</community>\n";
            }

            out << "</commRes>\n";
            out << "</PFStats>";

            f.close();
            break;
        }
        case 2:
        {
            for(int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(int j = 0; j < tempFN.size()-1; j++){
                        path +=tempFN[j];
                    }
                }
                path += "_comm" + QString::number(i+1).toStdString() + ".html";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n";
                out << "<body>\n";

                out << "<table border=1>\n";
                out << "<center>\n";

                out << "<tr>\n";
                out << "<th>Sequence</th>\n";

                for(int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "<th>" << textCab.c_str() << "</th>\n";
                }
                out << "</tr>\n";

                for(int j = 0; j < refSeqs.size(); j++){
                    out << "<tr>\n<td><b>" << sequencenames[refCodes[j]].c_str() << "</b></td>\n";

                    for(int k = 0; k < Communities[i].pos.size(); k++){
                        if(sequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence(refCodes[j]+1,Communities[i].pos[k])+GetOffsetFromSeqName(sequencenames[refCodes[j]])).toStdString();

                            out << "<td><b><font color=#00FF00>" << textItem.c_str() << "</font></b></td>\n";
                        }else{
                            if(sequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "<td><center>-</center></td>\n";
                            else{
                                string textItem = sequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence(refCodes[j]+1,Communities[i].pos[k])+GetOffsetFromSeqName(sequencenames[refCodes[j]])).toStdString();

                                out << "<td>" << textItem.c_str() << "</td>\n";
                            }
                        }
                    }
                    out << "</tr>\n";
                }
                out << "</table>\n";
                out << "</body>\n";
                out << "</html>";
                f.close();
            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Residues of communities data was exported.");
}

void Alignment::exportLookProt(QString filename, int type){
    set<string> proteins;

    //GET LIST OF PROTEINS NAMES
    for(int i = 0; i < uniprotMined.size(); i++)
        proteins.insert(uniprotMined[i]->getName());

    switch(type){
        case 0:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "RESIDUE CONS/COMM TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){

                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature* f = entryprot->getFeature(j);

                            if(f->getResidueColigated() == "") out << "UNKNOWN ";
                            else out << f->getResidueColigated().c_str() << " ";

                            if(f->getAgregate() == 0) out << "CONS ";
                            else if(f->getAgregate() > 0) out << f->getAgregate() << " ";
                            else out << "UNKNOWN ";

                            if(f->getType() == "") out << "NONE ";
                            else out << f->getType().c_str() << " ";

                            if(f->getDescription() == "") out << "NONE ";
                            else out << f->getDescription().c_str() << " ";

                            if(f->getPosition() == -1) out << "NONE ";
                            else out << f->getPosition() << " ";

                            if(f->getBegin() == -1) out << "NONE ";
                            else out << f->getBegin() << " ";

                            if(f->getEnd() == -1) out << "NONE ";
                            else out << f->getEnd() << " ";

                            if(f->getOriginal() == "") out << "NONE ";
                            else out << f->getOriginal().c_str() << " ";

                            if(f->getVariation() == "") out << "NONE";
                            else out << f->getVariation().c_str();

                            out << "\n";
                        }

                    }

                }
                f.close();
            }
            break;
        }
        case 1:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature* f = entryprot->getFeature(j);

                            if(f->getResidueColigated() == "") out << "UNKNOWN,";
                            else out << f->getResidueColigated().c_str() << ",";

                            if(f->getAgregate() == 0) out << "CONS,";
                            else if(f->getAgregate() > 0) out << f->getAgregate() << ",";
                            else out << "UNKNOWN,";

                            if(f->getType() == "") out << "NONE,";
                            else out << f->getType().c_str() << ",";

                            if(f->getDescription() == "") out << "NONE,";
                            else out << f->getDescription().c_str() << ",";

                            if(f->getPosition() == -1) out << "NONE,";
                            else out << f->getPosition() << ",";

                            if(f->getBegin() == -1) out << "NONE,";
                            else out << f->getBegin() << ",";

                            if(f->getEnd() == -1) out << "NONE,";
                            else out << f->getEnd() << ",";

                            if(f->getOriginal() == "") out << "NONE,";
                            else out << f->getOriginal().c_str() << ",";

                            if(f->getVariation() == "") out << "NONE";
                            else out << f->getVariation().c_str();

                            out << "\n";
                        }

                    }

                }
                f.close();
            }

            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                out << "\t<protein name=\"" << protName.c_str() << "\" ";

                for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        if(entryprot->getDataset() == 0) out << "dataset=\"Swiss-Prot\">\n";
                        else out << "dataset=\"TrEMBL\">\n";
                        break;
                    }
                }

                for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            Feature *f = entryprot->getFeature(j);

                            if(f->getAgregate() == 0) out << "\t\t<feature agregate=\"CONS\" ";
                            else out << "\t\t<feature agregate=\"" << f->getAgregate() << "\" ";

                            if(f->getType() != "")
                                out << "type=\"" << f->getType().c_str() << "\" ";
                            if(f->getDescription() != "")
                                out << "description=\"" << f->getDescription().c_str() << "\" ";
                            if(f->getId() != "")
                                out << "id=\"" << f->getId().c_str() << "\" ";
                            out << ">\n";

                            if(f->getOriginal() != "")
                                out << "\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                            if(f->getVariation() != "")
                                out << "\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                            if(f->getBegin() != -1 || f->getPosition() != -1){
                                out << "\t\t\t<location>\n";

                                if(f->getPosition() != -1)
                                    out << "\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                                if(f->getBegin() != -1 && f->getEnd() != -1){
                                    out << "\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                                    out << "\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                                }

                                out << "\t\t\t</location>\n";
                            }

                            out << "\t\t</feature>\n";
                        }

                    }
                }

                out << "\t</protein>\n";
            }

            out << "</PFStats>";
            f.close();

            break;
        }
        case 3:
        {
            for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++) {
                string protName = *it;

                string path = filename.toStdString() + "/" + protName + ".html";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n<body>\n<table border=1>\n<center>\n";
                out << "<tr>\n";
                out << "<th>Residue</th>\n";
                out << "<th>Communitie</th>\n";
                out << "<th>Type</th>\n";
                out << "<th>Description</th>\n";
                out << "<th>Position</th>\n";
                out << "<th>Begin</th>\n";
                out << "<th>End</th>\n";
                out << "<th>Original</th>\n";
                out << "<th>Variation</th>\n";
                out << "</tr>\n";

                for(int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        for(int j = 0; j < entryprot->countFeatures(); j++){
                            out << "<tr>\n";

                            Feature* f = entryprot->getFeature(j);

                            out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";

                            if(f->getAgregate() == 0) out << "<td>CONS</td>\n";
                            else if(f->getAgregate() > 0) out << "<td>" << f->getAgregate() << "</td>\n";
                            else out << "<td>UNKNOWN</td>\n";

                            if(f->getType() == "") out << "<td>NONE</td>\n";
                            else out << "<td>" << f->getType().c_str() << "</td>\n";

                            if(f->getDescription() == "") out << "<td>NONE</td>\n";
                            else out << "<td>" << f->getDescription().c_str() << "</td>\n";

                            if(f->getPosition() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getPosition() << "</td>\n";

                            if(f->getBegin() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getBegin() << "</td>\n";

                            if(f->getEnd() == -1) out << "<td></td>\n";
                            else out << "<td>" << f->getEnd() << "</td>\n";

                            if(f->getOriginal() == "") out << "<td></td>\n";
                            else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                            if(f->getVariation() == "") out << "<td></td>\n";
                            else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                            out << "</tr>\n";
                        }

                    }

                }
                out << "</body>\n</html>";
                f.close();

            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Uniprot Mined data was exported succesfully.");
}

void Alignment::exportLookComm(QString filename, int type){
    switch(type){
        case 0:
        {
            //COMMS
            for(int i = 0; i < comunidades.size(); i++){
                for(int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(int k = 0; k < resFeats.size(); k++){
                        out << resFeats[k]->getName().c_str() << " ";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << " ";
                        else out << "UNKNOWN ";

                        if(f->getType() != "") out << f->getType().c_str() << " ";
                        else out << "NONE ";

                        if(f->getDescription() != "") out << f->getDescription().c_str() << " ";
                        else out << "NONE ";

                        if(f->getPosition() == -1) out << "NONE ";
                        else out << f->getPosition() << " ";

                        if(f->getBegin() == -1) out << "NONE ";
                        else out << f->getBegin() << " ";

                        if(f->getEnd() == -1) out << "NONE ";
                        else out << f->getEnd() << " ";

                        if(f->getOriginal() == "") out << "NONE ";
                        else out << f->getOriginal().c_str() << " ";

                        if(f->getVariation() == "") out << "NONE";
                        else out << f->getVariation().c_str();

                        out << "\n";

                    }

                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes();

            for(int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(int k = 0; k < resFeats.size(); k++){
                    out << resFeats[k]->getName().c_str() << " ";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << " ";
                    else out << "UNKNOWN ";

                    if(f->getType() != "") out << f->getType().c_str() << " ";
                    else out << "NONE ";

                    if(f->getDescription() != "") out << f->getDescription().c_str() << " ";
                    else out << "NONE ";

                    if(f->getPosition() == -1) out << "NONE ";
                    else out << f->getPosition() << " ";

                    if(f->getBegin() == -1) out << "NONE ";
                    else out << f->getBegin() << " ";

                    if(f->getEnd() == -1) out << "NONE ";
                    else out << f->getEnd() << " ";

                    if(f->getOriginal() == "") out << "NONE ";
                    else out << f->getOriginal().c_str() << " ";

                    if(f->getVariation() == "") out << "NONE";
                    else out << f->getVariation().c_str();

                    out << "\n";

                }

                f.close();
            }

            break;
        }
        case 1:
        {
            //COMM
            for(int i = 0; i < comunidades.size(); i++){
                for(int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".csv";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(int k = 0; k < resFeats.size(); k++){
                        out << resFeats[k]->getName().c_str() << ",";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << ",";
                        else out << "UNKNOWN,";

                        if(f->getType() != "") out << f->getType().c_str() << ",";
                        else out << "NONE,";

                        if(f->getDescription() != "") out << f->getDescription().c_str() << ",";
                        else out << "NONE,";

                        if(f->getPosition() == -1) out << "NONE,";
                        else out << f->getPosition() << ",";

                        if(f->getBegin() == -1) out << "NONE,";
                        else out << f->getBegin() << ",";

                        if(f->getEnd() == -1) out << "NONE,";
                        else out << f->getEnd() << ",";

                        if(f->getOriginal() == "") out << "NONE,";
                        else out << f->getOriginal().c_str() << ",";

                        if(f->getVariation() == "") out << "NONE";
                        else out << f->getVariation().c_str();

                        out << "\n";

                    }

                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes();

            for(int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(int k = 0; k < resFeats.size(); k++){
                    out << resFeats[k]->getName().c_str() << ",";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << f->getResidueColigated().c_str() << ",";
                    else out << "UNKNOWN,";

                    if(f->getType() != "") out << f->getType().c_str() << ",";
                    else out << "NONE,";

                    if(f->getDescription() != "") out << f->getDescription().c_str() << ",";
                    else out << "NONE,";

                    if(f->getPosition() == -1) out << "NONE,";
                    else out << f->getPosition() << ",";

                    if(f->getBegin() == -1) out << "NONE,";
                    else out << f->getBegin() << ",";

                    if(f->getEnd() == -1) out << "NONE,";
                    else out << f->getEnd() << ",";

                    if(f->getOriginal() == "") out << "NONE,";
                    else out << f->getOriginal().c_str() << ",";

                    if(f->getVariation() == "") out << "NONE";
                    else out << f->getVariation().c_str();

                    out << "\n";

                }

                f.close();
            }


            break;
        }
        case 2:
        {
            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "xml" && tempFN[tempFN.size()-1] != "XML")
                filename += ".xml";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                return;
            }

            QTextStream out(&f);

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            //COMM
            for(int i = 0; i < comunidades.size(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(int j = 0; j < comunidades[i].size(); j++){
                    out << "\t\t<residue alignN=\"" << comunidades[i][j].c_str() << "\">\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(int k = 0; k < resFeats.size(); k++){
                        out << "\t\t\t<feature ";
                        out << "protein=\"" << resFeats[k]->getName().c_str() << "\" ";

                        if(resFeats[k]->getDataset() == 0) out << "dataset=\"Swiss-Prot\" ";
                        else out << "dataset=\"TrEMBL\" ";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getType() != "")
                            out << "type=\"" << f->getType().c_str() << "\" ";
                        if(f->getDescription() != "")
                            out << "description=\"" << f->getDescription().c_str() << "\" ";
                        if(f->getId() != "")
                            out << "id=\"" << f->getId().c_str() << "\" ";
                        out << ">\n";

                        if(f->getOriginal() != "")
                            out << "\t\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                        if(f->getVariation() != "")
                            out << "\t\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                        if(f->getBegin() != -1 || f->getPosition() != -1){
                            out << "\t\t\t\t<location>\n";

                            if(f->getPosition() != -1)
                                out << "\t\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                            if(f->getBegin() != -1 && f->getEnd() != -1){
                                out << "\t\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                                out << "\t\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                            }

                            out << "\t\t\t\t</location>\n";
                        }

                        out << "\t\t\t</feature>\n";
                    }

                    out << "\t\t</residue>\n";
                }

                out << "\t</community>\n";
            }

            //CONS
            vector<string> residues = this->getConsRes();

            out << "\t<community id=\"CONS\">\n";

            for(int i = 0; i < residues.size(); i++){
                out << "\t\t<residue alignN=\"" << residues[i].c_str() << "\">\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(int k = 0; k < resFeats.size(); k++){
                    out << "\t\t\t<feature ";
                    out << "protein=\"" << resFeats[k]->getName().c_str() << "\" ";

                    if(resFeats[k]->getDataset() == 0) out << "dataset=\"Swiss-Prot\" ";
                    else out << "dataset=\"TrEMBL\" ";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getType() != "")
                        out << "type=\"" << f->getType().c_str() << "\" ";
                    if(f->getDescription() != "")
                        out << "description=\"" << f->getDescription().c_str() << "\" ";
                    if(f->getId() != "")
                        out << "id=\"" << f->getId().c_str() << "\" ";
                    out << ">\n";

                    if(f->getOriginal() != "")
                        out << "\t\t\t\t<original>" << f->getOriginal().c_str() << "</original>\n";
                    if(f->getVariation() != "")
                        out << "\t\t\t\t<variation>" << f->getVariation().c_str() << "</variation>\n";

                    if(f->getBegin() != -1 || f->getPosition() != -1){
                        out << "\t\t\t\t<location>\n";

                        if(f->getPosition() != -1)
                            out << "\t\t\t\t\t<position position=\"" << f->getPosition() << "\"/>\n";

                        if(f->getBegin() != -1 && f->getEnd() != -1){
                            out << "\t\t\t\t\t<begin position=\"" << f->getBegin() << "\"/>\n";
                            out << "\t\t\t\t\t<end position=\"" << f->getEnd() << "\"/>\n";
                        }

                        out << "\t\t\t\t</location>\n";
                    }

                    out << "\t\t\t</feature>\n";
                }

                out << "\t\t</residue>\n";
            }

            out << "\t</community>\n";
            out << "</PFStats>";

            f.close();
            break;
        }
        case 3:
        {
            //COMM
            for(int i = 0; i < comunidades.size(); i++){
                for(int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".html";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "<html>\n<body>\n<table border=1>\n<center>\n";
                    out << "<tr>\n";
                    out << "<th>Protein</th>\n";
                    out << "<th>Seq. Number</th>\n";
                    out << "<th>Type</th>\n";
                    out << "<th>Description</th>\n";
                    out << "<th>Position</th>\n";
                    out << "<th>Begin</th>\n";
                    out << "<th>End</th>\n";
                    out << "<th>Original</th>\n";
                    out << "<th>Variation</th>\n";
                    out << "</tr>\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(int k = 0; k < resFeats.size(); k++){
                        out << "<tr>\n";

                        out << "<td>" << resFeats[k]->getName().c_str() << "</td>\n";

                        Feature *f = resFeats[k]->getFeature(0);

                        if(f->getResidueColigated() != "") out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";
                        else out << "<td>UNKNOWN</td>";

                        if(f->getType() != "") out << "<td>" << f->getType().c_str() << "</td>\n";
                        else out << "<td>NONE</td>";

                        if(f->getDescription() != "") out << "<td>" << f->getDescription().c_str() << "</td>\n";
                        else out << "<td>NONE</td>\n";

                        if(f->getPosition() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getPosition() << "</td>\n";

                        if(f->getBegin() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getBegin() << "</td>\n";

                        if(f->getEnd() == -1) out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getEnd() << "</td>\n";

                        if(f->getOriginal() == "") out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                        if(f->getVariation() == "") out << "<td>NONE</td>\n";
                        else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                        out << "<tr>\n";

                    }

                    out << "</body>\n</html>";
                    f.close();
                }
            }

            //CONS
            vector<string> residues = this->getConsRes();

            for(int i = 0; i < residues.size(); i++){
                string path = filename.toStdString() + "/cons_" + residues[i] + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "<html>\n<body>\n<table border=1>\n<center>\n";
                out << "<tr>\n";
                out << "<th>Protein</th>\n";
                out << "<th>Seq. Number</th>\n";
                out << "<th>Type</th>\n";
                out << "<th>Description</th>\n";
                out << "<th>Position</th>\n";
                out << "<th>Begin</th>\n";
                out << "<th>End</th>\n";
                out << "<th>Original</th>\n";
                out << "<th>Variation</th>\n";
                out << "</tr>\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(residues[i]);

                for(int k = 0; k < resFeats.size(); k++){
                    out << "<tr>\n";

                    out << "<td>" << resFeats[k]->getName().c_str() << "</td>\n";

                    Feature *f = resFeats[k]->getFeature(0);

                    if(f->getResidueColigated() != "") out << "<td>" << f->getResidueColigated().c_str() << "</td>\n";
                    else out << "<td>UNKNOWN</td>";

                    if(f->getType() != "") out << "<td>" << f->getType().c_str() << "</td>\n";
                    else out << "<td>NONE</td>";

                    if(f->getDescription() != "") out << "<td>" << f->getDescription().c_str() << "</td>\n";
                    else out << "<td>NONE</td>\n";

                    if(f->getPosition() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getPosition() << "</td>\n";

                    if(f->getBegin() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getBegin() << "</td>\n";

                    if(f->getEnd() == -1) out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getEnd() << "</td>\n";

                    if(f->getOriginal() == "") out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getOriginal().c_str() << "</td>\n";

                    if(f->getVariation() == "") out << "<td>NONE</td>\n";
                    else out << "<td>" << f->getVariation().c_str() << "</td>\n";

                    out << "<tr>\n";

                }

                out << "</body>\n</html>";
                f.close();

            }

            break;
        }
        default:
        {
            QMessageBox::critical(NULL,"Error","An error ocurred while trying to export this result.");
            return;
        }
    }

    QMessageBox::information(NULL,"Exporting Data","Uniprot Mined data was exported succesfully.");
}

void Alignment::uniprotLook(bool cons, bool comm, vector<string> proteins, vector<int> idproteins){
    QProgressDialog progress("Reading data from Uniprot... (1/2)", "Abort", 0, proteins.size()+1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    vector<Uniprot*> dataprot;

    for(int i = 0; i < proteins.size(); i++){
        Uniprot *unientry = new Uniprot();
        progress.setValue(i+1);

        if(progress.wasCanceled()) return;

        //vector<string> vecSplit = this->split(sequencenames[i],'/');
        //string protName = vecSplit[0];
        QString url = "http://www.uniprot.org/uniprot/" + QString::fromStdString(proteins[i]) + ".xml";


        //Faz a conexão
        QUrl qurl = url;
        QNetworkAccessManager manager;
        QNetworkRequest request(qurl);
        QNetworkReply *reply(manager.get(request));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        //QObject::connect(reply, SIGNAL(urlChanged (const QUrl&)), &loop, SLOT(onRedirected(const QUrl&)));
        loop.exec();
        //qDebug(reply->readAll());
        QString nurl = reply->readAll();


        //Salvar arquivo
        if(nurl == ""){
            QNetworkAccessManager manager2;
            qurl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            QNetworkRequest request2(qurl);
            QNetworkReply *reply2(manager2.get(request2));
            QObject::connect(reply2, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            QByteArray xmlcontent = reply2->readAll();
            //QMessageBox::information(NULL,"A",xmlcontent);

            //LER MONTAR UNIPROT E ADD NA LISTA
            //ERRO NA LEITURA
            QXmlStreamReader reader(xmlcontent);

            //reader.readNext();

            while(!reader.atEnd()){//Esse while serve só para ler coisas que podem estar antes do entry
                reader.readNext();
                if(reader.isStartElement() && reader.name() == "entry"){

                    QString dataset = reader.attributes().value("dataset").toString();

                    if(dataset == "Swiss-Prot") unientry->setDataset(0);
                    else unientry->setDataset(1);

                    while(!reader.atEnd()){//Vai ler a entry toda
                        reader.readNext();

                        if(reader.isStartElement()){
                            if(reader.name() == "accession"){
                                //printf("ACCESSION: %s\n",reader.readElementText().toStdString().c_str());
                                unientry->addAccession(reader.readElementText().toStdString());
                            }
                            else if(reader.name() == "protein") reader.skipCurrentElement();
                            else if(reader.name() == "gene") reader.skipCurrentElement();
                            else if(reader.name() == "organism") reader.skipCurrentElement();
                            else if(reader.name() == "reference") reader.skipCurrentElement();
                            else if(reader.name() == "comment") reader.skipCurrentElement();
                            else if(reader.name() == "dbReference") reader.skipCurrentElement();
                            else if(reader.name() == "proteinExistence") reader.skipCurrentElement();
                            else if(reader.name() == "keyword") reader.skipCurrentElement();
                            else if(reader.name() == "evidence") reader.skipCurrentElement();
                            else if(reader.name() == "sequence") reader.skipCurrentElement();
                            else if(reader.name() == "name"){
                                //printf("NAME: %s\n",reader.readElementText().toStdString().c_str());
                                unientry->setName(reader.readElementText().toStdString());
                            }
                            else if(reader.name() == "feature"){
                                Feature *f = new Feature();

                                if(reader.attributes().hasAttribute("type"))
                                    f->setType(reader.attributes().value("type").toString().toStdString());
                                if(reader.attributes().hasAttribute("description"))
                                    f->setDescription(reader.attributes().value("description").toString().toStdString());
                                if(reader.attributes().hasAttribute("id"))
                                    f->setId(reader.attributes().value("id").toString().toStdString());

                                while(!reader.atEnd()){ //Vai ler a feature toda
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "original")
                                        f->setOriginal(reader.readElementText().toStdString());
                                    else if(reader.isStartElement() && reader.name() == "variation")
                                        f->setVariation(reader.readElementText().toStdString());
                                    else if(reader.isStartElement() && reader.name() == "location"){
                                        while(!reader.atEnd()){//Vai ler o location todo
                                            reader.readNext();

                                            if(reader.isStartElement()){
                                                if(reader.name() == "begin")
                                                    f->setBegin(reader.attributes().value("position").toInt());
                                                if(reader.name() == "end")
                                                    f->setEnd(reader.attributes().value("position").toInt());
                                                if(reader.name() == "position")
                                                    f->setPosition(reader.attributes().value("position").toInt());
                                            }else if(reader.isEndElement() && reader.name() == "location")
                                                break;
                                        }
                                    }else if(reader.isEndElement() && reader.name() == "feature"){
                                        //QMessageBox::information(NULL,"A",QString::fromStdString(f.toString()));
                                        //printf("FEATURE:\n%s",f.toString().c_str());
                                        unientry->addFeature(f);
                                        break;
                                    }
                                }
                            }
                        }else if(reader.isEndElement() && reader.name() == "entry"){
                            break;
                        }
                    }

                }//TENHO QUE LER TUDO AI EM CIMA
            }

        }
        //printf("\n%s\n",unientry->toString().c_str());
        //printf("READING %s XML\n",unientry->getName().c_str());
        dataprot.push_back(unientry);
    }
    //QMessageBox::information(NULL,"A","PRIMERA PARTE OK");
    //SEGUNDA PARTE => TRABALHAR OS DADOS OBTIDOS


    vector<vector<string> > residuesList;
    vector<vector<string> > alignResiduesList;
    QProgressDialog progress2("Working on data... (1/2)", "Abort", 0, dataprot.size() + 5);
    progress2.setWindowModality(Qt::WindowModal);
    progress.show();
    progress2.setValue(1);

    if(cons){
        //Calculate Conserved Residues
        vector<char> conservedaa;
        vector<int> conservedpos;

        this->CalculateFrequencies();

        for(int i = 0; i < frequencies.size()-2; i++){
            for(int j = 1; j <= 20; j++){
                float freq = frequencies[i][j]/((float)sequences.size());
                //printf("freq=%f / minCons=%f\n",freq,minCons);
                if(freq >= minCons){
                    conservedaa.push_back(num2aa(j));
                    conservedpos.push_back(i);
                }
            }
        }

        for(int i = 0; i < idproteins.size(); i++){
            vector<string> vec;
            vector<string> vec2;
            residuesList.push_back(vec);
            alignResiduesList.push_back(vec2);
            for(int j = 0; j < conservedaa.size(); j++){
                if(sequences[idproteins[i]][conservedpos[j]]==conservedaa[j]){
                    string res = conservedaa[j] + QString::number(AlignNumbering2Sequence(idproteins[i]+1,conservedpos[j]) + GetOffsetFromSeqName(sequencenames[idproteins[i]])).toStdString();
                    residuesList[i].push_back(res);
                    string res2 = conservedaa[j] + QString::number(conservedpos[j]).toStdString();
                    alignResiduesList[i].push_back(res2);
                }
            }
        }

    }


    progress2.setValue(5);
    uniprotMined.clear();


    for(int i = 0; i < dataprot.size(); i++){
        Uniprot *entry = new Uniprot(*dataprot[i]);
        Uniprot *out = new Uniprot();
        out->setName(entry->getName());
        out->setDataset(entry->getDataset());
        printf("ENTRY: %s\nOUT:%s\n\n",entry->getName().c_str(),out->getName().c_str());

        for(int j = 0; j < entry->countAccession(); j++)
            out->addAccession(entry->getAcesssionAt(j));

        progress2.setValue(i + 5);

        if(progress.wasCanceled()) return;

        //printf("%s\n",entry->toString().c_str());

        for(int j = 0; j < entry->countFeatures(); j++){
            Feature *f = entry->getFeature(j);
            //printf("%s\n",f->toString().c_str());
            if(f->getType() != "chain"){

                if(cons){
                    for(int k = 0; k < residuesList[i].size(); k++){
                        string respos = residuesList[i][k];
                        string resAlign = alignResiduesList[i][k];
                        int pos = stoi(respos.substr(1));

                        if(pos >= f->getBegin() && pos <= f->getEnd()){
                            Feature *f1 = new Feature();
                            f1->setAggregation(0);
                            f1->setBegin(f->getBegin());
                            f1->setDescription(f->getDescription());
                            f1->setEnd(f->getEnd());
                            f1->setId(f->getId());
                            f1->setOriginal(f->getOriginal());
                            f1->setPosition(f->getPosition());
                            f1->setResidueColigated(respos);
                            f1->setAlignResidue(resAlign);
                            f1->setType(f->getType());
                            f1->setVariation(f->getVariation());
                            //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                            out->addFeature(f1);
                        }else if(pos == f->getPosition()){
                            Feature *f1 = new Feature();
                            f1->setAggregation(0);
                            f1->setBegin(f->getBegin());
                            f1->setDescription(f->getDescription());
                            f1->setEnd(f->getEnd());
                            f1->setId(f->getId());
                            f1->setOriginal(f->getOriginal());
                            f1->setPosition(f->getPosition());
                            f1->setResidueColigated(respos);
                            f1->setAlignResidue(resAlign);
                            f1->setType(f->getType());
                            f1->setVariation(f->getVariation());
                            //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                            out->addFeature(f1);
                        }
                    }
                }

                if(comm){
                    for(int k = 0; k < comunidades.size(); k++){
                        for(int l = 0; l < comunidades[k].size(); l++){
                            string respos = comunidades[k][l];
                            char aa = respos[0];
                            int alignPos = stoi(respos.substr(1));
                            int pos = AlignNumbering2Sequence(idproteins[i]+1,alignPos) + GetOffsetFromSeqName(sequencenames[idproteins[i]]);
                            string newResPos = aa + QString::number(pos).toStdString();
                            string newAlignPos = aa + QString::number(alignPos).toStdString();


                            if(pos >= f->getBegin() && pos <= f->getEnd()){
                                Feature *f1 = new Feature();
                                f1->setAggregation(k+1);
                                f1->setBegin(f->getBegin());
                                f1->setDescription(f->getDescription());
                                f1->setEnd(f->getEnd());
                                f1->setId(f->getId());
                                f1->setOriginal(f->getOriginal());
                                f1->setPosition(f->getPosition());
                                f1->setResidueColigated(newResPos);
                                f1->setAlignResidue(newAlignPos);
                                f1->setType(f->getType());
                                f1->setVariation(f->getVariation());
                                //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                                out->addFeature(f1);
                            }else if(pos == f->getPosition()){
                                Feature *f1 = new Feature();
                                f1->setAggregation(k+1);
                                f1->setBegin(f->getBegin());
                                f1->setDescription(f->getDescription());
                                f1->setEnd(f->getEnd());
                                f1->setId(f->getId());
                                f1->setOriginal(f->getOriginal());
                                f1->setPosition(f->getPosition());
                                f1->setResidueColigated(newResPos);
                                f1->setAlignResidue(newAlignPos);
                                f1->setType(f->getType());
                                f1->setVariation(f->getVariation());
                                //DEPOIS TROCAR ISSO PRO SOBRECARGA DE OPERADOR COPY
                                out->addFeature(f1);
                            }
                        }
                    }
                }
            }
            f->kill();
        }
        entry->kill();
        uniprotMined.push_back(out);
    }

/*
    for(int i = 0; i < uniprotMined.size(); i++){
        printf("%s\n",uniprotMined[i]->toString().c_str());
    }
*/

    QMessageBox::information(NULL,"Uniprot Looking","Uniprot Looking has finished successfully");
}

vector<string> Alignment::getConsRes(){
    vector<char> conservedaa;
    vector<int> conservedpos;

    this->CalculateFrequencies();

    for(int i = 0; i < frequencies.size()-2; i++){
        for(int j = 1; j <= 20; j++){
            float freq = frequencies[i][j]/((float)sequences.size());
            //printf("freq=%f / minCons=%f\n",freq,minCons);
            if(freq >= minCons){
                conservedaa.push_back(num2aa(j));
                conservedpos.push_back(i);
            }
        }
    }

    vector<string> outVec;

    for(int i = 0; i < conservedaa.size(); i++){
        string res = conservedaa[i] + QString::number(conservedpos[i]).toStdString();
        outVec.push_back(res);
    }

    return outVec;
}

vector<Uniprot *> Alignment::getAllResidueFeatures(string res){
    vector<Uniprot*> outVec;

    for(int i = 0; i < uniprotMined.size(); i++){
        for(int j = 0; j < uniprotMined[i]->countFeatures(); j++){
            Feature *f = uniprotMined[i]->getFeature(j);

            if(f->getAlignResidue() == res){
                //QMessageBox::information(NULL,"a","OK");
                Uniprot *entry = new Uniprot();
                entry->setDataset(uniprotMined[i]->getDataset());
                entry->setName(uniprotMined[i]->getName());
                entry->addFeature(f);
                outVec.push_back(entry);
            }
        }
    }

    return outVec;
}
