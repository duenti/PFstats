#ifndef PDBINTERACTION_H
#define PDBINTERACTION_H

#include "pdbatom.h"
#include "pdbpseudoatom.h"

using namespace std;

class PdbInteraction
{
private:
    PdbAtom* atom1;
    PdbAtom* atom2;
    float distance;
public:
    PdbInteraction();
    PdbInteraction(float d);
    PdbInteraction(PdbAtom *a1, float d);
    PdbInteraction(PdbAtom* a1, PdbAtom* a2, float d);
    PdbAtom* getAtom1();
    PdbAtom* getAtom2();
    virtual string getType() = 0;
};

class Disulfide : public PdbInteraction
{
public:
    Disulfide(PdbAtom* a1, PdbAtom* a2, float d);
    string getType();
};

class Hydrogen : public PdbInteraction
{
private:
    float angle1, angle2;
    PdbAtom* antecessor1;
    PdbAtom* antecessor2;
public:
    Hydrogen(PdbAtom *a1, PdbAtom *a2, float d, float ang, PdbAtom *ant);
    Hydrogen(PdbAtom* a1, PdbAtom* a2, float d, float ang1, float ang2, PdbAtom* ant1, PdbAtom* ant2);
    string getType();
};

class Hydrofobic : public PdbInteraction
{
public:
    Hydrofobic(PdbAtom* a1, PdbAtom* a2, float d);
    string getType();
};

class Ionic : public PdbInteraction
{
public:
    Ionic(PdbAtom* a1, PdbAtom* a2, float d);
    string getType();
};

class AromaticAmide : public PdbInteraction
{
private:
    PdbPseudoAtom* aromaticAtom;
    int aro_num;
    float angle;

public:
    AromaticAmide(PdbAtom* a1, PdbPseudoAtom* a2, float d, float ang, int num);
    string getType();
};

class AromaticSulphur : public PdbInteraction
{
private:
    PdbPseudoAtom* aromaticAtom;
    int aro_num;
public:
    AromaticSulphur(PdbAtom* a1, PdbPseudoAtom* a2, float d, int num);
    string getType();
};

class CationPi : public PdbInteraction
{
private:
    PdbPseudoAtom* aromaticAtom;
    int aro_num;
public:
    CationPi(PdbAtom* a1, PdbPseudoAtom* a2, float d, int num);
    string getType();
};

class AromaticAromatic : public PdbInteraction
{
private:
    PdbPseudoAtom* aromaticAtom1;
    PdbPseudoAtom* aromaticAtom2;
    int aro_num1, aro_num2;
public:
    AromaticAromatic(PdbPseudoAtom* a1, PdbPseudoAtom* a2, float d, int num1, int num2);
    string getType();
};

#endif // PDBINTERACTION_H
