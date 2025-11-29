#include <stdlib.h>
#include <time.h>
#include "../include/draw.h"
#include "../include/types.h"

/* Static state for the draw sequence */
static int draw_pool[BINGO_MAX]; // Array of numbers 1-75
static int draw_index = 0;       // Current position in draw_pool
static bool initialized = false; // Whether the draw system is ready

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
    // Fisher yates shuffle

    // start from last element and move backwards towards index 0
    for (int i = size - 1; i > 0; i--)
    {

        // picking a random index(j) from 0 to i
        int j = rand() % (i + 1);

        // swap array[i] with array[j]
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    /*
    - Each iteration ensure that the element positon of i
    is swapped with a random element from the unshuffled
    portions of the array (0 to j), gets a uniformaly random
    value.
    - Ensuring every element has a equal chance of ending up
    in any position, producing a uniform shuffle.
    */
}

/**
 * init_draw_sequence - Initialize the draw system
 *
 * Sets up the draw pool with numbers 1-75 and shuffles them.
 */
void init_draw_sequence(void)

{
    /* TODO: Populate draw_pool with 1-75, shuffle, initialize state */

    // if initalization has already happened once, do nothing.
    if (initialized)
    {
        return;
    }

    // seed RNG using the current time
    // making sure each program run produces a random sequence.
    srand(time(NULL));

    // fill the draw_pool array with numbers 1 to 75
    // represent all possible BINGO draw before shuffling

    for (int i = 0; i < BINGO_MAX; i++)
    {
        draw_pool[i] = i + 1;
    }

    // shuffle for random order in draw_pool.
    shuffle_array(draw_pool, BINGO_MAX);

    // index reset, drawing will start the first shuffled number.
    draw_index = 0;

    // making sequence as fully inialized so the function does not run again.

    initialized = true;

    /*
    - init_draw_seqeunce - Initalize the draw system.
    - fills the draw pool with numbers from 1 to 75, shuffles them and 
    then resets the index.
    -runs only one per program excecution in order to avoid,
    rerandomizing an already initalozed sequence.
    */
}

void reset_draw_sequence(void)
{
    initialized = false;
    draw_index = 0;
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
    
    // if initalization has already happened once, do nothing.

    if(!initialized)
    {
        return -1;
    }

    //if all the BINGO_MAX numbers have been drawn, nothing left to return
    if(draw_index >= BINGO_MAX)
    {
        return -1;
    }
    
    //get the next number from the shuffle pool
    int next = draw_pool[draw_index];

    //index is moved forward for the next draw.
    draw_index++;

    //selected number is returned.
    return next;

    /*
    - get_next_draw - return the next number in the shuffled draw seqeuence.
    - Returns -1 of the system is not initalized or if all numbers have been drawn
    otherise it returns draw_pool[draw_index] and moves foward with index 
    for the next call.
    */
    


}

/**
 * has_more_draws - Check if there are more numbers to draw
 *
 * Return: true if more draws are available, false otherwise
 */
bool has_more_draws(void)
{
    /* TODO: Check if there are more numbers to draw */

    // If draw_index has reached BINGO_MAX, we've have used up the entire pool.
    if(draw_index >= BINGO_MAX){
        //no more numbers left to draw
        return false;
    }else {
        //numbers still left to draw
        return true;
    }
    /*
    - When draw_index equals or exceeds BINGO_MAX, all draws are finished.
    - Otherwise, at east one draw is left 
     */
}

/**
 * get_draw_count - Get the number of draws that have been made
 *
 * Return: Number of draws made so far
 */
int get_draw_count(void)
{
    /* TODO: Return how many draws have been made */
    return draw_index;

    /*
    - draw_index stores how many draws have happend. 
    - return the current draw count
    
    */



}
