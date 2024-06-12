/**
 * 
 * Directiva parallel
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
   int Hebra;

   if(argc < 2)     {
    fprintf(stderr,"\n[ERROR] -: Hay un parámetros de entrada: número de hebra \n");
          exit(-1);
     }
   Hebra = atoi(argv[1]);

#pragma omp parallel 
   {
     if ( omp_get_thread_num() < Hebra ) 
        printf("  Hebra %d realiza la tarea 1\n",
               omp_get_thread_num());
     else 
	printf("  Hebra %d realiza la tarea 2\n",
               omp_get_thread_num());
   }

   return(0);
}
