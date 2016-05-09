#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#define SISTEMA "cls"
	#define PAUSE "pause"
#else
	#define SISTEMA "clear"
	#define PAUSE "read -p \"Pressione enter para sair\" saindo"

#endif

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

typedef struct 
{ 
    int tamanho; 
    int quantidade; 
    LDE* table; 
}tHashTable; 

no* busca(LDE* l, int chave) 
{
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->conteudo.chave != chave)
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

int remover(LDE* l, int chave) 
{	
	no* ptrAnt = NULL;
	no* ptrAtual = l->primeiro;
	
	while(ptrAtual != NULL && ptrAtual->conteudo.chave != chave)
	{
		ptrAnt = ptrAtual;
		ptrAtual = ptrAtual->proximo;
	}
	if(ptrAnt == NULL && ptrAtual->conteudo.chave == chave)
	{
		l->primeiro = ptrAtual->proximo;
		free(ptrAtual);
		l->total--;
		return 1;
	}
	else if(ptrAtual != NULL && ptrAtual->conteudo.chave == chave)
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

int funcaoHash(int chave, int tamanho)
{
	return (chave % tamanho);
}

tHashTable* criaHashTable(int tamanho)
{
	int i;
	tHashTable* table = malloc(sizeof(tHashTable));
	table->table = malloc(sizeof(LDE)*tamanho);
	table->tamanho = tamanho;
	table->quantidade = 0;

	for(i = 0; i < tamanho; i++)
	{
		inicializa( &(table->table[i]) );
	}

	return table;
}

int verificaHash(tHashTable* table)
{
	int i, contador = 0;

	for(i=0; i < table->tamanho; i++ )
	{
		no* ptrAnt = NULL;
		no* ptrAtual = table->table[i].primeiro;

		while(ptrAtual != NULL)
		{
			ptrAnt = ptrAtual;
			ptrAtual = ptrAtual->proximo;
			contador++;
		}
	}

	if(contador == table->tamanho)
		return 0;
	else
		return 1;
}

int insereHash(tHashItem item, tHashTable* table)
{
	int posicao = funcaoHash(item.valor, table->tamanho);

	if( verificaHash(table) )
	{
		insereLde( &(table->table[posicao]), item);
		table->quantidade++;
		return 1;
	}
	
	return 0;

}

int removeHash(int chave, tHashTable* table)
{
	int posicao = funcaoHash(chave, table->tamanho);

	if(remover( &(table->table[posicao]), chave))
	{
		table->quantidade--;
		return 1;
	}
	else
		return 0;

}

tHashItem* buscaHash(tHashTable* table, int chave)
{
	int posicao = funcaoHash(chave, table->tamanho);

	no* aux = busca( &(table->table[posicao]), chave );

	if(aux != NULL)
		return &(aux->conteudo);
	else
		return NULL;

}

void destroyHash(tHashTable* table)
{
	int i;
	for(i = 0 ; i < table->tamanho; i++)
	{
		if(table->table[i].primeiro != NULL)
		{
			removerTudo( &(table->table[i]) );
		}
	}
	table->quantidade = 0;
	free(table->table);
	free(table);
}

int main(int argc, char* argv[]) 
{
    int x;
	int tamanho;
	int aux,i,no;
	tHashTable* hash;
	//test(hash);

	do{
		system(SISTEMA);
		printf("\n");
		printf("\n");
		printf("Programa teste: \n");
		printf("Chave utilizada igual ao numero adicionado..\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("1 - Criar hash\n");
		printf("2 - Inserir numeros\n");
		printf("3 - Remover numero\n");
		printf("4 - Verificar se numero existe\n");
		printf("6 - Destroi hash\n");
		printf("0 - Sair\n\n");

		scanf("%d", &x);

		switch(x) 
		{
			case 0:
				break;
				
			case 1:
				printf("\n");
				printf("Digite o tamanho da hash: ");
				scanf("%d", &tamanho);
				hash = criaHashTable(tamanho);
				if (hash != NULL)
					printf("Hash criada com sucesso\n\n");
				system(PAUSE);
				break;
			
			case 2:
				printf("\n");
				printf("Quantos numeros deseja adicionar? ");
				scanf("%d", &aux);

				for(i=0; i < aux; i ++) 
				{
					int number, answer;
					printf("\nnumero %d: \n", i+1);
					scanf("%d", &number);

					tHashItem num1;
					num1.valor = number;
					num1.chave = number;

					answer = insereHash(num1, hash);

					if(answer)
						printf("\nNumero adicionado com sucesso\n\n");
					else
						printf("\nHash cheia\n\n");
				}

				
				system(PAUSE);
				
				break;

			case 3:
				printf("\n");
				printf("Qual numero deseja remover? ");
				scanf("%d", &aux);
				
				int answer = removeHash(aux, hash);

				if(answer)
					printf("\nNumero removido com sucesso\n\n");
				else
					printf("\nNumero nao encontrado\n\n");

				system(PAUSE); 
				break;
			
			case 4:
				printf("\n");
				printf("Qual numero deseja verificar se existe? ");
				scanf("%d", &aux);

				tHashItem* number = buscaHash(hash, aux);

				if(number != NULL)
				{
					puts("Numero encontrado na hash: \n");
					printf("Numero: %d\nChave: %d\n\n",number->valor, number->chave);
				}
				else 
				{
					printf("\nEsse numero nao existe\n\n");
				}

				system(PAUSE); 
				break;
			
			case 6:	
				printf("Deseja excluir a hash? 1. Sim / 2. Nao\n");
				scanf("%d", &no);
				if (no == 1) 
				{
					destroyHash(hash);
				}
				
				system(PAUSE); 
				break;
			
			default:
				printf("Por favor digite uma opcao valida\n");
				system(PAUSE); 
		}


	}while(x);
	

}
