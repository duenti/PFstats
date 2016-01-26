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
    char refseq_chain;
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
    char getRefseq_chain();
    void setRefseq_chain(char c);
    vector<PdbAtom*> getAllAtoms();
    vector<PdbAtom*> getAllAtoms(char chain);
    int countAtoms();
    void clearAtoms();
    PdbAtom* getAtom(int i);
    void addAtom(PdbAtom* atom);
    void setResiduesSeqNumber(char chain);
    vector<tuple<string,string> > getResiduesInContact(float dist, char chain);
    string getPDBSequence(char chain);
    bool SWSalign(int offset, char chain);
    string getSWSSeq(char chain);
    bool exportStructure(QString filepath, vector<float> bfactors, char chain);
    void printSeqNumbers();
};

#endif // PDB_H
