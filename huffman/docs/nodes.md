# Nós na árvore de Huffman

Numa árvore de Huffman, os nós podem ser `internos` ou `folhas`.  
Os **nós internos** representam a junção de dois nós filhos, enquanto as **folhas** representam um caractere e sua frequência.  
Para diferenciar os dois tipos de nós, utilizamos um caractere de escape antes de escrever um nó folha que possa ser confundido com um nó interno.  
Isso é necessário porque o caractere `*` é utilizado para representar nós internos, e **os nós folha podem assumir qualquer valor**.  
Portanto, precisamos de um caractere de escape para diferenciar os dois tipos de nós.

#### Precisamos prestar atenção a outro detalhe!

Caso o valor de um nó folha seja uma contra-barra (`\`) precisamos escapar esse caractere para que ele não seja interpretado como um caractere de escape pelo compilador.  
Basicamente, anulamos o efeito padrão do compilador de considerar a contra-barra (`\`) como um sinal para escape.

### Exemplos

#### Exemplo com nó folha contendo asterisco

Considere a árvore de Huffman abaixo:

```
    *
   / \
  *   *
 / \
b   c
```

Como podemos ver, o caractere `*` é utilizado para representar nós internos, enquanto os caracteres `*` (à direita da raiz), `b` e `c` são nós folha.

> [!NOTE]
> Para simplificar a escrita, omitimos as frequências dos nós folha, no entanto, numa situação real os nós folha seriam representados com um caractere e sua frequência.

Para diferenciar os dois tipos de nós, utilizamos um caractere de escape `\` antes de escrever um nó folha que possa ser confundido com um nó interno. Portanto, a árvore de Huffman em pré-ordem seria escrita como:

```
**bc\*
```

#### Exemplo com nó folha contendo contra-barra

Considere a árvore de Huffman abaixo:

```
    *
   / \
  *   *
 / \
b   \
```

Como podemos ver, o caractere `*` é utilizado para representar nós internos, enquanto os caracteres `*` (à direita da raiz), `b` e `\` (à direita do nó `b`) são nós folha.

Para evitar que o nó (`\`) seja interpretado como um caractere de escape, precisamos escapar esse caractere. Portanto, a árvore de Huffman em pré-ordem seria escrita como:

```
**b\\*
```