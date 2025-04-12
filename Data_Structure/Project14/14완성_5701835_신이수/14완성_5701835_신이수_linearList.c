#include <stdio.h>
#include <stdlib.h>

#include "linearList.h"

listType* createList(int size) {
	listType* lptr;

	lptr = (listType*)malloc(sizeof(listType));
	lptr->array = (elementType*)malloc(sizeof(elementType) * size);
	lptr->size = size;
	lptr->last = -1;
	lptr->move = 0;

	return lptr;
}

int destroyList(listType* list) {
	free(list->array);
	free(list);

}


elementType readItem(listType* list, int index) {
	if (index < 0 || index > list->last) {
		fprintf(stderr,"Index error %d in readItem\n", index);
		return NULL_ITEM;
	}
	return list->array[index];
}

//Polynomial
int compare_item(elementType item1, elementType item2) {
	return (item1.expo - item2.expo);
}



int ordered_insertItem(listType* list, elementType item) {
	int i,j;

	for (i = 0; i <= list->last; i++) {
		if (compare_item(list->array[i], item) > 0) break;
	}

	for ( j = list->last + 1; j > i ; j--) {
		list->array[j] = list->array[j - 1];
		list->move++;
	}
	list->array[i] = item;
	list->last++;

	return 1;

}

int insertItem(listType* list, int index, elementType item) {
	if (index < 0 || index > (list->last+1)) {
		fprintf(stderr, "Index error %d in readItem\n", index);
		return -1;
	}
	if (index > list->size) {
		fprintf(stderr, "list is full(%d) in readItem\n", index);
			return -1;
	}

	for (int i = list->last + 1; i > index; i--) {
		list->array[i] = list->array[i - 1];
			list->move++;
	}
	list->array[index] = item;
	list->last++;
	
	return 1;
}

elementType deleteItem(listType* list, int index) {
	elementType r = list->array[index];

	if (index < 0 || index > list->last) {
		fprintf(stderr, "Index error %d in deleteItem\n", index);
		return NULL_ITEM;
	}

	for (int i = index; i < list->last; i++) {
		list->array[i] = list->array[i + 1];
		list->move++;
	}
	list->last--;

	return r;
}

//Polynomial
int printList(listType* list) {

	printf("List: size = %d, last = %d, move = %d\n\t Items : P(x)= ", list->size, list->last, list->move);
	for (int i = list->last; i >= 0; i--) {
		printf("%d", list->array[i].coef);
		if (list->array[i].expo != 0) printf("X^%d", list->array[i].expo);
		if (i != 0) printf("+");


	}
	printf("\n");
}




int initList(listType* list) {
	list->last = -1;
	list->move = 0;
}


//다항식 덧셈
listType* polyadd(listType* f, listType* s) {
	listType* a;
	int i = 0, j = 0;
	elementType f_item, s_item;

	a = createList(f->last + s->last + 2);

	while (i <= f->last && j <= s->last) {
		f_item = readItem(f, i);
		s_item = readItem(s, j);
		if (f_item.expo < s_item.expo) {
			ordered_insertItem(a, f_item);
			i++;
		}
		else if (f_item.expo == s_item.expo) {
			ordered_insertItem(a, (elementType) { (f_item.coef + s_item.coef), f_item.expo });
			i++;
			j++;
		}
		else if (f_item.expo != s_item.expo) {
			ordered_insertItem(a, s_item);
			j++;
		}
	}
	while (i <= f->last) {
		ordered_insertItem(a, readItem(f, i));
		i++;

	}
	while (j <= s->last) {
		ordered_insertItem(a, readItem(s, j));
		j++;

	}

	return a;
}