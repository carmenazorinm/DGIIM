#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
 
    #pragma omp parallel
	{		
	 #pragma omp for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);
    }
    
    #pragma omp single
    {
    	printf("%d, %d, %d", omp_get_num_threads(),omp_get_num_procs(),omp_in_parallel());
    }
	}
	    printf("Fuera de 'parallel for' suma=%d\n",suma); 
	    
	    printf("%d, %d, %d", omp_get_num_threads(),omp_get_num_procs(),omp_in_parallel());
	    
}

