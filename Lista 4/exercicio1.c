#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void listarVetor(int *vetor, int tam);
int limparVetor(int *vetor);
void insertionSort(int *vetor, int tam);
void selectionSort(int *vetor, int tam);
void quickSort(int *vetor, int esquerda, int direita);
void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);

int main(){
    int *vetor, tam = 0, random, op;
    do{
        if(tam == 0){
            srand(time(NULL));

            printf("Qual o tamanho do vetor que desejas?\n");
            scanf("%d", &tam);
            vetor = malloc(sizeof(int) * tam);

            for(int i=0; i<tam; i++){
                random = rand()%1000;
                vetor[i] = random;
            }
        }

        printf("<1> Insertion Sort\n");
        printf("<2> Selection Sort\n");
        printf("<3> Quick Sort\n");
        printf("<4> Merge sort\n");
        printf("<5> Listar vetor\n");
        printf("<6> Limpar vetor\n");
        printf("<7> Sair\n");
        scanf("%d", &op);
        
        switch(op){
            case 1:
            insertionSort(vetor, tam);
            break;

            case 2:
            selectionSort(vetor, tam);
            break;

            case 3:
            quickSort(vetor, 0, tam-1);
            break;

            case 4:
            mergeSort(vetor, 0, tam-1);
            break;
            

            case 5:
            listarVetor(vetor, tam);
            break;

            case 6:
            tam = limparVetor(vetor);
            break;

            case 7:
            free(vetor);
            exit(1);
            break;

            default:
            printf("opcao invalida.\n");
            break;
        }
    }while(op!=7);
}

int limparVetor(int *vetor){
    if(vetor != NULL){
        free(vetor);
        return 0;
    }
    else
        return 0;
}

void listarVetor(int *vetor, int tam){
    for(int k=0; k<tam; k++){
        printf("%d\n", vetor[k]);
    }
}

void insertionSort(int *vetor, int tam){
    int i, j, x;
    for (i=1; i<tam; i++){
	    x = vetor[i];
	    j=i-1;

	    while ((j>=0) && (x < vetor[j])){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = x;
    }

}

void selectionSort(int *vetor, int tam){
    int menor, menor_id, temp, i, j;

    for(i=0; i<tam-1; i++){
        menor = vetor[i];
        for(j=i+1; j<tam; j++){
            if(vetor[j] < menor){
                menor = vetor[j];
                menor_id = j;
            }
        }
        /*coloca o menor na sua posição*/
        temp = vetor[i];
        vetor[i] = vetor[menor_id];
        vetor[menor_id] = temp;
        menor_id = i+1;
    }

    for(int k=0; k<tam; k++){
        printf("%d\n", vetor[k]);
    }
}

void quickSort(int *vetor, int esquerda, int direita){

    int meio,temp,i,j;
    i = esquerda;
    j = direita;
    meio = vetor[(esquerda + rand()%direita)];
    do{
        while(vetor[i] < meio)
            i++;
        while(meio < vetor[j])
            j--;
        if(i <= j){
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }while(i <= j);
        if(esquerda < j)
            quickSort(vetor,esquerda,j);
        if(i < direita)
            quickSort(vetor,i,direita);
}

void mergeSort(int *vetor, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void merge(int *vetor, int inicio, int meio, int fim){
    int *temp, n1, n2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    n1 = inicio;
    n2 = meio+1;
    temp = malloc(sizeof(int)*tamanho);

    if(temp!=NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(vetor[n1] < vetor[n2]) //adicionando no vetor temporario ordenado
                    temp = vetor[n1++];
                else
                    temp = vetor[n2++];

                if(n1>meio)
                    fim1 = 1;
                if(n2>fim)
                    fim2=1;
            }
            else{ //o que sobrou copia pro temp
                if(!fim1)
                    temp[i] = vetor[n1++];
                else
                    temp[i] = vetor[n2++];
            }
        }

        for(j=0, k=inicio; j<tamanho; j++, k++){ //copia ordenado pro vetor de novo
            vetor[k] = temp[j];
        }
    }
    free(temp);
}