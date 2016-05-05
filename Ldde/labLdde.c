#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
//fodace
	typedef struct
	{
	   int codBarras;
	   char nomeProduto[50];
	   float valor;
	} registro;
	typedef struct s_no no;
	struct s_no 
	{
	   registro conteudo;
	   no* proximo;
	   no* anterior;
	};
	typedef struct 
	{
	   no* primeiro;
	   no* ultimo;
	   int quantidade;
	} ldde;
	
	void inicializaLde(ldde* l) 
	{
	   l->primeiro = NULL;
	   l->ultimo = NULL;
	   l->quantidade = 0;
	}
	
	void limparLde(ldde* l) 
	{
		no* ptrAtual = l->primeiro;
		while (ptrAtual != NULL)
		{
	       removeLdde(l, ptrAtual->conteudo.codBarras);
	       ptrAtual = l->primeiro;
	    }
	   
		l->primeiro = NULL;
		l->quantidade = 0;
	}
	
	int insereLdde(ldde* lista, registro r) 
	{
		no* ptrAnt = NULL;
		no* ptrAtual = lista->primeiro;
		no* novo=malloc(sizeof(no));
		novo->conteudo = r;
		if(lista->quantidade == 0)
		{
		  lista->primeiro = novo;
		  lista->ultimo = novo;
		  lista->quantidade++;
		  novo->anterior = NULL;
		  novo->proximo = NULL;
		  return 0;
		}
	   while(ptrAtual != NULL && ptrAtual->conteudo.codBarras < r.codBarras )
	   {
	       ptrAnt = ptrAtual;
	       ptrAtual = ptrAtual->proximo;
	   }
	   
	   if(ptrAnt == NULL)
	   {
	       novo->proximo = ptrAtual;
	       novo->anterior = NULL;
	       lista->primeiro = novo;
	       lista->quantidade++;
	   }
	   else
	   {
	       novo->proximo = ptrAtual;
	       novo->anterior = ptrAnt;
	       ptrAnt->proximo = novo;
	       lista->quantidade++;
	   }
	   if(ptrAtual == NULL)
	   {
	       lista->ultimo = novo;
	   }
	   return 0;
	}
	
	no* buscaLdde(ldde* lista, int chave) 
	{
		no* ptrAtual = lista->primeiro;
		
		while(ptrAtual != NULL && ptrAtual->conteudo.codBarras != chave)
		{
			ptrAtual = ptrAtual->proximo;
		}
		return ptrAtual;
	}
		
	int removeLdde(ldde* lista, int chave) 
	{
		no* ptrAtual = buscaLdde(lista,chave);
		if(ptrAtual != NULL)
		{
			if(ptrAtual == lista->primeiro)
			{
				lista->primeiro = ptrAtual->proximo;
			}
			else if(ptrAtual->proximo == NULL)
			{
				lista->ultimo = ptrAtual;
			}
			else
			{
				ptrAtual->anterior->proximo = ptrAtual->proximo;
			}
			lista->quantidade--;
		}
		else
		{
			printf("\n\nCodigo de barras nao encontrado\n\n");
		}
		free(ptrAtual);
		return 1;
	}
	
	void imprimeLdde(ldde* l) 
	{
	   no* ptrAtual = l->primeiro;
		while (ptrAtual != NULL) 
		{
	       printf("Codigo: %d \n", ptrAtual->conteudo.codBarras);
	       printf("Nome:   %s \n", ptrAtual->conteudo.nomeProduto);
	       printf("Valor:  %.2f \n", ptrAtual->conteudo.valor);
	       ptrAtual = ptrAtual->proximo;
	       if (ptrAtual != NULL)
				printf("=============================================\n");
	   	}
	}
	
	void PopulaLista(ldde *l) 
	{
	   registro r;
	   r.codBarras = 1234565;
	   strcpy(r.nomeProduto, "The Legend Of Zelda");
	   r.valor = 77.80;
	   insereLdde(l, r);
	   r.codBarras = 8765434;
	   strcpy(r.nomeProduto, "The Cuckcoos Calling");
	   r.valor = 49.90;
	   insereLdde(l, r);
	   r.codBarras = 555478;
	   strcpy(r.nomeProduto, "And the Mountains Echoed");
	   r.valor = 53.90;
	   insereLdde(l, r);
	   r.codBarras = 1234567;
	   strcpy(r.nomeProduto, "Fifty Shades Trilogy");
	   r.valor = 82.80;
	   insereLdde(l, r);
	   r.codBarras = 1234569;
	   strcpy(r.nomeProduto, "Marketing Trendlines");
	   r.valor = 25.20;
	   insereLdde(l, r);
	}
	
	void GravaBinario(ldde *l)
	{
		FILE *arq = fopen("LDDE.txt","wb");
		no* ptrAtual = l->primeiro;
		fwrite( &(l->quantidade) , sizeof(int) , 1 , arq );
		while(ptrAtual != NULL)
		{
			fwrite( &(ptrAtual->conteudo) , sizeof(registro) , 1 , arq );
			ptrAtual = ptrAtual->proximo;
		}
		fclose(arq);
	}
	
	void LeBinario(ldde *l)
	{
		int total,i;
		registro aux;
		FILE *arq = fopen("LDDE.txt","rb");
		if(arq != NULL)
		{ 
			fread( &total, sizeof(int) , 1 , arq );
			for(i=0;i<total;i++)
			{
				fread(&aux , sizeof(registro) , 1 , arq);
				insereLdde(l, aux);
			}
		}
	}
	
	int main() 
	{
		int aux;
	    ldde l1;
	    inicializaLde(&l1);
	    LeBinario(&l1);
	    imprimeLdde(&l1);
		    
		printf("\nDeseja popular a lista ?\n1 - SIM\n2 - NAO\n");
		scanf("%d", &aux);
		    
		if(aux == 1)
		{
			PopulaLista(&l1);
			imprimeLdde(&l1);  
		}
		
		printf("\nDeseja apagar a lista antes de salvar no arquivo?\n1 - SIM\n2 - NAO\n");
		scanf("%d", &aux);
		
		if(aux == 1)
		{
			limparLde(&l1);
		}

		GravaBinario(&l1);
		return 0;
	}
	

