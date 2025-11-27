#include <stdio.h>
#include <stdlib.h>
#include "../include/draw.h"
#include "../include/types.h"

/**
 * test_init_draw_sequence - Test draw initialization
 *
 * Return: 1 on success, 0 on failure
 */
static int test_init_draw_sequence(void)
{
    init_draw_sequence();
    
    if (!has_more_draws()) {
        printf("FAIL: Should have draws available after init\n");
        return 0;
    }
    
    printf("PASS: Draw sequence initialized\n");
    return 1;
}

/**
 * test_get_next_draw - Test drawing numbers
 *
 * Return: 1 on success, 0 on failure
 */
static int test_get_next_draw(void)
{
    init_draw_sequence();
    
    int num = get_next_draw();
    
    if (num < BINGO_MIN || num > BINGO_MAX) {
        printf("FAIL: Draw %d is out of range [%d, %d]\n", num, BINGO_MIN, BINGO_MAX);
        return 0;
    }
    
    printf("PASS: get_next_draw returns valid number (%d)\n", num);
    return 1;
}

/**
 * test_unique_draws - Test that all draws are unique
 *
 * Return: 1 on success, 0 on failure
 */
static int test_unique_draws(void)
{
    init_draw_sequence();
    
    int seen[BINGO_MAX + 1] = {0};
    
    for (int i = 0; i < BINGO_MAX; i++) {
        int num = get_next_draw();
        
        if (num == -1) {
            printf("FAIL: Got -1 before drawing all %d numbers (at draw %d)\n", BINGO_MAX, i);
            return 0;
        }
        
        if (num < BINGO_MIN || num > BINGO_MAX) {
            printf("FAIL: Draw %d is out of range\n", num);
            return 0;
        }
        
        if (seen[num]) {
            printf("FAIL: Number %d was drawn twice\n", num);
            return 0;
        }
        
        seen[num] = 1;
    }
    
    printf("PASS: All %d draws are unique\n", BINGO_MAX);
    return 1;
}

/**
 * test_has_more_draws - Test draw availability checking
 *
 * Return: 1 on success, 0 on failure
 */
static int test_has_more_draws(void)
{
    init_draw_sequence();
    
    if (!has_more_draws()) {
        printf("FAIL: Should have draws after init\n");
        return 0;
    }
    
    get_next_draw();
    
    if (!has_more_draws()) {
        printf("FAIL: Should still have draws after one draw\n");
        return 0;
    }
    
    printf("PASS: has_more_draws works correctly\n");
    return 1;
}

/**
 * test_exhausted_draws - Test behavior when draws are exhausted
 *
 * Return: 1 on success, 0 on failure
 */
static int test_exhausted_draws(void)
{
    init_draw_sequence();
    
    for (int i = 0; i < BINGO_MAX; i++) {
        get_next_draw();
    }
    
    if (has_more_draws()) {
        printf("FAIL: Should have no more draws after %d draws\n", BINGO_MAX);
        return 0;
    }
    
    int extra = get_next_draw();
    if (extra != -1) {
        printf("FAIL: Expected -1 when exhausted, got %d\n", extra);
        return 0;
    }
    
    printf("PASS: Exhausted draws handled correctly\n");
    return 1;
}

/**
 * test_draw_count - Test draw counting
 *
 * Return: 1 on success, 0 on failure
 */
static int test_draw_count(void)
{
    init_draw_sequence();
    
    int initial_count = get_draw_count();
    
    get_next_draw();
    get_next_draw();
    get_next_draw();
    
    int new_count = get_draw_count();
    
    if (new_count != initial_count + 3) {
        printf("FAIL: Expected count %d, got %d\n", initial_count + 3, new_count);
        return 0;
    }
    
    printf("PASS: Draw count tracks correctly\n");
    return 1;
}

/**
 * main - Run all draw module tests
 *
 * Return: EXIT_SUCCESS if all tests pass, EXIT_FAILURE otherwise
 */
int main(void)
{
    int passed = 0;
    int total = 6;
    
    printf("=== Draw Module Tests ===\n\n");
    
    passed += test_init_draw_sequence();
    passed += test_get_next_draw();
    passed += test_unique_draws();
    passed += test_has_more_draws();
    passed += test_exhausted_draws();
    passed += test_draw_count();
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    return (passed == total) ? EXIT_SUCCESS : EXIT_FAILURE;
}
