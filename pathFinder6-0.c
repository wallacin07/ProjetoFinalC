#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Para sleep em sistemas Unix-like

#define L 9
#define C 15
#define ENEMY_SYMBOL 22
#define CHAR_SYMBOL 10
#define NUM_ENEMIES 5

struct Enemy {
    int xEnemy;
    int yEnemy;
    int direction;
};

//limpa a tela
void clearWin() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void generatePosition(int matriz[L][C], struct Enemy enemies[], int numEnemies, int *xCharc, int *yCharc) {
    srand(time(NULL));
    
    // Gerar posições para os inimigos
    // para cada item gera uma posição diferente  para cada inimigo e acrescenta na lista
    for (int i = 0; i < numEnemies; i++) {
        enemies[i].xEnemy = rand() % L;  // line
        enemies[i].yEnemy = rand() % C; // column
        enemies[i].direction = rand() % 4; // Direção inicial aleatória
        matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
    }
    
    // Gera a posição para o protagonista 
    *xCharc = rand() % L;
    *yCharc = rand() % C;
    matriz[*xCharc][*yCharc] = CHAR_SYMBOL;
}

// mostrar a matriz
void displayMatriz(int matriz[L][C]) {
    clearWin();
    printf("\n");
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
}

//move os inimigos
void moveEnemies(int matriz[L][C], struct Enemy enemies[], int numEnemies, int xCharc, int yCharc) {
    while (1) {
        // Verifica se algum inimigo alcançou o personagem
        for (int i = 0; i < numEnemies; i++) {
            if (enemies[i].xEnemy == xCharc && enemies[i].yEnemy == yCharc) {
                printf("YOU LOSE!\n");
                return;
            }
        }

        // Movimenta todos os inimigos simultaneamente
        for (int i = 0; i < numEnemies; i++) {
            int x = enemies[i].xEnemy;
            int y = enemies[i].yEnemy;

            // Limpa a posição atual do inimigo na matriz
            matriz[x][y] = 0;

            // Define uma nova direção aleatória para o inimigo
            enemies[i].direction = rand() % 4;

            // Movimenta o inimigo na nova direção, se possível
            switch (enemies[i].direction) {
                case 0: // Movimento para cima top
                    if (x > 0 && (matriz[x - 1][y] == 0 || matriz[x - 1][y] == CHAR_SYMBOL)) {
                        enemies[i].xEnemy--;
                    }
                    break;
                case 1: // Movimento para baixo down
                    if (x < L - 1 && (matriz[x + 1][y] == 0 || matriz[x + 1][y] == CHAR_SYMBOL)) {
                        enemies[i].xEnemy++;
                    }
                    break;
                case 2: // Movimento para a esquerda left
                    if (y > 0 && (matriz[x][y - 1] == 0 || matriz[x][y - 1] == CHAR_SYMBOL)) {
                        enemies[i].yEnemy--;
                    }
                    break;
                case 3: // Movimento para a direita right
                    if (y < C - 1 && (matriz[x][y + 1] == 0 || matriz[x][y + 1] == CHAR_SYMBOL)) {
                        enemies[i].yEnemy++;
                    }
                    break;
            }

            // Atualiza a posição do inimigo na matriz
            matriz[enemies[i].xEnemy][enemies[i].yEnemy] = ENEMY_SYMBOL;
        }

        // Mostra a matriz atualizada
        displayMatriz(matriz);

        sleep(1); // Espera 1 segundo entre cada movimento
    }
}

int main() {
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

    struct Enemy enemies[NUM_ENEMIES];
    int xCharc, yCharc;

    generatePosition(matriz, enemies, NUM_ENEMIES, &xCharc, &yCharc);
    displayMatriz(matriz);
    moveEnemies(matriz, enemies, NUM_ENEMIES, xCharc, yCharc);

    return 0;
}
