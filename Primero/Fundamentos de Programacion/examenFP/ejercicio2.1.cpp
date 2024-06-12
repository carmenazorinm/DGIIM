/* CARMEN AZORIN MARTI GRUPO 2
	INGENIERIA INFORMÁTICA Y MATEMÁTICAS
	
	Examen Convocatoria Ordinaria 2020-2021: Fundamentos de la Programación
	
	Ejercicio Palabras Seudosimétricas
	
*/

#include<iostream>
#include<string>
#include<cmath>

using namespace std;

class SecuenciaCaracteres{
	
private:
	//datos miembro
public:
	//constructores
	
	//PRE:num_max > 0
	SecuenciaCaracteres SubSecuencia (int num, int pos_inicio){	
    	
    	SecuenciaCaracteres subsecuencia;
    	
    	for (pos_inicio; pos_inicio<num; pos_inicio++){
    		subsecuencia.Aniade (vector_privado[pos_inicio]);
   		}
    
    	return subsecuencia;	
    }
	
	/*
		En este método lo que vamos a hacer es crear dos vectores con las 
		frecuencias de cada letra. Un vector guarda las frecuencias de la
		primera mitad de la secuencia y el otro vector, de la segunda mitad.
		En caso de que la secuencia tenga un numero impar de caracteres, 
		la mitad se calculará truncando, porque hemos puesto que 
		mitad_secuencia es de tipo int.
		
		Para rellenar los vectores pasamos por todas las casillas del 
		vector_privado[TAMANIO] exceptuando la de enmedio. Para ello, creamos
		un for que rellene la casilla del vector[i] y vector[mitad_secuencia+1]
		
		Para añadir +1 en el vector_frecuencias_parte1[] en la letra 'a', por
		ejemplo, la guardaremos en 'a' - 'a' = 0. Es decir, en la posicion 0.
		Para añadir +1 en la 'c', calculares 'c' - 'a' = 2, en la casilla 2.
		
	*/
	bool EsSeudoSimétrica(void){
		
		bool es_seudo = true;
		
		int mitad_secuencia = total_utilizados/2;
		int pos_letra;
		
		//es imprescindible inicializar todos los vectores a 0 para poder
		//comparar posteriormente las frecuencias
		const int NUM_LETRAS = 'z' - 'a' +1;
		int vector_frecuencias_parte1[NUM_LETRAS] = {0};
		int vector_frecuencias_parte2[NUM_LETRAS] = {0};
		
		for(int i = 0; i < mitad_secuencia; i++){
			
			pos_letra = vector_privado[i];
			vector_frecuencias_parte1[pos_letra - 'a']++;
			
			pos_letra = vector_privado[mitad_secuencia + i];
			vector_frecuencias_parte2[pos_letra - 'a']++;
		}
		
		//comprobamos que los dos vectores son iguales
		
		int letra_actual = 0;
		while(es_seudo && letra_actual<NUM_LETRAS){
			
			if(vector_frecuencias_parte1[letra_actual] 
									!= vector_frecuencias_parte2[letra_actual])
				es_seudo = false;
			
			letra_actual++;
		}
		
		return es_seudo;
	}
		
};

/*
	En mi caso, mi secuencia sería carmenazorin 
	
	1º suponemos que es_seudo = true
	2º mitad_secuencia = 12/2 = 6
	3º comienza el for:
		
		int pos_letra = vector_privado[0] = 'c'
		vector_frecuencias_parte1[2]++;
		
		pos_letras = vector_privado[6 + 1] = 'a'
		vector_frecuencias_parte2[0]++;
		
		Después se hace con la segunda letra. Po lo tanto, la casilla de la 'a'
		en vector_frecuencias_parte1[0]++; y la 'z' en el 
		vector_frecuencias_parte2['z'-'a']++; Así hasta la última letra
		
		De manera que el vector_frecuencias_parte1 tendría 0 en todo excepto:
		- posicion 2 = 1
		- posicion 0 = 1
		- posicion 'r' - 'a' = 1
		- posicion 'm' - 'a' = 1
		- posicion 'e' - 'a' = 1
		- posicion 'n' - 'a' = 1
		
		en el vector_frecuencias_parte2 se quedarían todas las casilla en 0, 
		exceptuando:
		- poscicion 0 = 1
		- posicion 'z' - 'a' = 1
		- posicion 'o' - 'a' = 1
		- posicion 'r' - 'a' = 1
		- posicion 'i' - 'a' = 1
		- posicion 'n' - 'a' = 1
		
		ahora que ya están los dos vectores rellenos, comprobamos que son
		iguales. 
		Vamos a ir pasando por todas las casillas de los vectores_frecuencia
		Entonces, en la casilla 0 (la casilla de la 'a') (0<NUM_LETRAS)
		tenemos que la parte1 tiene 1 y la parte2 tiene 1. Por lo tanto, el 
		bucle continua y sigue siendo true. En la casilla 1 (de la 'b') 
		(1 < NUM_LETRAS) tenemos que en la parte1 es 0 y en la parte2, tambien.
		Por lo tanto, sigue el bucle. Llegamos a la casilla 2 (de la 'c')
		(2 < NUM_LETRAS) tenemos que en el vector parte1 tiene un 1 y en la 
		parte2 tiene un 0. Por lo tanto, son diferentes y es_seudo = false.
		EL bucle se para y concluimos con que no es seudosimétrica.
		
		
*/