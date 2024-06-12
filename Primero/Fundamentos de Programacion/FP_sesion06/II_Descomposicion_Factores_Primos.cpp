/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 47: el programa leerá un numero y lo descompondrá en factores 
	primos de dos maneras diferentes:
	1) enumerará todos todos los divisores primos. Para ello, el numero irá 
	dividiendose por el primer primo todas las veces que pueda. Cuando ya no 
	sea divisible por ese primo, llamará a otra funcion que buscará el siguiente
	numero primo y lo dividirá por ese, siempre que sea posible. Cuando el 
	numero se haya quedado en 1, entonces la función parará.
	2) enumerará todos los divisores primos con potencias. Para ello, con la 
	función cuantas_veces_divisible se verá a qué potencia se tiene que elevar 
	cada primo y con la función imprimir_potencia se mostrará. 
	
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

double elevar(double x, int n){
	
	if(n<0) //si la potencia es negativa, se tiene que multiplicar por el 
		x = 1/x;		            //inverso de la base.
	
	const double X = x; //para guardar el valor de la base.
	
	if(n==0) //si el numero se va a elevar a 0, siempre es 1.
		x = 1;
	
	for(int i=1; i<abs(n); i++){
		
		x = x*X;
	}
	
	return x;
}

/******************************************************************************/

bool es_primo(int numero){
	
	int i=1;
	
	while(i<=numero){
		
		int aux = numero%i;
		
		if((aux==0)&&(i!=1)&&(i!=numero)){
			
			return false;
		}
		i++;
	}
	return true;
}

/******************************************************************************/

int siguiente_numero_primo(int primo){
	
	do{
		primo++;
			
	}while(!(es_primo(primo)));
	
	return primo;
}

/******************************************************************************/

int cuantas_veces_divisible(int numero, int primo){
	
	int contador = 0;	
	
	while(numero%primo == 0){
		
		numero = numero/primo;
		contador++;
	}
	return contador;
}

/******************************************************************************/

void imprimir_potencia(int numero, int potencia){
	
	if(potencia == 1)
		cout<<numero;
	else{
		if(numero == 1)	
			cout<< numero << "^"<<potencia;					
		else
			cout<< numero << "^"<<potencia<< " * ";	
	}
}
/******************************************************************************/

int convertir_absoluto(int numero){
	
	if(numero<0)
		numero=(-1)*numero;
		
	return numero;
}

/******************************************************************************/

void imprimir_primera_forma(int numero){
		
	cout<< " "<< numero << " = ";
	
	if(numero<0)
		cout<<"- ";
	
	int aux = convertir_absoluto(numero);
	int primo = 2;
	
	do{	
		while(aux%primo == 0){
			
			aux = aux/primo;
			
			if(aux == 1)	
				cout<< primo;
			else	
				cout<< primo << " * ";
		}
		primo = siguiente_numero_primo(primo);
		
	}while(aux/1 != 1);
}

/******************************************************************************/

void imprimir_segunda_forma(int numero){
	
	cout<< " " << numero << " = ";
	
	if(numero<0)
		cout<<"- ";
	
	int primo = 2;
	int aux = convertir_absoluto(numero);
	
	while(aux/1 != 1){
	
		if(aux%primo == 0){
			int potencia = cuantas_veces_divisible(aux,primo);
			imprimir_potencia(primo,potencia);		
			aux = aux/elevar(primo,potencia);
		}
		primo = siguiente_numero_primo(primo);
	}
}

/******************************************************************************/

int main(){
	
	int numero;
	int primo_forma_1 = 2;
	
	cout<<endl;
	cout<< " Escriba un numero: ";
	cin>> numero;
	cout<< endl;
	
	if(numero == 0)	
		cout<< " " << numero << " = " << numero;
	else{	
		imprimir_primera_forma(numero);
		cout<< endl;
		imprimir_segunda_forma(numero);
	}
	
	return 0;
}
