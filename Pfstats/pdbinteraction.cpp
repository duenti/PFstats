#include "pdbinteraction.h"

PdbInteraction::PdbInteraction()
{

}

PdbInteraction::PdbInteraction(PdbAtom *a1, PdbAtom *a2, float d){
    atom1 = a1;
    atom2 = a2;
    distance = d;
}

PdbInteraction::PdbInteraction(PdbAtom *a1, float d){
    atom1 = a1;
    atom2 = NULL;
    distance = d;
}

PdbInteraction::PdbInteraction(float d){
    atom1 = NULL;
    atom2 = NULL;
    distance = d;
}

PdbAtom* PdbInteraction::getAtom1(){
    return atom1;
}

PdbAtom* PdbInteraction::getAtom2(){
    return atom2;
}

Disulfide::Disulfide(PdbAtom *a1, PdbAtom *a2, float d) : PdbInteraction(a1,a2,d){

}

string Disulfide::getType(){
    return "disulfide";
}

Hydrogen::Hydrogen(PdbAtom *a1, PdbAtom *a2, float d, float ang, PdbAtom *ant) : PdbInteraction(a1,a2,d){
    angle1 = ang;
    angle2 = 0;
    antecessor1 = ant;
    antecessor2 = NULL;
}

Hydrogen::Hydrogen(PdbAtom *a1, PdbAtom *a2, float d, float ang1, float ang2, PdbAtom *ant1, PdbAtom *ant2) : PdbInteraction(a1,a2,d){
    angle1 = ang1;
    angle2 = ang2;
    antecessor1 = ant1;
    antecessor2 = ant2;
}

string Hydrogen::getType(){
    return "hydrogen";
}

Hydrofobic::Hydrofobic(PdbAtom *a1, PdbAtom *a2, float d) : PdbInteraction(a1,a2,d){

}

string Hydrofobic::getType(){
    return "hydrofobic";
}

Ionic::Ionic(PdbAtom *a1, PdbAtom *a2, float d) : PdbInteraction(a1,a2,d){

}

string Ionic::getType(){
    return "ionic";
}

AromaticAmide::AromaticAmide(PdbAtom *a1, PdbPseudoAtom *a2, float d, float ang, int num) : PdbInteraction(a1,d){
    angle = ang;
    aromaticAtom = a2;
    aro_num = num;
}

string AromaticAmide::getType(){
    return "amide-pi";
}

AromaticSulphur::AromaticSulphur(PdbAtom *a1, PdbPseudoAtom *a2, float d, int num) : PdbInteraction(a1,d){
    aromaticAtom = a2;
    aro_num = num;
}

string AromaticSulphur::getType(){
    return "sulphur-pi";
}

CationPi::CationPi(PdbAtom *a1, PdbPseudoAtom *a2, float d, int num) : PdbInteraction(a1,d){
    aromaticAtom = a2;
    aro_num = num;
}

string CationPi::getType(){
    return "cation-pi";
}

AromaticAromatic::AromaticAromatic(PdbPseudoAtom *a1, PdbPseudoAtom *a2, float d, int num1, int num2) : PdbInteraction(d){
    aromaticAtom1 = a1;
    aromaticAtom2 = a2;
    aro_num1 = num1;
    aro_num2 = num2;
}

string AromaticAromatic::getType(){
    return "pi-pi";
}
