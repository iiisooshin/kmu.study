#include<stdio.h>

//입력값 정수 n 이하의 모든 소수 출력

//정수 n을 입력받는다.
//for문을 이용하여 n부터 1까지 나눠지는 수가 있는지 확인한다.
//나눠지면 출력하지 않고, 나눠지지 않으면 출력한다.

//int n 선언
//for문에 활용할 i, j 선언
//정수 n을 입력받는다.
//n 이하의 소수 출력
//for문 i를 활용하여 n부터 1까지 반복
//for문 if(n % j == 0) 이면 넘어가고, if(n % j != 0) 이면 출력한다.
//1까지 반복
//종료

/*
int n, i, j
scanf n
for i
    for j
        if n % j == 0
            continue
        else if n % j != 0
            print n
*/

int main(){

    int n, i, j;
    int count = 1;

    printf("정수 n을 입력하세요 : ");
    scanf("%d", &n);
    printf("%d 이하의 소수 ", n);

    for(i = 2; i <= n; i++){
        for(j = 2; j < i; j++){
            if(i % j == 0){
                break;
            }else{
                printf("%d ", i);
            }
        }
    }
    return 0;
}