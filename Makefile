CC = gcc
CFLAGS = -Wall -Werror
# CFLAGS_ARG should be passed via the command-line
LDFLAGS = -lm

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = tangler

ifeq ($(OS),Windows_NT)
	CLEAN_CMD = powershell -noprofile rm -force -ErrorAction SilentlyContinue
else
	CLEAN_CMD = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_ARG) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CFLAGS_ARG) -c -o $@ $< $(LDFLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	$(CLEAN_CMD) $(OBJ_DIR)/*
	$(CLEAN_CMD) $(TARGET)
