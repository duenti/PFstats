#include "alignment.h"
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QApplication>

Alignment::Alignment()
{
    refSeqName = "";
}

Alignment::Alignment(string path){
    this->filepath = path;
    this->GetFromFile();
    refSeqName = "";
}

Alignment::~Alignment()
{
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

vector<tuple<string,string,int> > Alignment::getCorrelationGraph(){
    return this->corrGraph;
}

void Alignment::addCorrRefSeq(string seq){
    this->corrRefSeqs.push_back(seq);
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
    return this->fullAlignment;
}

void Alignment::addFilterSequence(vector<string> align){
    this->filterSequences.push_back(align);
}

void Alignment::loadFullAlignment(){
    this->sequences.clear();
    this->sequencenames.clear();

    for(int i = 0; i < this->fullAlignment.size(); i++){
        sequences.push_back(this->fullSequences[i]);
        sequencenames.push_back(this->fullAlignment[i]);
    }
}

void Alignment::addParameter(string tag, string filter, int refSeq, int offset, char chain, string pdb){
    if(pdb == "") pdb = "0";
    string parameter = tag + "," + filter + "," + QString::number(refSeq).toStdString() + "," + QString::number(offset).toStdString() + "," + chain + "," + pdb;
    parameters.push_back(parameter);
    QMessageBox::information(NULL,"Add Conservation",QString::number(parameters.size()));
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
            out << "   <entry id='" << j-1 << "' offset='" << vecSplit[1].c_str() << "'>" << vecSplit[0].c_str() << "</entry>\n";
        }
        out << "</filter>\n";
    }

    out << "<conservation>\n";
    out << "   <parameters>\n";

    vector<string> consPars = this->getConservationParameters();

    if(consPars.size() >4){
        out << "      <filter>" << consPars[1].c_str() << "</filter>\n";
        out << "      <refseq>" << consPars[2].c_str() << "</refseq>\n";
        out << "      <offset>" << consPars[3].c_str() << "</offset>\n";
        out << "      <chain>" << consPars[4].c_str() << "</chain>\n";
    }

    out << "   </parameters>\n";

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

    out << "</conservation>\n";

    out << "<minss>\n";

    out << "   <parameters>\n";

    vector<string> minssParam = this->getMinssParameters();

    if(minssParam.size() > 2){
        out << "      <filter>" << minssParam[1].c_str() << "</filter>\n";
        out << "      <repetitions>" << minssParam[2].c_str() << "</repetitions>\n";
    }

    out << "   </parameters>\n";

    for(int i = 0; i < this->minssData.size(); i++){
        out << "   <data id='" << i+1 << "'>" << minssData[99-i] << "</data>\n";
    }

    out << "<\minss>\n";


    out << "<correlation>\n";
    out << "   <parameters>\n";

    vector<string> corrParam = this->getCorrelationParameters();

    if(corrParam.size() > 4){
        out << "      <filter>" << corrParam[1].c_str() << "</filter>\n";
        out << "      <minlog>" << corrParam[2].c_str() << "</minlog>\n";
        out << "      <minss>" << corrParam[3].c_str() << "</minss>\n";
        out << "      <deltafreq>" << corrParam[4].c_str() << "</deltafreq>\n";
    }

    out << "   </parameters>\n";

    out << "   <corrgraph>\n";

    for(int i = 0; i < corrGraph.size(); i++){
        string v1 = std::get<0>(corrGraph[i]);
        string v2 = std::get<1>(corrGraph[i]);
        int val = std::get<2>(corrGraph[i]);

        out << "      <edge v1='" << v1.c_str() << "' v2='" << v2.c_str() << "'>" << QString::number(val) << "</edge>\n";
    }

    out << "   </corrgraph>\n";

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


    out << "   <referecences>\n";

    for(int i = 0; i < corrRefSeqs.size(); i++)
        out << "      <protein>" << corrRefSeqs[i].c_str() << "</protein>\n";

    out << "   </references>\n";

    out << "   <output>\n";

    for(int i = 0; i < this->communityX.size(); i++){
        out << "      <community id='" << i + 1 << "'>\n";

        //Falta ALL
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

    out << "</correlation>\n";

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

    for(int i = 0; i < sequencenames.size(); i++){
        this->fullAlignment.push_back(sequencenames[i]);
        this->fullSequences.push_back(sequences[i]);
    }
}

bool Alignment::getFromStd(string text){
    //Implementar
}

vector<string> Alignment::getSequencesName(){
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

void Alignment::AlignmentTrimming(float minocc, int refseq, string refseqName, string newalignmentfilename){
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

    vector<string> filterVec;
    string parameters = QString::number(minocc).toStdString() + " 0 0 " + refseqName;
    filterVec.push_back(parameters);
    for(int i = 0; i < sequencenames.size(); i++){
        filterVec.push_back(sequencenames[i]);
    }

    vector<string> sequenceVec;
    sequenceVec.push_back(parameters);
    for(int i = 0; i < sequences.size(); i++){
        sequenceVec.push_back(sequences[i]);
    }

    filtersList.push_back(filterVec);
    filterSequences.push_back(sequenceVec);

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);

}

void Alignment::IdentityMinimum(float minid, int refseq, float minocc, string refSeqName, string newalignmentfilename){
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

    vector<string> filterVec;
    string parameters = QString::number(minocc).toStdString() + " " + QString::number(minid).toStdString() + " 0 " + refSeqName;
    filterVec.push_back(parameters);
    for(int i = 0; i < sequencenames.size(); i++){
        filterVec.push_back(sequencenames[i]);
    }

    vector<string> sequenceVec;
    sequenceVec.push_back(parameters);
    for(int i = 0; i < sequences.size(); i++){
        sequenceVec.push_back(sequences[i]);
    }

    filtersList.push_back(filterVec);
    filterSequences.push_back(sequenceVec);

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);
}

void Alignment::IdentityTrimming(float maxid, float minocc, float minid, int refseq, string refseqName, string newalignmentfilename){
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

    vector<string> filterVec;
    string parameters = QString::number(minocc).toStdString() + " " + QString::number(minid).toStdString() + " " + QString::number(maxid).toStdString() + " " + refseqName;
    filterVec.push_back(parameters);
    for(int i = 0; i < sequencenames.size(); i++){
        filterVec.push_back(sequencenames[i]);
    }

    vector<string> sequenceVec;
    sequenceVec.push_back(parameters);
    for(int i = 0; i < sequences.size(); i++){
        sequenceVec.push_back(sequences[i]);
    }

    filtersList.push_back(filterVec);
    filterSequences.push_back(sequenceVec);

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
        if(Ci>0) dGDT.push_back(sqrt(partialresult/((float) Ci)));
        else dGDT.push_back(0);
    }
}

vector<float> Alignment::DTRandomElimination(int repetitions, int max, int min, int step){
    int c1,c3;
    long double partialresult=0;
    long double partialsum=0;
    vector<int> SortOrder;
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

        for(c1=1;c1<=repetitions;c1++){
            random_shuffle(SortOrder.begin(),SortOrder.end());
            dGDTCalculation(currentsize);

            for (c3=0;c3<=populatedpos.size()-1;c3++)
                partialsum+=dGDT[populatedpos[c3]];
        }
        //printf("%f - %d\n",(float)partialsum,populatedpos.size());
        //out << 100-i << "\t" << (float)(partialsum/((long double)(populatedpos.size()*repetitions))) << "\n";
        outputVec.push_back((float)(partialsum/((long double)(populatedpos.size()*repetitions))));
    }
    //sucelimfile.close();

    for(int i = 0; i < outputVec.size(); i++){
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

    if(Communities[communitynumber].aa.size()>1)
        for (i=0;i<=Communities[communitynumber].aa.size()-1;i++){
            for(j=0;j<=Communities[communitynumber].aa.size()-1;j++){
                if(((Communities[communitynumber].aa[i]==sequences[seqnumber][Communities[communitynumber].pos[i]])&&(Communities[communitynumber].aa[j]==sequences[seqnumber][Communities[communitynumber].pos[j]]))&&(Communities[communitynumber].pos[i]!=Communities[communitynumber].pos[j]))
                    sum+=Singlepvalue(Communities[communitynumber].aa[i],Communities[communitynumber].pos[i],Communities[communitynumber].aa[j],Communities[communitynumber].pos[j]);
            }
        }
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
                if(!renumber) residue = aalist[j] + QString::number(poslist[j]+1).toStdString();
                else if (AlignNumbering2Sequence(seqnumber,poslist[j])!=0) residue = aalist[j] + QString::number(AlignNumbering2Sequence(seqnumber,poslist[j])+offset).toStdString();
                else residue = aalist[j] + "X(" + QString::number(poslist[j] + 1).toStdString() + ")";
                clustersResidues.push_back(residue);
            }
            residuesComm.push_back(clustersResidues);

            for(int j = 0; j < aalist.size(); j++){
                clusterXAll.push_back((float)100*frequencies[poslist[j]][freqmatrixposition(aalist[j])]/((float)sequences.size()));
            }

/*
            //printf("SCM SIZE = %d\n",selfcorrelationmatrix.size());
            for(int j = 0; j < selfcorrelationmatrix.size(); j++){
                //printf("i = %d, SIZE = %d\n", j, aalist.size());
                for(int k = 0; k < selfcorrelationmatrix[j].size(); k++){
                    printf(" %5.1f ",100 * selfcorrelationmatrix[j][k]);
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
