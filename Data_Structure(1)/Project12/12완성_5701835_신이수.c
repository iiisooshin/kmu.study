//visual studio 2022 에서 작성

#include<stdio.h>
#include<stdlib.h>


//재귀 (ex. 하노이의탑, 정렬 알고리즘) 
//피보나치는 재귀(recursion)방식으로 좋지않음

//재귀함수 사용

int plus_count;


//피보나치 recursion
//m = 15일때 덧셈 986번 실행
//이미 구한 값을 재귀하여 똑같이 새로 구함
//쓸데없는 일을 많이 반복 -> 오래걸린다
//호출 5 4 3 2 1 -> 다시 1 2 3 4 5 줄어듬 -> 시간 증가(스택)
//시간을 줄이는데는 재귀보단 반복문
int fibo_rec(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else {
        plus_count++;
        return(fibo_rec(n - 1) + fibo_rec(n - 2));
    }
}

//피보나치 itr
//m = 15일때 덧셈 14번 실행
int fibo_itr(int n) {
    int f_n_2 = 0;
    int f_n_1 = 1;
    int f_n;

    for (int i = 2; i <= n; i++) {
        plus_count++;
        f_n = f_n_1 + f_n_2;
        f_n_2 = f_n_1;
        f_n_1 = f_n;
    }
    if (n == 0)
        return f_n_2;
    else if (n == 1)
        return f_n_1;
    else return f_n;
}



int main() {

    int input;
    int num;
    int repeat = 1;

    while (repeat) {

        printf("피보나치 수열 방법 선택 (1 : 재귀적, 2 : 순환적, 0 : 종료) : ");
        scanf_s("%d", &input);

        switch (input) {
        case 0:
            printf("프로그램이 종료되었습니다.\n");
            repeat = 0;
            break;
        case 1:
            printf("정수 n을 입력하세요 (종료하려면 0 입력) : ");
            scanf_s("%d", &num);
            if (num == 0) {
                printf("프로그램이 종료되었습니다.\n");
                break;
            }
            else if (num < 0) {
                printf("잘못된 입력입니다.");
            }
            else if (num > 0) {
                printf("f(%d) = %d (재귀적 방법)\n", num, fibo_rec(num));
                break;
            }

        case 2:
            printf("정수 n을 입력하세요 (종료하려면 0 입력) : ");
            scanf_s("%d", &num);
            if (num == 0) {
                printf("프로그램이 종료되었습니다.\n");
                break;
            }
            else if (num < 0) {
                printf("잘못된 입력입니다.");
            }
            else if (num > 0) {
                printf("f(%d) = %d (순환적 방법)\n", num, fibo_itr(num));
                break;
            }
        default:
            printf("잘못된 입력입니다.\n");
            break;


        }
    }

    

    

    return 0;

}
