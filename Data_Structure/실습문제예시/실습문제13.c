#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

// (row, col) 기준 정렬용 비교 함수
int compare_matrix_item(elementType a, elementType b) {
    if (a.row != b.row) return a.row - b.row;
    else return a.col - b.col;
}

// 행렬 항목 입력 함수
listType* inputMatrix() {
    elementType tempArray[100];
    int count = 0;
    int row, col, val;

    printf("행, 열, 값을 입력하세요? (행의 값이 -1이면 종료)\n");
    while (1) {
        if (scanf("%d %d %d", &row, &col, &val) != 3) {
            printf("입력 오류\n");
            exit(1);
        }
        if (row == -1) break;
        if (count >= 100) {
            printf("100개 이상 항은 지원하지 않습니다.\n");
            break;
        }
        tempArray[count++] = (elementType){ row, col, val };
    }

    listType* mat = createList(count);
    for (int i = 0; i < count; i++) {
        ordered_insertItem(mat, tempArray[i]);
    }
    return mat;
}

// 행렬 덧셈 함수
listType* addMatrix(listType* A, listType* B) {
    listType* result = createList(A->last + B->last + 1);
    int i = 0, j = 0;

    while (i <= A->last && j <= B->last) {
        elementType a = readItem(A, i);
        elementType b = readItem(B, j);

        int cmp = compare_matrix_item(a, b);
        if (cmp < 0) {
            ordered_insertItem(result, a);
            i++;
        }
        else if (cmp > 0) {
            ordered_insertItem(result, b);
            j++;
        }
        else {
            int sum = a.val + b.val;
            if (sum != 0)
                ordered_insertItem(result, (elementType) { a.row, a.col, sum });
            i++; j++;
        }
    }

    // 나머지 항들 추가
    while (i <= A->last) ordered_insertItem(result, readItem(A, i++));
    while (j <= B->last) ordered_insertItem(result, readItem(B, j++));

    return result;
}

// 메인 함수
int main() {
    printf("첫째 행렬을 입력하시오? (행의 값이 -1이면 행렬의 입력이 종료됨)\n");
    listType* mat1 = inputMatrix();

    printf("둘째 행렬을 입력하시오? (행의 값이 -1이면 행렬의 입력이 종료됨)\n");
    listType* mat2 = inputMatrix();

    listType* sum = addMatrix(mat1, mat2);

    printf("두 행렬의 합\n");
    printList(sum);

    return 0;
}
