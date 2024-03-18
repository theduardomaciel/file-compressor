#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdio.h>
#include <stdlib.h>

// Enumeração para representar as cores dos nós
enum Color
{
    RED,
    BLACK
};

// Estrutura para representar um nó da árvore rubro-negra
struct treeNode
{
    int data; // Dados armazenados no nó
    int color; // Cor do nó (RED ou BLACK)
    struct treeNode *link[2]; // Ponteiros para os filhos esquerdo (link[0]) e direito (link[1])
    struct treeNode *parent; // Ponteiro para o pai do nó
};

// Variável global representando a raiz da árvore
extern struct treeNode *root;

// Funções do TAD

/**
 * @brief Cria um novo nó com o dado fornecido.
 * 
 * @param data O dado a ser armazenado no novo nó.
 * @return struct treeNode* Um ponteiro para o novo nó criado.
 */
struct treeNode *createNode(int data);

/**
 * @brief Insere um novo nó com o dado fornecido na árvore rubro-negra.
 * 
 * @param data O dado a ser inserido na árvore.
 */
void insertNode(int data);

/**
 * @brief Remove o nó com o dado fornecido da árvore rubro-negra.
 * 
 * @param data O dado do nó a ser removido.
 */
void deleteNode(int data);

/**
 * @brief Busca o dado especificado na árvore rubro-negra.
 * 
 * @param data O dado a ser buscado na árvore.
 */
void search(int data);

/**
 * @brief Realiza uma rotação para a esquerda em torno do nó fornecido.
 * 
 * @param x O nó em torno do qual a rotação será realizada.
 */
void leftRotate(struct treeNode *x);

/**
 * @brief Realiza uma rotação para a direita em torno do nó fornecido.
 * 
 * @param x O nó em torno do qual a rotação será realizada.
 */
void rightRotate(struct treeNode *x);

/**
 * @brief Ajusta as cores dos nós após a inserção de um novo nó.
 * 
 * @param ptr O nó inserido que pode violar as propriedades da árvore.
 */
void insertionFixUp(struct treeNode *ptr);

/**
 * @brief Ajusta as cores dos nós após a exclusão de um nó.
 * 
 * @param ptr O nó que substituiu o nó removido.
 * @param parent_ptr O pai do nó que substituiu o nó removido.
 */
void deletionFixUp(struct treeNode *ptr, struct treeNode *parent_ptr);

/**
 * @brief Realiza uma travessia em ordem na árvore rubro-negra e imprime os dados dos nós.
 * 
 * @param node O nó a partir do qual a travessia em ordem será iniciada.
 */
void inorderTraversal(struct treeNode *node);

/**
 * @brief Realiza uma travessia pré-ordem na árvore rubro-negra e imprime os dados dos nós.
 * 
 * @param node O nó a partir do qual a travessia pré-ordem será iniciada.
 */
void preorderTraversal(struct treeNode *node);

#endif /* REDBLACK_H */
