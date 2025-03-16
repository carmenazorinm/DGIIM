
/* CARMEN AZORIN MARTI GRUPO 2
	INGENIERIA INFORMÁTICA Y MATEMÁTICAS
	
	Examen Convocatoria Ordinaria 2020-2021: Fundamentos de la Programación
	
	Tablero y sus Propiedades
	
*/

#include<iostream>
#include<string>
#include<cmath>

class SecuenciaEnteros{

private:
	//datos miembro

public:
	//constrcutores y metodos dados
	
	//método que suma todos los enteros de una SecuenciaEnteros. Para ello va
	//recorriendo todo el vector y va añadiendo a la variable suma, cada numero
	int SumaTotalSecuencia(void){
		
		int suma = 0;
		
		for(int i = 0; i < utiles; i++){
			suma = suma + vp[i];
		}
	}
	
};

///////////////////////////////////////////////////////////////

class Tablero{

private: 
	//datos miembro

public:
	//constructores metodos dados
	
	/*
		para saber si es califragilistico lo que hacemos es llmaar al método 
		privado VectorSumas() que nos devuelve una SecuenciaEnteros. Esta 
		secuencia esta formada por las sumas de todas las filas, todas las 
		columnas y las dos diagonales. Además, esta secuencia está ordenada de
		forma creciente.
		
		Por lo tanto, para saber si algun elemento es igual que otro, es 
		suficiente con mirar si un elemento es igual que el anterior. Por 
		ejemplo, en una SecuenciaEnteros sumas esta formado por 1, 2, 3, 3.
		Empezamos por la posicion 1. sumas(1) != sumas(0) porque 2 != 1.
		sumas(2) != sumas(3) porque 3 != 2. Pero sumas(3) == sumas(2) porque
		3 == 3. Por lo tanto, este vector tiene dos elementos iguales.
		
		En el momento en que dos elementos sean iguales, ya sabemos que no 
		es califragilistico, asi que no hace falta seguir comprobandolo
	*/
	bool EsCalifragilistico(void){
		
		bool es_cali = true;
		int contador = 1;
		
		SecuenciaEnteros sumas();
		sumas = VectorSumas();
		
		while(es_cali && contador < sumas.TotalUtilizados()){
			
			if(suma.Elemento(contador) == suma.Elemento(contador-1))
				es_cali = false;
			
			contador++;
		}
		
		return es_cali;
	}
	
	////////////////////////////////////////////////////////////
	
	/*
		Para saber si es supercalifragilistico lo primero que debemos saber es 
		si es califragilistico. Si no lo es, tampoco puede ser super.
		
		Si sí que lo es, entonces comprobamos que cada elemento del vector 
		sumas es igual que el elemento anterior -1. Si no lo es, 
		entonces esos dos numeros no son consecutivos y, por lo tanto, no es
		super y no hace falta seguir comprobandolo.
		
	*/
	
	bool EsSuperCalifragilistico(void){
		
		bool es_super = true;
		
		if(EsCalifragilistico){
			
			es_super = true;
			int contador = 1;
			
			SecuenciaEnteros sumas(VectorSumas())
			
			while(es_super && contador < sumas.TotalUtilizados()){
				
				if(sumas_ordenadas.Elemento(contador) != 
										sumas_ordenadas.Elemento(contador) -1)
					es_super = false;
				
				contador++;
			}
		}
		else
			es_super = false;
			
		return es_super;	
	}

private:
	
	/*
		Este metodo devuelve una secuencia de caracteres que tiene la suma de
		todas las filas y todas las columnas de la matriz, ademas de las 
		diagoales. Las sumas esta´ran ordenadas de la siguiente forma:
		
		1º Suma de la fila 0
		2º Suma de la columna 0
		3º Suma de la fila 1
		4º Suma de la columna 1
		.
		.
		.
		Suma de la fila dimension-1
		Suma de la columna dimension-1
		Suma de la diagonal principal
		Suma de la diagonal inversa
		
		Para hacerlo, tenemos un bucle que se ejecutará dimesion veces y 
		calculará la suma de la fila i y la columna i. Posteriormente, añadirá
		las dos sumas calculadas en el vector_sumas.
		
		Una vez tengamos todas las sumas de las columnas y las filas, 
		calcularemos las sumas de las diagonales. Pra ello, creamos un for que
		vaya pasando por la casilla [0][0] y [dim][1], luego pasa por la 
		casilla [1][1] y [dim-1][1] y añade los valores a la suma_diagonal
		y suma_diagonal_inv respectivamente. Así se ejecutará hasta completar
		toda la dimension. Y ambas sumas se añaden al vector_sumas. 
		
		antes de devolver el vector, ordena las sumas con el metodo 
		OrdenaCreciente(), así el vector será más facil de manejar en el resto
		de métodos.
	*/
	
	SecuenciaEnteros VectorSumas(void){
		
		SecuenciaEnteros vector_sumas();
		SecuenciaEnteros fila();
		SecuenciaEnteros col();
		
		for(int i = 0; i < dimension; i++){
			
			fila = Fila(i);
			col = Columna(i);
			
			vector_sumas.Aniade(fila.SumaTotalSecuencia());
			vector_sumas.Aniade(col.SumaTotalSecuencia());
		}
		
		int suma_diagonal = 0;
		int suma_diagonal_inv = 0;
		for(int i = 0; i < dimension; i++){
			
			suma_diagonal = suma_diagonal + t[i][i];
			suma_diagonal_inv = suma_diagonal_inv + t[dimension-i][i];
			
		}
		
		vector_sumas.Aniade(suma_diagonal);
		vector_sumas.aniade(suma_diagonal_inv);
		
		vector_sumas.OrdenaCreciente();
		
		return vector_sumas;
	}

};

/////////////////////////////////////////////////////////////////////
/*
	 En mi caso, el apartado c) se hace con el numero 487683281
	 
	 4 8 7
	 6 8 3
	 2 8 1
	 
	Primero llamaríamos al método EsCalifragilistico.
	Se craería el vector sumas formado por {4+8+7, 4+6+2, 6+8+3, 8+8+8, 2+8+1,
	7+3+1, 4+8+1, 2+8+7}, es decir, {19, 12, 17, 24, 11, 11, 13, 17}. Después
	se ordenaría {11, 11, 12, 13, 17, 17, 24}
	
	Para mirar si es califragilistico empezamos por el sumas[1] = 11 y 
	mirariamos si sumas[0] = 11 es igual que sumas[1]. Como 11 == 11, entonces, 
	se dejaría de comprobar que es califragilistico y devolvería false.
	
	Para mirar si es supercalifragilistico se llamaria al máetodo 
	EsSuperCalifragilistico() y lo primero que hace este método es comprobar 
	que es caliragilistico. Como no lo es, tampoco es super.
	
*/