#pragma once

#define MAX 100
#define NULL_ITEM (elementType){"", ""}

typedef struct {
    char name[30];
    char phone[20];
} elementType;

typedef struct {
    int size;
    int last;
    elementType array[MAX];
} listType;


extern void initList(listType* list);
extern void addContact(listType* list);
extern void deleteContact(listType* list);
extern void searchContact(listType* list);
extern void printAllContacts(listType* list);
