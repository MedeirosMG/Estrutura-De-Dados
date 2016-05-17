#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int *vetor;
	int max;
	int quantidade;
}heap;

void inicializaHeap(heap *h, int n)
{
	h->vetor = malloc(sizeof(int)* n );
	h->max = n;
	h->quantidade = 0;

	if(!h->vetor)
		puts("Problema na alocacao");
}

int filhoEsquerdo(heap *h, int ind)
{
	return 2 * ind + 1;
}

int filhoDireito(heap *h, int ind)
{
	return 2 * ind + 2;
}

int ultimoPai(heap *h)
{
	return (h->quantidade/2) - 1;
}

int pai(heap *h, int ind)
{
	return (ind - 1) / 2;
}

void troca(heap *h, int filho, int pai)
{
	int aux = h->vetor[pai];

	h->vetor[pai] = h->vetor[filho];
	h->vetor[filho] = aux;
}

void sift(heap *h, int pai)
{
	int fe = filhoEsquerdo(h, pai);
	int fd = filhoDireito(h, pai);
	int maior = pai;

	if(fe < h->quantidade && h->vetor[fe] > h->vetor[maior] )
		maior = fe;

	if(fd < h->quantidade && h->vetor[fd] > h->vetor[maior] )
		maior = fd;

	if(maior != pai)
	{
		troca(h, maior, pai);
		sift(h, maior);
	}
}

void construirHeap(heap *h)
{
	int i;
	for(i = ultimoPai(h) ; i >= 0 ; i-- )
		sift(h, i);
}

void insereMaxHeap(heap* h, int x)
{
	if(h->quantidade == h->max)
		return;
	else
	{
		h->vetor[h->quantidade] = x;
		h->quantidade++;
		construirHeap(h);	
	}
	
}

int removerMaxHeap(heap* h)
{
	int aux = h->vetor[0];

	h->vetor[0] = h->vetor[ h->quantidade -1 ];
	h->quantidade--;
	construirHeap(h);
	return aux;
}

int main(int argc, char *argv[]) 
{

    heap h;
    inicializaHeap(&h, 20);

    insereMaxHeap(&h, 5);
    insereMaxHeap(&h, 6);
    insereMaxHeap(&h, 2);
    insereMaxHeap(&h, 3);
    insereMaxHeap(&h, 1);

    puts("ok");
    printf("%d\n", removerMaxHeap(&h));
    printf("%d\n", removerMaxHeap(&h));
    printf("%d\n", removerMaxHeap(&h));
    printf("%d\n", removerMaxHeap(&h));
    printf("%d\n", removerMaxHeap(&h));

   // system("pause");
    return 0;
}