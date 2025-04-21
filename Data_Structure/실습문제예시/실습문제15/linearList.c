#include <stdio.h>
#include <string.h>
#include "linearList.h"

void initList(listType* list) {
    list->last = -1;
    list->size = MAX;
}

void addContact(listType* list) {
    if (list->last + 1 >= list->size) {
        printf("����Ʈ�� ���� á���ϴ�.\n");
        return;
    }

    elementType e;

    printf("�̸��� �Է��ϼ���: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("��ȭ��ȣ�� �Է��ϼ���: ");
    fgets(e.phone, sizeof(e.phone), stdin);
    e.phone[strcspn(e.phone, "\n")] = '\0';

    list->array[++list->last] = e;
    printf("����ó�� �߰��Ǿ����ϴ�.\n");
}

void deleteContact(listType* list) {
    char name[30];
    printf("������ �̸��� �Է��ϼ���: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i <= list->last; i++) {
        if (strcmp(list->array[i].name, name) == 0) {
            for (int j = i; j < list->last; j++) {
                list->array[j] = list->array[j + 1];
            }
            list->last--;
            printf("�����Ǿ����ϴ�.\n");
            return;
        }
    }

    printf("�ش� �̸��� ����ó�� ã�� �� �����ϴ�.\n");
}

void searchContact(listType* list) {
    char keyword[30];

    printf("�˻��� �̸� �Ǵ� ��ȭ��ȣ�� �Է��ϼ���: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i <= list->last; i++) {
        if (strstr(list->array[i].name, keyword) != NULL ||
            strstr(list->array[i].phone, keyword) != NULL) {
            printf("�̸�: %s\n��ȭ��ȣ: %s\n", list->array[i].name, list->array[i].phone);
            found = 1;
        }
    }

    if (!found) {
        printf("�˻� ����� �����ϴ�.\n");
    }
}


void printAllContacts(listType* list) {
    printf("\n----- ��ü ����ó -----\n");
    for (int i = 0; i <= list->last; i++) {
        printf("[%d] �̸�: %s, ��ȭ��ȣ: %s\n", i + 1, list->array[i].name, list->array[i].phone);
    }
    printf("----------------------\n");
}
