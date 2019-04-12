#ifndef MAIN_STRUCT_H_INCLUDED
#define MAIN_STRUCT_H_INCLUDED

typedef struct chess
{
    char game[8][8];                     //Main game board
    char taken_pieces[2][16];            //Indicates lost pieces to be printed: row 0 for white pieces - row 1 for black pieces.
    int turn;                            //Indicates next move: 1 for white - (-1) for black.
    int Wcheck;                          //White king's state.
    int Bcheck;                          //Black king's state.
    int whiteShortCastle, whiteLongCastle;
    int blackShortCastle, blackLongCastle;
}chess;

#endif // MAIN_STRUCT_H_INCLUDED
