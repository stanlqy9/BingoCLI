#ifndef GAME_H
#define GAME_H

#include "types.h"

/* Function prototypes for game.c */
void init_card(BingoCard *card, int card_id);
void mark_number(BingoCard *cards, int num_cards, int drawn_number);
bool check_bingo(const BingoCard *card);
int check_all_cards_for_bingo(const BingoCard *cards, int num_cards);
void print_card(const BingoCard *card);

#endif 

