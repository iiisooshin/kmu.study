#include<stdio.h>

int main(){

    //변수 선언
    int i;
    float input;
    unsigned int f;


    //실수 입력받기
    printf("실수를 입력하세요 : ");
    scanf("%f",&input);
    f = *(unsigned int *)(&input);
    printf("\n");

    //부호비트 (맨 첫 비트) 출력
    printf("부호 (1비트) : ");
    printf("%d\n", (f >> 31) & 1);
    //부호비트 출력 안됨 0(양수)만 나옴 해결필요 -> (f >> 1) & 0은 1번 비트를 확인하는 것이므로 (f >> 31) & 1 31번 비트 부터 사용해야함

    //지수비트 8비트 (30번째부터 23번째까지) 출력
    printf("지수 (8비트) : ");
    {
    for(i = 30; i>=23; i--){
        printf("%d ", (f >> i) & 1);
       }
    }
    printf("\n");

    //가수비트 23비트 (22번째부터 0번째까지) 출력    
    printf("가수 (23비트) : ");
    {
    for(i = 22; i>=0; i--){
        printf("%d ", (f >> i) & 1);
       }
    }
    printf("\n");

    

    return 0;
}