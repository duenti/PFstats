#include "pdbresidues.h"

PdbResidues::PdbResidues()
{
    alignPos = 0;
}

void PdbResidues::addAtom(PdbAtom *atom){
    atoms.push_back(atom);
}

vector<PdbAtom*> PdbResidues::getAtoms(){
    return atoms;
}

PdbAtom* PdbResidues::getAtom(int i){
    return atoms[i];
}

string PdbResidues::getResname(){
    PdbAtom* atom = atoms[0];
    return atom->getResidue();
}

char PdbResidues::getChain(){
    PdbAtom* atom = atoms[0];
    return atom->getChain();
}

char PdbResidues::getResidueCode(){
    PdbAtom* atom = atoms[0];
    return atom->getResidueCode();
}

int PdbResidues::getAlignPos(){
    return alignPos;
}

void PdbResidues::setAlignPos(int pos){
    alignPos = pos;
}

int PdbResidues::getResidueNumber(){
    PdbAtom* atom = atoms[0];
    return atom->getResidueNumber();
}
