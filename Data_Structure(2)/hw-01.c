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
    if (!newNode) {
        exit(1);
    }
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
    int paren_count = 0; // 괄호 짝 확인용

    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i] == ',') {
            i++; // 공백이나 쉼표 무시
            continue;
        }
        if (str[i] == '(') {
            paren_count++;
            if (current != NULL) {
                push(&s, current);
            }
            current = NULL; // 새로운 서브트리 시작
        }
        else if (str[i] == ')') {
            paren_count--;
            if (paren_count < 0) {
                printf("Error: Too many closing parentheses\n");
                isBinary = false;
                break;
            }
            if (!isEmpty(&s)) {
                current = pop(&s);
            }
            else if (current != NULL) {
                current = NULL; // 루트 수준으로 돌아감
            }
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            Node* newNode = createNode(str[i]);
            if (root == NULL) {
                root = newNode;
                current = root;
            }
            else if (current == NULL) {
                if (!isEmpty(&s)) {
                    current = pop(&s);
                    if (current->left == NULL) {
                        current->left = newNode;
                    }
                    else if (current->right == NULL) {
                        current->right = newNode;
                    }
                    else {
                        printf("Error: Node %c has more than two children\n", current->data);
                        isBinary = false;
                        free(newNode);
                        break;
                    }
                    current = newNode; // 새 노드를 현재 노드로 설정
                }
                else {
                    printf("Error: Invalid tree structure\n");
                    isBinary = false;
                    free(newNode);
                    break;
                }
            }
            else {
                if (current->left == NULL) {
                    current->left = newNode;
                }
                else if (current->right == NULL) {
                    current->right = newNode;
                }
                else {
                    printf("Error: Node %c has more than two children\n", current->data);
                    isBinary = false;
                    free(newNode);
                    break;
                }
                current = newNode; // 새 노드를 현재 노드로 업데이트
            }
        }
        else {
            printf("Error: Invalid character '%c'\n", str[i]);
            isBinary = false;
            break;
        }
        i++;
    }

    if (paren_count != 0) {
        printf("Error: Unclosed parentheses\n");
        isBinary = false;
    }
    else if (paren_count == 0 && !isBinary) {
        // 괄호는 맞지만 이진 트리 조건을 위반한 경우, 메시지 유지
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
        free(pop(&s));
    }

    return isBinary;
}

int main() {
    char input[MAX_SIZE];
    printf("Enter a parenthesized binary tree (ex (A(B(C)(D))(E(F)(G))) ): ");
    fgets(input, MAX_SIZE, stdin);

    // 개행 문자 제거
    input[strcspn(input, "\n")] = 0;

    if (isBinaryTree(input)) {
        printf("TRUE\n");
    }
    else {
        printf("FALSE\n");
    }

    return 0;
}