#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv){

int i=0, sum =0;
#pragma omp parallel shared(i)
{
for(i=0; i<5; ++i)
{
	#pragma omp atomic
	sum += i;
}
}
printf("Suma = %d\n",sum);
}
