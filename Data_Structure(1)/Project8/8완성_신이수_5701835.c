//vs code에서 작성

/*
2x2배열 2종류 입력 후 덧셈 출력

int main()
    int iArray[2][2];
    int jArray[2][2];
    int result[2][2];

    scanf iArray[][];
    scanf jArray[][];

    for i = 0 -> 1 do
        for j = 0 -> 1 do
            result[i][j] = iArray[i][j] + jArray[i][j];

    printf result;

*/

#include<stdio.h>



int main(){

    int iArray[2][2];
    int jArray[2][2];
    int result[2][2];
    int k = 0;

    printf("첫 번째 2x2 행렬 입력 : \n");
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            scanf("%d", &iArray[i][j]);
        }
    }


    printf("두 번째 2x2 행렬 입력 : \n");
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            scanf("%d", &jArray[i][j]);
        }
    }

    
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            result[i][j] = iArray[i][j] + jArray[i][j];
        }
    }

    printf("행렬 덧셈 결과 : \n");
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            printf("%d ", result[i][j]);
            k++;
            if (k % 2 == 0) printf("\n");
        }
    }



    return 0;
}