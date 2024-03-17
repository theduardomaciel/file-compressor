# Leitura e processamento de bytes

Para lidarmos com a compactação de qualquer tipo arquivo por meio do algoritmo de Huffman, precisamos de uma forma de ler e processar os bytes do arquivo.

> Mesmo que a compactação em arquivos binários, os quais não são compostos de texto propriamente dito, não seja recomendada, devido à natureza desses arquivos e de suas estratégias de compactação, é possível realizar a compactação de arquivos binários, como imagens, vídeos, áudios, entre outros.

### Por que o uso do número 256 durante a leitura e escrita de bytes?

Utilizamos o número **256** pois esta é a quantidade de combinações possíveis quando estamos lidando com bytes.

> [!NOTE]
> byte = unidade de dados de 8 bits

Cada byte pode ter 256 valores diferentes possíveis, variando de 0 a 255. Isso ocorre porque um byte de 8 bits pode representar `2^8 = 256` valores distintos.

No contexto de arquivos binários, cada byte pode representar um caractere ou um valor numérico dentro de um intervalo de 0 a 255.  
Por exemplo, se estivermos lidando com um arquivo de texto, cada byte pode representar um caractere, como letras, números, espaços em branco, sinais de pontuação, etc. Se estivermos lidando com arquivos de imagem, cada byte pode representar a intensidade de um pixel em uma escala de cores específica, como em imagens em tons de cinza ou em uma das cores RGB em uma imagem colorida.

Portanto, as frequências de bytes em arquivos binários podem ter no máximo 256 combinações possíveis porque cada byte pode assumir um dos 256 valores diferentes possíveis em um byte de 8 bits.
