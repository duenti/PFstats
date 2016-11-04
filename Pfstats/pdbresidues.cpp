#include "pdbresidues.h"

PdbResidues::PdbResidues()
{
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
