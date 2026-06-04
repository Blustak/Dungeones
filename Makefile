CC = bear -- clang
CFLAGS ?= -Wall -I./src -g
LDFLAGS=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11 -g
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

.PHONY: build
build: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)

.PHONY: compile
compile: $(BIN_DIR)/$(TARGET)

$(BIN_DIR):
	@echo "making $(BIN_DIR)..."
	@mkdir $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@echo "linking objects..."
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling source..."
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:clean distclean
clean:
	@echo "deleting binaries..."
	@rm -f $(BIN_DIR)/*

distclean: clean
	@echo "removing objects..."
	@rm -f $(OBJ_DIR)/*
