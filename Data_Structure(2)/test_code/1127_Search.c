#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_STUDENTS 33000
#define NAME_LEN     64
#define NUM_TRIALS   40    // 임의 연산 횟수

typedef struct {
    int id;
    char name[NAME_LEN];
    char gender;          // 'M' or 'F'
    int korean;
    int english;
    int math;
    int mul_of_score;     // korean * english * math
} Student;

// ---- 전역 변수 ----
long long g_sort_comp_count = 0; // qsort 비교 횟수 집계용
int last_id = 0;

/* =====================================================
 * 유틸리티 및 비교 함수
 * ===================================================== */
int compare_by_mul(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    g_sort_comp_count++; // 비교 발생 시 카운트 증가
    if (s1->mul_of_score < s2->mul_of_score) return -1;
    else if (s1->mul_of_score > s2->mul_of_score) return 1;
    else return (s1->id < s2->id) ? -1 : (s1->id > s2->id) ? 1 : 0;
}

Student create_dummy_student(int key) {
    Student s;
    s.id = ++last_id;
    s.gender = (rand() % 2) ? 'M' : 'F';
    s.korean = 0; s.english = 0; s.math = 0;
    s.mul_of_score = key;
    strcpy_s(s.name, sizeof(s.name), "RANDOM");
    return s;
}

/* =====================================================
 * [1] 정렬되지 않은 배열 (순차 탐색)
 * ===================================================== */
int sequential_search(Student arr[], int n, int key, int* compCount) {
    *compCount = 0;
    for (int i = 0; i < n; i++) {
        (*compCount)++;
        if (arr[i].mul_of_score == key) return i;
    }
    return -1;
}

int unsorted_insert(Student arr[], int* n, int key, int* compCount) {
    if (sequential_search(arr, *n, key, compCount) != -1) return 0; // 중복
    if (*n >= MAX_STUDENTS) return 0;
    arr[*n] = create_dummy_student(key);
    (*n)++;
    return 1;
}

int unsorted_delete(Student arr[], int* n, int key, int* compCount) {
    int idx = sequential_search(arr, *n, key, compCount);
    if (idx == -1) return 0;
    arr[idx] = arr[*n - 1]; // 끝 원소로 덮어쓰기
    (*n)--;
    return 1;
}

/* =====================================================
 * [2] 정렬된 배열 (이진 탐색)
 * ===================================================== */
int binary_search(Student arr[], int n, int key, int* compCount) {
    int low = 0, high = n - 1;
    *compCount = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        (*compCount)++;
        if (arr[mid].mul_of_score == key) return mid;
        else if (key < arr[mid].mul_of_score) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int lower_bound(Student arr[], int n, int key, int* compCount) {
    int low = 0, high = n;
    *compCount = 0;
    while (low < high) {
        int mid = (low + high) / 2;
        (*compCount)++;
        if (arr[mid].mul_of_score < key) low = mid + 1;
        else high = mid;
    }
    return low;
}

int sorted_insert(Student arr[], int* n, int key, int* compCount) {
    if (*n >= MAX_STUDENTS) return 0;
    int pos = lower_bound(arr, *n, key, compCount);

    // 중복 체크
    if (pos < *n) {
        (*compCount)++;
        if (arr[pos].mul_of_score == key) return 0;
    }

    // Shift
    int moves = (*n - pos);
    for (int i = *n; i > pos; i--) arr[i] = arr[i - 1];
    *compCount += moves; // 이동 비용 포함

    arr[pos] = create_dummy_student(key);
    (*n)++;
    return 1;
}

int sorted_delete(Student arr[], int* n, int key, int* compCount) {
    int idx = binary_search(arr, *n, key, compCount);
    if (idx == -1) return 0;

    // Shift
    int moves = (*n - 1 - idx);
    for (int i = idx; i < *n - 1; i++) arr[i] = arr[i + 1];
    *compCount += moves;
    (*n)--;
    return 1;
}

/* =====================================================
 * [3] AVL 트리
 * ===================================================== */
typedef struct AVLNode {
    Student data;
    struct AVLNode* left, * right;
    int height;
} AVLNode;

int my_max(int a, int b) { return (a > b) ? a : b; }
int height(AVLNode* n) { return n ? n->height : 0; }
AVLNode* newNode(Student s) {
    AVLNode* p = (AVLNode*)malloc(sizeof(AVLNode));
    p->data = s; p->left = p->right = NULL; p->height = 1;
    return p;
}
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left; AVLNode* T = x->right;
    x->right = y; y->left = T;
    y->height = my_max(height(y->left), height(y->right)) + 1;
    x->height = my_max(height(x->left), height(x->right)) + 1;
    return x;
}
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right; AVLNode* T = y->left;
    y->left = x; x->right = T;
    x->height = my_max(height(x->left), height(x->right)) + 1;
    y->height = my_max(height(y->left), height(y->right)) + 1;
    return y;
}
int getBalance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

// AVL Insert
AVLNode* avl_insert_node(AVLNode* node, Student s, int* comp, int* success) {
    if (!node) { *success = 1; return newNode(s); }
    (*comp)++;
    if (s.mul_of_score < node->data.mul_of_score) node->left = avl_insert_node(node->left, s, comp, success);
    else if (s.mul_of_score > node->data.mul_of_score) node->right = avl_insert_node(node->right, s, comp, success);
    else { *success = 0; return node; } // 중복

    node->height = 1 + my_max(height(node->left), height(node->right));
    int bal = getBalance(node);
    if (bal > 1 && s.mul_of_score < node->left->data.mul_of_score) return rotateRight(node);
    if (bal < -1 && s.mul_of_score > node->right->data.mul_of_score) return rotateLeft(node);
    if (bal > 1 && s.mul_of_score > node->left->data.mul_of_score) { node->left = rotateLeft(node->left); return rotateRight(node); }
    if (bal < -1 && s.mul_of_score < node->right->data.mul_of_score) { node->right = rotateRight(node->right); return rotateLeft(node); }
    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

// AVL Delete
AVLNode* avl_delete_node(AVLNode* root, int key, int* comp, int* success) {
    if (!root) { *success = 0; return root; }
    (*comp)++;
    if (key < root->data.mul_of_score) root->left = avl_delete_node(root->left, key, comp, success);
    else if (key > root->data.mul_of_score) root->right = avl_delete_node(root->right, key, comp, success);
    else {
        *success = 1;
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) { temp = root; root = NULL; }
            else *root = *temp;
            free(temp);
        }
        else {
            AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = avl_delete_node(root->right, temp->data.mul_of_score, comp, success);
        }
    }
    if (!root) return root;
    root->height = 1 + my_max(height(root->left), height(root->right));
    int bal = getBalance(root);
    if (bal > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (bal > 1 && getBalance(root->left) < 0) { root->left = rotateLeft(root->left); return rotateRight(root); }
    if (bal < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (bal < -1 && getBalance(root->right) > 0) { root->right = rotateRight(root->right); return rotateLeft(root); }
    return root;
}

int avl_search(AVLNode* root, int key, int* comp) {
    *comp = 0;
    while (root) {
        (*comp)++;
        if (key == root->data.mul_of_score) return 1;
        root = (key < root->data.mul_of_score) ? root->left : root->right;
    }
    return 0;
}

void freeAVL(AVLNode* node) {
    if (node) { freeAVL(node->left); freeAVL(node->right); free(node); }
}

/* =====================================================
 * [4] 보간 탐색 (정렬된 배열)
 * ===================================================== */
int interpolation_search(Student arr[], int n, int key, int* compCount) {
    int low = 0, high = n - 1;
    *compCount = 0;
    while (low <= high && key >= arr[low].mul_of_score && key <= arr[high].mul_of_score) {
        (*compCount)++;
        if (low == high) return (arr[low].mul_of_score == key) ? low : -1;

        long long diff_key = (long long)key - arr[low].mul_of_score;
        long long diff_range = (long long)arr[high].mul_of_score - arr[low].mul_of_score;
        if (diff_range == 0) return (arr[low].mul_of_score == key) ? low : -1;

        int pos = low + (int)((double)diff_key / diff_range * (high - low));
        if (pos < low) pos = low; if (pos > high) pos = high;

        if (arr[pos].mul_of_score == key) return pos;
        if (arr[pos].mul_of_score < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

/* =====================================================
 * 메인 함수
 * ===================================================== */
int parse_student_line(const char* line, Student* stu) {
    char buffer[256], * token, * ctx = NULL;
    strcpy_s(buffer, sizeof(buffer), line);
    token = strtok_s(buffer, ",\n", &ctx); if (!token) return 0; stu->id = atoi(token); last_id = stu->id;
    token = strtok_s(NULL, ",\n", &ctx); if (!token) return 0; strcpy_s(stu->name, sizeof(stu->name), token);
    token = strtok_s(NULL, ",\n", &ctx); if (!token) return 0; stu->gender = token[0];
    token = strtok_s(NULL, ",\n", &ctx); if (!token) return 0; stu->korean = atoi(token);
    token = strtok_s(NULL, ",\n", &ctx); if (!token) return 0; stu->english = atoi(token);
    token = strtok_s(NULL, ",\n", &ctx); if (!token) return 0; stu->math = atoi(token);
    stu->mul_of_score = stu->korean * stu->english * stu->math;
    return 1;
}

// 각 실험을 위한 별도의 데이터 공간
Student students[MAX_STUDENTS];             // A. 순차
Student sorted_bin[MAX_STUDENTS];           // B. 이진
Student sorted_interp[MAX_STUDENTS];        // D. 보간

int main(void) {
    FILE* fp = NULL;
    char line[256];
    int n = 0;

    // 1. 파일 읽기
    if (fopen_s(&fp, "students.csv", "r") != 0 || !fp) {
        printf("students.csv 파일 오류\n"); return 1;
    }
    fgets(line, sizeof(line), fp); // 헤더 스킵
    while (fgets(line, sizeof(line), fp) && n < MAX_STUDENTS) {
        if (line[0] == '\n') continue;
        if (parse_student_line(line, &students[n])) n++;
    }
    fclose(fp);
    if (n == 0) return 1;
    printf("데이터 로드: %d명\n", n);

    // 2. 실험 데이터 준비 및 초기 구축 비용 측정

    // --- (1) AVL 트리 구축 및 비용 측정 ---
    AVLNode* avl_root = NULL;
    long long avl_build_cost = 0;
    int tmp_comp = 0, tmp_succ = 0;

    for (int i = 0; i < n; i++) {
        tmp_comp = 0;
        avl_root = avl_insert_node(avl_root, students[i], &tmp_comp, &tmp_succ);
        avl_build_cost += tmp_comp;
    }

    // --- (2) 배열 복사 및 정렬 비용 측정 ---
    for (int i = 0; i < n; i++) sorted_bin[i] = students[i];

    g_sort_comp_count = 0;
    qsort(sorted_bin, n, sizeof(Student), compare_by_mul);
    long long array_sort_cost = g_sort_comp_count;

    // 보간 탐색용 배열 복사 및 정렬
    for (int i = 0; i < n; i++) sorted_interp[i] = students[i];
    qsort(sorted_interp, n, sizeof(Student), compare_by_mul);

    printf("\n======================================================\n");
    printf(" [초기 데이터 구축 비용 비교]\n");
    printf("======================================================\n");
    printf(" 1. 배열 정렬 비용 (Quick Sort): %lld 회\n", array_sort_cost);
    printf(" 2. AVL 트리 구축 비용 (Insert): %lld 회\n", avl_build_cost);
    printf("======================================================\n");

    // 3. 공통 랜덤 키 생성
    srand((unsigned)time(NULL));
    int keys[NUM_TRIALS];
    for (int i = 0; i < NUM_TRIALS; i++) keys[i] = rand() % 1000001;

    // ★ 수정됨: 콤마 대신 탭(\t) 사용, 헤더 정렬 ★
#define RUN_EXPERIMENT(Title, LogicCode) \
    { \
        printf("\n======================================================\n"); \
        printf(" %s\n", Title); \
        printf("======================================================\n"); \
        printf("(Op: 0=Insert, 1=Delete, 2=Search)\n"); \
        printf("시도\tKey\tOp\t이번비교\t누적비교\t평균비교\t결과\n"); \
        long long total_comp = 0; \
        int cur_n = n; \
        for (int t = 0; t < NUM_TRIALS; t++) { \
            int key = keys[t]; \
            int op = key % 3; \
            int comp = 0, ok = 0; \
            LogicCode \
            total_comp += comp; \
            printf("%d\t%d\t%d\t%d\t\t%lld\t\t%.2f   \t%s\n", \
                t + 1, key, op, comp, total_comp, (double)total_comp / (t + 1), ok ? "OK" : "FAIL"); \
        } \
    }

    /* === A. 순차 탐색 실험 === */
    RUN_EXPERIMENT("A) 순차 탐색 (Unsorted Array)",
        if (op == 0) ok = unsorted_insert(students, &cur_n, key, &comp);
        else if (op == 1) ok = unsorted_delete(students, &cur_n, key, &comp);
        else { (void)sequential_search(students, cur_n, key, &comp); ok = 1; }
            );

    /* === B. 이진 탐색 실험 === */
    RUN_EXPERIMENT("B) 이진 탐색 (Sorted Array)",
        if (op == 0) ok = sorted_insert(sorted_bin, &cur_n, key, &comp);
        else if (op == 1) ok = sorted_delete(sorted_bin, &cur_n, key, &comp);
        else { (void)binary_search(sorted_bin, cur_n, key, &comp); ok = 1; }
            );

    /* === C. AVL 트리 실험 === */
    RUN_EXPERIMENT("C) AVL 트리 (Balanced BST)",
        if (op == 0) avl_root = avl_insert_node(avl_root, create_dummy_student(key), &comp, &ok);
        else if (op == 1) avl_root = avl_delete_node(avl_root, key, &comp, &ok);
        else { ok = avl_search(avl_root, key, &comp); }
            );
    freeAVL(avl_root);

    /* === D. 보간 탐색 실험 === */
    RUN_EXPERIMENT("D) 보간 탐색 (Sorted Array + Interpolation)",
        if (op == 0) ok = sorted_insert(sorted_interp, &cur_n, key, &comp);
        else if (op == 1) ok = sorted_delete(sorted_interp, &cur_n, key, &comp);
        else {
            int idx = interpolation_search(sorted_interp, cur_n, key, &comp);
            ok = (idx != -1);
        }
            );

    return 0;
}
