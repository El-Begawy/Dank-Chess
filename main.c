//Chess game
#include "Main_struct.h"
#include "Legal_moves.h"
#include "AI.h"
#include "Game_ending.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

chess undos[50];
int undocounter=0;
int maxundos=0;
int multiplayer=0;
//New game board - sets all pieces to starting squares - makes a static board with (- .) and notation
void new_game(char game[8][8], char static_board[8][8], char taken_pieces[2][16])
{
    char line[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    //Filling game board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            game[i][j] = '0';
        }
    }

    for (int i = 0; i < 8; i++)
    {
        game[0][i] = line[i];
        game[1][i] = 'P';
        game[7][i] = line[i] + 32;
        game[6][i] = 'p';
    }

    //Filling static board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
                static_board[i][j] = '-';
            else
                static_board[i][j] = ' ';
        }
    }

    //Emptying taken pieces array
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            taken_pieces[i][j] = '0';
        }
    }
}

//Starting game
char start()
{
    printf("\n\n\tWELCOME TO \n\n"
            " \t\t\t      ************   ************   ***      ***   ***   ***\n"
            " \t\t\t      ************   ************   ****     ***   ***  ***\n"
            " \t\t\t      *****    ***   ****    ****   *****    ***   *** **\n"
            " \t\t\t      *****    ***   ****    ****   ******   ***   *****\n"
            " \t\t\t      *****    ***   ************   *******  ***   *****\n"
            " \t\t\t      *****    ***   ************   *** **** ***   ******\n"
            " \t\t\t      *****    ***   ****    ****   ***  *******   *** ***\n"
            " \t\t\t      *****    ***   ****    ****   ***   ******   ***  ****\n"
            " \t\t\t      ************   ****    ****   ***    *****   ***   ****\n"
            " \t\t\t      ************   ****    ****   ***     ****   ***    ****"
            " \n\n"
            " \t\t\t************   ****           ************   ************   ************\n"
            " \t\t\t************   ****           ************   ************   ************\n"
            " \t\t\t************   ****           ****           ****           ****\n"
            " \t\t\t****           ************   ****           ****           ****\n"
            " \t\t\t****           ************   ************   ************   ************\n"
            " \t\t\t****           ************   ************   ************   ************\n"
            " \t\t\t****           ****    ****   ****                   ****           ****\n"
            " \t\t\t************   ****    ****   ****                   ****           ****\n"
            " \t\t\t************   ****    ****   ************   ************   ************\n"
            " \t\t\t************   ****    ****   ************   ************   ************\n"
            "\n\n\t\t\t\t Press:"
            "\n\t\t\t\t        1 - Start new game."
            "\n\t\t\t\t        2 - Load previous game."
            "\n\t\t\t\t        3 - Play the machine.\n");

    char start;
    do
    {
        scanf(" %c", &start);
        if(start!='1'&&start!='2'&&start!='3'&&start!='\n')
        {
            printf("Enter a valid instruction\n");
            continue;
        }

    }while(start!='1'&&start!='2'&&start!='3');



    return start;
}

//Clearing the screen
void clrscr()
{
    system("@cls||clear");
}

//Printing function
void print(char game[8][8], char static_board[8][8], char taken_pieces[2][16], int *wcheck, int *bcheck)
{
    //Clear screen
    clrscr();

    //Undo, load and new game
    printf("Press :\n        1 - Undo.\n        2 - Redo.\n        3 - Save game.\n        4 - Exit.\n\n");


    if (*bcheck == 1)
    {
        printf("\t\t\tBlack is in check.\n\n");
        *bcheck = 0;
    }
    else if (*wcheck == 1)
    {
        printf("\t\t\tWhite is in check.\n\n");
        *wcheck = 0;
    }

    //Counting taken pieces
    int whiteCounter = 0, blackCounter = 0;
    for (int i = 0; i < 16; i++)
    {
        if (taken_pieces[0][i] == '0')
            break;
        whiteCounter++;
    }
    for (int i = 0; i < 16; i++)
    {
        if (taken_pieces[1][i] == '0')
            break;
        blackCounter++;
    }

    //Printing characters
    printf("                                  ");
    for (int i = 0; i < 8; i++)
    {
        printf(" %c  ", 65 + i);
    }
    printf("\t\t\t Taken pieces.");
    printf("  \n\n");

    //Taken pieces
    int wCounter = 0, bCounter = 0;
    //Printing board
    for (int i = 0; i < 8; i++)
    {
        //Seperating lines
        printf("                                 +");
        for (int j = 0; j < 8; j++)
        {
            printf("---+");
        }

        //Taken pieces box
        if (i == 0 || i == 4)
        {
            printf("\t\t+");
            for (int j = 0; j < 28; j++)
                printf("-");
            printf("+");
        }
        else
        {
            printf("\t\t+\t\t\t     +");
        }

        //Pieces
        printf("\n                              %i  |", i + 1);
        for (int j = 0; j < 8; j++)
        {
            if (game[i][j] == '0')
                printf(" %c |", static_board[i][j]);
            else
                printf(" %c |", game[i][j]);
        }
        printf("  %i", i + 1);

        //Taken pieces
        if (i == 0)
            printf("\t\t|\t     White.\t     |");
        else if (i == 4)
            printf("\t\t|\t     Black.\t     |");
        else if (i < 4)
        {
            printf("\t\t|");
            for (int j = 1; j < 8; j++)
            {
                if (wCounter < whiteCounter && (wCounter < 7 * i))
                    printf(" %c  ", taken_pieces[0][wCounter++]);
                else
                    printf("    ");
            }
            printf("|");
        }
        else if (i > 4)
        {
            printf("\t\t|");
            for (int j = 1; j < 8; j++)
            {
                if (bCounter < blackCounter && (bCounter < 7 * i))
                    printf(" %c  ", taken_pieces[1][bCounter++]);
                else
                    printf("    ");
            }
            printf("|");
        }


        printf("\n");
    }

    //Final separating line
    printf("                                 +");
    for (int j = 0; j < 8; j++)
    {
        printf("---+");
    }

    printf("\t\t+");
    for (int j = 0; j < 28; j++)
        printf("-");
    printf("+");

    //Printing final characters
    printf("\n\n                                  ");
    for (int i = 0; i < 8; i++)
    {
        printf(" %c  ", 65 + i);
    }

    printf("\n\n\t\t\tEnter new move: \n");
}

chess undo(chess mainGame)
{
    if(multiplayer==1)
        undocounter--;
    return undos[--undocounter];
}

chess redo(chess mainGame)
{
    return undos[++undocounter];
}

void load_game(char game[8][8], char static_board[8][8], char taken_pieces[2][16],int* turn)
{
    printf("Choose save file:\n");
    for(int i=1;i<5;i++)
    printf("Save %d:\n",i);
    int save=0;
    do
    {
        scanf("%d",&save);
        if(save<1||save>4)
        {
            printf("Enter a valid save file\n");
        }
    }while(save<1||save>4);
    FILE *Savef;
    switch(save)
    {
        case 1:Savef=fopen("Save 1.txt","r");break;
        case 2:Savef=fopen("Save 2.txt","r");break;
        case 3:Savef=fopen("Save 3.txt","r");break;
        case 4:Savef=fopen("Save 4.txt","r");break;
    }
    //Filling static board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
                static_board[i][j] = '-';
            else
                static_board[i][j] = ' ';
        }
    }

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            game[i][j]=getc(Savef);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            taken_pieces[i][j]=getc(Savef);
        }
    }
    fscanf(Savef,"%d",turn);
    fscanf(Savef, " %d", &multiplayer);
    fclose(Savef);
}

void save_game(char game[8][8], char static_board[8][8], char taken_pieces[2][16],int turn)
{
    printf("Choose save file:\n");
    for(int i=1;i<5;i++)
    printf("Save %d:\n",i);
    int save=0;
    do
    {
        scanf("%d",&save);
        if(save<1||save>4)
        {
            printf("Enter a valid save file\n");
        }
    }while(save<1||save>4);
    FILE *Savef;
    switch(save)
    {
        case 1:Savef=fopen("Save 1.txt","w");break;
        case 2:Savef=fopen("Save 2.txt","w");break;
        case 3:Savef=fopen("Save 3.txt","w");break;
        case 4:Savef=fopen("Save 4.txt","w");break;
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            putc(game[i][j],Savef);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            putc(taken_pieces[i][j],Savef);
        }
    }
    fprintf(Savef,"%d",turn);
    fprintf(Savef, " %d", multiplayer);
    fclose(Savef);
}

//Updating game board
void change_board(char taken[2][16], char move[6], char game[8][8])
{
    int to_x = move[3] - 49;
    int to_y = move[2] - 65;
    int from_x = move[1] - 49;
    int from_y = move[0] - 65;

    //White piece
    if (islower(game[to_x][to_y]))
    {
        for (int i = 0; i < 16; i++)
        {
            if (taken[0][i] == '0')
            {
                taken[0][i] = game[to_x][to_y];
                break;
            }
        }
    }
    //Black piece
    else if (isupper(game[to_x][to_y]))
    {
        for (int i = 0; i < 16; i++)
        {
            if (taken[1][i] == '0')
            {
                taken[1][i] = game[to_x][to_y];
                break;
            }
        }
    }

    game[to_x][to_y] = game[from_x][from_y];
    game[from_x][from_y] = '0';

    //Castling
    if ((game[to_x][to_y] == 'k' || game[to_x][to_y] == 'K') && abs(to_y - from_y) == 2)
    {
        if (to_y == 6 && to_x == 7)
        {
            game[7][5] = 'r';
            game[7][7] = '0';
        }
        else if (to_y == 2 && to_x == 7)
        {
            game[7][3] = 'r';
            game[7][0] = '0';
        }
        else if (to_y == 6 && to_x == 0)
        {
            game[0][5] = 'R';
            game[0][7] = '0';
        }
        else if (to_y == 2 && to_x == 0)
        {
            game[0][3] = 'R';
            game[0][0] = '0';
        }
    }

    //Promotion
    if ((game[to_x][to_y] == 'p' && to_x == 0) || (game[to_x][to_y] == 'P' && to_x == 7))
    {
        game[to_x][to_y] = move[4];
    }
}

int main()
{
    //Main game loop
    chess mainGame;
    char starting = start();
    char static_board[8][8];
    mainGame.turn = 1;
    mainGame.blackLongCastle = 0;
    mainGame.blackShortCastle = 0;
    mainGame.whiteLongCastle = 0;
    mainGame.whiteShortCastle = 0;
    int checkmate=0;   //Winner determination 1 for white -1 for black.

    if (starting == '1')
    {
        //Initialize standard board.
        new_game(mainGame.game, static_board, mainGame.taken_pieces);
        print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
    }
    else if (starting == '2')
    {
        load_game(mainGame.game, static_board, mainGame.taken_pieces,&mainGame.turn);
        print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
    }
    else if (starting == '3')
    {
        //Initialize standard board.
        new_game(mainGame.game, static_board, mainGame.taken_pieces);
        print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
        multiplayer=1;
    }
    undos[undocounter]=mainGame;
    while(!checkmate)
    {
        char move[6];
        //If machine turn
        if(multiplayer==1&&mainGame.turn==1)
        {
           dank_zero(move, mainGame.game, mainGame);
           move[4]='q';
        }
        else
        {
            scanf(" ");
            fgets(move, 6, stdin);
        }
        if(move[0]=='1')
        {
            if(undocounter)
            {
                mainGame=undo(mainGame);
                print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
            }
            else
                printf("Nothing to undo\n");
            continue;
        }
        else if(move[0] == '2')
        {
            if(maxundos==undocounter)
                printf("Nothing to redo\n");
            else
            {
                mainGame=redo(mainGame);
                print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
            }
            continue;
        }
        else if(move[0] == '3')
        {
            save_game(mainGame.game, static_board, mainGame.taken_pieces,mainGame.turn);
        }
        else if(move[0] == '4')
        {
            break;
        }
        //Main game loop
        else
        {
            if(!Position_check(mainGame.game,move))
            {
                printf("Invalid move\n");
                continue;
            }
            char piece=piece_check(mainGame.turn, mainGame.game, move);
            if(piece == '0')
            {
                printf("Invalid piece\n");
                continue;
            }
            if(move_check(piece, mainGame.game, move, mainGame.turn, mainGame, &mainGame.blackLongCastle, &mainGame.blackShortCastle, &mainGame.whiteLongCastle, &mainGame.whiteShortCastle))
                {
                    change_board(mainGame.taken_pieces, move, mainGame.game);
                    undocounter++;
                    mainGame.turn*=-1;
                    undos[undocounter]=mainGame;
                    maxundos=undocounter;
                }
            else
                {
                    printf("Invalid move\n");
                    continue;
                }
        }
        //Check & checkmate.
        if (is_check(mainGame.game, mainGame.turn * -1, &mainGame.Bcheck, &mainGame.Wcheck, mainGame))
        {
            if (End_Game(mainGame.turn, mainGame.game, mainGame))
            {
                if (mainGame.turn == -1)
                {
                    print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
                    printf("\t\t\tCheckmate! Congratulations %s.\n", "White");
                    break;
                }
                else
                {
                    print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
                    printf("\t\t\tCheckmate! Congratulations %s.\n", "Black");
                    break;
                }
            }
            else
            {
                if (mainGame.turn == -1)
                {
                    mainGame.Bcheck = 1;
                }
                else
                {
                    mainGame.Wcheck = 1;
                }
            }
        }

        //Stalemate
        if (End_Game(mainGame.turn, mainGame.game, mainGame))
        {
            print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
            printf("\t\t\tIt's a stalemate.\n");
            break;
        }

        //Draw by insufficient material
        if (insufficient(mainGame.game))
        {
            print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
            printf("\t\t\tDraw by insufficient material.\n");
            break;
        }

        print(mainGame.game, static_board, mainGame.taken_pieces, &mainGame.Wcheck, &mainGame.Bcheck);
    }

    return 0;
}
