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

    PdbAtom *firstatom = new PdbAtom(lines[i]);
    int currentPos = firstatom->getResidueNumber();
    PdbResidues *residue = new PdbResidues();
    for(i; i < lines.size(); i++){
        if(lines[i].substr(0,4) == "ATOM"){
            PdbAtom *atom = new PdbAtom(lines[i]);
            atoms.push_back(atom);
            if(currentPos != atom->getResidueNumber()){
                residues.push_back(residue);
                residue = new PdbResidues();
                residue->addAtom(atom);
            }else{
                residue->addAtom(atom);
            }
           currentPos = atom->getResidueNumber();
        }else
            footer += lines[i] + "\n";
    }
    residues.push_back(residue);

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

    int currentPos = 0;
    bool isfirstatom = true;
    PdbResidues *residue = new PdbResidues();
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
            if(isfirstatom){
                PdbAtom *atom = new PdbAtom(line);
                currentPos = atom->getResidueNumber();
                        isfirstatom = false;
            }
            PdbAtom *atom = new PdbAtom(line);
            atoms.push_back(atom);
            isatom = true;
            if(currentPos != atom->getResidueNumber()){
                residues.push_back(residue);
                residue = new PdbResidues();
                residue->addAtom(atom);
            }else{
                residue->addAtom(atom);
            }
           currentPos = atom->getResidueNumber();
        }else{
            if(isatom) footer += line + "\n";
            else header += line + "\n";
        }
    }
    residues.push_back(residue);
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

//NOT USED ANYMORE
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

//Não requer intervalos
int Pdb::setResiduesSeqNumber(string pfamsequence, char chain){

    string pdbsequence = this->getPDBSequence(chain);
    tuple<string,string,int> tup = this->needleman_wunsch(pfamsequence,pdbsequence);
    string alignedPFAM = get<0>(tup);
    string alignedPDB = get<1>(tup);
    //string newpdbseq = "";
    vector<int> nums;
    unsigned int actualresn;// = atoms[0]->getResidueNumber();
    unsigned int seqcount = 1;
    unsigned int vetcount = 0;

    for(unsigned int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];
        if(atom->getChain() == chain){
            actualresn = atoms[i]->getResidueNumber();
            break;
        }
    }

    for(int i = 0; i < alignedPDB.size(); i++){
        if(alignedPFAM[i] == '-') nums.push_back(0);
        else if(alignedPDB[i] == '-') seqcount++;
        else{
            nums.push_back(seqcount);
            seqcount++;
        }
    }

    for(int i = 0; i < atoms.size(); i++){
        PdbAtom* atom = atoms[i];
        if(atom->getChain() == chain){
            if(atom->getResidueNumber() == actualresn){
                //if(nums[vetcount] == -1) vetcount += 2;
                atom->setSeqnumber(nums[vetcount]);
            }else{
                vetcount++;
                actualresn = atom->getResidueNumber();
                atom->setSeqnumber(nums[vetcount]);
            }
        }

        //printf("%d\n",atom->getSeqnumber());
    }


    return get<2>(tup);

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

tuple<string,string,int> Pdb::needleman_wunsch(string a, string b){
    int dp[1001][1001];
    int n = a.length();
    int m = b.length();
    int match_score = 2;
    int mismatch_score = 1;
    int gap_score = 1;
    tuple<string,string,int> tup;

    if(n > 1000 || m > 1000) return tup;

    for (unsigned int i = 0; i <= n; i++) dp[i][0] = dp[0][i] = -i * gap_score;

    for (unsigned int i = 1; i <= n; i++){
        for (unsigned int j = 1; j <= m; j++){
            int S = (a[i-1] == b[j-1]) ? match_score : -mismatch_score;
            dp[i][j] = max(dp[i-1][j-1] + S, max(dp[i-1][j] - gap_score, dp[i][j-1] - gap_score));
        }
    }

    //dp[n][m] is the best score
    get<2>(tup) = dp[n][m];

    string retA, retB;
    stack<char> SA, SB;
    int ii = n, jj = m;

    while (ii != 0 || jj != 0){
        if (ii == 0){
            SA.push('-');
            SB.push(b[jj-1]);
            jj--;
        }else if (jj == 0){
            SA.push(a[ii-1]);
            SB.push('-');
            ii--;
        }else{
            int S = (a[ii-1] == b[jj-1]) ? match_score : -mismatch_score;
            if (dp[ii][jj] == dp[ii-1][jj-1] + S){
                SA.push(a[ii-1]);
                SB.push(b[jj-1]);
                ii--; jj--;
            }else if (dp[ii-1][jj] > dp[ii][jj-1]){
                SA.push(a[ii-1]);
                SB.push('-');
                ii--;
            }else{
                SA.push('-');
                SB.push(b[jj-1]);
                jj--;
            }
        }
    }

    while (!SA.empty()){
        retA += SA.top();
        retB += SB.top();
        SA.pop();
        SB.pop();
    }

    get<0>(tup) = retA;
    get<1>(tup) = retB;

    printf("%d\n%s\n%s\n\n",dp[n][m],retA.c_str(),retB.c_str());

    return tup;

}

float Pdb::distance2atoms(PdbAtom *a1, PdbAtom *a2){
    return sqrt(pow(a1->getX() - a2->getX(),2) + pow(a1->getY() - a2->getY(),2) + pow(a1->getZ() - a2->getZ(),2));
}

float Pdb::distance2atoms(PdbAtom *a1, PdbPseudoAtom *a2){
    return sqrt(pow(a1->getX() - a2->getX(),2) + pow(a1->getY() - a2->getY(),2) + pow(a1->getZ() - a2->getZ(),2));
}

float Pdb::distance2atoms(PdbPseudoAtom *a1, PdbPseudoAtom *a2){
    return sqrt(pow(a1->getX() - a2->getX(),2) + pow(a1->getY() - a2->getY(),2) + pow(a1->getZ() - a2->getZ(),2));
}

float Pdb::angle3atoms(PdbAtom *a1, PdbAtom *a2, PdbAtom *a3){
    float ABx = a1->getX() - a2->getX();
    float ABy = a1->getY() - a2->getY();
    float ABz = a1->getZ() - a2->getZ();
    float BCx = a3->getX() - a2->getX();
    float BCy = a3->getY() - a2->getY();
    float BCz = a3->getZ() - a3->getZ();
    float ABvec = sqrt(ABx*ABx + ABy*ABy + ABz*ABz);
    float BCvec = sqrt(BCx*BCx + BCy*BCy + BCz*BCz);
    float ABnormalX = ABx/ABvec;
    float ABnormalY = ABy/ABvec;
    float ABnormalZ = ABz/ABvec;
    float BCnormalX = ABx/BCvec;
    float BCnormalY = ABy/BCvec;
    float BCnormalZ = ABz/BCvec;
    float result = ABnormalX*BCnormalX + ABnormalY*BCnormalY + ABnormalZ*BCnormalZ;

    return acos(result)*180/3.141592653589793;
}

float Pdb::angle3atoms(PdbAtom *a1, PdbPseudoAtom *a2, PdbAtom *a3){
    float ABx = a1->getX() - a2->getX();
    float ABy = a1->getY() - a2->getY();
    float ABz = a1->getZ() - a2->getZ();
    float BCx = a3->getX() - a2->getX();
    float BCy = a3->getY() - a2->getY();
    float BCz = a3->getZ() - a3->getZ();
    float ABvec = sqrt(ABx*ABx + ABy*ABy + ABz*ABz);
    float BCvec = sqrt(BCx*BCx + BCy*BCy + BCz*BCz);
    float ABnormalX = ABx/ABvec;
    float ABnormalY = ABy/ABvec;
    float ABnormalZ = ABz/ABvec;
    float BCnormalX = ABx/BCvec;
    float BCnormalY = ABy/BCvec;
    float BCnormalZ = ABz/BCvec;
    float result = ABnormalX*BCnormalX + ABnormalY*BCnormalY + ABnormalZ*BCnormalZ;

    return acos(result)*180/3.141592653589793;
}

bool Pdb::connectedAtoms(PdbAtom *a1, PdbAtom *a2){
    map<string,float> vdw = {{"C",1.70}, {"O",1.52}, {"N",1.55}, {"H",1.20}, {"P",1.80}, {"S",1.80}, {"Cl",1.75}, {"F",1.47} ,{"Zn",1.39} ,{"Mg",1.73},{"K",2.75},
                             {"Na",2.27}, {"I",1.98}, {"He",1.40},{"Cu",1.40}, {"Ne",1.54}, {"Hg",1.55}, {"Cd",1.58}, {"Ni",1.63}, {"Au",1.66}, {"Ag",1.72}, {"Pt",1.75},
                             {"Li",1.82},{"As",1.85}, {"Pd",1.63}, {"Br",1.85}, {"Si",2.10}, {"Xe",2.16}, {"Ga",1.87}, {"Ar",1.88}, {"U",1.86},{"Se",1.90},{"In",1.93},{"Tl",1.96},
                             {"Kr",2.02},{"Pb",2.02},{"Te",2.06},{"Sn",2.17}};
    if(distance2atoms(a1,a2) < (((vdw[a1->getElement()] + vdw[a2->getElement()])/2) + 0.35))
        return true;
    return false;
}

vector<float> Pdb::getMidpoints(vector<PdbAtom*> atom_list){
    vector<float> coord;
    coord.push_back(0);
    coord.push_back(0);
    coord.push_back(0);

    for(unsigned int i = 0; i < atom_list.size(); i++){
        PdbAtom* atom = atom_list[i];
        coord[0] += atom->getX() / atom_list.size();
        coord[1] += atom->getY() / atom_list.size();
        coord[2] += atom->getZ() / atom_list.size();
    }

    return coord;
}

bool Pdb::isValidResidue(string res){
    if(res == "HOH" || res == "ILE" || res == "VAL" || res == "LEU" || res == "PHE" || res == "CYS" || res == "MET" || res == "ALA"
            || res == "GLY" || res == "THR" || res == "TRP" || res == "PRO" || res == "GLN" || res == "GLU" || res == "ASP"
            || res == "ASN" || res == "TYR" || res == "HIS" || res == "SER" || res == "LYS" || res == "ARG") return true;
    return false;
}

bool Pdb::isPositiveCharged(PdbAtom *atom){
    string residue = atom->getResidue();
    string name = atom->getAtomName();

    if(name == "NmH2") return true;
    else{
        if(residue == "HIS" && (name == "ND1" || name == "NE2")) return true;
        else if(residue == "LYS" && name == "NZ") return true;
        else if(residue == "ARG" && (name == "NH!" || name == "NE" || name == "NH2")) return true;
    }

    return false;
}

bool Pdb::isNegativeCharged(PdbAtom *atom){
    string residue = atom->getResidue();
    string name = atom->getAtomName();

    if(name == "OXT") return true;
    else{
        if(residue == "GLU" && (name == "OE1" || name == "OE2")) return true;
        else if(residue == "ASP" && (name == "OD1" || name == "OD2")) return true;
    }

    return false;
}

bool Pdb::isHydrogenDonor(PdbAtom *atom){
    string residue = atom->getResidue();
    string name = atom->getAtomName();

    if(name == "N" && residue != "HOH" && residue != "PRO") return true;
    else{
        if(residue == "THR" && name == "OG1") return true;
        else if(residue == "TRP" && name == "NE1") return true;
        else if(residue == "GLN" && name == "NE2") return true;
        else if(residue == "LYS" && name == "NZ") return true;
        else if(residue == "SER" && name == "OG") return true;
        else if(residue == "TYR" && name == "OH") return true;
        else if(residue == "ASN" && name == "ND2") return true;
        else if(residue == "HIS" && (name == "ND1" || name == "NE2")) return true;
        else if(residue == "ARG" && (name == "NH1" || name == "NH2" || name == "NE")) return true;
    }

    return false;
}

bool Pdb::isHydrogenAcceptor(PdbAtom *atom){
    string residue = atom->getResidue();
    string name = atom->getAtomName();

    if(name == "O" && residue != "HOH") return true;
    else{
        if(residue == "CYS" && name == "SG") return true;
        else if(residue == "THR" && name == "OG1") return true;
        else if(residue == "GLN" && name == "OE1") return true;
        else if(residue == "GLU" && (name == "OE1" || name == "OE2")) return true;
        else if(residue == "MET" && name == "SD") return true;
        else if(residue == "SER" && name == "OG") return true;
        else if(residue == "TYR" && name == "OH") return true;
        else if(residue == "HIS" && (name == "ND1" || name == "NE2")) return true;
        else if(residue == "ASN" && name == "OD1") return true;
        else if(residue == "ASP" && (name == "OD1" || name == "OD2")) return true;
    }

    return false;
}

bool Pdb::isHydrophobic(PdbAtom *atom){
    string residue = atom->getResidue();
    string name = atom->getAtomName();

    if(residue == "ILE"){
        if(name == "CB" || name == "CD1" || name == "CG1" || name == "CG2") return true;
    }else if(residue == "VAL"){
        if(name == "CB" || name == "CG1" || name == "CG2") return true;
    }else if(residue == "LEU"){
        if(name == "CD1" || name == "CD2" || name == "CG" || name == "CE") return true;
    }else if(residue == "PHE"){
        if(name == "CB" || name == "CG" || name == "CD1" || name == "CE1" || name == "CZ" || name == "CE2" || name == "CD2") return true;
    }else if(residue == "CYS"){
        if(name == "CB") return true;
    }else if(residue == "MET"){
        if(name == "CB" || name == "CE") return true;
    }else if(residue == "ALA"){
        if(name == "CB") return true;
    }else if(residue == "THR"){
        if(name == "CG2") return true;
    }else if(residue == "TRP"){
        if(name == "CB" || name == "CG" || name == "CD2" || name == "CE3" || name == "CZ3" || name == "CH2" || name == "CZ2" || name == "CE2") return true;
    }else if(residue == "TYR"){
        if(name == "CB" || name == "CG" || name == "CD1" || name == "CE1" || name == "CZ" || name == "CE2" || name == "CD2") return true;
    }else if(residue == "PRO"){
        if(name == "CB" || name == "CG") return true;
    }else if(residue == "HIS"){
        if(name == "CB") return true;
    }else if(residue == "GLN"){
        if(name == "CB" || name == "CG") return true;
    }else if(residue == "ASN"){
        if(name == "CB") return true;
    }else if(residue == "GLU"){
        if(name == "CB") return true;
    }else if(residue == "ASP"){
        if(name == "CB") return true;
    }else if(residue == "LYS"){
        if(name == "CB" || name == "CG" || name == "CD") return true;
    }else if(residue == "ARG"){
        if(name == "CB" || name == "CG") return true;
    }
}


void Pdb::calculateInterations(){
    map<int,set<PdbAtom*> > bonded_list;
    vector<PdbPseudoAtom*> pseudoatoms;

    //#leitura dos pares de atomos ligados covalentemente
    for(unsigned int i = 0; i < atoms.size()-1; i++){
        for(unsigned int j = i+1; j < atoms.size(); j++){
            PdbAtom* atom1 = atoms[i];
            PdbAtom* atom2 = atoms[j];
            int pdbnum1 = atom1->getAtomNumber();
            int pdbnum2 = atom2->getAtomNumber();
            if(connectedAtoms(atom1,atom2)){
                bonded_list[pdbnum1].insert(atom2);
                bonded_list[pdbnum2].insert(atom1);
            }
        }
    }

    //#geracao dos centros aromaticos
    for(unsigned int i = 0; i < residues.size(); i++){
        PdbAtom* pre_ring_atom;
        vector<PdbAtom*> aromatics;
        PdbResidues* residue = residues[i];
        vector<PdbAtom*> residue_atoms = residue->getAtoms();
        string resname = residue->getResname();
        string flag = "";

        for(unsigned int j = 0; j < residue_atoms.size(); j++){
            PdbAtom* atom = residue_atoms[i];

            if(resname == "TYR" || resname == "PHE"){
                if(atom->getAtomName() == "CG" || atom->getAtomName() == "CD1" || atom->getAtomName() == "CD2" || atom->getAtomName() == "CE1" || atom->getAtomName() == "CE2" || atom->getAtomName() == "CZ")
                    aromatics.push_back(atom);
                if(atom->getAtomName() == "CG")
                    pre_ring_atom = atom;
            }else if(resname == "PRO"){
                if(atom->getAtomName() == "CA" || atom->getAtomName() == "CB" || atom->getAtomName() == "CG" || atom->getAtomName() == "CD")
                    aromatics.push_back(atom);
                if(atom->getAtomName() == "CA")
                    pre_ring_atom = atom;
            }else if(resname == "HIS"){
                if(atom->getAtomName() == "CG" || atom->getAtomName() == "ND1" || atom->getAtomName() == "CE1" || atom->getAtomName() == "NE2" || atom->getAtomName() == "CD2")
                    aromatics.push_back(atom);
                pre_ring_atom = atom;
        }else if(resname == "TRP"){
            if(atom->getAtomName() == "CG" || atom->getAtomName() == "CD1" || atom->getAtomName() == "NE1" || atom->getAtomName() == "CE2" || atom->getAtomName() == "CD2" || atom->getAtomName() == "CZ1" || atom->getAtomName() == "CH2" || atom->getAtomName() == "CZ3" || atom->getAtomName() == "CE3")
                aromatics.push_back(atom);
            if(atom->getAtomName() == "CD1")
                if(atom->getAtomName() == "CG")
                    pre_ring_atom = atom;
            }
        }

        if(aromatics.size() == 5){
            if(resname == "PRO") flag = "Pyrrolidine";
            else if(resname == "HIS") flag = "Imidazole";
        }else if(aromatics.size() == 6){
            if(resname == "TYR" || resname == "PHE") flag = "Phenyl";
        }if(aromatics.size() == 9 && resname == "TRP") flag = "Indol";

        if(flag != ""){
            PdbAtom* aromatic_atom = aromatics[0];
            int resnum = aromatic_atom->getResidueNumber();
            vector<float> coord = this->getMidpoints(aromatics);
            PdbPseudoAtom* pseudoatom = new PdbPseudoAtom(resnum,resname,i+1,flag,coord[0],coord[1],coord[2],aromatics,pre_ring_atom);
            pseudoatoms.push_back(pseudoatom);
            continue;
        }
    }

    //#calculo interacoes inter-atomicas nao covalentes
    for(unsigned int i = 0; i < atoms.size()-1; i++){
        for(unsigned int j = i+1; j < atoms.size(); j++){
            PdbAtom* atom1 = atoms[i];
            PdbAtom* atom2 = atoms[j];
            string atomname1 = atom1->getAtomName();
            string atomname2 = atom2->getAtomName();
            string resname1 = atom1->getResidue();
            string resname2 = atom2->getResidue();

            if(isValidResidue(resname1) && isValidResidue(resname2)){
                float dist = this->distance2atoms(atom1,atom2);
                if(dist <= 3 && atomname1 == "SG" && resname1 == "CYS" && atomname2 == "SG" && resname2 == "CYS"){
                    PdbInteraction *interaction = new Disulfide(atom1,atom2,dist);
                    interactions.push_back(interaction);
                }else if(dist <= 3.9 && isHydrogenAcceptor(atom1) && isHydrogenDonor(atom2)){
                    set<PdbAtom*> ant_acceptor = bonded_list[atom1->getAtomNumber()];
                    if(ant_acceptor.size() > 1){
                        string respos1 = resname1 + to_string(atom1->getResidueNumber());
                        string respos2 = resname2 + to_string(atom2->getResidueNumber());

                        if(respos1 == respos2){
                            if((atomname1 == "N" && atomname2 == "O") || (atomname2 == "N" && atomname1 == "O"))
                                continue;
                            if(resname1 == "ASN" && (atomname1 == "ND2" && atomname2 == "OD1") || (atomname2 == "ND2" && atomname1 == "OD1"))
                                continue;
                            if(resname1 == "GLN" && (atomname1 == "NE2" && atomname2 == "OE1") || (atomname2 == "NE2" && atomname1 == "OE1"))
                                continue;
                            if(resname1 == "HIS"){
                                if((atomname1 == "ND1" || atomname1 == "NE2") && (atomname2 == "ND1" || atomname2 == "NE2"))
                                    continue;
                            }
                        }
                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        PdbAtom* ant_acceptor2 = *std::next(ant_acceptor.begin(),1);
                        float ang1 = angle3atoms(atom1,ant_acceptor1,atom2);
                        float ang2 = angle3atoms(atom1,ant_acceptor2,atom2);
                        if(ang1 >= 90 || ang2 >= 90){
                            PdbInteraction *interaction = new Hidrogen(atom1,atom2,dist,ang1,ang2,ant_acceptor1,ant_acceptor2);
                            //if (new_obj.num_diff() >= 3): SERÁ MODIFICADO, NÃO FUNCIONANDO!!
                                interactions.push_back(interaction);
                        }
                    }else{
                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        float ang = angle3atoms(atom1,ant_acceptor1,atom2);
                        if(ang >= 90){
                            PdbInteraction *interaction = new Hidrogen(atom1,atom2,dist,ang,ant_acceptor1);
                            //if (new_obj.num_diff() >= 3): ERRADO
                                interactions.push_back(interaction);
                        }
                    }
                }else if(dist <= 3.9 && isHydrogenAcceptor(atom2) && isHydrogenDonor(atom1)){
                    set<PdbAtom*> ant_acceptor = bonded_list[atom2->getAtomNumber()];
                    if(ant_acceptor.size() > 1){
                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        PdbAtom* ant_acceptor2 = *std::next(ant_acceptor.begin(),1);
                        float ang1 = angle3atoms(atom2,ant_acceptor1,atom1);
                        float ang2 = angle3atoms(atom2,ant_acceptor2,atom1);
                        if(ang1 >= 90 || ang2 >= 90){
                            PdbInteraction *interaction = new Hidrogen(atom1,atom2,dist,ang1,ang2,ant_acceptor1,ant_acceptor2);
                            //if (new_obj.num_diff() >= 3): ERRADO
                                interactions.push_back(interaction);
                        }
                    }else{
                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        float ang = angle3atoms(atom2,ant_acceptor1,atom1);
                        if(ang >= 90){
                            PdbInteraction *interaction = new Hidrogen(atom1,atom2,dist,ang,ant_acceptor1);
                            //if (new_obj.num_diff() >= 3): ERRADO
                                interactions.push_back(interaction);
                        }
                    }
                }else if(dist <= 5 && isHydrophobic(atom1) && isHydrophobic(atom2)){
                    PdbInteraction *interaction = new Hydrofobic(atom1,atom2,dist);
                    interactions.push_back(interaction);
                }else if(dist <= 6 && ((isPositiveCharged(atom1) && isNegativeCharged(atom2)) || (isNegativeCharged(atom1) && isPositiveCharged(atom2)))){
                    PdbInteraction *interaction = new Ionic(atom1,atom2,dist);
                    interactions.push_back(interaction);
                }
            }
        }
    }

    //#definicao interacoes aromaticas
    for(unsigned int i = 0; i < atoms.size(); i++){
        for(unsigned int j = 0; j < pseudoatoms.size(); j++){
            PdbAtom* atom1 = atoms[i];
            PdbPseudoAtom* pseudoatom = pseudoatoms[j];
            if(atom1->getResidueNumber() != pseudoatom->getResidueNumber()){
                if(isValidResidue(atom1->getResidue())){
                    float dist = distance2atoms(atom1,pseudoatom);

                    if(dist <= 3.9 && isHydrogenDonor(atom1)){
                        float ang = angle3atoms(atom1,pseudoatom,pseudoatom->getPreRingAtpm());
                        if(ang <= 20){
                            PdbInteraction *interaction = new AromaticAmide(atom1,pseudoatom,dist,ang,j);
                            interactions.push_back(interaction);
                        }
                    }else if(dist <= 5.3 && atom1->getElement() == "S"){
                        PdbInteraction *interaction = new AromaticSulphur(atom1,pseudoatom,dist,j);
                        interactions.push_back(interaction);
                    }else if(dist <= 6 && isPositiveCharged(atom1)){
                        PdbInteraction *interaction = new CationPi(atom1,pseudoatom,dist,j);
                        interactions.push_back(interaction);
                    }
                }
            }
        }
    }

    for(unsigned int i = 0; i < pseudoatoms.size() -1; i++){
        for(unsigned int j = i + 1; j < pseudoatoms.size(); j++){
            PdbPseudoAtom *a1 = pseudoatoms[i];
            PdbPseudoAtom *a2 = pseudoatoms[j];
            float dist = distance2atoms(a1,a2);
            if(dist <= 7 && dist >= 4.5){
                PdbInteraction *interaction = new AromaticAromatic(a1,a2,dist,i,j);
                interactions.push_back(interaction);
            }
        }
    }
}

