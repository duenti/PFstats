#include "pdb.h"

Pdb::Pdb(){
    id = "nothing";
}

Pdb::Pdb(string pdb, bool win){
    windows = win;
    vector<string> lines = split(pdb,'\n');
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
            if(!windows)
                replace(temp.begin(),temp.end(),'.',',');
            this->resolution = atof(temp.c_str());
            //printf("%s - %f",temp.c_str(),resolution);
        }else if(lines[i].substr(0,4) == "ATOM")
            break;
        header += lines[i] + "\n";
    }

    bool NTerminal = true;
    PdbAtom *firstatom = new PdbAtom(lines[i],windows);
    int currentPos = firstatom->getResidueNumber();
    PdbResidues *residue = new PdbResidues();
    for(i; i < lines.size(); i++){
        if(lines[i].substr(0,4) == "ATOM"){
            PdbAtom *atom = new PdbAtom(lines[i],windows);
            if(NTerminal && atom->getAtomName() == "N"){
                atom->setAtomName("NmH2");
                NTerminal = false;
            }
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

Pdb::Pdb(QString filepath, bool win){
    windows = win;
    string line;
    this->resolution = 0;
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
            if(!windows)
                replace(temp.begin(),temp.end(),'.',',');
            this->resolution = atof(temp.c_str());
        }else if(line.substr(0,4) == "ATOM"){
            if(isfirstatom){
                PdbAtom *atom = new PdbAtom(line,windows);
                currentPos = atom->getResidueNumber();
                        isfirstatom = false;
            }
            PdbAtom *atom = new PdbAtom(line,windows);
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

int Pdb::getRefSeqId(){
    return refseq_id;
}

void Pdb::setRefSeqId(int ref){
    refseq_id = ref;
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

int Pdb::countResidues(){
    return residues.size();
}

void Pdb::clearResidues(){
    residues.clear();
}

PdbResidues* Pdb::getResidue(int i){
    return residues[i];
}

//Não requer intervalos
int Pdb::setResiduesSeqNumber(string pfamsequence, char chain, string fullSeq){
    string pdbsequence = this->getPDBSequence(chain);
    //printf("%s %s",pfamsequence.c_str(),pdbsequence.c_str());
    tuple<string,string,int> tup = needleman_wunsch(pfamsequence,pdbsequence);
    string alignedPFAM = get<0>(tup);
    string alignedPDB = get<1>(tup);
    int score = get<2>(tup);
    int count = 0; //Contador de alignedPFAM e alignedPBD
    int count2 = 0; //contador da seq PDB (residuo)

    for(unsigned int i = 0; i < fullSeq.size(); i++){
        if(fullSeq[i] != '-'){
            //sincroniza fullSeq com alignedpfam
            while(alignedPFAM[count] != fullSeq[i]){
                if(alignedPDB[count] != '-') count2++;

                count++;
            }

            if(alignedPDB[count] == alignedPFAM[count]){
                if(count2 < residues.size()){
                    PdbResidues* res = residues[count2];
                    res->setAlignPos(i+1);
                    count2++;
                    count++;
                }
            }else{
                if(alignedPDB[count] != '-') count2++;

                count++;
            }
        }
    }

    return score;

    //Remover seqnumber depois
}

/*
//OLD
//Não requer intervalos
int Pdb::setResiduesSeqNumber(string pfamsequence, char chain, string fullseq){

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
*/

string Pdb::getPDBSequence(char chain){
    string sequence = "";

    for(unsigned int i = 0; i < residues.size(); i++){
        PdbResidues* res = residues[i];
        if(res->getChain() == chain)
            sequence += res->getResidueCode();
    }

    return sequence;
}

/*//OLD
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
*/

bool Pdb::exportStructure(QString filepath, vector<tuple<int,float> > bfactors, char chain){
    //Salva em arquivo
    QFile f(filepath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&f);

    out << this->header.c_str();

    for(unsigned int i = 0; i < residues.size(); i++){
        PdbResidues* residue = residues[i];
        float bf = 0.0;
        if(residue->getChain() == chain){
            for(unsigned int j = 0; j < bfactors.size(); j++){
                tuple<int,float> tup = bfactors[j];
                int anumber = get<0>(tup);
                if(anumber == residue->getAlignPos()){
                    bf = get<1>(tup)*100.0;
                    break;
                }
            }
        }
        vector<PdbAtom*> atoms = residue->getAtoms();
        for(unsigned int j = 0; j < atoms.size(); j++){
            PdbAtom* atom = atoms[j];
            out << atom->to_string(bf).c_str() << "\n";
        }
    }

    out << this->footer.c_str();

    f.close();
}

tuple<string,string,int> Pdb::needleman_wunsch(string a, string b){
    tuple<string,string,int> tup(a,b,0);
    //int dp[1001][1001];
    int n = a.size();
    int m = b.size();
    //vector<vector<int> > dp(1001,vector<int>(1001,0));
    vector<vector<int> > dp((n+1),vector<int>((m+1),0));
    int match_score = 2;
    int mismatch_score = 1;
    int gap_score = 1;

    //if(n > 1000 || m > 1000) return tup;

    for(unsigned int i = 0; i <= n; i++){
        dp[i][0] = i * -1 * gap_score;
    }

    for(unsigned int i = 0; i <= m; i++){
        dp[0][i] = i * -1 * gap_score;
    }

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
        char tempA = SA.top();
        char tempB = SB.top();
        retA += tempA;
        retB += tempB;
        SA.pop();
        SB.pop();
    }

    get<0>(tup) = retA;
    get<1>(tup) = retB;

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
    float ABx = a2->getX() - a1->getX();
    float ABy = a2->getY() - a1->getY();
    float ABz = a2->getZ() - a1->getZ();
    float BCx = a3->getX() - a2->getX();
    float BCy = a3->getY() - a2->getY();
    float BCz = a3->getZ() - a2->getZ();
    float ABvec = sqrt(ABx*ABx + ABy*ABy + ABz*ABz);
    float BCvec = sqrt(BCx*BCx + BCy*BCy + BCz*BCz);
    float ABnormalX = ABx/ABvec;
    float ABnormalY = ABy/ABvec;
    float ABnormalZ = ABz/ABvec;
    float BCnormalX = BCx/BCvec;
    float BCnormalY = BCy/BCvec;
    float BCnormalZ = BCz/BCvec;
    float result = ABnormalX*BCnormalX + ABnormalY*BCnormalY + ABnormalZ*BCnormalZ;
    //printf("%f\n",acos(result)*180/3.141592653589793);
    return acos(result)*180/3.141592653589793;
}

float Pdb::angle3atoms(PdbAtom *a1, PdbPseudoAtom *a2, PdbAtom *a3){
    float ABx = a1->getX() - a2->getX();
    float ABy = a1->getY() - a2->getY();
    float ABz = a1->getZ() - a2->getZ();
    float BCx = a3->getX() - a2->getX();
    float BCy = a3->getY() - a2->getY();
    float BCz = a3->getZ() - a2->getZ();
    float ABvec = sqrt(ABx*ABx + ABy*ABy + ABz*ABz);
    float BCvec = sqrt(BCx*BCx + BCy*BCy + BCz*BCz);
    float ABnormalX = ABx/ABvec;
    float ABnormalY = ABy/ABvec;
    float ABnormalZ = ABz/ABvec;
    float BCnormalX = BCx/BCvec;
    float BCnormalY = BCy/BCvec;
    float BCnormalZ = BCz/BCvec;
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
        else if(residue == "ARG" && (name == "NH1" || name == "NE" || name == "NH2")) return true;
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

    if(name == "N" && residue != "PRO") return true;
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

    if(name == "O") return true;
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

    return false;
}


void Pdb::calculateInterations(){
    map<int,set<PdbAtom*> > bonded_list;
    vector<PdbPseudoAtom*> pseudoatoms;

    QProgressDialog progress("Reading covalent bonded atoms pairs...(1/4)", "Abort", 0,atoms.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );

    //#leitura dos pares de atomos ligados covalentemente
    for(unsigned int i = 0; i < atoms.size()-1; i++){
        progress.setValue(i);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled());

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

    progress.setLabelText("Calculating aromatic centers...(2/4)");
    progress.setValue(0);
    progress.setMaximum(residues.size());

    //#geracao dos centros aromaticos
    for(unsigned int i = 0; i < residues.size(); i++){
        progress.setValue(i);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return;

        PdbAtom* pre_ring_atom;
        vector<PdbAtom*> aromatics;
        PdbResidues* residue = residues[i];
        vector<PdbAtom*> residue_atoms = residue->getAtoms();
        string resname = residue->getResname();
        string flag = "";

        for(unsigned int j = 0; j < residue_atoms.size(); j++){
            PdbAtom* atom = residue_atoms[j];

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

    progress.setLabelText("Calculating non-covalent interatomics bonds...(3/4)");
    progress.setValue(0);
    progress.setMaximum(atoms.size()-1);

    //#calculo interacoes inter-atomicas nao covalentes
    for(unsigned int i = 0; i < atoms.size()-1; i++){
        progress.setValue(i);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return;

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
                            if(resname1 == "ASN" && ((atomname1 == "ND2" && atomname2 == "OD1") || (atomname2 == "ND2" && atomname1 == "OD1")))
                                continue;
                            if(resname1 == "GLN" && ((atomname1 == "NE2" && atomname2 == "OE1") || (atomname2 == "NE2" && atomname1 == "OE1")))
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
                            PdbInteraction *interaction = new Hydrogen(atom1,atom2,dist,ang1,ang2,ant_acceptor1,ant_acceptor2);
                            printf("%s%d(%s) - %s%d(%s)\n",atom1->getResidue().c_str(),atom1->getResidueNumber(),atom1->getAtomName().c_str(),atom2->getResidue().c_str(),atom2->getResidueNumber(),atom2->getAtomName().c_str());
                            interactions.push_back(interaction);
                        }
                    }else{
                        string respos1 = resname1 + to_string(atom1->getResidueNumber());
                        string respos2 = resname2 + to_string(atom2->getResidueNumber());

                        if(respos1 == respos2){
                            if((atomname1 == "N" && atomname2 == "O") || (atomname2 == "N" && atomname1 == "O"))
                                continue;
                            if(resname1 == "ASN" && ((atomname1 == "ND2" && atomname2 == "OD1") || (atomname2 == "ND2" && atomname1 == "OD1")))
                                continue;
                            if(resname1 == "GLN" && ((atomname1 == "NE2" && atomname2 == "OE1") || (atomname2 == "NE2" && atomname1 == "OE1")))
                                continue;
                            if(resname1 == "HIS"){
                                if((atomname1 == "ND1" || atomname1 == "NE2") && (atomname2 == "ND1" || atomname2 == "NE2"))
                                    continue;
                            }
                        }

                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        float ang = angle3atoms(atom1,ant_acceptor1,atom2);
                        if(ang >= 90){
                            PdbInteraction *interaction = new Hydrogen(atom1,atom2,dist,ang,ant_acceptor1);
                            printf("%s%d(%s) - %s%d(%s)\n",atom1->getResidue().c_str(),atom1->getResidueNumber(),atom1->getAtomName().c_str(),atom2->getResidue().c_str(),atom2->getResidueNumber(),atom2->getAtomName().c_str());
                            interactions.push_back(interaction);
                        }
                    }
                }else if(dist <= 3.9 && isHydrogenAcceptor(atom2) && isHydrogenDonor(atom1)){
                    string respos1 = resname1 + to_string(atom1->getResidueNumber());
                    string respos2 = resname2 + to_string(atom2->getResidueNumber());

                    if(respos1 == respos2){
                        if((atomname1 == "N" && atomname2 == "O") || (atomname2 == "N" && atomname1 == "O"))
                            continue;
                        if(resname1 == "ASN" && ((atomname1 == "ND2" && atomname2 == "OD1") || (atomname2 == "ND2" && atomname1 == "OD1")))
                            continue;
                        if(resname1 == "GLN" && ((atomname1 == "NE2" && atomname2 == "OE1") || (atomname2 == "NE2" && atomname1 == "OE1")))
                            continue;
                        if(resname1 == "HIS"){
                            if((atomname1 == "ND1" || atomname1 == "NE2") && (atomname2 == "ND1" || atomname2 == "NE2"))
                                continue;
                        }
                    }

                    set<PdbAtom*> ant_acceptor = bonded_list[atom2->getAtomNumber()];
                    if(ant_acceptor.size() > 1){
                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        PdbAtom* ant_acceptor2 = *std::next(ant_acceptor.begin(),1);
                        float ang1 = angle3atoms(atom2,ant_acceptor1,atom1);
                        float ang2 = angle3atoms(atom2,ant_acceptor2,atom1);
                        if(ang1 >= 90 || ang2 >= 90){
                            PdbInteraction *interaction = new Hydrogen(atom1,atom2,dist,ang1,ang2,ant_acceptor1,ant_acceptor2);
                            printf("%s%d(%s) - %s%d(%s)\n",atom1->getResidue().c_str(),atom1->getResidueNumber(),atom1->getAtomName().c_str(),atom2->getResidue().c_str(),atom2->getResidueNumber(),atom2->getAtomName().c_str());
                            interactions.push_back(interaction);
                        }
                    }else{
                        string respos1 = resname1 + to_string(atom1->getResidueNumber());
                        string respos2 = resname2 + to_string(atom2->getResidueNumber());

                        if(respos1 == respos2){
                            if((atomname1 == "N" && atomname2 == "O") || (atomname2 == "N" && atomname1 == "O"))
                                continue;
                            if(resname1 == "ASN" && ((atomname1 == "ND2" && atomname2 == "OD1") || (atomname2 == "ND2" && atomname1 == "OD1")))
                                continue;
                            if(resname1 == "GLN" && ((atomname1 == "NE2" && atomname2 == "OE1") || (atomname2 == "NE2" && atomname1 == "OE1")))
                                continue;
                            if(resname1 == "HIS"){
                                if((atomname1 == "ND1" || atomname1 == "NE2") && (atomname2 == "ND1" || atomname2 == "NE2"))
                                    continue;
                            }
                        }

                        PdbAtom* ant_acceptor1 = *std::next(ant_acceptor.begin(),0);
                        float ang = angle3atoms(atom2,ant_acceptor1,atom1);
                        if(ang >= 90){
                            PdbInteraction *interaction = new Hydrogen(atom1,atom2,dist,ang,ant_acceptor1);
                            printf("%s%d(%s) - %s%d(%s)\n",atom1->getResidue().c_str(),atom1->getResidueNumber(),atom1->getAtomName().c_str(),atom2->getResidue().c_str(),atom2->getResidueNumber(),atom2->getAtomName().c_str());
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

    progress.setLabelText("Calculating aromatic bonds...(4/4)");
    progress.setValue(0);
    progress.setMaximum(atoms.size()+pseudoatoms.size());

    //#definicao interacoes aromaticas
    for(unsigned int i = 0; i < atoms.size(); i++){
        progress.setValue(i);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return;

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
                    }else if(dist <= 6.0 && isPositiveCharged(atom1)){
                        PdbInteraction *interaction = new CationPi(atom1,pseudoatom,dist,j);
                        //printf("%s%d(%s)-%d\n",atom1->getResidue().c_str(),atom1->getResidueNumber(),atom1->getAtomName().c_str(),pseudoatom->getResidueNumber());
                        interactions.push_back(interaction);
                    }
                }
            }
        }
    }

    for(unsigned int i = 0; i < pseudoatoms.size() -1; i++){
        progress.setValue(atoms.size()+ i);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return;

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


    //TEMP
    int disulfide = 0;
    int hydrogen = 0;
    int hydrofobic = 0;
    int ionic = 0;
    int amidepi = 0;
    int sulphurpi = 0;
    int cationpi = 0;
    int pipi = 0;
    int unknown = 0;
    for(unsigned int i = 0; i < interactions.size(); i++){
        PdbInteraction* inte = interactions[i];
        string type = inte->getType();

        if(type == "disulfide") disulfide++;
        else if(type == "hydrogen") hydrogen++;
        else if(type == "ionic") ionic++;
        else if(type == "hydrofobic") hydrofobic++;
        else if(type == "amide-pi") amidepi++;
        else if(type == "sulphur-pi") sulphurpi++;
        else if(type == "cation-pi") cationpi++;
        else if(type == "pi-pi") pipi++;
        else unknown++;
    }
    printf("DISULFIDE: %d\n",disulfide);
    printf("HYDROGEN: %d\n",hydrogen);
    printf("HYDROFOBIC: %d\n",hydrofobic);
    printf("IONIC: %d\n",ionic);
    printf("AMIDE-PI: %d\n",amidepi);
    printf("SULPHUR-PI: %d\n",sulphurpi);
    printf("CATION-PI: %d\n",cationpi);
    printf("PI-PI: %d\n",pipi);
    printf("UNKNOWN: %d\n",unknown);

    progress.close();
}

