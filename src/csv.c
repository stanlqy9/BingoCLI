#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/csv.h"

#define MAX_LINE_LENGTH 256
#define CELL_MAX 32
//max characters allowed in one cell

static void trim_whitespace(char *str) {
    int i = 0;
    int j = 0;

    //i walks past spaces at the front
    while (str[i] != '\0' && isspace(str[i])) i++;
    //i points to the first non space character

    //j starts at 0 and copies from i to j
    while (str[i] != '\0') {
        str[j] = str[i];
        j++;
        i++;
    }
    //removes leading spaces by overwriting them and puts "\0' at the end

    //moves j back to last character
    str[j] = '\0';
    j--;

    while (j >= 0 && isspace(str[j])) {
        str[j] = '\0';
        j--;
    }
    //goes backward while the character is whitespace and replaces with \0
}

//hard codes 'FREE'
static bool is_free_space(const char *str) {
    if ((str[0] == 'F' || str[0] == 'f') &&
        (str[1] == 'R' || str[1] == 'r') &&
        (str[2] == 'E' || str[2] == 'e') &&
        (str[3] == 'E' || str[3] == 'e') &&
        str[4] == '\0') {
        return true;
    }
    return false;
}

//convert a cell string to a number
static int parse_cell_value(const char *str, int *value) {
    int i = 0;
    int num = 0;

    //-1 if FREE
    //an integer between 1-75
    // error -1 if invalid
    if (is_free_space(str)) {
        *value = -1;
        return 0;
    }

    //if string is empty then error
    if (str[0] == '\0') return -1;

    //loops through each character
    while (str[i] != '\0') {
        if (!isdigit(str[i])) return -1;
        num = num * 10 + (str[i] - '0');
        i++;
    }

    //check range or else error
    if (num < 1 || num > 75) return -1;

    //num goes into *value if success
    *value = num;
    return 0;
}

static int read_cell(FILE *fp, char *buffer, int max_len, int *end_of_row) {
    int c;
    int i = 0;
    *end_of_row = 0;

    //set to 1 if hit end of line
    //reads first none space char
    c = fgetc(fp);
    while (c == ' ' || c == '\t') c = fgetc(fp);

    //error if EOF is hit
    if (c == EOF) return -1;

    // read characters until ',', '\n', or 'EOF'
    while (c != ',' && c != '\n' && c != EOF) {
        if (i < max_len - 1) {
            buffer[i] = (char)c;
            i++;
        }
        c = fgetc(fp);
    }

    //marked 1 if stopped because of newline
    if (c == '\n') *end_of_row = 1;

    //null terminate the string
    buffer[i] = '\0';

    //will be error if nothing is read
    if (i == 0) return -1;

    return 0;
}

//read and ignore header ror
static int skip_header_line(FILE *fp) {
    char cell[CELL_MAX];
    int end_row;
    int col;

    //loop which reads each cell into cell
    for (col = 0; col < CARD_SIZE; col++) {
        if (read_cell(fp, cell, CELL_MAX, &end_row) != 0) return -1;
        if (col < CARD_SIZE - 1 && end_row) return -1;
    }
    return 0;
}

//skip blank lines
static void skip_empty_lines(FILE *fp) {
    //when something that is not newline gets hit, its pushed back into the stream
    int c = fgetc(fp);
    while (c == '\n' || c == '\r') c = fgetc(fp);
    if (c != EOF) ungetc(c, fp);
}

static int load_single_card(FILE *fp, BingoCard *card, int card_id) {
    int c;
    int r;
    int col;
    int value;
    int end;
    char cell[CELL_MAX];

    //reads until # at the start of a line
    //skips if it doesnt start with #
    //return -1 if no more cards or hits EOF
    c = fgetc(fp);
    if (c == EOF) return -1;

    while (c != '#' && c != EOF) {
        while (c != '\n' && c != EOF) c = fgetc(fp);
        if (c == EOF) return -1;
        c = fgetc(fp);
    }

    //discard # CARD N line until newline
    if (c == EOF) return -1;
    while (c != '\n' && c != EOF) c = fgetc(fp);

    if (skip_header_line(fp) != 0) return -1;
    //skip header line

    //sets ID and initializes all cells to 0
    (*card).card_id = card_id;

    for (r = 0; r < CARD_SIZE; r++) {
        for (col = 0; col < CARD_SIZE; col++) {
            (*card).grid[r][col].number = 0;
            (*card).grid[r][col].marked = false;
        }
    }

    //read a cell string into cell
    //trim whitespcae
    //parse it as number or FREE
    //error if end_of_row it gotten too early
    for (r = 0; r < CARD_SIZE; r++) {
        for (col = 0; col < CARD_SIZE; col++) {
            if (read_cell(fp, cell, CELL_MAX, &end) != 0) return -1;

            trim_whitespace(cell);
            if (parse_cell_value(cell, &value) != 0) return -1;

            (*card).grid[r][col].number = value;
            (*card).grid[r][col].marked = (value == -1);

            if (col < CARD_SIZE - 1 && end) return -1;
        }
    }

    //force center as FREE space
    (*card).grid[2][2].number = -1;
    (*card).grid[2][2].marked = true;
    //overwrite center even if something else is there

    return 0;
}

int load_cards_from_csv(const char *filename, BingoCard *cards, int max_cards) {
    //open file. return -1 if failed
    FILE *fp = fopen(filename, "r");
    int count = 0;
    int r;

    if (fp == NULL) return -1;

    skip_empty_lines(fp);

    //loop while theres room in array
    while (count < max_cards) {
        r = load_single_card(fp, &cards[count], count + 1);
        if (r != 0) break;
        count++;
        skip_empty_lines(fp);
    }

    //close file
    fclose(fp);

    //return -1 if no cards are loaded
    if (count == 0) return -1;

    //return number of cards loaded
    return count;
}
