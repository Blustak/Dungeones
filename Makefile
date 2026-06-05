CC = clang
BEAR = bear
CFLAGS ?= -Wall -I./src -glldb
LDFLAGS=-lm -lraylib -lGL -lpthread -ldl -lrt -lX11 -glldb
FD ?= fd
SHELL = /usr/bin/zsh

SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

TARGET ?= dungeones

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all
all: $(BIN_DIR) $(BIN_DIR)/$(TARGET)

.PHONY: build
build: $(BIN_DIR)
	$(BEAR) -- $(CC) $(CFLAGS) $(SOURCES) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)

$(BIN_DIR):
	@echo "making $(BIN_DIR)..."
	@mkdir $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@echo "linking objects..."
	$(BEAR) --append -- $(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling source..."
	$(BEAR) --append -- $(CC) $(CFLAGS) -c -o $@ $<

.PHONY:clean distclean
clean:
	@echo "deleting binaries..."
	@rm -f $(BIN_DIR)/* || return 0

distclean: clean
	@echo "removing objects..."
	@rm -f $(OBJ_DIR)/*
