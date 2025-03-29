//vs code에서 작성

//n개의 정수 입력받아 오름차순 정렬

/*
FUNCTION swap(a, b)
       if a < b
       temp = a
       a = b
       b = temp

int main()
    scanf n;
    for i -> n do
        scanf input[i]

    for i -> n do
        for j -> n do

    printf input[0] -> input[n]
*/




#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;

    // 정수의 개수 입력
    printf("정수의 개수를 입력하세요: ");
    scanf("%d", &n);

    // 입력값 유효성 검사
    if (n <= 0) {
        printf("잘못된 입력입니다. 양수를 입력하세요.\n");
        return 1;
    }

    // 동적 배열 할당
    int* input = (int*)malloc(n * sizeof(int));
    if (input == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 정수 입력
    printf("%d개의 정수를 입력하세요:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }

    // 버블 정렬 (오름차순)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (input[j] > input[j + 1]) { // 인접한 요소 비교
                swap(&input[j], &input[j + 1]);
            }
        }
    }

    // 결과 출력
    printf("오름차순으로 정렬된 정수들:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    // 동적 메모리 해제
    free(input);

    return 0;
}