/**
 * 
Calculo PI con procesadores
 * 
 */
#include <stdlib.h> // biblioteca con funciones atoi(), rand(), srand(), malloc() y free()
#include <studio.h>  // biblioteca donde se encuentra la función printf()
#ifdef _OPENMP
#include <omp.h>
#else
	#define omp_get_max_threads() 1
#endif 
/**
 * @file  pi_cop.c 
 * @brief #### calculo pi con coprocesadores ####
 *
 * @author Maria Cribilles Perez
 * 
 * @param intervals=atoi(argv[1]);  numero de intervalos de integración
 * 
 * **Compilación en atcgrid4:**
 * @code
 * sbatch -pac4 -Aac --wrap "nvc -O2 -openmp -mp=gpu pi_cop.c -o pi_cop_GPU"
 * @endcode
 * 
 *  **Ejecución en atcgrid4:**
 * ~~~~~~~~~~~~~~~~~~~~~
 *srun -pac4 -Aac pi_cop_GPU 1000000    (siendo 1000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
main (int arg, char **argv)
{
	register double width, x;
	double sum=0;
	register int intervals, i;
	
	double t;
	
	//Comprobacion de argumentos
	if (argc<2){
		fprintf(stderr, "\nFalta numero intervalos\n");
		exit(-1);
	}
	
	intervals=atoi(argv[1]);
	if(intervals<1) intervals=1;
	
	t=omp_get_wtime();
	
	width=1.0/intervals;
	
	#pragma omp parallel 
	{
		#pragma omp for reduction (+:sum) private(x)
		for (i=0; i<intervals; i++){
			x=(i+0.5)*width;
			sum+=4.0/(1.0+x*x);
		}
	}
	
	sum*=width;
	
	t=omp_get_wtime()-t;
	
	printf ("Iteraciones:\t%d\t. Pi:\t%26.24f\t. Threads:\t%d\t. Tiempo:\t%8.6f\n", intervals, sum, omp_get_max_threads(),t);
	
	return (0);
}
