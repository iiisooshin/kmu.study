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

elementType readItem(listType* list, int index) {
	if (index < 0 || index > list->last) {
		fprintf(stderr,"Index error %d in readItem\n", index);
		return NULL_ITEM;
	}
	return list->array[index];
}

int compare_item(elementType item1, elementType item2) {
	if (item1.row != item2.row) return (item1.row - item2.row);
	else return (item1.col - item2.col);
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

int printList(listType* list) {
	printf("List: size = %d, last = %d, move = %d\n\tItems:", list->size, list->last, list->move);
	for (int i = 0; i <= list->last; i++) {
		printf(" [%d]{%d,%d,%d} ", i, list->array[i].row, list->array[i].col, list->array[i].val);
		printf("\n");
	}
	return 0;
}

int initList(listType* list) {
	list->last = -1;
	list->move = 0;
}

listType* sumList(listType* list1, listType* list2) {
	listType* result = createList(list1->last + list2->last + 2); //배열끼리 더했을때 최대 크기는 배열1크기 + 배열2크기
	initList(result); //초기화

	int i = 0, j = 0;

	while (i <= list1->last && j <= list2->last) {
		elementType item1 = list1->array[i];
		elementType item2 = list2->array[j];

		int cmp = compare_item(item1, item2);

		if (cmp == 0) { //row col이 같으면
			int sum = item1.val + item2.val;
			if (sum != 0) { //합이 0이 아닌 경우만 삽입
				elementType newItem = { item1.row, item1.col, sum };
				ordered_insertItem(result, newItem);
			}
			i++;
			j++;
		}
		else if (cmp < 0) { //item1이 더 작을때
			ordered_insertItem(result, item1);
			i++;
		}
		else { //item2가 더 작을때
			ordered_insertItem(result, item2);
			j++;
		}


		while (i <= list1->last) {
			ordered_insertItem(result, list1->array[i]);
			i++;
		}

		while (j <= list2->last) {
			ordered_insertItem(result, list2->array[j]);
			j++;
		}
	}




	return result;
}