/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */


#include <string>
#include <cassert>
#include <iostream>
#include "Event.h"

#include "MPTests.h"

using namespace std;


/**
 * @brief displays the content of the array by using the method to_string that easy to transfer data to stream.  The content remains constant
 * @param array of the Events
 * @param nEvent number of events in the array
 */
void print(const Event array[], int & nEvent){
    
    for(int i = 0; i < nEvent; i++){
        cout << array[i].to_string();
        cout << endl;
    }
    cout << "Records read: " << nEvent;
}

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen in the following format
 * ~~~~
 *      SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0)
 *      +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 * @param arrayE an Event input array
 * @param nEvents number of events in arrayE
 * @param arrayA an int output array
 */
void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]){
    
    //inicializo a 0
    for(int i = 0; i < 7; i++){
        arrayA[i] = 0;
    }
    //rellena el vector arrayA con el numero de eventos que se realizan cada 
    //día de la semana.
    for(int i = 0; i < nEvents; i++){  
        int day_week = arrayE[i].getDateTime().weekDay();
        arrayA[day_week]++;
    }
    
    //pinto la actividad de cada día de la semana
    CVAL << "Activity found: ";
    for(int i = 0; i < 7; i++){
        CVAL << DAYNAME[i] << "("<<arrayA[i]<<") ";
    }
    CVAL << endl;
}
/**
 * @brief Compute the  max number of activity events, and the day on which is produced
 * @param arrayA the counter of activities, an input array
 * @param ndays number of days
 * @param maxDay
 * @return maxActivity the counter of events of 
 */
int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays=7){
    
    int max_activity = -1;
    maxDay = -1;
    
    //calculo el día de mayor actividad y cuánta actividad
    for(int i = 0; i < ndays; i++){
        
        if(arrayA[i] > max_activity){
            max_activity = arrayA[i];
            maxDay = i;
        }
    }
    
    return max_activity;
}



/**
 * @brief The main function of the program carries out the following procedure
 *   - It uses a static array of Events to store a sequence of events read from 
 * keyboard (likely to be redirected from a data file in the ./tests folder)
 *   - It reads the maximum number of valid records to be stored in the array.
 *   - If the event read is right (use the method isEmpty() to detect non-valid
 * records), it is stored in the array, otherwise, it is dismissed. Only valid records count.
 *   - Next, it computes the number of events found at each day of the week (complete the implementation
 * of the local function computeActivity() which also shows the result)
 *   - Next, it finds which is the day of highest activity recorded and show it on screen
 */
//pie el numero de elementos, los lee, los guarda en un vector, clacula la actividad por dias 
//y calculo el dia de máxima actividad y cuánta actividad ha sido
int main(int argc, char** argv) {
    
    const int DIM = 200; 
    Event events[DIM];
    int n = 0  ;
    int n_valid = 0;
    
    int activityWeek[7];
    int maxActivity, maxDay;
    string line;
    
    
   //con filtro incluido
    cout << "Number of events to read" << endl;
    do{
        cin >> n;  
    }while(n < 0 || n > DIM);
    
   
    getline(cin, line);
    //si el evento es vacío, entonces no quiero añadirlo al vector de events
    for(int i = 0; i < n; i++){
        getline(cin, line);
       
        if(!Event(line).isEmpty()){
            events[i] = Event(line);
            n_valid++;
        }
        line.clear();
    }
    
    print(events, n_valid);
    computeActivity(events, n_valid, activityWeek);
    maxActivity = computeMaxActivityDay(activityWeek, maxDay);
    CVAL << "Records read: " << n << endl;
    CVAL << "Valid records: " << n_valid << endl;
    CVAL << "Max activity: " << maxActivity << endl;
    CVAL << "Day of Max activity: " << DAYNAME[maxDay] << endl;

}