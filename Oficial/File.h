#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 256

struct Player {
    char nickName[15];
    int pontuation;
};

// Função de ordenação por Insertion Sort para struct Player
struct Player *insertionSort(struct Player *arr, int len) {
    int i, j;
    struct Player key;

    for (i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;

        // Move os elementos do array que são maiores que key para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j].pontuation < key.pontuation) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return arr;
}

// Função auxiliar para exibir os jogadores
void displayPlayers(struct Player *players, int numPlayers) {
    printf("RANKING:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d\n", players[i].nickName, players[i].pontuation);
    }
}

void savescore(int pontuation)
{
    char nickName[20];
    printf("\n\nENTER YOUR NICK NAME: ");
    scanf("%s", nickName);
    FILE *f;
    char url[] = "Score.txt";
    f = fopen(url, "a");
    fprintf(f,"\n%s : %i", nickName, pontuation);
    fclose(f);
}

void ver_score() {
FILE *f;
char url[] = "Score.txt";
f = fopen(url, "r");

if (f == NULL) {
    printf("Erro ao abrir o arquivo %s.\n", url);
    return;
}

// Inicialização da lista de jogadores
struct Player *players = NULL;
int count = 0;
char buffer[MAX_LENGTH];

// Lê cada linha do arquivo
while (fgets(buffer, MAX_LENGTH, f)) {
    // Aloca espaço para mais um jogador na lista
    players = realloc(players, (count + 1) * sizeof(struct Player));
    if (players == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(f);
        return;
    }

    // Extrai nome e pontuação da linha lida
    if (sscanf(buffer, "%s : %d", players[count].nickName, &players[count].pontuation) == 2) {
        count++;
    } else {
        printf("\n");
    }
}

fclose(f);

// Ordena os jogadores por pontuação
insertionSort(players, count);

displayPlayers(players, count);

// Libera a memória alocada para a lista de jogadores
free(players);
}   