#ifndef MOVES_H
#define MOVES_H

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>

#define linha 36
#define coluna 120


char getInput() //constantly gets the user input
{
    if (_kbhit())
    {
        char user = (char)_getch();

        return user;
    }
    return -1;
}

//MOVIMENTOS W, A ,S ,D

void up(char move, int y, int mapa[linha][coluna], char player)
{
    if (move == 'w' && y>0)
        {
            //y--;
            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    if (mapa[i][j] == player && i>0)
                    {
                        mapa[i - 1][j] = player;
                        mapa[i][j] = ' ';
                        break;
                    }
                }
            }

            system("cls");

            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    printf("%c", mapa[i][j]);
                }

                printf("\n");
            }
            Sleep(200);
        }
}

void down(char move, int y, int mapa[linha][coluna], char player){
    if (move == 's' && y<linha)
        {
            //y++;
            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    if (mapa[i][j] == player && i<linha)
                    {
                        mapa[i][j] = ' ';
                        mapa[i + 1][j] = player;
                        j=j+30;
                        i=i+20;
                    }
                }
            }

            system("cls");

            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    printf("%c", mapa[i][j]);
                }

                printf("\n");
            }
            Sleep(200);
        }
}

void left (char move, int x, int mapa[linha][coluna], char player)
{
    if (move == 'a' && x>0)
        {
            //x--;
            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    if (mapa[i][j] == player && j>0)
                    {
                        mapa[i][j] = ' ';
                        mapa[i][j-1] = player;
                        break;
                    }
                }
            }

            system("cls");

            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    printf("%c", mapa[i][j]);
                }

                printf("\n");
            }
            Sleep(200);
        }
}

void right(char move, int x, int mapa[linha][coluna], char player)
{
    if (move == 'd' && x<coluna)
        {
            //x++;
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    if (mapa[i][j] == player && j<coluna)
                    {
                        mapa[i][j] = ' ';
                        mapa[i][j+1] = player;
                        break;
                    }
                }
            }

            system("cls");

            for (int i = 0; i < linha; i++)
            {
                for (int j = 0; j < coluna; j++)
                {
                    printf("%c", mapa[i][j]);
                }

                printf("\n");
            }
            Sleep(200);
        }
}




#endif