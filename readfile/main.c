#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "list.h"

int main (int argc, char ** argv) {
    FILE *plik;
    char znak;
    int n; //liczba instrukcji
    int k; //licznik
    int arg1, arg2; //argumentu do komend i, d
    int get; // check do fscanf

    List *lista;
    lista = create_list();

    plik = fopen(argv[1], "r");
    if(plik == NULL) {
        printf("B³ad otwarcia pliku %s\n", strerror(errno));
    }

    //wczytujemy iloœæ instrukcji
    get = fscanf(plik, "%d ", &n);
    if(get != 1) {
        printf("B³ad odczytu liczby instrukcji");
        exit(-1);
    }
    if(n <= 0) {
        printf("Brak instrukcji do wykonania");
        return 0;
    }
    printf("Iloœæ argumentow to: %d\n", n);

    for(k = 0; k < n; k++) {
        get = fscanf(plik, "%c ", &znak);
        if(get != 1) {
            printf("B³ad odczytu instrukcji");
            exit(-1);
        }

        switch(znak) {
            //0 - argumentowe
            case 'p': print_list(lista); break;
            case 'c': clear_list(lista); break;
            case 'r': reverse_list(lista); break;
            case 's': sort_list(lista); break;

            //1 - argumentowe

            case 'a':
                get = fscanf(plik, "%d ", &arg1);
                if(get != 1) {
                    printf("B³ad odczytu argumentow instrukcji append");
                    exit(-1);
                }
                append_to_list(lista, arg1);
                break;

            case 'd':
                get = fscanf(plik, "%d ", &arg1);
                if(get != 1) {
                    printf("B³ad odczytu argumentow instrukcji delete");
                    exit(-1);
                }
                remove_nth_element(lista, arg1);
                break;

            //2 - argumentowe

            case 'i':
                get = fscanf(plik, "%d %d ", &arg1, &arg2);
                if(get != 2) {
                    printf("B³ad odczytu argumentow instrukcji insert_to_list");
                    exit(-1);
                }
                insert_to_list(lista, arg2, arg1);
                break;

            default :
                printf("Nieznana opcja");
                exit(-1);
                break;
        } // end switch
    } // end for
} // end main

