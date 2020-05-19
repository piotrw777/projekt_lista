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
    node * tail;  //wskaźnik na koniec listy
    unsigned long long length; //ilość elementów
};

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
    return list -> length;
}

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
}
int get_nth_element(List * list, int index) {
#ifdef check_access
    if(list->head == NULL) {
        perror("Proba dostepu do elementu w pustej liscie");
    }

    if( index >= (list -> length) )
        perror("Proba dostepu do nieistniejacego elementu listy");

#endif // check_access
    int k = 0;
    node * wsk_node = list -> head;

    while(k < index) {
        k++;
        wsk_node = wsk_node->next;
    };
    return wsk_node -> elem;
    void insert_to_list();
} // end of get_nth_element
void insert_to_list(List * list, int elem, int index) {
#ifdef check_access
	if(index < 0 || index >= list->length) {
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
