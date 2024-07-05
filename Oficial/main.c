#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "File.h"
#include "menu.h"

#define L 16
#define C 30
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 20
#define BOMB_RANGE 2
#define INITIAL_LIVES 3
#define ENEMY_SPEED 800 // Velocidade dos inimigos em milissegundos
#define BLACK 0
#define DARK_BLUE 1
#define RED 4
#define WHITE 15
#define ORANGE 6
#define CYAN_BLUE 3

struct Character
{
    int x;
    int y;
    int lives;
};

struct Enemy
{
    int xEnemy;
    int yEnemy;
    int direction;
    int alive;
};

// Variáveis globais para controle do jogo
int matriz[L][C] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}};

char fixedCharMatriz[L][C] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'}};

int gameOver = 1;
struct Character character;
struct Enemy enemies[NUM_ENEMIES];
int pontuation = 0;
HANDLE hMutex;

char nickName[20];
int eny = 5;

// Função para limpar a console
void clearConsole()
{
    system("cls");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para exibir a matriz com caracteres
void displayMatriz()
{
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            gotoxy(j * 2, i);
            if (matriz[i][j] == ENEMY_SYMBOL)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                printf("E ");
            }
            else if (matriz[i][j] == CHAR_SYMBOL)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_LIGHT_YELLOW);
                printf("P ");
            }
            else if (matriz[i][j] == BOMB_SYMBOL)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ORANGE);
                printf("O ");
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
                printf("%c ", fixedCharMatriz[i][j]);
            }
        }
    }
    gotoxy(0, L);
    printf("Lives: %d\n", character.lives);
}

int checkVictory()
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        if (enemies[i].alive)
        {
            return 0; // Ainda há inimigos vivos
        }
    }
    eny = 0;
    gameOver = 0;
    savescore(pontuation);
    ver_score();
    return 1; // Todos os inimigos foram derrotados
}
// Função para verificar se uma posição é válida para colocar a bomba
int isValidBombPosition(int x, int y)
{
    if (x < 0 || x >= L || y < 0 || y >= C)
    {
        return 0;
    }
    return (matriz[x][y] == 0);
}

// Função para colocar a bomba ao lado do personagem
void placeBomb()
{
    if (isValidBombPosition(character.x, character.y + 1))
    {
        matriz[character.x][character.y + 1] = BOMB_SYMBOL;
    }
    else if (isValidBombPosition(character.x, character.y - 1))
    {
        matriz[character.x][character.y - 1] = BOMB_SYMBOL;
    }
    else if (isValidBombPosition(character.x + 1, character.y))
    {
        matriz[character.x + 1][character.y] = BOMB_SYMBOL;
    }
    else if (isValidBombPosition(character.x - 1, character.y))
    {
        matriz[character.x - 1][character.y] = BOMB_SYMBOL;
    }
}
int temParedeEntre(int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
    { // Movimento horizontal
        for (int j = (y1 < y2 ? y1 + 1 : y2 + 1); j < (y1 > y2 ? y1 : y2); j++)
        {
            if (matriz[x1][j] == 1)
            {
                return 1; // Há parede no caminho
            }
        }
    }
    else if (y1 == y2)
    { // Movimento vertical
        for (int i = (x1 < x2 ? x1 + 1 : x2 + 1); i < (x1 > x2 ? x1 : x2); i++)
        {
            if (matriz[i][y1] == 1)
            {
                return 1; // Há parede no caminho
            }
        }
    }
    return 0; // Não há parede no caminho
}

// Função para explodir a bomba, corrigida para verificar paredes
void explodeBomb(int bombX, int bombY)
{
    WaitForSingleObject(hMutex, INFINITE);

    matriz[bombX][bombY] = 0;

    for (int i = -BOMB_RANGE; i <= BOMB_RANGE; i++)
    {
        for (int j = -BOMB_RANGE; j <= BOMB_RANGE; j++)
        {
            int x = bombX + i;
            int y = bombY + j;

            if (x >= 0 && x < L && y >= 0 && y < C)
            {
                // Verifica se há uma parede entre a bomba e o alvo
                if (abs(i) + abs(j) > BOMB_RANGE || temParedeEntre(bombX, bombY, x, y))
                {
                    continue; // Pula para o próximo alvo se houver parede
                }

                if (matriz[x][y] == ENEMY_SYMBOL)
                {
                    // Mata o inimigo
                    for (int k = 0; k < NUM_ENEMIES; k++)
                    {
                        if (enemies[k].xEnemy == x && enemies[k].yEnemy == y && enemies[k].alive)
                        {
                            enemies[k].alive = 0;
                            pontuation++;
                            matriz[x][y] = 0; // Limpa a posição do inimigo morto
                            break;            // Sai do loop após matar o inimigo
                        }
                    }
                }
                else if (matriz[x][y] == CHAR_SYMBOL)
                {
                    // Diminui a vida do personagem
                    character.lives--;
                    if (character.lives == 0)
                    {
                        gameOver = 0;
                        savescore(pontuation);
                        ver_score();
                        exit(0);
                    }

                    // Move o personagem para a posição inicial
                    matriz[character.x][character.y] = 0;
                    character.x = 0;
                    character.y = 0;
                    matriz[character.x][character.y] = CHAR_SYMBOL;
                }
            }
        }
    }

    ReleaseMutex(hMutex);
}

// Função para verificar se há uma parede entre dois pontos

// Função para verificar vitória

// Função para mover os inimigos
DWORD WINAPI moveEnemies(LPVOID lpParam)
{
    while (1)
    {
        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            if (!enemies[i].alive)
                continue;

            int x = enemies[i].xEnemy;
            int y = enemies[i].yEnemy;
            int newX = x;
            int newY = y;

            WaitForSingleObject(hMutex, INFINITE);

            // Código para perseguir o personagem
            int dx = character.x - x;
            int dy = character.y - y;

            // Verifica se o inimigo está na mesma linha ou coluna
            // e a uma distância máxima de 2 casas vazias
            if ((dx == 0 && abs(dy) <= 3 && !temParedeEntre(x, y, character.x, character.y)) ||
                (dy == 0 && abs(dx) <= 3 && !temParedeEntre(x, y, character.x, character.y)))
            {
                // Move o inimigo em direção ao jogador
                if (dx > 0)
                    newX++;
                if (dx < 0)
                    newX--;
                if (dy > 0)
                    newY++;
                if (dy < 0)
                    newY--;
            }
            else
            {
                // Movimento aleatório caso não esteja perto do personagem
                matriz[x][y] = 0; // Limpa a posição atual do inimigo
                enemies[i].direction = rand() % 4;

                switch (enemies[i].direction)
                {
                case 0: // Movimento para cima
                    if (x > 0 && matriz[x - 1][y] == 0)
                    {
                        newX--;
                    }
                    break;
                case 1: // Movimento para baixo
                    if (x < L - 1 && matriz[x + 1][y] == 0)
                    {
                        newX++;
                    }
                    break;
                case 2: // Movimento para a esquerda
                    if (y > 0 && matriz[x][y - 1] == 0)
                    {
                        newY--;
                    }
                    break;
                case 3: // Movimento para a direita
                    if (y < C - 1 && matriz[x][y + 1] == 0)
                    {
                        newY++;
                    }
                    break;
                }
            }

            // Verifica se a nova posição já está ocupada por outro inimigo
            int posicaoLivre = 1;
            for (int j = 0; j < NUM_ENEMIES; j++)
            {
                if (j != i && enemies[j].xEnemy == newX && enemies[j].yEnemy == newY && enemies[j].alive)
                {
                    posicaoLivre = 0;
                    break;
                }
            }

            // Move o inimigo se a nova posição estiver livre
            if (posicaoLivre)
            {
                matriz[x][y] = 0;
                enemies[i].xEnemy = newX;
                enemies[i].yEnemy = newY;
                matriz[newX][newY] = ENEMY_SYMBOL;
            }

            // Verifica se o inimigo encontrou o personagem
            if (enemies[i].xEnemy == character.x && enemies[i].yEnemy == character.y)
            {
                character.lives--;
                if (character.lives == 0)
                {
                    gameOver = 0;
                    printf("\nGame Over");
                    savescore(pontuation);
                    ver_score();
                    exit(0);
                }
                else
                {
                    // Reinicia o personagem na posição inicial
                    matriz[character.x][character.y] = 0;
                    character.x = 0;
                    character.y = 0;
                    matriz[character.x][character.y] = CHAR_SYMBOL;
                }
            }

            ReleaseMutex(hMutex);
        }

        Sleep(ENEMY_SPEED);

        if (checkVictory())
        {
            printf("You Win!\n");
            Sleep(2000);
            exit(0);
        }
    }
    return 0;
}

// Função para mover o personagem
DWORD WINAPI moveCharacter(LPVOID lpParam)
{
    while (1)
    {
        if (_kbhit())
        {
            char input = _getch();
            int newX = character.x;
            int newY = character.y;

            switch (input)
            {
            case 'w': // Para cima
                newX--;
                break;
            case 's': // Para baixo
                newX++;
                break;
            case 'a': // Para a esquerda
                newY--;
                break;
            case 'd': // Para a direita
                newY++;
                break;
            case ' ': // Colocar bomba
                placeBomb();
                break;
            }

            // Verifica se a nova posição é válida
            if (newX >= 0 && newX < L && newY >= 0 && newY < C && matriz[newX][newY] == 0)
            {
                WaitForSingleObject(hMutex, INFINITE);
                matriz[character.x][character.y] = 0;
                character.x = newX;
                character.y = newY;
                matriz[character.x][character.y] = CHAR_SYMBOL;
                ReleaseMutex(hMutex);
            }
        }
        Sleep(100);
    }
    return 0;
}

// Função para verificar e explodir bombas no mapa
DWORD WINAPI checkBombs(LPVOID lpParam)
{
    while (1)
    {
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (matriz[i][j] == BOMB_SYMBOL)
                {
                    Sleep(2000); // Tempo para explosão da bomba
                    explodeBomb(i, j);
                }
            }
        }
        Sleep(100);
    }
    return 0;
}

int main()
{
    int option = 0;
    int a;

    srand(time(NULL));

    clearConsole();
    while (option != 2)
    {
        a = 1;
        option = menu();
        if (option == 1)
        {
            ver_score();
            printf("\nCLIQUE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL");
            while(a == 1)
            {
                if(_kbhit())
                {
                    a = 0;
                    clearConsole();
                }
            }
        }
    }
    printf("\n\n=========================== BEM VINDO =============================");
    Sleep(1500);
    printf("\n\n===========================   REGRAS  =============================");
    Sleep(1500);
    printf("\n\n1 - ELIMINE OS INIMIGOS PARA VENCER O JOGO ========================");
    Sleep(1500);
    printf("\n\n2 - AO APERTAR ESPAÇO VOCÊ COLOCA UMA BOMBA =======================");
    Sleep(1500);
    printf("\n\n3 - MOVIMENTOS PELAS TECLAS WASD ==================================");
    Sleep(1500);
    printf("\n\n4 - OS INIMIGOS TE SEGUEM E DÃO DANO SE ELES ESTIVEREM PERTO DE VOCÊ");
    Sleep(1900);
    printf("\n\n=========================== BOM JOGO ===============================");
    Sleep(1500);

    clearConsole();

    // Inicializa o personagem
    character.x = 0;
    character.y = 0;
    character.lives = INITIAL_LIVES;
    matriz[character.x][character.y] = CHAR_SYMBOL;

    // Inicializa os inimigos em posições aleatórias
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        enemies[i].alive = 1;
        do
        {
            enemies[i].xEnemy = rand() % L;
            enemies[i].yEnemy = rand() % C;
        } while (matriz[enemies[i].xEnemy][enemies[i].yEnemy] != 0);
        matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
    }

    // Cria um mutex para sincronização
    hMutex = CreateMutex(NULL, FALSE, NULL);

    // Cria threads para mover os inimigos, o personagem e verificar as bombas
    HANDLE hThreadEnemies = CreateThread(NULL, 0, moveEnemies, NULL, 0, NULL);
    HANDLE hThreadCharacter = CreateThread(NULL, 0, moveCharacter, NULL, 0, NULL);
    HANDLE hThreadBombs = CreateThread(NULL, 0, checkBombs, NULL, 0, NULL);

    // Loop principal do jogo para exibir a matriz
    while (gameOver == 1)
    {
        displayMatriz();
        Sleep(100);
    }
   
    Sleep(250);

    // Espera que as threads terminem antes de encerrar o programa
    WaitForSingleObject(hThreadEnemies, INFINITE);
    WaitForSingleObject(hThreadCharacter, INFINITE);
    WaitForSingleObject(hThreadBombs, INFINITE);

    CloseHandle(hThreadEnemies);
    CloseHandle(hThreadCharacter);
    CloseHandle(hThreadBombs);
    CloseHandle(hMutex);

    Sleep(250);
    return 0;
}
