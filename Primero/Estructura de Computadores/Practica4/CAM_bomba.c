// gcc -O2 CAM_bomba.c -o CAM_bomba -no-pie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 11
#define TLIM 5

char contras[SIZE] = "animoFiera";
int pin			= 9876;

void boom(){
	printf("\n"
			 "*****************\n"
			 "* CAGASTE *******\n"
			 "*****************\n"
			 "\n");
	exit(-1);
}

void defused(){
	printf("\n"
			 "*****************\n"
			 "* BIEN HECHO ****\n"
			 "*****************\n"
			 "\n");
	exit(0);
}

void codifica(char palabra[]){
	for(int i = 0; i < SIZE; i++){
		if(palabra[i] != ' ')
			palabra[i] = palabra[i]+1;
	} 
}

int codifica_pin(int pin){
	int resul = pin*368+24;
	return resul;
}

int main(){
	char contras_leida[SIZE];
	int pin_leido,n;
	
	do printf("\nIntroduce la contraseña: ");
	while (fgets(contras_leida, SIZE, stdin) == NULL);
	
	codifica(contras_leida);
	// printf("%s",contras_leida);
	codifica(contras);
	// printf("%s\n",contras);
	
	if(strncmp(contras_leida, contras, sizeof(contras)))
		boom();
	
	do{ printf("\nIntroduce el pin: ");
		if((n = scanf("%i",&pin_leido))== 0)
			scanf("%*s") == 1;
		}
	while(n!= 1);
	
	int pin_leido_cod = codifica_pin(pin_leido);
	int pin_cod = codifica_pin(pin);
	
	if(pin_leido_cod != pin_cod)
		boom();
	
	defused();
}
