#ifndef FUNCTII_CITIRE_H
#define FUNCTII_CITIRE_H

#define MAX_MASINI 10000
#define FILENAME "masini.txt"

typedef struct {
    char marca[20];
    char model[20];
    int km;
    int an;
    char caroserie[20];
    char culoare[20];
    char sasiu[20];
    float pret;
} Masina;

extern Masina masini[MAX_MASINI];
extern int numarMasini;

void incarcaMasiniDinFisier();
void salveazaMasiniInFisier();

#endif