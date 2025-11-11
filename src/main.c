#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/csv.h"
#include "../include/game.h"
#include "../include/draw.h"

/**
 * print_usage - Display usage information
 * @program_name: Name of the program executable
 *
 * Prints command-line usage help to stderr.
 */
static void print_usage(const char *program_name)
{
    fprintf(stderr, "Usage: %s <csv_file>\n", program_name);
    fprintf(stderr, "\n");
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  csv_file    Path to CSV file containing Bingo cards\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Example:\n");
    fprintf(stderr, "  %s data/cards_sample_1.csv\n", program_name);
}

/**
 * parse_arguments - Parse and validate command line arguments
 * @argc: Argument count
 * @argv: Argument vector
 * @filename: Pointer to store the CSV filename
 *
 * Parses command line arguments and validates them.
 *
 * Return: 0 on success, -1 on error
 */
static int parse_arguments(int argc, char *argv[], char **filename)
{
    /* TODO: Validate argc and extract filename from argv */
}

/**
 * play_game - Run the main game loop
 * @cards: Array of loaded Bingo cards
 * @num_cards: Number of cards in the array
 *
 * Runs the game loop: draws numbers, marks cards, checks for winners.
 * Continues until a Bingo is detected or all numbers are drawn.
 *
 * Return: 0 on success, -1 on error
 */
static int play_game(BingoCard *cards, int num_cards)
{
    int draw_count = 0;
    int drawn_number;
    int winner_index;
    
    printf("\n🎲 Starting Bingo Game with %d card(s)!\n", num_cards);
    printf("========================================\n\n");
    
    /* TODO: Loop drawing numbers, marking cards, checking for winner */
    
    while (has_more_draws()) {
        drawn_number = get_next_draw();
        if (drawn_number == -1) {
            break;
        }
        
        draw_count++;
        printf("Draw #%d: %d\n", draw_count, drawn_number);
        
        /* Mark number on all cards */
        
        /* Check for winner */
        
    }
    
    printf("\nGame ended after %d draws.\n", draw_count);
    return 0;
}

/**
 * main - Entry point for BingoCLI
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Main program flow:
 * 1. Parse command line arguments
 * 2. Load Bingo cards from CSV file
 * 3. Initialize draw sequence
 * 4. Run game loop until winner or all draws exhausted
 * 5. Display results
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[])
{
    char *filename;
    BingoCard cards[MAX_CARDS];
    int num_cards;
    
    /* TODO: Parse args, load cards, initialize draws, play game */
    
    printf("Welcome to BingoCLI!\n");
    printf("====================\n\n");
    
    /* Parse arguments */
    if (parse_arguments(argc, argv, &filename) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Load cards */
    
    /* Initialize draws */
    
    /* Play game */
    
    return EXIT_SUCCESS;
}

