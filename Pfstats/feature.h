#ifndef FEATURE_H
#define FEATURE_H

#include <string>

using namespace std;

class Feature
{
private:
    string type;
    string description;
    int position;
    int begin;
    int end;
    string id;
    string original;
    string variation;
    string residueColigated;//SeqNumber
    string residueColigatedAlign; //AlignNumber
    int aggregate; //-1: NOT AGGREGATED, 0: CONS, N > 0: N OF COMM

public:
    Feature();
    ~Feature();
    string getType();
    void setType(string t);
    string getDescription();
    void setDescription(string d);
    int getPosition();
    void setPosition(int p);
    int getBegin();
    void setBegin(int p);
    int getEnd();
    void setEnd(int p);
    string getId();
    void setId(string id);
    string getOriginal();
    void setOriginal(string r);
    string getVariation();
    void setVariation(string r);
    int getAgregate();
    void setAggregation(int v);
    string getResidueColigated();
    void setResidueColigated(string res);
    string getAlignResidue();
    void setAlignResidue(string pos);
    string toString();
    void kill();
};

#endif // FEATURE_H
