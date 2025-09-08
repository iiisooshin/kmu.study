#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1000

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Node* item) {
    if (s->top < MAX_SIZE - 1) {
        s->items[++(s->top)] = item;
    }
}

Node* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return NULL;
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool isBinaryTree(const char* str) {
    Stack s;
    initStack(&s);
    Node* root = NULL;
    Node* current = NULL;
    bool isBinary = true;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '(') {
            if (current != NULL) {
                push(&s, current);
            }
        } else if (str[i] == ')') {
            if (!isEmpty(&s)) {
                current = pop(&s);
            }
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            Node* newNode = createNode(str[i]);
            if (root == NULL) {
                root = newNode;
                current = root;
            } else if (current->left == NULL) {
                current->left = newNode;
                current = newNode;
            } else if (current->right == NULL) {
                current->right = newNode;
                current = newNode;
            } else {
                isBinary = false; // 자식 노드가 2개를 초과
                break;
            }
        }
        i++;
    }

    // 메모리 해제
    if (root != NULL) {
        Stack treeStack;
        initStack(&treeStack);
        push(&treeStack, root);
        while (!isEmpty(&treeStack)) {
            Node* node = pop(&treeStack);
            if (node->left) push(&treeStack, node->left);
            if (node->right) push(&treeStack, node->right);
            free(node);
        }
    }
    while (!isEmpty(&s)) {
        Node* node = pop(&s);
        free(node);
    }

    return isBinary;
}

int main() {
    char input[MAX_SIZE];
    // printf("트리 문자열을 입력하세요 (예: (A (B (C D) E (F (G))))): ");
    fgets(input, MAX_SIZE, stdin);
    
    // 개행 문자 제거
    input[strcspn(input, "\n")] = 0;

    if (isBinaryTree(input)) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    return 0;
}