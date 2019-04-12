//Dank ZERO
#include "AI.h"
#include "Legal_moves.h"
#include "Main_struct.h"
#include "Game_ending.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int pawn_ev[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0}, {50, 50, 50, 50, 50, 50, 50, 50}, {10, 10, 20, 30, 30, 20, 10, 10}, {5,  5, 10, 25, 25, 10,  5,  5},
                    {0,  0,  0, 20, 20,  0,  0,  0}, {5, -5,-10,  0,  0,-10, -5,  5}, {5, 10, 10,-20,-20, 10, 10,  5}, {0,  0,  0,  0,  0,  0,  0,  0}};

int knight_ev[8][8] = {{-50,-40,-30,-30,-30,-30,-40,-50}, {-40,-20,  0,  0,  0,  0,-20,-40}, {-30,  0, 10, 15, 15, 10,  0,-30},
                       {-30,  5, 15, 20, 20, 15,  5,-30}, {-30,  0, 15, 20, 20, 15,  0,-30}, {-30,  5, 10, 15, 15, 10,  5,-30},
                       {-40,-20,  0,  5,  5,  0,-20,-40}, {-50,-40,-30,-30,-30,-30,-40,-50}};

int bishop_ev[8][8] = {{-20,-10,-10,-10,-10,-10,-10,-20}, {-10,  0,  0,  0,  0,  0,  0,-10}, {-10,  0,  5, 10, 10,  5,  0,-10},
                       {-10,  5,  5, 10, 10,  5,  5,-10}, {-10,  0, 10, 10, 10, 10,  0,-10}, {-10, 10, 10, 10, 10, 10, 10,-10},
                       {-10,  5,  0,  0,  0,  0,  5,-10}, {-20,-10,-10,-10,-10,-10,-10,-20}};

int rook_ev[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0}, {5, 10, 10, 10, 10, 10, 10, 5}, {-5,  0,  0,  0,  0,  0,  0, -5},
                     {-5,  0,  0,  0,  0,  0,  0, -5}, {-5,  0,  0,  0,  0,  0,  0, -5}, {-5,  0,  0,  0,  0,  0,  0, -5},
                     {-5,  0,  0,  0,  0,  0,  0, -5}, { 0,  0,  0,  5,  5,  0,  0,  0}};

int queen_ev[8][8] = {{-20,-10,-10, -5, -5,-10,-10,-20}, {-10,  0,  0,  0,  0,  0,  0,-10}, {-10,  0,  5,  5,  5,  5,  0,-10},
                      {-5,  0,  5,  5,  5,  5,  0, -5}, {0,  0,  5,  5,  5,  5,  0, -5}, {-10,  5,  5,  5,  5,  5,  0,-10},
                      {-10,  0,  5,  0,  0,  0,  0,-10}, {-20,-10,-10, -5, -5,-10,-10,-20}};

int kinq_middleGame_ev[8][8] = {{-30,-40,-40,-50,-50,-40,-40,-30}, {-30,-40,-40,-50,-50,-40,-40,-30}, {-30,-40,-40,-50,-50,-40,-40,-30},
                          {-30,-40,-40,-50,-50,-40,-40,-30}, {-20,-30,-30,-40,-40,-30,-30,-20}, {-10,-20,-20,-20,-20,-20,-20,-10},
                          {20, 20,  0,  0,  0,  0, 20, 20}, {20, 30, 10,  0,  0, 10, 30, 20}};

int king_endGame_ev[8][8] = {{-50,-40,-30,-20,-20,-30,-40,-50}, {-30,-20,-10,  0,  0,-10,-20,-30}, {-30,-10, 20, 30, 30, 20,-10,-30},
                       {-30,-10, 30, 40, 40, 30,-10,-30}, {-30,-10, 30, 40, 40, 30,-10,-30}, {-30,-10, 20, 30, 30, 20,-10,-30},
                       {-30,-30,  0,  0,  0,  0,-30,-30}, {-50,-30,-30,-30,-30,-30,-30,-50}};

//Values of pieces
int pawn1 = 100, knight1 = 320, bishop1 = 330, rook1 = 500, queen1 = 900, king1 = 20000;

//Board evaluation - playing white
int evaluate(char game[8][8], chess mGame)
{
    int evaluation = 0;
    //Checking if Game ended
    if (End_Game(1, game, mGame))
    {
        if (is_check(game, mGame.turn * -1, &mGame.Bcheck, &mGame.Wcheck, mGame))
        {
            //Black won
            return (-20000);
        }
        else
            return 0;
    }
    else if (End_Game(-1, game, mGame))
    {
        if (is_check(game, mGame.turn * -1, &mGame.Bcheck, &mGame.Wcheck, mGame))
        {
            //White won
            return 20000;
        }
        else
            return 0;
    }

    if (insufficient(game))
        return 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //Determining piece evaluation
            //White pieces
            if (islower(game[i][j]))
            {
                switch(game[i][j])
                {
                    case '0':
                        break;
                    case 'p':
                        evaluation += pawn1 + pawn_ev[i][j];
                        break;
                    case 'k':
                        evaluation += king1 + kinq_middleGame_ev[i][j];
                        break;
                    case 'q':
                        evaluation += queen1 + queen_ev[i][j];
                        break;
                    case 'n':
                        evaluation += knight1 + knight_ev[i][j];
                        break;
                    case 'b':
                        evaluation += bishop1 + bishop_ev[i][j];
                        break;
                    case 'r':
                        evaluation += rook1 + rook_ev[i][j];
                        break;
                }
            }
            //Black pieces
            else if (isupper(game[i][j]))
            {
                switch(game[i][j])
                {
                    case '0':
                        break;
                    case 'P':
                        evaluation -= (pawn1 + pawn_ev[7 - i][7 - j]);
                        break;
                    case 'K':
                        evaluation -= (king1 + kinq_middleGame_ev[7 - i][7 - j]);
                        break;
                    case 'Q':
                        evaluation -= (queen1 + queen_ev[7 - i][7 - j]);
                        break;
                    case 'N':
                        evaluation -= (knight1 + knight_ev[7 - i][7 - j]);
                        break;
                    case 'B':
                        evaluation -= (bishop1 + bishop_ev[7 - i][7 - j]);
                        break;
                    case 'R':
                        evaluation -= (rook1 + rook_ev[7 - i][7 - j]);
                        break;
                }
            }
        }
    }

    return evaluation;
}

//Generating possible moves - returns number of possible moves
int generate_moves(char game[8][8], char moves[200][5], int turn, chess mGame)
{
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //Next move for white                                   //Change turn before giving parameter
            if (turn == 1 && islower(game[i][j]))
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        char move[6];
                        move[0] = j + 65;
                        move[1] = i + 49;
                        move[2] = k + 65;
                        move[3] = l + 49;
                        move[4] = 'q';
                        //If move is valid
                        if (move_check(game[i][j], game, move, turn, mGame, &mGame.blackLongCastle, &mGame.blackShortCastle, &mGame.whiteLongCastle, &mGame.whiteShortCastle))
                        {
                            for (int m = 0; m < 5; m++)
                            {
                                moves[counter][m] = move[m];
                            }
                            counter++;
                        }
                    }
                }
            }
            else if (turn == -1 && isupper(game[i][j]))
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        char move[6];
                        move[0] = j + 65;
                        move[1] = i + 49;
                        move[2] = k + 65;
                        move[3] = l + 49;
                        move[4] = 'Q';
                        //If move is valid
                        if (move_check(game[i][j], game, move, turn, mGame, &mGame.blackLongCastle, &mGame.blackShortCastle, &mGame.whiteLongCastle, &mGame.whiteShortCastle))
                        {
                            for (int m = 0; m < 5; m++)
                            {
                                moves[counter][m] = move[m];
                            }
                            counter++;
                        }
                    }
                }
            }
        }
    }

    return counter;
}

//Updating game board
void change_board1(char move[6], char game[8][8])
{
    int to_x = move[3] - 49;
    int to_y = move[2] - 65;
    int from_x = move[1] - 49;
    int from_y = move[0] - 65;

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

void moveSort(char board[8][8], char possible_moves[200][5], int numberof_moves, chess mGame)
{
    //Rating moves
    int move_ratings[numberof_moves];
    for (int i = 0; i < numberof_moves; i++)
    {
        //Creating a temporary board
        char temp_board[8][8];
        memcpy(&temp_board[0][0], &board[0][0], 8*8*sizeof(board[0][0]));

        //Playing move
        char current_move[6];
        for (int j = 0; j < 5; j++)
            current_move[j] = possible_moves[i][j];

        change_board1(current_move, temp_board);

        move_ratings[i] = evaluate(temp_board, mGame);
    }

    //Sorting
    int arranged = 0;
    while (!arranged)
    {
        //Checking if moves are sorted
        for (int i = 0; i < numberof_moves - 1; i++)
        {
            if (move_ratings[i] >= move_ratings[i + 1])
                arranged = 1;
            else
            {
                arranged = 0;
                break;
            }
        }

        //Sorting
        for(int i = 0; i < numberof_moves - 1; i++)
        {
            if (move_ratings[i] < move_ratings[i+1])
            {
                int change = move_ratings[i+1];
                move_ratings[i + 1] = move_ratings[i];
                move_ratings[i] = change;

                char move[6];
                for (int j = 0; j < 5; j++)
                {
                    move[j] = possible_moves[i + 1][j];
                    possible_moves[i + 1][j] = possible_moves[i][j];
                    possible_moves[i][j] = move[j];
                }
            }
        }
    }
}

int findMove(int alpha, int beta, int turn, char move[6],char board[8][8], int depth, chess mGame)
{
    char possible_moves[200][5];
    int numberOfMoves = generate_moves(board, possible_moves, turn, mGame);

    //Checkmate and stalemate
    if (numberOfMoves == 0)
        return evaluate(board, mGame);

    if (depth == 3)
    {
        moveSort(board, possible_moves, numberOfMoves, mGame);
    }

    int bestmove_index, i;

	for (i = 0; i < numberOfMoves; i++)
    {
    	int score = -60000;

        //Creating a temporary board
        char temp_board[8][8];
        memcpy(&temp_board[0][0],&board[0][0],8*8*sizeof(board[0][0]));

        //Playing move
        char current_move[6];
        for (int j = 0; j < 5; j++)
            current_move[j] = possible_moves[i][j];

        change_board1(current_move, temp_board);

        //Checking depth
        if (depth == 0)
            score = evaluate(temp_board, mGame);
        else
            score = findMove(alpha, beta, turn * -1, move, temp_board, depth - 1, mGame);

        if(turn == 1)
        {
        	if (score >= beta)
            {
                return beta;
            }
            else if (score > alpha)
            {
                bestmove_index = i;
                alpha = score;
            }
        }
        else
        {
            if (score <= alpha)
            {
              	return alpha;
          	}
            else if (score < beta)
            {
                beta = score;
                bestmove_index = i;
            }
        }
    }

    for (int j = 0; j < 5; j++)
        move[j] = possible_moves[bestmove_index][j];

    if(turn == 1)
        return alpha;
    else
        return beta;

}

void dank_zero(char move[5], char board[8][8], chess mGame)
{
	int alpha = -50000, beta = 50000;
    int turn = 1;
    int depth = 3;
    findMove(alpha, beta, turn, move, board, depth, mGame);
}
