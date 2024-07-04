#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h> // Para size_t

// Função genérica de troca de elementos
void swap(void *a, void *b, size_t size) {
    char *temp = (char *)malloc(size);
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

// Função genérica do Quick Sort
void quickSort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *)) {
    if (num <= 1) return;

    char *pivot = base + (num / 2) * size;
    char *left = base;
    char *right = base + (num - 1) * size;

    while (left <= right) {
        while (compare(left, pivot) < 0) {
            left += size;
        }
        while (compare(right, pivot) > 0) {
            right -= size;
        }
        if (left <= right) {
            swap(left, right, size);
            left += size;
            right -= size;
        }
    }

    quickSort(base, (right - (char *)base) / size + 1, size, compare);
    quickSort(left, ((char *)base + num * size - left) / size, size, compare);
}

#endif /* QUICK_SORT_H */
