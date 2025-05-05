#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "functii_afisare.h"
#include "functii_citire.h"

int main() {
    incarcaMasiniDinFisier();
    
    int choice;
    while (true) {
        stergereEcran();
        meniuPrincipal();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                vizualizareOferte();
                break;
            case 2:
                adaugaAnunt();
                salveazaMasiniInFisier();
                break;
            case 3:
                exit(0);
            default:
                gresit();
                break;
        }
    }
    return 0;
}


//rm -f program main.o functii.o
//gcc main.c functii_citire.c -o program
//gcc main.c functii_citire.c functii_afisare.c -o program
