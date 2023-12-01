#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Space {
    int start;
    int end;
    struct Space *next;
} Space;

void initializeMemory(Space **memory) {
    srand(time(0));
    *memory = (Space *) malloc(sizeof(Space));
    (*memory)->start = 0;
    (*memory)->end = rand() % 100 + 50;
    (*memory)->next = NULL;
}

void addSpace(Space **memory, int start, int end) {
    Space *newSpace = (Space *) malloc(sizeof(Space));
    newSpace->start = start;
    newSpace->end = end;
    newSpace->next = *memory;
    *memory = newSpace;
}

void firstFit(Space **memory, int size) {
    Space *current = *memory;
    while (current != NULL) {
        if (current->end - current->start + 1 >= size) {
            printf("Alocação realizada com sucesso!\n");
            addSpace(memory, current->start, current->start + size - 1);
            return;
        }
        current = current->next;
    }
    printf("Não foi possível encontrar um espaço livre suficiente.\n");
}

void bestFit(Space **memory, int size) {
    Space *current = *memory;
    Space *bestSpace = NULL;
    int bestSize = 999999;
    while (current != NULL) {
        if (current->end - current->start + 1 >= size && current->end - current->start + 1 - size < bestSize) {
            bestSize = current->end - current->start + 1 - size;
            bestSpace = current;
        }
        current = current->next;
    }
    if (bestSpace != NULL) {
        printf("Alocação realizada com sucesso!\n");
        addSpace(memory, bestSpace->start, bestSpace->start + size - 1);
    } else {
        printf("Não foi possível encontrar um espaço livre suficiente.\n");
    }
}

void printMemory(Space *memory) {
    Space *current = memory;
    while (current != NULL) {
        printf("Espaço: %d a %d\n", current->start, current->end);
        current = current->next;
    }
}

int main() {
    Space *memory = NULL;
    int choice, size;
    initializeMemory(&memory);
    while (1) {
        printf("Escolha uma estratégia (1-First-Fit, 2-Best-Fit, 3-Sair): ");
        scanf("%d", &choice);
        if (choice == 3) {
            break;
        }
        printf("Informe o tamanho da ocupação desejada: ");
        scanf("%d", &size);
        if (choice == 1) {
            firstFit(&memory, size);
        } else if (choice == 2) {
            bestFit(&memory, size);
        }
        printMemory(memory);
    }
    return 0;
}
