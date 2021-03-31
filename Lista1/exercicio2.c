#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* inserir(char *string);
char* remover(char *string);
void listar(char *string);

int main(){
    char *string = NULL;
    int seleciona;
    do{
        /*MENU*/
        printf("Escolha a opcao desejada:\n");
        printf("<1> Adicionar nome\n");        
        printf ("<2> Remover nome\n");        
        printf ("<3> Listar todos os nomes\n");        
        printf ("<4> Sair\n");        
        scanf("%d", &seleciona);
        getchar();

        switch(seleciona){
            case 1:
                string = inserir(string);
                break;
            case 2:
                string = remover(string);
                break;

            case 3:
                listar(string);
            break;
            
            case 4:
                free(string);
                exit(1);
                break;
        }
    }while(seleciona != 4);
}

char *inserir(char *string){
    int tamanhoNome, tamanhoString;
    char *nome = (char *)malloc(sizeof(char)*100);
    printf("Qual nome desejas adicionar? ");
    scanf("%s", nome);
    getchar();

    tamanhoNome = strlen(nome); 
    nome[tamanhoNome] = ';';
    nome[tamanhoNome+1] = '\0';
    tamanhoNome = tamanhoNome+2;

    if(string==NULL){
        string = (char *)malloc(sizeof(char) * tamanhoNome);
        strcpy(string, nome);
    }
    else{
        tamanhoString = strlen(string);
        string = (char *)realloc(string, sizeof(char) * (tamanhoString + tamanhoNome));
        strcat(string, nome);
    }

    if(!string){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    free(nome);

    return string;

}

char* remover(char *string){
    if(!string){
        printf("A lista de nomes esta vazia.\n");
        return string;
    }
    else{
        int tamanhoString = strlen(string), tamanhoNomeAux, tamanhoNovaString = 0,  novoTamanho = 0, i, j, nomeRemovido=0;
        char *nomeRemover = NULL, *auxString = string, *novaString = NULL, *auxNome = NULL;
        auxNome = (char *)malloc(sizeof(char)*100);
        nomeRemover = (char *)malloc(sizeof(char)*100);

        printf("Digite qual nome deseja remover: ");
        scanf("%s", nomeRemover);
        getchar();

        for(i=0; i < tamanhoString; i++){ //percorre a string
            j=0;
            while(auxString[i] != ';'){
                auxNome[j++] = auxString[i++]; //armazena nome por nome para comparar
            }
            auxNome[j] = '\0';

            if(strcmp(nomeRemover, auxNome) != 0){
                strcat(auxNome,";");
                tamanhoNomeAux = strlen(auxNome);
                if(novaString == NULL){
                    novoTamanho = tamanhoNomeAux + 1;
                    novaString = (char*)malloc(sizeof(char) * novoTamanho);
                    strcpy(novaString, auxNome);
                    strcat(novaString, "\0");
                }
                else{
                    novoTamanho = tamanhoNovaString + tamanhoNomeAux + 2; //soma o tamanho atual com os demais
                    novaString = (char*)realloc(novaString, sizeof(char) * novoTamanho);
                    strcat (novaString, auxNome);
                    strcat(novaString, "\0");
                }

                tamanhoNovaString = novoTamanho; //tamanho atual da string
            }

            else{
                nomeRemovido++;
            }
        }
        
        if(nomeRemovido==0){
            printf("Nome nao encontrado.\n");
            free(auxNome);
            free(nomeRemover);
            free(novaString);
            return string;
        }
        else{
            free(string);
            free(auxNome);
            free(nomeRemover);
            return novaString;
        }
    }
    
}

void listar(char *string){
    char *auxiliar = string;
    if(!auxiliar){
        printf("A lista de nomes esta vazia.\n");
    }
    else{
        while(*auxiliar){
            if(*auxiliar!=';'){
                printf("%c", *auxiliar++); //pega o conteúdo de nome, o ++ acrescenta no endereço imprimindo o próximo caractere
            }
            else{
                printf("\n");
                auxiliar++;
            }
        }
    }
}