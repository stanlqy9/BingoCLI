#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

/* Constants */
#define CARD_SIZE 5
#define MAX_CARDS 100
#define BINGO_MIN 1
#define BINGO_MAX 75

/* Represents a single cell on a Bingo card */
typedef struct {
    int number;      // The number on this cell (or -1 for FREE space)
    bool marked;     // Whether this cell has been marked
} Cell;

/* Represents a single Bingo card */
typedef struct {
    Cell grid[CARD_SIZE][CARD_SIZE];  // 5x5 grid of cells
    int card_id;                       // Unique identifier for this card
} BingoCard;

#endif 

