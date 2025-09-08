#include<stdio.h>
#include<stdlib.h>
#include"linearList.h"







main() {



	listType* myList = createList(20);

	if (myList == NULL) {
		fprintf(stderr, "Failed to create list\n");
		return 1;
	}

	int repeat = 1;
	
	while (repeat) {
		int input;
		char name[100];
		char phone[14];


		printf("\n===== 전화번호부 메뉴 =====\n\n");
		printf("1. 연락처 추가\n");
		printf("2. 연락처 삭제\n");
		printf("3. 연락처 검색\n");
		printf("4. 전체 연락처 출력\n");
		printf("0. 종료\n\n");
		printf("\n메뉴를 선택하세요 : ");

		if (scanf_s("%d", &input) != 1) {
			while (getchar() != '\n'); // 입력 버퍼 비우기
			printf("잘못된 입력입니다.\n");
			continue;
		}



		switch (input) {
		case 1:

			printf("\n이름을 입력하세요 : ");
			scanf_s("%s", name, sizeof(name));
			printf("\n전화번호를 입력하세요 : ");
			scanf_s("%s", phone, sizeof(phone));


			elementType item;
			strcpy(item.name, name);
			strcpy(item.phone, phone);

			insertItem(myList, item);
			printf("\n연락처가 추가되었습니다.\n");
			break;

		case 2:

			printf("\n삭제할 이름을 입력하세요 : ");
			scanf_s("%s", name, sizeof(name));


			deleteList(myList, name);
			printf("\n연락처가 삭제되었습니다.\n");
			break;


		case 3:

			printf("\n검색할 이름을 입력하세요 : ");
			scanf_s("%s", name, sizeof(name));
			printf("\n");



			printf("\n----- 검색한 연락처 -----\n\n");

			searchList(myList, name);
			break;



		case 4:
			printf("\n----- 전체 연락처 -----\n\n");

			printList(myList);
			break;


		case 0:

			free(myList);
			repeat = 0;
			break;

		default:
			printf("\n잘못된 입력입니다.\n");
		}




	}







}