/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 81: el programa leerá un caracter de entre las opciones que da
	el menu principal. 
	
	Si se elige la A, se obligará a introducir otro caracter de entre las 
	opciones que da el menu secundario de A. 
		- Si se elige S o R, se pedirán dos numeros reales y se calculará la 
		operación corrspondiente. Como está en un bucle, volverá a mostrarse el 
		menu secundario.
		- Si se elige X, entonces el bucle se acaba y se muestra el menu 
		principal.
	
	Si se elige la P, se obligará a introducir unos de los caracteres de entre 
	las opciones que da el menu secundario de P.
		- Si se elige M o D, se pedirán dos numeros reales y se calculará la 
		operación correspondiente. Como está en un bucle, volverá a mostrarse el 
		menú secundario.
		- Si se elige X, entonces el bucle termina y se muestra el menu
		principal.
	
	Si se elige la X, se acaba el bucle principal y el programa se acaba.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	char caracter_menu_principal;
	char caracter_menu_secundario;
	

	do{//el primer bucle repetirá el programa siempre que el caracter del menu
		//principalsea distinto de X
		
		//el primer bucle secundario pide que se introduzca uno de los 
		//caracteres pedidos. En caso de que se introduzca un caracter diferente
		//al de las opciones, se volverá a pedir el caracter. 
		
		do{
			cout<< endl;
			cout<< " Introduzca uno de los siguientes caracteres: "<< endl;
			cout<< " - |A| si se quiere calcular una adicion "<< endl;
			cout<< " - |P| si se quiere calcular un producto "<< endl;
			cout<< " - |X| si se quiere salir del programa "<< endl;
			cout<< " Caracter: ";
			cin>> caracter_menu_principal;
			cout<<endl;
			
		}while(caracter_menu_principal != 'A' && caracter_menu_principal != 'P'
			&& caracter_menu_principal != 'X');
			
		//si se elige la opción de adición 
		
		if(caracter_menu_principal == 'A'){
			
			double numero1;
			double numero2;
			double resultado;
			
			do{//este bucle se repetirá siempre que el caracter introducido en
				//el menu secundario sea distinto de X
				
		//el siguiente bucle secundario pide que se introduzca uno de los 
		//caracteres pedidos. En caso de que se introduzca un caracter diferente
		//al de las opciones, se volverá a pedir el caracter. 
		
			do{
				cout<<endl;
				cout<< " Introduzca uno de los siguientes caracteres: "<< endl;
				cout<< " - |S| si se quiere calcular una suma "<< endl;
				cout<< " - |R| si se quiere calcular una resta "<< endl;
				cout<< " - |X| si se quiere ir al menu principal "<< endl;
				cout<< " Caracter: ";
				cin>> caracter_menu_secundario;
		
			}while(caracter_menu_secundario != 'S'
				&& caracter_menu_secundario != 'R' 
				&& caracter_menu_secundario != 'X');
				
			//si el caracter introducido es X, no hace falta que pida dos 
			//numeros reales, porque se va a ir directamente al inicio del 
			//bucle principal
				
			if(caracter_menu_secundario != 'X'){
				 
				cout<< " Introduzca dos numeros reales: ";
				cin>> numero1;
				cin>> numero2;
			}

			//si se elige la opción de la suma
			
			if(caracter_menu_secundario == 'S'){
				
				resultado = numero1 + numero2;
				cout<<endl;
				cout<< numero1 << "+"<< numero2<< "="<< resultado;
				cout<<endl<<endl;
			}
			
			//si se elige la opción de la resta
			
			if(caracter_menu_secundario == 'R'){
				
				resultado = numero1 - numero2;
				cout<<endl;
				cout<< numero1 << "-"<< numero2<< "="<< resultado;
				cout<<endl<<endl;
			}
			}while(caracter_menu_secundario !='X');
		}
		
		//si se elige la opción de producto
		
		if(caracter_menu_principal == 'P'){
			
			double numero1;
			double numero2;
			double resultado;

			do{//este bucle se repetirá siempre que el caracter del menu
				//secundario sea distinto de X
				
		//el siguiente bucle secundario pide que se introduzca uno de los 
		//caracteres pedidos. En caso de que se introduzca un caracter diferente
		//al de las opciones, se volverá a pedir el caracter. 
				
			do{
				cout<<endl;
				cout<< " Introduzca uno de los siguientes caracteres: "<< endl;
				cout<< " - |M| si se quiere calcular una multiplicacon "<< endl;
				cout<< " - |D| si se quiere calcular una division "<< endl;
				cout<< " - |X| si se quiere ir al menu principal "<< endl;
				cout<< " Caracter: ";
				cin>> caracter_menu_secundario;
		
			}while(caracter_menu_secundario != 'M'
				&& caracter_menu_secundario != 'D' 
				&& caracter_menu_secundario != 'X');
				
			//si el caracter introducido es X, no hace falta que pida dos 
			//numeros reales, porque se va a ir directamente al inicio del 
			//bucle principal
				
			if(caracter_menu_secundario != 'X'){
				 
				cout<< " Introduzca dos numeros reales: ";
				cin>> numero1;
				cin>> numero2;
			}

			//si se elige la opción de la multiplicacion
			
			if(caracter_menu_secundario == 'M'){
				
				resultado = numero1 * numero2;
				cout<<endl;
				cout<< numero1 << "x"<< numero2<< "="<< resultado;
				cout<<endl <<endl;
			}
			
			//si se elige la opción de la división
			
			if(caracter_menu_secundario == 'D'){
				
				resultado = numero1 / numero2;
				cout<< endl;
				cout<< numero1 << "/"<< numero2<< "="<< resultado;
				cout<<endl<<endl;
			}
			}while(caracter_menu_secundario !='X');
		}
	}while (caracter_menu_principal != 'X');
	
	
	return 0;
}
