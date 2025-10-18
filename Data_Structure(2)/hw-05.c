#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE 1000
#define MAX_VAL 10001 // 0 ~ 10000

// ===================================
// 1. 자료구조 정의
// ===================================

// 이진 탐색 트리 (BST) 노드
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// AVL 트리 노드
typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height; // 노드의 높이
} AVLNode;

// ===================================
// 2. 유틸리티 함수 (AVL용)
// ===================================

// 높이 반환
int height(AVLNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// 최대값 (이름 변경)
int max_value (int a, int b) {
    return (a > b) ? a : b;
}

// ===================================
// 3. 노드 생성 함수
// ===================================

// BST 노드 생성
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// AVL 노드 생성
AVLNode* newAVLNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // 새 노드는 높이 1
    return node;
}

// ===================================
// 4. AVL 회전 함수
// ===================================

// 오른쪽 회전 (LL Case)
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // 회전 수행
    x->right = y;
    y->left = T2;

    // 높이 갱신 (max_value 사용)
    y->height = max_value(height(y->left), height(y->right)) + 1;
    x->height = max_value(height(x->left), height(x->right)) + 1;

    return x; // 새로운 루트
}

// 왼쪽 회전 (RR Case)
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // 회전 수행
    y->left = x;
    x->right = T2;

    // 높이 갱신 (max_value 사용)
    x->height = max_value(height(x->left), height(x->right)) + 1;
    y->height = max_value(height(y->left), height(y->right)) + 1;

    return y; // 새로운 루트
}

// 균형 인수(Balance Factor) 반환
int getBalance(AVLNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// ===================================
// 5. 삽입 함수
// ===================================

// BST 삽입 (재귀)
Node* insertBST(Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insertBST(node->left, data);
    else if (data > node->data)
        node->right = insertBST(node->right, data);

    // (중복 데이터는 무시)
    return node;
}

// AVL 삽입 (재귀 및 균형 맞추기)
AVLNode* insertAVL(AVLNode* node, int data) {
    // 1. 표준 BST 삽입
    if (node == NULL)
        return newAVLNode(data);

    if (data < node->data)
        node->left = insertAVL(node->left, data);
    else if (data > node->data)
        node->right = insertAVL(node->right, data);
    else // 중복 데이터 무시
        return node;

    // 2. 높이 갱신 (max_value 사용)
    node->height = 1 + max_value(height(node->left), height(node->right));

    // 3. 균형 인수 확인
    int balance = getBalance(node);

    // 4. 불균형 시 4가지 케이스 처리
    // LL Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 균형이 맞으면 노드 반환
    return node;
}


// ===================================
// 6. 탐색 함수 (비교 횟수 카운트)
// ===================================

// 배열 선형 탐색 (요청대로)
void searchArray(int arr[], int n, int key, int* count) {
    *count = 0;
    for (int i = 0; i < n; i++) {
        (*count)++; // 비교 횟수 증가
        if (arr[i] == key) {
            return; // 찾으면 종료
        }
    }
    // 못 찾아도 count는 n이 됨
}

// BST 탐색 (반복문)
void searchBST(Node* root, int key, int* count) {
    *count = 0;
    Node* current = root;
    while (current != NULL) {
        (*count)++; // 노드 방문(비교) 횟수 증가
        if (key == current->data) {
            return; // 찾음
        }
        else if (key < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // 못 찾음
}

// AVL 탐색 (BST와 로직 동일)
void searchAVL(AVLNode* root, int key, int* count) {
    *count = 0;
    AVLNode* current = root;
    while (current != NULL) {
        (*count)++; // 노드 방문(비교) 횟수 증가
        if (key == current->data) {
            return; // 찾음
        }
        else if (key < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // 못 찾음
}


// ===================================
// 7. 데이터 생성 함수
// ===================================

// 1. 0~10000 사이 무작위 정수 1000개 (중복 없이)
void generate_random(int arr[]) {
    int visited[MAX_VAL] = { 0 };
    int count = 0;
    while (count < DATA_SIZE) {
        int val = rand() % MAX_VAL;
        if (visited[val] == 0) {
            visited[val] = 1;
            arr[count++] = val;
        }
    }
}

// 2. 0~999 정렬된 정수
void generate_sorted_asc(int arr[]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        arr[i] = i;
    }
}

// 3. 999~0 정렬된 정수
void generate_sorted_desc(int arr[]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        arr[i] = 999 - i;
    }
}

// 4. 특수 공식
void generate_formula(int arr[]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        arr[i] = i * (i % 2 + 2);
    }
}

// 데이터 생성 래퍼
void generate_data(int arr[], int type, const char** description) {
    switch (type) {
    case 1:
        *description = "무작위 (중복 없음)";
        generate_random(arr);
        break;
    case 2:
        *description = "오름차순 (0~999)";
        generate_sorted_asc(arr);
        break;
    case 3:
        *description = "내림차순 (999~0)";
        generate_sorted_desc(arr);
        break;
    case 4:
        *description = "특수 공식";
        generate_formula(arr);
        break;
    }
}

// 탐색용 난수 생성 (0~10000)
void generate_search_targets(int targets[]) {
    for (int i = 0; i < DATA_SIZE; i++) {
        targets[i] = rand() % MAX_VAL;
    }
}

// ===================================
// 8. 메모리 해제
// ===================================
void freeBST(Node* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

void freeAVL(AVLNode* root) {
    if (root != NULL) {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}


// ===================================
// 9. 메인 실행 함수
// ===================================
int main() {
    srand(time(NULL));

    int search_keys[DATA_SIZE];
    generate_search_targets(search_keys); // 탐색 키는 한 번만 생성

    for (int test_case = 1; test_case <= 4; test_case++) {
        // --- 1. 데이터 생성 ---
        int data[DATA_SIZE];
        const char* description;
        generate_data(data, test_case, &description);

        printf("==============================================\n");
        printf(" 테스트 케이스 %d: [%s] 데이터 삽입\n", test_case, description);
        printf("==============================================\n");

        // --- 2. 자료구조 초기화 및 삽입 ---
        // 배열은 data[] 자체를 사용
        Node* bst_root = NULL;
        AVLNode* avl_root = NULL;

        for (int i = 0; i < DATA_SIZE; i++) {
            bst_root = insertBST(bst_root, data[i]);
            avl_root = insertAVL(avl_root, data[i]);
        }

        // --- 3. 탐색 및 평균 계산 ---
        long long total_array_count = 0;
        long long total_bst_count = 0;
        long long total_avl_count = 0;

        for (int i = 0; i < DATA_SIZE; i++) {
            int key = search_keys[i];
            int count_arr = 0, count_bst = 0, count_avl = 0;

            searchArray(data, DATA_SIZE, key, &count_arr);
            searchBST(bst_root, key, &count_bst);
            searchAVL(avl_root, key, &count_avl);

            total_array_count += count_arr;
            total_bst_count += count_bst;
            total_avl_count += count_avl;
        }

        // --- 4. 결과 출력 ---
        printf(" [결과] 1000회 탐색 평균 비교 횟수:\n");
        printf(" 1. 배열 (선형 탐색) \t: %.2f 회\n", (double)total_array_count / DATA_SIZE);
        printf(" 2. 이진 탐색 트리 (BST): %.2f 회\n", (double)total_bst_count / DATA_SIZE);
        printf(" 3. AVL 트리         \t: %.2f 회\n", (double)total_avl_count / DATA_SIZE);
        printf("\n");

        // --- 5. 메모리 해제 ---
        freeBST(bst_root);
        freeAVL(avl_root);
    }

    return 0;
}
