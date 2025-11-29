#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/csv.h"
#include "../include/game.h"
#include "../include/draw.h"

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

static int parse_arguments(int argc, char *argv[], char **filename)
{
    if (argc != 2) {
        return -1;
    }
    
    *filename = argv[1];
    return 0;
}

static int play_game(BingoCard *cards, int num_cards)
{
    int draw_count = 0;
    int drawn_number;
    int winner_index;
    
    printf("\n🎲 Starting Bingo Game with %d card(s)!\n", num_cards);
    printf("========================================\n\n");
    
    while (has_more_draws()) {
        drawn_number = get_next_draw();
        if (drawn_number == -1) {
            break;
        }
        
        draw_count++;
        printf("Draw #%d: %d\n", draw_count, drawn_number);
        
        mark_number(cards, num_cards, drawn_number);
        
        winner_index = check_all_cards_for_bingo(cards, num_cards);
        if (winner_index >= 0) {
            printf("\n🎉 BINGO! Card %d wins after %d draws!\n", cards[winner_index].card_id, draw_count);
            print_card(&cards[winner_index]);
            return 0;
        }
    }
    
    printf("\nGame ended after %d draws.\n", draw_count);
    return 0;
}

int main(int argc, char *argv[])
{
    char *filename;
    BingoCard cards[MAX_CARDS];
    int num_cards;
    
    printf("Welcome to BingoCLI!\n");
    printf("====================\n\n");
    
    if (parse_arguments(argc, argv, &filename) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    
    num_cards = load_cards_from_csv(filename, cards, MAX_CARDS);
    if (num_cards <= 0) {
        fprintf(stderr, "Error: Failed to load cards from %s\n", filename);
        return EXIT_FAILURE;
    }
    
    printf("Loaded %d card(s) from %s\n", num_cards, filename);
    
    init_draw_sequence();
    
    play_game(cards, num_cards);
    
    return EXIT_SUCCESS;
}
