#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char expr[256];
} Expr;

void initExpr(Expr* e, const char* input) {
    strncpy(e->expr, input, sizeof(e->expr) - 1);
    e->expr[sizeof(e->expr) - 1] = '\0';
}

int evaluateExpr(const Expr* e) {
    int i = 0, num = 0, result = 0;
    char op = 0;

    while (e->expr[i] != '\0') {
        if (isdigit(e->expr[i])) {
            num = 0;
            while (isdigit(e->expr[i])) {
                num = num * 10 + (e->expr[i] - '0');
                i++;
            }

            if (op == 0) {
                result = num;  // 첫 번째 숫자
            } else {
                if (op == '+') result += num;
                else if (op == '-') result -= num;
                else if (op == '*') result *= num;
                else if (op == '/') result /= num;
            }
        }
        else if (strchr("+-*/", e->expr[i])) {
            op = e->expr[i++];
        }
        else {
            printf("잘못된 입력 문자: %c\n", e->expr[i]);
            exit(1);
        }
    }

    return result;
}

int main() {
    Expr expr;
    char input[256];

    printf("수식을 입력하세요 (예: 5+3*7): ");
    scanf("%s", input);

    initExpr(&expr, input);

    int result = evaluateExpr(&expr);
    printf("계산 결과: %d\n", result);

    return 0;
}
