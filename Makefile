CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I include

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/csv.c $(SRC_DIR)/game.c $(SRC_DIR)/draw.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/csv.o $(OBJ_DIR)/game.o $(OBJ_DIR)/draw.o

LIB_SRCS = $(SRC_DIR)/csv.c $(SRC_DIR)/game.c $(SRC_DIR)/draw.c
LIB_OBJS = $(OBJ_DIR)/csv.o $(OBJ_DIR)/game.o $(OBJ_DIR)/draw.o

TARGET = bingo

TEST_TARGETS = test_csv test_draw test_game

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/csv.o: $(SRC_DIR)/csv.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/game.o: $(SRC_DIR)/game.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/draw.o: $(SRC_DIR)/draw.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET) data/cards_sample_1.csv

test: $(TEST_TARGETS)
	@echo "=== Running CSV Tests ==="
	./test_csv
	@echo ""
	@echo "=== Running Draw Tests ==="
	./test_draw
	@echo ""
	@echo "=== Running Game Tests ==="
	./test_game

test_csv: $(TEST_DIR)/test_csv.c $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_draw: $(TEST_DIR)/test_draw.c $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test_game: $(TEST_DIR)/test_game.c $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)
	rm -f $(TEST_TARGETS)

