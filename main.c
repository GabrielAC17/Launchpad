#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

void init(),desliga();

bool mat_bot[4][4],mat_led[4][4];
int i,j;

int main (){
	init();
	while(1){
		//lógica aqui, tira esse break depois
		break;
	}
	printf("Hello World!\n");
	desliga();
}


void init(){
	//zerar matrizes de booleanos
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			mat_bot[i][j] = false;
			mat_led[i][j] = false;
		}
	}
	
	//botões
	GPIOExport(bot_lin1);
	GPIODirection(bot_lin1, INPUT);
	GPIOExport(bot_lin2);
	GPIODirection(bot_lin2, INPUT);
	GPIOExport(bot_lin3);
	GPIODirection(bot_lin3, INPUT);
	GPIOExport(bot_lin4);
	GPIODirection(bot_lin4, INPUT);
	
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
}
