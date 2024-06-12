/**
 * 
Calculo PI con procesadores
 * 
 */
 #include<math.h>
#include <stdlib.h> // biblioteca con funciones atoi(), rand(), srand(), malloc() y free()
#include <stdio.h>  // biblioteca donde se encuentra la función printf()
#ifdef _OPENMP
#include <omp.h>
#else
	#define omp_get_max_threads() 1
#endif 
/**
 * @file  pi_cop.c 
 * @brief #### calculo pi con coprocesadores ####
 *
 * @author Carme Azorin
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
main (int argc, char **argv)
{
	register double width;
	double sum=0;
	register int intervals, i;
	
	double t0, t1, t2, t3;
	
	//Comprobacion de argumentos
	if (argc<2){
		fprintf(stderr, "\nFalta numero intervalos\n");
		exit(-1);
	}
	
	intervals=atoi(argv[1]);
	if(intervals<1) intervals=1;
	width=1.0/intervals;
	
	t0=omp_get_wtime();
	
	#pragma omp target enter data map(to: intervals, width, sum)
	t1=omp_get_wtime();
	

	#pragma omp target teams distribute parallel for reduction(+:sum)
	for (i=0; i<intervals; i++){
		register double x=(i+0.5)*width;
		sum+=4.0/(1.0+x*x);
	}
	sum*=width;
	
	t2=omp_get_wtime();
	
	#pragma omp target exit data map (delete: intervals, width) map(from: sum)
	t3= omp_get_wtime();	
	sum*=width;
	
	double error=fabs(M_PI-sum);
	printf("Error: %d\n",error);
	
	//t=omp_get_wtime()-t;
	 
	double r1=t1-t0;
	double r2=t2-t1;
	double r3=t3-t2;
	
	printf ("Iteraciones:\t%d\t \nPi:\t%26.24f\t \nThreads:\t%d\t \nTiempo hacia GPU:\t%8.6f\t \nTiempo  calculo PI:\t%8.6f\t  \nTiempo desde GPU:\t%8.6f\n\n", intervals, sum, omp_get_max_threads(),r1,r2,r3);
	
	return (0);
}
