/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 22: el programa está formado por tres clases. 
	1) Punto2D: esta clase está formada por puntos con abscisa y ordenada.
	2) Triangulo: está formada por los vertices de triángulos guardados cada
	uno de ellos como Puntos2D. 
	3) Rectangulo: está formada por el Punto2D de la esquina superior izquierda
	y por los datos double longitud de la base (b) y de la altura (a).
	
*/

#include <iostream>
#include <cctype>
#include <cmath>
#include <iomanip>
using namespace std;

/***************************************************************************/
// Función global (asociada a la constante PRECISION_SON_IGUALES) que
// permite que dos números reales muy próximos sean considerados iguales.

const double PRECISION_SON_IGUALES = 1e-6; // 0.000001

bool SonIguales(double uno, double otro) 
{
	return (fabs(uno-otro) <= PRECISION_SON_IGUALES);
}

/////////////////////////////////////////////////////////////////////////////

class Punto2D
{
private:
	
	// La pareja (x,y) son las coordenadas de un punto en un espacio 2D
	double x;
	double y;

public:
	
	/***********************************************************************/
	// Constructor con argumentos.
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está creando.
	
	Punto2D (double abscisaPunto, double ordenadaPunto)
	{
		SetCoordenadas (abscisaPunto, ordenadaPunto);
	}
	
	/***********************************************************************/
	// Constructor sin argumentos.
	//
	// No recibe nada y inicializa el punto en la coordenada (0,0)
	
	Punto2D (void)
	{
		SetCoordenadas (0, 0);
	}

	/***********************************************************************/
	// Método Set para fijar simultaneamente las coordenadas. 
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está modificando.
	
	void SetCoordenadas (double abscisaPunto, double ordenadaPunto)
	{
		x = abscisaPunto;
		y = ordenadaPunto;
	}

	/***********************************************************************/
	// Métodos Get para leer las coordenadas

	double GetX (void)
	{
		return (x);
	}
	double GetY (void)
	{
		return (y);
	}

	/***********************************************************************/
	// Calcula si dos puntos son iguales 
	//
	// Recibe: otro, el punto que se quiere comparar con el objeto implícito. 
	// Devuelve: true, si se consideran iguales los dos objetos. 

	bool EsIgual (Punto2D otro)
	{
		return (SonIguales(x,otro.x) && SonIguales(y,otro.y));
	}

	/***********************************************************************/
	// Calcula la distancia Euclídea del punto (objeto implícito) a otro que 
	// se recibe como argumento. 
	//
	// Recibe: otro, el punto respecto al cual que se quiere calcular la 
	// distancia euclídea.
	// Devuelve: la distancia entre los dos puntos. 

	double DistanciaEuclidea (Punto2D otro)
	{
		double dif_x = pow (x - otro.x, 2);
		double dif_y = pow (y - otro.y, 2);

		return (sqrt(dif_x + dif_y));
	}

	/***********************************************************************/

	string ToString ()
	{
		return ("["+to_string(x)+", "+to_string(y)+"]");
	}
	
	/***********************************************************************/

};

///////////////////////////////////////////////////////////////////////////
class Triangulo{

private: 
	Punto2D vertice_a;
	Punto2D vertice_b;
	Punto2D vertice_c;
	
public:
	/*************************************************************/
	//constructor sin argumentos
	Triangulo(void){
		vertice_a.SetCoordenadas(0,0);
		vertice_b.SetCoordenadas(0,0);
		vertice_c.SetCoordenadas(0,0);
	}
	
	/*************************************************************/
	//constructor con argumentos
	Triangulo(Punto2D va, Punto2D vb, Punto2D vc):
		vertice_a(va), vertice_b(vb), vertice_c(vc)
		{}
	
	/*************************************************************/
	Punto2D GetVerticeA(void){
		return vertice_a;
	}
	
	/*************************************************************/
	Punto2D GetVerticeB(void){
		return vertice_b;
	}
	
	/*************************************************************/
	Punto2D GetVerticeC(void){
		return vertice_c;
	}
	
	/*************************************************************/
	void SetVerticeA(Punto2D a){
		vertice_a = a;
	}
	
	/*************************************************************/
	void SetVerticeB(Punto2D b){
		vertice_b = b;
	}
	
	/*************************************************************/
	void SetVerticeC(Punto2D c){
		vertice_c = c;
	}
	
	/*************************************************************/
	//para calcular el perímetro del triangulo calculamos la distancia entre
	//cada uno de sus vertices y los sumamos.
	double Perimetro(void){
		double perimetro = vertice_a.DistanciaEuclidea(vertice_b) + 
						   vertice_b.DistanciaEuclidea(vertice_c) + 
						   vertice_c.DistanciaEuclidea(vertice_a);
		return perimetro;	
	}
	
	/*************************************************************/
	//metodo que calcula si un triangulo es rectangulo. Un triangulo es 
	//rectangulo si, y solo si, cumple el teorema de pitagoras. 
	//Por tanto, calcularemos cada una de las posibilidades de un triangulo
	//rectangulo. Es decir, probamos si la hipotenusa es la distancia_a_b;
	//si la hipotenusa es la distancia_b_c; o si la hipotenusa en la 
	//distancia_a_c. En caso de que no sea ninguna de estas, entonces se
	//quedaría comprobado que el triangulo no es rectangulo.
	bool EsTrianguloRectangulo(void){
		bool es_rectangulo = false;
		double distancia_a_b = vertice_a.DistanciaEuclidea(vertice_b);
		double distancia_b_c = vertice_b.DistanciaEuclidea(vertice_c);
		double distancia_a_c = vertice_c.DistanciaEuclidea(vertice_a);
		
		if(distancia_a_b == sqrt(distancia_b_c*distancia_b_c + 
												distancia_a_c* distancia_a_c))
			es_rectangulo = true;
		else{
			if(distancia_a_c == sqrt(distancia_b_c*distancia_b_c + 
												distancia_a_b* distancia_a_b))
				es_rectangulo = true;
			else{
				if(distancia_b_c == sqrt(distancia_a_b*distancia_a_b + 
												distancia_a_c* distancia_a_c))
					es_rectangulo = true;
					
			}
			
		}
		return es_rectangulo;
	}
	
	/*****************************************************************/
	string ToString(void){
		string cad = " ( "+ vertice_a.ToString() +" ) ( "+ vertice_b.ToString()
					+ " ) ( " + vertice_c.ToString() + " )";
		
		return cad;
	}

};

//////////////////////////////////////////////////////////////////////////////

class Rectangulo{

private:
	Punto2D esi; //punto de la esquina superior izquierda
	double b; //longitud de la base
	double a; //longitud de la altura

public:
	/*************************************************************/
	//constructor sin argumentos
	Rectangulo(void){ 
		esi.SetCoordenadas(0,0); 
		b = 0;
		a = 0;	
		}
	
	/**************************************************************/
	//constrcutor con argumentos (valores de esi, b y a)
	Rectangulo(Punto2D esquina, double base, double altura):
		esi(esquina), b(base), a(altura)
		{}
	
	/*************************************************************/
	Punto2D GetESI(void){
		return esi;
	}
	
	/*************************************************************/
	double Getb(void){
		return b;
	}
	
	/*************************************************************/
	double Geta(void){
		return a;
	}
	
	/*************************************************************/
	//calcula el area. area=base*altura
	double Area(void){
		return b*a;
	}
	
	/*************************************************************/
	//calcula el perímetro. perimetro = base + base + altura + altura
	double Perimetro(void){
		return(2*b + 2*a);
	}
	
	/*************************************************************/
	//el método calcula si un punto está dentro del rectangulo. Para que esto
	//ocurra es necesario que la x del punto se encuentre entre las abscisas
	//de la esquina superior derecha y de la esquina inferior izquierda.
	//Además, es necesario que la y del punto se encuentre entre las ordenadas
	//de la esquina superior izquierda y de la esquina inferior derecha.
	bool Contiene(Punto2D punto){
		bool contenido = false;
		Punto2D eid(EID());
		
		if(punto.GetX() >= esi.GetX() && punto.GetX() <= eid.GetX()){
			
			if(punto.GetY() <= esi.GetY() && punto.GetY() >= eid.GetY())
				contenido = true;
		}
		
		return contenido;
	}
	
	/*************************************************************/
	//el triangulo superior de un rectangulo tendrá como vertices las 
	//esquinas superiores del rectangulo y la esquina inferior derecha, que es
	//donde termina la diagonal principal del rectangulo.
	Triangulo TrianguloSuperior(void){
		Triangulo triangulo_superior;
		triangulo_superior.SetVerticeA(esi);
		triangulo_superior.SetVerticeB(ESD());
		triangulo_superior.SetVerticeC(EID());
		
		return triangulo_superior;
	}
	
	/**************************************************************/
	//el triangulo inferior de un rectangulo tendrá como vertices las
	//esquinas inferioes del rectangulo y la esquina superior izquierda,
	// que es donde empieza la diagonal no princiapl del rectangulo.
	Triangulo TrianguloInferior(void){
		Triangulo triangulo_inferior;
		triangulo_inferior.SetVerticeA(esi);
		triangulo_inferior.SetVerticeB(EII());
		triangulo_inferior.SetVerticeC(EID());
		
		return triangulo_inferior;
	}
	
	/****************************************************************/
	string ToString(void){
		string cad = " ( "+esi.ToString() + " ) ( "+ EID().ToString() + " ) ";
		
		return cad;
	}
	
private:
	/*************************************************************/	
	//la esquina superior derecha tiene como abscisa la abscisa de la 
	//esquina superior izquierda más la base; la ordenada es igual.
	Punto2D ESD(void){
		Punto2D esd(esi.GetX()+b, esi.GetY());
		
		return esd;
	}
	
	/*************************************************************/
	//la esquina inferior izquierda tiene la misma abscisa que la esquina
	//superior izquierda; la ordenada es la ordenada de la esquina superior 
	//izquierda menos la altura.
	Punto2D EII(void){
		Punto2D eii(esi.GetX(), esi.GetY()-a);
		
		return eii;
	}
	
	/*************************************************************/
	//la esquina inferior derecha tiene la abscisa de la esquina superior 
	//izquierda más la base; la ordena de la esquina superior izuierda menos
	//la altura
	Punto2D EID(void){
		Punto2D eid(esi.GetX()+b, esi.GetY()-a);
		
		return eid;
	}
	
	/*************************************************************/	
};

//////////////////////////////////////////////////////////////////////////////

int main (void)
{
    cout.setf(ios::fixed);        // Notación de punto fijo para los reales
    cout.setf(ios::showpoint);    // Mostrar siempre decimales 


    // Crear un rectángulo
    Rectangulo r (Punto2D(10,8), 6, 2);

    cout << "Rectangulo:" << endl;
    cout << r.ToString() << endl;

    cout << "Area = " << r.Area() << endl;
    cout << "Perimetro = " << r.Perimetro() << endl;
    cout << endl << endl;
    
    // Pruebas de pertenencia a un rectángulo
    cout << "Pertenencia a Rectangulo: " << endl;    
    cout << (Punto2D(12,11).ToString()) << " --> " 
         << ((r.Contiene (Punto2D(12,11))) ? "SI":"NO") << endl; 
    cout << (Punto2D(9,8).ToString()) << " --> " 
         << ((r.Contiene (Punto2D(9,8))) ? "SI":"NO") << endl; 
    cout << (Punto2D(16,8).ToString()) << " --> " 
         << ((r.Contiene (Punto2D(16,8))) ? "SI":"NO") << endl; 
    cout << endl;
    
    
    // Crear un triángulo
    Triangulo t (Punto2D(12,7), Punto2D(17,11), Punto2D(20,7));
    
    cout << "Triangulo:" << endl;
    cout << t.ToString() << endl;        
    cout << "Perimetro = " << t.Perimetro() << endl;    
    cout << endl << endl;    
    
    // Crear otro triángulo    (rectángulo)
    Triangulo tr (Punto2D(10,3), Punto2D(10,6), Punto2D(16,6));

    cout << "Triangulo rectangulo:" << endl;    
    cout << tr.ToString() << endl;    
    cout << endl << endl;
    cout << (tr.EsTrianguloRectangulo() ? "SI":"NO") << endl;
    
    // Crear un triángulo a partir de un rectángulo (triángulo inferior) 
    Triangulo t_inf = r.TrianguloInferior();

    cout << "Triangulo inferior del rectangulo:" << endl;    
    cout << t_inf.ToString() << endl;    
    cout << endl << endl;
    
    // Crear otro triángulo a partir de un rectángulo (triángulo superior) 
    Triangulo t_sup = r.TrianguloSuperior();

    cout << "Triangulo superior del rectangulo:" << endl;    
    cout << t_sup.ToString() << endl;    
    cout << endl << endl; 
        
    return 0;
}


