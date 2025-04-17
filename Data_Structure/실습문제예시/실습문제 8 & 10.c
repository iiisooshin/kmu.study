#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** data;
    int rows;
    int cols;
} Matrix;

void allocateMatrix(Matrix* m) {
    m->data = (int**)malloc(m->rows * sizeof(int*));
    for (int i = 0; i < m->rows; i++) {
        m->data[i] = (int*)malloc(m->cols * sizeof(int));
    }
}

void freeMatrix(Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
}

void inputMatrix(Matrix* m, const char* name) {
    printf("%s 행렬을 입력하세요:\n", name);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%s[%d][%d] = ", name, i, j);
            scanf("%d", &m->data[i][j]);
        }
    }
}

Matrix addMatrix(const Matrix* a, const Matrix* b) {
    Matrix result;
    result.rows = a->rows;
    result.cols = a->cols;
    allocateMatrix(&result);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

void printMatrix(const Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%5d", m->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix A, B, C;

    printf("행과 열의 개수를 입력하세요 (예: 2 3): ");
    scanf("%d %d", &A.rows, &A.cols);

    B.rows = A.rows;
    B.cols = A.cols;

    allocateMatrix(&A);
    allocateMatrix(&B);

    inputMatrix(&A, "A");
    inputMatrix(&B, "B");

    C = addMatrix(&A, &B);

    printf("\n두 행렬의 합:\n");
    printMatrix(&C);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);

    return 0;
}
