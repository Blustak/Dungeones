CC ?= 'clang'
CFLAGS ?= -Wall -I.
FD ?= fd
SHELL = /usr/bin/zsh

SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

TARGET ?= dungeones

SOURCES := $(shell fd -tf -ec . $(SRC_DIR))
FLAT_SOURCES := $(foreach srcFile, $(SOURCES), $(notdir $(srcFile)))
OBJECTS := $(addprefix $(OBJ_DIR)/,$(patsubst %.c, %.o, $(FLAT_SOURCES)))

.PHONY: all
all: $(BIN_DIR) $(BIN_DIR)/$(TARGET)

$(BIN_DIR):
	@echo "making $(BIN_DIR)..."
	@mkdir $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
