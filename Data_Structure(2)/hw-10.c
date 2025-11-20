#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_STUDENTS 40000 

typedef struct {
    int id;
    char name[50];
    char gender;
    int korean;
    int english;
    int math;
    long long mul_of_score;
} Student;

// qsort 비교 함수
int compare(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    if (s1->mul_of_score > s2->mul_of_score) return 1;
    if (s1->mul_of_score < s2->mul_of_score) return -1;
    return 0;
}

// 순차 탐색
int sequentialSearch(Student arr[], int n, long long target) {
    int comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i].mul_of_score == target) {
            return comparisons;
        }
    }
    return comparisons;
}

// 이진 탐색
int binarySearch(Student arr[], int n, long long target) {
    int comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;

        if (arr[mid].mul_of_score == target) {
            return comparisons;
        }
        else if (arr[mid].mul_of_score < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return comparisons;
}

// 메모리 부족 방지를 위해 전역/static 선언
static Student students[MAX_STUDENTS];        // 순차 탐색용 (정렬 X)
static Student sorted_students[MAX_STUDENTS]; // 이진 탐색용 (정렬 O)

int main() {
    int count = 0;
    char line[MAX_LINE_LENGTH];

    // 1. 파일 읽기
    FILE* fp = fopen("dataset_id_ascending.csv", "r");
    if (fp == NULL) {
        printf("오류: 파일을 찾을 수 없습니다.\n");
        return 1;
    }

    fgets(line, MAX_LINE_LENGTH, fp); // 헤더 스킵

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && count < MAX_STUDENTS) {
        char* token;

        token = strtok(line, ","); if (token == NULL) continue;
        students[count].id = atoi(token);

        token = strtok(NULL, ","); strcpy(students[count].name, token);
        token = strtok(NULL, ","); students[count].gender = token[0];
        token = strtok(NULL, ","); students[count].korean = atoi(token);
        token = strtok(NULL, ","); students[count].english = atoi(token);
        token = strtok(NULL, ","); students[count].math = atoi(token);

        students[count].mul_of_score = (long long)students[count].korean * students[count].english * students[count].math;

        count++;
    }
    fclose(fp);

    // 2. 데이터 복사 및 정렬
    // 순차 탐색용은 그대로 두고, 이진 탐색용 배열을 따로 만들어 정렬합니다.
    memcpy(sorted_students, students, sizeof(Student) * count);
    qsort(sorted_students, count, sizeof(Student), compare);

    printf("==================================================\n");
    printf(" [자료구조 탐색 성능 비교 실험]\n");
    printf(" 데이터 개수: %d개\n", count);
    printf("==================================================\n\n");

    // 3. 실험 횟수 입력
    int num_experiments;
    printf("실험을 몇 번 반복하시겠습니까? : ");
    scanf("%d", &num_experiments);

    if (num_experiments <= 0) {
        printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
        return 0;
    }

    printf("\n>>> 실험 시작 (%d회 반복)...\n", num_experiments);

    srand((unsigned int)time(NULL));

    long long total_comp_seq = 0;
    long long total_comp_bin = 0;
    int found_count = 0;

    for (int i = 0; i < num_experiments; i++) {
        // 0 ~ 1,000,000 사이의 난수 생성
        long long target = rand() % 1000001;

        // 순차 탐색 (정렬 안 된 students 배열 사용)
        total_comp_seq += sequentialSearch(students, count, target);

        // 이진 탐색 (정렬 된 sorted_students 배열 사용)
        int comp = binarySearch(sorted_students, count, target);
        total_comp_bin += comp;

        // (참고) 실제로 찾았는지 확인하기 위해 잠시 검사
        // 이진 탐색 결과로 찾았는지 여부 판단 (비교 횟수가 logN 이하이면 찾은 것일 확률 높지만 정확히는 리턴값 수정 필요하나 실험상 비교횟수만 누적)
        // 정확한 통계를 위해 여기서는 비교 횟수 누적에 집중합니다.
    }

    // 4. 결과 출력
    printf("\n================== [실험 결과] ==================\n");
    printf(" 총 실험 횟수: %d회\n", num_experiments);
    printf("-------------------------------------------------\n");

    double avg_seq = (double)total_comp_seq / num_experiments;
    double avg_bin = (double)total_comp_bin / num_experiments;

    printf(" 1. 순차 탐색 (Sequential Search) - 정렬 X\n");
    printf("    - 평균 비교 횟수: %.2f회\n\n", avg_seq);

    printf(" 2. 이진 탐색 (Binary Search)     - 정렬 O\n");
    printf("    - 평균 비교 횟수: %.2f회\n", avg_bin);

    printf("-------------------------------------------------\n");
    printf(" 결론: 이진 탐색이 순차 탐색보다 평균 약 %.0f배 효율적입니다.\n", avg_seq / avg_bin);
    printf("=================================================\n");

    return 0;
}
