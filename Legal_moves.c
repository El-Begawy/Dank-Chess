//Functions needed to decide if the move is legal
#include "Legal_moves.h"
#include "Main_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//Checking if move exists
int Position_check(char game[8][8],char move[6])
{
    if(move[0] > 64 && move[0] < 73 && move[2] > 64 && move[2] < 73)
    {
        if(move[1]-'0'  >  0   &&  move[1]-'0' < 9 && move[3]-'0' > 0 && move[3]-'0'  <  9)
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

//Checking for a piece
char piece_check(int turn, char game[8][8], char move[6])
{
    if (isupper(game[move[1] - 49][move[0] - 65]) && turn == -1)
    {
        return (game[move[1] - 49][move[0] - 65]);
    }
    else if (islower(game[move[1] - 49][move[0] - 65]) && turn == 1)
    {
        return (game[move[1] - 49][move[0] - 65]);
    }
    else
        return '0';
}

//Castle
int castle(char piece, int to_x, int from_x, int to_y, int from_y, chess mGame)
{
    char game[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            game[i][j] = mGame.game[i][j];
        }
    }

    //If the king is in check
    if (!king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
            return 0;

    game[to_x][to_y] = game[from_x][from_y];
    game[from_x][from_y] = '0';

    //If king is going to a check
    if (!king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
            return 0;

    game[to_x][to_y] = '0';
    //White is castling
    if (from_y == 4 && from_x == 7 && islower(piece))
    {
        //Short castle
        if (to_y == 6 && !mGame.whiteShortCastle)
        {
            game[7][5] = 'k';
            game[7][4] = '0';
            if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
                return 1;
            else
                return 0;
        }
        //Long castle
        else if (to_y == 2 && !mGame.whiteLongCastle)
        {
            game[7][3] = 'k';
            game[7][4] = '0';
            if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
            {
                game[7][1] = 'k';
                game[7][3] = '0';
                if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
                {
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    //Black is castling
    else if (from_y == 4 && from_x == 0 && isupper(piece))
    {
        //Short castle
        if (to_y == 6 && !mGame.blackShortCastle)
        {
            game[0][5] = 'K';
            game[0][4] = '0';
            if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
                return 1;
            else
                return 0;
        }
        //Long castle
        else if (to_y == 2 && !mGame.blackLongCastle)
        {
            game[0][3] = 'K';
            game[0][4] = '0';
            if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
            {
                game[0][1] = 'K';
                game[0][4] = '0';
                if (king_state(game, mGame.turn, mGame.Bcheck, mGame.Wcheck, mGame))
                {
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}

//King
int king_move(char piece, int to_x, int from_x, int to_y, int from_y, char board[8][8], chess mGame)
{
    int diff_x = abs(to_x - from_x);
    int diff_y = abs(to_y - from_y);

    if ((diff_x == 1 && diff_y == 1) || (diff_x == 1 && diff_y == 0) || (diff_x == 0 && diff_y == 1))
    {
        return 1;
    }
    //Castling
    else if (diff_y == 2 && diff_x == 0)
    {
        return castle(piece, to_x, from_x, to_y, from_y, mGame);
    }
    else
    {
        return 0;
    }
}

//Rook
int rook(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8])
{
    int movement_type;
    if(from_y == to_y && from_x > to_x)
        movement_type = 1;//horizontally<left
    else if(from_y == to_y && from_x < to_x)
        movement_type = 10;//horizontally right
    else if (from_x == to_x && from_y > to_y)
        movement_type = 2;//vertically downwards
    else if (from_x == to_x && from_y < to_y)
        movement_type = 20;//vertically upwards
    else
        return 0;
    int i;
    switch(movement_type)
    {
      case 1:
            for( i=from_x-1 ; i>to_x ;i--)
            {
                if(game[from_y][i] != '0')
                    break;
            }
            if(i == to_x)
            {
                return 1;
            }break;
      case 10:
            for(i = from_x+1 ; i<to_x ;i++)
            {
                if(game[from_y][i] != '0')
                    break;
            }
            if(i == to_x)
            {
                return 1;
            }break;
        case 2:
            for( i=from_y-1 ; i>to_y ;i--)
            {
                if(game[i][from_x] != '0')
                    break;
            }
            if(i == to_y)
            {
                return 1;
            }break;
        case 20:
              for( i=from_y+1 ; i<to_y ;i++)
              {
                  if(game[i][from_x] != '0')
                  break;
              }
              if(i == to_y)
              {
                  return 1;
          }break;
    }
    return 0;
}

//Bishop
int bishop(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8])
{
    int movement_type;
    if (from_x-to_x == from_y-to_y && from_x>to_x)
        movement_type = 3;//southwest
    else if (from_x-to_x == from_y-to_y && from_y<to_y)
        movement_type = 4;//northeast
    else if(from_x-to_x == -(from_y-to_y) && from_y>to_y)
        movement_type = 5;//southeast
    else if(from_x - to_x== -(from_y-to_y) && from_y<to_y)
        movement_type = 6;//northwest
    else
        return 0;
     int i,j;
    switch(movement_type)
    {
        case 3:
              for(i=from_y-1,j=from_x-1;i>to_y ;i--,j--)
              {
                  if(game[i][j] != '0')
                  break;
              }
              if(i == to_y)
              {
                  return 1;
          }break;
        case 4:
            for(i=from_y+1,j=from_x+1 ; i<to_y ;i++,j++)
            {
                if(game[i][j] != '0')
                break;
            }
            if(i == to_y)
            {
               return 1;
            }break;
        case 5:
          		for(i=from_y-1,j=from_x+1 ; i>to_y ;i--,j++)
           		{
          	 	    if(game[i][j] != '0')
               	    break;
      	    	}
          		if(i == to_y)
          		{
                	return 1;
            }break;
        case 6:
          		for(i=from_y+1,j=from_x-1 ; i<to_y ;i++,j--)
           		{
          	 	    if(game[i][j] != '0')
               	    break;
      	    	}
          		if(i == to_y)
          		{
                	return 1;
            }break;
    }
    return 0;
}

//Queen
int queen(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8])
{
    int x_diff = abs(to_x - from_x);
    int y_diff = abs(to_y - from_y);

    //Checking if move is valid
    if (x_diff == 0 || y_diff == 0)
    {
        if (isupper(piece))
            return rook('R', to_x, from_x, to_y, from_y, game);
        else
            return rook('r', to_x, from_x, to_y, from_y, game);
    }
    else if (x_diff == y_diff)
    {
        if (isupper(piece))
            return bishop('B', to_x, from_x, to_y, from_y, game);
        else
            return bishop('b', to_x, from_x, to_y, from_y, game);
    }
    else
        return 0;
}

//Knight
int knight(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8])
{
    int x_diff = abs(to_x - from_x);
    int y_diff = abs(to_y - from_y);

    if ((x_diff == 1 && y_diff == 2) || (x_diff == 2 && y_diff == 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Pawn
int pawn(char piece, int to_x, int from_x, int to_y, int from_y, char game[8][8], char move[6])
{
    int x_diff = abs(to_x - from_x);
    int y_diff = abs(to_y - from_y);

    //Taking diagonally
    if ((y_diff == 1 && x_diff == 1) && ((to_y > from_y && !islower(piece)) || (to_y < from_y && islower(piece)) ) )
    {
        if (game[to_y][to_x] == '0')
            return 0;
        else
        {
            //Promotion
            if (to_y == 7)
            {
                switch (move[4])
                {
                    case 'Q':
                    case 'R':
                    case 'B':
                    case 'N':
                        return 1;
                    default :
                        return 0;
                }
            }
            else if(to_y == 0)
            {
                switch (move[4])
                {
                    case 'q':
                    case 'r':
                    case 'b':
                    case 'n':
                        return 1;
                    default :
                        return 0;
                }
            }
            else
                return 1;
        }
    }
    else if(isupper(piece)&&(to_y-from_y==1||(to_y-from_y==2&&from_y==1 && game[from_y + 1][from_x] == '0')) && x_diff == 0)
    {
        if(game[to_y][to_x]=='0')
        {
            if (to_y == 7)
            {
                switch (move[4])
                {
                    case 'Q':
                    case 'R':
                    case 'B':
                    case 'N':
                        return 1;
                    default :
                        return 0;
                }
            }
            else
                return 1;
        }
        else
            return 0;
    }
    else if(islower(piece)&&(from_y-to_y==1||(from_y-to_y==2&&from_y==6 && game[from_y - 1][from_x] == '0')) && x_diff == 0)
    {
        if(game[to_y][to_x]=='0')
        {
            if (to_y == 0)
            {
                switch (move[4])
                {
                    case 'q':
                    case 'r':
                    case 'b':
                    case 'n':
                        return 1;
                    default :
                        return 0;
                }
            }
            else
                return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

//Checks if theirs a different colour piece
int go_tocheck(int to_x,int to_y,char piece,char game[8][8])
{
    if(isupper(piece)==isupper(game[to_x][to_y])&&game[to_x][to_y]!='0')
        return 0;
    else
        return 1;
}

//Checking if the move is valid
int move_check_1(char piece, char game[8][8], char move[6], int turn, chess mGame)
{
    int to_x = move[3] - 49;
    int to_y = move[2] - 65;
    int from_x = move[1] - 49;
    int from_y = move[0] - 65;

    if(!go_tocheck(to_x,to_y,piece,game))
        return 0;

    int valid;
    switch (piece)
    {
        case 'P':
        case 'p':
            valid = pawn(piece, to_y, from_y, to_x, from_x, game, move);
                break;
        case 'K':
        case 'k':

            valid = king_move(piece, to_x, from_x, to_y, from_y, game, mGame);
            break;
        case 'Q':
        case 'q':
            valid = queen(piece, to_y, from_y,to_x, from_x, game);
            break;
        case 'N':
        case 'n':
            valid = knight(piece, to_x, from_x, to_y, from_y, game);
            break;
        case 'B':
        case 'b':
            valid = bishop(piece, to_y, from_y ,to_x, from_x, game);
            break;
        case 'R':
        case 'r':
            valid = rook(piece, to_y, from_y, to_x, from_x, game);
            break;
    }

    if (valid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//King's state
int king_state(char game[8][8], int turn, int bcheck, int wcheck, chess mGame)
{
    char to_king[6];
    if (turn == 1)
    {
        //Checking king's position
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (game[i][j] == 'k')
                {
                    //Going to king
                    to_king[3] = i + 49;
                    to_king[2] = j + 65;
                    goto next;
                }
            }
        }
    }
    else if (turn == -1)
    {
        //Checking king's position
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (game[i][j] == 'K')
                {
                    //Going to king
                    to_king[3] = i + 49;
                    to_king[2] = j + 65;
                    goto next;
                }
            }
        }
    }
    //Checking if a piece can get to the king
    int valid;
    next:
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if((turn == 1 && isupper(game[i][j])) || (turn == -1 && islower(game[i][j])))
            {
                to_king[1] = i + 49;
                to_king[0] = j + 65;

                //In case of promotion
                if (isupper(game[i][j]))
                    to_king[4] = 'Q';
                else
                    to_king[4] = 'q';


                if (move_check_1(game[i][j], game, to_king, turn, mGame))
                    return 0;
                else
                    valid = 1;
            }
        }
    }

    return valid;
}

//Checks if there's a check
int is_check(char game[8][8], int turn, int *bcheck, int *wcheck, chess mGame)
{
    char to_king[6];
    if (turn == -1)
    {
        //Checking king's position
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (game[i][j] == 'k')
                {
                    //Going to king
                    to_king[3] = i + 49;
                    to_king[2] = j + 65;
                    goto next;
                }
            }
        }
    }
    else if (turn == 1)
    {
        //Checking king's position
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (game[i][j] == 'K')
                {
                    //Going to king
                    to_king[3] = i + 49;
                    to_king[2] = j + 65;
                    goto next;
                }
            }
        }
    }
    //Checking if a piece can get to the king
    int valid;
    next:
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if((turn == -1 && isupper(game[i][j])) || (turn == 1 && islower(game[i][j])))
            {
                to_king[1] = i + 49;
                to_king[0] = j + 65;

                //In case of promotion
                if (isupper(game[i][j]))
                    to_king[4] = 'Q';
                else
                    to_king[4] = 'q';

                if (move_check_1(game[i][j], game, to_king, turn, mGame))
                    return 1;
                else
                    valid = 0;
            }
        }
    }

    return valid;
}

//If a move is valid
int move_check(char piece, char game[8][8], char move[6], int turn, chess mGame, int *BLC, int *BSC, int *WLC, int *WSC)
{

    if (move_check_1(piece, game, move, turn, mGame))
    {
        int to_x = move[3] - 49;
        int to_y = move[2] - 65;
        int from_x = move[1] - 49;
        int from_y = move[0] - 65;

        char temp_board[8][8];
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                temp_board[i][j] = game[i][j];
            }
        }

        temp_board[to_x][to_y] = game[from_x][from_y];
        temp_board[from_x][from_y] = '0';

        if (king_state(temp_board, turn, mGame.Bcheck, mGame.Wcheck, mGame))
        {
            if (piece == 'K')
            {
                *BLC = 1;
                *BSC = 1;
            }
            else if (piece == 'k')
            {
                *WLC = 1;
                *WSC = 1;
            }
            else if (piece == 'R' && move[0] == 'F')
                *BSC = 1;
            else if (piece == 'R' && move[0] == 'A')
                *BLC = 1;
            else if (piece == 'r' && move[0] == 'F')
                *WSC = 1;
            else if (piece == 'r' && move[0] == 'A')
                *WLC = 1;

            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
