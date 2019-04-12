#ifndef LEGAL_MOVES_H_INCLUDED
#define LEGAL_MOVES_H_INCLUDED

#include "Main_struct.h"

//Function prototypes
int Position_check(char game[8][8],char move[6]);
char piece_check(int turn, char game[8][8], char move[6]);
int castle(char piece, int to_x, int from_x, int to_y, int from_y, chess mGame);
int king_move(char piece, int to_x, int from_x, int to_y, int from_y, char board[8][8], chess mGame);
int rook(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8]);
int bishop(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8]);
int queen(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8]);
int knight(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8]);
int pawn(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8], char move[6]);
int go_tocheck(int to_x,int to_y,char piece,char game[8][8]);
int move_check_1(char piece, char game[8][8], char move[6], int turn, chess mGame);
int king_state(char game[8][8], int turn, int bcheck, int wcheck, chess mGame);
int is_check(char game[8][8], int turn, int *bcheck, int *wcheck, chess mGame);
int move_check(char piece, char game[8][8], char move[6], int turn, chess mGame, int *BLC, int *BSC, int *WLC, int *WSC);

#endif // LEGAL_MOVES_H_INCLUDED
