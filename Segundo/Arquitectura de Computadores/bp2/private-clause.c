/**
 * 
 Cláusula private
 *
 **/

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif
/**
 * @file  private-clause.c 
 * @brief _Parte del código de suma paralalela_
 * @return 0 upon exit success (print la variable suma dentro y fuera del <tt>parallel</tt>)
 *  
 * **Objetivo**
 * 
 * El código usa:
 * 
 * - Directivas <tt>parallel, for</tt> 
 * - Cláusulas <tt>private</tt> 
 * - Funciones <tt>omp_get_thread_num()</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o private-clause private-clause.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * private-clause 
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main()
{
   int i, n = 7;
   int a[n],suma=2;

   for (i=0; i<n; i++)
      a[i] = i;

#pragma omp parallel private(suma) shared(a)
{
   suma=0;
   #pragma omp for 
   for (i=0; i<n; i++)
   {
   	//printf("suma inicial = %d", suma);
       suma = suma + a[i];
       printf("Hebra %d suma a[%d] / ",
             omp_get_thread_num(),i);
   } 
   printf("\n* Hebra %d suma= %d",
             omp_get_thread_num(),suma);
}
   printf("\n"); 
   printf("[thread %d] suma=%d\n",omp_get_thread_num(),suma);
   return(0);
}
