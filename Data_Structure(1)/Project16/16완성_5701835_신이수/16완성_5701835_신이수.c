#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

main() {



	int input;
	int repeat = 1;
	elementType input_value;
	int pre_value;
	int loc;


	linkedList_h* myList;
	myList = createCLinkedList();




	while (repeat == 1) {

		printf("======= Linked_List Menu =======\n");
		printf("1) insertFirst\t\t(리스트의 제일 앞에 삽입)\n");
		printf("2) insertLast\t\t(리스트의 제일 뒤에 삽입)\n");
		printf("3) insertMiddle\t\t(특정 값 뒤에 삽입)\n");
		printf("4) insertNthNode\t(N번째 위치 삽입)\n");
		printf("5) searchNode\t\t(노드 찾기)\n");
		printf("6) delete Node\t\t(특정 값 삭제)\n");
		printf("7) print Head/Tail\n");
		printf("0) Program Stop\n");
		printf("Select Menu > ");
		scanf_s("%d", &input);
		myList->follow = 0;

		switch (input) {

			case 1:
				printf("삽입할 값 : ");
				scanf_s("%d", &input_value);
				insertFirstCNode(myList, input_value);
				printCList(myList);
				printf("\n");

				break;


			case 2:
				printf("삽입할 값 : ");
				scanf_s("%d", &input_value);
				insertLastCNode(myList, input_value);
				printCList(myList);
				printf("\n");

				break;


			case 3:
				printf("(key) 어떤 값 뒤에? ");
				scanf_s("%d", &pre_value);

				printf("삽입할 값 : ");
				scanf_s("%d", &input_value);

				if (myList->head == (listNode*)NULL) {
					printf("리스트가 비었습니다.\n");
				}
				else {
					
					listNode* pre;
					pre = myList->head;


					do
					{
						if (pre->data == pre_value) {
							insertMiddleCNode(myList, pre, input_value);
							break;
						}
						
						pre = pre->link;
						myList->follow++;

					} while (pre != myList->head);
					if (pre == myList->head && pre->data != pre_value) {
						printf("값 %d을(를) 찾을 수 없습니다.\n", pre_value);
					}
				}

				printCList(myList);

				printf("\n");

				break;


			case 4:

				printCList(myList);
				printf("위치 (index, 0부터) : ");
				scanf_s("%d", &loc);
				printf("삽입 할 값 : ");
				scanf_s("%d", &input_value);

				insertNthCNode(myList, loc, input_value);

				printCList(myList);
				printf("\n");

				break;


			case 5:

				printf("검색할 값 : ");
				scanf_s("%d", &input_value);
				searchCNode(myList, input_value);
				printf("\n");


				break;


			case 6:
				

				if (myList->head == (listNode*)NULL) {
					printf("리스트가 비었습니다.\n");
				}
				else {
					printCList(myList);
					printf("삭제할 값 : ");
					scanf_s("%d", &input_value);
					

					listNode* current;
					current = myList->head;

					do {
						if (current->data == input_value) {
							deleteCNode(myList, current);
							break;
						}

						current = current->link;
					
					} while (current != myList->head);
					
					if (current == myList->head && current->data != input_value) {
						printf("값 %d을(를) 찾을 수 없습니다.\n", input_value);
					}
				}

				printCList(myList);
				printf("\n");

				break;


			case 7:

				if (myList->head == (listNode*)NULL) {
					printf("List is NULL\n");
					break;
				}

				printf("Head > [%d]    Tail > [%d]", myList->head->data, myList->tail->data);
				printf("\n\n");

				break;


			case 0:
				repeat = 0;
				printf("프로그램을 종료합니다.");
				printf("\n");

				break;


			default:
				printf("잘못된 입력입니다.");
				printf("\n");

				break;


		}
			



	}


	







}
