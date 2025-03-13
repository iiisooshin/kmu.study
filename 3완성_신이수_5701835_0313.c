#include<stdio.h>

int main(){
    char str[50];                   // 입력 받을 문자열 선언
    int gap = 'a' - 'A';            // ASCII 순서를 통해 대소문자를 변환하기 위해 소문자a와 대문자A 번호의 값의 차이를 구한다

    printf("문자열을 입력하세요 : ");    // 문자열 입력 받기
    scanf("%[^\n]", str);           // 띄어쓰기 차례가 오면 코드가 스킵되는 것을 방지하기 위해 %s 대신에 %[^\n]을 사용
                                    // 기본적으로 C언어에서 빈칸은 \0으로 처리 but \n이 나올때까지 계속 입력받기

    int count = 0;                  // 문자열 길이 변수 선언 기본 0으로 시작해 문자 한글자씩 받을때 1씩 증가
    while (str[count] != '\0'){     // 문자열 길이 측정
        count ++;
    }


    // for문을 활용하여 대문자는 소문자로, 소문자는 대문자로, 나머지 글자(특수문자 등)는 그대로 출력 하도록 설정
    for(int i = 0; str[i]; i++){
        if((str[i] >= 'a') && (str[i] <= 'z')){
            str[i] = str[i] - gap;
        }else if((str[i] >= 'A') && (str[i] <= 'Z')){
            str[i] = str[i] + gap;
        }else(str[i] = str[i]);

    }


    // 계산된 문자열 길이와 변환된 문자열을 출력
    printf("문자열의 길이 : %d\n", count);
    printf("변환된 문자열 : %s", str);



    return 0;
}