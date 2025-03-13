#include<stdio.h>

int main(){
    char str[50];
    int gap = 'a' - 'A';

    printf("문자열을 입력하세요 : ");
    scanf("%[^\n]", str);

    int count = 0;
    while (str[count] != '\0'){
        count ++;
    }



    for(int i = 0; str[i]; i++){
        if((str[i] >= 'a') && (str[i] <= 'z')){
            str[i] = str[i] - gap;
        }else if((str[i] >= 'A') && (str[i] <= 'Z')){
            str[i] = str[i] + gap;
        }else(str[i] = str[i]);

    }


    printf("문자열의 길이 : %d\n", count);
    printf("변환된 문자열 : %s", str);





    return 0;
}