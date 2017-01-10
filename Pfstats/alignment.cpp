#include "alignment.h"
#include <omp.h>
#include <fstream>
#include <math.h>
#include "uniprot.h"
#include <cstdlib>
#include <ctype.h>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QFileDialog>
#include <QtNetwork>
#include <set>

Alignment::Alignment()
{
    type = -1;
    filepath = "";
}

Alignment::Alignment(string path){
    type = -1;
    this->filepath = path;
    this->GetFromFile();
}

Alignment::~Alignment()
{
    this->clear();
}

int Alignment::getType(){
    return type;
}

void Alignment::setType(int t){
    type = t;
}

void Alignment::clear(){
    filepath.clear();
    filepath.shrink_to_fit();

    recommendPdbs.clear();
    recommendPdbs.shrink_to_fit();

    sequences.clear();
    sequences.shrink_to_fit();
    sequencenames.clear();
    sequencenames.shrink_to_fit();

    hmmpositions.clear();
    hmmpositions.shrink_to_fit();

    /*
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter* filter = filters[i];
        filter->clear();
    }
    filters.clear();
    filters.shrink_to_fit();
    */
}

string Alignment::getFilepath(){
    return this->filepath;
}

vector<string> Alignment::getFullAlignment(){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter *filter = filters[i];
        if(filter->getType() == 9){
            return filter->getSequenceNames();
        }
    }

    vector<string> blank;
    return blank;
}

vector<string> Alignment::getFullSequences(){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter *filter = filters[i];
        if(filter->getType() == 9){
            return filter->getSequences();
        }
    }

    vector<string> blank;
    return blank;
}

Filter* Alignment::getFullFilter(){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter *filter = filters[i];
        if(filter->getType() == 9){
            return filter;
        }
    }

    return NULL;
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

unsigned int Alignment::freqmatrixposition(char c){
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

bool Alignment::validstartcharacter(char c){
    if ((c=='a')||(c=='b')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='j')||(c=='k')||(c=='l')||(c=='m')||
        (c=='n')||(c=='o')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='u')||(c=='v')||(c=='w')||(c=='x')||(c=='y')||
        (c=='z')||(c=='A')||(c=='B')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='J')||(c=='K')||
        (c=='L')||(c=='M')||(c=='N')||(c=='O')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='U')||(c=='V')||(c=='W')||(c=='X')||
        (c=='Y')||(c=='Z')||(c=='0')||(c=='1')||(c=='2')||(c=='3')||(c=='4')||(c=='5')||(c=='6')||(c=='7')||(c=='8')||(c=='9')) return(true);
    else return(false);
}

unsigned int Alignment::GetOffsetFromSeqName(string seqname){
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

bool Alignment::isaa(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
       (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
       (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
       (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y'))
            return (true);
    else return false;
}

bool Alignment::isaa(char c, bool casesensitive){
    if (!casesensitive)
        {
        if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
        (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y'))
            return true;
            else return false;
        }
     else
     {
        if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y'))
         return true;
     }
    return false;
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

void Alignment::generateXML(string outputXML){
    QFile f(outputXML.c_str());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);

    out << "<?xml version=\"1.0\"?>\n\n";
    out << "<PFStats>\n";

    for(unsigned int i = 0; i < filters.size(); i++){
        Filter* filter = filters[i];

        out << "<filters>\n";
        string content = filter->generateXML(); //N SALVAR CONSERVATION (SO PARAMETROS), RODAR DE NOVO
        out << content.c_str() << "\n";
        out << "</filters>";
    }

    out << "</PFStats>";
    f.close();
}

string Alignment::verifyOffset(string seqname){
    vector<string>splitSlash = this->split(seqname,'/');

    if(splitSlash.size() > 2){
        string str1 = "";
        string str2 = splitSlash[splitSlash.size()-1];

        for(unsigned int i = 0; i < splitSlash.size() - 1; i++){
            str1 += splitSlash[i];
        }

        splitSlash.clear();
        splitSlash.push_back(str1);
        splitSlash.push_back(str2);
    }else if(splitSlash.size() == 1){
        return splitSlash[0] + "/1-999";
    }

    if(splitSlash.size() == 2){
        vector<string> splitDash = this->split(splitSlash[1],'-');
        if(splitDash.size() == 2){
            if(splitDash[0].find_first_not_of( "0123456789" ) == string::npos && splitDash[1].find_first_not_of( "0123456789" ) == string::npos)
                return splitSlash[0] + "/" + splitSlash[1];
        }else{
            return splitSlash[0] + splitSlash[1] + "/1-999";
        }
    }

    return "error";

}

void Alignment::readSTO(){
    fstream alignmentfile;
    string line;

    alignmentfile.open(this->filepath.c_str());

    while(!alignmentfile.eof()){
        getline(alignmentfile,line);

        if(line[0] == '#'){
            vector<string> splittedLine = this->split(line,' ');
            for(unsigned int i = 0; i < splittedLine.size(); i++){
                if(splittedLine[i] == "PDB;"){
                    string protein = splittedLine[1];
                    string pdb = splittedLine[i+1];
                    char chain = splittedLine[i+2][0];
                    string temp = splittedLine[i+3];
                    string interval = temp.substr(0,temp.size()-1);
                    tuple<string,string,char,string> tup(protein,pdb,chain,interval);
                    recommendPdbs.push_back(tup);
                    break;
                }
            }
        }else if(line.length() > 50){
            vector<string> splittedLine = this->split(line,' ');
            string protein = splittedLine[0];
            string sequence;

            for(unsigned int i = 1; i < splittedLine.size(); i++){
                if(splittedLine[i] != ""){
                    sequence = splittedLine[i];
                    break;
                }
            }

            protein = this->verifyOffset(protein);
            sequencenames.push_back(protein);
            sequences.push_back(sequence);
        }
    }

    alignmentfile.close();
}

void Alignment::readSTO(vector<string> pfam){
    string line;

    for(unsigned int i = 0; i < pfam.size(); i++){
        line = pfam[i];

        if(line[0] == '#'){
            vector<string> splittedLine = this->split(line,' ');
            for(unsigned int i = 0; i < splittedLine.size(); i++){
                if(splittedLine[i] == "PDB;"){
                    string protein = splittedLine[1];
                    string pdb = splittedLine[i+1];
                    char chain = splittedLine[i+2][0];
                    string temp = splittedLine[i+3];
                    string interval = temp.substr(0,temp.size()-1);
                    tuple<string,string,char,string> tup(protein,pdb,chain,interval);
                    recommendPdbs.push_back(tup);
                    break;
                }
            }
        }else if(line.length() > 100){
            vector<string> splittedLine = this->split(line,' ');
            string protein = splittedLine[0];
            string sequence;

            for(unsigned int i = 1; i < splittedLine.size(); i++){
                if(splittedLine[i] != ""){
                    sequence = splittedLine[i];
                    break;
                }
            }

            protein = this->verifyOffset(protein);
            sequencenames.push_back(protein);
            sequences.push_back(sequence);
        }
    }
}

void Alignment::convertLowerDots(){
    for(unsigned int i = 0; i < sequences.size(); i++){
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            if(sequences[i][j] == '.') sequences[i][j] = '-';
            else sequences[i][j] = toupper(sequences[i][j]);
        }
    }
}

void Alignment::readFASTA(){
    fstream alignmentfile;
    string line;
    string seqname;
    string seq = "";

    alignmentfile.open(this->filepath.c_str());

    getline(alignmentfile,line);
    if(line[0] != '>') return;
    seqname = line.substr(1);

    while(!alignmentfile.eof()){
        getline(alignmentfile,line);

        if(line[0] == '>'){
            seqname = this->verifyOffset(seqname);
            sequencenames.push_back(seqname);
            sequences.push_back(seq);
            seqname = line.substr(1);
            seq = "";
        }else{
            seq += line;
        }
    }

    alignmentfile.close();
}

void Alignment::readFASTA(vector<string> fasta){
    string line, seqname;
    string seq = "";

    line = fasta[0];
    if(line[0] != '>') return;
    seqname = line.substr(1);

    for(unsigned int i = 1; i < fasta.size(); i++){
        line = fasta[i];

        if(line[0] == '>'){
            seqname = this->verifyOffset(seqname);
            sequencenames.push_back(seqname);
            sequences.push_back(seq);
            seqname = line.substr(1);
            seq = "";
        }else{
            seq += line;
        }
    }
}

void Alignment::readPFAM(){
    fstream alignmentfile;
    string line;
    bool flag1;      // 0 when still in sequence name
    bool flag2;      // 0 when still before sequence start

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
            for (unsigned int c1=0;c1<=line.size()-1;c1++){
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
}

void Alignment::readPFAM(vector<string> pfam){
    string line;
    bool flag1, flag2;

    for(unsigned int i = 0; i < pfam.size(); i++){
        line = pfam[i];
        flag1 = 0;
        flag2 = 0;

        if(validstartcharacter(line[0])){
            //printf("%s\n",line.c_str());
            sequencenames.push_back("");
            sequences.push_back("");
            for (unsigned int c1=0;c1<=line.size()-1;c1++){
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
}

bool Alignment::GetFromFile(){
    fstream alignmentfile;
    string line;
    unsigned int c1,c2;
    vector<vector<int> > subsetfrequencies;
    vector<int> SortOrder;

    sequencenames.clear();
    sequences.clear();

    alignmentfile.open(filepath.c_str());
    getline(alignmentfile,line);
    if(line[0] == '#') readSTO();
    else if(line[0] == '>') readFASTA();
    else readPFAM();

    QProgressDialog progress("Loading the alignment...","Cancel",0,0,NULL);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();


    // CHECKS ALIGNMENT CONSISTENCY
    SortOrder.clear();
    if (subsetfrequencies.size()>0) for(c1=0;c1<=subsetfrequencies.size()-1;c1++)
        subsetfrequencies[c1].clear();
        subsetfrequencies.clear();
    if(sequences.size()>0){
        for(c1=1;c1<=sequences.size()-1;c1++)
        if(sequences[0].size()!=sequences[c1].size() || sequences[c1].size() == 0){
            printf("Sequence #%d (%s) does not has the same size of the first sequence. Please check your alignment file",c1+1,sequencenames[c1].c_str());
            progress.close();
            return false;
        }

        for (c1=0;c1<=sequences.size()-1;c1++) SortOrder.push_back(c1);
        for(c1=0;c1<=sequences[0].size();c1++){ // total positions: sequencesize + 1 (positions + totals)
            QApplication::processEvents();
            if(progress.wasCanceled()){
                progress.close();
                return false;
            }

            subsetfrequencies.push_back( vector<int>(21) );
            for(c2=0; c2<=20; c2++)
                subsetfrequencies[c1].push_back(0);
        }

        Filter* fullFilter = new Filter("Full Alignment","T20",9);
        for(unsigned int i = 0; i < sequencenames.size(); i++){
            QApplication::processEvents();
            fullFilter->addSequences(sequencenames[i],sequences[i]);
        }

        fullFilter->setSorOrder(SortOrder);
        fullFilter->setSubsetFrequencies(subsetfrequencies);

        filters.push_back(fullFilter);

        progress.close();
        return true;
    }

    progress.close();
    return false;
}

bool Alignment::getFromStd(string text){
    vector<string> pfam = split(text,'\n');
    vector<int> SortOrder;
    vector<vector<int> > subsetfrequencies;

    sequencenames.clear();
    sequences.clear();

    string line = pfam[0];
    if(line[0] == '#') readSTO(pfam);
    else if(line[0] == '>') readFASTA(pfam);
    else readPFAM(pfam);

    // CHECKS ALIGNMENT CONSISTENCY
    if(sequences.size() > 0){
        for(unsigned int i = 0; i < sequences.size(); i++){
            if(sequences[0].size()!=sequences[i].size() || sequences[i].size() == 0){
                QString msg = "Sequence #" + QString::number(i+1) + " (" + sequencenames[i].c_str() +
                        ") does not has the same size of the first sequence. Please check your alignment file";
                QMessageBox::critical(NULL,"Error while parsing the alignment",msg);
                return false;
            }
        }

        for(unsigned int i = 0; i < sequences.size(); i++)
            SortOrder.push_back(i);

        for(unsigned int i = 0; i <= sequences[0].size(); i++){
            subsetfrequencies.push_back(vector<int>(21));
            for(unsigned int j = 0; j <= 20; j++)
                subsetfrequencies[i].push_back(0);
        }

        Filter* fullFilter = new Filter("Full Alignment","T20",9);
        for(unsigned int i = 0; i < sequencenames.size(); i++){
            fullFilter->addSequences(sequencenames[i],sequences[i]);
        }
        fullFilter->setSorOrder(SortOrder);
        fullFilter->setSubsetFrequencies(subsetfrequencies);

        filters.push_back(fullFilter);

        return true;
    }
    QMessageBox::critical(NULL,"Alignment loading error","Couldn't parse this alignment");
    return false;
}

vector<string> Alignment::getSequencesName(){
    return sequencenames;
}

vector<string> Alignment::getSequences(){
    return sequences;
}

unsigned int Alignment::SeqSize(int seq){
    int size=0;
    for (unsigned int i=0;i<=sequences[seq].size()-1;i++)
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

int Alignment::seqname2seqint3(string refseqcode){
    vector<string> fullAlignment = this->getFullAlignment();

    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        if(fullAlignment[i] == refseqcode) return i;
    }
    return 0;
}

int Alignment::seqname2seqint2(string refseqcode){
    vector<string> fullAlignment = this->getFullAlignment();

    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        vector<string> vecSplit = this->split(fullAlignment[i],'/');
        if(vecSplit[0] == refseqcode) return i;
    }
    return 0;
}

bool Alignment::taxonTrimming(string taxon, string refseqName, string refSeq){
    string url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/pfam/taxon-filter/" + taxon;
    string text = "";

    QProgressDialog progress("Filtering by taxon...", "Abort", 0, 0);

    for(unsigned int i = 0; i < sequencenames.size(); i++){
        text += split(sequencenames[i],'/')[0] + "\n";
    }

    //printf("%s\n",text.c_str());

    QByteArray const data = QString::fromStdString(text).toUtf8();

    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll();
    //printf("%s\n",html.toStdString().c_str());
    for(unsigned int i = 0; i < sequences.size(); i++){
        if(progress.wasCanceled()) return false;
        string protname = split(sequencenames[i],'/')[0];
        if(!html.contains(protname.c_str())){
            sequences[i].clear();
            sequencenames[i].clear();
            sequences.erase(sequences.begin()+i);
            sequencenames.erase(sequencenames.begin()+i);
            if(i > 0) i--;
        }//else printf("%s\n",protname.c_str());
    }


    if(refseqName != "0"){
        if(progress.wasCanceled()) return false;
        if(sequencenames[0] != refseqName){
            sequences.insert(sequences.begin(),refSeq);
            sequencenames.insert(sequencenames.begin(),refseqName);
        }
    }

    progress.close();
    return true;
}

bool Alignment::AlignmentTrimming(float minocc, int refseq, string refSeq, string refseqName, bool casesensitive){
    int totalseq,totalaln;
    unsigned int c2;
    string referencesequence=sequences[refseq];
    vector<int> seqstoremove;

    QProgressDialog progress("Trimming Alignment...", "Abort", 0, sequences.size());
    progress.show();

    for(int c1 = sequences.size()-1; c1 >= 0; c1--){
        progress.setValue(sequences.size() - c1);

        if(progress.wasCanceled()) return false;
        if(c1!=refseq){
            totalseq = 0;
            totalaln = 0;
            for (c2=0;c2<=sequences[c1].size()-1;c2++){
                if(isaa(referencesequence[c2],casesensitive)){
                    totalseq++;
                    if(isaa(sequences[c1][c2],casesensitive)){
                        totalaln++;
                    }
                }
            }
            if (((float)totalaln)/((float)totalseq)<minocc){
                seqstoremove.push_back(c1);
                //printf("%d ",c1);
            }
        }
    }

    for (int c1=0;c1<seqstoremove.size();c1++){
        if(progress.wasCanceled()) return false;
        sequences[seqstoremove[c1]].clear();
        sequencenames[seqstoremove[c1]].clear();
        sequences.erase(sequences.begin()+seqstoremove[c1]);
        sequencenames.erase(sequencenames.begin()+seqstoremove[c1]);
    }

    if(sequencenames[0] != refseqName){
        sequences.insert(sequences.begin(),refSeq);
        sequencenames.insert(sequencenames.begin(),refseqName);
    }

    progress.close();
    return true;
}

bool Alignment::AlignmentTrimming(float minocc, int refseq){
    //printf("%d",sequences.size());
    QProgressDialog progress("Trimming Alignment...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    unsigned int c1,c2;
    int totalseq,totalaln;

    //QMessageBox::information(NULL,"ok","CERTO");

    for(c1=0; c1<=sequences.size()-1;c1++){
        progress.setValue(c1);
        progress.setMaximum(sequences.size()-1);

        if(progress.wasCanceled()) return false;

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
    return true;
}

bool Alignment::IdentityMinimum(float minid, int refseq){
    //printf("%d",sequences.size());
    QProgressDialog progress("Culling Minimum Identity...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    unsigned int c1;

    //QMessageBox::information(NULL,"a",sequencenames[0].c_str());

    for (c1=0;c1<=sequences.size()-1;c1++){
        //printf("%d\n",c1);
        progress.setValue(c1);

        if(progress.wasCanceled()) return false;

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
    return true;
}

bool Alignment::hmmCoverageTrimmimg(float occ){
    int intProgress = sequences.size()-1;
    QProgressDialog progress("Trimming Coverage...", "Abort", 0, intProgress);
    progress.setWindowModality(Qt::WindowModal);
    int nvalidpositions;

    for(int i = sequences.size()-1; i >= 0; i--){
        nvalidpositions = 0;

        progress.setValue(intProgress-i);
        if(progress.wasCanceled()) return false;

        for(unsigned int j = 0; j < hmmpositions.size(); j++){
            if(isaa(sequences[i][hmmpositions[j]],false)) nvalidpositions++;
        }

        float currentValue = (float)nvalidpositions/(float)hmmpositions.size();
        if(currentValue < occ){
            sequencenames.erase(sequencenames.begin()+i);
            sequences.erase(sequences.begin() + i);
        }
    }

    if(sequences.size() == 0) return false;

    progress.close();
    return true;
}

bool Alignment::IdentityTrimming(float maxid){
    //QMessageBox::information(NULL,"a","TESTE");
    //printf("%d",sequences.size());
    QProgressDialog progress("Trimming Identity...", "Abort", 0, sequences.size()-1);
    progress.setWindowModality(Qt::WindowModal);
    unsigned int seq1,seq2;
    seq1=0;
    //printf("%d",sequences.size());
    while(true){ //for(seq1=0;seq1<=sequences.size()-2;seq1++)
        progress.setValue(seq1);
        progress.setMaximum(sequences.size());
        QApplication::processEvents();
        //printf("%d\n",seq1);

        if(seq1>=sequences.size()-2) break;

        seq2=seq1+1;
        while(true){
            if(progress.wasCanceled()) return false;
            QApplication::processEvents();
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
    return true;
}

vector<string> Alignment::getRecommendsPDBs(string protein){
    vector<string> recommended;

    for(unsigned int i = 0; i < recommendPdbs.size(); i++){
        string prot = std::get<0>(recommendPdbs[i]);
        //string prot = split(temp,'/')[0];
        if(protein == prot){
            string pdb = std::get<1>(recommendPdbs[i]);
            char chain = std::get<2>(recommendPdbs[i]);
            string pdbchain = pdb + " (" + chain + ")";
            recommended.push_back(pdbchain);
        }
    }

    return recommended;
}

string Alignment::getPDBInterval(string pdbid){
    string interval = "";

    for(unsigned int i = 0; i < recommendPdbs.size(); i++){
        string id = std::get<1>(recommendPdbs[i]);
        if(pdbid == id){
            interval = std::get<3>(recommendPdbs[i]);
            break;
        }
    }

    return interval;
}

//1 for contains .
//0 elsewhere
int Alignment::getKindOfAlignment(){
    for(unsigned int i = 0; i < sequences.size(); i++){
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            if(sequences[i][j] == '.') return 1;
        }
    }

    return 0;
}

void Alignment::dots2dashs(){
    for(unsigned int i = 0; i < sequences.size(); i++){
        for(unsigned int j = 0; j < sequences[i].size(); j++){
            if(sequences[i][j] == '.') sequences[i][j] = '-';
        }
    }
}

void Alignment::addFilter(Filter *filter){
    filters.push_back(filter);
}

void Alignment::removeFilter(string name){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter* filter = filters[i];

        if(filter->getName() == name){
            filter->clear();
            filters.erase(filters.begin() + i);
        }
    }
}

vector<Filter*> Alignment::getFilters(){
    return filters;
}

int Alignment::countFilters(){
    return filters.size();
}

Filter* Alignment::getFilterByName(string name){
    printf("\n\n");
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter *filter = filters[i];
        if(filter->getName() == name) return filter;
    }

    return NULL;
}

void Alignment::addSequences(vector<string> seqs, vector<string> names){
    this->sequences = seqs;
    this->sequencenames = names;
}

bool Alignment::isHMMposition(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
        (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
        (c=='-')) return true;
    else return false;
}


void Alignment::defineHMMpositions(){
    hmmpositions.clear();

    for(unsigned int i = 0; i < sequences[0].size(); i++){
        if(isHMMposition(sequences[0][i]))
            hmmpositions.push_back(i);
    }
}

void Alignment::updateFiltersData(){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter *filter = filters[i];
        filter->updateSequencesData();

        for(unsigned int i = 0; i < filter->countNetworks(); i++){
            Network *net = filter->getNetwork(i);
            net->updateCommunitiesData();
        }
    }
}

bool Alignment::verifyValidFilterName(string name){
    for(unsigned int i = 0; i < filters.size(); i++){
        Filter* f = filters[i];
        if(f->getName() == name) return false;
    }

    return true;
}
