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

int isAnagram(char primeira[], char segunda[])
{
	pilha estrutura;
	inicializa(&estrutura);
	int i,flag;
	
	i = 0;
	
	while(primeira[i] != '\0')
	{
		empilha(&estrutura, primeira[i]);
		i++;
	}
	
	i = 0;
	
	if(estrutura.quantidade == strlen(segunda) )
	{
		while(estrutura.topo != NULL && segunda[i] != '\0')
		{
			if(desempilha(&estrutura) == segunda[i]  )
			{
				i++;
			}
			else 
			{
				return 0;
				break;
			}
			
		}
	}
	else
		return 0;	
		
	return 1;
}

int main(int argc, char *argv[])
{
	char aux1[MAX],aux2[MAX];
	
	puts("Digite a primeira palavra: ");
	scanf("%s", &aux1);
	
	puts("Digite a segunda palavra: ");
	scanf("%s", &aux2);
	
	if( isAnagram(aux1,aux2) )
		puts("E anagrama");
	else
		puts("Nao e anagrama");
	
	system("pause");
	return 0;
}


