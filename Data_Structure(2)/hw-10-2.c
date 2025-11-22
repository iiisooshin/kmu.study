#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 발생하는 scanf, fopen 등의 보안 경고를 무시합니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 최대 학생 수 (파일의 크기에 따라 조정 가능)
#define MAX_STUDENTS 100000 
// CSV 파일의 한 줄 최대 길이
#define MAX_LINE 256 

// 전역 변수로 정렬 비교 횟수를 저장
long long sort_comparisons = 0; 

// 학생 정보를 저장할 구조체
typedef struct {
    int ID;
    char NAME[50];
    char GENDER;
    int KOREAN_GRADE;
    int ENGLISH_GRADE;
    int MATH_GRADE;
    // 새로 추가된 필드: 세 성적의 곱
    long long PRODUCT_SCORE; 
} Student;

// 학생 데이터 배열
Student students[MAX_STUDENTS];
int student_count = 0;

// =================================================================
// 1. 파일 로드 및 데이터 처리 함수
// =================================================================

/**
 * @brief CSV 파일을 읽고 데이터를 구조체 배열에 저장하며, PRODUCT_SCORE를 계산합니다.
 * @param filename 불러올 CSV 파일 이름
 * @return 성공 시 0, 실패 시 -1
 */
int load_data(const char *filename) {
    // _CRT_SECURE_NO_WARNINGS를 사용했으므로 fopen을 사용할 수 있습니다.
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return -1;
    }

    char line[MAX_LINE];
    // 첫 줄(헤더) 건너뛰기
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return -1; // 파일이 비어있음
    }

    // 파일에서 학생 정보 읽기
    while (fgets(line, sizeof(line), file) != NULL) {
        if (student_count >= MAX_STUDENTS) {
            printf("경고: 최대 학생 수(%d)를 초과했습니다. 더 이상 데이터를 로드할 수 없습니다.\n", MAX_STUDENTS);
            break;
        }

        Student *s = &students[student_count];
        
        // CSV 파싱
        if (sscanf(line, "%d,%49[^,],%c,%d,%d,%d", 
                   &s->ID, 
                   s->NAME, 
                   &s->GENDER, 
                   &s->KOREAN_GRADE, 
                   &s->ENGLISH_GRADE, 
                   &s->MATH_GRADE) == 6) {
            
            // PRODUCT_SCORE 계산 (long long 사용으로 오버플로우 방지)
            s->PRODUCT_SCORE = (long long)s->KOREAN_GRADE * s->ENGLISH_GRADE * s->MATH_GRADE;
            student_count++;
        } else {
            fprintf(stderr, "경고: 데이터 파싱 오류가 발생했습니다: %s", line);
        }
    }

    fclose(file);
    return 0;
}

// =================================================================
// 2. 탐색 함수
// =================================================================

/**
 * @brief PRODUCT_SCORE를 기준으로 순차 탐색을 수행합니다.
 * @param target_value 찾고자 하는 PRODUCT_SCORE 값 (임의의 수)
 * @param comparisons 비교 횟수를 저장할 포인터
 * @return 학생의 인덱스 (찾지 못하면 -1)
 */
int sequential_search(long long target_value, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < student_count; i++) {
        (*comparisons)++; // 비교 횟수 증가

        if (students[i].PRODUCT_SCORE == target_value) {
            return i; // 찾음
        }
    }
    return -1; // 찾지 못함
}

/**
 * @brief PRODUCT_SCORE를 기준으로 이진 탐색을 수행합니다. (데이터는 반드시 정렬되어 있어야 함)
 * @param target_value 찾고자 하는 PRODUCT_SCORE 값 (임의의 수)
 * @param comparisons 비교 횟수를 저장할 포인터
 * @return 학생의 인덱스 (찾지 못하면 -1)
 */
int binary_search(long long target_value, int *comparisons) {
    *comparisons = 0;
    int low = 0;
    int high = student_count - 1;

    // 

    while (low <= high) {
        (*comparisons)++; // 비교 횟수 증가 
        
        int mid = low + (high - low) / 2;
        
        if (students[mid].PRODUCT_SCORE == target_value) {
            return mid; // 찾음
        } else if (students[mid].PRODUCT_SCORE < target_value) {
            low = mid + 1; 
        } else {
            high = mid - 1; 
        }
    }
    return -1; // 찾지 못함
}

// =================================================================
// 3. 정렬 함수 (퀵 정렬 - 최적의 정렬 방법)
// =================================================================

/**
 * @brief 퀵 정렬을 위한 비교 함수 (PRODUCT_SCORE 기준)
 * 이 함수가 호출될 때마다 정렬 비교 횟수를 증가시킵니다.
 * @param a Student 구조체 포인터
 * @param b Student 구조체 포인터
 * @return a > b 이면 양수, a < b 이면 음수, 같으면 0
 */
int compare_product_score(const void *a, const void *b) {
    // 전역 변수를 사용하여 비교 횟수 기록
    sort_comparisons++; 

    long long score_a = ((Student *)a)->PRODUCT_SCORE;
    long long score_b = ((Student *)b)->PRODUCT_SCORE;

    if (score_a < score_b) return -1;
    if (score_a > score_b) return 1;
    return 0;
}

/**
 * @brief 퀵 정렬 함수를 호출하여 데이터를 정렬합니다.
 */
void sort_students_by_product_score() {
    // C 표준 라이브러리의 qsort 함수를 사용하여 퀵 정렬 수행
    // compare_product_score 함수 내에서 비교 횟수가 기록됨
    // 
    qsort(students, student_count, sizeof(Student), compare_product_score);
}

// =================================================================
// 4. 메인 함수
// =================================================================

int main() {
    // 1. 데이터 로드
    printf("1. CSV 파일에서 학생 데이터 로드 및 PRODUCT_SCORE 계산...\n");
    if (load_data("dataset_id_ascending.csv") != 0) {
        return 1;
    }
    printf("-> 총 %d명의 학생 데이터 로드 완료.\n", student_count);

    // 2. 탐색을 위한 임의의 값 생성
    srand(time(NULL));
    long long target_value = rand() % 1000001;
    
    printf("\n2. 탐색을 위한 임의의 값: %lld (0 ~ 1,000,000 범위)\n", target_value);

    // =================================================================
    // 3. 순차 탐색 수행
    // =================================================================
    int seq_comparisons = 0;
    int seq_index = sequential_search(target_value, &seq_comparisons);

    printf("\n3. 순차 탐색 (Sequential Search)\n");
    printf("-> 비교 횟수: %d회\n", seq_comparisons);
    if (seq_index != -1) {
        printf("-> 탐색 성공! (ID: %d, PRODUCT_SCORE: %lld)\n", 
               students[seq_index].ID, students[seq_index].PRODUCT_SCORE);
    } else {
        printf("-> 탐색 실패. (데이터가 존재하지 않음)\n");
    }

    // =================================================================
    // 4. 정렬 수행 (이진 탐색을 위한 준비)
    // =================================================================
    printf("\n4. 정렬 수행 (Quick Sort - PRODUCT_SCORE 기준)\n");
    clock_t start_sort = clock();
    sort_students_by_product_score();
    clock_t end_sort = clock();
    double sort_time = (double)(end_sort - start_sort) / CLOCKS_PER_SEC;
    printf("-> 정렬 완료. (소요 시간: %.4f초)\n", sort_time);
    printf("-> 정렬에 사용된 총 비교 횟수: %lld회\n", sort_comparisons);


    // =================================================================
    // 5. 이진 탐색 수행
    // =================================================================
    int bin_comparisons = 0;
    int bin_index = binary_search(target_value, &bin_comparisons);

    printf("\n5. 이진 탐색 (Binary Search)\n");
    printf("-> 이진 탐색 중 비교 횟수: %d회\n", bin_comparisons);
    
    // 이진 탐색의 전체 비용은 정렬 비용 + 탐색 비용
    long long total_bin_cost = sort_comparisons + bin_comparisons;
    printf("-> 이진 탐색을 위한 총 비용 (정렬 + 탐색 비교): %lld회\n", total_bin_cost);

    if (bin_index != -1) {
        printf("-> 탐색 성공! (ID: %d, PRODUCT_SCORE: %lld)\n", 
               students[bin_index].ID, students[bin_index].PRODUCT_SCORE);
    } else {
        printf("-> 탐색 실패. (데이터가 존재하지 않음)\n");
    }

    printf("\n=================================================\n");
    printf("최종 비교 요약:\n");
    printf("1. 순차 탐색 비교 횟수: %d회\n", seq_comparisons);
    printf("2. 이진 탐색 총 비교 횟수 (정렬 + 탐색): %lld회\n", total_bin_cost);
    printf("=================================================\n");

    return 0;
}
