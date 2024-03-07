# Makefile para automatizar a compilação do projeto

# Nome do executável gerado
TARGET = huffman

# Diretórios de origem
CORE_DIR = ./core
SRC_DIR = $(CORE_DIR)/modules
BUILD_DIR = ./build

# Obter todos os arquivos .c em SRC_DIR
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(CORE_DIR)/*.c)

# Gere os nomes dos arquivos de objeto com base nos arquivos fonte
OBJS := $(SRCS:$(CORE_DIR)/%.c=$(BUILD_DIR)/%.o)

# Opções de compilação
CC = gcc
CFLAGS = -Wall -I$(CORE_DIR)

# Comando para criar o diretório de build, se não existir
MKDIR_P = mkdir -p

# Alvo padrão
all: $(BUILD_DIR) $(TARGET)

# Compilação do executável
$(TARGET): $(OBJS)
	$(CC) $^ -o $@

# Compilação dos arquivos de objeto
$(BUILD_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Comando para criar o diretório de build
$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

# Limpar arquivos de compilação e o executável
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Define "clean" como um alvo phony, ou seja, não corresponde a um arquivo real
.PHONY: clean
