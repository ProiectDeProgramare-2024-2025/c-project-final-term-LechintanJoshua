#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "functii_afisare.h"
#include "functii_citire.h"
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define BOLD    "\033[1m"

int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void stergereEcran() {
    system("clear");
}

bool verificareLitere (char *text) {
    for (int i = 0; i < strlen (text); ++i) {
        if (!((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))) {
            return false;
        }
    }

    return true;
}

bool interval (int val, int min, int max) {
    return (val >= min && val <= max);
}

bool suntDoarCifre(const char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

void print_centered(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    
    if (padding > 0) {
        printf("%*s%s\n", padding, "", text);
    } else {
        printf("%s\n", text);
    }
}

void meniuPrincipal() {
    int width = get_terminal_width();
    print_centered("|=====>Meniu principal<=====|\n", width);
    printf("1. Vizualizeaza oferte.\n");
    printf("2. Adauga un anunt.\n");
    printf("3. Iesire\n");
    printf("\nIntroduceti optiunea: ");
}

void filtrare() {
    stergereEcran();
    int width = get_terminal_width();
    print_centered("|=====>Filtrare<=====|\n", width);
    printf("1. Pret crescator.\n");
    printf("2. Pret descrescator.\n");
    printf("3. An fabricatie crescator.\n");
    printf("4. An fabricatie descrescator.\n");
    printf("5. Nume marca.\n");
    printf("Presupunem ca am ales o optiune si iesim din submeniu apasand enter.\n");
    getchar();
    getchar();
}

// void vizualizareOferte() {
//     stergereEcran();
//     int width = get_terminal_width();
//     print_centered("|=====>Oferte<=====|\n", width);
    
//     printf("0. Filtrare lista.\n");
//     for (int i = 0; i < numarMasini; ++i) {
//         printf("%d. Marca: %s, model: %s, km: %d, an: %d, carosierie: %s, culoare: %s, sasiu: %s, pret: %.2f\n",
//         i + 1, masini[i].marca, masini[i].model, masini[i].km, masini[i].an, 
//         masini[i].caroserie, masini[i].culoare, masini[i].sasiu, masini[i].pret);
//     }

//     printf("Introduceti 0 pentru filtrare sau altceva pentru iesirea din meniu.\n");
//     int a = -1;
//     scanf("%d", &a);

//     if (a == 0) {
//         filtrare();
//     } else {
//         printf("Apasati enter pentru a iesi din meniu.\n");
//     }
    
//     while (getchar() != '\n');
//     getchar();
// }

void vizualizareOferte() {
    stergereEcran();
    int width = get_terminal_width();
    print_centered(BOLD BLUE "|=====> OFERTE DISPONIBILE <=====|" RESET "\n", width);
    
    printf(BOLD YELLOW "0. Filtrare lista\n" RESET);
    for (int i = 0; i < numarMasini; ++i) {
        printf(
            "%d. " BOLD "Marca: " RESET GREEN "%s" RESET ", "
            BOLD "Model: " RESET YELLOW "%s" RESET ", "
            BOLD "KM: " RESET CYAN "%d" RESET ", "
            BOLD "An: " RESET MAGENTA "%d" RESET ", "
            BOLD "Caroserie: " RESET WHITE "%s" RESET ", "
            BOLD "Culoare: " RESET RED "%s" RESET ", "
            BOLD "Sasiu: " RESET CYAN "%s" RESET ", "
            BOLD "Pret: " RESET GREEN "%.2f EUR" RESET "\n",
            i + 1,
            masini[i].marca,
            masini[i].model,
            masini[i].km,
            masini[i].an,
            masini[i].caroserie,
            masini[i].culoare,
            masini[i].sasiu,
            masini[i].pret
        );
    }

    printf("\n" BOLD "Introduceti 0 pentru filtrare sau orice alt numar pentru a iesi: " RESET);
    int a = -1;
    scanf("%d", &a);

    if (a == 0) {
        filtrare();
    } else {
        printf(BOLD GREEN "\nApasati enter pentru a reveni..." RESET);
    }
    
    while (getchar() != '\n');
    getchar();
}

void adaugaAnunt() {
    int a = 1;
    while (a == 1) {
        stergereEcran();
        int width = get_terminal_width();
        print_centered("|=====>Adauga Anunt<=====|\n", width);
        
        if (numarMasini >= MAX_MASINI) {
            printf("Ati atins numarul maxim de masini!\n");
            break;
        }

        do {
            printf ("Marca: ");
            scanf("%19s", masini[numarMasini].marca);

            while (getchar() != '\n');

            if (!verificareLitere(masini[numarMasini].marca)) {
                printf ("Greseala! Marca trebuie sa contina doar litere!\n");
            } 
        } while (!verificareLitere(masini[numarMasini].marca));

        printf("Model: ");
        scanf("%19s", masini[numarMasini].model);
        while (getchar() != '\n');

        do {
            printf ("Kilometraj: ");
            scanf("%d", &masini[numarMasini].km);

            while (getchar() != '\n');

            if (masini[numarMasini].km < 10) {
                printf("Greseala! Kilometrajul trebuie sa contina doar cifre si valoarea acestuia sa fie >= 10!\n");
            }
        } while (masini[numarMasini].km < 10);

        do {
            printf("An: ");
            scanf("%d", &masini[numarMasini].an);

            while(getchar() != '\n');
            
            if(masini[numarMasini].an < 1960) {
                printf("Greseala! Anul trebuie sa fie cel putin 1960!\n");
            }
        } while(masini[numarMasini].an < 1960);


        do {
            printf("Caroserie: "); // verificare litere
            scanf("%19s", masini[numarMasini].caroserie);
            
            while(getchar() != '\n');
        
            if (!verificareLitere (masini[numarMasini].caroserie)) {
                printf("Greseala! Caroseria trebuie sa contina doar litere!\n");
            }
        } while (!verificareLitere (masini[numarMasini].caroserie));

        do {
            printf ("Culoare: ");
            scanf("%19s", masini[numarMasini].culoare);

            while (getchar() != '\n');

            if (!verificareLitere(masini[numarMasini].culoare)) {
                printf ("Greseala! Culoarea trebuie sa contina doar litere!\n");
            } 
        } while (!verificareLitere(masini[numarMasini].culoare));

        printf("Sasiu: ");
        scanf("%19s", masini[numarMasini].sasiu);
        while(getchar() != '\n');

        do {
            printf("Pret: ");
            scanf("%f", &masini[numarMasini].pret);

            while(getchar() != '\n');

            if(masini[numarMasini].pret <= 0) {
                printf("Greseala! Pretul trebuie sa fie pozitiv si sa contina doar cifre!\n");
            }
        } while(masini[numarMasini].pret <= 0);

        numarMasini++;
        
        printf("Anuntul a fost adaugat cu succes!\n");
        printf("Apasati 1 daca doriti sa mai adaugati un anunt, altfel orice alt numar: ");
        
        if (scanf("%d", &a) != 1) {  
            a = 0;  
        }

        while (getchar() != '\n');
    }
}

void gresit() {
    stergereEcran();
    printf("Nu ati introdus o optiune corecta\n");
    printf("Apasa enter pentru a continua: ");
    getchar();
    getchar();
    stergereEcran();
}