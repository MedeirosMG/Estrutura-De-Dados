#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct _no no;

struct _no
{
	char letra;
	no *prox;
};

typedef struct
{
	int quantidade;
	no* topo;
}pilha;

void empilha(pilha *palavra, char x)
{
	no* aux = malloc(sizeof(no));
	aux->letra = x;
	aux->prox = palavra->topo;
	palavra->topo = aux;
	palavra->quantidade++;
}

char desempilha(pilha *palavra)
{
	no* aux = palavra->topo;
	
	if(aux != NULL)
	{
		char letra = palavra->topo->letra;
		palavra->topo = palavra->topo->prox;
		palavra->quantidade--;
		free(aux);
		return letra;
	}
		return '0';
}

void inicializa(pilha *aux)
{
	aux->quantidade = 0;
	aux->topo = NULL;
}

char strrts(char palavra[])
{
	pilha estrutura;
	inicializa(&estrutura);
	int i,meio,meioAux,status;
	
	int tamanho = strlen(palavra);
	meio = tamanho/2;
	
	
	if(tamanho%2 != 0)
		meioAux = meio+1;
	else
		meioAux = meio;
	
	i = 0;
	
	while(palavra[i] != '\0' && i<meio)
	{
		empilha(&estrutura, palavra[i]);
		i++;
	}
	
	for(i=0;i<meio;i++)
	{
		if(desempilha(&estrutura) == palavra[meioAux] )
		{
			status = 1;
			meioAux++;
		}
		else
		{
			status = 0;
			break;
		}
	}
	
	if(status)
	{
		if(tamanho%2 == 0)
			return 32;
		else
			return palavra[meio];
	}
	else
		return '0';
}

int main(int argc, char *argv[])
{
	char aux1[MAX];
	
	puts("Digite a palavra: ");
	scanf("%s", &aux1);
	
	printf("saida: '%c'", strrts(aux1) );
	puts("");
	
	system("pause");
	return 0;
}


