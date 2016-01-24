#ifndef PDB_H
#define PDB_H

#include <set>
#include <string>
#include <vector>
#include "pdbatom.h"
#include <iostream>
#include <fstream>
#include <QObject>
#include <vector>
#include <tuple>
#include <algorithm>
#include <QtNetwork>
#include <QMessageBox>

using namespace std;

class Pdb
{
private:
    string id;
    float resolution;
    int interval1, interval2;
    string refseq;
    string header, footer;
    vector<PdbAtom*> atoms;
    vector<string> split(string text, char sep);

public:
    Pdb(string pdb);
    Pdb(QString filepath);
    ~Pdb();
    string getId();
    void setId(string id);
    float getResolution();
    void setResolution(float res);
    int getInterval1();
    int getInterval2();
    void setIntervals(int i1, int i2);
    string getRefseq();
    void setRefseq(string seq);
    vector<PdbAtom*> getAllAtoms();
    int countAtoms();
    void clearAtoms();
    PdbAtom* getAtom(int i);
    void addAtom(PdbAtom* atom);
    void setResiduesSeqNumber();
    vector<tuple<string,string> > getResiduesInContact(float dist);
    string getPDBSequence();
    bool SWSalign(int offset);
    string getSWSSeq();
    bool exportStructure(QString filepath, vector<float> bfactors);
    void printSeqNumbers();
};

#endif // PDB_H
