#ifndef FILA_H
#define FILA_H

typedef struct
{
	int * elementos;
	unsigned int tamanho;
	unsigned int inicio, fim;

}Fila;

bool iniciar(unsigned int tamanho, Fila * qual);
bool push(int info, Fila * qual);
bool pop(Fila * qual);
int * listar(Fila qual, unsigned int * qtde);
bool cheia(Fila qual);
bool vazia(Fila qual);

#endif // !fila