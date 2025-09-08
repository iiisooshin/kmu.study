#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


//error 리턴 하려면 int값 사용


linkedList_h* createLinkedList(void) {

	linkedList_h* lptr;
	lptr = (linkedList_h*)malloc(sizeof(linkedList_h));
	lptr->head = (listNode*)NULL;
	lptr->follow = 0;
	return lptr;

}

linkedList_h* createCLinkedList(void) {



	linkedList_h* lptr;
	lptr = (linkedList_h*)malloc(sizeof(linkedList_h));
	lptr->head = (listNode*)NULL;
	lptr->follow = 0;
	lptr->tail = (listNode*)NULL;


	return lptr;


	

}






//create(메모리 할당) 했으면 끝날때 초기화 해주는게 좋다
void destroyLinkedList(linkedList_h* L) {

	listNode* p;

	while (L->head != NULL) {
		p = L->head;
		//L->head = L->head->link;
		L->head = p->link;

		free(p);
	}

	free(L);

}

void destroyCLinkedList(linkedList_h* L) {

	listNode* p;

	while (L->head != L->head->link) {
		p = L->head;
		//L->head = L->head->link;
		L->head = p->link;

		free(p);
	}

	free(L->head);
	free(L);

}



// 출력
int printList(linkedList_h* L) {

	listNode* lptr = L->head;


	printf("Linked List (follow = %d) : ", L->follow);
	while (lptr->link != (listNode*)NULL) {
		printf("[%d]", lptr->data);
		lptr = lptr->link;

	}
	printf("[%d]\n", lptr->data);

}

int printCList(linkedList_h* L) {

	listNode* lptr = L->head;


	printf("Circular Linked List (follow = %d) : ", L->follow);

	if (lptr == NULL) {
		printf("\n");
		return;
	}

	while (lptr->link != L->head) {
		printf("[%d]", lptr->data);
		lptr = lptr->link;

	}
	printf("[%d]\n", lptr->data);


}





// 첫번째 삽입
void insertFirstNode(linkedList_h* L, elementType item) {

	listNode* newNode;

	newNode = (listNode*)malloc(sizeof(listNode));

	newNode->data = item;
	newNode->link = L->head; // (1)

	L->head = newNode; // (2)


	return;

}

void insertFirstCNode(linkedList_h* L, elementType item) {

	if (L == NULL) return;
	
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));

	if (newNode == (listNode*)NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return;
	}

	newNode->data = item;
	
	if (L->head == (listNode*)NULL) {
		L->head = newNode;
		L->tail = newNode;
		newNode->link = newNode; // 자기 자신을 가리킴
	}
	else {
		newNode->link = L->head;
		L->head = newNode;
		L->tail->link = newNode; // 원형 구조 유지
	}
	L->follow++;



	return;

}




// 마지막에 삽입
void insertLastNode(linkedList_h* L, elementType item) {
	
	listNode* temp;
	listNode* newNode;

	newNode = (listNode*)malloc(sizeof(listNode));

	newNode->data = item;
	newNode->link = (listNode*)NULL;

	temp = L->head;



	if (temp == NULL) {
		L->head = newNode;
		return;
	}

	//리스트에 값이 없으면 에러가 난다
	while (temp->link != (listNode*)NULL) {
		temp = temp->link;
		L->follow++;
	}

	temp->link = newNode;

	return;


	
	

}


void insertLastCNode(linkedList_h* L, elementType item) {

	//listNode* temp;
	//listNode* newNode;

	//newNode = (listNode*)malloc(sizeof(listNode));

	//if (item == (elementType)NULL) return;


	//newNode->data = item;
	//newNode->link = L->tail;
	//temp = L->head;



	//if (temp == (listNode*)NULL) {
	//	L->head = newNode;
	//	return;
	//}

	////리스트에 값이 없으면 에러가 난다
	//while (temp->link != L->tail) {
	//	temp = temp->link;
	//	L->follow++;
	//}

	//temp->link = newNode;


	if (L == NULL) return;

	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));

	if (newNode == (listNode*)NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return;
	}

	newNode->data = item;

	if (L->head == (listNode*)NULL) {
		L->head = newNode;
		L->tail = newNode;
		newNode->link = newNode;
	}
	else {
		newNode->link = L->head;
		L->tail->link = newNode;
		L->tail = newNode;
	}
	L->follow++;

	
	
	
	return;

}






// pre 뒤에 삽입
void insertMiddleNode(linkedList_h* L, listNode* pre, elementType item) {

	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;


	if (L->head == (listNode*)NULL) {
		L->head = newNode;
		newNode->link = (listNode*)NULL;

	}
	else if (pre == (listNode*)NULL) {
		//insertFirstNode(L, item);
		newNode->link = L->head;
		L->head = newNode;

	}
	else {
		newNode->link = pre->link;
		pre->link = newNode;

	}

	
	return;
}

void insertMiddleCNode(linkedList_h* L, listNode* pre, elementType item) {

	if (L == (linkedList_h*)NULL || pre == (listNode*)NULL) return;


	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;


	if (L->head == (listNode*)NULL) {
		L->head = newNode;
		L->tail = newNode;
		newNode->link = newNode;

	}
	else {
		newNode->link = pre->link;
		pre->link = newNode;
		if (pre == L->tail) {
			L->tail = newNode;
		}
	}


	return;
}






//n 번째 삽입
void insertNthCNode(linkedList_h* L, int loc, elementType item) {

	if (L == (linkedList_h*)NULL) return;

	if (loc < 0) {
		fprintf(stderr, "[insertNthCNode: invalid location]\n");
		return;
	}


	if (L->head == (listNode*)NULL) {

		if (loc == 0) insertFirstCNode(L, item);
		else fprintf(stderr, "[insertNthNode : list empty and loc not 0]\n");
		return;

	}
	else {

		if (loc == 0) insertFirstCNode(L, item);

		else {

			int i = loc;
			listNode* pre = L->head;

			while (i > 1 && pre->link != (listNode*)NULL) {
				i--, pre = pre->link;
				L->follow++;
			}

			if (i == 1) insertMiddleCNode(L, pre, item);
			else fprintf(stderr, "[insertNthNode : location error]\n");
				
		}
		return;
	}


}


void insertNthNode(linkedList_h* L, int loc, elementType item) {



	if (L->head == (listNode*)NULL) {

		if (loc == 0) insertFirstNode(L, item);
		else fprintf(stderr, "[insertNthNode : list empty and loc not 0]\n");
		return;

	}
	else {

		if (loc == 0) insertFirstNode(L, item);

		else {

			int i = loc;
			listNode* pre = L->head;

			while (i > 1 && pre->link != L->tail) {
				i--, pre = pre->link;
				L->follow++;
			}

			if (i == 1) insertMiddleNode(L, pre, item);
			else fprintf(stderr, "[insertNthNode : location error]\n");

		}
		return;
	}


}






int compare_item(elementType first, elementType second) {
	return (first - second);
}



// 자동으로 위치 찾아서 삽입
void ordered_insertNode(linkedList_h* L, elementType item) {

	listNode* pre;

	if (L->head == (listNode*)NULL) insertFirstNode(L, item);
	else {

		if (compare_item(L->head->data, item) > 0) insertFirstNode(L, item);
		else {

			pre = L->head;

			while (pre->link != (listNode*)NULL) {
				if (compare_item(pre->data, item) < 0 && compare_item(pre->link->data, item) > 0) break;
				pre = pre->link;
				L->follow++;
			}

			insertMiddleNode(L, pre, item);

		}

	}

}




void deleteNode(linkedList_h* L, listNode* p) {
	
	listNode* pre;

	if (L->head == (listNode*)NULL) return;

	/*
	책에 있는 부분
	if (L->head->link == (listNode*)NULL) {
		free(L->head);
		L->head = (listNode*)NULL;
		return
	}
	*/

	else if (p == (listNode*)NULL) return;
	else {
		pre = L->head;

		while (pre->link != p && p->link != (listNode*)NULL) {
			pre = pre->link;
			L->follow++;
		}

		if (pre->link == p) {
			pre->link = p->link;
			free(p);
		}
		else {
			fprintf(stderr, "[delete item not in the list]\n");
		}
	}
}


void deleteCNode(linkedList_h* L, listNode* p) {

	if (L == (linkedList_h*)NULL || L->head == (listNode*)NULL || p == (listNode*)NULL) return;

	listNode* pre;

	if (L->head == L->tail && L->head == p) {

		free(p);
		L->head = (listNode*)NULL;
		L->tail = (listNode*)NULL;
		L->follow = 0;
		
		return;
	}
	else {

		pre = L->head;

		do {
			if (pre->link == p) {

				pre->link = p->link;

				if (p == L->head) {
					L->head = p->link;
				}

				if (p == L->tail) {
					L->tail = pre;
				}

				free(p);
				
				
				
				return;
			}

			pre = pre->link;
			L->follow++;

		} while (pre != L->head);
		fprintf(stderr, "[deleteCNode : item not in list]\n");

	}
}










void searchCNode(linkedList_h* L, elementType item) {


	if (L == (linkedList_h*)NULL || L->head == (listNode*)NULL) {
		printf("List is empty or not initialized.\n");
		return;
	}

	listNode* current = L->head;
	int position = 0;
	
	
	do {
		if (current->data == item) {
			printf("[%d]의 위치 [%d]\n", item, position);
			return;
		}
		current = current->link;
		position++;
	
	} while (current != L->head);

	printf("리스트에서 [%d]를 찾을 수 없습니다.\n", item);


}


// item 주고 해당 item 알아서 찾아서 삭제하는 함수 만들어보기
// search 해보기