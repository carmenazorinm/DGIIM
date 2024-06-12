/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 1: el programa consta de dos partes:
	a) en la primera parte se leen los coeficientes de dos rectas y se calcula 
	el punto de corte entre ellas. 
	b) en la segunda parte se leen los coeficientes de una recta y se pide un 
	punto. Mediante la funcion CalcularSiPuntoPerteneceARecta, aparecerá si 
	pertenece a la recta o no. Se van a ir pidiendo puntos hasta que el usuario
	escriba "fin" cuando se le pregunta por la abscisa.
*/

#include<iostream> //inclusion de recursos de E/S
#include<string>
#include<cctype> //para incluir la funcion toupper

using namespace std;

struct Punto2D{
	
	double abscisa;
	double ordenada;
};

struct Recta{
	
	double coeficiente_A;
	double coeficiente_B;
	double coeficiente_C;
};
/******************************************************************************/

double Pendiente(Recta recta){
	
	double pendiente = (-1)*recta.coeficiente_A/recta.coeficiente_B;	
	return pendiente;
}

double Ordenada(Recta recta){
	
	double ordenada_origen = (-1)*recta.coeficiente_C/recta.coeficiente_B;	
	return ordenada_origen;
}

/*****************************************************************************/

void MostrarTodosLosPuntos(Recta recta){
	
	cout<< " Los puntos por los que pasa la recta r son: ";
	cout<<endl;
	
	for(int x=-10; x<=10; x++){
		
		double y =((recta.coeficiente_C + recta.coeficiente_A*x)/
					((-1)*recta.coeficiente_B));

		cout<< " ("<<x<<","<<y<<")"<<endl;	
	}
}

void MostrarOrdenada(Recta recta){
	
	double x;
	
	cout<< " Introduzca un valor para la abscisa: ";
	cin>>x;
	
	double y =((recta.coeficiente_C + recta.coeficiente_A*x)/
					((-1)*recta.coeficiente_B));
					
	cout<< " El punto que se busca es: ("<<x<<","<<y<<")"<<endl<<endl;
}

void MostrarAbscisa(Recta recta){
	
	double y;
	
	cout<< " Introduzca un valor para la ordenada: ";
	cin>>y;
	
	double x =((recta.coeficiente_C + recta.coeficiente_B*y)/
					((-1)*recta.coeficiente_A));
					
	cout<< " El punto que se busca es: ("<<x<<","<<y<<")"<<endl<<endl;
}

/******************************************************************************/
void MostrarEcuacionExplicita(Recta recta){
	
	cout<< " La ecuacion explicita de la recta es: y = ";
	cout<<Pendiente(recta)<<"x + "<<Ordenada(recta);
	cout<<endl;	
}
/******************************************************************************/
void PosicionDosRectas (Recta recta1, Recta recta2){
	
	double pendiente_1 = Pendiente(recta1);
	double pendiente_2 = Pendiente(recta2);
	bool hay_punto_de_corte = true;
	
	if(pendiente_1 == pendiente_2){
		
		if(recta1.coeficiente_A/recta2.coeficiente_A == 
									recta1.coeficiente_C/recta2.coeficiente_C)	
			cout<< " Las rectas son coincidentes. ";
		else
			cout<< " Las rectas son paralelas. ";
	}
	else
		cout<< " Las rectas son secantes. ";
	
	cout<<endl;
}

/*****************************************************************************/

void MostrarPuntoDeCorte(Recta r, Recta s){
	
	Punto2D punto_de_corte;
	bool se_puede_calcular = Pendiente(r) != Pendiente(s);
	
	if(!se_puede_calcular)
		cout<< " No hay punto de corte entre las rectas r y s. ";
	else{
		
	//si alguno de los coeficiente_B es 0, entonces la recta es vertical y sólo
	//se podría calcular el punto de corte de esta manera, sin dividir entre 0:
	
		if(r.coeficiente_B==0 || s.coeficiente_B==0){
			if(r.coeficiente_B == 0){
				punto_de_corte.abscisa = ((-1)*r.coeficiente_C)/r.coeficiente_A;
			punto_de_corte.ordenada = ((s.coeficiente_C+s.coeficiente_A*
								punto_de_corte.abscisa)/((-1)*s.coeficiente_B));
			}
		else{
			punto_de_corte.abscisa = ((-1)*s.coeficiente_C)/s.coeficiente_A;
			punto_de_corte.ordenada = ((r.coeficiente_C+r.coeficiente_A*
								punto_de_corte.abscisa)/((-1)*r.coeficiente_B));
		}
		}
		else{
			//siendo r:mx+n y s:m'x+n', deducimos que: x=(n'-n)/(m-m')
	
			punto_de_corte.abscisa = 
					((Ordenada(s)-Ordenada(r))/(Pendiente(r)-Pendiente(s)));
			//sabemos que Ax+By+C=0 => y=-(C+Ax)/B en cualquiera de las rectas
	
			punto_de_corte.ordenada = (-1)*((r.coeficiente_C+r.coeficiente_A*
									punto_de_corte.abscisa)/r.coeficiente_B);
		}
	
		cout<< " El punto de corte de las rectas r y s es: ";
		cout<< "("<<punto_de_corte.abscisa<<","<<punto_de_corte.ordenada<<")";
	}
}
/******************************************************************************/

void CalcularSiPuntoPerteneceARecta(Recta recta, double x, double y){
	
	Punto2D punto;
	
	//si la recta tiene coeficiento_B=0, entonces todos los puntos que estén en
	//esa recta vertical pertenecen a la recta. Por tanto, no hace falta 
	//calcular la y del punto.
	
	if(recta.coeficiente_B==0){
		punto.abscisa = ((-1)*recta.coeficiente_C)/recta.coeficiente_A;
		
		if(punto.abscisa == x){
			cout<< " El punto con coordenadas ("<<x;
			cout<<","<<y<<") si que pertenece ";
			cout<< "a la recta";
		}else{
			cout<< " El punto con coordenadas ("<<x<<","<<y<<") no pertenece ";
			cout<< "a la recta";
		}	
	}
	else{
		punto.abscisa = x;
		punto.ordenada = (-1)*((recta.coeficiente_C+recta.coeficiente_A*x)
														/recta.coeficiente_B);
	
		if(punto.ordenada == y){	
			cout<< " El punto con coordenadas ("<<x;
			cout<<","<<y<<") si que pertenece ";
			cout<< "a la recta";
		}else{
			cout<< " El punto con coordenadas ("<<x<<","<<y<<") no pertenece ";
			cout<< "a la recta";
		}
		cout<<endl;	
	}
}
/******************************************************************************/

string ConvertirAMayuscula(string palabra){
	
	string palabra_en_mayusculas;
	
	for(int i=0; i<palabra.length(); i++){
		
		char caracter = toupper(palabra.at(i));
		palabra_en_mayusculas = palabra_en_mayusculas + caracter;	
	}
	
	return palabra_en_mayusculas;
}

/******************************************************************************/
bool ComprobarQueEsNumero (string cadena){
	
	int j = 0;
	bool es_numero = true;
	
	if(cadena.at(0) == '-')
		j++;
	
	//pasa caracter por caracter de la cadena comprobando que cada uno de ellos 
	//es un digito numerico.
	
	while(es_numero && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_numero = (caracter_posicion_j>='0' && caracter_posicion_j <='9')
						||caracter_posicion_j=='.';
		j++;
	}
	
	return es_numero; //true si es un numero y false si no lo es.	
}
/******************************************************************************/
int main(){
	
	Recta r;
	Recta s;

	cout<<endl;
	
	do{	
		cout<< " Escriba los coeficientes de la ecuacion";
		cout<<" general de una recta r: ";
		cout<< endl;
		cout<< " Coeficiente A: ";
		cin>>r.coeficiente_A;
		cout<< " Coeficiente B: ";
		cin>>r.coeficiente_B;
		cout<< " Coeficiente C: ";
		cin>>r.coeficiente_C;
	}while(r.coeficiente_A == 0 && r.coeficiente_B==0);
	
	//MostrarTodosLosPuntos(r);
	//MostrarOrdenada(r);
	//MostrarAbscisa(r);
	//MostrarEcuacionExplicita(r);
	
	do{
		cout<< " Escriba los coeficientes de la ecuacion";
		cout<<" general de una recta s: ";
		cout<< endl;
		cout<< " Coeficiente A: ";
		cin>>s.coeficiente_A;
		cout<< " Coeficiente B: ";
		cin>>s.coeficiente_B;
		cout<< " Coeficiente C: ";
		cin>>s.coeficiente_C;
	}while(s.coeficiente_A == 0 && s.coeficiente_B==0);
	
	//PosicionDosRectas(r,s);
	MostrarPuntoDeCorte(r,s);
	
	/**********************************************************************/
	
	cout<<endl;
	cout<<endl;
	
	string TERMINADOR = "FIN";
	bool seguir_pidiendo_numeros = true;
	
	Recta t;
	
	do{
		cout<< " Escriba los coeficientes de la ecuacion";
		cout<<" general de una recta: ";
		cout<< endl;
		cout<< " Coeficiente A: ";
		cin>>t.coeficiente_A;
		cout<< " Coeficiente B: ";
		cin>>t.coeficiente_B;
		cout<< " Coeficiente C: ";
		cin>>t.coeficiente_C;
	}while(t.coeficiente_A == 0 && t.coeficiente_B==0);
	
	do{
		string x;
		double y;
	
		cout<< " Escriba un punto: ";
		cout<< endl;
		cout<< " Abscisa: ";
		cin>>x;
		
		x = ConvertirAMayuscula(x);
		
		if(x == TERMINADOR)
			seguir_pidiendo_numeros = false;
		else{
			if(ComprobarQueEsNumero(x)){
				cout<< " Ordenada en el origen: ";
				cin>>y;
			
				double x_double = stoi(x);
				CalcularSiPuntoPerteneceARecta(t, x_double, y);
				cout<<endl;
			}
		}
		
	}while(seguir_pidiendo_numeros);
	
	cout<< endl<< endl;

	return 0;
}
