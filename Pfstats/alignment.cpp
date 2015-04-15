#include "alignment.h"
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

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

void Alignment::setFilepath(string path){
    this->filepath = path;
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

void Alignment::AlignmentTrimming(float minocc, int refseq, string newalignmentfilename){
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

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);

}

void Alignment::IdentityMinimum(float minid, int refseq, string newalignmentfilename){
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

    progress.close();
    if(newalignmentfilename != "") AlignmentWrite(newalignmentfilename);
}

void Alignment::IdentityTrimming(float maxid, string newalignmentfilename){
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
}

void Alignment::FreqWrite(){
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
