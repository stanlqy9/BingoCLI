#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/types.h"

/**
 * test_init_card - Test card initialization
 *
 * Return: 1 on success, 0 on failure
 */
static int test_init_card(void)
{
    BingoCard card;
    init_card(&card, 42);
    
    if (card.card_id != 42) {
        printf("FAIL: Expected card_id 42, got %d\n", card.card_id);
        return 0;
    }
    
    if (card.grid[2][2].number != -1) {
        printf("FAIL: Center should be FREE (-1), got %d\n", card.grid[2][2].number);
        return 0;
    }
    
    if (!card.grid[2][2].marked) {
        printf("FAIL: FREE space should be marked\n");
        return 0;
    }
    
    for (int r = 0; r < CARD_SIZE; r++) {
        for (int c = 0; c < CARD_SIZE; c++) {
            if (r == 2 && c == 2) continue;
            if (card.grid[r][c].marked) {
                printf("FAIL: Cell [%d][%d] should not be marked\n", r, c);
                return 0;
            }
        }
    }
    
    printf("PASS: Card initialization correct\n");
    return 1;
}

/**
 * test_mark_number - Test marking numbers on cards
 *
 * Return: 1 on success, 0 on failure
 */
static int test_mark_number(void)
{
    BingoCard card;
    init_card(&card, 1);
    
    card.grid[0][0].number = 5;
    card.grid[1][1].number = 5;
    card.grid[3][4].number = 10;
    
    mark_number(&card, 1, 5);
    
    if (!card.grid[0][0].marked) {
        printf("FAIL: Cell [0][0] should be marked\n");
        return 0;
    }
    
    if (!card.grid[1][1].marked) {
        printf("FAIL: Cell [1][1] should be marked\n");
        return 0;
    }
    
    if (card.grid[3][4].marked) {
        printf("FAIL: Cell [3][4] should NOT be marked (has 10, not 5)\n");
        return 0;
    }
    
    printf("PASS: mark_number works correctly\n");
    return 1;
}

/**
 * test_check_bingo_row - Test row detection
 *
 * Return: 1 on success, 0 on failure
 */
static int test_check_bingo_row(void)
{
    BingoCard card;
    init_card(&card, 1);
    
    for (int c = 0; c < CARD_SIZE; c++) {
        card.grid[0][c].marked = true;
    }
    
    if (!check_bingo(&card)) {
        printf("FAIL: Should detect row bingo\n");
        return 0;
    }
    
    printf("PASS: Row bingo detection works\n");
    return 1;
}

/**
 * test_check_bingo_column - Test column detection
 *
 * Return: 1 on success, 0 on failure
 */
static int test_check_bingo_column(void)
{
    BingoCard card;
    init_card(&card, 1);
    
    for (int r = 0; r < CARD_SIZE; r++) {
        card.grid[r][0].marked = true;
    }
    
    if (!check_bingo(&card)) {
        printf("FAIL: Should detect column bingo\n");
        return 0;
    }
    
    printf("PASS: Column bingo detection works\n");
    return 1;
}

/**
 * test_check_bingo_diagonal - Test diagonal detection
 *
 * Return: 1 on success, 0 on failure
 */
static int test_check_bingo_diagonal(void)
{
    BingoCard card;
    init_card(&card, 1);
    
    for (int i = 0; i < CARD_SIZE; i++) {
        card.grid[i][i].marked = true;
    }
    
    if (!check_bingo(&card)) {
        printf("FAIL: Should detect main diagonal bingo\n");
        return 0;
    }
    
    init_card(&card, 2);
    
    for (int i = 0; i < CARD_SIZE; i++) {
        card.grid[i][CARD_SIZE - 1 - i].marked = true;
    }
    
    if (!check_bingo(&card)) {
        printf("FAIL: Should detect anti-diagonal bingo\n");
        return 0;
    }
    
    printf("PASS: Diagonal bingo detection works\n");
    return 1;
}

/**
 * test_check_bingo_no_win - Test no false positives
 *
 * Return: 1 on success, 0 on failure
 */
static int test_check_bingo_no_win(void)
{
    BingoCard card;
    init_card(&card, 1);
    
    card.grid[0][0].marked = true;
    card.grid[0][1].marked = true;
    card.grid[1][0].marked = true;
    card.grid[4][4].marked = true;
    
    if (check_bingo(&card)) {
        printf("FAIL: Should NOT detect bingo with scattered marks\n");
        return 0;
    }
    
    printf("PASS: No false positive bingo detection\n");
    return 1;
}

/**
 * test_check_all_cards - Test checking multiple cards
 *
 * Return: 1 on success, 0 on failure
 */
static int test_check_all_cards(void)
{
    BingoCard cards[3];
    
    for (int i = 0; i < 3; i++) {
        init_card(&cards[i], i + 1);
    }
    
    int result = check_all_cards_for_bingo(cards, 3);
    if (result != -1) {
        printf("FAIL: Expected -1 when no winner, got %d\n", result);
        return 0;
    }
    
    for (int c = 0; c < CARD_SIZE; c++) {
        cards[1].grid[2][c].marked = true;
    }
    
    result = check_all_cards_for_bingo(cards, 3);
    if (result != 1) {
        printf("FAIL: Expected winner index 1, got %d\n", result);
        return 0;
    }
    
    printf("PASS: check_all_cards_for_bingo works correctly\n");
    return 1;
}

/**
 * test_print_card - Test card printing
 *
 * Return: 1 on success, 0 on failure
 */
static int test_print_card(void)
{
    BingoCard card;
    init_card(&card, 99);
    
    for (int r = 0; r < CARD_SIZE; r++) {
        for (int c = 0; c < CARD_SIZE; c++) {
            card.grid[r][c].number = r * CARD_SIZE + c + 1;
        }
    }
    card.grid[2][2].number = -1;
    
    printf("Testing print_card output:\n");
    print_card(&card);
    
    printf("PASS: print_card executed without crash\n");
    return 1;
}

/**
 * main - Run all game module tests
 *
 * Return: EXIT_SUCCESS if all tests pass, EXIT_FAILURE otherwise
 */
int main(void)
{
    int passed = 0;
    int total = 8;
    
    printf("=== Game Module Tests ===\n\n");
    
    passed += test_init_card();
    passed += test_mark_number();
    passed += test_check_bingo_row();
    passed += test_check_bingo_column();
    passed += test_check_bingo_diagonal();
    passed += test_check_bingo_no_win();
    passed += test_check_all_cards();
    passed += test_print_card();
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    return (passed == total) ? EXIT_SUCCESS : EXIT_FAILURE;
}
