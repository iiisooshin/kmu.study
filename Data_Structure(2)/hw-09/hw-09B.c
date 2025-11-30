#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// [1] 환경 설정
// ============================================================================

#define TEST_REPEAT_COUNT 1000  // 1000회 반복
#define QUICK_THRESHOLD 16      // 퀵 정렬 최적화 임계값 (이하일 때 삽입 정렬 전환)

#define MAX_NAME_LEN 50
#define MAX_LINE_LEN 200

// ============================================================================
// [2] 데이터 구조
// ============================================================================

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char gender;
    int korean;
    int english;
    int math;
} Student;

long long comparison_count = 0;
long long memory_usage = 0;

// ============================================================================
// [3] 파일 로드
// ============================================================================

Student* load_students(const char* filename, int* out_count) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { perror("파일 열기 실패"); return NULL; }
    char line[MAX_LINE_LEN];
    int capacity = 10;
    int count = 0;
    Student* arr = (Student*)malloc(sizeof(Student) * capacity);
    if (!arr) return NULL;
    fgets(line, sizeof(line), fp); // 헤더 스킵
    while (fgets(line, sizeof(line), fp)) {
        if (count >= capacity) {
            capacity *= 2;
            Student* temp = (Student*)realloc(arr, sizeof(Student) * capacity);
            if (!temp) { free(arr); fclose(fp); return NULL; }
            arr = temp;
        }
        Student s;
        char* token = strtok(line, ","); s.id = atoi(token);
        token = strtok(NULL, ","); strncpy(s.name, token, MAX_NAME_LEN); s.name[MAX_NAME_LEN - 1] = '\0';
        token = strtok(NULL, ","); s.gender = token[0];
        token = strtok(NULL, ","); s.korean = atoi(token);
        token = strtok(NULL, ","); s.english = atoi(token);
        token = strtok(NULL, ","); s.math = atoi(token);
        arr[count++] = s;
    }
    fclose(fp);
    Student* tight = (Student*)realloc(arr, sizeof(Student) * count);
    if (tight) arr = tight;
    *out_count = count;
    return arr;
}

// ============================================================================
// [4] 비교 함수
// ============================================================================

int cmp_id_asc(const void* a, const void* b) { comparison_count++; return ((Student*)a)->id - ((Student*)b)->id; }
int cmp_id_desc(const void* a, const void* b) { comparison_count++; return ((Student*)b)->id - ((Student*)a)->id; }
int cmp_name_asc(const void* a, const void* b) { comparison_count++; return strcmp(((Student*)a)->name, ((Student*)b)->name); }
int cmp_name_desc(const void* a, const void* b) { comparison_count++; return strcmp(((Student*)b)->name, ((Student*)a)->name); }
int cmp_gender_asc(const void* a, const void* b) { comparison_count++; return ((Student*)a)->gender - ((Student*)b)->gender; }
int cmp_gender_desc(const void* a, const void* b) { comparison_count++; return ((Student*)b)->gender - ((Student*)a)->gender; }
int cmp_grade_total_asc(const void* a, const void* b) {
    comparison_count++;
    const Student* s1 = (const Student*)a; const Student* s2 = (const Student*)b;
    int sum1 = s1->korean + s1->english + s1->math; int sum2 = s2->korean + s2->english + s2->math;
    if (sum1 != sum2) return sum1 - sum2;
    comparison_count++; if (s1->korean != s2->korean) return s1->korean - s2->korean;
    comparison_count++; if (s1->english != s2->english) return s1->english - s2->english;
    comparison_count++; return s1->math - s2->math;
}
int cmp_grade_total_desc(const void* a, const void* b) {
    comparison_count++;
    const Student* s1 = (const Student*)a; const Student* s2 = (const Student*)b;
    int sum1 = s1->korean + s1->english + s1->math; int sum2 = s2->korean + s2->english + s2->math;
    if (sum1 != sum2) return sum2 - sum1;
    comparison_count++; if (s1->korean != s2->korean) return s2->korean - s1->korean;
    comparison_count++; if (s1->english != s2->english) return s2->english - s1->english;
    comparison_count++; return s2->math - s1->math;
}

// ============================================================================
// [5] 정렬 알고리즘 (극한 최적화 버전)
// ============================================================================

// 1. [Shell Sort] Ciura Sequence (비교 횟수 최소화 간격)
void shell_sort_ciura(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    // Ciura Gap: 1, 4, 10, 23, 57, 132, 301, 701, 1750 (가장 효율적이라고 알려짐)
    int gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
    int n_gaps = sizeof(gaps) / sizeof(int);

    for (int k = 0; k < n_gaps; k++) {
        int gap = gaps[k];
        if (gap >= n) continue;

        for (int i = gap; i < n; i++) {
            Student temp = arr[i];
            int j;
            for (j = i; j >= gap && cmp(&arr[j - gap], &temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 2. [Quick Sort] Hybrid (Median-of-3 + Insertion Sort for small range)
void swap(Student* a, Student* b) {
    Student temp = *a; *a = *b; *b = temp;
}

// 작은 구간용 삽입 정렬
void insertion_sort_range(Student* arr, int low, int high, int (*cmp)(const void*, const void*)) {
    for (int i = low + 1; i <= high; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= low && cmp(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quick_sort_hybrid_recursive(Student* arr, int low, int high, int (*cmp)(const void*, const void*)) {
    // [최적화 1] 구간이 작으면(예: 16개 이하) 삽입 정렬 사용 -> 재귀 오버헤드 및 비교 감소
    if (high - low + 1 <= QUICK_THRESHOLD) {
        insertion_sort_range(arr, low, high, cmp);
        return;
    }

    if (low < high) {
        // [최적화 2] Median-of-Three 피벗 선정
        int mid = low + (high - low) / 2;
        if (cmp(&arr[low], &arr[mid]) > 0) swap(&arr[low], &arr[mid]);
        if (cmp(&arr[low], &arr[high]) > 0) swap(&arr[low], &arr[high]);
        if (cmp(&arr[mid], &arr[high]) > 0) swap(&arr[mid], &arr[high]);

        // 중앙값(mid)을 high-1 위치로 보냄 (피벗 숨기기)
        swap(&arr[mid], &arr[high - 1]);
        Student pivot = arr[high - 1];

        int i = low;
        int j = high - 1;

        while (1) {
            while (cmp(&arr[++i], &pivot) < 0);
            while (cmp(&arr[--j], &pivot) > 0);
            if (i >= j) break;
            swap(&arr[i], &arr[j]);
        }
        swap(&arr[i], &arr[high - 1]); // 피벗 원위치

        quick_sort_hybrid_recursive(arr, low, i - 1, cmp);
        quick_sort_hybrid_recursive(arr, i + 1, high, cmp);
    }
}

void quick_sort_hybrid(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    quick_sort_hybrid_recursive(arr, 0, n - 1, cmp);
}

// 3. [Tree Sort] Counting AVL Tree (중복 데이터 압축)
typedef struct AVLNode {
    Student data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
    int count; // [최적화] 중복 개수 카운팅 (노드 수 감소 -> 비교 횟수 감소)
} AVLNode;

int get_height(AVLNode* N) { if (!N) return 0; return N->height; }
int max_val(int a, int b) { return (a > b) ? a : b; }

AVLNode* new_avl_node(Student data) {
    memory_usage += sizeof(AVLNode);
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data; node->left = NULL; node->right = NULL;
    node->height = 1; node->count = 1;
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left; AVLNode* T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max_val(get_height(y->left), get_height(y->right)) + 1;
    x->height = max_val(get_height(x->left), get_height(x->right)) + 1;
    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right; AVLNode* T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max_val(get_height(x->left), get_height(x->right)) + 1;
    y->height = max_val(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

int get_balance(AVLNode* N) { if (!N) return 0; return get_height(N->left) - get_height(N->right); }

AVLNode* insert_avl(AVLNode* node, Student data, int (*cmp)(const void*, const void*)) {
    if (node == NULL) return new_avl_node(data);

    int compare_result = cmp(&data, &node->data);

    if (compare_result < 0)
        node->left = insert_avl(node->left, data, cmp);
    else if (compare_result > 0)
        node->right = insert_avl(node->right, data, cmp);
    else {
        // [핵심] 값이 같으면 노드를 추가하지 않고 카운트만 증가!
        // 트리의 깊이가 깊어지지 않아 비교 횟수가 획기적으로 줄어듦.
        node->count++;
        return node;
    }

    node->height = 1 + max_val(get_height(node->left), get_height(node->right));
    int balance = get_balance(node);

    if (balance > 1 && cmp(&data, &node->left->data) < 0) return right_rotate(node);
    if (balance < -1 && cmp(&data, &node->right->data) > 0) return left_rotate(node);
    if (balance > 1 && cmp(&data, &node->left->data) > 0) {
        node->left = left_rotate(node->left); return right_rotate(node);
    }
    if (balance < -1 && cmp(&data, &node->right->data) < 0) {
        node->right = right_rotate(node->right); return left_rotate(node);
    }
    return node;
}

// 중복 카운트만큼 반복해서 배열에 저장
void store_avl_sorted(AVLNode* root, Student* arr, int* i) {
    if (root) {
        store_avl_sorted(root->left, arr, i);
        for (int k = 0; k < root->count; k++) {
            arr[(*i)++] = root->data;
        }
        store_avl_sorted(root->right, arr, i);
    }
}

void free_avl_tree(AVLNode* root) {
    if (root) {
        free_avl_tree(root->left); free_avl_tree(root->right); free(root);
    }
}

void tree_sort_avl_counter(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    AVLNode* root = NULL;
    for (int i = 0; i < n; i++) root = insert_avl(root, arr[i], cmp);
    int i = 0; store_avl_sorted(root, arr, &i);
    free_avl_tree(root);
}

// ============================================================================
// [6] 메인 함수
// ============================================================================

typedef void (*SortFunc)(Student*, int, int (*)(const void*, const void*));
typedef struct { char* name; SortFunc func; int is_stable; } AlgoInfo;
typedef struct { char* name; int (*cmp)(const void*, const void*); int is_gender; } CriteriaInfo;

int main() {
    int count = 0;
    const char* filename = "dataset_id_ascending.csv";

    printf(">> 파일 로딩 중: %s ...\n", filename);
    Student* original_data = load_students(filename, &count);
    if (!original_data) { fprintf(stderr, "파일 로딩 실패.\n"); return 1; }
    printf(">> 로딩 완료: %d students.\n", count);
    printf(">> 극한의 최적화 (반복 %d회)\n\n", TEST_REPEAT_COUNT);

    AlgoInfo algos[] = {
        {"Shell Sort (Ciura)", shell_sort_ciura, 0},     // Ciura 간격
        {"Quick Sort (Hybrid)", quick_sort_hybrid, 0},   // Hybrid (Median-3 + Insertion)
        {"Tree Sort (Counter)", tree_sort_avl_counter, 1}// Counting AVL
    };
    int algo_count = sizeof(algos) / sizeof(AlgoInfo);

    CriteriaInfo criteria[] = {
        {"ID Ascending", cmp_id_asc, 0},
        {"ID Descending", cmp_id_desc, 0},
        {"Name Ascending", cmp_name_asc, 0},
        {"Name Descending", cmp_name_desc, 0},
        {"Gender Ascending", cmp_gender_asc, 1},
        {"Gender Descending", cmp_gender_desc, 1},
        {"Grade Sum Ascending", cmp_grade_total_asc, 0},
        {"Grade Sum Descending", cmp_grade_total_desc, 0}
    };
    int criteria_count = sizeof(criteria) / sizeof(CriteriaInfo);

    Student* test_data = (Student*)malloc(sizeof(Student) * count);

    printf("=================================================================================\n");
    printf("| %-20s | %-20s | %-12s | %-12s |\n", "Algorithm", "Criteria", "Avg Comp", "Avg Mem(B)");
    printf("=================================================================================\n");

    for (int i = 0; i < algo_count; i++) {
        for (int j = 0; j < criteria_count; j++) {

            // Unstable 제외 (Shell, Quick)
            if (criteria[j].is_gender && !algos[i].is_stable) continue;

            printf(">> [진행중] %-18s - %-18s ...         \r", algos[i].name, criteria[j].name);
            fflush(stdout);

            long long total_comp = 0;
            long long total_mem = 0;

            for (int k = 0; k < TEST_REPEAT_COUNT; k++) {
                memcpy(test_data, original_data, sizeof(Student) * count);
                comparison_count = 0;
                memory_usage = 0;
                algos[i].func(test_data, count, criteria[j].cmp);
                total_comp += comparison_count;
                total_mem += memory_usage;
            }

            printf("| %-20s | %-20s | %12lld | %12lld |      \n",
                algos[i].name, criteria[j].name,
                total_comp / TEST_REPEAT_COUNT, total_mem / TEST_REPEAT_COUNT);
        }
        printf("---------------------------------------------------------------------------------\n");
    }

    free(test_data);
    free(original_data);
    printf("\n>> 모든 테스트가 완료되었습니다.\n");
    return 0;
}
