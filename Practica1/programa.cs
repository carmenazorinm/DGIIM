
/*El ayuntamiento de Gijon, se dispone a otorgar subenciones a jovenes trabajadores en riesgo de
exclusión social, los requisitos para acceder a la ayuda son los siguientes.
-Edad comprendia entre 18 y 38 años.
-Sueldo maximo de 1100 euros para solicitantes que no tengan hijos a su cargo, esta cuantia será
incrementada en un 9 porciento para solicitantes con un hijo a su cargo, en un 11 porciento para los
que tengan dos hijos a su cargo, y en un 17 por ciento para los que tengan tres o mas hijos a su
cargo.
Elabora un programa que determine si el solicitante cumple o no los requisitos exigidos para
acceder a la ayuda.*/
//Clase Requisitos
//Fecha : 18/11/2022
//Autor: Adrian Suarez
//Se dispone de dos metodos
//Edadcorrecta. Devuelve si es verdad que cumple los parametros exigidos
//Sueldomaximo. Devuelve el sueldo maximo exigido dependiendo del numero de hijos

using System;
// metodo para calcular si la edad esta dentro de el rango exigido
namespace Requisitos
{
  class Programa
  {
    bool edad_correcta (int edad)
    {
      bool Edadcorrecta = false;
      if (edad >= 18) && (edad <= 38) Edadcorrecta= true;
      return Edadcorrecta;
    }

    //metodo para calcular el sueldo maximo
    double calcular_sueldo_max (int nhijos)
    {
      double sueldo = 1100;
      double cantidad_aniadida;
      switch(nhijos)
      {
        case 0: cantidad_aniadida = 0; break;
        case 1: cantidad_aniadida = sueldo*0.09; break;
        case 2: cantidad_aniadida = sueldo*0.11; break;
        default: cantidad_aniadida = sueldo*0.17; break;
      }
      sueldo = sueldo + cantidad_aniadida;
      return sueldo;
    }

    static void main(String[] args)
    {
      int edad, n_hijos;
      int sueldo;
        Console.WriteLine("Inserte su edad: ");
        edad = int.Parse(Console.ReadLine());
        Console.WriteLine("Inserte número de hijos: ");
        n_hijos = int.Parse(Console.ReadLine());
        Console.WriteLine("Inserte sueldo:" );
        sueldo = int.Parse(Console.ReadLine());

        if(edad_correcta(edad))
        {
          double sueldo_maximo = calcular_sueldo_maximo(n_hijos);
          if(sueldo < sueldo_maximo)
          {
            Console.WriteLine("Has sido admitido");
          }
          else
          {
            Console.WriteLine("Su sueldo es demasiado alto para la subvencion");
          }

        }
        else
        {
          Console.WriteLine("No se tiene la edad requerida para subvencion");
        }
    }
  }
}
