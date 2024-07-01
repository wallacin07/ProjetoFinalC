#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define L 9
#define C 15
#define ENEMY_SYMBOL 'E'
#define CHAR_SYMBOL 'P'
#define BOMB_SYMBOL 'O'
#define NUM_ENEMIES 5
#define BOMB_RANGE 2
#define INITIAL_LIVES 3
#define ENEMY_SPEED 800 // Velocidade dos inimigos em milissegundos
#define BOMB_DURATION 2000 // Duração da bomba em milissegundos

int pontuation = 0;
int numEnemies = 5;
char nickName[20];

//limpa a tela
void clearWin() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

struct Character {
    int x;
    int y;
    int lives;
};

struct Enemy {
    int xEnemy;
    int yEnemy;
    int direction;
    int alive;
};

struct Bomb {
    int x;
    int y;
    int active;
    clock_t placedTime;
};

struct Player {
    char nickName[15];
    int pontuation;
};

// Variáveis globais para controle do jogo
int matriz[L][C] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char fixedCharMatriz[L][C] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};

struct Character character;
struct Enemy enemies[NUM_ENEMIES];
struct Bomb bomb = { -1, -1, 0, 0 };

HANDLE hMutex;

// Função para mover o cursor do console para uma posição específica
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para exibir a matriz com caracteres
void displayMatriz() {
    gotoxy(0, 0); // Move o cursor para o início da tela
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (matriz[i][j] == ENEMY_SYMBOL) {
                printf("E ");
            } else if (matriz[i][j] == CHAR_SYMBOL) {
                printf("P ");
            } else if (matriz[i][j] == BOMB_SYMBOL) {
                printf("O ");
            } else {
                printf("%c ", fixedCharMatriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("Lives: %d\n", character.lives);
}

// Função para verificar se uma posição é válida para colocar a bomba
int isValidBombPosition(int x, int y) {
    if (x < 0 || x >= L || y < 0 || y >= C) {
        return 0;
    }
    return (matriz[x][y] == 0);
}

// Função para colocar a bomba ao lado do personagem
void placeBomb() {
    if (!bomb.active) {
        if (isValidBombPosition(character.x, character.y + 1)) {
            bomb.x = character.x;
            bomb.y = character.y + 1;
        } else if (isValidBombPosition(character.x, character.y - 1)) {
            bomb.x = character.x;
            bomb.y = character.y - 1;
        } else if (isValidBombPosition(character.x + 1, character.y)) {
            bomb.x = character.x + 1;
            bomb.y = character.y;
        } else if (isValidBombPosition(character.x - 1, character.y)) {
            bomb.x = character.x - 1;
            bomb.y = character.y;
        }

        if (bomb.x != -1 && bomb.y != -1) {
            matriz[bomb.x][bomb.y] = BOMB_SYMBOL;
            bomb.active = 1;
            bomb.placedTime = clock();
        }
    }
}

// Função para verificar se há uma parede entre dois pontos
int temParedeEntre(int x1, int y1, int x2, int y2) {
    if (x1 == x2) { // Movimento horizontal
        for (int j = (y1 < y2 ? y1 + 1 : y2 + 1); j < (y1 > y2 ? y1 : y2); j++) {
            if (matriz[x1][j] == 1) {
                return 1; // Há parede no caminho
            }
        }
    } else if (y1 == y2) { // Movimento vertical
        for (int i = (x1 < x2 ? x1 + 1 : x2 + 1); i < (x1 > x2 ? x1 : x2); i++) {
            if (matriz[i][y1] == 1) {
                return 1; // Há parede no caminho
            }
        }
    }
    return 0; // Não há parede no caminho
}

// Função para explodir a bomba
void explodeBomb() {
    if (bomb.active && ((clock() - bomb.placedTime) >= BOMB_DURATION)) {
        WaitForSingleObject(hMutex, INFINITE);

        matriz[bomb.x][bomb.y] = 0;

        for (int i = -BOMB_RANGE; i <= BOMB_RANGE; i++) {
            for (int j = -BOMB_RANGE; j <= BOMB_RANGE; j++) {
                int x = bomb.x + i;
                int y = bomb.y + j;

                if (x >= 0 && x < L && y >= 0 && y < C) {
                    // Verifica se há uma parede entre a bomba e o alvo
                    if (abs(i) + abs(j) > BOMB_RANGE || temParedeEntre(bomb.x, bomb.y, x, y)) {
                        continue; // Pula para o próximo alvo se houver parede
                    }

                    if (matriz[x][y] == ENEMY_SYMBOL) {
                        // Mata o inimigo
                        for (int k = 0; k < NUM_ENEMIES; k++) {
                            if (enemies[k].xEnemy == x && enemies[k].yEnemy == y && enemies[k].alive) {
                                enemies[k].alive = 0;
                                matriz[x][y] = 0;
                                numEnemies --;
                                pontuation ++;
                                 // Limpa a posição do inimigo morto
                                break; // Sai do loop após matar o inimigo
                            }
                        }
                    } else if (x == character.x && y == character.y) {
                        // Diminui a vida do personagem
                        character.lives--;
                        if (character.lives <= 0) {
                            printf("\n\nGAME OVER!\n\nYour pontuation is: %d\n", pontuation);
                            saveScore("Game Over", &nickName);
                            exit(0); // Encerra o jogo
                        }
                    }
                    else if(numEnemies == 0)
                    {
                        printf("YOU WIN!\n\nYour pontuation is: %d", pontuation);
                        saveScore("You win", &nickName);
                        exit(0); 
                    }
                }
            }
        }

        bomb.active = 0;
        bomb.x = -1;
        bomb.y = -1;

        ReleaseMutex(hMutex);
    }
}

// Função para mover o personagem
void moveCharacter(int dx, int dy) {
    int newX = character.x + dx;
    int newY = character.y + dy;

    // Verifica se a nova posição é válida
    if (newX >= 0 && newX < L && newY >= 0 && newY < C && matriz[newX][newY] == 0) {
        // Limpa a posição atual do personagem na matriz
        matriz[character.x][character.y] = 0;

        // Atualiza as coordenadas do personagem
        character.x = newX;
        character.y = newY;

        // Coloca o símbolo do personagem na nova posição na matriz
        matriz[character.x][character.y] = CHAR_SYMBOL;
    }
    // Se não for possível mover, mantém o personagem na posição atual
    else {
        // Garante que a posição atual do personagem na matriz seja CHAR_SYMBOL
        matriz[character.x][character.y] = CHAR_SYMBOL;
    }
}

// Função para mover os inimigos
DWORD WINAPI moveEnemies() {
    while (1) {
        Sleep(ENEMY_SPEED);
        WaitForSingleObject(hMutex, INFINITE);

        for (int i = 0; i < NUM_ENEMIES; i++) {
            if (enemies[i].alive) {
                int newX = enemies[i].xEnemy;
                int newY = enemies[i].yEnemy;

                // Direção do movimento
                switch (enemies[i].direction) {
                    case 0: newX++; break; // Baixo
                    case 1: newX--; break; // Cima
                    case 2: newY++; break; // Direita
                    case 3: newY--; break; // Esquerda
                }

                // Verifica se a nova posição é válida
                if (newX >= 0 && newX < L && newY >= 0 && newY < C && matriz[newX][newY] == 0) {
                    matriz[enemies[i].xEnemy][enemies[i].yEnemy] = 0; // Limpa a posição atual
                    enemies[i].xEnemy = newX;
                    enemies[i].yEnemy = newY;
                    matriz[newX][newY] = ENEMY_SYMBOL; // Atualiza para a nova posição
                } else {
                    // Muda a direção do inimigo se houver obstáculo
                    enemies[i].direction = rand() % 4;
                }
            }
        }

        ReleaseMutex(hMutex);
    }
    return 0;
}

void displayScores() {
    FILE *file = fopen("dados.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Player *players = NULL;
    int count = 0;
    while (!feof(file)) {
        players = realloc(players, sizeof(struct Player) * (count + 1));
        if (fscanf(file, "%s %d", players[count].nickName, &players[count].pontuation) == 2) {
            count++;
        }
    }
    fclose(file);

    printf("\nRANKING:\n");
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", players[i].nickName, players[i].pontuation);
    }

    free(players);
}

void saveScore(char* result, char *nickName[20]) {
    // char nickName[15];
    // printf("\n\nEnter your nickname: ");
    // scanf("%s", nickName);

    FILE *file = fopen("dados.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s %d\n", nickName, pontuation);
    fclose(file);

    printf("%s\n", result);
    displayScores();
}

// Função principal
int main() {

    printf("\n\nENTER YOUR NICK NAME: ");
    scanf("%s", nickName);

    clearWin();

    character.x = 0;
    character.y = 0;
    character.lives = INITIAL_LIVES;
    matriz[character.x][character.y] = CHAR_SYMBOL;

    srand(time(NULL));

    for (int i = 0; i < NUM_ENEMIES; i++) {
        int enemyX, enemyY;
        do {
            enemyX = rand() % L;
            enemyY = rand() % C;
        } while (matriz[enemyX][enemyY] != 0);

        enemies[i].xEnemy = enemyX;
        enemies[i].yEnemy = enemyY;
        enemies[i].direction = rand() % 4;
        enemies[i].alive = 1;
        matriz[enemyX][enemyY] = ENEMY_SYMBOL;
    }

    hMutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE hThread = CreateThread(NULL, 0, moveEnemies, NULL, 0, NULL);

    while (1) {
        if (_kbhit()) {
            char ch = getch(); // Captura a tecla pressionada

            switch (ch) {
                case 'w': moveCharacter(-1, 0); break;
                case 's': moveCharacter(1, 0); break;
                case 'a': moveCharacter(0, -1); break;
                case 'd': moveCharacter(0, 1); break;
                case ' ': placeBomb(); break; // Coloca a bomba quando a tecla de espaço é pressionada
            }
        }

        explodeBomb();
        displayMatriz();
        Sleep(100);
    }

    CloseHandle(hThread);
    CloseHandle(hMutex);

    return 0;
}
