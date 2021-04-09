#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct end{
    char nome[10];
    int idade;
    int telefone;
}pessoas[10];

void inserirContato(void *pBuffer);
void apagarContato(void *pBuffer);
void buscarContato(void *pBuffer);
void imprimirContatos(void *pBuffer);

int main(){
    void *pBuffer = NULL;
    pBuffer = malloc(sizeof(int) * 5 + sizeof(char) * 10); //quantContatos, i, j, flag, opcao, nomeRemover
    *(int *)pBuffer = 0;//quantContatos = 0;
    do{
        printf("<1> Inserir\n<2> Apagar\n<3> Buscar\n<4> Imprimir\n<5> Sair\n");
        scanf("%d", (int *)(pBuffer + sizeof(int) * 4));
        switch(*(int *)(pBuffer + sizeof(int) * 4)){
            case 1:
            inserirContato(pBuffer);
            break;

            case 2:
            apagarContato(pBuffer);
            break;

            case 3:
            buscarContato(pBuffer);
            break;

            case 4:
            imprimirContatos(pBuffer);
            break;

            case 5:
            free(pBuffer);
            exit(1);
            break;

            default:
            printf("Opcao invalida.\n");
            break;
        }
    }while(*(int *)(pBuffer + sizeof(int) * 4) != 5);
}

void inserirContato(void *pBuffer){
    if(*(int*)pBuffer != 10){
        printf("Nome: ");
        scanf("%s", pessoas[*(int *)pBuffer].nome);
        getchar();
        printf("Idade: ");
        scanf("%d", &pessoas[*(int *)pBuffer].idade);
        getchar();
        printf("Telefone: ");
        scanf("%d", &pessoas[*(int *)pBuffer].telefone);
        getchar();

        *(int *)pBuffer += 1;
    }
    else{
        printf("Agenda lotada.\n");
    }
}

void apagarContato(void *pBuffer){
    if(*(int *)pBuffer > 0){
        *(int *)(pBuffer + sizeof(int) * 3) = 0;
        printf("Qual nome deseja remover?\n");
        scanf("%s", (char *)(pBuffer + sizeof(int) * 5));

        for(*(int *)(pBuffer + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int)) < *(int *)pBuffer; *(int *)(pBuffer + sizeof(int)) += 1){
            if(strcmp((char *)(pBuffer + sizeof(int) * 5), pessoas[*(int *)(pBuffer + sizeof(int))].nome) == 0){ //nome digitado pelo usuário comparado ao nome da pessoa[i]
                for(*(int *)(pBuffer + sizeof(int) * 2) = *(int *)(pBuffer + sizeof(int)) + 1; *(int *)(pBuffer + sizeof(int) * 2) < *(int *)pBuffer; *(int *)(pBuffer + sizeof(int) * 2) += 1){ //j=i+1; j<quantPessoas;j++
                    strcpy(pessoas[*(int *)(pBuffer + sizeof(int))].nome, pessoas[*(int *)(pBuffer + sizeof(int) * 2)].nome);
                    pessoas[*(int *)(pBuffer + sizeof(int))].idade = pessoas[*(int *)(pBuffer + sizeof(int) * 2)].idade;
                    pessoas[*(int *)(pBuffer + sizeof(int))].telefone = pessoas[*(int *)(pBuffer + sizeof(int) * 2)].telefone;
                    *(int *)(pBuffer + sizeof(int)) += 1;
                }
                *(int *)(pBuffer + sizeof(int) * 3) += 1;
                *(int *)pBuffer -= 1;
            }
        }

        if(*(int *)(pBuffer + sizeof(int) * 3) == 0){
            printf("Nome não encontrado.\n");
        }
    }
    else{
        printf("Agenda vazia.\n");
    }
}

void buscarContato(void *pBuffer){
    if(*(int *)pBuffer > 0){
        *(int *)(pBuffer + sizeof(int) * 3) = 0;
        printf("Qual nome deseja buscar?\n");
        scanf("%s", (char *)(pBuffer + sizeof(int) * 5));

        for(*(int *)(pBuffer + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int)) < *(int *)pBuffer; *(int *)(pBuffer + sizeof(int)) += 1){
            if(strcmp((char *)(pBuffer + sizeof(int) * 5), pessoas[*(int *)(pBuffer + sizeof(int))].nome) == 0){ //nome digitado pelo usuário comparado ao nome da pessoa[i]
                printf("Contato: %d; ", *(int *)(pBuffer + sizeof(int)) + 1);
                printf("Nome: %s; ", pessoas[*(int *)(pBuffer + sizeof(int))].nome);
                printf("Idade: %d; ", pessoas[*(int *)(pBuffer + sizeof(int))].idade);
                printf("Telefone: %d.\n", pessoas[*(int *)(pBuffer + sizeof(int))].telefone);
                *(int *)(pBuffer + sizeof(int) * 3) += 1;
            }
        }

        if(*(int *)(pBuffer + sizeof(int) * 3) == 0){
            printf("Nome não encontrado.\n");
        }
    }
    else{
        printf("Agenda vazia.\n");
    }
}

void imprimirContatos(void *pBuffer){
    if(*(int *)pBuffer > 0){
        for(*(int *)(pBuffer + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int)) < *(int *)pBuffer; *(int *)(pBuffer + sizeof(int)) += 1){
            printf("Contato: %d; ", *(int *)(pBuffer + sizeof(int)) + 1);
            printf("Nome: %s; ", pessoas[*(int *)(pBuffer + sizeof(int))].nome);
            printf("Idade: %d; ", pessoas[*(int *)(pBuffer + sizeof(int))].idade);
            printf("Telefone: %d.\n", pessoas[*(int *)(pBuffer + sizeof(int))].telefone);
        }
    }
    else{
        printf("Agenda vazia.\n");
    }
}