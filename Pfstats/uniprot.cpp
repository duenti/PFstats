#include "uniprot.h"

Uniprot::Uniprot()
{
    name = "";
    dataset = -1;

}

Uniprot::Uniprot(Uniprot &prot){
    name = prot.getName();
    dataset = prot.getDataset();

    for(int i = 0; i < prot.countFeatures(); i++)
        feats.push_back(prot.getFeature(i));
}

Uniprot::Uniprot(string name, int dataset){
    this->name = name;
    this->dataset = dataset;
}

Uniprot::~Uniprot()
{

}

void Uniprot::addAccession(string access){
    this->accession.push_back(access);
}

string Uniprot::getAcesssionAt(int i){
    return this->accession[i];
}

int Uniprot::countAccession(){
    return this->accession.size();
}

string Uniprot::getAccession(int i){
    return accession[i];
}

int Uniprot::getAccessionSize(){
    return accession.size();
}

int Uniprot::getDataset(){
    return dataset;
}

void Uniprot::setDataset(int v){
    dataset = v;
}

string Uniprot::getName(){
    return name;
}

void Uniprot::setName(string n){
    name = n;
}

void Uniprot::addFeature(Feature *f){
    feats.push_back(f);
}

int Uniprot::countFeatures(){
    return feats.size();
}

Feature *Uniprot::getFeature(int i){
    return feats.at(i);
}

string Uniprot::toString(){
    string text = "";
    if(name != "")
        text += "NAME: " + name + "\n";
    if(dataset = 0) text += "DATASET: SWISS-PROT\n";
    else if(dataset > 0) text += "DATASET: TREMBL\n";

    for(int i = 0; i < accession.size(); i++)
        text += "ACCESSION NAME: " + accession[i] + "\n";

    for(int i = 0; i < feats.size(); i++)
        text += "FEATURES:\n\n" + feats.at(i)->toString();

    return text;
}

void Uniprot::kill(){
    name = "";
    name.shrink_to_fit();
    dataset = -1;

    for(int i = 0; i < accession.size(); i++){
        accession[i] = "";
        accession[i].shrink_to_fit();
    }
    accession.clear();
    accession.shrink_to_fit();

    for(int i = 0; i < feats.size(); i++){
        feats[i]->kill();
    }
    feats.clear();
    feats.shrink_to_fit();
}
