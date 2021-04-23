#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho *(int*)(pBuffer)
#define i *(int*)(pBuffer + sizeof(int))
#define selLer (int*)(pBuffer + sizeof(int) * 2)
#define sel *(int*)(pBuffer + sizeof(int) * 2) 
#define flag *(int *)(pBuffer + sizeof(int) * 3)
#define tamanhoFila *(int *)(pBuffer + sizeof(int) * 4)
#define j *(int *)(pBuffer + sizeof(int) * 5)
#define nomeAux (char*)(pBuffer + sizeof(int) * 6)

typedef struct Contato{
    char nome[10];
    int idade, telefone;
    struct Contato *proximo;
    struct Contato *anterior;
}Contato;

typedef struct Lista{
    Contato *inicio;
    Contato *fim;
}Lista;

void *criarLista(Lista *lista);
void menu(Lista *lista, void *pBuffer);
void inserir(Lista *lista, void *pBuffer);
void imprimir(Lista *lista, void *pBuffer);
void buscar(Lista *lista, void *pBuffer);
void apagar(Lista *lista, void*pBuffer);
void menuOrdenar(Lista *lista, void *pBuffer);
void *intCrescente(Lista *filaP, Contato *atual, void *pBuffer);
void *intDecrescente(Lista *filaP, Contato *atual, void *pBuffer);
void *stringCrescente(Lista *filaP, Contato *atual, void *pBuffer);
void *stringDecrescente(Lista *filaP, Contato *atual, void *pBuffer);
void pop(Lista *filaP);
void idadeCrescente(Lista *lista, void *pBuffer);
void idadeDecrescente(Lista *lista, void *pBuffer);
void nomeCrescente(Lista *lista, void *pBuffer);
void nomeDecrescente(Lista *lista, void *pBuffer);
void imprimirOrdenado(Lista *filaP, void *pBuffer);
void clear(Lista *lista, void *pBuffer);

int main(){
    Lista *lista = NULL;
    lista = criarLista(lista);
    void *pBuffer = NULL;
    pBuffer = malloc(sizeof(int) * 6 + sizeof(char) * 10);
    // posição 0: tamanhoLista
    // posição 1: i
    // posição 2: sel (switch)
    // posição 3: flag
    // posicao 4: tamanho filaP
    // posição 5: j
    // posição 6: 10 char de nomeAux 
    tamanho = 0;
    menu(lista, pBuffer);
}

void *criarLista(Lista *lista){
    lista = (Lista *)malloc(sizeof(Lista));
    if(!lista){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

void menu(Lista *lista, void *pBuffer){
    do{
        printf("1)Inserir\n");
        printf("2)Imprimir\n");
        printf("3)Buscar\n");
        printf("4)Apagar\n");
        printf("5)Menu de Ordenar\n");
        printf("6)Sair\n");
        scanf("%d", selLer);
        getchar();

        switch(sel){
            case 1:
            inserir(lista, pBuffer);
            break;

            case 2:
            imprimir(lista, pBuffer);
            break;

            case 3:
            buscar(lista, pBuffer);
            break;

            case 4:
            apagar(lista, pBuffer);
            break;

            case 5:
            menuOrdenar(lista, pBuffer);
            break;

            case 6:
            clear(lista, pBuffer);
            exit(1);
            break;

            default:
            printf("Opcao invalida.\n");
        }
    }while(sel != 6);
}

void menuOrdenar(Lista *lista, void *pBuffer){
    do{
        printf("1)Ordenar por ordem crescente nome\n");
        printf("2)Ordenar por ordem decrescente nome\n");
        printf("3)Ordenar por ordem crescente idade\n");
        printf("4)Ordenar por ordem decrescente idade\n");
        printf("5)Retornar ao menu anterior\n");
        scanf("%d", selLer);
        getchar();

        switch(sel){
            case 1:
            nomeCrescente(lista, pBuffer);
            break;
            
            case 2:
            nomeDecrescente(lista, pBuffer);
            break;

            case 3:
            idadeCrescente(lista, pBuffer);
            break;

            case 4:
            idadeDecrescente(lista, pBuffer);
            break;

            case 5:
            menu(lista, pBuffer);
            break;

            default:
            printf("Opcao invalida.\n");
        }
    }while(sel != 5);
}

void inserir(Lista *lista, void *pBuffer){
    Contato *novo;
    novo = (Contato *)malloc(sizeof(Contato));
    novo->proximo = NULL;
    novo->anterior = NULL;

    printf("Nome: ");
    scanf("%s", novo->nome);
    getchar();
    printf("Idade: ");
    scanf("%d", &novo->idade);
    getchar();
    printf("Telefone: ");
    scanf("%d", &novo->telefone);
    getchar();

    if(lista->inicio == NULL){
        lista->inicio = novo;
        lista->fim = novo;
    }
    else{
        lista->fim->proximo = novo; //seta o ->proximo do nodo que é apontado pelo fim da lista a apontar para o novo nodo
        novo->anterior = lista->fim; //o anterior do novo nodo aponta pro nodo que a lista->fim aponta
        lista->fim = novo; //e o final da lista passa apontar para o novo nodo
    }
    tamanho += 1;
}

void imprimir(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Contato *auxiliar = lista->inicio;
        i=0;
        while(auxiliar!=NULL){
            printf("Contato: %d; Nome: %s; Idade: %d; Telefone: %d\n", i + 1, auxiliar->nome, auxiliar->idade, auxiliar->telefone);
            i += 1;
            auxiliar = auxiliar->proximo;
        }
    }
}

void buscar(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        flag = 0;
        i = 0;
        Contato *auxiliar = lista->inicio;
        printf("Qual nome deseja buscar? ");
        scanf("%s", nomeAux);
        getchar();
        while(auxiliar != NULL){
            i += 1;
            if(strcmp(auxiliar->nome, nomeAux) == 0){
                printf("Contato: %d; Nome: %s; Idade: %d; Telefone: %d\n", i, auxiliar->nome, auxiliar->idade, auxiliar->telefone);
                flag += 1;
            }
            auxiliar = auxiliar->proximo;
        }

        if(flag == 0){
            printf("Nome nao encontrado.\n");
        }
    }
}

void apagar(Lista *lista, void*pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Contato *auxiliar = lista->inicio;
        flag = 0;
        printf("Qual contato deseja remover? ");
        scanf("%s", nomeAux);

        while(auxiliar!=NULL){
            if(strcmp(auxiliar->nome, nomeAux)==0){//se encontrou

                if(auxiliar->anterior == NULL){ //testa se é o primeiro elemento da lista
                    if(auxiliar->proximo == NULL){ //testa se é o ÚNICO da lista
                        lista->inicio = NULL; //seta tudo pra nulo novamente
                        lista->fim = NULL;
                        free(auxiliar);
                        tamanho -= 1;
                        flag += 1;
                        return;
                    }
                    else{//caso seja o primeiro mas tem mais itens lá
                        auxiliar->proximo->anterior = NULL; //o anterior do próximo nodo vai apontar pra nulo
                        lista->inicio = auxiliar->proximo; //o inicio da lista agora passa a apontar para o nodo que vem depois do nodo a ser removido
                        free(auxiliar);
                        tamanho -= 1;
                        flag += 1;
                        return;
                    }
                }

                else if(auxiliar->anterior != NULL && auxiliar->proximo != NULL){//testa se tá no meio
                    auxiliar->anterior->proximo = auxiliar->proximo; //o próximo do nodo anterior aponta para o que vem depois do novo que será removido
                    auxiliar->proximo->anterior = auxiliar->anterior; //o anterior do próximo nodo aponta para o que vem antes do nodo que será removido
                    free(auxiliar);
                    tamanho -= 1;
                    flag += 1;
                    return;
                }

                else{//se não é o último elemento
                    auxiliar->anterior->proximo = NULL; //o próximo do nodo anterior fica nulo
                    lista->fim = auxiliar->anterior; //o final da lista agora aponta pro nodo anterior
                    free(auxiliar);
                    tamanho -= 1;
                    flag += 1;
                    return;
                }
            }

            auxiliar = auxiliar->proximo; 
        }
        if(flag == 0){
            printf("Dado nao encontrado.\n");
        }
    }
}

void *intCrescente(Lista *filaP, Contato *atual, void *pBuffer){
    Contato *novo, *contatoAux;
    novo = (Contato *)malloc(sizeof(Contato));
    novo->proximo = NULL;
    novo->anterior = NULL;
    
    strcpy(novo->nome, atual->nome);
    novo->idade = atual->idade;
    novo->telefone = atual->telefone;

    if(tamanhoFila == 0){
        filaP->inicio = novo;
        filaP->fim = novo;
    }
    else if(tamanhoFila == 1){ //se só tiver um item lá dentro até então
        if(novo->idade >= filaP->inicio->idade){ //se a nova idade inserida for maior do que a que está lá, então insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{ //se for menor, insere no início
            filaP->inicio->anterior = novo; 
            novo->proximo = filaP->inicio;
            filaP->inicio = novo;
        }
    }
    else{ //se tiver mais do que dois itens, vai ter de percorrer a lista do fim pra frente
        contatoAux = filaP->fim;
        if(novo->idade >= contatoAux->idade){ //se o que for pra inserir for maior do que o que tá lá no fim, só insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{
            j = tamanhoFila;
            while((j>0) && (contatoAux->idade > novo->idade)){
                if(j==1){ //entra aqui caso tenha de comparar com o primeiro da fila
                    contatoAux->proximo = novo->proximo;
                    contatoAux->anterior = novo;
                    novo->proximo->anterior = contatoAux;
                    novo->proximo = contatoAux;
                    novo->anterior = NULL;
                    filaP->inicio = novo;
                }
                else if(j == tamanhoFila){ //entra aqui caso tenha que comparar com o ultimo da fila
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                else{ //testa se o está comparando com qqr outro elemento que não seja o primeiro ou o último
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->proximo = novo->proximo;
                    novo->proximo->anterior = contatoAux;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                j = j - 1;
                contatoAux = novo->anterior;
            }
        }
    }
    return filaP;
}

void *intDecrescente(Lista *filaP, Contato *atual, void *pBuffer){
    Contato *novo, *contatoAux;
    novo = (Contato *)malloc(sizeof(Contato));
    novo->proximo = NULL;
    novo->anterior = NULL;
    
    strcpy(novo->nome, atual->nome);
    novo->idade = atual->idade;
    novo->telefone = atual->telefone;

    if(tamanhoFila == 0){
        filaP->inicio = novo;
        filaP->fim = novo;
    }
    else if(tamanhoFila == 1){ //se só tiver um item lá dentro até então
        if(novo->idade <= filaP->inicio->idade){ 
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{ //se for menor, insere no início
            filaP->inicio->anterior = novo; 
            novo->proximo = filaP->inicio;
            filaP->inicio = novo;
        }
    }
    else{ //se tiver mais do que dois itens, vai ter de percorrer a lista do fim pra frente
        contatoAux = filaP->fim;
        if(novo->idade <= contatoAux->idade){ //se o que for pra inserir for maior do que o que tá lá no fim, só insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{
            j = tamanhoFila;
            while((j>0) && (contatoAux->idade < novo->idade)){
                if(j==1){ //entra aqui caso tenha de comparar com o primeiro da fila
                    contatoAux->proximo = novo->proximo;
                    contatoAux->anterior = novo;
                    novo->proximo->anterior = contatoAux;
                    novo->proximo = contatoAux;
                    novo->anterior = NULL;
                    filaP->inicio = novo;
                }
                else if(j == tamanhoFila){ //entra aqui caso tenha que comparar com o ultimo da fila
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                else{ //testa se o está comparando com qqr outro elemento que não seja o primeiro ou o último
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->proximo = novo->proximo;
                    novo->proximo->anterior = contatoAux;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                j = j - 1;
                contatoAux = novo->anterior;
            }
        }
    }
    return filaP;
}

void *stringCrescente(Lista *filaP, Contato *atual, void *pBuffer){
    Contato *novo, *contatoAux;
    novo = (Contato *)malloc(sizeof(Contato));
    novo->proximo = NULL;
    novo->anterior = NULL;
    
    strcpy(novo->nome, atual->nome);
    novo->idade = atual->idade;
    novo->telefone = atual->telefone;

    if(tamanhoFila == 0){
        filaP->inicio = novo;
        filaP->fim = novo;
    }
    else if(tamanhoFila == 1){ //se só tiver um item lá dentro até então
        if(strcmp(novo->nome, filaP->inicio->nome) >= 0){ //se a nova idade inserida for maior do que a que está lá, então insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{ //se for menor, insere no início
            filaP->inicio->anterior = novo; 
            novo->proximo = filaP->inicio;
            filaP->inicio = novo;
        }
    }
    else{ //se tiver mais do que dois itens, vai ter de percorrer a lista do fim pra frente
        contatoAux = filaP->fim;
        if(strcmp(novo->nome, contatoAux->nome) >= 0){ //se o que for pra inserir for maior do que o que tá lá no fim, só insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{
            j = tamanhoFila;
            while((j>0) && (strcmp(novo->nome, contatoAux->nome) < 0)){
                if(j==1){ //entra aqui caso tenha de comparar com o primeiro da fila
                    contatoAux->proximo = novo->proximo;
                    contatoAux->anterior = novo;
                    novo->proximo->anterior = contatoAux;
                    novo->proximo = contatoAux;
                    novo->anterior = NULL;
                    filaP->inicio = novo;
                }
                else if(j == tamanhoFila){ //entra aqui caso tenha que comparar com o ultimo da fila
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                else{ //testa se o está comparando com qqr outro elemento que não seja o primeiro ou o último
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->proximo = novo->proximo;
                    novo->proximo->anterior = contatoAux;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                j = j - 1;
                contatoAux = novo->anterior;
            }
        }
    }
    return filaP;
}

void *stringDecrescente(Lista *filaP, Contato *atual, void *pBuffer){
    Contato *novo, *contatoAux;
    novo = (Contato *)malloc(sizeof(Contato));
    novo->proximo = NULL;
    novo->anterior = NULL;
    
    strcpy(novo->nome, atual->nome);
    novo->idade = atual->idade;
    novo->telefone = atual->telefone;

    if(tamanhoFila == 0){
        filaP->inicio = novo;
        filaP->fim = novo;
    }
    else if(tamanhoFila == 1){ //se só tiver um item lá dentro até então
        if(strcmp(novo->nome, filaP->inicio->nome) <= 0){ //se a nova idade inserida for maior do que a que está lá, então insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{ //se for menor, insere no início
            filaP->inicio->anterior = novo; 
            novo->proximo = filaP->inicio;
            filaP->inicio = novo;
        }
    }
    else{ //se tiver mais do que dois itens, vai ter de percorrer a lista do fim pra frente
        contatoAux = filaP->fim;
        if(strcmp(novo->nome, contatoAux->nome) <= 0){ //se o que for pra inserir for maior do que o que tá lá no fim, só insere no fim
            novo->anterior = filaP->fim;
            filaP->fim->proximo = novo;
            filaP->fim = novo;
        }
        else{
            j = tamanhoFila;
            while((j>0) && (strcmp(novo->nome, contatoAux->nome) > 0)){
                if(j==1){ //entra aqui caso tenha de comparar com o primeiro da fila
                    contatoAux->proximo = novo->proximo;
                    contatoAux->anterior = novo;
                    novo->proximo->anterior = contatoAux;
                    novo->proximo = contatoAux;
                    novo->anterior = NULL;
                    filaP->inicio = novo;
                }
                else if(j == tamanhoFila){ //entra aqui caso tenha que comparar com o ultimo da fila
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                else{ //testa se o está comparando com qqr outro elemento que não seja o primeiro ou o último
                    contatoAux->anterior->proximo = novo;
                    novo->anterior = contatoAux->anterior;
                    contatoAux->proximo = novo->proximo;
                    novo->proximo->anterior = contatoAux;
                    contatoAux->anterior = novo;
                    novo->proximo = contatoAux;
                }
                j = j - 1;
                contatoAux = novo->anterior;
            }
        }
    }
    return filaP;
}

void pop(Lista *filaP){
    Contato *auxiliar, *contAux;
    contAux = filaP->inicio;

    while(contAux!=NULL){
        auxiliar = contAux;
        contAux = contAux->proximo;
        free(auxiliar);
    }
    free(filaP);
}

void idadeCrescente(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Lista *filaP = NULL;
        filaP = criarLista(filaP);
        Contato *contato;
        contato = lista->inicio;
        tamanhoFila = 0;
        if(tamanho == 1){
            filaP = intCrescente(filaP, contato, pBuffer);
        }
        else{
            for(; contato!=NULL; contato = contato->proximo){
                filaP = intCrescente(filaP, contato, pBuffer);
                tamanhoFila += 1;
            }
        }
        imprimirOrdenado(filaP, pBuffer);
    }
    
}

void idadeDecrescente(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Lista *filaP = NULL;
        filaP = criarLista(filaP);
        Contato *contato;
        contato = lista->inicio;
        tamanhoFila = 0;
        if(tamanho == 1){
            filaP = intDecrescente(filaP, contato, pBuffer);
        }
        else{
            for(; contato!=NULL; contato = contato->proximo){
                filaP = intDecrescente(filaP, contato, pBuffer);
                tamanhoFila += 1;
            }
        }
        imprimirOrdenado(filaP, pBuffer);
    }
    
}

void nomeCrescente(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Lista *filaP = NULL;
        filaP = criarLista(filaP);
        Contato *contato;
        contato = lista->inicio;
        tamanhoFila = 0;
        if(tamanho == 1){
            filaP = stringCrescente(filaP, contato, pBuffer);
        }
        else{
            for(; contato!=NULL; contato = contato->proximo){
                filaP = stringCrescente(filaP, contato, pBuffer);
                tamanhoFila += 1;
            }
        }
        imprimirOrdenado(filaP, pBuffer);
    }
    
}

void nomeDecrescente(Lista *lista, void *pBuffer){
    if(tamanho == 0){
        printf("lista vazia.\n");
    }
    else{
        Lista *filaP = NULL;
        filaP = criarLista(filaP);
        Contato *contato;
        contato = lista->inicio;
        tamanhoFila = 0;
        if(tamanho == 1){
            filaP = stringDecrescente(filaP, contato, pBuffer);
        }
        else{
            for(; contato!=NULL; contato = contato->proximo){
                filaP = stringDecrescente(filaP, contato, pBuffer);
                tamanhoFila += 1;
            }
        }
        imprimirOrdenado(filaP, pBuffer);
    }
    
}

void imprimirOrdenado(Lista *filaP, void *pBuffer){
    Contato *aux = filaP->inicio;
    i=0;
    while(aux!=NULL){
        i += 1;
        printf("Contato: %d; Nome: %s; Idade: %d; Telefone: %d\n", i, aux->nome, aux->idade, aux->telefone);
        aux = aux->proximo;
    }
    pop(filaP);
}

void clear(Lista *lista, void *pBuffer){
    Contato *auxiliar, *contAux;
    contAux = lista->inicio;

    while(contAux!=NULL){
        auxiliar = contAux;
        contAux = contAux->proximo;
        free(auxiliar);
        tamanho -= 1;
    }
    free(lista);
    free(pBuffer);
}