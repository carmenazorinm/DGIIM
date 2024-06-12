/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 9: el programa lee caracteres hasta que se introduzca '*'. 
	Mostrar�:
	1) Cu�ntas veces se ha escrito cada letras
	2) Cu�ntos caracteres se han escrito en total y cu�les de ellos son letras 
	y espacios.
	3) Cu�ntas letras no se han escrito ninguna vez. Y cu�les son.
	4) Cu�les son las letras m�s y menos.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	const int TOTAL_LETRAS = 'z' - 'a' + 1;
	int letra_abecedario[TOTAL_LETRAS] = {0};
	
	//los contadores 
	int total_caracteres = 0;
	int total_letras = 0;
	int total_espacios = 0;
	char caracter;
	
	do{	
		cin.get(caracter);
		total_caracteres++; //por cada caracter le�do se suma uno al total
		
		//si el caracter le�do es una letra, se a�ade +1 a su posici�n en el 
		//vector letra_abecedario indistintamente de si es mayuscula o 
		//minuscula
		if(caracter >= 'a' && caracter <= 'z'){ 
		
			total_letras++;		
			caracter = tolower(caracter);
			int posicion_letra = caracter - 'a';
		
			letra_abecedario[posicion_letra]++;	
		}
		//si el caracter le�do es un espacio, se suma uno al total_espacios
		if(caracter == ' ')
			total_espacios++;
			
	}while(caracter != '*'); //se leer�n caracteres hasta que se inserte '*'
	cout<<endl;
	
	/***********************************************/
	
	//Mostrar cu�ntas veces ha aparecido cada letra
	
	int total_letras_que_no_aparecen = 0;//se crea un nuevo contador
	for(int j=0; j<TOTAL_LETRAS; j++){ //por cada letra del abecedario se 
									   //se mostrar� cu�nas veces ha aparecido
		char letra_a_mostrar = j + 'a';
		cout<< " La letra " << letra_a_mostrar;
		cout<< " ha aparecido " << letra_abecedario[j] << " veces."<<endl;
		
		if(letra_abecedario[j]==0) //si la letra no ha aparecido ninguna vez, 
								   //se suma +1 al contador que servir� despu�s
			total_letras_que_no_aparecen++;
	}
	cout<<endl;
	
	//Mostrar cu�ntos caracteres se han escrito.
	
	cout<< " Se han escrito un total de "<< total_caracteres<< " caracteres.";
	cout<< " De los cuales: "<<endl;
	cout<< " -" << total_letras<< " son letras"<< endl;
	cout<< " -" << total_espacios << " son separadores" <<endl<<endl;
	
	//Mostrar las letras que no han aparecido ninguna vez.
	
	//si hay alguna letra que no se haya mostrado ninguna vez, entonces 
	//pintamos cu�l es. Si se han mostrado todas las letras, entonces se 
	//pintar� el mensaje de "Hay 0 letras que no aparecen"
	if(total_letras_que_no_aparecen != 0){  
		cout<< " Las letras que no han aparecido ninguna vez son:";
		for(int k=0; k<TOTAL_LETRAS; k++){
		
			if(letra_abecedario[k]==0){
				char letra_a_mostrar = k + 'a';
				cout<< " " << letra_a_mostrar;
			}
		}
	}
	cout<<endl;
	cout<< " Hay "<<total_letras_que_no_aparecen<< " letras que no aparecen";
	cout<<endl<<endl;
	
	//Mostar letras m�s y menos frecuentes
	int mayor_numero_veces = total_letras;
	int posicion_mayor_numero_veces = 0;
	int posicion_menor_numero_veces = 0;
	int l;
	
	while(letra_abecedario[posicion_menor_numero_veces] == 0 && 
									posicion_menor_numero_veces<TOTAL_LETRAS){
		posicion_menor_numero_veces++;
	}
	int menor_numero_veces = letra_abecedario[posicion_menor_numero_veces];
	
	
	//calculo cu�ntas veces han salido las letras m�s y menos frecuentes. Es
	//decir, voy mirando cada uno de los valores en las casillas del vector y 
	//me guardo el valor m�s grande y m�s peque�o.
	for(l = 0; l < TOTAL_LETRAS; l++){
		if(letra_abecedario[l] > mayor_numero_veces)
			mayor_numero_veces = letra_abecedario[l];
		if(letra_abecedario[l] != 0 && letra_abecedario[l]<menor_numero_veces)
			menor_numero_veces = letra_abecedario[l];
	}

	//Las letras m�s frecuentes son aquellas que han salido el mayor numero de 
	//veces. Es decir, en las que el valor de su casilla es el mayor valor de 
	//entre todas las casillas. Las letras m�s frecuentes pueden ser varias.
	cout<< endl;
	cout<< " Las letras mas frecuentes son:";
	for(l = 0; l < TOTAL_LETRAS; l++){
		if(letra_abecedario[l] == mayor_numero_veces){
			char caracter_a_mostrar = l + 'a';
			cout<< " "<< caracter_a_mostrar; 
		} 
	}
	cout<< ". Salen "<< mayor_numero_veces << " veces."<<endl;
	
	//Las letras menos frecuentes son aquellas que han salido el menor numero de 
	//veces. Es decir, en las que el valor de su casilla es el menor valor de 
	//entre todas las casillas. Las letras menos frecuentes pueden ser varias.
	cout<< " Las letras menos frecuentes son:";
	for(l = 0; l < TOTAL_LETRAS; l++){
		if(letra_abecedario[l] == menor_numero_veces){
			char caracter_a_mostrar = l + 'a';
			cout<<  " "<<caracter_a_mostrar; 
		}
	}
	cout<< ". Salen "<< menor_numero_veces << " veces."<<endl;
	
	return 0;
}
