#include <stdio.h>
#include <string.h>
#include "linearList.h"

void initList(listType* list) {
    list->last = -1;
    list->size = MAX;
}

void addContact(listType* list) {
    if (list->last + 1 >= list->size) {
        printf("리스트가 가득 찼습니다.\n");
        return;
    }

    elementType e;

    printf("이름을 입력하세요: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("전화번호를 입력하세요: ");
    fgets(e.phone, sizeof(e.phone), stdin);
    e.phone[strcspn(e.phone, "\n")] = '\0';

    list->array[++list->last] = e;
    printf("연락처가 추가되었습니다.\n");
}

void deleteContact(listType* list) {
    char name[30];
    printf("삭제할 이름을 입력하세요: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i <= list->last; i++) {
        if (strcmp(list->array[i].name, name) == 0) {
            for (int j = i; j < list->last; j++) {
                list->array[j] = list->array[j + 1];
            }
            list->last--;
            printf("삭제되었습니다.\n");
            return;
        }
    }

    printf("해당 이름의 연락처를 찾을 수 없습니다.\n");
}

void searchContact(listType* list) {
    char keyword[30];

    printf("검색할 이름 또는 전화번호를 입력하세요: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i <= list->last; i++) {
        if (strstr(list->array[i].name, keyword) != NULL ||
            strstr(list->array[i].phone, keyword) != NULL) {
            printf("이름: %s\n전화번호: %s\n", list->array[i].name, list->array[i].phone);
            found = 1;
        }
    }

    if (!found) {
        printf("검색 결과가 없습니다.\n");
    }
}


void printAllContacts(listType* list) {
    printf("\n----- 전체 연락처 -----\n");
    for (int i = 0; i <= list->last; i++) {
        printf("[%d] 이름: %s, 전화번호: %s\n", i + 1, list->array[i].name, list->array[i].phone);
    }
    printf("----------------------\n");
}
