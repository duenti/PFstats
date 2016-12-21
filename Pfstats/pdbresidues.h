#ifndef PDBRESIDUES_H
#define PDBRESIDUES_H

#include "pdbatom.h";

using namespace std;

class PdbResidues
{
private:
    vector<PdbAtom*> atoms;
    int alignPos;

public:
    PdbResidues();
    void addAtom(PdbAtom* atom);
    vector<PdbAtom*> getAtoms();
    PdbAtom* getAtom(int i);
    string getResname();
    char getChain();
    char getResidueCode();
    int getAlignPos();
    void setAlignPos(int pos);
    int getResidueNumber();
};

#endif // PDBRESIDUES_H
