#include <stdio.h>
#include <stdbool.h>
#include "../include/game.h"

/**
 * init_card - Initialize a Bingo card with default values
 * @card: Pointer to the BingoCard to initialize
 * @card_id: Unique identifier for this card
 *
 * Sets all cells to unmarked and initializes the card ID.
 * The center cell (2,2) should be marked as FREE (-1) and pre-marked.
 */
void init_card(BingoCard *card, int card_id)
{
    //initializes all cells of cards unmarked
    (*card).card_id = card_id;
    
    for(int r =0; r < CARD_SIZE; r++)
        {
            for( int c =0; c < CARD_SIZE;c++)
                {
                    (*card).grid[r][c].number = 0;
                    (*card).grid[r][c].marked = false;
                }
        }
//free space
    (*card).grid[2][2].number =-1;
    (*card).grid[2][2].marked = true;
    
    /* TODO: Initialize card with ID, set all cells unmarked, mark center FREE space */
}

/**
 * mark_number - Mark a drawn number on all cards that contain it
 * @cards: Array of BingoCard structures
 * @num_cards: Number of cards in the array
 * @drawn_number: The number that was just drawn
 *
 * Searches all cards for the drawn number and marks it if found.
 * The FREE space should already be marked during initialization.
 */
void mark_number(BingoCard *cards, int num_cards, int drawn_number)
{
    for(int i =0; i < num_cards; i++){
            for(int r = 0; r< CARD_SIZE; r++)
                {
                for(int c=0; c<CARD_SIZE; c++)
                    {
                        if(cards[i].grid[r][c].number == drawn_number){
                            cards[i].grid[r][c].marked = true;
                        }
                    }
                }
    }
    /* TODO: Search all cards for drawn_number and mark it if found */
}

/**
 * check_row - Check if a specific row has Bingo
 * @card: Pointer to the BingoCard to check
 * @row: Row index (0-4)
 *
 * Return: true if all cells in the row are marked, false otherwise
 */
static bool check_row(const BingoCard *card, int row)
{
    for (int c = 0; c < CARD_SIZE; c++){
        if(!(*card).grid[row][c].marked)
            return false;
    }
    return true;
    /* TODO: Check if all cells in the specified row are marked */
}

/**
 * check_column - Check if a specific column has Bingo
 * @card: Pointer to the BingoCard to check
 * @col: Column index (0-4)
 *
 * Return: true if all cells in the column are marked, false otherwise
 */
static bool check_column(const BingoCard *card, int col)
{
    for(int r = 0; r< CARD_SIZE; r++)
        {
            if(!(*card).grid[r][col].marked)
            {
                return false;
            }
            return true;
    /* TODO: Check if all cells in the specified column are marked */
}

/**
 * check_diagonal - Check if either diagonal has Bingo
 * @card: Pointer to the BingoCard to check
 *
 * Return: true if either diagonal is fully marked, false otherwise
 */
static bool check_diagonal(const BingoCard *card)
{
    bool leftSide = true;
    bool rightSide = true;
    for(int i = 0; i < CARD_SIZE; i++){
        if(!(*card).grid[i][i].marked)
        {
            leftSide = false;
        }
        if(!(*card).grid[i][CARD_SIZE -1 -i].marked)
        {
            rightSide = false;
        }
    }

        return leftSide || rightSide;
    /* TODO: Check both diagonals for complete marking */
}

/**
 * check_bingo - Check if a card has achieved Bingo
 * @card: Pointer to the BingoCard to check
 *
 * Checks all possible winning conditions: rows, columns, and diagonals.
 *
 * Return: true if Bingo is detected, false otherwise
 */
bool check_bingo(const BingoCard *card)
{
    for(int r =0; r< CARD_SIZE;r++)
        {
            if(check_row(card,r))
                return true;
        }
    for(int c = 0; c < CARD_SIZEl c++)
        {
        if(check_column(card, c))
            return true;
        }
    if(check_diagonal(card))
    {
        return true;
    }

    return false;
    
    /* TODO: Check all rows, columns, and diagonals for a win */
}

/**
 * check_all_cards_for_bingo - Check all cards for a Bingo winner
 * @cards: Array of BingoCard structures
 * @num_cards: Number of cards in the array
 *
 * Return: Index of the first winning card, or -1 if no winner
 */
int check_all_cards_for_bingo(const BingoCard *cards, int num_cards)
{
    /* TODO: Check all cards and return index of first winner, or -1 */
}

/**
 * print_card - Display a Bingo card to stdout
 * @card: Pointer to the BingoCard to display
 *
 * Prints the card in a readable format with marked cells indicated.
 * Useful for debugging and showing game state.
 */
void print_card(const BingoCard *card)
{
    /* TODO: Print card in readable format showing numbers and marked cells */
    printf("Card %d:\n", (*card).card_id);
    printf("  B   I   N   G   O\n");
    printf("-------------------\n");
    
    /* Print grid here */
}

