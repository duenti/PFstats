#ifndef PDB_H
#define PDB_H

#include <set>
#include <string>
#include <vector>
#include "pdbatom.h"
#include "pdbresidues.h"
#include "pdbpseudoatom.h"
#include "pdbinteraction.h"
#include <iostream>
#include <fstream>
#include <QObject>
#include <vector>
#include <tuple>
#include <algorithm>
#include <QtNetwork>
#include <QMessageBox>
#include <stack>
#include <QApplication>
#include <QProgressDialog>

using namespace std;

class Pdb
{
private:
    bool windows;
    string id;
    float resolution;
    string refseq;
    int refseq_id;
    char refseq_chain;
    string header, footer;
    vector<PdbAtom*> atoms;
    vector<PdbResidues*> residues;
    vector<PdbInteraction*> interactions;
    vector<string> split(string text, char sep);
    float distance2atoms(PdbAtom* a1, PdbAtom* a2);
    float distance2atoms(PdbAtom* a1, PdbPseudoAtom* a2);
    float distance2atoms(PdbPseudoAtom *a1, PdbPseudoAtom *a2);
    float angle3atoms(PdbAtom* a1, PdbAtom* a2, PdbAtom* a3);
    float angle3atoms(PdbAtom *a1, PdbPseudoAtom *a2, PdbAtom *a3);
    bool connectedAtoms(PdbAtom* a1, PdbAtom* a2);
    vector<float> getMidpoints(vector<PdbAtom*> atom_list);
    bool isValidResidue(string res);
    bool isPositiveCharged(PdbAtom* atom);
    bool isNegativeCharged(PdbAtom* atom);
    bool isHydrogenAcceptor(PdbAtom* atom);
    bool isHydrogenDonor(PdbAtom* atom);
    bool isHydrophobic(PdbAtom* atom);

public:
    Pdb(string pdb, bool win);
    Pdb(QString filepath, bool win);
    Pdb();
    ~Pdb();
    int getRefSeqId();
    void setRefSeqId(int ref);
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
    int countResidues();
    void clearResidues();
    PdbResidues* getResidue(int i);
    void setResiduesSeqNumber(char chain);
    int setResiduesSeqNumber(string pfamsequence, char chain, string fullSeq);
    string getPDBSequence(char chain);
    bool exportStructure(QString filepath, vector<tuple<int,float> > bfactors, char chain);
    tuple<string, string, int> needleman_wunsch(string a, string b); //ALIGN_A, ALIGN_B, SCORE
    void calculateInterations();
};

#endif // PDB_H
