//2x2

#include<stdio.h>
#include<stdlib.h>



int main(){

    int i, j, k;

    //동적 메모리 할당(행)
    int **iArray = (int **)malloc(sizeof(int *) * 2);
    int **jArray = (int **)malloc(sizeof(int *) * 2);
    int **result = (int **)malloc(sizeof(int *) * 2);
    
    //메모리 할당(열)
    for (i = 0; i < 2; i++) {
        iArray[i] = (int *)malloc(sizeof(int) * 2);
        jArray[i] = (int *)malloc(sizeof(int) * 2);
        result[i] = (int *)malloc(sizeof(int) * 2);
    }

    if (iArray == NULL || jArray == NULL || result == NULL) { // 메모리 할당 확인
        printf("메모리 할당 실패\n");
        return 1;
    }

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

    k = 0;
    printf("행렬 덧셈 결과 : \n");
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            printf("%d ", result[i][j]);
            k++;
            if (k % 2 == 0) printf("\n");
        }
    }

    // 메모리 해제
    for (i = 0; i < 2; i++) {
        free(iArray[i]);
        free(jArray[i]);
        free(result[i]);
    }
    free(iArray);
    free(jArray);
    free(result);

    return 0;
}