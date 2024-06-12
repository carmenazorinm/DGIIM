/**
 * @file Event.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <string>
#include <fstream>
#include "Event.h"
#include "DateTime.h"
using namespace std;

Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

Event::Event(const string & line) {
    set(line);
}

DateTime Event::getDateTime() const {
    return _dateTime;
}

string Event::getType() const {
    return _type;
}

string Event::getProductID() const {
    return _prod_id;
}

string Event::getCategoryID() const {
    return _cat_id;
}

string Event::getCategoryCode() const {
    return _cat_cod;
}

string Event::getBrand() const {
    return _brand;
}

double Event::getPrice() const {
    return _price;
}

string Event::getUserID() const {
    return _user_id;
}

string Event::getSession() const {
    return _session;
}

void Event::setDateTime(const std::string & time) {
    
    _dateTime = DateTime(time);
}

void Event::setType(const std::string & type) {
    
    bool valid = false;
    
    for(int i = 0; (i < 4) && !valid; i++){
        
        if(type == VALID_TYPES[i]){
            valid = true;
            _type = type;
        }
    }
    
    if(!valid)
        _type =  VALID_TYPES[0];
}

void Event::setProductID(const std::string & prod_id) {
    
    if(prod_id != "")
        _prod_id = prod_id;
    else
        _prod_id = EMPTY_FIELD;
 }

void Event::setCategoryID(const std::string & cat_id) {
    _cat_id = cat_id;
}

void Event::setCategoryCode(const std::string & cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string & brand) {
    _brand = brand;
}

void Event::setPrice(double price) {
    
    if(price >= 0)
        _price = price;
    else
        _price = -1.0;
}

void Event::setUserID(const std::string & user_id) {
    
    if(user_id != "")
        _user_id = user_id;
    else
        _user_id = EMPTY_FIELD;
}

void Event::setSession(const std::string & session) {
    
    if(session != "")
        _session = session;
    else
        _session = EMPTY_FIELD;
}

void Event::set(const std::string & line) {
    
    string valor_a_calcular = "";
    int contador = 0;
    bool _continue;
    
    for(int i = 0; i < 9; i++){
        
        _continue = true;
        
        while(contador < line.length() && _continue){
            
            if(line.at(contador) != ','){
                valor_a_calcular.push_back(line.at(contador));
                contador++;
            }else
                _continue = false;
        }
        
        if(i == 0)
            _dateTime = DateTime(valor_a_calcular);
        if(i == 1)
            _type = valor_a_calcular;
        if(i == 2)
            _prod_id = valor_a_calcular;
        if(i == 3)
            _cat_id = valor_a_calcular;
        if(i == 4)
            _cat_cod = valor_a_calcular;
        if(i == 5)
            _brand = valor_a_calcular;
        if(i == 6)
            _price = stod(valor_a_calcular);
        if(i == 7)
            _user_id = valor_a_calcular;
        if(i == 8)
            _session = valor_a_calcular;
        
        valor_a_calcular.clear();
        contador++;
    }
     
}

bool Event::isEmpty() const {
    
    bool is_empty;
    
    is_empty = (_prod_id ==  EMPTY_FIELD || _price < 0 || _user_id == EMPTY_FIELD 
            || _session == EMPTY_FIELD);
    
    return is_empty;
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    return salida;
}

std::string Event::getField(const std::string &field)const{
    
    string respuesta = "";
    if(field == "DateTime")
        respuesta = _dateTime.to_string();
    if(field == "Type")
        respuesta = _type;
    if(field == "ProductID")
        respuesta = _prod_id;
    if(field == "CategoryID")
        respuesta = _cat_id;
    if(field == "CategoryCode")
        respuesta = _cat_cod;
    if(field == "Brand")
        respuesta = _brand;
    if(field == "Price")
        respuesta = std::to_string(_price);
    if(field == "UserID")
        respuesta = _user_id;
    if(field == "Session")
        respuesta = _session;
    
    return respuesta;
}

void Event::write(ostream &os) const { 
    os << to_string();
} 
void Event::read(istream &is) { 
     string line; 
    
    getline(is, line);
    
    if (is)
        set(line);
}