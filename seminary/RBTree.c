#include "RBTree.h"

struct treeNode *root = NULL;

struct treeNode *createNode(int data)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    newNode->data = data;
    newNode->color = RED;
    newNode->link[0] = newNode->link[1] = NULL;
    return newNode;
}

// Função para realizar a rotação para a esquerda
void leftRotate(struct treeNode *x)
{
    struct treeNode *y = x->link[1]; 
    x->link[1] = y->link[0]; 
    if (y->link[0] != NULL)  
        y->link[0]->parent = x; 
    if (y != NULL)
        y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->link[0])
        x->parent->link[0] = y;
    else
        x->parent->link[1] = y;
    y->link[0] = x;
    if (x != NULL)
        x->parent = y;
}

// Função para realizar a rotação para a direita
void rightRotate(struct treeNode *x)
{
    struct treeNode *y = x->link[0];
    x->link[0] = y->link[1];
    if (y->link[1] != NULL)
        y->link[1]->parent = x;
    if (y != NULL)
        y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->link[1])
        x->parent->link[1] = y;
    else
        x->parent->link[0] = y;
    y->link[1] = x;
    if (x != NULL)
        x->parent = y;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ajustar as cores após a inserção
void insertionFixUp(struct treeNode *ptr)
{
    while (ptr->parent != NULL && ptr->parent->color == RED)
    {
        struct treeNode *parent_ptr = ptr->parent;
        struct treeNode *grand_parent_ptr = ptr->parent->parent;

        // Se o pai for o filho da esquerda do avô
        if (parent_ptr == grand_parent_ptr->link[0])
        {
            struct treeNode *uncle_ptr = grand_parent_ptr->link[1];

            // Se o tio for vermelho (o pai também é vermelho), troca as cores
            // Isso mantém a propriedade 3 (se um nó é "vermelho", então os seus filhos são "pretos")
            if (uncle_ptr != NULL && uncle_ptr->color == RED)
            {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            }
            else
            {
                // Se o nó for o filho da direita do pai, faz uma rotação para a esquerda
                // Isso mantém a propriedade 4 (todos os caminhos de um nó para os nós folhas 
                // descendentes contém o mesmo número de nós "pretos")
                if (ptr == parent_ptr->link[1])
                {
                    leftRotate(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }
                // Faz uma rotação para a direita no avô e troca as cores do pai e do avô
                // Isso mantém a propriedade 3 (se um nó é "vermelho", então os seus filhos são "pretos")
                rightRotate(grand_parent_ptr);
                swap(&(parent_ptr->color), &(grand_parent_ptr->color));
                ptr = parent_ptr;
            }
        }
        else
        {
            struct treeNode *uncle_ptr = grand_parent_ptr->link[0];

            // Se o tio for vermelho (o pai também é vermelho), troca as cores
            // Isso mantém a propriedade 3 (se um nó é "vermelho", então os seus filhos são "pretos")
            if (uncle_ptr != NULL && uncle_ptr->color == RED)
            {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            }
            else
            {
                // Se o nó for o filho da esquerda do pai, faz uma rotação para a direita
                // Isso mantém a propriedade 4 (todos os caminhos de um nó para os nós folhas descendentes contém o mesmo número de nós "pretos")
                if (ptr == parent_ptr->link[0])
                {
                    rightRotate(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }
                // Faz uma rotação para a esquerda no avô e troca as cores do pai e do avô
                // Isso mantém a propriedade 3 (se um nó é "vermelho", então os seus filhos são "pretos")
                leftRotate(grand_parent_ptr);
                swap(&(parent_ptr->color), &(grand_parent_ptr->color));
                ptr = parent_ptr;
            }
        }
    }
    // A raiz é sempre "preta" (propriedade 1)
    root->color = BLACK;
}

// Função para inserir um nó na árvore
void insertNode(int data)
{
    struct treeNode *ptr = root, *parent_ptr = NULL;
    while (ptr != NULL)
    {
        if (data == ptr->data)
        {
            printf("Valores duplicados nao sao permitidos!\n");
            return;
        }
        parent_ptr = ptr;
        ptr = (data < ptr->data) ? ptr->link[0] : ptr->link[1];
    }
    struct treeNode *newNode = createNode(data);
    newNode->parent = parent_ptr;
    if (parent_ptr == NULL)
        root = newNode;
    else if (data < parent_ptr->data)
        parent_ptr->link[0] = newNode;
    else
        parent_ptr->link[1] = newNode;
    insertionFixUp(newNode);
}

// Função para ajustar as cores após a exclusão
void deletionFixUp(struct treeNode *ptr, struct treeNode *parent_ptr)
{
    while (ptr != root && (ptr == NULL || ptr->color == BLACK))
    {
        if (ptr == parent_ptr->link[0])
        {
            struct treeNode *sibling = parent_ptr->link[1];
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                parent_ptr->color = RED;
                leftRotate(parent_ptr);
                sibling = parent_ptr->link[1];
            }
            if ((sibling->link[0] == NULL || sibling->link[0]->color == BLACK) &&
                (sibling->link[1] == NULL || sibling->link[1]->color == BLACK))
            {
                sibling->color = RED;
                ptr = parent_ptr;
                parent_ptr = ptr->parent;
            }
            else
            {
                if (sibling->link[1] == NULL || sibling->link[1]->color == BLACK)
                {
                    sibling->link[0]->color = BLACK;
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = parent_ptr->link[1];
                }
                sibling->color = parent_ptr->color;
                parent_ptr->color = BLACK;
                sibling->link[1]->color = BLACK;
                leftRotate(parent_ptr);
                ptr = root;
            }
        }
        else
        {
            struct treeNode *sibling = parent_ptr->link[0];
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                parent_ptr->color = RED;
                rightRotate(parent_ptr);
                sibling = parent_ptr->link[0];
            }
            if ((sibling->link[0] == NULL || sibling->link[0]->color == BLACK) &&
                (sibling->link[1] == NULL || sibling->link[1]->color == BLACK))
            {
                sibling->color = RED;
                ptr = parent_ptr;
                parent_ptr = ptr->parent;
            }
            else
            {
                if (sibling->link[0] == NULL || sibling->link[0]->color == BLACK)
                {
                    sibling->link[1]->color = BLACK;
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = parent_ptr->link[0];
                }
                sibling->color = parent_ptr->color;
                parent_ptr->color = BLACK;
                sibling->link[0]->color
 = BLACK;
                rightRotate(parent_ptr);
                ptr = root;
            }
        }
    }
    if (ptr != NULL)
        ptr->color = BLACK;
}

// Função para remover um nó da árvore
void deleteNode(int data)
{
    struct treeNode *ptr = root, *parent_ptr = NULL;
    while (ptr != NULL)
    {
        if (data == ptr->data)
            break;
        parent_ptr = ptr;
        ptr = (data < ptr->data) ? ptr->link[0] : ptr->link[1];
    }
    if (ptr == NULL)
    {
        printf("Elemento nao faz parte da arvore\n");
        return;
    }
    struct treeNode *x, *y = ptr;
    enum Color y_original_color = y->color;
    if (ptr->link[0] == NULL)
    {
        x = ptr->link[1];
        if (parent_ptr == NULL)
            root = x;
        else if (ptr == parent_ptr->link[0])
            parent_ptr->link[0] = x;
        else
            parent_ptr->link[1] = x;
        if (x != NULL)
            x->parent = parent_ptr;
    }
    else if (ptr->link[1] == NULL)
    {
        x = ptr->link[0];
        if (parent_ptr == NULL)
            root = x;
        else if (ptr == parent_ptr->link[0])
            parent_ptr->link[0] = x;
        else
            parent_ptr->link[1] = x;
        if (x != NULL)
            x->parent = parent_ptr;
    }
    else
    {
        y = ptr->link[1];
        while (y->link[0] != NULL)
            y = y->link[0];
        y_original_color = y->color;
        x = y->link[1];
        if (y->parent == ptr)
            x->parent = y;
        else
        {
            if (parent_ptr == NULL)
                root = x;
            else if (ptr == parent_ptr->link[0])
                parent_ptr->link[0] = x;
            else
                parent_ptr->link[1] = x;
            if (x != NULL)
                x->parent = parent_ptr;
            y->link[1] = ptr->link[1];
            ptr->link[1]->parent = y;
        }
        if (parent_ptr == NULL)
            root = y;
        else if (ptr == parent_ptr->link[0])
            parent_ptr->link[0] = y;
        else
            parent_ptr->link[1] = y;
        y->parent = parent_ptr;
        y->color = ptr->color;
        y->link[0] = ptr->link[0];
        ptr->link[0]->parent = y;
    }
    free(ptr);
    if (y_original_color == BLACK)
        deletionFixUp(x, parent_ptr);
}

void search(int data)
{
    struct treeNode *ptr = root;
    int found = 0;
    while (ptr != NULL)
    {
        if (data == ptr->data)
        {
            found = 1;
            break;
        }
        if (data > ptr->data)
            ptr = ptr->link[1];
        else
            ptr = ptr->link[0];
    }
    if (found)
    {
        printf("O valor %d se encontra na arvore :)\n", data);
    }
    else
    {
        printf("O valor %d nao se encontra na arvore :(\n", data);
    }
}

void inorderTraversal(struct treeNode *node)
{
    if (node)
    {
        inorderTraversal(node->link[0]);
        printf("%d  ", node->data);
        inorderTraversal(node->link[1]);
    }
}

void preorderTraversal(struct treeNode *node)
{
    if (node)
    {
        printf("%d  ", node->data);
        preorderTraversal(node->link[0]);
        preorderTraversal(node->link[1]);
    }
}

int main()
{
    int ch, data;
    while (1)
    {
        printf("\n1. Inserir\t2. Deletar\n");
        printf("3. Buscar\t4. Print\n");
        printf("5. Sair\nInsira sua opção:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Insira o valor a ser inserido:");
            scanf("%d", &data);
            insertNode(data);
            break;
        case 2:
            printf("Insira o valor a ser deletado:");
            scanf("%d", &data);
            deleteNode(data);
            break;
        case 3:
            printf("Insira o valor a ser buscado:");
            scanf("%d", &data);
            search(data);
            break;
        case 4:
            if (root)
            {
                printf("Inorder Traversal:\n");
                inorderTraversal(root);
                printf("\n");
                printf("Preorder Traversal:\n");
                preorderTraversal(root);
                printf("\n");
            }
            else
            {
                printf("A arvore esta vazia.\n");
            }
            break;
        case 5:
            exit(0);
        default:
            printf("Por favor, insira uma opcao valida amigao\n");
            break;
        }
    }
    return 0;
}
