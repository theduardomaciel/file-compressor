import matplotlib.pyplot as plt
from os import system
import sys
import numpy as np

#Gets cmd args (if they exist)
ordenado = False if "desordenado" in sys.argv else True
escalado = False if "escalado" not in sys.argv else True
recorte = False if "recorte" not in sys.argv else True
novo = False if "previous" in sys.argv else True 

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
if ordenado:
    print("Ordenando")

    n = len(gerados)
    swapped = False

    for i in range(n-1):
        for j in range(0, n-i-1):
            if gerados[j] > gerados[j + 1]:
                gerados[j], gerados[j + 1] = gerados[j + 1], gerados[j]
                listas[j], listas[j + 1] = listas[j + 1], listas[j]
                arvores[j], arvores[j + 1] = arvores[j + 1], arvores[j]

                swapped = True
            
        if not swapped:
            break

else:
    #gerados = [1, 2, 3... n]
    listas = sorted(listas)
    arvores = sorted(arvores)


if recorte:
    gerados = gerados[:100]
    listas = listas[:100]
    arvores = arvores[:100]


#Sets graph's styling
if not escalado:
    plt.plot(gerados, listas, label="Listas Encadeadas")
    plt.plot(gerados, arvores, label="Árvores de Busca")

    #Annotates the biggest values of each comparison
    plt.annotate(f'{listas[-1]}', xy=(max(gerados) - 5, listas[-1] - 10), color='blue')
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
    print(f"{gerados[x]} {listas[x]} {arvores[x]}")

    #Label points that have the same value on both lists
    if (listas[x] == arvores[x] and not escalado):
        plt.annotate('.', xy=(gerados[x], listas[x]), color='purple', fontsize=15)
        plt.annotate(listas[x], xy=(gerados[x] - 1.5, listas[x] + 5), color='purple', fontsize=12)

plt.title("Listas Encadeadas x Árvores de Busca Binárias")
plt.xlabel('Elementos')
plt.ylabel('Comparações')

plt.show()
