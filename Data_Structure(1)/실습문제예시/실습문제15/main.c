#include <stdio.h>
#include "linearList.h"

int main() {
    listType phonebook;
    int choice;

    initList(&phonebook);

    while (1) {
        printf("\n===== 전화번호부 메뉴 =====\n");
        printf("1. 연락처 추가\n");
        printf("2. 연락처 삭제\n");
        printf("3. 연락처 검색\n");
        printf("4. 전체 연락처 출력\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            addContact(&phonebook);
            break;
        case 2:
            deleteContact(&phonebook);
            break;
        case 3:
            searchContact(&phonebook);
            break;
        case 4:
            printAllContacts(&phonebook);
            break;
        case 0:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
        printf("\n");
    }
}
