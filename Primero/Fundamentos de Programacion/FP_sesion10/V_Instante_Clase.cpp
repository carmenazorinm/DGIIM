/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 7: el programa lee dos instantes diferentes y los introduce en 
	dos objetos de la clase Instante. Después, crea otro Instante que sea 
	la diferencia de tiempo entre la hora inicial y la final.
	
*/

#include<iostream> //inclusion de recursos de E/S
#include<string>
#include<iomanip>

using namespace std;

class Instante{
	//PRE: todas las variables deben ser numeros enteros positivos.
	private:
		int horas;
		int minutos;
		int segundos;
		const int SEGUNDOS_DIA = 24*3600;
	
	public:
		Instante(int num_h, int num_min, int num_seg):
			horas(num_h), minutos(num_min), segundos(num_seg)
			{
				Simplificar();
			}
		
		//devuelve la diferencia de instantes entre dos. Para eso, calcula los
		//segundos transcurridos de cada uno de los instantes y los resta. 
		//Posteriormente, se crea un nuevo instante que se inicilizará con 
		//0 horas, 0 minutos y la diferencia de segundos. luego, se 
		//simplificará la forma del Instante diferencia.
		Instante DiferenciaInstantes(Instante a, Instante b){
			int segs_a = a.SegundosTranscurridos();
			int segs_b = b.SegundosTranscurridos();
			int diferencia_segundos;
			
			if(EsDistintoDia(a,b))
				diferencia_segundos = SEGUNDOS_DIA - segs_a + segs_b;
			else
				diferencia_segundos = segs_b - segs_a;
				
			Instante diferencia(0, 0, diferencia_segundos);
			return diferencia;
		}
		
		//calcula los minutos transcurridos en un instante desde las 0h 0min 0s
		//Como en el instante, los segundos ya están simplificados para que 
		//no sean más de 60, entonces no hace falta añadir los segundos del
		//instante, porque nunca van a completar un minuto entero..
		int MinutosTranscurridos(void){
			int min_transcurridos = horas*60 + minutos;
			return min_transcurridos;
		}
		
		int SegundosTranscurridos(void){
			int seg_transcurridos = horas*3600 + minutos*60 + segundos;
			return seg_transcurridos;
		}
		
		string ToString(void){
			string cad;
			cad = " " + to_string(horas) +  " h: " + to_string(minutos) + 
				" min: " + to_string(segundos) + " s ";
			return cad;
		}
	
	private:
		//mientras que los segundos totales de un instante sean mayores que 
		//todo un día, entonces es que se cambia día.
		void Simplificar(void){
			int seg_totales = SegundosTranscurridos();
			while(seg_totales >= SEGUNDOS_DIA){
				seg_totales = seg_totales - SEGUNDOS_DIA;
			}
			horas = seg_totales/3600;
			minutos = (seg_totales%3600)/60;
			segundos = (seg_totales%3600)%60;
		}
		
		//calcula si los instantes están en diferente día. Si la hora del 
		//instante b es menor que la hora del a, entonces se ha cambiado de día.
		//En caso de que sean las horas iguales, son los minutos los que mandan.
		//si tanto las horas como los minutos son iguales, mandan los segundos.
		bool EsDistintoDia(Instante a, Instante b){
			bool cambia_dia = true;
			if(a.horas > b.horas)
				cambia_dia = true;
			else{
				if(a.horas == b.horas){
					if(a.minutos > b.minutos)
						cambia_dia = true;
					else{
						if(a.minutos == b.minutos){
							if(a.segundos > b.segundos)
								cambia_dia = true;
						}
					}
				}
			}
			return cambia_dia;	
		}
};
/****************************************************************************/

bool ComprobarQueEsPositivo (string cadena){
	
	int j = 0;
	bool es_positivo = true;
	
	if(cadena.at(0) == '+')
		j++;
	
	while(es_positivo && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_positivo = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == ' ';
		j++;
	}
		
	return es_positivo; //true si es un positivo y false si no lo es.	
}

int LeePositivo (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		cin>>respuesta;
		es_valido = ComprobarQueEsPositivo(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}

/*****************************************************************************/

int main(){
	int segundos, minutos, horas;
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	
	//aunque las horas sean más de 24, o los minutos más de 59, al introducir
	//los datos en un objeto de la clase Instante, se simplificarán los datos
	//para que pertenezcan a un día.
	cout<< " Introduzca un instante: "<< endl;
	horas = LeePositivo(" Horas: ");
	minutos = LeePositivo(" Minutos: ");
	segundos = LeePositivo(" Segundos: ");
	
	Instante instante_inicial(horas, minutos, segundos);
	cout<< " El instante inicial introducido es "<<instante_inicial.ToString();
		
	cout<<endl<<endl;
	cout<< " Introduzca un instante: "<< endl;
	horas = LeePositivo(" Horas: ");
	minutos = LeePositivo(" Minutos: ");
	segundos = LeePositivo(" Segundos: ");
	
	Instante instante_final(horas, minutos, segundos);
	cout<< " El instante final introducido es "<<instante_final.ToString();
	
	//CALCULOS
	
	Instante inst_diferencia = 
	inst_diferencia.DiferenciaInstantes(instante_inicial, instante_final);
	
	//SALIDA
	
	cout<<endl<<endl;
	cout<<" La diferencia entre los tiempos es "<< inst_diferencia.ToString();
	cout<<endl << " Los segundos totales transcurridos son "
		<<inst_diferencia.SegundosTranscurridos()<<" s"<<endl;
	cout<< " Los minutos totales transcurridos son "
		<<inst_diferencia.MinutosTranscurridos()<<" min";
		
	cout<<endl<<endl;
	return 0;
}
