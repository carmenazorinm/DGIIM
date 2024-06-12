/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

	
/***************************************************************************/
/***************************************************************************/

enum class Tipo {muy_cortas, cortas, otras};

Tipo Clasifica (string palabra)
{
	Tipo tipo;
	
	if(palabra.length()<=2)
		tipo = Tipo::muy_cortas;
	else{	
		if(palabra.length()<=4)
			tipo = Tipo::cortas;
		else
			tipo = Tipo::otras;
	}
	
	return tipo;
}

/***************************************************************************/
/***************************************************************************/

int main()
{
	string cadena_final;		
	string lo_que_se_lee;
	int num_otras, num_muy, num_cortas;
	
	while(lo_que_se_lee != "FIN"){

		cin>>lo_que_se_lee;
		
		if(Clasifica(lo_que_se_lee) == Tipo::otras){
			
			for(int i = 0; i<lo_que_se_lee.length(); i++) 
      			lo_que_se_lee.at(i) = toupper(lo_que_se_lee.at(i));	
      			
			num_otras++;
		}else{
			if(Clasifica(lo_que_se_lee) == Tipo::muy_cortas)
				num_muy++;
			else
				num_cortas++;
		}
		
		cadena_final = cadena_final + " " + lo_que_se_lee;
	}	
	
	int total = num_muy+num_cortas + num_otras;
	

	// Salida
	
	cout << endl;	
	cout << cadena_final << endl; 
	cout << endl;
	
	 
	cout << endl;
	cout << "Hay un total de " << total << " palabras." << endl;	
	cout << endl;
	cout << "Hay " << setw(2) << num_muy << " muy cortas." << endl;	
	cout << "Hay " << setw(2) << num_cortas << " cortas." << endl;
	cout << "Hay " << setw(2) << num_otras << " otras." << endl;
	cout << endl;

	return 0;	
}

/***************************************************************************/
/***************************************************************************/
