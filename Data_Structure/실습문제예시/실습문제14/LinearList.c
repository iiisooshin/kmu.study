#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

listType* createList(int size) {
	listType* listptr = (listType*)malloc(sizeof(listType));
	listptr->size = size;
	listptr->move = 0;
	listptr->last = -1;
	listptr->array = (elementType*)malloc(sizeof(elementType) * size);
	return listptr;
}

elementType readItem(listType* list, int index) {
	if (index < 0 || index > list->last) {
		fprintf(stderr, "Index out of range in readItem: %d\n", index);
		return NULL_ITEM;
	}
	return list->array[index];
}

int compare_item(elementType item1, elementType item2) {
	return item1.expo - item2.expo;
}

int ordered_insertItem(listType* list, elementType item) {
	int i, j;
	for (i = 0; i <= list->last; i++) {
		if (compare_item(list->array[i], item) >= 0) break;
	}
	for (j = list->last + 1; j > i; j--) {
		list->array[j] = list->array[j - 1];
		list->move++;
	}
	list->array[i] = item;
	list->last++;
	return 1;
}

int insertItem(listType* list, int index, elementType item) {
	if (index < 0 || index > list->last + 1 || (list->last + 1) >= list->size) return 0;
	for (int i = list->last + 1; i > index; i--) {
		list->array[i] = list->array[i - 1];
		list->move++;
	}
	list->array[index] = item;
	list->last++;
	return 1;
}

elementType deleteItem(listType* list, int index) {
	if (index < 0 || index > list->last) return NULL_ITEM;
	elementType r = list->array[index];
	for (int i = index; i < list->last; i++) {
		list->array[i] = list->array[i + 1];
		list->move++;
	}
	list->last--;
	return r;
}

int printList(listType* list) {
	printf("List: size = %d, last = %d, move = %d\n", list->size, list->last, list->move);
	printf("Items: P(x) = ");
	for (int i = list->last; i >= 0; i--) {
		printf("%d", list->array[i].coef);
		if (list->array[i].expo != 0) printf("X^%d", list->array[i].expo);
		if (i != 0) printf("+");
	}
	printf("\n");
	return 1;
}

int initList(listType* list) {
	list->last = -1;
	list->move = 0;
	return 1;
}
