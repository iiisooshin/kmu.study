#include <stdio.h>


int main(){
    int a;                          // 정수값을 입력 받을 변수 선언

    printf("정수를 입력하세요 : ");
    scanf("%d", &a);                // 32비트 표현으로 변경 할 정수 입력
    printf("입력된 정수의 32비트 표현 : ");

    for(int i = 31; i>=0; i--){     //for 문을 통해 31(32)번째 비트부터 0(1)번째 비트까지 차례로 출력
        printf("%d", (a>>i) & 1);
    }
    return 0;
}