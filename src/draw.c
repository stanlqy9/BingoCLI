#include <stdlib.h>
#include <time.h>
#include "../include/draw.h"
#include "../include/types.h"

/* Static state for the draw sequence */
static int draw_pool[BINGO_MAX];        // Array of numbers 1-75
static int draw_index = 0;               // Current position in draw_pool
static bool initialized = false;         // Whether the draw system is ready

/**
 * shuffle_array - Shuffle an array
 * @array: Array to shuffle
 * @size: Number of elements in the array
 *
 * Uses the random number generator to shuffle the array in place.
 */
static void shuffle_array(int *array, int size)
{
    /* TODO: Implement shuffle algorithm */
}

/**
 * init_draw_sequence - Initialize the draw system
 *
 * Sets up the draw pool with numbers 1-75 and shuffles them.
 */
void init_draw_sequence(void)
{
    /* TODO: Populate draw_pool with 1-75, shuffle, initialize state */
}

/**
 * get_next_draw - Get the next number in the draw sequence
 *
 * Returns the next number from the shuffled draw pool.
 * Numbers are returned in the order they were shuffled.
 *
 * Return: Next number (1-75), or -1 if no more draws available
 */
int get_next_draw(void)
{
    /* TODO: Return next number from draw_pool and advance index */
}

/**
 * has_more_draws - Check if there are more numbers to draw
 *
 * Return: true if more draws are available, false otherwise
 */
bool has_more_draws(void)
{
    /* TODO: Check if there are more numbers to draw */
}

/**
 * get_draw_count - Get the number of draws that have been made
 *
 * Return: Number of draws made so far
 */
int get_draw_count(void)
{
    /* TODO: Return how many draws have been made */
}

