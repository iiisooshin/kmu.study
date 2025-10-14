#include <stdio.h>
#include <stdlib.h>

// AVL 트리 노드 구조체
typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// --- 함수 선언 ---
int maxHeight(int a, int b);
int getHeight(AVLNode* node);
AVLNode* createNode(int key);
AVLNode* LLRotate(AVLNode* y);
AVLNode* RRRotate(AVLNode* x);
int getBalanceFactor(AVLNode* node);
AVLNode* insert(AVLNode* node, int key);
void preOrder(AVLNode* root);

// --- 메인 함수 ---
int main() {
    AVLNode* root = NULL;

    /*
     * 이전 예제에서는 10, 20, 30, 40, 50을 순서대로 넣으면
     * 한쪽으로 치우친 트리가 되었지만, 이제는 회전을 통해
     * 균형을 유지합니다.
     */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30); // 10, 20, 30 삽입 시 RR 회전 발생
    root = insert(root, 40);
    root = insert(root, 50); // 30, 40, 50 삽입 시 RR 회전 발생
    root = insert(root, 25); // 30, 20, 25 삽입 시 RL 회전 발생

    printf("최종 트리의 전위 순회 결과 (Key(BalanceFactor)): \n");
    preOrder(root);
    printf("\n");

    return 0;
}

// --- 함수 정의 ---

// 두 정수 중 큰 값 반환
int maxHeight(int a, int b) {
    return (a > b) ? a : b;
}

// 노드의 높이 반환
int getHeight(AVLNode* node) {
    if (node == NULL)
        return -1;
    return node->height;
}

// 새 노드 생성
AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}

// 오른쪽으로 회전 (LL 회전)
AVLNode* LLRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + maxHeight(getHeight(y->left), getHeight(y->right));
    x->height = 1 + maxHeight(getHeight(x->left), getHeight(x->right));

    return x;
}

// 왼쪽으로 회전 (RR 회전)
AVLNode* RRRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + maxHeight(getHeight(x->left), getHeight(x->right));
    y->height = 1 + maxHeight(getHeight(y->left), getHeight(y->right));

    return y;
}

// 균형 인수 계산
int getBalanceFactor(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 노드 삽입 (회전 포함)
AVLNode* insert(AVLNode* node, int key) {
    if (node == NULL)
        return(createNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + maxHeight(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return LLRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return RRRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = RRRotate(node->left);
        return LLRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = LLRotate(node->right);
        return RRRotate(node);
    }

    return node;
}

// 전위 순회 (트리 구조 및 균형 인수 확인용)
void preOrder(AVLNode* root) {
    if (root != NULL) {
        printf("%d(BF:%d) ", root->key, getBalanceFactor(root));
        preOrder(root->left);
        preOrder(root->right);
    }
}
