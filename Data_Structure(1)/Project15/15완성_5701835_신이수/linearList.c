#include<stdio.h>
#include<stdlib.h>
#include"linearList.h"


listType* createList(int size) {

	listType* listptr = (listType*)malloc(sizeof(listType));
	if (listptr == NULL) {
		fprintf(stderr, "Memory allocation failed for listptr\n");
		return NULL;
	}

	if (size <= 0) {
		fprintf(stderr, "Size Error\n");
		return NULL;
	}


	listptr->size = size;
	listptr->last = -1;
	listptr->array = (elementType*)malloc(sizeof(elementType) * size);
	return listptr;
}





//리스트 삽입(추가)
void insertItem(listType* list, elementType item) {
	if (list == NULL) {
		fprintf(stderr, "Invalid list\n");
		return;
	}

	// 리스트가 꽉 찬 경우 메모리 재할당
	if (list->last + 1 >= list->size) {
		int new_size = list->size * 2; // 크기를 2배로 확장
		elementType* new_array = realloc(list->array, sizeof(elementType) * new_size);
		if (new_array == NULL) {
			fprintf(stderr, "Memory reallocation failed\n");
			return;
		}
		list->array = new_array;
		list->size = new_size;
	}

	list->last++;
	list->array[list->last] = item;
}




//전체 연락처 출력
void printList(listType* list) {
	int i;
	
	if (list == NULL || list->last < 0) {
		printf("연락처가 없습니다.\n");
		return;
	}

	for (i = 0; i < list->last + 1; i++) {

		printf("[%d] 이름 : %s, 전화번호 : %s\n\n", i + 1, list->array[i].name, list->array[i].phone);

	}

}




//search 해서 해당 리스트 삭제
elementType deleteList(listType* list, char name[]) {
	
	if (list == NULL || list->last < 0) {
		fprintf(stderr, "List is empty or invalid\n");
		return NULL_ITEM;
	}


	int i;

	//해당 리스트 찾기
	for (i = 0; i <= list->last; i++) {
		if (strcmp(list->array[i].name, name) == 0) break;
	}

	if (i > list->last) {
		printf("연락처를 찾을 수 없습니다.\n");
		return NULL_ITEM;
	}


	elementType r = list->array[i];

	//리스트 당기기(자동적으로 해당리스트 삭제)
	for (int j = i; j < list->last; j++) {
		list->array[j] = list->array[j + 1];
	}
	list->last--;

	return r;
}


//0부터 size까지 반복하며 검색
void searchList(listType* list, char name[]) {
	if (list == NULL || list->last < 0) {
		fprintf(stderr, "List is empty or invalid\n");
		return;
	}
	
	int i;

	for (i = 0; i < list->last + 1; i++) {
		if (strcmp(list->array[i].name, name) == 0) {
			printf("[%d] 이름 : %s, 전화번호 : %s\n\n", i + 1, list->array[i].name, list->array[i].phone);
			return;
		}
	}
	
	printf("연락처를 찾을 수 없습니다.\n\n");

}

