#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char nome[30];
    int idade;
    int altura;
    struct no *prox;
}Pessoa;

void *inserir(Pessoa *listaPessoas);
void imprimir(Pessoa *listaPessoas);
int quantPessoas = 0;

int main(){
    Pessoa *listaPessoas = NULL;
    int escolha;

    do{
        printf("<1> Insere uma pessoa\n");
        printf("<2> Para de inserir e imprime:\n");
        scanf("%d", &escolha);
        getchar();

        switch(escolha){
            case 1:
            listaPessoas = inserir(listaPessoas);
            break;

            case 2:
            imprimir(listaPessoas);
            free(listaPessoas);
            break;

            default:
            printf("Escolha inexistente.\n");
            break;
        }
    }while(escolha != 2);
}

void *inserir(Pessoa *listaPessoas){
    if(quantPessoas == 0){
        listaPessoas = (Pessoa *)malloc(sizeof(Pessoa));
    }
    else{
        listaPessoas = (Pessoa *)realloc(listaPessoas, sizeof(Pessoa) * (quantPessoas+1));
    }

    printf("Digite o nome: ");
    scanf("%s", listaPessoas[quantPessoas].nome);
    getchar();
    printf("Digite a idade: ");
    scanf("%d", &listaPessoas[quantPessoas].idade);
    getchar();
    printf("Digite a altura: ");
    scanf("%d", &listaPessoas[quantPessoas].altura);
    getchar();

    quantPessoas++;
    return listaPessoas;
}

void imprimir(Pessoa *listaPessoas){
    if(quantPessoas > 0){
        for(int i=0; i<quantPessoas; i++){
            printf("Nome: %s; ", listaPessoas[i].nome);
            printf("Idade: %d; ", listaPessoas[i].idade);
            printf("Altura: %d.\n", listaPessoas[i].altura);
        }
    }
    else{
        printf("A lista está vazia.\n");
    }
}