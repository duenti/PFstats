#include "feature.h"
#include <QString>

Feature::Feature()
{
    type = "";
    description = "";
    position = -1;
    begin = -1;
    end = -1;
    id = "";
    original = "";
    variation = "";
    aggregate = -1;
    residueColigated = "";
}

Feature::~Feature()
{
    this->kill();
}

string Feature::getType(){
    return type;
}

void Feature::setType(string t){
    type = t;
}

string Feature::getDescription(){
    return description;
}

void Feature::setDescription(string d){
    description = d;
}

int Feature::getPosition(){
    return position;
}

void Feature::setPosition(int p){
    position = p;
}

int Feature::getBegin(){
    return begin;
}

void Feature::setBegin(int p){
    begin = p;
}

int Feature::getEnd(){
    return end;
}

void Feature::setEnd(int p){
    end = p;
}

string Feature::getId(){
    return id;
}

void Feature::setId(string id){
    this->id = id;
}

string Feature::getOriginal(){
    return original;
}

void Feature::setOriginal(string r){
    original = r;
}

string Feature::getVariation(){
    return variation;
}

void Feature::setVariation(string r){
    variation = r;
}

int Feature::getAgregate(){
    return aggregate;
}

void Feature::setAggregation(int v){
    aggregate = v;
}

string Feature::getResidueColigated(){
    return residueColigated;
}

void Feature::setResidueColigated(string res){
    residueColigated = res;
}

string Feature::getAlignResidue(){
    return this->residueColigatedAlign;
}

void Feature::setAlignResidue(string pos){
    residueColigatedAlign = pos;
}

string Feature::toString(){
    string text = "";
    if(type != "")
        text = "TYPE: " + type + "\n";
    if(residueColigated != "")
        text += "RESIDUE: " + residueColigated + " (SEQ-NUMBER)" + residueColigatedAlign + " (ALIGN NUMBER)\n";
    if(aggregate == 0) text += "CONSERVED RESIDUES\n";
    else if(aggregate > 0) text += "COMMUNITY: " + QString::number(aggregate).toStdString() + "\n";
    if(description != "")
        text += "DESCRIPTION: " + description + "\n";
    if(id != "")
        text += "ID: " + id + "\n";
    if(position != -1)
        text += "POSITION: " + QString::number(position).toStdString() + "\n";
    if(begin != -1)
        text += "BEGIN: " + QString::number(begin).toStdString() + "\n";
    if(end != -1)
        text += "END: " + QString::number(end).toStdString() + "\n";
    if(original != "")
        text += "ORIGINAL: " + original + "\n";
    if(variation != "")
        text += "VARIATION: " + variation + "\n";

    return text;
}

void Feature::kill(){
    type = "";
    type.shrink_to_fit();
    description = "";
    description.shrink_to_fit();
    position = -1;
    begin = -1;
    end = -1;
    id = "";
    id.shrink_to_fit();
    original = "";
    original.shrink_to_fit();
    variation = "";
    variation.shrink_to_fit();
    aggregate = -1;
    residueColigated = "";
    residueColigated.shrink_to_fit();
    residueColigatedAlign = "";
    residueColigatedAlign.shrink_to_fit();
}
