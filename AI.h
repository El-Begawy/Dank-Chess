#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "Main_struct.h"

int evaluate(char game[8][8], chess mGame);
int generate_moves(char game[8][8], char moves[200][5], int turn, chess mGame);
void change_board1(char move[6], char game[8][8]);
void moveSort(char board[8][8], char possible_moves[200][5], int numberof_moves, chess mGame);
int findMove(int alpha, int beta, int turn, char move[6],char board[8][8], int depth, chess mGame);
void dank_zero(char move[5], char board[8][8], chess mGame);

#endif // AI_H_INCLUDED
