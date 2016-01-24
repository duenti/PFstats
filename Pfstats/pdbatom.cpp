#include "pdbatom.h"

PdbAtom::PdbAtom()
{

}

PdbAtom::PdbAtom(string line){
    char c = ' ';
    string temp = "";

    //Atom Number
    for(int i = 6; i <= 10; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    this->atomNumber = stoi(temp);

    //Atom Name
    temp = "";
    for(int i = 12; i <= 15; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    this->atomName = temp;

    //Alternate Location Indicator
    this->alternateLocation = line[16];

    //Residue
    //temp = line[17] + line[18] + line[19];
    temp = line.substr(17,3);
    this->residue = temp;
    this->residueCode = aa3lto1l(temp);

    //Chain
    this->chain = line[21];

    //Residue Number
    temp = "";
    for(int i = 22; i <= 25; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    this->residueNumber = stoi(temp);

    //Code for insertion of residues
    this->insertionResiduesCode = line[26];

    //Position X
    temp = "";
    for(int i = 30; i <= 37; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    replace(temp.begin(),temp.end(),'.',',');
    this->x = atof(temp.c_str());

    //Position Y
    temp = "";
    for(int i = 38; i <= 45; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    replace(temp.begin(),temp.end(),'.',',');
    this->y = atof(temp.c_str());

    //Position Z
    temp = "";
    for(int i = 46; i <= 53; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    replace(temp.begin(),temp.end(),'.',',');
    this->z = atof(temp.c_str());

    //Occupancy
    temp = "";
    for(int i = 54; i <= 59; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    replace(temp.begin(),temp.end(),'.',',');
    this->occ = atof(temp.c_str());

    //B-factor
    temp = "";
    for(int i = 60; i <= 65; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    replace(temp.begin(),temp.end(),'.',',');
    this->bfactor = atof(temp.c_str());

    //Segment Identifier
    temp = "";
    for(int i = 72; i <= 75; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }
    this->segmentIdentifier = temp;

    //Element
    temp = "";
    for(int i = 76; i <= 77; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    this->element = temp;

    //Charge
    temp = "";
    for(int i = 78; i <= 79; i++){
        c = line[i];
        if(c != ' ') temp += c;
    }

    this->charge = temp;

    this->seqnumber = 0;

    //printf("%d %s %c %s %c %d %c %f %f %f %f %f %s %s %s\n",atomNumber,atomName.c_str(),alternateLocation,residue.c_str(),chain,residueNumber,insertionResiduesCode,x,y,z,occ,bfactor,segmentIdentifier.c_str(),element.c_str(),charge.c_str());
}

PdbAtom::PdbAtom(int atomNb, string atomNm, string residue, char chain, int resNum, float x, float y, float z, float occ, float b, string element, string charge){
    this->atomNumber = atomNb;
    this->atomName = atomNm;
    this->residue = residue;
    this->chain = chain;
    this->residueNumber = resNum;
    this->x = x;
    this->y = y;
    this->z = z;
    this->occ = occ;
    this->bfactor = b;
    this->element = element;
    this->charge = charge;
}

PdbAtom::~PdbAtom()
{

}

char PdbAtom::aa3lto1l(string res){
    if(res == "ARG") return 'R';
    else if(res == "HIS") return 'H';
    else if(res == "LYS") return 'K';
    else if(res == "ASP") return 'D';
    else if(res == "GLU") return 'E';
    else if(res == "SER") return 'S';
    else if(res == "THR") return 'T';
    else if(res == "ASN") return 'N';
    else if(res == "GLN") return 'Q';
    else if(res == "CYS") return 'C';
    else if(res == "SEC") return 'U';
    else if(res == "GLY") return 'G';
    else if(res == "PRO") return 'P';
    else if(res == "ALA") return 'A';
    else if(res == "VAL") return 'V';
    else if(res == "ILE") return 'I';
    else if(res == "LEU") return 'L';
    else if(res == "MET") return 'M';
    else if(res == "PHE") return 'F';
    else if(res == "TYR") return 'Y';
    else if(res == "TRP") return 'W';
}


int PdbAtom::getAtomNumber(){
    return this->atomNumber;
}

void PdbAtom::setAtomNumber(int n){
    this->atomNumber = n;
}

string PdbAtom::getAtomName(){
    return this->atomName;
}

void PdbAtom::setAtomName(string name){
    this->atomName = name;
}

string PdbAtom::getResidue(){
    return this->residue;
}

void PdbAtom::setResidue(string aa){
    this->residue = aa;
}

char PdbAtom::getChain(){
    return this->chain;
}

void PdbAtom::setChain(char c){
    this->chain = c;
}

int PdbAtom::getResidueNumber(){
    return this->residueNumber;
}

void PdbAtom::setResidueNumber(int n){
    this->residueNumber = n;
}

float PdbAtom::getX(){
    return this->x;
}

void PdbAtom::setX(float x){
    this->x = x;
}

float PdbAtom::getY(){
    return this->y;
}

void PdbAtom::setY(float y){
    this->y = y;
}

float PdbAtom::getZ(){
    return this->z;
}

void PdbAtom::setZ(float z){
    this->z = z;
}

float PdbAtom::getOcc(){
    return this->occ;
}

void PdbAtom::setOcc(float occ){
    this->occ = occ;
}

float PdbAtom::getBfactor(){
    return this->bfactor;
}

void PdbAtom::setBfactor(float bf){
    this->bfactor = bf;
}

string PdbAtom::getElement(){
    return this->element;
}

void PdbAtom::setElement(string ele){
    this->element = ele;
}

string PdbAtom::getCharge(){
    return this->charge;
}

void PdbAtom::setCharge(string c){
    this->charge = c;
}

char PdbAtom::getResidueCode(){
    return this->residueCode;
}

void PdbAtom::setResidueCode(char r){
    this->residueCode = r;
}

int PdbAtom::getSeqnumber(){
    return this->seqnumber;
}

void PdbAtom::setSeqnumber(int n){
    this->seqnumber = n;
}

string PdbAtom::to_string(float bf){
    string line = "ATOM  ";
    string temp;

    //ATOM NUMBER
    temp = std::to_string(this->atomNumber);

    switch(temp.size()){
    case 0:
    {
        line += "     ";
        break;
    }
    case 1:
    {
        line += "    " + temp;
        break;
    }
    case 2:
    {
        line += "   " + temp;
        break;
    }
    case 3:
    {
        line += "  " + temp;
        break;
    }
    case 4:
    {
        line += " " + temp;
        break;
    }
    case 5:
    {
        line += temp;
        break;
    }
    }

    line += "  ";

    //ATOM NAME
    switch(this->atomName.size()){
    case 0:
    {
        line += "   ";
        break;
    }
    case 1:
    {
        line += this->atomName + "  ";
        break;
    }
    case 2:
    {
        line += this->atomName + " ";
        break;
    }
    case 3:
    {
        line += this->atomName;
        break;
    }
    }

    //ALTERNATE LOCATION INDICATOR
    line += this->alternateLocation;

    //RESIDUE NAME
    line += this->residue;

    line += " ";

    //CHAIN
    line += this->chain;

    //RESIDUE SEQUENCE NUMBER
    temp = std::to_string(this->residueNumber);

    switch(temp.size()){
    case 0:
    {
        line += "    ";
        break;
    }
    case 1:
    {
        line += "   " + temp;
        break;
    }
    case 2:
    {
        line += "  " + temp;
        break;
    }
    case 3:
    {
        line += " " + temp;
        break;
    }
    case 4:
    {
        line += temp;
        break;
    }
    }

    //CODE FOR INSERTION OF RESIDUES
    line += this->insertionResiduesCode;

    line += "   ";

    //X
    stringstream stream;
    stream << fixed << setprecision(3) << this->x;
    temp = stream.str();

    switch(temp.size()){
    case 5:
    {
        line += "   " + temp;
        break;
    }
    case 6:
    {
        line += "  " + temp;
        break;
    }
    case 7:
    {
        line += " " + temp;
        break;
    }
    case 8:
    {
        line += temp;
        break;
    }
    }

    //Y
    stringstream stream2;
    stream2 << fixed << setprecision(3) << this->y;
    temp = stream2.str();

    switch(temp.size()){
    case 5:
    {
        line += "   " + temp;
        break;
    }
    case 6:
    {
        line += "  " + temp;
        break;
    }
    case 7:
    {
        line += " " + temp;
        break;
    }
    case 8:
    {
        line += temp;
        break;
    }
    }

    //Z
    stringstream stream3;
    stream3 << fixed << setprecision(3) << this->z;
    temp = stream3.str();

    switch(temp.size()){
    case 5:
    {
        line += "   " + temp;
        break;
    }
    case 6:
    {
        line += "  " + temp;
        break;
    }
    case 7:
    {
        line += " " + temp;
        break;
    }
    case 8:
    {
        line += temp;
        break;
    }
    }

    //OCCUPANCY
    stringstream stream4;
    stream4 << fixed << setprecision(2) << this->occ;
    temp = stream4.str();

    switch(temp.size()){
    case 4:
    {
        line += "  " + temp;
        break;
    }
    case 5:
    {
        line += " " + temp;
        break;
    }
    case 6:
    {
        line += temp;
        break;
    }
    }

    //B-FACTOR (SUBSTITUTE)
    stringstream stream5;
    stream5 << fixed << setprecision(2) << bf;
    temp = stream5.str();

    switch(temp.size()){
    case 4:
    {
        line += "  " + temp;
        break;
    }
    case 5:
    {
        line += " " + temp;
        break;
    }
    case 6:
    {
        line += temp;
        break;
    }
    }

    line += "      ";

    //SEGMENT IDENTIFIER
    switch(this->segmentIdentifier.size()){
    case 0:
    {
        line += "    ";
        break;
    }
    case 1:
    {
        line += this->segmentIdentifier + "   ";
        break;
    }
    case 2:
    {
        line += this->segmentIdentifier + "  ";
        break;
    }
    case 3:
    {
        line += this->segmentIdentifier + " ";
        break;
    }
    case 4:
    {
        line += this->segmentIdentifier;
        break;
    }
    }

    //ELEMENT SYMBOL
    switch(this->element.size()){
    case 0:
    {
        line += "  ";
        break;
    }
    case 1:
    {
        line += " " + this->element;
        break;
    }
    case 2:
    {
        line += this->element;
        break;
    }
    }

    //CHARGE OF ELEMENT
    switch(this->charge.size()){
    case 0:
    {
        line += "  ";
        break;
    }
    case 1:
    {
        line += " " + this->charge;
        break;
    }
    case 2:
    {
        line += this->charge;
        break;
    }
    }

    return line;
}
