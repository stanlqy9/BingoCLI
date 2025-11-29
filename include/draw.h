#ifndef DRAW_H
#define DRAW_H

#include <stdbool.h>

/* Function prototypes for draw.c */
void init_draw_sequence(void);
int get_next_draw(void);
bool has_more_draws(void);
int get_draw_count(void);

#endif 

