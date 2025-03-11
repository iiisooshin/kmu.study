#include <stdio.h>


int main(){
    int a;

    printf("정수를 입력하세요 : ");
    scanf("%d", &a);
    printf("입력된 정수의 32비트 표현 : ");

    for(int i = 31; i>=0; i--){
        printf("%d", (a>>i) & 1);
    }
    return 0;
}