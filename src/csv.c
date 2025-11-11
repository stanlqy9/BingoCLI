#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/csv.h"

#define MAX_LINE_LENGTH 256

/**
 * trim_whitespace - Remove leading and trailing whitespace from a string
 * @str: The string to trim (modified in place)
 *
 * Helper function to clean up CSV field values.
 */
static void trim_whitespace(char *str)
{
    /* TODO: Remove leading and trailing whitespace from string */
}

/**
 * is_free_space - Check if a string represents a FREE space
 * @str: The string to check
 *
 * Return: true if the string is "FREE" (case-insensitive), false otherwise
 */
static bool is_free_space(const char *str)
{
    /* TODO: Check if string is "FREE" (case-insensitive) */
}

/**
 * parse_cell_value - Parse a single CSV cell value into a number
 * @str: The string to parse
 * @value: Pointer to store the parsed integer value
 *
 * Handles both numeric values and the special "FREE" space.
 * FREE space should be represented as -1.
 *
 * Return: 0 on success, -1 on error
 */
static int parse_cell_value(const char *str, int *value)
{
    /* TODO: Parse string as number or FREE (-1), validate range, return status */
}

/**
 * parse_card_row - Parse a single row of a Bingo card
 * @line: CSV line containing comma-separated values
 * @card: Pointer to the BingoCard being built
 * @row: Row index (0-4)
 *
 * Parses a CSV line and populates one row of the card grid.
 * Expected format: "num,num,num,num,num" or "num,num,FREE,num,num"
 *
 * Return: 0 on success, -1 on error
 */
static int parse_card_row(char *line, BingoCard *card, int row)
{
    /* TODO: Split line by commas, parse 5 values, populate card grid row */
}

/**
 * skip_header_line - Skip a header line (B,I,N,G,O)
 * @fp: File pointer
 *
 * Reads and discards the B,I,N,G,O header line.
 *
 * Return: 0 on success, -1 on error
 */
static int skip_header_line(FILE *fp)
{    
    /* TODO: Read and discard the B,I,N,G,O header line */
}

/**
 * skip_empty_lines - Skip blank lines and comments
 * @fp: File pointer
 *
 * Advances the file pointer past empty lines and comment lines (starting with #).
 * Leaves the file positioned at the next meaningful line.
 */
static void skip_empty_lines(FILE *fp)
{
    /* TODO: Advance file pointer past blank lines and comments */
}

/**
 * load_single_card - Load one complete Bingo card from file
 * @fp: File pointer positioned at start of card
 * @card: Pointer to BingoCard structure to populate
 * @card_id: ID number for this card
 *
 * Reads a complete card including header and 5 data rows.
 * Expected format:
 *   # CARD N 
 *   B,I,N,G,O
 *   row1...
 *   row2...
 *   row3...
 *   row4...
 *   row5...
 *
 * Return: 0 on success, -1 on error or EOF
 */
static int load_single_card(FILE *fp, BingoCard *card, int card_id)
{
    /* TODO: Read header and 5 rows from file, populate card structure */
}

/**
 * load_cards_from_csv - Load all Bingo cards from a CSV file
 * @filename: Path to the CSV file
 * @cards: Array to store loaded BingoCard structures
 * @max_cards: Maximum number of cards the array can hold
 *
 * Loads all cards from the specified CSV file. The file format should be:
 *   # CARD 1
 *   B,I,N,G,O
 *   (5 rows of numbers)
 *   
 *   # CARD 2
 *   B,I,N,G,O
 *   (5 rows of numbers)
 *   ...
 *
 * Return: Number of cards successfully loaded, or -1 on error
 */
int load_cards_from_csv(const char *filename, BingoCard *cards, int max_cards)
{
    /* TODO: Open file, loop to load all cards, handle errors, return count */
}

