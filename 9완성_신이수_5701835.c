//vs code에서 작성

//n개의 정수 입력받아 오름차순 정렬

/*
FUNCTION swap(a, b)
       if a < b
       temp = a
       a = b
       b = temp

int main()
    scanf n;
    for i -> n do
        scanf input[i]

    for i -> n do
        for j -> n do

    printf input[0] -> input[n]
*/




#include<stdio.h>

int swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}

int main(){

    int n = 0;
    int input[n];
    int temp;

    printf("정수의 개수를 입력하세요 : ");
    scanf("%d", &n);

    printf("%d개의 정수를 입력하세요 : \n", n);
    for(int i = 0; i < n; i++){
        scanf(" %d", &input[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            if(input[i] < input[j]){
                swap(&input[i], &input[j]);
            }
        }
    }
    
    
    printf("오름차순으로 정렬된 정수들 : \n");
    for(int i = 0; i < n; i++) { printf("%d ", input[i]); }
    




    return 0;
}