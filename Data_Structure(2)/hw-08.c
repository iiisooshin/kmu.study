#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // memcpy를 위해 포함
#include <math.h> // pow를 위해 포함

// --- 상수 정의 ---
#define ARRAY_SIZE 10000   // 데이터 개수
#define MAX_VAL 1000000    // 최대값 (0 ~ 1,000,000)
#define NUM_TRIALS 100     // 실행 횟수

// --- 함수 프로토타입 ---
void generate_random_data(int arr[], int size, int max_val);
unsigned long long insertion_sort(int arr[], int size);
unsigned long long shell_sort_standard(int arr[], int size);
unsigned long long shell_sort_knuth(int arr[], int size);

/**
 * @brief Hibbard 시퀀스 간격(2^k - 1)을 이용한 쉘 정렬
 * @param arr 정렬할 배열
 * @param size 배열의 크기
 * @return 비교 횟수
 */
unsigned long long shell_sort_hibbard(int arr[], int size);

/**
 * @brief Ciura 시퀀스 간격(실험적 최적치)을 이용한 쉘 정렬
 * @param arr 정렬할 배열
 * @param size 배열의 크기
 * @return 비교 횟수
 */
unsigned long long shell_sort_ciura(int arr[], int size);

// --- 메인 함수 ---
int main() {
    srand((unsigned int)time(NULL));

    int* original_data = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int* data_to_sort = (int*)malloc(ARRAY_SIZE * sizeof(int));

    if (original_data == NULL || data_to_sort == NULL) {
        printf("메모리 할당에 실패했습니다!\n");
        return 1;
    }

    unsigned long long total_insertion_comps = 0;
    unsigned long long total_shell_comps = 0;
    unsigned long long total_knuth_comps = 0;
    unsigned long long total_hibbard_comps = 0; // Hibbard
    unsigned long long total_ciura_comps = 0;   // Ciura

    printf("%d개 요소에 대해 %d회 테스트를 시작합니다...\n", ARRAY_SIZE, NUM_TRIALS);
    printf("범위: 0 ~ %d\n", MAX_VAL);

    for (int i = 0; i < NUM_TRIALS; i++) {
        generate_random_data(original_data, ARRAY_SIZE, MAX_VAL);

        // 1. 단순 삽입 정렬
        memcpy(data_to_sort, original_data, ARRAY_SIZE * sizeof(int));
        total_insertion_comps += insertion_sort(data_to_sort, ARRAY_SIZE);

        // 2. 표준 쉘 정렬 (n/2)
        memcpy(data_to_sort, original_data, ARRAY_SIZE * sizeof(int));
        total_shell_comps += shell_sort_standard(data_to_sort, ARRAY_SIZE);

        // 3. Knuth 쉘 정렬
        memcpy(data_to_sort, original_data, ARRAY_SIZE * sizeof(int));
        total_knuth_comps += shell_sort_knuth(data_to_sort, ARRAY_SIZE);

        // 4. Hibbard 쉘 정렬
        memcpy(data_to_sort, original_data, ARRAY_SIZE * sizeof(int));
        total_hibbard_comps += shell_sort_hibbard(data_to_sort, ARRAY_SIZE);

        // 5. Ciura 쉘 정렬
        memcpy(data_to_sort, original_data, ARRAY_SIZE * sizeof(int));
        total_ciura_comps += shell_sort_ciura(data_to_sort, ARRAY_SIZE);

        if ((i + 1) % 10 == 0) {
            printf("진행: %d / %d 회 완료...\n", i + 1, NUM_TRIALS);
        }
    }

    // --- 결과 출력 ---
    printf("\n--- %d회 실행 평균 비교 횟수 ---\n", NUM_TRIALS);
    printf("1. 단순 삽입 정렬       : %.2f 회\n", (double)total_insertion_comps / NUM_TRIALS);
    printf("2. 표준 쉘 정렬 (n/2)   : %.2f 회\n", (double)total_shell_comps / NUM_TRIALS);
    printf("3. Knuth 쉘 정렬        : %.2f 회\n", (double)total_knuth_comps / NUM_TRIALS);
    printf("4. Hibbard 쉘 정렬      : %.2f 회\n", (double)total_hibbard_comps / NUM_TRIALS);
    printf("5. Ciura 쉘 정렬 (최적) : %.2f 회\n", (double)total_ciura_comps / NUM_TRIALS);

    free(original_data);
    free(data_to_sort);

    return 0;
}


// --- 함수 정의 ---

void generate_random_data(int arr[], int size, int max_val) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max_val + 1);
    }
}

// (공통) 갭 정렬을 위한 내부 삽입 정렬 함수
static inline unsigned long long insertion_sort_with_gap(int arr[], int size, int gap) {
    unsigned long long comparisons = 0;
    int i, j, temp;
    for (i = gap; i < size; i++) {
        temp = arr[i];
        j = i - gap;
        while (j >= 0) {
            comparisons++; // 비교 횟수 증가
            if (arr[j] > temp) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            else {
                break;
            }
        }
        arr[j + gap] = temp;
    }
    return comparisons;
}


unsigned long long insertion_sort(int arr[], int size) {
    // gap = 1 인 쉘 정렬과 동일
    return insertion_sort_with_gap(arr, size, 1);
}

unsigned long long shell_sort_standard(int arr[], int size) {
    unsigned long long comparisons = 0;
    int gap;
    for (gap = size / 2; gap > 0; gap /= 2) {
        comparisons += insertion_sort_with_gap(arr, size, gap);
    }
    return comparisons;
}

unsigned long long shell_sort_knuth(int arr[], int size) {
    unsigned long long comparisons = 0;
    int gap = 1;

    // 1. 간격 리스트 생성 (역순으로)
    int gaps[20];
    int num_gaps = 0;
    while (gap < size / 3) {
        gaps[num_gaps++] = gap;
        gap = 3 * gap + 1;
    }

    // 2. 큰 간격부터 적용
    for (int g_idx = num_gaps - 1; g_idx >= 0; g_idx--) {
        comparisons += insertion_sort_with_gap(arr, size, gaps[g_idx]);
    }
    return comparisons;
}

unsigned long long shell_sort_hibbard(int arr[], int size) {
    unsigned long long comparisons = 0;
    int k = 1;
    int gap;

    // 1. 간격 리스트 생성 (역순으로)
    int gaps[20];
    int num_gaps = 0;
    gap = (int)pow(2, k) - 1;
    while (gap < size / 2) { // n/2 보다 작은 간격까지만
        gaps[num_gaps++] = gap;
        k++;
        gap = (int)pow(2, k) - 1;
    }

    // 2. 큰 간격부터 적용
    for (int g_idx = num_gaps - 1; g_idx >= 0; g_idx--) {
        comparisons += insertion_sort_with_gap(arr, size, gaps[g_idx]);
    }
    return comparisons;
}

/**
 * @brief Ciura 시퀀스 간격(실험적 최적치)을 이용한 쉘 정렬
 */
unsigned long long shell_sort_ciura(int arr[], int size) {
    unsigned long long comparisons = 0;

    // Ciura가 실험적으로 찾은 시퀀스 (N=10000 이므로 1750까지 사용)
    // 역순으로 미리 저장
    int gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
    int num_gaps = sizeof(gaps) / sizeof(gaps[0]);

    for (int i = 0; i < num_gaps; i++) {
        // 배열 크기보다 큰 간격은 건너뜀
        if (gaps[i] >= size) continue;

        comparisons += insertion_sort_with_gap(arr, size, gaps[i]);
    }
    return comparisons;
}
