/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <fstream>
#include "Index.h"

using namespace std;

Index::Index()  {
    _nEntries = 0;
    _onBrand = 0;
}

Index::Index(int onBrand) {
    setIOnWhich(onBrand);
}

void Index::setIOnWhich(int val) {
    _onBrand = val;
}

int Index::size() const {
    return(_nEntries);
}

void Index::clear(){
    _nEntries = 0;
}

int Index::getIOnWhich() const {
    return(_onBrand);
}

int Index::add(const Pair & pair) {

    int es_posible = 1;
    int pos = upper_bound(pair.getKey());
        
    if(_nEntries >= MAXEVENT && !pair.isEmpty())
        es_posible = 0;
    else{
        if(_nEntries != 0){
            for(int i = _nEntries -1 ; i >=  pos; i--){
                _entries[i+1] = _entries[i];
            }
        }
        _entries[pos] = pair;
        _nEntries++;
    }
    
    return es_posible;
}

void Index::build(const EventSet & evSet, int onBrand) {
    _nEntries = 0;
    setIOnWhich(onBrand);
    
    if (_onBrand == 1) {
        for (int i=0; i<evSet.size(); i++) {
            if (evSet.at(i).getBrand()!= "") {
                Pair newPair(evSet.at(i).getBrand(), i);
                add(newPair);
            }
        }
    }
    else if (_onBrand == 0) {
        for (int i=0; i<evSet.size(); i++) {
            if (evSet.at(i).getUserID()!= "") {
                Pair newPair(evSet.at(i).getUserID(), i);
                add(newPair);
            }
        }
    }
}

int Index::lower_bound(const string & key) const {
    bool found = false;
    int pos = 0;
    
    for (int i=0; i<_nEntries && !found; i++) {
        if (_entries[i].getKey() >= key) {
            pos = i;
            found = true;
        }
    }
    
    return pos;
}

int Index::upper_bound(const string & key) const {
    bool found = false;
    int pos = _nEntries;
    
    for (int i=0; (i<_nEntries) && !found; i++) {
        if (_entries[i].getKey() > key) {
            pos = i;
            found = true;
        }
    }
    return pos;
}

const Pair & Index::at(int pos) const {
    return(_entries[pos]);
}

Pair & Index::at(int pos) {
    return(_entries[pos]);
}

void Index::print()const {
    cout << to_string();
}

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    Event newEvent;
    newEvent = evSet.at(indx.at(pos).getPos());
    return newEvent;
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    for(int i = 0; i < indx.size(); i++){
        os << evSet.at(indx.at(i).getPos()).to_string();
    }
}

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    Index resultado;
    
    for(int i = 0; i < indx.size(); i++){
        if(evSet.at(indx.at(i).getPos()).getField(field) == value)
            resultado.add(indx.at(i));
    }
    
    return resultado;
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    float suma = 0;
    for(int i = 0; i < indx.size(); i++){
        suma += getEvent(evSet,indx,i).getPrice();
    }
    
    return suma;
}