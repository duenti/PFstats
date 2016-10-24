#include "pdbpseudoatom.h"

PdbPseudoAtom::PdbPseudoAtom()
{

}

PdbPseudoAtom::PdbPseudoAtom(int resnum, string resname, int pdbresnum, string ringtype, float x, float y, float z, vector<PdbAtom *> ringatoms, PdbAtom *prering){
    this->res_num = resnum;
    this->res_type = resname;
    this->pdbres_num = pdbresnum;
    this->ring_type = ringtype;
    this->ring_x = x;
    this->ring_y = y;
    this->ring_z = z;
    this->ring_atoms = ringatoms;
    this->pre_ring_atom = prering;
}

int PdbPseudoAtom::getResidueNumber(){
    return this->res_num;
}

float PdbPseudoAtom::getX(){
    return ring_x;
}

float PdbPseudoAtom::getY(){
    return ring_y;
}

float PdbPseudoAtom::getZ(){
    return ring_z;
}

PdbAtom* PdbPseudoAtom::getPreRingAtpm(){
    return pre_ring_atom;
}
