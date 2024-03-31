# Máscaras

Para aplicar máscaras em operações com bits em C, é necessário utilizar o prefixo `0b` seguido do valor binário da máscara.
Por exemplo, para criar uma máscara que tenha o bit mais à esquerda setado e os demais bits zerados, utilizamos `0b10000000`.
Para criar uma máscara que tenha os 3 bits mais à direita setados e os demais bits zerados, utilizamos `0b00000111`.

Para aplicar uma máscara em um valor, utilizamos o operador `&` (AND) entre o valor e a máscara.

### Exemplo:

```c
uint8_t value = 0b10101010;
uint8_t mask = 0b00001111;
uint8_t result = value & mask;
```

Neste exemplo, o valor de `result` será `0b00001010`, pois somente os 4 bits mais à direita de `value` são mantidos após a operação de AND com a máscara `mask`.
