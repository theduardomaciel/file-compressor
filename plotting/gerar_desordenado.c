#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct node{
    int valor;
    struct node *next;
};

struct arvore{
    int valor;
    struct arvore *left;
    struct arvore *right;
};

struct node* create_node(int valor){
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->valor = valor;
    newnode->next = NULL;

    return newnode;
}


struct arvore* create_arvore(int valor){
    struct arvore* newarvore = (struct arvore*) malloc(sizeof(struct arvore));
    newarvore->valor = valor;
    newarvore->left = NULL;
    newarvore->right = NULL;

    return newarvore;
}

struct arvore *inserirArvore(struct arvore *arvore,int valor){
    if(arvore==NULL){
        return create_arvore(valor);
    }
    if (valor < arvore->valor) {
        arvore->left = inserirArvore(arvore->left, valor);
    } else if (valor > arvore->valor) {
        arvore->right = inserirArvore(arvore->right, valor);
    }
    return arvore;

}

struct node *inserirLista(struct node *node,int valor){
    if(node==NULL){
        node = create_node(valor);
    }else{
        //printf("valor %d\n",node->valor);
        struct node *newnode = create_node(valor);
        newnode->next = node;
        node = newnode;

    }
    return node;

}

int giveRandom(int min, int max) {
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

int jaFoi(int array[],int random_num, int index_array_randoms){
    int i=0;
    while(i<=index_array_randoms){
        if(random_num == array[i]){
            //printf("%d e %d s�o iguais\n",random_num,array[i]);
            return 1;
        }
        i++;
    }
    return 0;
}

int jaFoiMatriz(int matriz[][3],int random_num, int index_matriz_search){
    int i=0;
    while(i<=index_matriz_search){
        if(random_num == matriz[i][0]){
            //printf("%d e %d s�o iguais\n",random_num,array[i]);
            return 1;
        }
        i++;
    }
    return 0;
}

void printArvoreEmOrdem(struct arvore *arvore) {
    if (arvore != NULL) {
        printArvoreEmOrdem(arvore->left);
        printf("%d ", arvore->valor);
        printArvoreEmOrdem(arvore->right);
    }
}

void printLista(struct node *node){
    struct node *aux = node;
    while(aux!=NULL){
        printf("%d ",aux->valor);
        aux = aux->next;
    }
}

void printRandoms(int array[],int index_array_randoms){
    int i=0;
    while(i<index_array_randoms){
        printf("%d ",array[i]);
        i++;
    }
}

int buscaLista(struct node *node,int valor){
    struct node *aux = node;
    int comparacoes=0;
    while(aux!=NULL){
        comparacoes++;
        if(aux->valor == valor){
            return comparacoes;
        }
        aux = aux->next;
    }
}

int buscaArvore(struct arvore *arvore,int valor,int *comp_arvore){
    if(arvore==NULL){
        return -1;
    }else{
        (*comp_arvore)++;
        if(arvore->valor == valor){
            return *comp_arvore;
        }else{
            if(arvore->valor > valor){
                return buscaArvore(arvore->left,valor,comp_arvore);
            }else if(arvore->valor < valor){
                return buscaArvore(arvore->right,valor,comp_arvore);
            }

        }

    }
}

void printMatriz(int matriz[][3],int index_matriz_search){
    int i=0;
    while(i<index_matriz_search){
        printf("[%d,%d,%d]\n",matriz[i][0],matriz[i][1],matriz[i][2]);
        i++;
    }
}

void colocar(char matrizz[][30], int matriz[][3],int index_matriz_search, int *index_matriz_colocar){
    int i=0;
    while(i<index_matriz_search){
        sprintf(matrizz[i],"%d %d %d",matriz[i][0],matriz[i][1],matriz[i][2]);
        (*index_matriz_colocar)++;
        i++;
    }
}

void printMatrizColocar(char matrizz[][30],int index_matriz_colocar){
    int i=0;
    while(i<index_matriz_colocar){
        printf("%s\n",matrizz[i]);
        i++;
    }
}

int main()
{
    printf("inicio\n");
    struct node *lista_encadeada = NULL;
    struct arvore *arvore_bi = NULL;
    srand(time(0));
    int quant_num=10000;
    int array_randoms[10000];
    int index_array_randoms = 0;
    while(quant_num!=0){

        int random_num = giveRandom(0,10000);
        if(jaFoi(array_randoms,random_num,index_array_randoms)){
            quant_num++;
        }else{
            array_randoms[index_array_randoms] = random_num;
            index_array_randoms++;
            arvore_bi = inserirArvore(arvore_bi,random_num);
            lista_encadeada = inserirLista(lista_encadeada,random_num);

        }

        quant_num--;
    }
    printf("Array de Numeros randomizados:\n");
    printRandoms(array_randoms,index_array_randoms);
    printf("\n");
    printf("Lista Encadeada:\n");
    printLista(lista_encadeada);
    printf("\n");
    printf("Arvore em Ordem:\n");
    printArvoreEmOrdem(arvore_bi);
    printf("\n");

    int quant_search = 1000;

    int matriz[1000][3];
    int index_matriz_search = 0;

    while(quant_search!=0){

        int random_num = giveRandom(0,10000);
        if(jaFoiMatriz(matriz,random_num,index_matriz_search)){
            quant_search++;
        }else{
            int comp_arvore=0;
            int comparacoesLista = buscaLista(lista_encadeada,random_num);
            struct arvore *aux_arvore = arvore_bi;
            buscaArvore(aux_arvore,random_num,&comp_arvore);
            int comparacoesArvore=comp_arvore;
            matriz[index_matriz_search][0]=random_num;
            matriz[index_matriz_search][1]=comparacoesLista;
            matriz[index_matriz_search][2]=comparacoesArvore;
            index_matriz_search++;
        }
        quant_search--;
    }

    memset(array_randoms,0,10000);
    char matrizz[1000][30];
    int index_matriz_colocar=0;

    colocar(matrizz,matriz, index_matriz_search,&index_matriz_colocar);
    printf("\n\n\n");
    printMatrizColocar(matrizz,index_matriz_colocar);
    printf("\n\n\n");
    //printf("[valor,comp_lista,comp_arvore]:\n");
    //printMatriz(matriz,index_matriz_search);
    FILE *fPtr;
    fPtr = fopen("data.txt", "w");

    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    int i=0;
    while(i<index_matriz_search){
        fputs(matrizz[i], fPtr);
        fputs("\n", fPtr);
        i++;
    }

    fclose(fPtr);

    printf("fim\n");
    memset(matrizz,'\0',1000);
    memset(matriz,0,1000);

    return 0;
}
