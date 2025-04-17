#include <stdio.h>

// 🔁 순환적(반복문) 피보나치
int fib_iterative(int n) {
    if (n <= 1) return n;
    int prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// 🔁 재귀적 피보나치
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    int method, n;

    while (1) {
        printf("피보나치 수열 방법 선택 (1: 재귀적, 2: 순환적, 0: 종료): ");
        scanf_s("%d", &method);

        switch (method) {
        case 0:
            printf("프로그램이 종료되었습니다.\n");
            return 0;

        case 1:
            printf("정수 N을 입력하세요 (종료하려면 0 입력): ");
            scanf_s("%d", &n);
            printf("F(%d) = %d (재귀적 방법)\n", n, fib_recursive(n));
            break;
        case 2:
            printf("정수 N을 입력하세요 (종료하려면 0 입력): ");
            scanf_s("%d", &n);
            printf("F(%d) = %d (순환적 방법)\n", n, fib_iterative(n));
            break;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}
