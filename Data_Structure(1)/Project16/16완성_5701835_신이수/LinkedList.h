#pragma once


typedef int elementType;	//node에 저장할 데이터는 정수


//연결 리스트의 node타입 정의
typedef struct ListNode {

	elementType data;
	struct ListNode* link;

} listNode;		//listNode와 ListNode는 다르다 하지만 같이 써도 지장은 없다


//연결 리스트의 header
typedef struct {

	int follow;
	listNode* head;
	listNode* tail;

} linkedList_h;



extern linkedList_h* createLinkedList(void); //linkedList_h 라는 포인터를 리턴
extern linkedList_h* createCLinkedList(void); // circular linked list


extern void destroyLinkedList(linkedList_h* L);
extern void destroyCLinkedList(linkedList_h* L); // circular linked list


extern int printList(linkedList_h* L);
extern int printCList(linkedList_h* L); //circular linked list


extern void insertFirstNode(linkedList_h* L, elementType item);
extern void insertFirstCNode(linkedList_h* L, elementType item); // circular linked list


extern void insertMiddleNode(linkedList_h* L, listNode* pre, elementType item);
extern void insertMiddleCNode(linkedList_h* L, listNode* pre, elementType item);


extern void insertLastNode(linkedList_h* L, elementType item);
extern void insertLastCNode(linkedList_h* L, elementType item);


extern void insertNthNode(linkedList_h* L, int loc, elementType item);
extern void insertNthCNode(linkedList_h* L, int loc, elementType item);


extern int compare_item(elementType first, elementType second);
extern void ordered_insertNode(linkedList_h* L, elementType item);


extern void deleteNode(linkedList_h* L, listNode* p);
extern void deleteCNode(linkedList_h* L, listNode* p);


//extern void ordered_deleteNode(linkedList_h* L, elementType item);
extern void searchCNode(linkedList_h* L, elementType item);