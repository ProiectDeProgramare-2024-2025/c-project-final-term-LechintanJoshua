#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_citire.h"

Masina masini[MAX_MASINI];
int numarMasini = 0;

void incarcaMasiniDinFisier() {
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("Eroare la deschiderea fisierului! Se va folosi lista implicita.\n");

        Masina defaultMasini[] = {
            {"BMW", "E9", 24867, 1972, "sedan", "alb", "bmwfjsn2nfds0", 29000.0}, 
            {"Porsche", "Cayman", 24000, 2017, "coupe", "negru", "djdkaooncvi2", 71000.0},
            {"Toyota", "Yaris", 120000, 2021, "sedan", "gri", "tofuyandf192nf", 8000.0}
        };

        memcpy(masini, defaultMasini, sizeof(defaultMasini));
        numarMasini = 3;
        return;
    }

    numarMasini = 0;

    while (fscanf(file, "%19[^,],%19[^,],%d,%d,%19[^,],%19[^,],%19[^,],%f\n",
                 masini[numarMasini].marca,
                 masini[numarMasini].model,
                 &masini[numarMasini].km,
                 &masini[numarMasini].an,
                 masini[numarMasini].caroserie,
                 masini[numarMasini].culoare,
                 masini[numarMasini].sasiu,
                 &masini[numarMasini].pret) == 8) {
        numarMasini++;

        if (numarMasini >= MAX_MASINI) break;
    }

    fclose(file);
}

void salveazaMasiniInFisier() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului pentru salvare!\n");
        return;
    }

    for (int i = 0; i < numarMasini; i++) {
        fprintf(file, "%s,%s,%d,%d,%s,%s,%s,%.2f\n",
                masini[i].marca,
                masini[i].model,
                masini[i].km,
                masini[i].an,
                masini[i].caroserie,
                masini[i].culoare,
                masini[i].sasiu,
                masini[i].pret);
    }

    fclose(file);
}