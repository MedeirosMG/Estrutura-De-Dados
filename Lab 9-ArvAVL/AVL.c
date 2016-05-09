#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

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

void Balanceie(Arvore* arv, No* folha);

int _print_t(No *tree, int is_esquerdo, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;
    int i = 0;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->chave);

    int esquerdo  = _print_t(tree->esquerdo,  1, offset,                depth + 1, s);
    int direito = _print_t(tree->direito, 0, offset + esquerdo + width, depth + 1, s);

#ifdef COMPACT
    for (i = 0; i < width; i++)
        s[depth][offset + esquerdo + i] = b[i];

    if (depth && is_esquerdo) {

        for (i = 0; i < width + direito; i++)
            s[depth - 1][offset + esquerdo + width/2 + i] = '-';

        s[depth - 1][offset + esquerdo + width/2] = '.';

    } else if (depth && !is_esquerdo) {

        for (i = 0; i < esquerdo + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + esquerdo + width/2] = '.';
    }
#else
    for (i = 0; i < width; i++)
        s[2 * depth][offset + esquerdo + i] = b[i];

    if (depth && is_esquerdo) {

        for (i = 0; i < width + direito; i++)
            s[2 * depth - 1][offset + esquerdo + width/2 + i] = '-';

        s[2 * depth - 1][offset + esquerdo + width/2] = '+';
        s[2 * depth - 1][offset + esquerdo + width + direito + width/2] = '+';

    } else if (depth && !is_esquerdo) {

        for (i = 0; i < esquerdo + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + esquerdo + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return esquerdo + width + direito;
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

int insere(Arvore* arv, int valor)
{
    
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
        Balanceie(arv, novo);
        return 1;
    }
    else
    {
        novo->pai = pai;
        pai->direito = novo;
        arv->quantidade++;
        Balanceie(arv, novo);
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
   int aux;

    if (!remover)
        return 0;

    No* rp=NULL;

    //Caso 1: remover n�o tem filhos
    if (remover->esquerdo == NULL && remover->direito == NULL) 
    {
        if(remover->pai){
            if (chave < remover->pai->chave) {
                remover->pai->esquerdo = NULL;
            } else {
                remover->pai->direito = NULL;
            }
       }
       Balanceie(arv, remover->pai);
    }//CASO 2: remover tem apenas 1 filho
    else if ((remover->esquerdo != NULL || remover->direito != NULL)
            && !(remover->esquerdo != NULL && remover->direito != NULL)) 
    {

        if (remover->esquerdo != NULL)
        {
            rp = remover->esquerdo;
            aux = 1;
        }
        else
        {
            rp = remover->direito;
            aux = 2;
        }

        if(remover->pai){
             if (chave < remover->pai->chave) {
                 remover->pai->esquerdo = rp;
             } else {
                 remover->pai->direito = rp;
             }
        }
        rp->pai = remover->pai;
        Balanceie(arv, rp);
    }//CASO 3: remover tem os dois filhos
    else 
    {
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

            if(rp->direito)
            {
                rp->direito = remover->direito;
                rp->direito->pai = rp;
            }
            
        }
        
        rp->pai = remover->pai;
        if(remover->pai){
                if (chave < remover->pai->chave)
                    remover->pai->esquerdo = rp;
                else
                    remover->pai->direito = rp;
        }
        Balanceie(arv, rp->direito);
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

// FUNCOES DO LAB 9

int Altura(No* no) 
{
    if (!no)
        return -1;
    return MAX(Altura(no->esquerdo), Altura(no->direito)) + 1;
}

int FatorBalanc(No* no)    
{
    if(!no)
        return 0;

    return Altura(no->direito) - Altura(no->esquerdo);
}

void leftRotate(Arvore* arv, No* folha)
{
    if(!folha)
        return;

    No* aux = folha->direito;

    if(aux)
    {
        if(folha->pai)
        {
            aux->pai = folha->pai;

            if(aux->chave > folha->pai->chave)
                folha->pai->direito = aux;
            else
                folha->pai->esquerdo = aux;
        }
        else
        {
            aux->pai = NULL;
            arv->raiz = folha->direito;
        }

        folha->direito = aux->esquerdo; 
        folha->pai = aux;
        aux->esquerdo = folha;
    }


}

void rightRotate(Arvore* arv, No* folha)
{
    if(!folha)
        return;

    No* aux = folha->esquerdo;

    if(aux)
    {
        if(folha->pai)
        {
            aux->pai = folha->pai;

            if(aux->chave > folha->pai->chave)
                folha->pai->direito = aux;
            else
                folha->pai->esquerdo = aux;
        }
        else
        {
            aux->pai = NULL;
            arv->raiz = folha->esquerdo;
        }

        folha->esquerdo = aux->direito;
        folha->pai = aux;
        aux->direito = folha;
    }
     
}

void Balanceie(Arvore* arv, No* folha)
{  
    No* balance = folha;
    int aux = 0;

    do
    {
        aux = FatorBalanc(balance->pai);
        balance = balance->pai;
        
    }while(aux > -2 && aux< 2 && balance->pai != NULL);

    int pai = FatorBalanc(balance);
    int filhoDir = FatorBalanc(balance->direito);
    int filhoEsq = FatorBalanc(balance->esquerdo);
    
    if(pai >= 2)
    {
        if(filhoDir == -1)
            rightRotate(arv, balance->direito);

        leftRotate(arv, balance);
    }
    else if(pai <= -2)
    {
        if(filhoEsq == 1)
            leftRotate(arv, balance->esquerdo);

        rightRotate(arv, balance);
    }

}


int main(int argc, char *argv[]) {

    Arvore a;
    int aux,numero,i,aux2;
    No* noAuxiliar;
    inicializa(&a);
    /*
    insere(&a, 5);
    insere(&a, 8);
    insere(&a, 6);
    insere(&a, 20);
    insere(&a, 19);
    insere(&a, 17);
    insere(&a, 18);
    insere(&a, 15);
    print_t(a.raiz);
    */

    puts("SEQUENCIA DE TESTES");
        insere(&a, 5);
        print_t(a.raiz);
        insere(&a, 8);
        print_t(a.raiz);
        insere(&a, 6);
        print_t(a.raiz);
        insere(&a, 20);
        print_t(a.raiz);
        insere(&a, 21);
        print_t(a.raiz);
        insere(&a, 19);
        print_t(a.raiz);
        insere(&a, 17);
        print_t(a.raiz);
        insere(&a, 18);
        print_t(a.raiz);
        insere(&a, 15);
        print_t(a.raiz);
        puts("REMOCAO");
        remover(&a, 5);
        print_t(a.raiz);
        remover(&a, 17);
        print_t(a.raiz);
        remover(&a, 15);
        print_t(a.raiz);


    puts("FIM DOS TESTES");
    /*
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
    */


 //  system("pause");
    return 0;
}