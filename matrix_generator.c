#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 20
#define MAX_COLS 20

// ------------ Menü ------------

void menu() {
    printf("\n=== ---------------------- ===\n---- Spirál Matrix Program ----\n=== ---------------------- ===\n");
    printf("\n\n0 - Használati útmutató");
    printf("\n1 - Mátrix generálás");
    printf("\n2 - Mentés");
    printf("\n3 - Betöltés");
    printf("\n4 - Aktuális mátrix kiiratása");
    printf("\n5 - Kilépés");
}

// ------------ Használati útmutató ------------

void user_manual() {
    printf("Felhasználói kézikönyv\n");

    printf("\nMenüpontok:\n\n");
    printf("0: Használati útmutató: Kiírja a felhasználói kézikönyvet.\n\n");
    printf("1: Mátrix generálás: A felhasználótól bekéri a mátrix méretét,\naz indulási irányt (0: jobbra, 1: le, 2: balra, 3: fel) és a forgás irányát\n(0: óramutató járásával megegyezően, 1: óramutató járásával ellentétesen). Generál egy spirális mátrixot a megadott paraméterek alapján.\n\n");
    printf("2: Mentés: Elmenti a generált mátrixot egy fájlba.\nA fájl neve a mátrix méretét, indulási irányát és forgás irányát tartalmazza.\n\n");
    printf("3: Betöltés: Bekéri a felhasználótól a betölteni kívánt fájl nevét\nés betölti a mátrixot ebből a fájlból.\n\n");
    printf("4: Aktuális mátrix kiíratása: Kiírja a terminálra a jelenlegi mátrixot.\n\n");
    printf("5: Kilépés: Kilép a programból.\n\n\n");

    printf("A program működése:\n\n");
    printf("A felhasználó által megadott paraméterek alapján a program generál egy spirális mátrixot.\n\n");
    printf("A generált mátrixot el lehet menteni egy fájlba, majd később vissza lehet tölteni.\n\n");
    printf("A generált vagy betöltött mátrixot ki lehet íratni a terminálra.\n\n");
    printf("A program futása során a felhasználó bármikor kiléphet a 5-ös menüponttal.\n\n");
}

// ------------ Mátrix legenerálása ------------

int** generate_matrix(int n, int startDir, int spin) {

    int** matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }

    int value = 1;
    int i;
    int j;

    if (n % 2 == 1){
        i = n / 2;
        j = n / 2;
    }
    if (n % 2 == 0){
        if ((startDir == 1 && spin == 0) || (startDir == 2 && spin == 1)){
            i = n / 2 - 1;
            j = n / 2;
        }
        if ((startDir == 1 && spin == 1) || (startDir == 0 && spin == 0)){
            i = n / 2 - 1;
            j = n / 2 - 1;
        }
        if ((startDir == 3 && spin == 0) || (startDir == 0 && spin == 1)){
            i = n / 2;
            j = n / 2 - 1;
        }
        if ((startDir == 3 && spin == 1) || (startDir == 2 && spin == 0)){
            i = n / 2;
            j = n / 2;
        }
    }

    int dir = startDir;
    int step = 1;

    while (value <= n * n) {
        for (int k = 0; k < step; k++) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                matrix[i][j] = value;
            }
            value++;

            switch (dir) {
                case 0:
                    j++;
                    break;
                case 1:
                    i++;
                    break;
                case 2:
                    j--;
                    break;
                case 3:
                    i--;
                    break;
            }
        
        }

        if (spin == 0){
           dir = (dir + 1) % 4; 
        }
        else {
            dir = (dir + 3) % 4;
        }

        if (startDir == 0 || startDir == 2){
            if (dir == 0 || dir == 2) {
            step++;
        }
        }
        else {
            if (dir == 1 || dir == 3) {
            step++;
        }
        }
        
    }
    return matrix;
}
// ------------ Mátrix mentése ------------

void save_matrix(int N, int** matrix, char file_name[]) {
    FILE* file = fopen(file_name, "w");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j != N - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// ------------ Mátrix betöltése ------------

int** load_matrix(int* n, char* file_name) {
    const char* filename = file_name;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Hiba a fajl megnyitasakor.\n");
        return NULL;
    }

    int** matrix = (int**)malloc(MAX_ROWS * sizeof(int*));
    for (int i = 0; i < MAX_ROWS; i++) {
        matrix[i] = (int*)malloc(MAX_COLS * sizeof(int));
    }

    *n = 0;
    int cols = 0;

    while (fscanf(file, "%d", &matrix[*n][cols]) == 1) {
        cols++;
        char c = fgetc(file);
        if (c == '\n' || c == EOF) {
            (*n)++;
            cols = 0;
        }
    }
    fclose(file);
    return matrix;
}

// ------------ Mátrix kiiratása ------------

void print_matrix(int n, int** matrix) {
    printf("A mátrix elemei:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
// ------------ Main ------------

int main() {
    int choice;
    int** matrix = NULL;
    int n;
    int startDir;
    int spin;
    char file_name[50];
    char* direction;

    
    do {
        menu();
        printf("\n");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                user_manual();
                break;
            case 1:
                printf("Adja meg a mátrix méretét: ");
                scanf("%d", &n);

                printf("Adja meg az irányt (0: jobbra, 1: le, 2: balra, 3: fel): ");
                scanf("%d", &startDir);

                printf("Adja meg a forgás irányát (0: cw, 1: ccw): ");
                scanf("%d", &spin);

                matrix = generate_matrix(n, startDir, spin);
                break;
            case 2:
                if (startDir == 0){
                    direction = 'j';     //javítás
                }
                if (startDir == 1){
                    direction = 'l';
                }
                if (startDir == 2){
                    char direction[5] = "balra";
                }
                if (startDir == 3){
                    char direction[5] = "fel";
                }
                sprintf(file_name, "spiral%d%s%d.txt", n, direction, spin);
                if (matrix != NULL) {
                    save_matrix(n, matrix, file_name);
                } else {
                    printf("Nincs még létrehozott mátrix.\n");
                }
                break;
            case 3:
                printf("Addja meg a betölteni kívánt fájlt!\n");
                scanf("%s", file_name);
                matrix = load_matrix(&n, file_name);
                break;
            case 4:
                if (matrix != NULL) {
                    print_matrix(n, matrix);
                } else {
                    printf("Nincs még létrehozott mátrix.\n");
                }
                break;
            case 5:
                break;
            default:
                printf("Érvénytelen bemenet.");
                break;
        }
    } while (choice != 5);

    if (matrix != NULL) {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    return 0;
}