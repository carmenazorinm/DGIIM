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

void Index::reallocate(int size){
    
    while((_nEntries + size) > _capacity){
        _capacity = (_capacity*2) + 1;
    }
    
    Pair *aux = new Pair [_capacity];
    
    for(int i = 0; i < _nEntries; i++){
        aux[i] = _entries[i];
    }
    
    deallocate();
    _entries = aux;
    aux = nullptr;
}

void Index::deallocate(){
    
    if(_entries != nullptr){
        delete[] _entries;
        _entries = nullptr;
    }
}

void Index::copy(Pair *dest){
    
    dest = new Pair [_capacity];
    
    for(int i = 0; i < _nEntries; i++){
        dest[i] = _entries[i];
    }
}

void Index::copy(const Index &orig){
    
    _nEntries = orig.size();
    _capacity = orig.getCapacity();
    _onBrand = orig.getIOnWhich();
    
    deallocate();
    
    _entries = new Pair [_capacity];
    
    for(int i = 0; i < _nEntries; i++){
        _entries[i]=orig.at(i);
    }
}

Index::Index(int onBrand) {
    _entries = nullptr;
    _capacity = 0;
    _nEntries = 0;
    
    setIOnWhich(onBrand);
}

Index::Index(const Index &orig){
    _entries = nullptr;
    _capacity = 0;
    _nEntries = 0;
    
    copy(orig);
}

void Index::setIOnWhich(int val) {
    _onBrand = val;
}

int Index::size() const {
    return(_nEntries);
}

void Index::clear(){
    _nEntries = 0;
    _capacity = 0;
    
    deallocate();
}

int Index::getIOnWhich() const {
    return(_onBrand);
}

int Index::add(const Pair & pair) {
    
    if(!pair.isEmpty()){

        reallocate(1);
        int pos = upper_bound(pair.getKey());
        
        for(int i = _nEntries -1 ; i >= pos; i--){
            _entries[i+1] = _entries[i];
        }
        _entries[pos] = pair;
        _nEntries++;
    }
    
    return 1;
}

void Index::build(const EventSet & evSet, int onBrand) {
    clear();
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
    else if (_onBrand == 2){
        for (int i=0; i<evSet.size(); i++) {
            if (evSet.at(i).getSession()!= "") {
                Pair newPair(evSet.at(i).getSession(), i);
                add(newPair);
            }
        }
    }
}

int Index::lower_bound(const string & key) const {
    bool found = false;
    int pos = _nEntries;
    
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
        suma = suma + getEvent(evSet,indx,i).getPrice();
    }
    
    return suma;
}

Index & Index::operator=(const Index & one){
    if(&one != this){
        copy(one);
    }
    return *this;
}

Index::~Index(){
    deallocate();
}

int Index::getCapacity() const{
    return _capacity;
}