#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define KOMENTARZ 1
#define prezentuj
//#define check_get_nth_element
#define test_remove_nth_element
//#define test_insert_to_list
//valgrind --leak-check=full ./list

//moje deklaracje
void print_list(List * list);
void present_list(List * list);
int count_elements(List * list);
unsigned long long count_elements_v2(List * list);

// funkcje do napisania
void sort_list(List * list);
void reverse_list(List * list);

int main()
{
#ifdef KOMENTARZ
	printf("To jest komentarz\n");
#endif

    int k;
	const int rozmiar_l1 = 3;
	const int rozmiar_l2 = 4;

    List * lista_1 = create_list();
    List * lista_2 = create_list();

#ifdef prezentuj
    print_list(lista_1);
    print_list(lista_2);
#endif

    for(k = 0; k < rozmiar_l1; k++) {
        append_to_list(lista_1, k);
    }
	for(k = 0; k < rozmiar_l2; k++) {
        append_to_list(lista_2, 2*k);
    }

#ifdef prezentuj

    printf("Ilosc elementow pierwszej listy: %d\n", count_elements(lista_1));
    printf("Ilosc elementow drugiej listy: %d\n", count_elements(lista_2));
	printf("\nWersja 2 funkcji count\n\n");
    printf("Ilosc elementow pierwszej listy: %lld\n", count_elements_v2(lista_1));
    printf("Ilosc elementow drugiej listy: %lld\n", count_elements_v2(lista_2));

	printf("\nLista 1 \n\n");
    print_list(lista_1);

	printf("\nLista 2 \n\n");
    print_list(lista_2);

#endif //prezentuj
	
#ifdef test_insert_to_list
	insert_to_list(lista_1,77,2);
	insert_to_list(lista_2,88,5);
	print_list(lista_1);
	print_list(lista_2);
	printf("Ilosc elementow pierwszej listy: %d\n", count_elements(lista_1));
#endif //test_insert_to_list
	
#ifdef check_get_nth_element
	for(k = 0; k < 9; k++)
		printf("Element nr %d w liście 1 to:"
			   "%d\n", k, get_nth_element(lista_1,k));

	printf("\n\n");

	for(k = 0; k < 7; k++)
		printf("Element nr %d w liście 2 to:"
			   "%d\n", k, get_nth_element(lista_2,k));
#endif // check_get_nth_element

#ifdef test_remove_nth_element
    int ind = 0;
    do{
        printf("Podaj indeks elementu do usunięcia: ");
        scanf("%d",&ind);
        if(ind >= 0) {
            remove_nth_element(lista_1,ind);
            printf("Lista1 po usunięciu: \n\n");
            present_list(lista_1);
        }
    }while(ind != -1);


#endif // test_remove_nth_element
	clear_list(lista_1);
	clear_list(lista_2);

#ifdef prezentuj
	printf("\nJestem po clear\n\n");
	printf("Ilosc elementow pierwszej listy: %d\n", count_elements(lista_1));
    printf("Ilosc elementow drugiej listy: %d\n", count_elements(lista_2));
#endif


	destroy_list(&lista_1);
	destroy_list(&lista_2);

    return 0;
}
