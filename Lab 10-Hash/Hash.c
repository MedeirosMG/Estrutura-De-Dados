#include <stdio.h>
#include <stdlib.h>
typedef struct _no no;

typedef struct 
{ 
    int chave; 
    int valor; 
}tHashItem;

struct _no 
{
    tHashItem conteudo;
    no* proximo;
};

typedef struct 
{
    int total;
    no* primeiro;
}LDE;

no* busca(LDE* l, tHashItem* chave) 
{
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->conteudo.chave != chave->chave)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
	}
	return ptrAtual;
}

void inicializa(LDE* l) 
{
   l->total = 0;
   l->primeiro = NULL;
}

int insereLde(LDE* l, tHashItem conteudo) 
{	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	no* novo = malloc(sizeof(no));
	novo->conteudo = conteudo;
	   
   if(l->primeiro == NULL)
   {
   		l->primeiro = novo;
   		novo->proximo = NULL;
   		l->total++;
   		return 1;
   }
   else
   {
		while(ptrAtual != NULL  )
		{
			ptrAnt = ptrAtual;
			ptrAtual = ptrAtual->proximo;
		}
		if(ptrAnt == NULL)
		{
			novo->proximo = l->primeiro;
			l->primeiro = novo;
			l->total++;
			return 1;
		}
		else
		{
			novo->proximo = ptrAtual;
			ptrAnt->proximo = novo;
			l->total++;
			return 1;
		}   
	}
	return 0;
}

int remover(LDE* l, tHashItem chave) 
{	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->conteudo != chave)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
	}
	if(ptrAnt == NULL && ptrAtual->conteudo == chave)
	{
		l->primeiro = ptrAtual->proximo;
		free(ptrAtual);
		l->total--;
		return 1;
	}
	else if(ptrAtual != NULL && ptrAtual->conteudo == chave)
	{
		ptrAnt->proximo = ptrAtual->proximo;
		free(ptrAtual);
		l->total--;
		return 1;
	}

	return 0;
	
}

void removerTudo(LDE* l) 
{	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
		free(ptrAnt);
		l->total--;
	}
	l->primeiro = ptrAtual;
	
}

int main(int argc, char* argv[]) 
{
    return 0;
}
