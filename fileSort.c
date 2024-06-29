#include "fileSort.h"
#ifndef FILESORT_H
#define FILESORT_H

int main() {
    char name[20];
    double pontuation = 299;
    const char *filename = "players.txt";
    int numPlayers;
    Player *playerArray;

    printf("Enter your nick name: ");
    scanf("%s", name);

    // Adiciona alguns jogadores fictícios ao arquivo
    appendToFile(filename, name, pontuation);

    // Lê os jogadores do arquivo e armazena em um array dinâmico
    playerArray = readPlayersFromFile(filename, &numPlayers);
    if (playerArray == NULL) {
        printf("Failed to read players from file.\n");
        return 1;
    }

    // Ordena os jogadores em ordem decrescente de pontuação
    qsort(playerArray, numPlayers, sizeof(Player), comparePlayers);

    // Exibe os jogadores armazenados no array dinâmico
    displayPlayers(playerArray, numPlayers);

    // Libera a memória alocada para o array dinâmico
    free(playerArray);

    return 0;
}
#endif