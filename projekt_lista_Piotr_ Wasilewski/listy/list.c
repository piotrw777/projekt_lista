#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#define ull unsigned long long
#define check_access  // sprawdzanie poprawności indeksu elementu listy w funkcjach
typedef struct node node;
struct node {
    node * next;
    int elem;
};

int size_of_node = sizeof(node);

struct List {
    node * head;  //wskaźnik na początek listy
    node * tail;  //wskaźnik na koniec listy
    unsigned long long length; //ilość elementów
};

//zadane:
List * create_list(void) {
    List * nowa_lista = malloc( sizeof( List ) );
    nowa_lista -> head = NULL;
    nowa_lista -> tail = NULL;
    nowa_lista -> length = 0;
    return nowa_lista;
}
void append_to_list(List * list, int a) {
    //jeśli lista jest pusta
    if( list -> head == NULL ) {
        list -> head = malloc( size_of_node );
        list -> tail = list -> head;
        list -> head -> next = NULL;
        list -> head -> elem = a;
        list -> length = 1;
    } else {
        node * wsk_node = list -> tail;
        wsk_node -> next = malloc( size_of_node );
        wsk_node -> next -> next = NULL;
        wsk_node -> next -> elem = a;
        list -> tail = wsk_node -> next;
        (list -> length)++;
    }
}
void clear_list(List * list) {
    node * wsk_node_1 = list -> head;
    node * wsk_node_2;

    while(wsk_node_1 != NULL) {
        wsk_node_2 = wsk_node_1 -> next;
        free(wsk_node_1);
        wsk_node_1 = wsk_node_2;
    }
    list -> head = NULL;
    list -> tail = NULL;
    list -> length = 0;
}
void destroy_list(List ** list) {
    clear_list(*list);
    free((*list) -> head);
    free((*list) -> tail);
    free(*list);
    *list = NULL;
}
int get_nth_element(List * list, int index) {
#ifdef check_access
    if(list->head == NULL) {
        perror("Proba dostepu do elementu w pustej liscie\nBlad w funkcji get_nth_element");
		exit(1);
    }

    if( index >= (list -> length) ) {
        perror("Proba dostepu do nieistniejacego elementu listy\nBlad w funkcji get_nth_element");
		exit(1);
	}

#endif // check_access
    int k = 0;
    node * wsk_node = list -> head;

    while(k < index) {
        k++;
        wsk_node = wsk_node->next;
    };
    return wsk_node -> elem;
} // end of get_nth_element

void insert_to_list(List * list, int elem, int index) {
#ifdef check_access
	if(index < 0 || index > list->length) {
		perror("Proba dodania elementu listy na niewlasciwej pozycji\nBlad w funkcji insert_to_list");
		exit(1);
	}
#endif
	//dodanie nowego na końcu
	if(index == list->length) {
		append_to_list(list, elem);
		return;
	}
    //dodajemy na początku
    if(index == 0) {
        node *wsk_node = list->head;
        list->head = malloc(size_of_node);
        list->head ->next = wsk_node;
        list->head->elem=elem;
        list->length++;
        return;
    }
    if(index < list->length) {
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
		list->length++;
		return;
	}

} //end insert_to_list

void remove_nth_element(List * list, int index) {
    //usuwanie elementu o indeksie 0
    if(index == 0) {
        //jeśli jest tylko jeden element
        if(list->length == 1) {
            free( list->head);
            list->head = NULL;
            list->tail = NULL;
        }
        else {
            node * wsk_node = list->head->next;
            free(list->head);
            list->head = wsk_node;
        }
        list->length--;
        return;
    }
#ifdef check_access
	if(index < 0 || index >= list->length) {
		perror("Proba usuniecia elementu o nieistniejacym indeksie.\bBlad w funkcji remove_nth_element");
		exit(1);
	}
#endif
    //elementy o indeksie >= 1
    int k = index - 1;
    node * wsk_node = list->head;
    node * wsk_node2;
    //idziemy do miejsca usuwania
    while(k--) {
        wsk_node = wsk_node->next;
    }
    wsk_node2 = wsk_node->next->next;
    free(wsk_node->next);
    wsk_node->next = wsk_node2;
    //jeśli usuwamy ostatni zmieniamy tail
    if(index == list->length - 1)
        list->tail = wsk_node;

    list->length--;
} //end of remove_nth_element
void reverse_list(List * list) {
	if(list->length <= 1) return;

	node * wsk_node1 = NULL;
	node * wsk_node2 = list->head;
	node * wsk_node3 = list->head->next;

	list->tail = list->head;

	while(wsk_node3 != NULL) {
		//odwrócenie strzałki
		wsk_node2->next = wsk_node1;
		//idziemy dalej
		wsk_node1 = wsk_node2;
		wsk_node2 = wsk_node3;
		wsk_node3 = wsk_node3 -> next;
	}
	list->head = wsk_node2;
	wsk_node2->next = wsk_node1;
}
void sort_list(List * list) {
	if(list->length <= 1) return;
	//selection sort
	node * wsk_i = list->head;
	node * wsk_j;
	node * wsk_min;
	int min_element, tmp;

	while(wsk_i->next != NULL) {
		wsk_min = wsk_i;
		min_element = wsk_i->elem;
		wsk_j = wsk_i->next;

		while(wsk_j != NULL) {
			if(wsk_j->elem < min_element) {
				wsk_min = wsk_j;
				min_element = wsk_j->elem;
			}
			wsk_j = wsk_j->next;
		}
		//zamieniamy elementy
		tmp = wsk_i->elem;
		wsk_i->elem = wsk_min->elem;
		wsk_min->elem = tmp;
		wsk_i = wsk_i->next;
	}
}

void sort_list_2(List * list) {
	if(list->length <= 1) return;
	//insertion sort
    node *wsk_i1 = list->head;
    node *wsk_i2 = list->head->next;
    node *wsk_j1, *wsk_j2;
    short int k;

    //wsk_i2 przebiega po kolei elementu listy
    //wsk_i1 pokazuje na element poprzedzający *wsk_i2
    //(potrzebne do zamiany wskaźników next potem)
    while(wsk_i2 != NULL) {
        k = 0;
        wsk_j1 = wsk_j2 = list->head;
        //szukamy gdzie umieścić element *wsk_i2
        while(wsk_j2->elem < wsk_i2->elem) {
            wsk_j2 = wsk_j2->next;
            if(k != 0) wsk_j1 = wsk_j1->next;
            k = 1;
        }
        //jeśli *wsk_i2 powinien być na początku
        if(wsk_j2 == list->head) {
            //zmiana head'a
            if(wsk_i2 == list->tail) list->tail = wsk_i1;
            list->head = wsk_i2;
            wsk_i2 = wsk_i2->next;
            wsk_i1->next = wsk_i2;
            list->head->next = wsk_j1;
        }
        //element *wsk_j2 jest na swoim miejscu
        else if(wsk_j2 == wsk_i2) {
            wsk_i1 = wsk_i1->next;
            wsk_i2 = wsk_i2->next;
        }
        else {
            if(list->tail == wsk_i2) list->tail = wsk_i1;
            wsk_j1->next = wsk_i2;
            wsk_i2 = wsk_i2->next;
            wsk_i1->next = wsk_i2;
            wsk_j1->next->next = wsk_j2;
        }
    }
}
//moje:

void print_list(List * list) {
    if(list->head == NULL) {
        printf("Lista jest pusta\n");
        return;
    }
    int k = 0;
    node * wsk_node = list -> head;

    while( wsk_node != NULL ) {
		printf( "Element nr %d: %d\n", k, wsk_node->elem );
		wsk_node = wsk_node->next;
		k++;
	}
}
void present_list(List * list) {
    printf("Lista ma %lld elementów\n",list->length);
    print_list(list);

}
