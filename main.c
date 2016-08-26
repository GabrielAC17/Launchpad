#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

//Funções relacionadas ao GPIO
#include "lp.h"

//Funções relacionadas a fila circular
#include "fila.h"

//Multiplexação de botões 4x4
#define bot_lin1 0
#define bot_lin2 1
#define bot_lin3 2
#define bot_lin4 3

#define bot_col1 4
#define bot_col2 5
#define bot_col3 6
#define bot_col4 7

//Multiplexação de leds 4x4
#define led_lin1 8
#define led_lin2 9
#define led_lin3 10
#define led_lin4 11

#define led_col1 12
#define led_col2 13
#define led_col3 14
#define led_col4 15

//Define até quantos elementos de aúdio de uma coluna podem ser colocados na fila
#define list_size 10


//Funções do programa
void init(),desliga();
//Funções que iniciam em uma nova thread:
void * ler_bot(void * threadid), *update_leds(void * threadid);

bool mat_bot[4][4],mat_led[4][4];
int aux_bot;
int i,j;

//Fila circular, uma para cada coluna em reprodução
Fila playlist[4];

//Variáveis de thread!
//Thread 1: ler botões
//Thread 2: atualizar LED's
pthread_t thread;
pthread_t thread2;

int rc;
int rc2;

long t;
long t2;
//Fim das variáveis de thread


int main (){
	init();
	while(1){
		aux_bot=0;
		for (i=0;i<4;i++){
			for (j=0;j<4;j++){
				if (mat_bot[i][j]==true){
					mat_led[i][j] = true;
					aux_bot++;
					push(aux_bot, &playlist[i]);
				}
			}
		}
		
	}
	desliga();
	return 0;
}

void init(){
	for (i=0;i<4;i++){
		iniciar(list_size ,&playlist[i]);
	}
	
	//zerar matrizes de booleanos
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			mat_bot[i][j] = false;
			mat_led[i][j] = false;
		}
	}
	
	//botões
	GPIOExport(bot_lin1);
	GPIODirection(bot_lin1, OUTPUT);
	GPIOExport(bot_lin2);
	GPIODirection(bot_lin2, OUTPUT);
	GPIOExport(bot_lin3);
	GPIODirection(bot_lin3, OUTPUT);
	GPIOExport(bot_lin4);
	GPIODirection(bot_lin4, OUTPUT);
	
	GPIOExport(bot_col1);
	GPIODirection(bot_col1, INPUT);
	GPIOExport(bot_col2);
	GPIODirection(bot_col2, INPUT);
	GPIOExport(bot_col3);
	GPIODirection(bot_col3, INPUT);
	GPIOExport(bot_col4);
	GPIODirection(bot_col4, INPUT);
	
	//leds
	GPIOExport(led_lin1);
	GPIODirection(led_lin1, OUTPUT);
	GPIOExport(led_lin2);
	GPIODirection(led_lin2, OUTPUT);
	GPIOExport(led_lin3);
	GPIODirection(led_lin3, OUTPUT);
	GPIOExport(led_lin4);
	GPIODirection(led_lin4, OUTPUT);
	
	GPIOExport(led_col1);
	GPIODirection(led_col1, OUTPUT);
	GPIOExport(led_col2);
	GPIODirection(led_col2, OUTPUT);
	GPIOExport(led_col3);
	GPIODirection(led_col3, OUTPUT);
	GPIOExport(led_col4);
	GPIODirection(led_col4, OUTPUT);
	
	rc = pthread_create(&thread,NULL,ler_bot,(void*)t);
	if (rc){
		printf("Init. Failed! Cannot start thread ler_bot.\n");
		exit(-1);
	}
	
	rc2 = pthread_create(&thread2,NULL,update_leds,(void*)t2);
	if (rc2){
		printf("Init. Failed! Cannot start thread update_leds\n");
		exit(-1);
	}
}

void desliga(){
	//botões
	GPIOUnexport(bot_lin1);
	GPIOUnexport(bot_lin2);
	GPIOUnexport(bot_lin3);
	GPIOUnexport(bot_lin4);
	
	GPIOUnexport(bot_col1);
	GPIOUnexport(bot_col2);
	GPIOUnexport(bot_col3);
	GPIOUnexport(bot_col4);
	
	//leds
	GPIOUnexport(led_lin1);
	GPIOUnexport(led_lin2);
	GPIOUnexport(led_lin3);
	GPIOUnexport(led_lin4);
	
	GPIOUnexport(led_col1);
	GPIOUnexport(led_col2);
	GPIOUnexport(led_col3);
	GPIOUnexport(led_col4);
	
	
	pthread_exit(NULL);
}

void * ler_bot(void * threadid)
{

}

void * update_leds(void * threadid)
{

}
