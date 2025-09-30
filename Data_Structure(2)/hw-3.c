#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ====================================================
// 자료구조 정의
// ====================================================

// 트리의 기본 구성 단위인 TreeNode
typedef struct TreeNode {
    char value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 스택 자료구조 (메모리 해제를 위해 필요)
#define STACK_SIZE 256
typedef struct {
    TreeNode* items[STACK_SIZE];
    int top;
} Stack;

// ====================================================
// 스택 헬퍼 함수
// ====================================================

void init_stack(Stack* s) { s->top = -1; }
int is_stack_empty(Stack* s) { return s->top == -1; }
void push(Stack* s, TreeNode* node) { if (s->top < STACK_SIZE - 1) s->items[++(s->top)] = node; }
TreeNode* pop(Stack* s) { return is_stack_empty(s) ? NULL : s->items[(s->top)--]; }

// ====================================================
// 트리 생성 함수
// ====================================================

// 문자열을 재귀적으로 파싱하여 트리 생성
TreeNode* parse_recursive(const char** str_ptr) {
    while (isspace(**str_ptr)) (*str_ptr)++;
    if (**str_ptr == '\0' || **str_ptr == ')') return NULL;

    TreeNode* node = NULL;
    if (**str_ptr == '(') {
        (*str_ptr)++;
        while (isspace(**str_ptr)) (*str_ptr)++;
        node = (TreeNode*)malloc(sizeof(TreeNode));
        node->value = **str_ptr;
        (*str_ptr)++;
        node->left = parse_recursive(str_ptr);
        node->right = parse_recursive(str_ptr);
        while (isspace(**str_ptr)) (*str_ptr)++;
        if (**str_ptr == ')') (*str_ptr)++;
    }
    else if (isalpha(**str_ptr)) {
        node = (TreeNode*)malloc(sizeof(TreeNode));
        node->value = **str_ptr;
        node->left = NULL;
        node->right = NULL;
        (*str_ptr)++;
    }
    return node;
}

TreeNode* string_to_tree(const char* s) {
    if (!s || *s == '\0') return NULL;
    return parse_recursive(&s);
}

// ====================================================
// 트리 순회 (모리스 순회)
// ====================================================

// 전위 순회 (Morris Pre-order)
void preorder_morris(TreeNode* root) {
    TreeNode* current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%c ", current->value);
            current = current->right;
        }
        else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == NULL) {
                printf("%c ", current->value);
                predecessor->right = current;
                current = current->left;
            }
            else {
                predecessor->right = NULL;
                current = current->right;
            }
        }
    }
    printf("\n");
}

// 중위 순회 (Morris In-order)
void inorder_morris(TreeNode* root) {
    TreeNode* current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%c ", current->value);
            current = current->right;
        }
        else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == NULL) {
                predecessor->right = current;
                current = current->left;
            }
            else {
                predecessor->right = NULL;
                printf("%c ", current->value);
                current = current->right;
            }
        }
    }
    printf("\n");
}

// 후위 순회를 위해 경로를 역순으로 출력하는 헬퍼 함수
void reverse_and_print(TreeNode* from, TreeNode* to) {
    if (from == to) {
        printf("%c ", from->value);
        return;
    }
    TreeNode* p = from, * c = from->right, * n;
    while (p != to) {
        n = c->right;
        c->right = p;
        p = c;
        c = n;
    }
    c = p;
    while (1) {
        printf("%c ", c->value);
        if (c == from) break;
        c = c->right;
    }
    c = p; p = NULL;
    while (c != NULL) {
        n = c->right;
        c->right = p;
        p = c;
        c = n;
    }
}

// 후위 순회 (Morris Post-order)
void postorder_morris(TreeNode* root) {
    TreeNode dummy_node;
    dummy_node.left = root;
    dummy_node.right = NULL;

    TreeNode* current = &dummy_node;
    while (current != NULL) {
        if (current->left == NULL) {
            current = current->right;
        }
        else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == NULL) {
                predecessor->right = current;
                current = current->left;
            }
            else {
                reverse_and_print(current->left, predecessor);
                predecessor->right = NULL;
                current = current->right;
            }
        }
    }
    printf("\n");
}

// ====================================================
// 안전한 메모리 해제 및 메인 함수
// ====================================================

// 재귀 없는 안전한 free_tree 함수 (반복문 사용)
void free_tree_safe(TreeNode* root) {
    if (root == NULL) return;

    Stack s1, s2;
    init_stack(&s1);
    init_stack(&s2);

    push(&s1, root);

    // 1. 후위 순회 순서의 역순으로 s2에 노드를 저장
    while (!is_stack_empty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);
        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    // 2. s2에서 하나씩 꺼내면서 메모리 해제
    while (!is_stack_empty(&s2)) {
        TreeNode* node_to_free = pop(&s2);
        free(node_to_free);
    }
}

int main() {
    char input_buffer[256];
    TreeNode* root_node = NULL;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        printf("\n");

        // 1. 전위 순회
        root_node = string_to_tree(input_buffer);
        printf("pre-order: ");
        preorder_morris(root_node);
        free_tree_safe(root_node);

        // 2. 중위 순회
        root_node = string_to_tree(input_buffer);
        printf("in-order: ");
        inorder_morris(root_node);
        free_tree_safe(root_node);

        // 3. 후위 순회
        root_node = string_to_tree(input_buffer);
        printf("post-order: ");
        postorder_morris(root_node);
        free_tree_safe(root_node);
    }

    return 0;
}