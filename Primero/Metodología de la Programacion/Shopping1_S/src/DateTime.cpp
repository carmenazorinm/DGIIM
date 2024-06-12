/**
 * @file DateTime.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <iostream>
#include <sstream>
#include <string>
#include "DateTime.h"
using namespace std;

/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(const int &year,const int &month,const int &day,const int &hour,
                const int &min,const int &sec){
    
    bool is_correct;
    int end = 31; 
    
    if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
        end = 30;
    else{     
        if (month == 2){
            end = 28;
            
             if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
                 end = 29;       
        }    
    }
    
    is_correct = (((day >= 1) && (day <= end)) && ((month >= 1)&&(month <= 12))
                  && ((hour >= 0) && (hour <= 23)) && ((min >= 0) 
                  && (min <= 59)) && ((sec >= 0) && (sec <= 59)) 
                  && ((year >= 1971)));
    
    
    return is_correct;
}
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split(const std::string & line,int & y,int & m,int & d,int & h,int & mn,int & s){
    
    string valor_a_calcular = "";
    bool imposible = false;
   
    for(int i = 0; (i < 20) && !imposible ; i++){
        if(i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19){
            if(i == 4)
                y = stoi(valor_a_calcular);
            if(i == 7)
                m = stoi(valor_a_calcular);
            if(i == 10)
                d = stoi(valor_a_calcular);
            if(i == 13)
                h = stoi(valor_a_calcular);
            if(i == 16)
                mn = stoi(valor_a_calcular);
            if(i == 19)
                s = stoi(valor_a_calcular);
            
            valor_a_calcular.clear();
        }
        else{
            if(line.at(i) >= '0' && line.at(i) <= '9')
                valor_a_calcular.push_back(line.at(i));
            else
               imposible = true; 
        }
    } 
    
    if(!isCorrect(y, m, d, h, mn, s) || imposible){
        split(DATETIME_DEFAULT, y, m, d, h, mn, s);
    }
}

DateTime::DateTime() {
    _year = 1971;
    _month = 1;
    _day = 1;
    _hour = 0;
    _min = 0;
    _sec = 0;
}

void DateTime::initDefault() {
    set(DATETIME_DEFAULT);
}

void DateTime::set(const std::string  &line) {
    
    int year, month, day, hour, min, sec;
    split(line, year, month, day, hour, min, sec);
    
    //if(isCorrect(year, month, day, hour, min, sec)){
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _min = min;
    _sec = sec;
    //}
    //else
    //    initDefault();
}

DateTime::DateTime(const string &line) {
    set(line);
}

int DateTime::year() const {
    return _year;
}

int DateTime::month() const {
    return _month;
}

int DateTime::day() const {
    return _day;
}

int DateTime::hour() const {
    return _hour;
}

int DateTime::min() const {
    return _min;
}

int DateTime::sec() const {
    return _sec;
}

bool DateTime::isBefore(const DateTime &one) const {
    
    bool is_before = false;
    
    if(_year < one.year())
        is_before = true;
    else{
        if(_year == one.year()){
            if(_month < one.month())
                is_before = true;
            else{
                if(_month == one.month()){
                    if(_day < one.day())
                        is_before = true;
                    else{
                        if(_day == one.day()){
                            if(_hour < one.hour())
                                is_before = true;
                            else{
                                if(_hour == one.hour()){
                                    if(_min <one.min())
                                        is_before = true;
                                    else{
                                        if(_min == one.min()){
                                            if(_sec < one.sec())
                                                is_before = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return is_before;
}

int DateTime::weekDay() const {
     /*
    int m = _month;
    int y = _year;
    int a = _year%100;
    int b = _year / 100;
    int c = a/4;
    int d = b / 4;
    
    if(_month <= 2){
        m = m + 12;
        y = y - 1;
    }else
        m = m - 2;
    
    int week_day = (700 + (m*26-2)/10 + _day + a + c + d - 2*b)%7;
    */
   
    int a = (14 - _month)/12;
    int y = _year - a;
    int m = _month + 12* a - 2;
    int wDay;
    wDay = (_day + y + y / 4 - y / 100 + y / 400 + (31*m)/12) %7;
    
    return wDay;
    
   /*
    int m = _month;
    int y = _year;
    
    if(_month <= 2){
        m = m + 12;
        y = y - 1;
    }else
        m = m - 2;
    
    int j = (y/100);
    int k = (y%100);
    
    int week_day = ((_day + int((13*(m + 1))/5) + k + int(k/4) + int(j/4) - (2*j))-1) %7;
   */
    
   /*
   if(week_day >= 1)
        week_day--;
    else
        if(week_day == 0)
            week_day = 6;
    */ 
    
    //return week_day;
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

