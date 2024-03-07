<h1 align="center">
    File Compressor - Huffman
</h1>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="/.github/cover.png">
  <source media="(prefers-color-scheme: light)" srcset="/.github/cover_light.png">
  <img alt="Main project cover" src="/.github/cover_light.png">
</picture>

## 💻 Projeto

Um compactador e descompactador de arquivos com base no Algoritmo de Huffman, desenvolvido como AV2 da disciplina de Estrutura de Dados por discentes do curso de Ciência da Computação.

> [!NOTE]
> Os arquivos restantes do projeto estão disponíveis em: [https://drive.google.com/drive/folders/1iTDoScdPs6Fg8qhWdWpXTZJ1RoaVnmYH?usp=sharing](https://drive.google.com/drive/folders/1iTDoScdPs6Fg8qhWdWpXTZJ1RoaVnmYH?usp=sharing)

#### 🧭 Disponível inicialmente para Terminal

<br />

## ✨ Tecnologias

| Backend |
| ------- |
| C       |

<br />

> [!WARNING]
> O projeto encontra-se em desenvolvimento, portanto, diversos aspectos estarão inacabados e/ou não funcionais, à medida que a aplicação torna-se mais robusta.

<br />

<br />

## 🧠 Princípios

1.  Ser capaz de **compactar e descompactar** QUALQUER tipo de arquivo
2.  Todos os Tipos Abstratos de Dados (TADs) devem ser **documentados**
3.  Todas as estruturas de dados devem ser implementadas com `*void`
4.  Toda as estruturas de dados utilizadas no projeto devem possuir **Casos de Testes Unitários**

## 🔧 Compilação e execução

A fim de facilitar o processo de _compilação_ do código durante a fase de desenvolvimento e testes, tendo em visto o alto grau de modularização do projeto, o repositório faz uso de um arquivo `Makefile`, responsável por lidar com o gerenciamento de dependências nos arquivos `.c`.  
Durante o desenvolvimento com o Visual Studio Code (VSCode), para que o processo de _build_ ocorra corretamente, [baixe a extensão](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools) disponibilizada pela Microsoft para esse tipo de arquivo.

Quando necessário compilar o código da aplicação, utilize no terminal:

```
make run
```

> Caso seja de interesse **somente** compilar o código, sem executá-lo logo em seguida, utilize somente `make`

Caso seja necessário realizar uma limpeza dos arquivos locais, utilize no terminal:

```
make clean
```

#### Diferença entre arquivos `.c` e `.h`

- .c: arquivo c (onde está a ação real, em geral)

- .h: arquivo de cabeçalho (a ser incluído em uma diretiva #include do pré-processador). Contém coisas que normalmente são compartilhadas com outras partes do código, como protótipos de funções, declarações #define' e assim por diante.

> [!NOTE]  
> Caso queira saber mais sobre como a modularização e arquivos `Makefile` funcionam, visite estes links:
>
> - [Programação modular em C - forcepush.tech](https://forcepush.tech/modular-programming-in-c)
> - ["o que as extensões de arquivo c e h significam para c" - stackoverflow.com](https://stackoverflow.com/questions/1695224/what-do-c-and-h-file-extensions-mean-to-c)

<br />

## 🧪 Testes unitários

Como parte do processo de desenvolvimento, é necessário que todos os módulos e estruturas de dados implementadas possuam testes unitários.  
~~Os testes unitários são realizados com a biblioteca `cmocka`, que é uma biblioteca de teste unitário para C.~~

Para executar os testes unitários, utilize no terminal:

```
make test
```

<br />

## 🚧 Roadmap

- [ ] Desenvolver os módulos de `heap` e `árvore de huffman` para utilização nos processos de compressão e descompressão
- [ ] Implementar o algoritmo básico para compressão de textos (char\*)

<br />

## 👥 Grupo

- [ ] [Eduardo Maciel Alexandre](https://github.com/theduardomaciel)
- [ ] Eliezir Moreira Peixoto Neto
- [ ] [Lucas Cassiano Maciel dos Santos](https://github.com/lucas7maciel)
- [ ] [Maria Letícia Ventura de Oliveira](https://github.com/letsventura)
- [ ] [Josenilton Ferreira da Silva Junior](https://github.com/914joseph)

<br />

## 🔗 Links úteis

#### Teoria

| Vídeos                                                                                                  | Artigos                                                                                      |
| ------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
| [Básico do Algoritmo de Huffman _(curto e bem didático!)_](https://www.youtube.com/watch?v=JsTptu56GM8) | [Codificação de Huffman - Wikipedia em inglês](https://en.wikipedia.org/wiki/Huffman_coding) |
| [História e Funcionamento do Código de Huffman](https://www.youtube.com/watch?v=B3y0RsVCyrw)            |                                                                                              |

#### Implementação

- [Codificação Huffman - Geeks for Geeks](https://www.youtube.com/watch?v=0kNXhFIEd_w&t=413s)
- [Codificação Huffman Eficiente - Geeks for Geeks](https://www.youtube.com/watch?v=IX810fNtTzU&t=12s)

#### Documentação

- [Guia para a documentação do código em C com Doxygen](https://embeddedinventor.com/guide-to-configure-doxygen-to-document-c-source-code-for-beginners/)

#### Testes unitários

- [Framework de testes para C](https://cmocka.org/)

<br />
