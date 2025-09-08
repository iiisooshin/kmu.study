#pragma once

#define NULL_ITEM (elementType){0,0}

typedef struct ElementType {
	int coef, expo;
} elementType;

typedef struct ListType {
	int size; // size of list
	int last;
	int move;
	elementType* array;
} listType;

extern listType* createList(int size);
extern elementType readItem(listType* list, int index);
extern int insertItem(listType* list, int index, elementType item);
extern elementType deleteItem(listType* list, int index);
extern int printList(listType* list);
extern int initList(listType* list);
extern int ordered_insertItem(listType* list, elementType item);
