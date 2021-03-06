#ifndef UNIPROT_H
#define UNIPROT_H

#include "feature.h"
#include <vector>

using namespace std;

class Uniprot
{
private:
    vector<string> accession;
    string name;
    string function;
    vector<Feature*> feats;
    int dataset; //0-SWISS, 1-TremBL

public:
    Uniprot();
    Uniprot(Uniprot &prot);
    Uniprot(string name, int dataset);
    Uniprot(string name, string function);
    ~Uniprot();
    void addAccession(string access);
    string getAcesssionAt(int i);
    vector<string> getAccessions();
    int countAccession();
    string getAccession(int i);
    int getAccessionSize();
    int getDataset();
    void setDataset(int v);
    string getName();
    void setName(string n);
    string getFunction();
    void setFunction(string func);
    void addFeature(Feature *f);
    int countFeatures();
    Feature* getFeature(int i);
    string toString();
    void kill();
};

#endif // UNIPROT_H
