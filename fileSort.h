#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char playerName[20];
    int playerScore;
} Player;

void appendToFile(const char *filename, const char *name, int score) {
    FILE *file = fopen(filename, "a"); // "a" abre o arquivo para escrita no final (append)
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(file, "%s %d\n", name, score); // Escreve o nome e a pontuação no arquivo
    fclose(file); // Fecha o arquivo
}

Player *readPlayersFromFile(const char *filename, int *count) {
    FILE *file = fopen(filename, "r"); // "r" abre o arquivo para leitura
    if (file == NULL) {
        printf("Could not open file %s for reading.\n", filename);
        return NULL;
    }

    // Conta quantos jogadores existem no arquivo
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        (*count)++;
    }

    // Aloca memória para armazenar os jogadores
    Player *players = (Player*)malloc(*count * sizeof(Player));
    if (players == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Retorna ao início do arquivo para leitura
    fseek(file, 0, SEEK_SET);

    // Lê os jogadores do arquivo
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d", players[i].playerName, &players[i].playerScore);
        i++;
    }

    fclose(file); // Fecha o arquivo
    return players;
}

int comparePlayers(const void *a, const void *b) {
    const Player *playerA = (const Player *)a;
    const Player *playerB = (const Player *)b;

    // Ordena em ordem decrescente (maior para menor) pela pontuação
    return playerB->playerScore - playerA->playerScore;
}

void displayPlayers(Player *players, int count) {
    printf("Players in descending order of score:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Score: %d\n", players[i].playerName, players[i].playerScore);
    }
}