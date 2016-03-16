#ifndef PDBATOM_H
#define PDBATOM_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <QMessageBox>

using namespace std;

class PdbAtom
{
private:
    int atomNumber;
    string atomName;
    char alternateLocation;
    string residue;
    char chain;
    int residueNumber;
    char insertionResiduesCode;
    float x,y,z;
    float occ;
    float bfactor;
    string segmentIdentifier;
    string element;
    string charge;
    char residueCode;
    int seqnumber;

    char aa3lto1l(string res);


public:
    PdbAtom();
    PdbAtom(string line);
    PdbAtom(int atomNb, string atomNm, string residue, char chain, int resNum, float x, float y, float z, float occ, float b, string element, string charge);
    ~PdbAtom();
    int getAtomNumber();
    void setAtomNumber(int n);
    string getAtomName();
    void setAtomName(string name);
    string getResidue();
    void setResidue(string aa);
    char getChain();
    void setChain(char c);
    int getResidueNumber();
    void setResidueNumber(int n);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    float getZ();
    void setZ(float z);
    float getOcc();
    void setOcc(float occ);
    float getBfactor();
    void setBfactor(float bf);
    string getElement();
    void setElement(string ele);
    string getCharge();
    void setCharge(string c);
    char getResidueCode();
    void setResidueCode(char r);
    int getSeqnumber();
    void setSeqnumber(int n);
    string to_string(float bf);
};

#endif // PDBATOM_H
