#include <stdio.h>
#include <stdlib.h>
//Crie uma estrutura de nó que guarde um número inteiro
typedef struct _no no;
struct _no {
    int valor;
    no* proximo;
};
//Lista
typedef struct {
    int total;
    no* primeiro;
} lista;
void imprimeLista(lista* l) {
    no* ptrAtual = l->primeiro;
    printf("l = {");
    while (ptrAtual != NULL) {
        printf("%-3d%s", ptrAtual->valor, ptrAtual->proximo!=NULL ? ", " : "}\n" );
        ptrAtual = ptrAtual->proximo;
    }
}
no* buscaLinear(lista* l, int chave) {
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->valor != chave)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
	}
	return ptrAtual;
}
void inicializa(lista* l) {
   l->total = 0;
   l->primeiro = NULL;
}
int insereLde(lista* l, int valor) {
	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	no* novo = malloc(sizeof(no));
	novo->valor = valor;
	   
   if(l->primeiro == NULL)
   {
   		l->primeiro = novo;
   		novo->proximo = NULL;
   		l->total++;
   }
   else
   {
		while(ptrAtual != NULL && novo->valor > ptrAtual->valor )
		{
			ptrAnt = ptrAtual;
			ptrAtual = ptrAtual->proximo;
		}
		if(ptrAnt == NULL)
		{
			novo->proximo = l->primeiro;
			l->primeiro = novo;
			l->total++;
		}
		else
		{
			novo->proximo = ptrAtual;
			ptrAnt->proximo = novo;
			l->total++;
		}   
	}
	return;
}

int remover(lista* l, int chave) {
	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->valor != chave)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
	}
	if(ptrAnt == NULL && ptrAtual->valor == chave)
	{
		l->primeiro = ptrAtual->proximo;
		free(ptrAtual);
		l->total--;
	}
	else if(ptrAtual != NULL && ptrAtual->valor == chave)
	{
		ptrAnt->proximo = ptrAtual->proximo;
		free(ptrAtual);
		l->total--;
	}
	return;
	
}

lista split(lista* l, int n) {
	int i;
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	lista r;
	
	for(i=0;i<n-1;i++)
	{
		if(ptrAtual != NULL)
		{
			ptrAnt = ptrAtual;
			ptrAtual = ptrAtual->proximo;
		}
		else
		{
			break;
		}
	}
	
	if(ptrAtual != NULL && n != 1)
	{
		inicializa(&r);
		r.primeiro = ptrAtual;
		ptrAnt->proximo = NULL;
		r.total = l->total-n+1;
		l->total = n-1;
	}
	else if(ptrAtual == NULL)
	{
		inicializa(&r);
	}
	else if(n == 1)
	{
		inicializa(&r);
		r.primeiro = ptrAtual;
		l->primeiro = NULL;
		r.total = l->total;
		l->total = 0;
	}
	
		return r;
}

void removerTudo(lista* l) {
	
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
//Código de Teste
void testaLista() {
	int aux;
    lista l;
    inicializa(&l);
    printf("\n\n============ Inserindo valores na lista ============\n\n");
    insereLde(&l, 2);
    insereLde(&l, 5);
    insereLde(&l, 9);
    insereLde(&l, 12);
    insereLde(&l, 3);
    printf("Lista 1 (Quantidade de Itens: %d)\n", l.total);
    imprimeLista(&l);
    
    printf("\n\n============ Buscando valor na lista ============\n\nQue valor deseja buscar? ");
    scanf("%d",&aux);
    no* buscar = buscaLinear(&l, aux);
    if(buscar != NULL)
    	printf("\nO valor %d foi encontrado, se encontra no endereco: %d",aux,buscar);
    else
    	printf("\nO valor %d nao foi encontrado",aux);
    printf("\n\n============ Removendo alguns valores da lista ============\n\nItens removidos: 4,2,3\n\n");
    remover(&l, 4);
    remover(&l, 2);
    remover(&l, 3);
    printf("Lista 1 original (Quantidade de Itens: %d)\n", l.total);
    imprimeLista(&l);
    
    printf("\n\n============ split ============\n\nDeseja comecar em qual posicao o split? ");
    scanf("%d", &aux);
    
    printf("\n\n============ Listas apos o split ============\n\n");
    lista l2 = split(&l, aux);
    printf("Lista 1 (Quantidade de Itens: %d)\n", l.total);
    imprimeLista(&l);
    
    printf("\n\nLista 2 (Quantidade de Itens: %d)\n", l2.total);
    imprimeLista(&l2);
    
    printf("\n\n-- Removendo todos os valores das duas listas....\n");
    printf("\n\n");
    removerTudo(&l);
    removerTudo(&l2);
    
    printf("============ Listas apos a remocao ============\n\n");
    printf("Lista 1 (Quantidade de Itens: %d)\n", l.total);
    imprimeLista(&l);
    
    printf("\n\nLista 2 (Quantidade de Itens: %d)\n", l2.total);
    imprimeLista(&l2);
    
}
int main(int argc, char* argv[]) {
    testaLista();
    return 0;
}
