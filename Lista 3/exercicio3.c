#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Registro {
    int dado;
} Registro;

typedef struct No {
    Registro Reg;
    struct No *pEsq, *pDir;
} No;

/*BALANCEAR*/
int FB (No* pRaiz);
int Altura(No* pRaiz);
void RSE(No** ppRaiz);
void RSD(No** ppRaiz);
int BalancaEsquerda(No** ppRaiz);
int BalancaDireita(No** ppRaiz);
int Balanceamento(No** ppRaiz);
int EhArvoreArvl(No* pRaiz);

/*DEMAIS FUNÇÕES*/
int Insere(No** ppRaiz,int x);
void listarArvore (No *pRaiz);
void clear(No *pRaiz);
void Registrar(Registro *reg);
int Remover(No** ppRaiz, int x);
No* procuraMenor (No* pAtual);
void PrimeiroCenario(No *pRaiz);
void SegundoCenario();

int main(){
    No *pRaiz = NULL;

    int op;

    do{
        printf("<1> Primeiro cenario\n");
        printf("<2>Segundo cenario\n");
        printf("<3>Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                PrimeiroCenario(pRaiz);
                break;
            case 2:
                SegundoCenario();
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }while(op!=3);

}

void SegundoCenario(){
    No *pRaiz = NULL;
    /*INSERÇÃO*/
    printf("Case 1a: Insert 15\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    printf("--ARVORE ANTES DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n");
    Insere(&pRaiz, 15);
    printf("--ARVORE DEPOIS DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 2a: Insert 15\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 3);
    printf("--ARVORE ANTES DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n");
    /*Inserindo o 15*/
    Insere(&pRaiz, 15);
    printf("--ARVORE DEPOIS DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 3a: Insert 15\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 21);
    Insere(&pRaiz, 30);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 11);
    printf("--ARVORE ANTES DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n");
    /*Inserindo o 15*/
    Insere(&pRaiz, 15);
    printf("--ARVORE DEPOIS DE INSERIR O 15--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 1b: Insert 8\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    printf("--ARVORE ANTES DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n");
    Insere(&pRaiz, 8);
    printf("--ARVORE DEPOIS DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 2b: Insert 8\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 3);
    printf("--ARVORE ANTES DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n");
    /*Inserindo o 8*/
    Insere(&pRaiz, 8);
    printf("--ARVORE DEPOIS DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 3b: Insert 8\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 21);
    Insere(&pRaiz, 30);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 11);
    printf("--ARVORE ANTES DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n");
    /*Inserindo o 8*/
    Insere(&pRaiz, 8);
    printf("--ARVORE DEPOIS DE INSERIR O 8--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 1: Delete - Double Rebalancing\n");
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 5);
    printf("--ARVORE ANTES DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n");
    //Removendo o 1
    Remover(&pRaiz, 1);
    printf("--ARVORE DEPOIS DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("Case 2: Delete - Double Rebalancing\n");
    Insere(&pRaiz, 6);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 8);
    Insere(&pRaiz, 66);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 5);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 65);
    Insere(&pRaiz, 67);
    Insere(&pRaiz, 68);
    printf("--ARVORE ANTES DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n");
    //Removendo o 1
    Remover(&pRaiz, 1);
    printf("--ARVORE DEPOIS DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    
    printf("Case 3: Delete - Double Rebalancing\n");
    Insere(&pRaiz, 5);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 8);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 65); //A
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 6);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 66);//B
    Insere(&pRaiz, 67);//C
    printf("--ARVORE ANTES DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n");
    //Removendo o 1
    Remover(&pRaiz, 1);
    printf("--ARVORE DEPOIS DE REMOVER O 1--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;

    printf("TESTE\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 10);
    Insere(&pRaiz, 25);
    Insere(&pRaiz, 5);
    Insere(&pRaiz, 15);
    Insere(&pRaiz, 23);
    Insere(&pRaiz, 13);
    //Insere(&pRaiz, 3);
    printf("--ARVORE ANTES DE REMOVER O 10--\n");
    listarArvore(pRaiz);
    printf("\n");
    //Removendo o 1
    Remover(&pRaiz, 10);
    printf("--ARVORE DEPOIS DE REMOVER O 10--\n");
    listarArvore(pRaiz);
    printf("\n\n");
    clear(pRaiz);
    pRaiz = NULL;
}

void PrimeiroCenario(No *pRaiz){
    int numeroNodos, random, i;
    srand(time(0));

    printf("Numero de nodos que deseja ter na árvore? ");
    scanf("%d", &numeroNodos);
    getchar();

    for(i=0;i<numeroNodos;i++){
        random = rand()%1000;
        Insere(&pRaiz, random);
    }

    listarArvore(pRaiz);
    printf("\n");

    if(EhArvoreArvl(pRaiz)) {
        printf("\nA arvore eh AVL\n");
    }
    else {
        printf("\nNao eh AVL\n");
    }

    clear(pRaiz);
}

No* procuraMenor (No* pAtual) { //procura pelo nó mais a esquerda
    No *no1 = pAtual;
    No *no2 = pAtual->pEsq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->pEsq;
    }
    return no1;
}

int Remover(No** ppRaiz, int x){
    if(*ppRaiz == NULL){
        printf("O valor n existe\n");
        return 0;
    }
    int res; //resposta da remoção
    if(x < (*ppRaiz)->Reg.dado){
        if((res=Remover(&(*ppRaiz)->pEsq, x)) == 1){
            Balanceamento(ppRaiz);
        }
    }

    if(x > (*ppRaiz)->Reg.dado){
        if((res=Remover(&(*ppRaiz)->pDir, x)) == 1){
            Balanceamento(ppRaiz);
        }
    }

    if((*ppRaiz)->Reg.dado == x){
        //pai pode ter 1 filho ou nenhum
        if((*ppRaiz)->pEsq == NULL || (*ppRaiz)->pDir == NULL){
            No *removido = (*ppRaiz);
            if((*ppRaiz)->pEsq != NULL){
                (*ppRaiz) = (*ppRaiz)->pEsq;
            }
            else
                (*ppRaiz) = (*ppRaiz)->pDir;
            free(removido);
        }
        //tem dois filhos
        else{
            No *temporario = procuraMenor((*ppRaiz)->pDir);
            (*ppRaiz)->Reg.dado = temporario->Reg.dado;
            Remover(&(*ppRaiz)->pDir, (*ppRaiz)->Reg.dado);
            Balanceamento(ppRaiz);
        }
        return 1;
    }
    return res;
}

void clear(No *pRaiz){
    if (pRaiz == NULL) {
        return;
    }

    clear(pRaiz->pEsq);
    clear(pRaiz->pDir);

    free(pRaiz);
}


int Altura(No* pRaiz){
    int iEsq,iDir;
    if (pRaiz == NULL)
        return 0;

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if( iEsq > iDir )
        return iEsq + 1;

    else
        return iDir + 1;
}

int FB (No* pRaiz){
    if (pRaiz == NULL){
        return 0;
    }

    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

void RSE(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsquerda(No** ppRaiz){
    int fbe = FB ( (*ppRaiz)->pEsq );

    if( fbe >= 0 ){
        RSD(ppRaiz);
        return 1;
    }

    else if (fbe < 0 )
    { /* Rotação Dupla Direita */
        RSE( &((*ppRaiz)->pEsq) );
        RSD( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }

    return 0;
}

int BalancaDireita(No** ppRaiz){
    int fbd = FB( (*ppRaiz)->pDir);

    if( fbd <= 0 ){
        RSE (ppRaiz);
        return 1;
    }

    else if (fbd > 0 ){ 
    /* Rotação Dupla Esquerda */
        RSD( &((*ppRaiz)->pDir) );
        RSE( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }
    return 0;
}

int Balanceamento(No** ppRaiz){
    int fb = FB(*ppRaiz);
    if( fb > 1)
        return BalancaEsquerda(ppRaiz);

    else if(fb < -1 )
        return BalancaDireita(ppRaiz);

    else
        return 0;
}

int Insere(No** ppRaiz,int x){
    if (*ppRaiz == NULL){
        *ppRaiz = (No*)malloc(sizeof(No));
        (*ppRaiz)->Reg.dado = x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }

    else if ( (*ppRaiz)->Reg.dado > x){
        if ( Insere(&(*ppRaiz)->pEsq,x) ){
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    }

    else if ( (*ppRaiz)->Reg.dado < x ){
        if ( Insere(&(*ppRaiz)->pDir,x) ){
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
        else
            return 0;
    }

    else{
        return 0; /* valor já presente */
    }
    return 0;
}

int EhArvoreArvl(No* pRaiz){
    int fb;
    if (pRaiz == NULL)
        return 1;

    if (!EhArvoreArvl(pRaiz->pEsq))
        return 0;

    if (!EhArvoreArvl(pRaiz->pDir))
        return 0;

    fb = FB (pRaiz);
    if ( ( fb > 1 ) || ( fb < -1) )
        return 0;

    else
        return 1;
}

void listarArvore (No *pRaiz){

    if (pRaiz != NULL) {
        printf("%d(", pRaiz->Reg.dado);
        listarArvore(pRaiz->pEsq);
        listarArvore(pRaiz->pDir);
        printf(")");
    }

}