/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */

#include <unordered_map>
#include <fstream> 
#include <string>
#include "EventSet.h"

using namespace std;

Event NULL_EVENT = Event(); //sirve para que en el at, si le doy una posicion incorrecta, me devuelva un null_event

/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to llok for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name) {
    
    int pos = 0;
    bool encontrada = false;
    
    while(!encontrada){
        
        if(array[pos] == name)
            encontrada = true;
        else
            pos++;
    }
    
    if(!encontrada)
        pos = -1;
    
    return pos;
}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet() {
    _nEvents=0;
}

int EventSet::size() const {
    return _nEvents;
}


void EventSet::clear() {
    _nEvents = 0;
}

int EventSet::add(const Event & e) {
    
    int es_posible = 1;
    if(_nEvents < MAXEVENT){
        _events[_nEvents] = e;
        _nEvents++;
    }
    else
        es_posible = 0;
        
    return es_posible;
}

int EventSet::add(const std::string& line) {
    
    Event nuevo_evento(line);
    
    int resultado = add(nuevo_evento);
    
    return resultado;

}

const Event & EventSet::at(int pos) const {
    
    if(pos < 0 || pos >= _nEvents){
        return(NULL_EVENT);
    }
    else
        return(_events[pos]);
}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    
    EventSet newSet;
    
    if (field == "DateTime") {
        DateTime date(value);
        
        for (int i=0; i<es.size(); i++) {
            if (date.sameDay(es.at(i).getDateTime()))
                newSet.add(es.at(i));
        }
    }
    else {
        for (int i=0; i<es.size(); i++) {
            if (es.at(i).getField(field) == value)
               newSet.add(es.at(i));
        }
    }
    
    return(newSet);
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    
   bool found = false;
    n_values = 0; 
    
    if (field == "DateTime") {
        for (int i=0; i<es.size(); i++) {
            found = false;
            
            for (int j=0; (j<n_values) && (!found); j++) {
                DateTime date(values[j]);
                
                if (date.sameDay(es.at(i).getDateTime()))
                    found = true;
            }
            if(!found){
                string date = es.at(i).getDateTime().to_string();
                
                date.at(11) = '0';
                date.at(12) = '0';
                date.at(14) = '0';
                date.at(15) = '0';
                date.at(17) = '0';
                date.at(18) = '0';
                
                values[n_values] = date;
                n_values++;
            }
        }
    }
    else { 
        for (int i=0; i<es.size(); i++) {
            found = false;
            for (int j=0; (j<n_values) && (!found); j++) {
                if (es.at(i).getField(field) == values[j])
                    found = true;
            }
            if (!found) {
                values[n_values] = es.at(i).getField(field);
                n_values++;
            }  
        }
    }
}

float sumPrice(const EventSet & evSet) {
    
    float total = 0;
    
    for(int i = 0; i < evSet.size(); i++){
        
        double precio = evSet.at(i).getPrice();
        
        if(precio >= 0)
            total += precio;
    }
    
    return total;
}

void EventSet::write(ofstream &os) const { // Laura lo tiene con "\n"
    string cadena;
    for(int i = 0; i <_nEvents; i++){
        cadena = cadena + _events[i].to_string() + "\n";
    }
    os << cadena;
}
bool EventSet::read(ifstream &is, int nelements) { 
    Event e;
    bool result=true;
    
    // Limpiar el EventSet
    clear();
    
    //Repetir nelements
    for (int i=0; i<nelements && result; i++) {
        e.read(is);
        if (is) {
            add(e);
        }
        else
            result = false;
    }
    
    return result;
} //tiene que informar de si el proceso de lectura ha sido bueno o no

