#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//valgrind --leak-check=full ./list
//dodatkowe funkcje
void print_list(List * list);
void present_list(List * list);

int main() {



    int k,p = 1;
	const int rozmiar_l1 = 12;
	const int rozmiar_l2 = 8;

    List * lista_1 = create_list();
    List * lista_2 = create_list();
	List * lista_3 = create_list();
	//dodajemy elementy do listy1
    for(k = 0; k < rozmiar_l1; k++) {
        append_to_list(lista_1, p % 13);
		p *= 2;
    }
    //dodajemy elementy do listy2
	for(k = 0; k < rozmiar_l2; k++) {
        append_to_list(lista_2, 2*k);
    }

	printf("\nElementy listy 1:\n\n");
	
	for(k = 0; k < rozmiar_l1; k++) {
		printf("Element nr %d: %d\n", k,get_nth_element(lista_1, k));
    }
    printf("\nElementy listy 2:\n\n");
	
    for(k = 0; k < rozmiar_l2; k++) {
		printf("Element nr %d: %d\n", k,get_nth_element(lista_2, k));
    }
    
    printf("\nOdwracamy listę 2\n\n");
	reverse_list(lista_2);
	
	printf("Elementy listy 2 :\n\n");
	for(k = 0; k < rozmiar_l2; k++) {
		printf("Element nr %d: %d\n", k,get_nth_element(lista_2, k));
    }
    
    printf("\nSortujemy listę 1\n");
	sort_list(lista_1);
	
	printf("\nLista 1 po sortowaniu: \n");
	
	for(k = 0; k < rozmiar_l1; k++) {
		printf("Element nr %d: %d\n", k,get_nth_element(lista_1, k));
    }

	clear_list(lista_1);
	clear_list(lista_2);

	insert_to_list(lista_3,5,0);
	insert_to_list(lista_3,7,0);
	insert_to_list(lista_3,9,1);
	printf("\n");
	present_list(lista_3);
	
	destroy_list(&lista_1);
	destroy_list(&lista_2);
	destroy_list(&lista_3);
    return 0;
}
