#ifndef PDBPSEUDOATOM_H
#define PDBPSEUDOATOM_H

#include "pdbatom.h"

using namespace std;

class PdbPseudoAtom
{
private:
    int res_num;
    string res_type;
    int pdbres_num;
    string ring_type;
    float ring_x;
    float ring_y;
    float ring_z;
    vector<PdbAtom*> ring_atoms;
    PdbAtom* pre_ring_atom;
public:
    PdbPseudoAtom();
    PdbPseudoAtom(int resnum, string resname, int pdbresnum, string ringtype, float x, float y, float z, vector<PdbAtom*> ringatoms, PdbAtom* prering);
    int getResidueNumber();
    float getX();
    float getY();
    float getZ();
    PdbAtom* getPreRingAtpm();
};

#endif // PDBPSEUDOATOM_H
