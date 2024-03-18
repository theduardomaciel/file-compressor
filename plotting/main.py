import matplotlib.pyplot as plt
import sys
import numpy as np
from os import system

#Gets cmd args (if they exist)
ordenado = False if "desordenado" in sys.argv else True
escalado = False if "escalado" not in sys.argv else True
recorte = False if "recorte" not in sys.argv else True
novo = False if "previous" in sys.argv else True
onlyListas = False if not "listas" in sys.argv else True
onlyArvores = False if not "arvores" in sys.argv else True

#Generates new numbers
if ordenado and novo:
    system("gcc gerar_ordenado.c -o data && data")
elif novo:
    system("gcc gerar_desordenado.c -o data && data")

#Gets generated file data
file = open("data.txt", "r")

gerados = []
listas = []
arvores = []

counter = 1

while True:
    content = file.readline()

    if not content:
        break

    contentList = content.split(" ")

    if ordenado:
        gerados.append(int(contentList[0]))
    else:
        gerados.append(counter)

    listas.append(int(contentList[1]))
    arvores.append(int(contentList[2].replace("\n", "")))

    counter += 1

file.close()

#Sorts the lists
if not ordenado:
    ##gerados = [1, 2, 3... n]
    listas = sorted(listas)
    arvores = sorted(arvores)
    pass


if recorte:
    gerados = gerados[:100]
    listas = listas[:100]
    arvores = arvores[:100]


#Sets graph's styling
if not escalado or onlyListas or onlyArvores:
    #Sets width, color and path of each data structure
    if not onlyArvores:
        plt.plot(gerados, listas, label="Listas Encadeadas")
        plt.annotate(f'{listas[-1]}', xy=(max(gerados) - 5, listas[-1] - 10), color='blue')

    if not onlyListas:
        plt.plot(gerados, arvores, label="Árvores de Busca")
        plt.annotate(f'{arvores[-1]}', xy=(max(gerados) - 5, arvores[-1] + 4), color='red')

    plt.legend()
else:
    x = np.arange(len(gerados))

    fig, ax1 = plt.subplots()

    #Sets color, width and path of yaxis1
    color = 'tab:red'
    ax1.plot(x, listas, color=color)
    line1, = ax1.plot(x, listas, color=color, label='Listas Encadeadas')
    ax1.tick_params(axis='y', labelcolor=color)

    ax2 = ax1.twinx()

    #Sets color, width and path of yaxis2
    color = 'tab:blue'
    ax2.plot(x, arvores, color=color)
    line2, = ax2.plot(x, arvores, color=color, label='Árvores de Busca Binárias')
    ax2.tick_params(axis='y', labelcolor=color)

    ax1.legend(handles=[line1, line2])

for x in range(len(gerados)):
    #Label points that have the same value on both lists
    if (listas[x] == arvores[x] and not escalado):
        plt.annotate('.', xy=(gerados[x], listas[x]), color='purple', fontsize=16)
        plt.annotate(listas[x], xy=(gerados[x] - 1.5, listas[x] + 5), color='purple', fontsize=12)
        break

plt.title("Listas Encadeadas x Árvores de Busca Binárias")
plt.xlabel('Elementos')
plt.ylabel('Comparações')

plt.show()
