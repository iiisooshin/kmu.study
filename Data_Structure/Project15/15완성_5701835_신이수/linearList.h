#pragma once


#define NULL_ITEM (elementType){0,0}

typedef struct ElementType {
	char name[100];
	char phone[14];

} elementType;


typedef struct Listtype {
	int size;
	int last;
	elementType* array;

} listType;


extern listType* createList(int size);
//리스트 삽입(추가)
extern void insertItem(listType* list, elementType item);
//전체 연락처 출력
extern void printList(listType* list);
//마지막 리스트에 추가하기
extern void addList(listType* list);
//search 해서 해당 리스트 삭제
extern elementType deleteList(listType* list, char name[]);
//0부터 size까지 반복하며 검색
extern void searchList(listType* list, char name[]);