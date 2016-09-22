#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "fila.h"

Fila hue;

/*
//Exemplo de uso de Fila circular:
int main() {

	unsigned int x;
	int *valores;
	srand(time(0));
	iniciar(8, &hue);
	for (int i = 0; i < 8; i++) {
		push(rand(), &hue);
	}

	valores = listar(hue,&x);

	for (unsigned int i = 0; i < x;i++) {
		printf("%d\n",valores[i]);
	}

	pop(&hue);
	pop(&hue);

	push(rand(), &hue);

	valores = listar(hue, &x);
	
	for (unsigned int i = 0; i < x; i++) {
		printf("%d\n", valores[i]);
	}

	return 0;
}
*/

bool iniciar(unsigned int tamanho, Fila * qual)
{
	qual->tamanho = tamanho;
	qual->elementos = (int*)malloc(sizeof(int)*tamanho);
	qual->fim = qual->inicio = 0;
	return qual->elementos != 0;

}

bool push(int info, Fila * qual)
{
	if (qual->fim == qual->tamanho)
		qual->fim = 0;

	if (cheia(*qual))
		return false;

	qual->elementos[qual->fim] = info;
	qual->fim++;

	
	return true;
}

bool pop(Fila * qual)
{
	if (vazia(*qual)) return false;
	if (qual->inicio == qual->tamanho - 1) qual->inicio = 0;
	else qual->inicio++;
	return true;
}

int * listar(Fila qual, unsigned int * qtde)
{
	//dar free depois de usar a função
	int * retorno;
	*qtde = (qual.fim >= qual.inicio) ? qual.fim - qual.inicio : qual.tamanho - (qual.inicio - qual.fim);
	retorno = (int*)malloc(sizeof(int)*(*qtde));
	for (unsigned int i = 0, j = qual.inicio; i < *qtde; i++, j++) {
		if (j == qual.tamanho) j = 0;
		retorno[i] = qual.elementos[j];
	}
	return retorno;
}

bool cheia(Fila qual) {
	if ((qual.fim == qual.tamanho && qual.inicio < 2) || (qual.fim == qual.inicio - 1))
		return true;
	return false;
}

bool vazia(Fila qual) {
	if (qual.inicio == qual.fim)
		return true;
	return false;
}
