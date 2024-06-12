#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
	
	int horas, min, seg, dias,total;
	
	cout << "Segundos: "; cin >> seg;
	cout << "Minutos: "; cin >> min;
	cout << "Horas: "; cin >> horas;
	
	total = seg + min*60 + horas*3600; //86461
	
	seg = total%60; //seg = 1
	total = total - seg; //total = 86460 (se quitan los segs que sobran)
	
	min = (total/60)%60; //min = 1
	total = (total - min*60); //total = 86400  (se quitan los min que sobran)
	
	horas = (total/3600)%24; //horas = 0
	total = (total - horas*3600); //total = 86400 (se quitan las horas que sobran)
	
	dias = ((total/3600)/24)%24; //dias = 1
	total = (total - dias*24*3600); //total = 0 (se quitan los dias que sobran)ç
	
	
	cout << "Resultados:" << endl;
	cout << "Segundos: " << seg <<endl;
	cout << "Minutos: " << min << endl;
	cout << "Horas: " << horas << endl;
	cout << "Dias: " << dias << endl;
			
	return 0;
}
