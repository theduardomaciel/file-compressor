# Sobre o uso de stdint.h

Tendo em vista que o tamanho de um `int` pode variar dependendo da arquitetura do sistema, a biblioteca `stdint.h` foi criada para fornecer tipos de dados inteiros com tamanhos específicos e garantidos.
Isso é especialmente importante quando estamos lidando com a contagem de frequência de bytes em um arquivo, como é o caso da função `build_frequency_table` no arquivo `frequency_table.c`.  
Nesse contexto, é importante garantir que o tipo utilizado para armazenar a contagem de frequência seja grande o suficiente para acomodar todos os possíveis valores de contagem.

### De onde vem os nomes da biblioteca, como `uint64_t` e `uint8_t`?

- A letra 'u' no início indica "sem sinal", o que significa que esse tipo de dado só pode representar valores positivos (incluindo zero) e não possui um bit de sinal para representar valores negativos.
- O número após o 'int' (inteiros) indica o tamanho do tipo de dado em bits.
- O '\_t' no final do nome indica que o tipo de dado tem um tamanho específico garantido.

### Onde é utilizado

Esses tipos de dados são frequentemente utilizados em situações em que é necessário garantir que o tamanho do tipo de dado seja consistente em diferentes plataformas e arquiteturas de sistemas.  
O uso de `uint64_t` é comum em situações em que é necessário armazenar valores inteiros grandes, como contadores, tamanhos de arquivos e valores de tempo.  
Já o `uint8_t` é comumente utilizado para representar bytes de dados.

Em C e em linguagens que seguem o padrão C (como C++), uint64_t é definido na biblioteca padrão `stdint.h` (ou cstdint em C++) e pode ser utilizado após incluir essa biblioteca.

### Exemplo de uso

```c
#include <stdint.h>

int main()
{
    uint64_t large_number = 18446744073709551615;
    // O valor máximo que pode ser armazenado em um uint64_t é 18446744073709551615
    // O valor mínimo é 0
    return 0;
}
```
