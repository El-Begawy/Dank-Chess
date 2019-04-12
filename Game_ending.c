//Functions that decide the game ending
#include "Legal_moves.h"
#include "Main_struct.h"
#include "Game_ending.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


//End game - Stalemate - checkmate
int End_Game(int turn,char game[8][8],chess mGame)
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            {
                if(turn==-1&&isupper(game[i][j]))
                {
                    for(int k=65;k<73;k++)
                        for(int l=0;l<8;l++)
                    {
                        char move[5];
                        move[0]=65+j;
                        move[1]=i+'0'+1;
                        move[2]=k;
                        move[3]=l+'0'+1;
                        move[4]='Q';
                        if(move_check(game[i][j], mGame.game, move, turn, mGame, &mGame.blackLongCastle, &mGame.blackShortCastle, &mGame.whiteLongCastle, &mGame.whiteShortCastle))
                            return 0;
                    }
                }
                else if(turn==1&&islower(game[i][j]))
                    for(int k=65;k<73;k++)
                        for(int l=0;l<8;l++)
                    {
                        char move[5];
                        move[0]=65+j;
                        move[1]=i+'0'+1;
                        move[2]=k;
                        move[3]=l+'0'+1;
                        move[4]='q';
                        if(move_check(game[i][j],mGame.game,move,turn,mGame, &mGame.blackLongCastle, &mGame.blackShortCastle, &mGame.whiteLongCastle, &mGame.whiteShortCastle))
                            return 0;
                    }
    }
    return 1;
}

//Returns 1 if draw by insufficient material
int insufficient(char game[8][8])
{
    int pieces = 0;
    //Counting pieces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (game[i][j] != '0')
                pieces++;
        }
    }

    //2 kings
    if (pieces == 2)
        return 1;
    //2 kings and a piece
    else if (pieces == 3)
    {
        //Checking the piece
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                //If the piece is a bishop or a knight
                if (game[i][j] == 'B' || game[i][j] == 'b' || game[i][j] == 'N' || game[i][j] == 'n')
                    return 1;
            }
        }
    }

    return 0;
}
