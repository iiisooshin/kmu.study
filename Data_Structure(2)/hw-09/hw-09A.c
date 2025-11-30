#define _CRT_SECURE_NO_WARNINGS  // Visual Studio 보안 경고 무시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// [1] 환경 설정 (반복 횟수 조정)
// ============================================================================

// 느린 정렬 (버블, 선택, 삽입) 반복 횟수
#define REPEAT_SLOW 10

// 빠른 정렬 (셸, 퀵, 힙, 병합, 기수, 트리) 반복 횟수
#define REPEAT_FAST 1000

#define MAX_NAME_LEN 50
#define MAX_LINE_LEN 200

// ============================================================================
// [2] 데이터 구조 및 전역 변수
// ============================================================================

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char gender;
    int korean;
    int english;
    int math;
} Student;

// 성능 측정용 전역 변수
long long comparison_count = 0;
long long memory_usage = 0;

// ============================================================================
// [3] 파일 로드 함수
// ============================================================================

Student* load_students(const char* filename, int* out_count) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        return NULL;
    }

    char line[MAX_LINE_LEN];
    int capacity = 10;
    int count = 0;
    Student* arr = (Student*)malloc(sizeof(Student) * capacity);

    if (!arr) {
        perror("메모리 할당 실패");
        fclose(fp);
        return NULL;
    }

    // 헤더 스킵
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        if (count >= capacity) {
            capacity *= 2;
            Student* temp = (Student*)realloc(arr, sizeof(Student) * capacity);
            if (!temp) {
                perror("메모리 재할당 실패");
                free(arr);
                fclose(fp);
                return NULL;
            }
            arr = temp;
        }

        Student s;
        char* token = strtok(line, ",");
        s.id = atoi(token);

        token = strtok(NULL, ",");
        strncpy(s.name, token, MAX_NAME_LEN);
        s.name[MAX_NAME_LEN - 1] = '\0';

        token = strtok(NULL, ",");
        s.gender = token[0];

        token = strtok(NULL, ",");
        s.korean = atoi(token);

        token = strtok(NULL, ",");
        s.english = atoi(token);

        token = strtok(NULL, ",");
        s.math = atoi(token);

        arr[count++] = s;
    }

    fclose(fp);

    Student* tight = (Student*)realloc(arr, sizeof(Student) * count);
    if (!tight) {
        *out_count = count;
        return arr;
    }
    arr = tight;
    *out_count = count;
    return arr;
}

// ============================================================================
// [4] 비교 함수 (Comparison Functions)
// ============================================================================

int cmp_id_asc(const void* a, const void* b) {
    comparison_count++;
    return ((Student*)a)->id - ((Student*)b)->id;
}

int cmp_id_desc(const void* a, const void* b) {
    comparison_count++;
    return ((Student*)b)->id - ((Student*)a)->id;
}

int cmp_name_asc(const void* a, const void* b) {
    comparison_count++;
    return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

int cmp_name_desc(const void* a, const void* b) {
    comparison_count++;
    return strcmp(((Student*)b)->name, ((Student*)a)->name);
}

int cmp_gender_asc(const void* a, const void* b) {
    comparison_count++;
    return ((Student*)a)->gender - ((Student*)b)->gender;
}

int cmp_gender_desc(const void* a, const void* b) {
    comparison_count++;
    return ((Student*)b)->gender - ((Student*)a)->gender;
}

int cmp_grade_total_asc(const void* a, const void* b) {
    comparison_count++;
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    int sum1 = s1->korean + s1->english + s1->math;
    int sum2 = s2->korean + s2->english + s2->math;

    if (sum1 != sum2) return sum1 - sum2;

    comparison_count++;
    if (s1->korean != s2->korean) return s1->korean - s2->korean;
    comparison_count++;
    if (s1->english != s2->english) return s1->english - s2->english;
    comparison_count++;
    return s1->math - s2->math;
}

int cmp_grade_total_desc(const void* a, const void* b) {
    comparison_count++;
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    int sum1 = s1->korean + s1->english + s1->math;
    int sum2 = s2->korean + s2->english + s2->math;

    if (sum1 != sum2) return sum2 - sum1;

    comparison_count++;
    if (s1->korean != s2->korean) return s2->korean - s1->korean;
    comparison_count++;
    if (s1->english != s2->english) return s2->english - s1->english;
    comparison_count++;
    return s2->math - s1->math;
}

// ============================================================================
// [5] 정렬 알고리즘 (9가지)
// ============================================================================

void bubble_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (cmp(&arr[j], &arr[j + 1]) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (cmp(&arr[j], &arr[min_idx]) < 0) min_idx = j;
        }
        if (min_idx != i) {
            Student temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void insertion_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shell_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
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

void quick_sort_recursive(Student* arr, int low, int high, int (*cmp)(const void*, const void*)) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        Student temp_swap = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp_swap;

        Student pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (cmp(&arr[j], &pivot) <= 0) {
                i++;
                Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Student temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quick_sort_recursive(arr, low, pi - 1, cmp);
        quick_sort_recursive(arr, pi + 1, high, cmp);
    }
}
void quick_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    quick_sort_recursive(arr, 0, n - 1, cmp);
}

void heapify(Student* arr, int n, int i, int (*cmp)(const void*, const void*)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && cmp(&arr[left], &arr[largest]) > 0) largest = left;
    if (right < n && cmp(&arr[right], &arr[largest]) > 0) largest = right;
    if (largest != i) {
        Student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, cmp);
    }
}
void heap_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i, cmp);
    for (int i = n - 1; i > 0; i--) {
        Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, cmp);
    }
}

void merge(Student* arr, int l, int m, int r, Student* temp, int (*cmp)(const void*, const void*)) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (cmp(&arr[i], &arr[j]) <= 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}
void merge_sort_recursive(Student* arr, int l, int r, Student* temp, int (*cmp)(const void*, const void*)) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m, temp, cmp);
        merge_sort_recursive(arr, m + 1, r, temp, cmp);
        merge(arr, l, m, r, temp, cmp);
    }
}
void merge_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    memory_usage += n * sizeof(Student);
    Student* temp = (Student*)malloc(n * sizeof(Student));
    if (temp) {
        merge_sort_recursive(arr, 0, n - 1, temp, cmp);
        free(temp);
    }
}

// --------------------------------------------------------
// [AVL 트리 구현]
// --------------------------------------------------------

typedef struct AVLNode {
    Student data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int height(AVLNode* N) {
    if (N == NULL) return 0;
    return N->height;
}

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* new_avl_node(Student data) {
    memory_usage += sizeof(AVLNode);
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_val(height(y->left), height(y->right)) + 1;
    x->height = max_val(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_val(height(x->left), height(x->right)) + 1;
    y->height = max_val(height(y->left), height(y->right)) + 1;

    return y;
}

int get_balance(AVLNode* N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

AVLNode* insert_avl(AVLNode* node, Student data, int (*cmp)(const void*, const void*)) {
    if (node == NULL)
        return new_avl_node(data);

    int compare_result = cmp(&data, &node->data);

    if (compare_result < 0)
        node->left = insert_avl(node->left, data, cmp);
    else if (compare_result > 0)
        node->right = insert_avl(node->right, data, cmp);
    else {
        // 중복 데이터 처리 (오른쪽 삽입)
        node->right = insert_avl(node->right, data, cmp);
    }

    node->height = 1 + max_val(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Left Left
    if (balance > 1 && cmp(&data, &node->left->data) < 0)
        return right_rotate(node);

    // Right Right (중복 데이터 고려 >= 0)
    if (balance < -1 && cmp(&data, &node->right->data) >= 0)
        return left_rotate(node);

    // Left Right
    if (balance > 1 && cmp(&data, &node->left->data) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left
    if (balance < -1 && cmp(&data, &node->right->data) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void store_avl_sorted(AVLNode* root, Student* arr, int* i) {
    if (root != NULL) {
        store_avl_sorted(root->left, arr, i);
        arr[(*i)++] = root->data;
        store_avl_sorted(root->right, arr, i);
    }
}

void free_avl_tree(AVLNode* root) {
    if (root != NULL) {
        free_avl_tree(root->left);
        free_avl_tree(root->right);
        free(root);
    }
}

void tree_sort(Student* arr, int n, int (*cmp)(const void*, const void*)) {
    AVLNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert_avl(root, arr[i], cmp);
    }
    int i = 0;
    store_avl_sorted(root, arr, &i);
    free_avl_tree(root);
}

// ============================================================================
// [6] 기수 정렬 (Radix Sort) 확장
// ============================================================================

int get_max_id(Student* arr, int n) {
    int max = arr[0].id;
    for (int i = 1; i < n; i++) if (arr[i].id > max) max = arr[i].id;
    return max;
}
void count_sort_radix_id(Student* arr, int n, int exp) {
    memory_usage += (n * sizeof(Student)) + (10 * sizeof(int));
    Student* output = (Student*)malloc(n * sizeof(Student));
    int count[10] = { 0 };
    for (int i = 0; i < n; i++) count[(arr[i].id / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i].id / exp) % 10] - 1] = arr[i];
        count[(arr[i].id / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}
void radix_sort_id(Student* arr, int n) {
    int m = get_max_id(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) count_sort_radix_id(arr, n, exp);
}

void count_sort_for_name(Student* arr, int n, int char_idx, int is_desc) {
    memory_usage += (n * sizeof(Student)) + (256 * sizeof(int));
    Student* output = (Student*)malloc(n * sizeof(Student));
    int count[256] = { 0 };
    for (int i = 0; i < n; i++) {
        unsigned char c = (char_idx < strlen(arr[i].name)) ? (unsigned char)arr[i].name[char_idx] : 0;
        count[c]++;
    }
    if (!is_desc) {
        for (int i = 1; i < 256; i++) count[i] += count[i - 1];
    }
    else {
        for (int i = 254; i >= 0; i--) count[i] += count[i + 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        unsigned char c = (char_idx < strlen(arr[i].name)) ? (unsigned char)arr[i].name[char_idx] : 0;
        output[count[c] - 1] = arr[i];
        count[c]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}
void radix_sort_name(Student* arr, int n, int is_desc) {
    for (int i = MAX_NAME_LEN - 1; i >= 0; i--) count_sort_for_name(arr, n, i, is_desc);
}

void radix_sort_gender(Student* arr, int n, int is_desc) {
    memory_usage += (n * sizeof(Student)) + (256 * sizeof(int));
    Student* output = (Student*)malloc(n * sizeof(Student));
    int count[256] = { 0 };
    for (int i = 0; i < n; i++) count[(unsigned char)arr[i].gender]++;
    if (!is_desc) {
        for (int i = 1; i < 256; i++) count[i] += count[i - 1];
    }
    else {
        for (int i = 254; i >= 0; i--) count[i] += count[i + 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        unsigned char c = (unsigned char)arr[i].gender;
        output[count[c] - 1] = arr[i];
        count[c]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void count_sort_grade_field(Student* arr, int n, int field_type, int is_desc) {
    int max_val = (field_type == 3) ? 300 : 100;
    memory_usage += (n * sizeof(Student)) + ((max_val + 1) * sizeof(int));
    Student* output = (Student*)malloc(n * sizeof(Student));
    int* count = (int*)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        int val = 0;
        if (field_type == 0) val = arr[i].math;
        else if (field_type == 1) val = arr[i].english;
        else if (field_type == 2) val = arr[i].korean;
        else if (field_type == 3) val = arr[i].korean + arr[i].english + arr[i].math;
        count[val]++;
    }
    if (!is_desc) {
        for (int i = 1; i <= max_val; i++) count[i] += count[i - 1];
    }
    else {
        for (int i = max_val - 1; i >= 0; i--) count[i] += count[i + 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int val = 0;
        if (field_type == 0) val = arr[i].math;
        else if (field_type == 1) val = arr[i].english;
        else if (field_type == 2) val = arr[i].korean;
        else if (field_type == 3) val = arr[i].korean + arr[i].english + arr[i].math;
        output[count[val] - 1] = arr[i];
        count[val]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
    free(count);
}
void radix_sort_grade(Student* arr, int n, int is_desc) {
    count_sort_grade_field(arr, n, 0, is_desc);
    count_sort_grade_field(arr, n, 1, is_desc);
    count_sort_grade_field(arr, n, 2, is_desc);
    count_sort_grade_field(arr, n, 3, is_desc);
}

// ============================================================================
// [7] 메인 함수
// ============================================================================

typedef void (*SortFunc)(Student*, int, int (*)(const void*, const void*));

typedef struct {
    char* name;
    SortFunc func;
    int is_stable; // 1: Stable, 0: Unstable
} AlgoInfo;

typedef struct {
    char* name;
    int (*cmp)(const void*, const void*);
    int is_gender;
} CriteriaInfo;

int main() {
    int count = 0;
    const char* filename = "dataset_id_ascending.csv";

    // 1. 파일 로드
    printf(">> 파일 로딩 중: %s ...\n", filename);
    Student* original_data = load_students(filename, &count);

    if (original_data == NULL) {
        fprintf(stderr, "파일 로딩 실패.\n");
        return 1;
    }
    printf(">> 로딩 완료: %d students.\n", count);
    printf(">> 반복 설정: Slow=%d회, Fast=%d회\n\n", REPEAT_SLOW, REPEAT_FAST);

    // 2. 알고리즘 초기화
    AlgoInfo algos[] = {
        {"Bubble Sort", bubble_sort, 1},
        {"Selection Sort", selection_sort, 0},
        {"Insertion Sort", insertion_sort, 1},
        {"Shell Sort", shell_sort, 0},
        {"Quick Sort", quick_sort, 0},
        {"Heap Sort", heap_sort, 0},
        {"Merge Sort", merge_sort, 1}
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
    printf("| %-15s | %-20s | %-12s | %-12s |\n", "Algorithm", "Criteria", "Avg Comp", "Avg Mem(B)");
    printf("=================================================================================\n");

    // [Part 1] Bubble ~ Merge
    for (int i = 0; i < algo_count; i++) {
        for (int j = 0; j < criteria_count; j++) {

            if (criteria[j].is_gender && !algos[i].is_stable) continue;

            printf(">> [진행중] %-12s - %-18s 정렬 연산 중...       \r", algos[i].name, criteria[j].name);
            fflush(stdout);

            long long total_comp = 0;
            long long total_mem = 0;

            // [변경됨] 버블, 선택, 삽입 정렬은 적게 반복, 나머지는 많이 반복
            int repeat_count = REPEAT_FAST;
            if (strcmp(algos[i].name, "Bubble Sort") == 0 ||
                strcmp(algos[i].name, "Selection Sort") == 0 ||
                strcmp(algos[i].name, "Insertion Sort") == 0) {
                repeat_count = REPEAT_SLOW;
            }

            for (int k = 0; k < repeat_count; k++) {
                memcpy(test_data, original_data, sizeof(Student) * count);
                comparison_count = 0;
                memory_usage = 0;
                algos[i].func(test_data, count, criteria[j].cmp);
                total_comp += comparison_count;
                total_mem += memory_usage;
            }

            printf("| %-15s | %-20s | %12lld | %12lld |      \n",
                algos[i].name, criteria[j].name,
                total_comp / repeat_count, total_mem / repeat_count);
        }
        printf("---------------------------------------------------------------------------------\n");
    }

    // [Part 2] Radix Sort
    struct {
        char* name;
        int is_desc;
        void (*func)(Student*, int, int);
    } radix_tests[] = {
        {"ID Ascending", 0, NULL},
        {"Name Ascending", 0, radix_sort_name},
        {"Name Descending", 1, radix_sort_name},
        {"Gender Ascending", 0, radix_sort_gender},
        {"Gender Descending", 1, radix_sort_gender},
        {"Grade Sum Ascending", 0, radix_sort_grade},
        {"Grade Sum Descending", 1, radix_sort_grade}
    };
    int radix_count = sizeof(radix_tests) / sizeof(radix_tests[0]);

    for (int j = 0; j < radix_count; j++) {
        printf(">> [진행중] %-12s - %-18s 정렬 연산 중...       \r", "Radix Sort", radix_tests[j].name);
        fflush(stdout);

        long long total_mem = 0;

        for (int k = 0; k < REPEAT_FAST; k++) {
            memcpy(test_data, original_data, sizeof(Student) * count);
            memory_usage = 0;
            if (strstr(radix_tests[j].name, "ID") != NULL) {
                if (radix_tests[j].is_desc == 0) radix_sort_id(test_data, count);
            }
            else {
                radix_tests[j].func(test_data, count, radix_tests[j].is_desc);
            }
            total_mem += memory_usage;
        }

        printf("| %-15s | %-20s | %12s | %12lld |      \n",
            "Radix Sort", radix_tests[j].name, "0 (Non-cmp)", total_mem / REPEAT_FAST);
    }
    printf("---------------------------------------------------------------------------------\n");

    // [Part 3] Tree Sort (AVL)
    AlgoInfo tree_algo = { "Tree Sort", tree_sort, 1 };

    for (int j = 0; j < criteria_count; j++) {

        printf(">> [진행중] %-12s - %-18s 정렬 연산 중...       \r", tree_algo.name, criteria[j].name);
        fflush(stdout);

        long long total_comp = 0;
        long long total_mem = 0;

        for (int k = 0; k < REPEAT_FAST; k++) {
            memcpy(test_data, original_data, sizeof(Student) * count);
            comparison_count = 0;
            memory_usage = 0;
            tree_algo.func(test_data, count, criteria[j].cmp);
            total_comp += comparison_count;
            total_mem += memory_usage;
        }

        printf("| %-15s | %-20s | %12lld | %12lld |      \n",
            tree_algo.name, criteria[j].name,
            total_comp / REPEAT_FAST, total_mem / REPEAT_FAST);
    }
    printf("---------------------------------------------------------------------------------\n");

    free(test_data);
    free(original_data);

    printf("\n>> 모든 테스트가 완료되었습니다.\n");
    return 0;
}
