


#include <stdio.h>

// 사칙연산 함수 선언 (ADT 인터페이스)
void add(int a, int b);     // 두 정수의 합을 출력
void sub(int a, int b);     // 두 정수의 차를 출력
void mul(int a, int b);     // 두 정수의 곱을 출력
void div(float a, float b); // 두 수의 나눗셈 결과를 출력 (0으로 나누기 예외 처리)

// 계산기 관련 함수 선언
void init(int* numC, int* opC);                   // 계산기 상태 초기화
void parse(char* str, float num[], char op[], int* numC, int* opC); // 수식을 숫자와 연산자로 분리
float calculate(float num[], char op[], int* numC, int* opC);       // 연산자 우선순위를 고려한 계산

int main() {
    // 계산기 구조체 정의 (수식과 데이터를 저장)
    typedef struct {
        char str[100];    // 입력된 수식을 저장하는 배열
        float num[50];    // 파싱된 숫자를 저장하는 배열
        char op[50];      // 파싱된 연산자를 저장하는 배열
        int numC, opC;    // 숫자와 연산자의 개수를 추적
    } Calculator;

    // 두 정수 입력받아 개별 사칙연산 수행
    int a, b;
    printf("첫 번째 정수: ");
    scanf_s("%d", &a);    // 첫 번째 정수 입력
    printf("두 번째 정수: ");
    scanf_s("%d", &b);    // 두 번째 정수 입력

    // 개별 사칙연산 결과 출력
    printf("덧셈: "); add(a, b);
    printf("뺄셈: "); sub(a, b);
    printf("곱셈: "); mul(a, b);
    printf("나눗셈: "); div((float)a, (float)b);

    // 계산기 객체 생성 및 초기화
    Calculator calc;
    init(&calc.numC, &calc.opC);    // 숫자와 연산자 카운터를 0으로 초기화

    // 수식 입력
    printf("계산할 수식을 입력하세요 (예: 3 + 5 * 2 / 4): ");
    fgets(calc.str, sizeof(calc.str), stdin);    // 수식을 문자열로 입력받음
    for(int i = 0; calc.str[i]; i++) {           // 개행 문자 제거
        if(calc.str[i] == '\n') calc.str[i] = '\0';
    }

    // 수식 처리 및 계산
    parse(calc.str, calc.num, calc.op, &calc.numC, &calc.opC);    // 수식을 숫자와 연산자로 파싱
    float result = calculate(calc.num, calc.op, &calc.numC, &calc.opC); // 계산 수행
    printf("결과: %.2f\n", result);    // 최종 결과 출력

    return 0;    // 프로그램 종료
}

// 사칙연산 함수 정의
void add(int a, int b) {    // 덧셈: a + b 출력
    printf("%d\n", a + b);
}

void sub(int a, int b) {    // 뺄셈: a - b 출력
    printf("%d\n", a - b);
}

void mul(int a, int b) {    // 곱셈: a * b 출력
    printf("%d\n", a * b);
}

void div(float a, float b) {    // 나눗셈: a / b 출력, 0으로 나누기 예외 처리
    if(b != 0) printf("%.2f\n", a / b);
    else printf("0으로 나눌 수 없습니다.\n");
}

// 계산기 관련 함수 정의
void init(int* numC, int* opC) {    // 계산기 상태 초기화: 숫자와 연산자 개수를 0으로 설정
    *numC = *opC = 0;
}

void parse(char* str, float num[], char op[], int* numC, int* opC) {    // 수식 파싱 함수
    float n = 0;    // 현재 숫자를 임시 저장
    for(int i = 0; str[i]; i++) {    // 문자열을 순회하며 파싱
        if(str[i] >= '0' && str[i] <= '9') {    // 숫자면 현재 숫자에 추가
            n = n * 10 + (str[i] - '0');
        } else if(str[i] == '+' || str[i] == '-' ||    // 연산자나 공백이면
                 str[i] == '*' || str[i] == '/' || str[i] == ' ') {
            if(n || (i > 0 && str[i-1] >= '0')) {    // 이전에 숫자가 있으면 배열에 저장
                num[(*numC)++] = n;
                n = 0;
            }
            if(str[i] != ' ') op[(*opC)++] = str[i];    // 공백이 아니면 연산자 저장
        }
    }
    if(n || str[0] >= '0') num[(*numC)++] = n;    // 마지막 숫자 저장
}

float calculate(float num[], char op[], int* numC, int* opC) {    // 연산자 우선순위 계산 함수
    // 높은 우선순위 연산 (*, /) 먼저 처리
    for(int i = 0; i < *opC; i++) {
        if(op[i] == '*' || op[i] == '/') {    // 곱셈 또는 나눗셈 발견
            float a = num[i], b = num[i + 1];    // 연산 대상 숫자
            if(op[i] == '*') {    // 곱셈 수행
                num[i] = a * b;
            } else if(b != 0) {    // 나눗셈 수행 (0으로 나누기 체크)
                num[i] = a / b;
            } else {
                printf("0으로 나눌 수 없습니다.\n");
                return 0;    // 오류 시 0 반환
            }
            // 배열 조정: 계산된 숫자와 연산자를 제거
            for(int j = i + 1; j < *numC - 1; j++) num[j] = num[j + 1];
            for(int j = i; j < *opC - 1; j++) op[j] = op[j + 1];
            (*numC)--; (*opC)--; i--;    // 카운터 감소 및 인덱스 조정
        }
    }
    // 낮은 우선순위 연산 (+, -) 처리
    float result = num[0];    // 초기 결과값 설정
    for(int i = 0; i < *opC; i++) {
        if(op[i] == '+') result += num[i + 1];    // 덧셈
        else if(op[i] == '-') result -= num[i + 1];    // 뺄셈
    }
    return result;    // 최종 결과 반환
}