#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define MAP_HEIGHT 36
#define MAP_WIDTH 120

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMap(char mapa[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

void updatePlayerPosition(char mapa[MAP_HEIGHT][MAP_WIDTH], int x, int y, char player1, char player2, char player3, char player4) {
    mapa[y][x] = player1;
    mapa[y][x + 1] = player2;
    mapa[y + 1][x] = player3;
    mapa[y + 1][x + 1] = player4;
}

int main() {
    int x = 1;
    int y = 1;
    char move;
    char player1 = 'S';
    char player2 = '2';
    char player3 = '[';
    char player4 = ']';

    char mapa[MAP_HEIGHT][MAP_WIDTH];

    // Inicializa o mapa
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i % 4 == 0 && j % 4 == 0) {
                mapa[i][j] = 'X';
                mapa[i - 1][j - 1] = 'X';
                mapa[i][j - 1] = 'X';
                mapa[i - 1][j] = 'X';
            } else {
                mapa[i][j] = ' ';
            }
        }
    }

    // Inicializa posição inicial do jogador
    updatePlayerPosition(mapa, x, y, player1, player2, player3, player4);

    // Desenha o mapa inicial
    drawMap(mapa);

    while (true) {
        if (_kbhit()) {
            move = (char)_getch();

            // Limpa a posição atual do jogador no mapa
            updatePlayerPosition(mapa, x, y, ' ', ' ', ' ', ' ');

            // Atualiza a posição do jogador conforme a tecla pressionada
            switch (move) {
                case 'w':
                    if (mapa[y - 1][x] != 'X' && mapa[y - 2][x] != 'X') {
                        if (y > 1) y -= 2;
                    }
                    break;
                case 's':
                    if (mapa[y + 1][x] != 'X' && mapa[y + 2][x] != 'X') {
                        if (y < MAP_HEIGHT - 3) y += 2;
                    }
                    break;
                case 'a':
                    if (mapa[y][x - 1] != 'X' && mapa[y][x - 2] != 'X') {
                        if (x > 1) x -= 2;
                    }
                    break;
                case 'd':
                    if (mapa[y][x + 1] != 'X' && mapa[y][x + 2] != 'X') {
                        if (x < MAP_WIDTH - 3) x += 2;
                    }
                    break;
                default:
                    break;
            }

            // Desenha o jogador na nova posição
            updatePlayerPosition(mapa, x, y, player1, player2, player3, player4);

            // Move o cursor para o início da tela e redesenha o mapa
            gotoxy(0, 0);
            drawMap(mapa);
        }

        // Espera um curto período para controle de velocidade
        Sleep(100);
    }

    return 0;
}