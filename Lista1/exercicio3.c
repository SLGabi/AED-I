#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *incluir(void *pBuffer);
void *apagar(void *pBuffer);
void buscar(void *pBuffer);
void listar(void *pBuffer);

int main(){
    void *pBuffer = NULL;
    pBuffer = malloc(sizeof(int)); //int qtdeContatos;
    if(!pBuffer){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    *(int*)pBuffer = 0;//qtdeContatos = 0;

    int opcao;
    do{
        printf("1)Inserir na agenda\n");
        printf("2)Apagar um contato\n");
        printf("3)Buscar um contato\n");
        printf("4)Listar contatos\n");
        printf("5)Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
            pBuffer = incluir(pBuffer);
            break;

            case 2:
            pBuffer = apagar(pBuffer);
            break;

            case 3:
            buscar(pBuffer);
            break;

            case 4:
            listar(pBuffer);
            break;

            case 5:
            free(pBuffer);
            exit(1);
            break;

            default:
            printf("Opcao invalida.\n");
            break;
        }
    }while(opcao != 5);
    
    return 0;
}

void *incluir(void *pBuffer){
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * ((*(int*)(pBuffer)) + 1)); //o que já tinha antes +10 carac do nome, +2 int pro idade e telefone, e acrescenta +1 na quantContatos
    if(!pBuffer){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    printf("Nome: ");
    scanf("%s", (char *)pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * (*(int*)(pBuffer)));
    getchar();
    printf("Idade: ");
    scanf("%d", (int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * ((*(int*)(pBuffer))))); //pula +10 caracteres que é referente ao nome inserido, apontando agora pra idade
    getchar();
    printf("Telefone: ");
    scanf("%d", (int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * ((*(int*)(pBuffer))))); //pula também o 1 size de inteiro referente a idade lida, e aponta para o telefone
    getchar();

    *(int*)(pBuffer) += 1; //+1 qtdeContatos
    
    return pBuffer;
}

void *apagar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        int contador = 0;
        char nomeRemover[10];
        printf("Informe um nome: ");
        scanf("%s", nomeRemover); //pega o nome para comparar
        getchar();

        for(int i = 0; i < *(int*)(pBuffer); i++){
        
            if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * i), nomeRemover) == 0){ //compara o nome lido com os percorridos
                if(i == *(int*)(pBuffer)){ // se é o último elemento que deseja remover
                    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * ((*(int*)(pBuffer) - 1)));
                }
                else{
                    for(int j = i + 1; j < *(int*)(pBuffer); j++){ 
                        strcpy((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * i), (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * j));
                        *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i) = *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * j);
                        *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i) = *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * j);
                        i++;
                    }
                    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * ((*(int*)(pBuffer) - 1)));
                    if(!pBuffer){
                        printf("Erro ao alocar memoria.\n");
                        exit(1);
                    }
                }
                contador++;
                *(int*)(pBuffer) -= 1;
            }        
        }

        if(contador == 0){
            printf("Nome nao encontrado\n");
        }
    }
    else{
        printf("Lista vazia.\n");
    }

    return pBuffer;
}

void buscar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        int contador = 0;
        char nomeBuscar[10];
        printf("Informe um nome: ");
        scanf("%s", nomeBuscar);
        getchar();

        for(int i = 0; i < *(int*)(pBuffer); i++){
        
            if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * i), nomeBuscar) == 0){ //compara o nome lido com os percorridos
                printf("Nome: %s| ", (char *)pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * i); 
                printf("Idade: %d| ", *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i));
                printf("Telefone: %d\n", *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i));
                contador++;
            }        
        }

        if(contador == 0){
            printf("Nome nao encontrado\n");
        }
    }
    else{
        printf("Lista vazia.\n");
    }
}

void listar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        for(int i = 0; i < *(int*)(pBuffer); i++){ //i=0; i<qtdeContatos; i++
            printf("Nome: %s| ", (char *)pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int) * 2) * i); //Lista os nomes, é como se fosse nome[i]
            printf("Idade: %d| ", *(int *)(pBuffer + sizeof(int) + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i));
            printf("Telefone: %d\n", *(int *)(pBuffer + sizeof(int) * 2 + sizeof(char) * 10 + (sizeof(char) * 10 + sizeof(int) * 2) * i));
        }
    }
    else{
        printf("Lista vazia.\n");
    }
}