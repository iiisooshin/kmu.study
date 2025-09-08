#include <stdio.h>
#include <stdint.h>

void printBits(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
    int input;

    printf("정수를 입력하세요: ");
    scanf_s("%d", &input);

    // 부호가 있는 int를 부호 없는 32비트로 해석
    uint32_t bitPattern = (uint32_t)input;

    printf("입력된 정수의 32비트 표현: ");
    printBits(bitPattern);

    return 0;
}
