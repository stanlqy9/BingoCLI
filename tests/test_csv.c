#include <stdio.h>
#include <stdlib.h>
#include "../include/csv.h"
#include "../include/types.h"

/**
 * test_load_valid_file - Test loading a valid CSV file
 *
 * Return: 1 on success, 0 on failure
 */
static int test_load_valid_file(void)
{
    BingoCard cards[MAX_CARDS];
    int num_cards = load_cards_from_csv("data/cards_sample_1.csv", cards, MAX_CARDS);
    
    if (num_cards <= 0) {
        printf("FAIL: Expected positive number of cards, got %d\n", num_cards);
        return 0;
    }
    
    printf("PASS: Loaded %d cards from valid file\n", num_cards);
    return 1;
}

/**
 * test_load_invalid_file - Test loading an invalid file
 *
 * Return: 1 on success, 0 on failure
 */
static int test_load_invalid_file(void)
{
    BingoCard cards[MAX_CARDS];
    int num_cards = load_cards_from_csv("nonexistent_file.csv", cards, MAX_CARDS);
    
    if (num_cards != -1) {
        printf("FAIL: Expected -1 for invalid file, got %d\n", num_cards);
        return 0;
    }
    
    printf("PASS: Correctly returned -1 for invalid file\n");
    return 1;
}

/**
 * test_card_structure - Test card structure validation
 *
 * Return: 1 on success, 0 on failure
 */
static int test_card_structure(void)
{
    BingoCard cards[MAX_CARDS];
    int num_cards = load_cards_from_csv("data/cards_sample_1.csv", cards, MAX_CARDS);
    
    if (num_cards <= 0) {
        printf("FAIL: Could not load cards for structure test\n");
        return 0;
    }
    
    for (int i = 0; i < num_cards; i++) {
        if (cards[i].card_id != i + 1) {
            printf("FAIL: Card %d has wrong ID %d\n", i, cards[i].card_id);
            return 0;
        }
    }
    
    printf("PASS: Card structure is valid\n");
    return 1;
}

/**
 * test_free_space - Test FREE space handling
 *
 * Return: 1 on success, 0 on failure
 */
static int test_free_space(void)
{
    BingoCard cards[MAX_CARDS];
    int num_cards = load_cards_from_csv("data/cards_sample_1.csv", cards, MAX_CARDS);
    
    if (num_cards <= 0) {
        printf("FAIL: Could not load cards for FREE space test\n");
        return 0;
    }
    
    for (int i = 0; i < num_cards; i++) {
        if (cards[i].grid[2][2].number != -1) {
            printf("FAIL: Card %d center cell should be -1 (FREE), got %d\n", 
                   i, cards[i].grid[2][2].number);
            return 0;
        }
        if (!cards[i].grid[2][2].marked) {
            printf("FAIL: Card %d FREE space should be marked\n", i);
            return 0;
        }
    }
    
    printf("PASS: FREE space handling correct\n");
    return 1;
}

/**
 * test_card_values - Test card value parsing
 *
 * Return: 1 on success, 0 on failure
 */
static int test_card_values(void)
{
    BingoCard cards[MAX_CARDS];
    int num_cards = load_cards_from_csv("data/cards_sample_1.csv", cards, MAX_CARDS);
    
    if (num_cards <= 0) {
        printf("FAIL: Could not load cards for value test\n");
        return 0;
    }
    
    for (int i = 0; i < num_cards; i++) {
        for (int r = 0; r < CARD_SIZE; r++) {
            for (int c = 0; c < CARD_SIZE; c++) {
                int val = cards[i].grid[r][c].number;
                
                if (val != -1 && (val < BINGO_MIN || val > BINGO_MAX)) {
                    printf("FAIL: Card %d value %d at [%d][%d] out of range\n", 
                           i, val, r, c);
                    return 0;
                }
                
                if (r == 2 && c == 2 && val != -1) {
                    printf("FAIL: Card %d center should be FREE (-1), got %d\n", i, val);
                    return 0;
                }
            }
        }
    }
    
    printf("PASS: Card values parsed correctly\n");
    return 1;
}

/**
 * main - Run all CSV module tests
 *
 * Return: EXIT_SUCCESS if all tests pass, EXIT_FAILURE otherwise
 */
int main(void)
{
    int passed = 0;
    int total = 5;
    
    printf("=== CSV Module Tests ===\n\n");
    
    passed += test_load_valid_file();
    passed += test_load_invalid_file();
    passed += test_card_structure();
    passed += test_free_space();
    passed += test_card_values();
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    return (passed == total) ? EXIT_SUCCESS : EXIT_FAILURE;
}
