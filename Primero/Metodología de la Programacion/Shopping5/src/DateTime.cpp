

#include <iostream>
#include <sstream>
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
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
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
void split(const std::string & line, int &y, int  &m, int  &d, int  &h, int &mn, int &s);

DateTime::DateTime() {
    initDefault();
}

void DateTime::initDefault() {
    set(DATETIME_DEFAULT);
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {

    int daysOfMonth;
    
    if(month==4 || month==6 || month==9 || month==11)
        daysOfMonth=30;
    else if (month==2) {
        if((year%4==0 && year%100 != 0) || (year%400 == 0))
            daysOfMonth = 29;
        else 
            daysOfMonth = 28;
    }
    else 
        daysOfMonth = 31;
    
    return ((month>0 && month<=12) && (day>0 && day<=daysOfMonth) && (hour>=0 && hour <=23) && (min>=0 && min<=59) && (sec>=0 && sec<= 59)); 
}

void split(const std::string & line, int &y, int  &m, int  &d, int  &h, int &mn, int &s) {
    
    try {
        y = stoi(line.substr(0,4));
        m=stoi(line.substr(5,2));
        d=stoi(line.substr(8,2));
        h=stoi(line.substr(11,2));
        mn=stoi(line.substr(14,2));
        s=stoi(line.substr(17,2));
    } catch (const std::invalid_argument& e) {
        split (DATETIME_DEFAULT, y, m, d, h, mn, s);
    }
}

void DateTime::set(const std::string & line) {
    
    int year, month, day, hour, min, sec;
    split(line, year, month, day, hour, min, sec);
    
    if (isCorrect(year, month, day, hour, min, sec)){
        _year=year;
        _month=month;
        _day=day;
        _hour=hour;
        _min=min;
        _sec=sec;
    }
    else
        initDefault();
}

DateTime::DateTime(const string & line) {
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

bool DateTime::isBefore(const DateTime & one) const {
    return to_string() < one.to_string();
}

int DateTime::weekDay() const {
    
//    int a =(14 - _month)/12;
//    int y = _year - a;
//    int m = _month + 12*a -2;
//    int dayOfWeek;
//    
//    dayOfWeek=(_day+y+y/4-y/100+y/400+(31*m)/12)%7;
//    
//    return dayOfWeek;
    
    int dayOfWeek;
    int month = _month - 2;
    int year = _year;
    
    if (_month <= 2) {
        year = _year-1;
        month = _month + 10;
    }
    
    dayOfWeek = (_day + (31*month)/12 + year + year/4 - year/100 + year/400)%7;
    
    return dayOfWeek;
  
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

bool DateTime::sameDay(const DateTime &other) const {
    bool same = false;
    
    if (weekDay() == other.weekDay())
        same = true;
    
    return same;
}