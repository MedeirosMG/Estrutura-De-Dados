#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tNo No;

struct tNo {
    No* pai, *direito, *esquerdo;
    int chave;
};

typedef struct {
    No* raiz;
    int quantidade;
} Arvore;

void inicializa(Arvore* a) {
    a->quantidade = 0;
    a->raiz = NULL;
}

int _print_t(No *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;
    int i = 0;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->chave);

    int left  = _print_t(tree->esquerdo,  1, offset,                depth + 1, s);
    int right = _print_t(tree->direito, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

int print_t(No *tree)
{

	int i = 0;

    char s[20][255];
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);

}

int insere(Arvore* arv, int valor) {
	
	No* novo = malloc(sizeof(No));
	No* pai = NULL;
	No* filho = arv->raiz;
	novo->direito = NULL;
	novo->esquerdo = NULL;
	novo->chave = valor;

	if(filho == NULL)
	{
		arv->raiz = novo;
		arv->quantidade++;
		novo->pai = NULL;
		return 1;
	}

	while(filho != NULL)
	{
		pai = filho;

		if(valor < filho->chave)
		{
			filho = filho->esquerdo;
		}
		else
			filho = filho->direito;
	}

	if(valor < pai->chave)
	{
		novo->pai = pai;
		pai->esquerdo = novo;
		arv->quantidade++;
		return 1;
	}
	else
	{
		novo->pai = pai;
		pai->direito = novo;
		arv->quantidade++;
		return 1;
	}

	return 0;

}

No* busca(No* folha, int chave) {  // Passar a primeira folha ao invez da arvore toda

	if(folha == NULL || folha->chave == chave)
	{
		return folha;
	}

	if(chave < folha->chave)
		busca(folha->esquerdo, chave);
	else
		busca(folha->direito, chave);
}

int remover(Arvore* arv, int chave) {

   No* remover = busca(arv->raiz, chave);

    if (!remover)
        return 0;

    No* rp=NULL;

    //Caso 1: remover n�o tem filhos
    if (remover->esquerdo == NULL && remover->direito == NULL) {
        if(remover->pai){
            if (chave < remover->pai->chave) {
                remover->pai->esquerdo = NULL;
            } else {
                remover->pai->direito = NULL;
            }
       }
    }//CASO 2: remover tem apenas 1 filho
    else if ((remover->esquerdo != NULL || remover->direito != NULL)
            && !(remover->esquerdo != NULL && remover->direito != NULL)) {

        if (remover->esquerdo != NULL)
            rp = remover->esquerdo;
        else
            rp = remover->direito;

        if(remover->pai){
             if (chave < remover->pai->chave) {
                 remover->pai->esquerdo = rp;
             } else {
                 remover->pai->direito = rp;
             }
        }
        rp->pai = remover->pai;
    }//CASO 3: remover tem os dois filhos
    else {
        rp = remover->direito;
        while (rp->esquerdo) {
            rp = rp->esquerdo;
        }

        rp->esquerdo = remover->esquerdo;
        if (rp->esquerdo)
            rp->esquerdo->pai = rp;

        if (rp->direito)
            rp->direito->pai = rp->pai;

        if (rp->pai != remover) {
           if(rp->pai)
              rp->pai->esquerdo = rp->direito;
            rp->direito = remover->direito;
            rp->direito->pai = rp;
        }
        
        rp->pai = remover->pai;
        if(remover->pai){
                if (chave < remover->pai->chave)
                    remover->pai->esquerdo = rp;
                            else
                    remover->pai->direito = rp;
        }
    }

    //No removido era a raiz
    if (!remover->pai) {
        arv->raiz = rp;
    }

    free(remover);
    return 1;

}

void preOrder(No* no) {

    printf(" %d ", no->chave);

    if (no->esquerdo)
        preOrder(no->esquerdo);

    if (no->direito)
        preOrder(no->direito);
}

void inOrder(No* no) {

    if (no->esquerdo)
        inOrder(no->esquerdo);

	printf(" %d ", no->chave);

    if (no->direito)
        inOrder(no->direito);
}


int main(int argc, char *argv[]) {

    Arvore a;
    int aux,numero,i,aux2;
    No* noAuxiliar;
    inicializa(&a);
    
    do
    {
    	puts("O que deseja fazer?\n1 - Inserir\n2 - Buscar\n3 - Remover\n4 - Imprimir preOrder\n5 - Imprimir inOrder\n6 - Desenhar arvore\n0 - Sair\n");
    	scanf("%d", &aux );
    	switch(aux)
    	{
    		case 0:
    			break;
    			
    		case 1:
    			puts("Quantos numeros deseja inserir? ");
    			scanf("%d", &aux2 );

    			for(i=0;i<aux2;i++)
    			{
	    			puts("Digite o numero que deseja inserir: \n");
	    			scanf("%d", &numero );

	    			if(insere(&a, numero) )
	    				puts("Numero inserido com sucesso\n");
	    			else
	    				puts("\nErro ao inserir\n");
	    		}

    			break;

    		case 2:
    			puts("\nDigite o numero que deseja buscar\n");
    			scanf("%d", &numero );
    			noAuxiliar =  busca(a.raiz, numero );

    			if(noAuxiliar != NULL)
    				printf("\nValor encontrado: %d\n", noAuxiliar->chave );
    			else
    				puts("\nValor nao encontrado\n");
    			
    			break;

    		case 3:
    			puts("\nDigite o numero que deseja remover\n");
    			scanf("%d", &numero );

    			if(remover(&a, numero ))
    				puts("Numero removido com sucesso");
    			else
    				puts("Numero nao encontrado");

    			break;

    		case 4:
    			preOrder(a.raiz);
    			puts("");
    			break;

    		case 5:
    			inOrder(a.raiz);
    			puts("");
    			break;

    		case 6:
    			print_t(a.raiz);
    			puts("Arvore acima ^^^^^^");
    			break;

    		default:
    			puts("\nOpcao invalida\n");
    			break;

    	}
    }while(aux != 0);

 //  system("pause");
    return 0;
}