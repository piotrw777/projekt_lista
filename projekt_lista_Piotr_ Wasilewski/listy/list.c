#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#define ull unsigned long long
#define check_access  // sprawdzanie poprawności indeksu elementu listy
typedef struct node node;
struct node {
    node * next;
    int elem;
};

int size_of_node = sizeof(node);

struct List {
    node * head;  //wskaźnik na początek listy
    node * tail;  //wska?nik na koniec listy
    unsigned long long list_size; //ilo?? elementów
};

//moje:

void print_list(List * list) {
    if(list->head == NULL) {
        printf("Lista jest pusta\n");
        return;
    }
    int k = 0;
    node * wsk_node = list -> head;

    do {
        printf( "Element nr %d: %d\n", k++, wsk_node->elem );
        wsk_node = wsk_node->next;
    } while( wsk_node->next != NULL );
    printf( "Element nr %d: %d\n\n", k, wsk_node->elem );

}
int count_elements(List * list) {
    if(list->head == NULL) {
        return 0;
    }
    int k = 1;
    node * wsk_node = list -> head;

    while(wsk_node->next != NULL) {
        k++;
        wsk_node = wsk_node->next;
    };
    return k;
}
unsigned long long count_elements_v2(List * list) {
    return list -> list_size;
}

//zadane:
List * create_list(void) {
    List * nowa_lista = malloc( sizeof( List ) );
    nowa_lista -> head = NULL;
    nowa_lista -> tail = NULL;
    nowa_lista -> list_size = 0;
    return nowa_lista;
}
void append_to_list(List * list, int a) {
    //je?li lista jest pusta
    if( list -> head == NULL ) {
        list -> head = malloc( size_of_node );
        list -> tail = list -> head;
        list -> head -> next = NULL;
        list -> head -> elem = a;
        list -> list_size = 1;
    } else {
        node * wsk_node = list -> tail;
        wsk_node -> next = malloc( size_of_node );
        wsk_node -> next -> next = NULL;
        wsk_node -> next -> elem = a;
        list -> tail = wsk_node -> next;
        (list -> list_size)++;
    }
}
void clear_list(List * list) {
    node * wsk_node_1 = list -> head;
    node * wsk_node_2;

    while( wsk_node_1 != NULL) {
        wsk_node_2 = wsk_node_1 -> next;
        free(wsk_node_1);
        wsk_node_1 = wsk_node_2;
    }
    list -> head = NULL;
    list -> tail = NULL;
    list -> list_size = 0;
}
void destroy_list(List ** list) {
    clear_list(*list);
    free((*list) -> head);
    free((*list) -> tail);
    free(*list);
}
int get_nth_element(List * list, int index) {
#ifdef check_access
    if(list->head == NULL) {
        perror("Proba dostepu do elementu w pustej liscie");
    }

    if( index >= (list -> list_size) )
        perror("Proba dostepu do nieistniejacego elementu listy");

#endif // check_access
    int k = 0;
    node * wsk_node = list -> head;

    while( k < index ) {
        k++;
        wsk_node = wsk_node->next;
    };
    return wsk_node -> elem;
    void insert_to_list();
} // end of get_nth_element
void insert_to_list(List * list, int elem, int index) {
#ifdef check_access
	if(index < 0 || index >= list->list_size) {
		perror("Proba dodania elementu listy na niewlasciwej pozycji\nBlad w funkcji insert_to_list");
		exit(1);
	}
#endif
    //dodajemy na początku
    if(index == 0) {
        node *wsk_node = list->head;
        list->head = malloc(size_of_node);
        list->head ->next = wsk_node;
        list->head->elem=elem;
        list->list_size++;
        return;
    }
    if(index < list->list_size) {
		node * wsk_node = list->head;
		node * wsk_node_2;
		int k = index - 1;
		//idziemy do miejsca wstawiania
		while(k--) wsk_node = wsk_node->next;
		wsk_node_2 = wsk_node->next;
		//tworzenie nowego elementu
		wsk_node->next = malloc(size_of_node);
		wsk_node->next->next=wsk_node_2;
		wsk_node->next->elem=elem;
		list->list_size++;
		return;
	}


} //end insert_to_list
void remove_nth_element(List * list, int index) {
	
}
