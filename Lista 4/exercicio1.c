#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *vetor, int tam);
void selectionSort(int *vetor, int tam);
void quickSort(int *vetor, int esquerda, int direita);
void mergeSort(int *vetor);

int main(){
    int tam, random, op;
    srand(time(NULL));

    printf("Qual o tamanho do vetor que desejas?\n");
    scanf("%d", &tam);
    int *vetor = malloc(sizeof(int) * tam);

    for(int i=0; i<tam; i++){
        random = rand()%1000;
        vetor[i] = random;
    }

    for(int k=0; k<tam; k++){
        printf("%d\n", vetor[k]);
    }

    do{
        printf("<1> Insertion Sort\n");
        printf("<2> Selection Sort\n");
        printf("<3> Quick Sort\n");
        printf("<4> Merge sort\n");
        printf("<5> Sair\n");
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
            for(int k=0; k<tam; k++){
                printf("%d\n", vetor[k]);
            }
            break;

            /*case 4:
            mergeSort(vetor, tam);
            break;
            */
            case 5:
            free(vetor);
            exit(1);
            break;

            default:
            printf("opcao invalida.\n");
            break;
        }
    }while(op!=5);
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

    for(int k=0; k<tam; k++){
        printf("%d\n", vetor[k]);
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
    meio = vetor[(esquerda + direita)/2];
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