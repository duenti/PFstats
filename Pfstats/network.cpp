#include "network.h"

Network::Network()
{
    name = "unnamed";
    commPDBPath = "";
    min_score = 0;
    minss = 0;
    minDelta = 0;
    refseq = 1;

    c = new Colors();
}

Network::Network(vector<string> *seq, vector<string> *seqname){
    name = "unnamed";
    sequences = seq;
    sequencenames = seqname;
    commPDBPath = "";
    min_score = 0;
    minss = 0;
    minDelta = 0;
    refseq = 1;

    c = new Colors();
}

Network::Network(vector<string> *seq, vector<string> *seqname, int logp, float minssfrac, float delta){
    stringstream ss;
    ss << fixed << setprecision(2) << minssfrac;
    string strMinss = ss.str();
    ss.str(std::string());
    ss << fixed << setprecision(2) << delta;
    string strDelta = ss.str();
    name = to_string(logp) + "_" + strMinss + "_" + strDelta;
    sequences = seq;
    sequencenames = seqname;
    commPDBPath = "";
    min_score = logp;
    minss = minssfrac;
    minDelta = delta;
    refseq = 1;

    c = new Colors();
}

Network::Network(vector<string> *seq, vector<string> *seqname, Network *net){
    name = net->getName();
    frequencies = net->getFrequencies();
    corr_pdb = net->getPDB();
    min_score = net->getMinScore();
    minss = net->getMinssFraction();
    minDelta = net->getMinDelta();
    refseq = net->getRefSeq();
    commPDBPath = net->getCommPDBPath();
    corrGraph = net->getCorrelationGraph();
    comunidades = net->getComunidades();
    residuesComm = net->getResiduesComm();
    residuesCommPs = net->getResiduesCommPs();
    communityX = net->getCommunityX();
    communityXAll = net->getCommunityXAll();
    communityXps = net->getCommunityXPs();
    selfcorrelationmatrix = net->getSelfCorrelationMatrix();
    Deltas = net->getDeltas();
    sequences = seq;
    sequencenames = seqname;

    this->updateCommunitiesData();
    c = new Colors();
}

void Network::clear(){
    corr_pdb.clear();
    corr_pdb.shrink_to_fit();
    min_score = 0;
    minss = 0;
    minDelta = 0;
    refseq = 0;
    commPDBPath.clear();
    commPDBPath.shrink_to_fit();
    corrGraph.clear();
    corrGraph.shrink_to_fit();
    subalignmentseqs.clear();
    subalignmentseqs.shrink_to_fit();
    comunidades.clear();
    comunidades.shrink_to_fit();
    residuesComm.clear();
    residuesComm.shrink_to_fit();
    residuesCommPs.clear();
    residuesCommPs.shrink_to_fit();
    communityX.clear();
    communityX.shrink_to_fit();
    communityXAll.clear();
    communityXAll.shrink_to_fit();
    communityXps.clear();
    communityXps.shrink_to_fit();
    selfcorrelationmatrix.clear();
    selfcorrelationmatrix.shrink_to_fit();
    Deltas.clear();
    Deltas.shrink_to_fit();
    frequencies.clear();
    frequencies.shrink_to_fit();
    uniprotMined.clear();
    uniprotMined.shrink_to_fit();

}

string Network::getName(){
    return name;
}

void Network::setName(string n){
    name = n;
}

string Network::getPDB(){
    return this->corr_pdb;
}

void Network::setPDB(string pdb){
    this->corr_pdb = pdb;
}

int Network::getMinScore(){
    return this->min_score;
}

void Network::setMinScore(int value){
    this->min_score = value;
}

float Network::getMinssFraction(){
    return this->minss;
}

void Network::setMinssFraction(float value){
    this->minss = value;
}

float Network::getMinDelta(){
    return this->minDelta;
}

void Network::setMinDelta(float value){
    this->minDelta = value;
}

void Network::setRefSeq(string seq){
    unsigned int i = 0;

    for(i = 0; i < sequencenames->size(); i++){
        if(sequencenames->at(i) == seq) break;
    }

    this->refseq = i;
}

int Network::getRefSeq(){
    return refseq;
}

void Network::setCommPDBPath(string path){
    this->commPDBPath = path;
}

string Network::getCommPDBPath(){
    return this->commPDBPath;
}

vector<vector<int> > Network::getFrequencies(){
    return frequencies;
}

unsigned int Network::getCommListSize(){
    return this->comunidades.size();
}

unsigned int Network::getGraphSize(){
    return this->corrGraph.size();
}

tuple<string,string,int> Network::getGraphTuple(int i){
    return this->corrGraph[i];
}

vector<vector<string> > Network::getComunidades(){
    return comunidades;
}

vector<string> Network::getCommunitie(int i){
    return this->comunidades[i];
}

vector<string> Network::getResiduesComm(int c){
    return this->residuesComm[c];
}

vector<string> Network::getResiduesCommPs(int c){
    return this->residuesCommPs[c];
}

vector<float> Network::getCommAll(int c){
    return this->communityXAll[c];
}

vector<float> Network::getCommXRow(int c, int i){
    return this->communityX[c][i];
}

int Network::getCommXRowSize(int c){
    return communityX[c].size();
}

vector<int> Network::getCommPsRow(int c, int i){
    return this->communityXps[c][i];
}

int Network::getCommPsRowSize(int c){
    return communityXps[c].size();
}

long double Network::lnfact(int x){
    long double result=1.0;
    if ((x==0)||(x==1)) return(0.0);
    else for (int i=1;i<=x;i++) result=result*((long double)i);
    return (logl(result));
}

long double Network::stirling(int x){
    if(x<=8) return(lnfact(x));
    return ((((long double)x)+0.5)*logl((long double)x)-x+0.918938533205);
}

long double Network::lnbdf(int N, int nx, float px){
    if(N==nx) return ((long double)N*logl((long double)px));
    if(nx==0) return ((long double)N*logl((long double)(1.0-px)));
    return (stirling(N)-stirling(nx)-stirling(N-nx)+((long double)nx)*logl((long double)px)+((long double)(N-nx))*logl(1-(long double)(px)));
}

vector<vector<int> > Network::createBlankIntMatrix(int i1, int j1, int v){
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

long Network::eto10(long double x){
    return (x/((long double)2.30258509299));
}

long double Network::cbd_tietjen(int N, int n, float freq, bool right){
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

int Network::cbd(int N, int n, float freq, bool right){
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
        }

            for (int i=0;i<=n;i++){
                sum+=pow(10,lPs[i]-floor(minP));
        }
    }
    delete Ps;
    delete lPs;

    printf("P<10^%i\n",int(floor(logl(sum))+floor(minP)));
    return(int(floor(logl(sum))+floor(minP)));
}

unsigned int Network::freqmatrixposition(char c){
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

char Network::num2aa(int n){
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

bool Network::isaax(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
        (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y')||(c=='X'))
         return true;
    else return false;
}

vector<string> Network::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

Feature* Network::parseFeature(string feature){
    Feature *f = new Feature();

    if(feature[0] == ' ') feature = feature.substr(1);

    vector<string> vecFilter = split(feature,' ');

    f->setType("");
    if(vecFilter[0] == "ACT_SITE") f->setType("Active Site");
    else if(vecFilter[0] == "BINDING") f->setType("Binding Site");
    else if(vecFilter[0] == "CA_BIND") f->setType("Calcium Bind");
    else if(vecFilter[0] == "DNA_BIND") f->setType("DNA Bind");
    else if(vecFilter[0] == "METAL") f->setType("Metal Bind");
    else if(vecFilter[0] == "NP_BIND") f->setType("Nucleotide Bind");
    else if(vecFilter[0] == "SITE") f->setType("Site");
    else if(vecFilter[0] == "CROSSLNK") f->setType("Cross-Link");
    else if(vecFilter[0] == "DISULFID") f->setType("Disulfide Bond");
    else if(vecFilter[0] == "CARBOHYD") f->setType("Glycosylation");
    else if(vecFilter[0] == "LIPID") f->setType("Lipidation");
    else if(vecFilter[0] == "MOD_RES") f->setType("Modified Residue");

    if(f->getType() == "") return f;

    if(vecFilter[1] == vecFilter[2]) f->setPosition(atoi(vecFilter[2].c_str()));
    else{
        f->setBegin(atoi(vecFilter[1].c_str()));
        f->setEnd(atoi(vecFilter[2].c_str()));
    }

    string description = "";

    for(unsigned int i = 3; i < vecFilter.size(); i++)
        description += vecFilter[i] + " ";

    f->setDescription(description);

    return f;
}

unsigned int Network::GetOffsetFromSeqName(string seqname){
    bool found=false;
    string offsetstr;
    unsigned int c1=0;

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

unsigned int Network::AlignNumbering2Sequence2(int seqnumber, int position, vector<string> fullSequences){
    unsigned int c1;
    vector<int> referencevector;

    for(c1=0;c1<=fullSequences[0].size()-1;c1++)
        if(isaax(fullSequences[seqnumber-1][c1])) referencevector.push_back(c1);


    for(unsigned int c1=0;c1<=referencevector.size()-1;c1++)
        if (referencevector[c1]==position) return(c1+1);
    return 0;
}

int Network::seqname2seqint2(string refseqcode, vector<string> fullAlignment){
    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        vector<string> vecSplit = this->split(fullAlignment[i],'/');
        if(vecSplit[0] == refseqcode) return i;
    }
    return 0;
}

vector<int> Network::getRefSeqCodes(vector<string> fullAlignment, vector<string> refseqs){
    vector<int> codes;
    for(unsigned int i = 0; i < refseqs.size(); i++){
        codes.push_back(seqname2seqint2(refseqs[i],fullAlignment));
    }

    return codes;
}

void Network::CalculateFrequencies(){
    long double partialresult;
    unsigned int c1,c2;

    frequencies.clear();

    // FREQUENCE MATRIX INITIALIZATION
    for(c1=0;c1<=sequences->at(0).size();c1++){ // total positions: sequencesize + 1 (positions + totals)
        frequencies.push_back( vector<int>(21) );
        for(c2=0; c2<=20; c2++)
            frequencies[c1].push_back(0);
    }

    // INSERT AMINO ACID FREQUENCES ON EACH POSITION OF THE ALIGNMENT
    for(c1=0;c1<=sequences->size()-1;c1++){
        for(c2=0;c2<=sequences->at(0).size()-1;c2++){
            frequencies[c2][freqmatrixposition(sequences->at(c1)[c2])]++;
            frequencies[sequences->at(0).size()][freqmatrixposition(sequences->at(c1)[c2])]++;
        }
    }

    for (c1=1;c1<=20;c1++){
        partialresult=(long double)(frequencies[sequences->at(0).size()][c1]);
        partialresult=partialresult/((long double)((sequences->size()*sequences->at(0).size())-frequencies[sequences->at(0).size()][0]));
        //meanf[c1]=partialresult;
    }
}



void Network::SubAlignmentIndices(char aa, int pos){
    unsigned int c1;

    if(subalignmentseqs.size()>0) subalignmentseqs.clear();

    for (c1=0;c1<sequences->size();c1++)
        if(sequences->at(c1)[pos]==aa)
            subalignmentseqs.push_back(c1);
}

vector<int> Network::subalignmentIndicesW(char aa, int pos){
    vector<int> indices;

    for(unsigned int i = 0; i < sequences->size(); i++)
        if(sequences->at(i)[pos] == aa)
            indices.push_back(i);

    return indices;
}

int Network::Singlepvalue(char aa1, int pos1, char aa2, int pos2){
    unsigned int aa2pos2count=0;
    unsigned int c2;
    if(pos1==pos2) return 0;
    //this->CalculateFrequencies();
    SubAlignmentIndices(aa1,pos1);

    if (subalignmentseqs.size()>0){
        for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
            if (sequences->at(subalignmentseqs[c2])[pos2]==aa2) aa2pos2count++;

        if ((((float)aa2pos2count)/((float)subalignmentseqs.size()))!=((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences->size()))){
            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences->size())))
                return(-cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences->size())),true));
            else
                return(cbd(subalignmentseqs.size(),aa2pos2count,((float)frequencies[pos2][freqmatrixposition(aa2)])/(float(sequences->size())),false));
        }else return 0;
    }else return 0;
}

/*
void Network::SympvalueCalculation(int minlogp, float minssfraction, float mindeltafreq){
    int aa1,aa2,aa2pos2count,aa1pos1count;
    unsigned int c2,pos1,pos2;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();
    //FILE *temp;
    //temp = fopen("temppvalues.txt","w");

    QProgressDialog progress("Calculating correlations...(1/6)", "Abort", 0,sequences[0].size()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences[0].size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()){
            corrGraph.clear();
            return;
        }

        for (aa1=1;aa1<=20;aa1++){
            if(frequencies[pos1][aa1]>minssfraction*((float)sequences->size()))
                for(pos2=pos1+1;pos2<=sequences[0].size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        if(frequencies[pos2][aa2]>minssfraction*((float)sequences->size())){
                            QApplication::processEvents();

                            if(progress.wasCanceled()){
                                corrGraph.clear();
                                return;
                            }
                            SubAlignmentIndices(num2aa(aa1),pos1);
                            aa2pos2count=0;

                            for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                if (sequences->at(subalignmentseqs[c2])[pos2]==num2aa(aa2)) aa2pos2count++;

                            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][aa2])/(float(sequences->size()))){
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++){
                                        if (sequences->at(subalignmentseqs[c2])[pos1]==num2aa(aa1)) aa1pos1count++;
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
                                        if (sequences->at(subalignmentseqs[c2])[pos1]==num2aa(aa1)) aa1pos1count++;

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }
                            if(mindeltafreqok){
                                pvalue1=Singlepvalue(num2aa(aa1),pos1,num2aa(aa2),pos2);
                                pvalue2=Singlepvalue(num2aa(aa2),pos2,num2aa(aa1),pos1);
                                //fprintf(temp,"%c%d %c%d \n",num2aa(aa1),pos1,num2aa(aa2),pos2);
                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    //printf ("%c%d %c%d %i\n",num2aa(aa1),pos1+1,num2aa(aa2),pos2+1,(pvalue1+pvalue2)/2);
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    //printf("%s %s %d\n",residue1.c_str(),residue2.c_str(),edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }

    progress.close();
}
*/

void Network::SympvalueCalculation(int minlogp, float minssfraction, float mindeltafreq){
    int aa1,aa2,aa2pos2count,aa1pos1count;
    unsigned int c2,pos1,pos2;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();
    //FILE *temp;
    //temp = fopen("temppvalues.txt","w");

    QProgressDialog progress("Calculating correlations...(1/6)", "Abort", 0,sequences->at(0).size()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences->at(0).size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()){
            corrGraph.clear();
            return;
        }

        for (aa1=1;aa1<=20;aa1++){
            if(frequencies[pos1][aa1]>minssfraction*((float)sequences->size()))
                for(pos2=pos1+1;pos2<=sequences->at(0).size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        if(frequencies[pos2][aa2]>minssfraction*((float)sequences->size())){
                            QApplication::processEvents();

                            if(progress.wasCanceled()){
                                corrGraph.clear();
                                return;
                            }
                            SubAlignmentIndices(num2aa(aa1),pos1);
                            aa2pos2count=0;

                            for(c2=0;c2<=subalignmentseqs.size()-1;c2++)
                                if (sequences->at(subalignmentseqs[c2])[pos2]==num2aa(aa2)) aa2pos2count++;

                            if(((float)aa2pos2count)/((float)subalignmentseqs.size())>((float)frequencies[pos2][aa2])/(float(sequences->size()))){
                                if(((float)aa2pos2count)/((float)subalignmentseqs.size())>(1.0-mindeltafreq)){
                                    SubAlignmentIndices(num2aa(aa2),pos2);
                                    aa1pos1count=0;

                                    for(c2=0;c2<=subalignmentseqs.size()-1;c2++){
                                        if (sequences->at(subalignmentseqs[c2])[pos1]==num2aa(aa1)) aa1pos1count++;
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
                                        if (sequences->at(subalignmentseqs[c2])[pos1]==num2aa(aa1)) aa1pos1count++;

                                    if(((float)aa1pos1count)/((float)subalignmentseqs.size())<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }
                            if(mindeltafreqok){
                                pvalue1=Singlepvalue(num2aa(aa1),pos1,num2aa(aa2),pos2);
                                pvalue2=Singlepvalue(num2aa(aa2),pos2,num2aa(aa1),pos1);
                                //fprintf(temp,"%c%d %c%d \n",num2aa(aa1),pos1,num2aa(aa2),pos2);
                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    //printf ("%c%d %c%d %i\n",num2aa(aa1),pos1+1,num2aa(aa2),pos2+1,(pvalue1+pvalue2)/2);
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    //printf("%s %s %d\n",residue1.c_str(),residue2.c_str(),edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }

    progress.close();
}


void Network::henikoffpvalueCalculation(int minlogp, float minssfraction, float mindeltafreq, vector<float> weights){
    int aa1,aa2;
    unsigned int c2,pos1,pos2;
    short int pvalue1,pvalue2;
    bool mindeltafreqok;
    this->corrGraph.clear();

    QProgressDialog progress("Calculating correlations...(1/6)", "Abort", 0,sequences->at(0).size()-1);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (pos1=0;pos1<=sequences->at(0).size()-2;pos1++){
        progress.setValue(pos1);
        QApplication::processEvents();

        if(progress.wasCanceled()){
            corrGraph.clear();
            return;
        }

        for (aa1=1;aa1<=20;aa1++){
            vector<int> subalignmentseqs1 = subalignmentIndicesW(num2aa(aa1),pos1);
            float f0a1 = 0.0;

            for(unsigned int i = 0; i < subalignmentseqs1.size(); i++){
                f0a1 += weights[subalignmentseqs1[i]];
            }

            if(f0a1>minssfraction)
                for(pos2=pos1+1;pos2<=sequences->at(0).size()-1;pos2++){
                    for(aa2=1;aa2<=20;aa2++){
                        QApplication::processEvents();

                        if(progress.wasCanceled()){
                            corrGraph.clear();
                            return;
                        }
                        vector<int> subalignmentseqs2 = subalignmentIndicesW(num2aa(aa2),pos2);
                        float f0a2 = 0.0;

                        for(unsigned int i = 0; i < subalignmentseqs2.size(); i++){
                            f0a2 += weights[subalignmentseqs2[i]];
                        }

                        if(f0a2>minssfraction){
                            float f1a2 = 0.0;

                            for(c2=0;c2<=subalignmentseqs1.size()-1;c2++)
                                if (sequences->at(subalignmentseqs1[c2])[pos2]==num2aa(aa2)) f1a2 += weights[subalignmentseqs1[c2]];

                            f1a2 = f1a2/(float)f0a1;

                            float f1a1 = 0.0;
                            if(f1a2 > f0a2){
                                if(f1a2 > (1.0-mindeltafreq)){
                                    for(c2=0;c2<=subalignmentseqs2.size()-1;c2++){
                                        if (sequences->at(subalignmentseqs2[c2])[pos1]==num2aa(aa1)) f1a1 += weights[subalignmentseqs2[c2]];
                                    }

                                    f1a1 = f1a1/(float)f0a2;

                                    if(f1a1 > (1.0-mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }else{
                                if(f1a2<(mindeltafreq)){
                                    for(c2=0;c2<=subalignmentseqs2.size()-1;c2++){
                                        if (sequences->at(subalignmentseqs2[c2])[pos1]==num2aa(aa1)) f1a1 += weights[subalignmentseqs2[c2]];
                                    }

                                    f1a1 = f1a1/(float)f0a2;

                                    if(f1a1<(mindeltafreq))
                                        mindeltafreqok=true;
                                    else mindeltafreqok=false;
                                }else mindeltafreqok=false;
                            }

                            if(mindeltafreqok){
                                //P-Value1
                                if(f1a2 > f0a2){
                                    pvalue1 = -cbd(f0a1*sequences->size(),f1a2*f0a1*sequences->size(),f0a2,true);
                                }else if(f1a2 < f0a2){
                                    pvalue1 = cbd(f0a1*sequences->size(),f1a2*f0a1*sequences->size(),f0a2,false);
                                }else{
                                    pvalue1 = 0;
                                }
                                //P-Value 2
                                if(f1a1 > f0a1){
                                    pvalue2 = -cbd(f0a2*sequences->size(),f1a1*f0a2*sequences->size(),f0a1,true);
                                }else if(f1a1 < f0a1){
                                    pvalue2 = cbd(f0a2*sequences->size(),f1a1*f0a2*sequences->size(),f0a1,false);
                                }else{
                                    pvalue2 = 0;
                                }

                                if((abs((pvalue1+pvalue2)/2)>=minlogp)&&(abs(pvalue2)>=minlogp)&&(abs(pvalue2)>=minlogp)){
                                    //printf ("%c%d %c%d %i\n",num2aa(aa1),pos1+1,num2aa(aa2),pos2+1,(pvalue1+pvalue2)/2);
                                    string residue1 = num2aa(aa1) + QString::number(pos1+1).toStdString();
                                    string residue2 = num2aa(aa2) + QString::number(pos2+1).toStdString();
                                    int edgeValue = (pvalue1+pvalue2)/2;
                                    tuple<string,string,int> node(residue1,residue2,edgeValue);
                                    //printf("%s %s %d\n",residue1.c_str(),residue2.c_str(),edgeValue);
                                    this->corrGraph.push_back(node);
                                    //out << num2aa(aa1) << pos1+1 << " " << num2aa(aa2) << pos2+1 << " " << (pvalue1+pvalue2)/2 << "\n";
                                }
                            }
                        }
                    }
                }
        }
    }

    progress.close();
}

void Network::clearCommunity(){
    comunidades.clear();
}

void Network::resetCommunities(){
    if (Communities.size()>0){
        for (unsigned int c1=0;c1<=Communities.size()-1;c1++){
            Communities[c1].pos.clear();
            Communities[c1].aa.clear();
        }
        Communities.clear();
    }

    tempcommunity.pos.clear();
    tempcommunity.aa.clear();
}

tuple<string,string,int> Network::getCorrelationEdge(int i){
    return corrGraph[i];
}

unsigned int Network::getCorrelationGraphSize(){
    return corrGraph.size();
}

void Network::addCommunity(vector<string> comm){
    comunidades.push_back(comm);
}

void Network::addToCommunity(string res, int i){
    if(i < comunidades.size())
        comunidades[i].push_back(res);
    else
        printf("error adding %s to community %d\n",res.c_str(),i);
}

unsigned int Network::getDeltasSize(){
    return Deltas.size();
}

float Network::getDeltaValue(int i, int j){
    return Deltas[i][j];
}

void Network::addDeltaLine(vector<float> line){
    Deltas.push_back(line);
}

vector<vector<string> > Network::getResiduesComm(){
    return residuesComm;
}

vector<vector<string> > Network::getResiduesCommPs(){
    return residuesCommPs;
}

vector<vector<vector<float> > > Network::getCommunityX(){
    return communityX;
}

vector<vector<float> > Network::getCommunityXAll(){
    return communityXAll;
}

vector<vector<vector<int> > > Network::getCommunityXPs(){
    return communityXps;
}

vector<vector<float> > Network::getSelfCorrelationMatrix(){
    return selfcorrelationmatrix;
}

vector<vector<float> > Network::getDeltas(){
    return Deltas;
}

void Network::addCorrEdge(string v1, string v2, int score){
    tuple<string,string,int> node(v1,v2,score);

    this->corrGraph.push_back(node);
}

void Network::addResiduesComm(vector<string> residues){
    this->residuesComm.push_back(residues);
}

void Network::addCommXAll(vector<float> resAll){
    this->communityXAll.push_back(resAll);
}

void Network::addCommX(vector<vector<float> > commX){
    this->communityX.push_back(commX);
}

void Network::addResiduesCommPs(vector<string> residuesPs){
    this->residuesCommPs.push_back(residuesPs);
}

void Network::addCommXPs(vector<vector<int> > commXPs){
    this->communityXps.push_back(commXPs);
}

void Network::updateCommunitiesData(){
    Communities.clear();
    tempcommunity.pos.clear();
    tempcommunity.aa.clear();

    for(unsigned int i = 0; i < comunidades.size(); i++){
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
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

string Network::getResidueColor(string residue){
    for(unsigned int i = 0; i < comunidades.size(); i++){
        if(comunidades[i].size() > 1){
            for(unsigned int j = 0; j < comunidades[i].size(); j++){
                if(comunidades[i][j] == residue) return c->getColor(i);
            }
        }else return "";
    }

    return "";
}

void Network::getCommunitiesFromRAM(){
    QProgressDialog progress("Getting communities...(3/6)", "Abort", 0,comunidades.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    this->resetCommunities();

    for(unsigned int i = 0; i < comunidades.size(); i++){
        QApplication::processEvents(  );
        progress.setValue(i);
        if(progress.wasCanceled()) return;
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            QApplication::processEvents(  );
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

    progress.close();
}

void Network::Cluster2SCMFromRAM(bool renumber, int seqnumber, int offset){
    QProgressDialog progress("Calculating tables...(4/6)", "Abort", 0,comunidades.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    int nclusters = comunidades.size();
    vector<char> aalist;
    vector<int> poslist;
    this->communityX.clear();
    this->communityXAll.clear();
    this->residuesComm.clear();

    for(int i = 0; i < nclusters; i++){
        progress.setValue(i);
        if(progress.wasCanceled()) return;
        QApplication::processEvents(  );
        aalist.clear();
        poslist.clear();
        vector<float> clusterXAll;

        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            if(progress.wasCanceled()) return;
            QApplication::processEvents(  );
            string temp = comunidades[i][j];
            aalist.push_back(temp[0]);
            poslist.push_back(atoi(temp.substr(1).c_str())-1);
        }

        if(comunidades[i].size() > 1){
            SelfCorrelationMatrixCalculation(aalist,poslist);

            //ESCRITA SCM2HTML*RAM
            vector<string> clustersResidues;
            for(unsigned int j = 0; j < aalist.size(); j++){
                if(progress.wasCanceled()) return;
                QApplication::processEvents(  );
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

            for(unsigned int j = 0; j < aalist.size(); j++){
                if(progress.wasCanceled()) return;
                QApplication::processEvents(  );
                clusterXAll.push_back((float)100*frequencies[poslist[j]][freqmatrixposition(aalist[j])]/((float)sequences->size()));
            }

            this->communityX.push_back(selfcorrelationmatrix);
            this->communityXAll.push_back(clusterXAll);
        }
    }

    progress.close();
}

int Network::getEdge(string v1, string v2){
    for(unsigned int i = 0; i < corrGraph.size(); i++){
        string gv1 = get<0>(corrGraph[i]);
        string gv2 = get<1>(corrGraph[i]);
        if((v1==gv1 && v2 == gv2) || (v1==gv2 && v2==gv1)){
            return get<2>(corrGraph[i]);
        }
    }
    return 0;
}

void Network::DeltaCommunitiesCalculation(){
    QProgressDialog progress("Calculating Deltas...(5/6)", "Abort", 0,comunidades.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    Deltas.clear();

    for(unsigned int i = 0; i < this->comunidades.size(); i++){
        vector<float> vec;
        for(unsigned int j = 0; j < this->comunidades.size(); j++){
            vec.push_back(0);
        }
        Deltas.push_back(vec);
    }

    if(comunidades.size() > 0){
        for(unsigned int i = 0; i < this->comunidades.size()-1; i++){
            progress.setValue(i);
            if(progress.wasCanceled()) return;
            QApplication::processEvents();
            for(unsigned int j = i+1; j < this->comunidades.size(); j++){
                if(progress.wasCanceled()) return;
                QApplication::processEvents();
                vector<string> commA = comunidades[i];
                vector<string> commB = comunidades[j];
                float N = commA.size();
                float M = commB.size();
                float sumW = 0;

                for(unsigned int k = 0; k < commA.size(); k++){
                    for(unsigned int l = 0; l < commB.size(); l++){
                        if(progress.wasCanceled()) return;
                        QApplication::processEvents(  );
                        string an = commA[k];
                        string bm = commB[l];
                        int pvalue = getEdge(an,bm);
                        if(pvalue != 0){
                            sumW += pvalue;
                        }
                    }
                }

                Deltas[i][j] = sumW/(N*M);
            }
        }
    }
    progress.close();
}

/*
void Network::DeltaCommunitiesCalculation(){
    float Delta;
    int c1,c2,c3,c4;
    QProgressDialog progress("Calculating Deltas...(5/6)", "Abort", 0,Communities.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();


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
            progress.setValue(c1);
            if(progress.wasCanceled()) return;
            QApplication::processEvents(  );
            for(c2=0;c2<=Communities.size()-1;c2++){
                Delta=0;
                for(c3=0;c3<=Communities[c1].aa.size()-1;c3++){
                    QApplication::processEvents(  );
                    for(c4=0;c4<=Communities[c2].aa.size()-1;c4++){
                        Delta+=(float)Singlepvalue(Communities[c1].aa[c3],Communities[c1].pos[c3],Communities[c2].aa[c4],Communities[c2].pos[c4]);
                    }
                }
                Deltas[c1][c2]=((float)Delta)/((float)(Communities[c1].aa.size()*Communities[c2].aa.size()));
            }
        }
    }

    progress.close();
}
*/
void Network::pMatrix2HTMLRAM(bool renumber, int seqnumber){
    this->communityXps.clear();
    this->residuesCommPs.clear();
    QProgressDialog progress("Generating p-values matrixes..(6/6)", "Abort", 0,Communities.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(unsigned int c1 = 0; c1 < Communities.size(); c1++){
        progress.setValue(c1);
        if(progress.wasCanceled()) return;
        QApplication::processEvents(  );
        if(Communities[c1].aa.size() > 1){

            vector<vector<int> > matrix = this->createBlankIntMatrix(Communities[c1].aa.size(),Communities[c1].aa.size(),-1);
            vector<string> clustersResidues;
            for(unsigned int j = 0; j < Communities[c1].aa.size(); j++){
                QApplication::processEvents(  );
                string residue;
                if(!renumber) residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                else if(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j]) != 0) residue = Communities[c1].aa[j] + QString::number(AlignNumbering2Sequence(seqnumber,Communities[c1].pos[j])).toStdString();
                else residue = Communities[c1].aa[j] + QString::number(Communities[c1].pos[j]+1).toStdString();
                clustersResidues.push_back(residue);
            }
            residuesCommPs.push_back(clustersResidues);

            for(unsigned int i = 0; i < Communities[c1].aa.size(); i++){
                QApplication::processEvents(  );
                for(unsigned int j = 0; j < Communities[c1].aa.size(); j++){
                    if(i != j){
                        matrix[i][j] = Singlepvalue(Communities[c1].aa[i],Communities[c1].pos[i],Communities[c1].aa[j],Communities[c1].pos[j]);
                    }
                }
            }

            this->communityXps.push_back(matrix);
        }
    }

    progress.close();
}

unsigned int Network::getNumOfUtilComms(){
    return this->communityX.size();
}

vector<tuple<int, float> > Network::createCommuntitiesVector(){
    vector<tuple<int,float> > commvec;
    int nOfComms = this->getNumOfUtilComms();

    for(unsigned int i = 0; i < nOfComms; i++){
        for(unsigned int j = 0; j < comunidades[i].size(); j++){
            int commpos = atoi(comunidades[i][j].substr(1).c_str());
            tuple<int,float> tup;
            get<0>(tup) = commpos;
            get<1>(tup) = (float)(i+1)/(float)nOfComms;
            commvec.push_back(tup);
        }
    }

    return commvec;
}


void Network::SelfCorrelationMatrixCalculation(const std::vector<char> &aalist, const std::vector<int> &poslist){
    unsigned int i, j;

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
            if(i==j) selfcorrelationmatrix[i][j]=-1;
            else{
                selfcorrelationmatrix[i][j]=((float)SubAlignmentFrequency(aalist[i],poslist[i],subalignmentseqs))/((float)subalignmentseqs.size());            }
        }
    }
}

float Network::PSA(int seqnumber, int communitynumber){
    unsigned int i,j;
    float sum=0;

    //QMessageBox::information(NULL,"a",QString::number(sequences->size()));

    if(Communities[communitynumber].aa.size()>1)
        for (i=0;i<=Communities[communitynumber].aa.size()-1;i++){
            for(j=0;j<=Communities[communitynumber].aa.size()-1;j++){
                if(((Communities[communitynumber].aa[i]==sequences->at(seqnumber)[Communities[communitynumber].pos[i]])&&(Communities[communitynumber].aa[j]==sequences->at(seqnumber)[Communities[communitynumber].pos[j]]))&&(Communities[communitynumber].pos[i]!=Communities[communitynumber].pos[j])){
                    //QMessageBox::information(NULL,"a","OK");
                    sum+=Singlepvalue(Communities[communitynumber].aa[i],Communities[communitynumber].pos[i],Communities[communitynumber].aa[j],Communities[communitynumber].pos[j]);
                    //QMessageBox::information(NULL,"a","OK");
                }
            }
        }
    //QMessageBox::information(NULL,"a","FIM PSA");
    return(sum/(float)(Communities[communitynumber].aa.size()*(Communities[communitynumber].aa.size()-1)));
}

vector<tuple<string,string,int> > Network::getCorrelationGraph(){
    return this->corrGraph;
}

set<string> Network::getCorrelationNodes(){
    set<string> nodes;

    for(unsigned int i = 0; i < this->corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        nodes.insert(std::get<0>(tupCorr).c_str());
        nodes.insert(std::get<1>(tupCorr).c_str());
    }

    return nodes;
}

map<string,int> Network::getNodesHubs(){
    map<string,int> hubs;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];
        string n1 = get<0>(tupCorr);
        string n2 = get<1>(tupCorr);

        if(hubs.find(n1) == hubs.end()){
            hubs[n1] = 1;
        }else{
            hubs[n1] += 1;
        }
        if(hubs.find(n2) == hubs.end()){
            hubs[n2] = 1;
        }else{
            hubs[n2] += 1;
        }
    }

    return hubs;
}

set<string> Network::getPositiveCorrelationNodes(){
    set<string> nodes;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        if(std::get<2>(tupCorr) > 0){
            nodes.insert(std::get<0>(tupCorr).c_str());
            nodes.insert(std::get<1>(tupCorr).c_str());
        }
    }

    return nodes;
}

map<string,int> Network::getPositiveNodeHubs(){
    map<string,int> hubs;

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> tupCorr = corrGraph[i];

        if(get<2>(tupCorr) > 0){
            string n1 = get<0>(tupCorr);
            string n2 = get<1>(tupCorr);

            if(hubs.find(n1) == hubs.end()){
                hubs[n1] = 1;
            }else{
                hubs[n1] += 1;
            }
            if(hubs.find(n2) == hubs.end()){
                hubs[n2] = 1;
            }else{
                hubs[n2] += 1;
            }
        }
    }

    return hubs;
}

vector<tuple<string,string,int> > Network::getEdgesByComm(int comm){
    vector<tuple<string,string,int> > graph;
    vector<string> residues = comunidades[comm];

    for(unsigned int i = 0; i < corrGraph.size(); i++){
        tuple<string,string,int> edge = corrGraph[i];
        bool ok = false;

        for(unsigned int j = 0; j < residues.size(); j++){
            if(std::get<0>(edge) == residues[j]){
                for(unsigned int k = 0; k < residues.size(); k++){
                    if(std::get<1>(edge) == residues[k])
                        ok = true;
                }
            }
        }

        if(ok) graph.push_back(edge);
    }

    return graph;
}

vector<tuple<string,string,float> > Network::getDeltasEdges(float cutoff){
    vector<tuple<string,string,float> > graph;

    for(unsigned int i = 0; i < this->comunidades.size(); i++){
        for(unsigned int j = 0; j < this->comunidades.size(); j++){
            if(i!=j){
                if((Deltas[i][j] > 0 && Deltas[i][j] > cutoff) || (Deltas[i][j] < 0 && Deltas[i][j] < (-1*cutoff))){
                    string c1 = "";
                    string c2 = "";
                    if(comunidades[i].size() > 1)
                        c1 = "Comm" + std::to_string(i+1);
                    else
                        c1 = comunidades[i][0];
                    if(comunidades[j].size() > 1)
                        c2 = "Comm" + std::to_string(j+1);
                    else
                        c2 = comunidades[j][0];

                    tuple<string,string,float> edge (c1,c2,Deltas[i][j]);
                    if(c1.substr(0,2) == "Co" || c2.substr(0,2) == "Co")
                        graph.push_back(edge);
                    //printf("%s\t%s\t%f\n",c1.c_str(),c2.c_str(),Deltas[i][j]);
                }
            }
        }
    }

    //Verifica as correlaçoes inversas e mantem a maior
    for(unsigned int i = 0; i < graph.size(); i++){
        tuple<string,string,float> edge = graph[i];
        string c1 = std::get<0>(edge);
        string c2 = std::get<1>(edge);
        float weight1 = std::get<2>(edge);
        float weight2 = 0;
        bool ok = false;
        int j = 0;

        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,float> edge2 = graph[j];
            if(c1 == std::get<1>(edge2) && std::get<0>(edge2) == c2){
                ok = true;
                weight2 = std::get<2>(edge2);
                break;
            }
        }

        if(ok){
            if(fabs(weight1) >= fabs(weight2)){
                graph.erase(graph.begin()+j);

                if(i > 0) i--;
            }
        }
    }

    return graph;
}

void Network::removeItemOfCommunity(int comm, int item){
    comunidades[comm].erase(comunidades[comm].begin() + item);
}

void Network::addItemToCommunity(string res, int commindex){
    comunidades[commindex].push_back(res);
}

void Network::setCommunityItems(int comm, vector<string> residues){
    comunidades[comm] = residues;
}

void Network::sortCommunitiesVector(){
    sort(comunidades.begin(),comunidades.end(),
         [](const std::vector<string>& a, const std::vector<string>& b) {
        return a.size() > b.size();
    });
}

vector<int> Network::CalculateReferenceVector(int seqnumber){
    vector<int> referencevector;
    //referencesequence=seqnumber;

    for(unsigned int c1=0;c1<sequences->at(0).size();c1++)
        if(isaax(sequences->at(seqnumber-1)[c1])) referencevector.push_back(c1);
}

unsigned int Network::AlignNumbering2Sequence(int seqnumber, int position){
    //printf("PARS %d %d\n",seqnumber,position);
    vector<int> referencevector = this->CalculateReferenceVector(seqnumber);
    for(unsigned int c1=0;c1<=referencevector.size()-1;c1++)
        if (referencevector[c1]==position) return(c1+1);
    return 0;
}

int Network::SubAlignmentFrequency(char aa, int pos, vector<int> subalignmentseqs){
    unsigned int c1;
    unsigned int result = 0;

    if(subalignmentseqs.size()==0) return -1;

    for(c1=0;c1<=subalignmentseqs.size()-1;c1++)
        if(sequences->at(subalignmentseqs[c1])[pos]==aa) result++;

    return result;
}

void Network::alignment2UpperCase(){
    for(unsigned int i = 0; i < sequences->size(); i++){
        string sequenceI = sequences->at(i);
        std::transform(sequenceI.begin(),sequenceI.end(),sequenceI.begin(),::toupper);
        sequences->at(i) = sequenceI;
        //printf("%s - %s\n",sequenceI.c_str(),sequences[i].c_str());
    }
}

bool Network::uniprotLook(bool cons, bool comms, vector<string> proteins, vector<int> idproteins, vector<string> conserved, vector<string> fullAlignment, vector<string> fullSequences, bool hasproxy, QNetworkProxy proxy){
    string url = "";
    QProgressDialog progress("Reading data from webservice (1/3)","Abort",0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    vector<Uniprot*> dataprot;
    if(proteins[0].find("_") != std::string::npos)
        url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/uniprot/look/";
    else
        url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/uniprot/look2/";
    string post_content = "";

    //Monta a string POST
    for(unsigned int i = 0; i < proteins.size(); i++){
        post_content += split(proteins[i],'.')[0] + "\n";
    }

    QByteArray const data = QString::fromStdString(post_content).toUtf8();
    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    if(hasproxy) manager.setProxy(proxy);
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString result = response->readAll();
    //printf("%s",result.toStdString().c_str());

    if(result == ""){
        string msg = "The query returned a null content. It may be caused by one of the following cases:\n";
        msg += "-You are having problems with your internet connection.\n";
        msg += "-Our servers are down. You can check it by accessing www.biocomp.icb.ufmg.br";
        QMessageBox::information(NULL,"Null result",msg.c_str());
        return false;
    }

    vector<string> lines = split(result.toStdString(),'\n');

    progress.setLabelText("Parsing UniprotKb data (2/3)");
    progress.setValue(0);
    progress.setMaximum(lines.size()+1);

    //Percorre linhas de proteínas
    for(unsigned int i = 0; i < lines.size(); i++){
        if(progress.wasCanceled()) return false;
        progress.setValue(i);

        vector<string> featVec = split(lines[i],'\t');
        if(featVec.size() > 2){
            string function = "";
            if(featVec[1].substr(0,11) == " FUNCTION: ") function = featVec[1].substr(11);
            else if(featVec[1].substr(0,10) == "FUNCTION: ") function = featVec[1].substr(10);
            else function = featVec[1];
            Uniprot *unientry = new Uniprot(featVec[0],function);

            //Percorre cada tipo de feature de um grupo
            for(unsigned int j = 2; j < featVec.size(); j++){
                string kindOfFeature = featVec[j];
                //printf("%s\n",kindOfFeature.c_str());

                if(kindOfFeature != "null" && kindOfFeature != " "){
                    vector<string> featVec2 = split(kindOfFeature,';');

                    for(unsigned int k = 0; k < featVec2.size(); k++){
                        Feature* f = this->parseFeature(featVec2[k]);

                        if(f->getType() != "")
                            unientry->addFeature(f);
                    }
                }
            }

            dataprot.push_back(unientry);
        }
    }


    //QMessageBox::information(NULL,"A","PRIMERA PARTE OK");
    //SEGUNDA PARTE => TRABALHAR OS DADOS OBTIDOS
    progress.setLabelText("Looking for matchs (3/3)");
    progress.setValue(0);
    progress.setMaximum(dataprot.size());

    uniprotMined.clear();

    for(unsigned int i = 0; i < dataprot.size(); i++){
        progress.setValue(i);
        Uniprot *entry = new Uniprot(*dataprot[i]);
        Uniprot *out = new Uniprot();
        out->setName(entry->getName());
        //printf("FUNCTION: %s\n",entry->getFunction().c_str());
        out->setFunction(entry->getFunction());

        if(progress.wasCanceled()) return false;

        //printf("%s\n",entry->toString().c_str());

        for(int j = 0; j < entry->countFeatures(); j++){
            Feature *f = entry->getFeature(j);
            //printf("%s\n",f->toString().c_str());

            if(cons){
                for(unsigned int k = 0; k < conserved.size(); k++){
                    string respos = conserved[k];
                    char aa = respos[0];
                    int alignPos = stoi(respos.substr(1));
                    int pos = AlignNumbering2Sequence2(idproteins[i]+1,alignPos,fullSequences) + GetOffsetFromSeqName(fullAlignment[idproteins[i]]);
                    if(pos > 0){
                        string newResPos = fullSequences[idproteins[i]][alignPos-1] + to_string(pos);
                        string newAlignPos = aa + to_string(alignPos);

                        if(f->getType() == "Disulfide Bond"){
                            if(pos == f->getPosition() || pos == f->getBegin() || pos == f->getEnd()){
                                Feature *f1 = new Feature();
                                f1->setAggregation(0);
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
                        }else{
                            if(pos == f->getPosition() || (pos >= f->getBegin() && pos <= f->getEnd())){
                                Feature *f1 = new Feature();
                                f1->setAggregation(0);
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

            if(comms){
                for(unsigned int k = 0; k < comunidades.size(); k++){
                    for(unsigned int l = 0; l < comunidades[k].size(); l++){
                        string respos = comunidades[k][l];
                        char aa = respos[0];
                        int alignPos = stoi(respos.substr(1));
                        int pos = AlignNumbering2Sequence2(idproteins[i]+1,alignPos-1,fullSequences) + GetOffsetFromSeqName(fullAlignment[idproteins[i]]);
                        if( pos > 0){
                            string newResPos = fullSequences[idproteins[i]][alignPos-1] + QString::number(pos).toStdString();
                            string newAlignPos = aa + to_string(alignPos);
                            printf("SEQUENCE: %s - ALIGNN: %s - SEQN: %s\n",fullAlignment[idproteins[i]].c_str(),newAlignPos.c_str(),newResPos.c_str());

                            //printf("POS: %d   -   %d  %d-%d\n",pos,f->getPosition(),f->getBegin(),f->getEnd());
                            if(f->getType() == "Disulfide Bond"){
                                if(pos == f->getPosition() || pos == f->getBegin() || pos == f->getEnd()){
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
                            }else{
                                if(pos == f->getPosition() || (pos >= f->getBegin() && pos <= f->getEnd())){
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
            }
            f->kill();
        }
        entry->kill();
        uniprotMined.push_back(out);
    }
    progress.close();

    QMessageBox::information(NULL,"Uniprot Looking","Uniprot Looking has finished successfully");
    return true;
}

unsigned int Network::getUniprotMinedSize(){
    return uniprotMined.size();
}

string Network::getUniprotEntryName(int i){
    return uniprotMined[i]->getName();
}

unsigned int Network::getUniprotEntryNofFeatures(int i){
    return uniprotMined[i]->countFeatures();
}

Uniprot* Network::getUniprotEntry(int i){
    return uniprotMined[i];
}

void Network::addUniprotEntry(Uniprot *u){
    uniprotMined.push_back(u);
}

int Network::getResidueFeaturesByCommCount(string res){
    int total = 0;

    for(unsigned int i = 0; i < uniprotMined.size(); i++){
        for(int j = 0; j < uniprotMined[i]->countFeatures(); j++){
            Feature *f = uniprotMined[i]->getFeature(j);

            if(f->getAlignResidue() == res) total ++;
        }
    }

    return total;
}

vector<Uniprot *> Network::getAllResidueFeatures(string res){
    vector<Uniprot*> outVec;

    for(unsigned int i = 0; i < uniprotMined.size(); i++){
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

string Network::getUniprotFunction(int i){
    return uniprotMined[i]->getFunction();
}

Feature* Network::getUniprotFeature(int i, int j){
    return uniprotMined[i]->getFeature(j);
}

void Network::exportCorrGraph(QString filename, int type){
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

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
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

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
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

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<correlation>\n";
            out << "\t\t<parameters>\n";

            out << "\t\t\t<refseq>" << sequencenames->at(refseq-1).c_str() << "</refseq>\n";
            out << "\t\t\t<minScore>" << QString::number(min_score) << "</minScore>\n";
            out << "\t\t\t<minss>" << QString::number(minss) << "</minss>\n";
            out << "\t\t\t<delta>" << QString::number(minDelta) << "</delta>\n";

            out << "\t\t</parameters>\n";

            out << "\t\t<graph>\n";

            for(unsigned int i = 0; i < this->corrGraph.size(); i++){
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

void Network::exportCommNet(QString filename, int type){
    vector<tuple<string,string,float> > graph = this->getDeltasEdges(0);

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

            for(unsigned int i = 0; i < graph.size(); i++){
                tuple<string,string,int> tupCorr = graph[i];

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

            for(unsigned int i = 0; i < graph.size(); i++){
                tuple<string,string,int> tupCorr = graph[i];

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

            out << "<?xml version=\"1.0\"?>\n";
            out << "<PFStats>\n";

            out << "\t<correlation>\n";
            out << "\t\t<parameters>\n";

            out << "\t\t\t<refseq>" << sequencenames->at(refseq-1).c_str() << "</refseq>\n";
            out << "\t\t\t<minScore>" << QString::number(min_score) << "</minScore>\n";
            out << "\t\t\t<minss>" << QString::number(minss) << "</minss>\n";
            out << "\t\t\t<delta>" << QString::number(minDelta) << "</delta>\n";

            out << "\t\t</parameters>\n";

            out << "\t\t<graph>\n";

            for(unsigned int i = 0; i < graph.size(); i++){
                tuple<string,string,int> tupCorr = graph[i];

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

void Network::exportCommList(QString filename, int type){
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

            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << comunidades[i].size() << " nodes in community " << i+1 << "\n";
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
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

            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << "\t\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < comunidades[i].size(); j++){
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

void Network::exportCorrTable(QString filename, int type, bool perc){
    if(perc){
        switch(type){
            case 0:
            {
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
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
                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << residuesComm[i][j].c_str() << " " << QString::number(communityXAll[i][j],'f',2) << " ";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
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

                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    out << "<column>ALL</column>\n";
                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << "<column>" << residuesComm[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" c0=\"" << QString::number(communityXAll[i][j],'f',2) << "\" ";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == -1)
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
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
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

                    for(unsigned int j = 0; j < residuesComm[i].size(); j++){
                        out << "<th>" << residuesComm[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(unsigned int j = 0; j < communityX[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesComm[i][j].c_str() << "</b></td>\n";
                        out << "<td>" << QString::number(communityXAll[i][j],'f',1) << "</td>\n";

                        for(unsigned int k = 0; k < communityX[i][j].size(); k++){
                            if (communityX[i][j][k] == -1)
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
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    //QMessageBox::information(NULL,"OK","Teste");
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
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

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";
                    }
                    out << "\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << residuesCommPs[i][j].c_str() << " ";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
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

                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    out << "\t<community id=\"" << i+1 << "\">\n";
                    out << "\t\t<table>\n";

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<column>" << residuesCommPs[i][j].c_str() << "</column>\n";
                    }

                    out << "\t\t</table>\n";

                    out << "\t\t<table_data>\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << "\t\t\t<row id=\"" << j << "\" ";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == -1)
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
                for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                    vector<string> tempFN = split(filename.toStdString(),'.');
                    string path = "";
                    if(tempFN.size() == 1) path = tempFN[0];
                    else{
                        for(unsigned int j = 0; j < tempFN.size()-1; j++){
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

                    for(unsigned int j = 0; j < residuesCommPs[i].size(); j++){
                        out << "<th>" << residuesCommPs[i][j].c_str() << "</th>\n";
                    }

                    out << "</tr>\n";

                    for(unsigned int j = 0; j < communityXps[i].size(); j++){
                        out << "<tr>\n<td><b>" << residuesCommPs[i][j].c_str() << "</b></td>\n";

                        for(unsigned int k = 0; k < communityXps[i][j].size(); k++){
                            if (communityXps[i][j][k] == -1)
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

void Network::exportAdh(QString filename, int type){
    this->CalculateFrequencies();
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
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "Comm" << i+1 << " (" << residuesComm[i].size() << ")\t";
            }
            out << "\n";

            for(unsigned int i = 0; i < sequences->size()-1; i++){
                out << sequencenames->at(i).c_str() << "\t";

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
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

            for(unsigned int i = 0; i < sequences->size()-1; i++){
                out << sequencenames->at(i).c_str();

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
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

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                if(Communities[i].aa.size() > 1){
                    out << "\t<community id=\"" << i+1 << "\">\n";

                    for(unsigned int j = 0; j < sequences->size()-1; j++){
                        float psa = this->PSA(j,i);

                        out << "\t\t<protein value=\"" << QString::number(psa,'f',6) << "\">" << sequencenames->at(j).c_str() << "</protein>\n";
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

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "<th>Comm" << i+1 << " (" << residuesComm[i].size() << ")</th>\n";
            }
            out << "</tr>\n";

            for(unsigned int i = 0; i < sequences->size()-1; i++){
                out << "<tr>\n<td><b>" << sequencenames->at(i).c_str() << "</b></td>\n";

                for(unsigned int j = 0; j < this->getNumOfUtilComms(); j++){
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

void Network::exportResComm(QString filename, int type, vector<string> fullAlignment, vector<string> fullSequences, vector<int> refCodes){
    switch(type){
        case 0:
        {
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(unsigned int j = 0; j < tempFN.size()-1; j++){
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

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t" << textCab.c_str();
                }
                out << "\n";

                for(unsigned int j = 0; j < refCodes.size(); j++){
                    out << fullAlignment[refCodes[j]].c_str();

                    for(unsigned int k = 0; k < Communities[i].pos.size(); k++){
                        if(fullSequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                            out << "\t" << textItem.c_str();
                        }else{
                            if(fullSequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "\t - ";
                            else{
                                string textItem = fullSequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

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

            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "\t\t<residue alignNumber=\"" << textCab.c_str() << "\">\n";


                    for(unsigned int k = 0; k < refCodes.size(); k++){
                        if(fullSequences[refCodes[k]][Communities[i].pos[j]] == Communities[i].aa[j]){
                            string textItem = Communities[i].aa[j] + QString::number(AlignNumbering2Sequence2(refCodes[k]+1,Communities[i].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"true\">" << fullAlignment[refCodes[k]].c_str() << "</sequence>\n";
                        }else if(fullSequences[refCodes[k]][Communities[i].pos[j]] != '-'){
                            string textItem = fullSequences[refCodes[k]][Communities[i].pos[j]] + QString::number(AlignNumbering2Sequence2(refCodes[k]+1,Communities[i].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[k]])).toStdString();

                            out << "\t\t\t<sequence seqNumber=\"" << textItem.c_str() << "\" match=\"false\">" << fullAlignment[refCodes[k]].c_str() << "</sequence>\n";
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
            for(unsigned int i = 0; i < this->getNumOfUtilComms(); i++){
                vector<string> tempFN = split(filename.toStdString(),'.');
                string path = "";
                if(tempFN.size() == 1) path = tempFN[0];
                else{
                    for(unsigned int j = 0; j < tempFN.size()-1; j++){
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

                for(unsigned int j = 0; j < Communities[i].pos.size(); j++){
                    string textCab = Communities[i].aa[j] + QString::number(Communities[i].pos[j]+1).toStdString();
                    out << "<th>" << textCab.c_str() << "</th>\n";
                }
                out << "</tr>\n";

                for(unsigned int j = 0; j < refCodes.size(); j++){
                    out << "<tr>\n<td><b>" << fullAlignment[refCodes[j]].c_str() << "</b></td>\n";

                    for(unsigned int k = 0; k < Communities[i].pos.size(); k++){
                        if(fullSequences[refCodes[j]][Communities[i].pos[k]] == Communities[i].aa[k]){
                            string textItem = Communities[i].aa[k] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

                            out << "<td><b><font color=#00FF00>" << textItem.c_str() << "</font></b></td>\n";
                        }else{
                            if(fullSequences[refCodes[j]][Communities[i].pos[k]] == '-')
                                out << "<td><center>-</center></td>\n";
                            else{
                                string textItem = fullSequences[refCodes[j]][Communities[i].pos[k]] + QString::number(AlignNumbering2Sequence2(refCodes[j]+1,Communities[i].pos[k],fullSequences)+GetOffsetFromSeqName(fullAlignment[refCodes[j]])).toStdString();

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

void Network::exportLookProt(QString filename, int type){
    set<string> proteins;

    //GET LIST OF PROTEINS NAMES
    for(unsigned int i = 0; i < uniprotMined.size(); i++)
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

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
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

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
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

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
                    Uniprot* entryprot = uniprotMined[i];

                    if(protName == entryprot->getName()){
                        if(entryprot->getDataset() == 0) out << "dataset=\"Swiss-Prot\">\n";
                        else out << "dataset=\"TrEMBL\">\n";
                        break;
                    }
                }

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
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

                for(unsigned int i = 0; i < uniprotMined.size(); i++){
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

void Network::exportLookComm(QString filename, int type, vector<string> conserved){
    switch(type){
        case 0:
        {
            //COMMS
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".txt";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < conserved.size(); i++){
                string path = filename.toStdString() + "/cons_" + conserved[i] + ".txt";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(conserved[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    string path = filename.toStdString() + "/c" + QString::number(i).toStdString() + "_" + comunidades[i][j] + ".csv";

                    //Salva em arquivo
                    QFile f(path.c_str());
                    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                        return;
                    }

                    QTextStream out(&f);

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < conserved.size(); i++){
                string path = filename.toStdString() + "/cons_" + conserved[i] + ".csv";

                //Salva em arquivo
                QFile f(path.c_str());
                if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                    return;
                }

                QTextStream out(&f);

                out << "PROTEIN SEQNUMBER TYPE DESCRIPTION POSITION BEGIN END ORIGINAL VARIATION\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(conserved[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < comunidades.size(); i++){
                out << "\t<community id=\"" << i+1 << "\">\n";

                for(unsigned int j = 0; j < comunidades[i].size(); j++){
                    out << "\t\t<residue alignN=\"" << comunidades[i][j].c_str() << "\">\n";

                    vector<Uniprot*> resFeats = this->getAllResidueFeatures(comunidades[i][j]);

                    for(unsigned int k = 0; k < resFeats.size(); k++){
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
            out << "\t<community id=\"CONS\">\n";

            for(unsigned int i = 0; i < conserved.size(); i++){
                out << "\t\t<residue alignN=\"" << conserved[i].c_str() << "\">\n";

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(conserved[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < comunidades.size(); i++){
                for(unsigned int j = 0; j < comunidades[i].size(); j++){
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

                    for(unsigned int k = 0; k < resFeats.size(); k++){
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
            for(unsigned int i = 0; i < conserved.size(); i++){
                string path = filename.toStdString() + "/cons_" + conserved[i] + ".csv";

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

                vector<Uniprot*> resFeats = this->getAllResidueFeatures(conserved[i]);

                for(unsigned int k = 0; k < resFeats.size(); k++){
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


int Network::countCommunities(){
    return comunidades.size();
}
