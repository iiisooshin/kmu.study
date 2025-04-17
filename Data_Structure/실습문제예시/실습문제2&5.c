#include <stdio.h>

void printBits(unsigned int value, int from, int to) {
    for (int i = from; i >= to; i--) {
        printf("%d", (value >> i) & 1);
        if ((i > to) && ((i - to) % 4 == 0)) printf(" "); // 보기 좋게 4비트 간격
    }
    printf("\n");
}

int main() {
    float input;
    unsigned int* ptr;

    printf("실수를 입력하세요: ");
    scanf_s("%f", &input);

    ptr = (unsigned int*)&input;  // float의 비트를 정수처럼 해석

    printf("부호 (1비트) : ");
    printBits(*ptr, 31, 31);

    printf("지수 (8비트) : ");
    printBits(*ptr, 30, 23);

    printf("가수 (23비트) : ");
    printBits(*ptr, 22, 0);

    return 0;
}
