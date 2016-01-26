#include "pdb.h"


Pdb::Pdb(string pdb){
    vector<string> lines = split(pdb,'\n');
    interval1 = 0;
    interval2 = 0;
    resolution = 0;
    this->refseq = "";
    header = lines[0] + "\n";
    footer = "";

    id = lines[0].substr(62,4);
    //printf("%s\n",id.c_str());

    int i;
    for(i = 1; i < lines.size(); i++){
        if(lines[i].substr(0,21) == "REMARK   2 RESOLUTION"){
            string temp = "";
            char c;

            c = lines[i][25];

            if(c != ' ') temp += c;
            //temp += lines[i][26] + lines[i][27] + lines[i][28] + lines[i][29];
            temp += lines[i].substr(26,4);
            replace(temp.begin(),temp.end(),'.',',');
            this->resolution = atof(temp.c_str());
            //printf("%s - %f",temp.c_str(),resolution);
        }else if(lines[i].substr(0,4) == "ATOM")
            break;
        header += lines[i] + "\n";
    }

    for(i; i < lines.size(); i++){
        if(lines[i].substr(0,4) == "ATOM"){
            PdbAtom *atom = new PdbAtom(lines[i]);
            atoms.push_back(atom);
        }else
            footer += lines[i] + "\n";
    }
}

Pdb::Pdb(QString filepath){
    string line;
    this->resolution = 0;
    this->interval1 = 0;
    this->interval2 = 0;
    this->refseq = "";
    header = "";
    footer = "";
    ifstream infile;

    infile.open(filepath.toStdString());

    getline(infile,line);

    id = line.substr(62,4);
    header += line + "\n";

    bool isatom = false;
    while(getline(infile,line)){
        if(line.substr(0,21) == "REMARK   2 RESOLUTION"){
            string temp = "";
            header += line + "\n";
            char c;

            c = line[25];

            if(c != ' ') temp += c;
            temp += line.substr(26,4);
            replace(temp.begin(),temp.end(),'.',',');
            this->resolution = atof(temp.c_str());
        }else if(line.substr(0,4) == "ATOM"){
            PdbAtom *atom = new PdbAtom(line);
            atoms.push_back(atom);
            isatom = true;
        }else{
            if(isatom) footer += line + "\n";
            else header += line + "\n";
        }
    }
    infile.close();

    //printf("%s\n%s",header.c_str(),footer.c_str());
}

Pdb::~Pdb()
{

}

vector<string> Pdb::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

string Pdb::getId(){
    return this->id;
}

void Pdb::setId(string id){
    this->id = id;
}

float Pdb::getResolution(){
    return this->resolution;
}

void Pdb::setResolution(float res){
    this->resolution = res;
}

int Pdb::getInterval1(){
    return interval1;
}

int Pdb::getInterval2(){
    return interval2;
}

void Pdb::setIntervals(int i1, int i2){
    interval1 = i1;
    interval2 = i2;
}

string Pdb::getRefseq(){
    return this->refseq;
}

void Pdb::setRefseq(string seq){
    refseq = seq;
}

char Pdb::getRefseq_chain(){
    return this->refseq_chain;
}

void Pdb::setRefseq_chain(char c){
    this->refseq_chain = c;
}

vector<PdbAtom *> Pdb::getAllAtoms(){
    return atoms;
}

vector<PdbAtom*> Pdb::getAllAtoms(char chain){
    vector<PdbAtom*> vec;

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];

        if(atom->getChain() == chain)
            vec.push_back(atom);
    }

    return vec;
}

int Pdb::countAtoms(){
    return atoms.size();
}

void Pdb::clearAtoms(){
    atoms.clear();
}

PdbAtom *Pdb::getAtom(int i){
    return atoms[i];
}

void Pdb::addAtom(PdbAtom *atom){
    atoms.push_back(atom);
}

void Pdb::setResiduesSeqNumber(char chain){
    unsigned int i = 0;

    for(i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];

        if(atom->getResidueNumber() == interval1 && atom->getChain() == chain){
            break;
        }
    }

    unsigned int seqcount = 1;
    unsigned int actualresn = interval1;
    for(i; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];
        if(atom->getChain() == chain){
            if(atom->getResidueNumber() == actualresn)
                atom->setSeqnumber(seqcount);
            else if(atom->getResidueNumber() > interval2){
                break;
            }else{
                seqcount ++;
                actualresn = atom->getResidueNumber();
                atom->setSeqnumber(seqcount);
            }
        }
    }
}

vector<tuple<string, string> > Pdb::getResiduesInContact(float dist, char chain){
    vector<tuple<string,string> > contacts;
    set<tuple<string, string> > tempset;

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom *atom1 = atoms[i];
        if(atom1->getChain() == chain){
            for(unsigned int j = 0; j < atoms.size(); j++){
                if(i != j){
                    PdbAtom *atom2 = atoms[j];
                    if(atom2->getChain() == chain){
                        float x1 = atom1->getX();
                        float x2 = atom2->getX();
                        float y1 = atom1->getY();
                        float y2 = atom2->getY();
                        float z1 = atom1->getZ();
                        float z2 = atom2->getZ();

                        float distance = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)) + ((z2-z1)*(z2-z1)));

                        string res1 = atom1->getResidueCode() + to_string(atom1->getSeqnumber());
                        string res2 = atom2->getResidueCode() + to_string(atom2->getSeqnumber());
                        if(distance <= dist && res1 != res2 && atom1->getSeqnumber() != 0 && atom2->getSeqnumber() != 0){
                            if(res1 > res2){
                                tuple<string,string> tup(res1,res2);
                                tempset.insert(tup);
                            }else{
                                tuple<string,string> tup(res2,res1);
                                tempset.insert(tup);
                            }
                        }
                    }
                }
            }
        }
    }

    set<tuple<string, string> >::const_iterator sit(tempset.begin()), send(tempset.end());
    for(;sit!=send;++sit){
        contacts.push_back(*sit);
    }

    return contacts;
}

string Pdb::getPDBSequence(char chain){
    string sequence = "";
    int currentPos = 0;

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];

        if(atom->getChain() == chain){
            if(currentPos != atom->getResidueNumber()){
                sequence += atom->getResidueCode();
                currentPos = atom->getResidueNumber();
            }
        }
    }

    return sequence;
}

bool Pdb::SWSalign(int offset, char chain){
    map<int,int> swsmap;
    string strchain = std::string(1,chain);


    //Montar URL
    QString url = "http://www.bioinf.org.uk/cgi-bin/pdbsws/query.pl?qtype=pdb;";
    url += "id=" + QString::fromStdString(this->id.c_str()) + ";";
    url += "chain=" + QString::fromStdString(strchain.c_str()) + ";";
    url += "all=yes&pretty=0";

    //Faz a conexão
    QUrl qurl = url;
    QNetworkAccessManager manager;
    QNetworkRequest request(qurl);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //qDebug(reply->readAll());
    QString swscontent = reply->readAll();

    if(swscontent.contains("302 Found") || swscontent.contains("301 Moved") || swscontent == "" || swscontent.contains("not found")){
        //printf("\n%s",swscontent.toStdString().c_str());
        return false;
    }else{
        vector<string> lines = this->split(swscontent.toStdString(),'\n');

        for(unsigned int i = 0; i < lines.size(); i++){
            string line = lines[i];
            if(tolower(line[0]) == tolower(this->id[0]) && tolower(line[1]) == tolower(this->id[1]) && tolower(line[2]) == tolower(this->id[2]) && tolower(line[3]) == tolower(this->id[3])){
                string strpdbresn = "";
                string strseqnum = "";
                int pdbresn, seqnum;

                string temp = line.substr(43,5);
                for(unsigned int j = 0; j < temp.size(); j++){
                    if(temp[j] != ' ') strseqnum += temp[j];
                }
                seqnum = stoi(temp);

                temp = line.substr(20,5);
                for(unsigned int j = 0; j < temp.size(); j++){
                    if(temp[j] != ' ') strpdbresn += temp[j];
                }
                pdbresn = stoi(strpdbresn);

                int offsetedseqnum = seqnum-offset;

                swsmap[pdbresn] = offsetedseqnum;
            }
        }

        for(unsigned int i = 0; i < atoms.size(); i++){
            PdbAtom* atom = atoms[i];

            if(atom->getChain() == chain){
                if(swsmap[atom->getResidueNumber()] > 0)
                    atom->setSeqnumber(swsmap[atom->getResidueNumber()]);
                else
                    atom->setSeqnumber(0);
            }
        }
    }

    return true;
}

string Pdb::getSWSSeq(char chain){
    string sequence = "";
    int currentPos = 0;

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];

        if(atom->getChain() == chain){
            if(currentPos != atom->getResidueNumber()){
                if(atom->getSeqnumber() > 0) sequence += atom->getResidueCode();
                currentPos = atom->getResidueNumber();
            }
        }
    }

    return sequence;
}

bool Pdb::exportStructure(QString filepath, vector<float> bfactors, char chain){
    //Salva em arquivo
    QFile f(filepath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&f);

    out << this->header.c_str();

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];
        if(atom->getSeqnumber() > 0 && atom->getChain() == chain){
            float bf = bfactors[atom->getSeqnumber()-1];
            out << atom->to_string(bf).c_str() << "\n";
        }else
            out << atom->to_string(0).c_str() << "\n";
    }

    out << this->footer.c_str();

    f.close();
}

void Pdb::printSeqNumbers(){
    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];

        printf("%d\n",atom->getSeqnumber());
    }
}
