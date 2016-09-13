#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

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

//Define tempo de espera de leitura dos botões (ms)
#define button_mdelay 200

//Define tempo de espera de escrita dos leds (ms)
#define led_mdelay 10

//Funções do programa
void init(),desliga();
//Funções que iniciam em uma nova thread:
void * ler_bot(void * threadid), *update_leds(void * threadid),* coluna1(void * threadid),* coluna2(void * threadid),* coluna3(void * threadid),* coluna4(void * threadid);

bool mat_bot[4][4],mat_led[4][4];
int aux_bot;
int i,j;

//Fila circular, uma para cada coluna em reprodução
Fila playlist[4];

//Variáveis de thread!
//Thread 1: ler botões
//Thread 2: atualizar LED's
//Threads 3 a 6: Filas(Colunas) de reprodução
pthread_t thread;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
pthread_t thread5;
pthread_t thread6;

int rc;
int rc2;
int rc3;
int rc4;
int rc5;
int rc6;

long t;
long t2;
long t3;
long t4;
long t5;
long t6;
//Fim das variáveis de thread

char* cwd;
char buff[1025];
char dir[3000];

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
	//Inicia lista
	for (i=0;i<4;i++){
		iniciar(list_size ,&playlist[i]);
	}
	
	//Pega diretório do executável e cria comando para o player.
	cwd = getcwd( buff, 1025 );
    if( cwd != NULL ) {
        printf( "Diretorio de musicas: %s/audios/. Crie o diretorio se nao houver e cole as musicas (1.mp3 a 16.mp3)\n", cwd );
    }
    else {
    	printf("Error while getting dir path.\n");
    	exit(-1);
    }
    snprintf(dir, sizeof(dir),"mpg123 %s/audios/", cwd);
    
	
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
	
	rc3 = pthread_create(&thread3,NULL,coluna1,(void*)t3);
	if (rc3){
		printf("Init. Failed! Cannot start thread coluna1\n");
		exit(-1);
	}
	
	rc4 = pthread_create(&thread4,NULL,coluna2,(void*)t4);
	if (rc4){
		printf("Init. Failed! Cannot start thread coluna2\n");
		exit(-1);
	}
	
	rc5 = pthread_create(&thread5,NULL,coluna3,(void*)t5);
	if (rc5){
		printf("Init. Failed! Cannot start thread coluna3\n");
		exit(-1);
	}
	
	rc6 = pthread_create(&thread6,NULL,coluna4,(void*)t6);
	if (rc6){
		printf("Init. Failed! Cannot start thread coluna4\n");
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
	while(1){
		GPIOWrite(bot_lin1,HIGH);
		GPIOWrite(bot_lin2,LOW);
		GPIOWrite(bot_lin3,LOW);
		GPIOWrite(bot_lin4,LOW);

		mat_bot[1][1] = GPIORead(bot_col1);
		mat_bot[1][2] = GPIORead(bot_col2);
		mat_bot[1][3] = GPIORead(bot_col3);
		mat_bot[1][4] = GPIORead(bot_col4);
		
		
		GPIOWrite(bot_lin1,LOW);
		GPIOWrite(bot_lin2,HIGH);
		GPIOWrite(bot_lin3,LOW);
		GPIOWrite(bot_lin4,LOW);
		
		mat_bot[2][1] = GPIORead(bot_col1);
		mat_bot[2][2] = GPIORead(bot_col2);
		mat_bot[2][3] = GPIORead(bot_col3);
		mat_bot[2][4] = GPIORead(bot_col4);
		
		
		GPIOWrite(bot_lin1,LOW);
		GPIOWrite(bot_lin2,LOW);
		GPIOWrite(bot_lin3,HIGH);
		GPIOWrite(bot_lin4,LOW);
		
		mat_bot[3][1] = GPIORead(bot_col1);
		mat_bot[3][2] = GPIORead(bot_col2);
		mat_bot[3][3] = GPIORead(bot_col3);
		mat_bot[3][4] = GPIORead(bot_col4);
		
		
		GPIOWrite(bot_lin1,LOW);
		GPIOWrite(bot_lin2,LOW);
		GPIOWrite(bot_lin3,LOW);
		GPIOWrite(bot_lin4,HIGH);
		
		mat_bot[4][1] = GPIORead(bot_col1);
		mat_bot[4][2] = GPIORead(bot_col2);
		mat_bot[4][3] = GPIORead(bot_col3);
		mat_bot[4][4] = GPIORead(bot_col4);
		usleep(button_mdelay * 1000);
	}
}

void * update_leds(void * threadid)
{
	while(1){
		GPIOWrite(led_lin1,HIGH);
		GPIOWrite(led_lin2,LOW);
		GPIOWrite(led_lin3,LOW);
		GPIOWrite(led_lin4,LOW);
		
		GPIOWrite(led_col1,mat_led[1][1]);
		GPIOWrite(led_col2,mat_led[1][2]);
		GPIOWrite(led_col3,mat_led[1][3]);
		GPIOWrite(led_col4,mat_led[1][4]);
		usleep(led_mdelay);
		
		
		GPIOWrite(led_lin1,LOW);
		GPIOWrite(led_lin2,HIGH);
		GPIOWrite(led_lin3,LOW);
		GPIOWrite(led_lin4,LOW);
		
		GPIOWrite(led_col1,mat_led[2][1]);
		GPIOWrite(led_col2,mat_led[2][2]);
		GPIOWrite(led_col3,mat_led[2][3]);
		GPIOWrite(led_col4,mat_led[2][4]);
		usleep(led_mdelay);
		
		
		GPIOWrite(led_lin1,LOW);
		GPIOWrite(led_lin2,LOW);
		GPIOWrite(led_lin3,HIGH);
		GPIOWrite(led_lin4,LOW);
		
		GPIOWrite(led_col1,mat_led[3][1]);
		GPIOWrite(led_col2,mat_led[3][2]);
		GPIOWrite(led_col3,mat_led[3][3]);
		GPIOWrite(led_col4,mat_led[3][4]);
		usleep(led_mdelay);
		
		
		GPIOWrite(led_lin1,LOW);
		GPIOWrite(led_lin2,LOW);
		GPIOWrite(led_lin3,LOW);
		GPIOWrite(led_lin4,HIGH);
		
		GPIOWrite(led_col1,mat_led[4][1]);
		GPIOWrite(led_col2,mat_led[4][2]);
		GPIOWrite(led_col3,mat_led[4][3]);
		GPIOWrite(led_col4,mat_led[4][4]);
		usleep(led_mdelay);
	}
}

void * coluna1(void * threadid){
	int * fila;
	unsigned int qtde;
	while (1){
		fila = listar(playlist[0],&qtde);
		if (!vazia(playlist[0])){
			//system("mpg123 ");
		}
	}
}

void * coluna2(void * threadid){
	int * fila;
	unsigned int qtde;
	while (1){
		fila = listar(playlist[1],&qtde);
		if (!vazia(playlist[1])){
			//system("mpg123 ");
		}
	}
}

void * coluna3(void * threadid){
	int * fila;
	unsigned int qtde;
	while (1){
		fila = listar(playlist[2],&qtde);
		if (!vazia(playlist[2])){
			//system("mpg123 ");
		}
	}
}

void * coluna4(void * threadid){
	int * fila;
	unsigned int qtde;
	while (1){
		fila = listar(playlist[3],&qtde);
		if (!vazia(playlist[3])){
			//system("mpg123 ");
		}
	}
}
