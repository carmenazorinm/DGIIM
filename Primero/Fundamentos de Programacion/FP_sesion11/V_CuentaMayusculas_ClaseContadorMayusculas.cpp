/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 21: el programa lee caracteres hasta que se introduzca un '.'
	Cada vez que aparezca una mayuscula, se sumará 1 en el vector del objeto
	contador (clase ContadorMayusculas). Así, se podrán mostrar cuantas veces
	aparece cada letra mayuscula con el metodo CuantasHay() y el metodo
	IncrementaCuenta().
*/

#include<iostream>
#include<string>

using namespace std;

class ContadorMayusculas{
	
private:
    static const int TAMANIO = 'Z' - 'A' + 1;
    char vector_privado[TAMANIO];

public:
	//constructor. Inicializamos todo el vector a 0, porque al principio todas
	//las letras han aparecido 0 veces.
    ContadorMayusculas(void)
    {
        for(int i = 0; i < TAMANIO; i++){
            vector_privado[i] = 0;
        }
    }
    
    //PRE: mayuscula >= 'A' && mayuscula <= 'Z'
    void IncrementaCuenta(char mayuscula){
        vector_privado[mayuscula - 'A']++;
    }
    
    //PRE: mayuscula >= 'A' && mayuscula <= 'Z'
    int CuantasHay(char mayuscula){
        int numero = vector_privado[mayuscula - 'A'];
        return numero;
    }
};

/*****************************************************************************/
/*****************************************************************************/

int main(){
    const char TERMINADOR = '.';
    char caracter_a_leer;
    ContadorMayusculas contador;
    
    //ENTRADA DE DATOS
    
    do{
        caracter_a_leer = cin.get();
        if(caracter_a_leer >= 'A' && caracter_a_leer <= 'Z')
            contador.IncrementaCuenta(caracter_a_leer);
            
    }while(caracter_a_leer != TERMINADOR);
    
    //CALCULOS
  
    string cadena = "";
    for(char i = 'A'; i <= 'Z'; i++){
    	int numero_veces = contador.CuantasHay(i);
    	string num_veces_string = to_string(numero_veces);
        cadena = cadena + i + ": " + num_veces_string + " veces " +'\n';
    }
    
    //SALIDA
    
    cout<<cadena;
    
    cout<<endl<<endl;
    return 0;
}

