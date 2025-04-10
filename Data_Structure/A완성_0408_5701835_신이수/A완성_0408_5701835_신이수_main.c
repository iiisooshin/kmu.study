#include <stdio.h>
#include <stdlib.h>

#include "linearList.h"

listType* SmTranspose(listType* org) {
	listType* tr;
	elementType o_item;

	tr = createList(org->size);

	for (int i = 0; i <= org->last; i++){
		o_item = readItem(org, i);
		ordered_insertItem(tr, (elementType) { o_item.col, o_item.row, o_item.val });
	}
    return tr;
}

main() {
	listType* myList1,* myList2,* result;
	

	myList1 = createList(20);
	myList2 = createList(20);


	printf("첫 번째 행렬을 입력하시오. (-1 입력시 입력 종료)\n");
	while (1) {
		int row, col, val;
		scanf_s("%d", &row);
		if (row == -1) break;

		scanf_s("%d %d", &col, &val);
		ordered_insertItem(myList1, (elementType) { row, col, val });

	}

	printf("두 번째 행렬을 입력하시오. (-1 입력시 입력 종료)\n");
	while (1) {
		int row, col, val;
		scanf_s("%d", &row);
		if (row == -1) break;

		scanf_s("%d %d", &col, &val);
		ordered_insertItem(myList2, (elementType) { row, col, val });
	}

	
	
	printf("두 행렬의 합\n");
	result = sumList(myList1, myList2);
	printList(result);




	free(myList1->array);
	free(myList1);
	free(myList2->array);
	free(myList2);
	free(result->array);
	free(result);



}