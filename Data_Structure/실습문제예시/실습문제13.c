#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

// (row, col) ���� ���Ŀ� �� �Լ�
int compare_matrix_item(elementType a, elementType b) {
    if (a.row != b.row) return a.row - b.row;
    else return a.col - b.col;
}

// ��� �׸� �Է� �Լ�
listType* inputMatrix() {
    elementType tempArray[100];
    int count = 0;
    int row, col, val;

    printf("��, ��, ���� �Է��ϼ���? (���� ���� -1�̸� ����)\n");
    while (1) {
        if (scanf("%d %d %d", &row, &col, &val) != 3) {
            printf("�Է� ����\n");
            exit(1);
        }
        if (row == -1) break;
        if (count >= 100) {
            printf("100�� �̻� ���� �������� �ʽ��ϴ�.\n");
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

// ��� ���� �Լ�
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

    // ������ �׵� �߰�
    while (i <= A->last) ordered_insertItem(result, readItem(A, i++));
    while (j <= B->last) ordered_insertItem(result, readItem(B, j++));

    return result;
}

// ���� �Լ�
int main() {
    printf("ù° ����� �Է��Ͻÿ�? (���� ���� -1�̸� ����� �Է��� �����)\n");
    listType* mat1 = inputMatrix();

    printf("��° ����� �Է��Ͻÿ�? (���� ���� -1�̸� ����� �Է��� �����)\n");
    listType* mat2 = inputMatrix();

    listType* sum = addMatrix(mat1, mat2);

    printf("�� ����� ��\n");
    printList(sum);

    return 0;
}
