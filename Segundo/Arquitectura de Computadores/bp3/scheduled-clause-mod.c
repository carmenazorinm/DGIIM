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
    omp_sched_t kind;
    int chunk_size=0;
    
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
    #pragma omp for  firstprivate(suma) lastprivate(suma,kind) schedule(dynamic ,chunk)
    for (i=0; i<n; i++)
    {
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);
       
       //este for se va a ejecutar con schedule(static,chunk)
       //sin embargo, esta cláusula no modifica el run-ched-var, por tanto, va a salir lo que se
       //haya puesto en el último export OMP_SCHEDULE="monotonic:dynamic,8".
       //pero el for se ejecuta con la cláusula
    	omp_get_schedule(&kind,&chunk_size);
    	//podemos también utilizar aqui omp_set_schedule(1,2); y cambiarían los valores que se 
    	//imprimirían después, pero el for sigue haciendose con la clausula
    }
    #pragma omp single
        {
        int ch=chunk;
        printf(" thread=%d\n",omp_get_thread_num());
        printf(" dyn_var=%d\n",omp_get_dynamic());
    	printf(" nthreads_var=%d\n",omp_get_max_threads());
    	printf(" thread_limit_var=%d\n",omp_get_thread_limit());
    	//en run-ched-var van a salir unos valores que no son los que en realidad se han utilizado en el for
    	printf("run_sched_var(kind=%x,chunk=%d)\n",kind,chunk_size);
    	}
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
    
    //modificamos los valores del runtime
    omp_set_schedule(1,2);
    printf(" dyn_var=%d\n",omp_get_dynamic());
    printf(" nthreads_var=%d\n",omp_get_max_threads());
    printf(" thread_limit_var=%d\n",omp_get_thread_limit());
    	omp_get_schedule(&kind,&chunk_size);
    	//aquí se imprimen los valores del runtime igual que antes
    	printf("run_sched_var(kind=%x,chunk=%d)\n",kind,chunk_size);
}

