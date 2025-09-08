#include<stdio.h>
#include<stdlib.h>

typedef struct StdType{
    char name[20];
    int id;
    int score;
}StdType;





int main(){
    int i;
    int iArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int iArray2[10] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int *iptr;

    printf("number of iArray element? : ");
    scanf("%d", &i);
    iptr = (int *)malloc(i * sizeof(int)); //malloc 메모리 할당
    for(int j = 0; j < i; j++){
        *(iptr + j) = j + 1;
    }
    StdType students[3] = {{"Hong GilDong", 10, 90}, {"Lee MongRyong", 20, 80}, {"Seong ChoonHyang", 30, 70}};
    StdType* sptr = students; // = &students



    for(int k = 0; k < 3; k++){
        students[k].score += 10;
    }//일반적인 방법

    for(int k = 0; k < 3; k++){
        (*sptr).score += 10;
        //sptr->score += 10;

        sptr++; //포인터 이동
    }//포인터 사용 방법




    printf("memory alloc array : ");
    for(int j = 0; j < i; j++)
        printf("%d ", *(iptr + j));
    printf("\n");

    // i = 10;
    // iptr = &i; //주소값

    // //포인터는 배열이나 함수에 적합
    // printf("i : %d, address of i : 0x%X\n", i, &i);                         //& 주소
    // printf("iptr : 0x%X, value of iptr pointer : %d\n", iptr, *iptr);       //* 주소의 값

    // iptr = iArray;
    // printf("*iptr = %d", *iptr);

    // printf("iArray : ");
    // for(int j = 0; j < 10; j++)
    //     printf("%d ", iArray[j]);
    // printf("\n");


    // // iptr = &iArray[0];
    // // for(int j = 0; j < 10; j++){
    // //     *iptr = *iptr + 1;
    // //     iptr++;    //포인터 위치 변경
    // // }
    
    // // iptr = &iArray2[0];
    // // for(int j = 0; j < 10; j++){
    // //     *iptr = *iptr + 1;
    // //     iptr++;    //포인터 위치 변경
    // // }


    // //add1_array(&iArray[0]);
    // add1_array(iArray); //같다 iArray -> 첫번째 주소, 배열의 이름은 첫번째 요소의 주소

    // add1_array(&iArray2[0]);




    // // for(int j = 0; j < 10; j++){
    // //     iArray[j] = iArray[j] + 1;
    // // }

    // printf("iArray : ");
    // for(int j = 0; j < 10; j++)
    //     printf("%d ", iArray[j]);
    // printf("\n");


    return 0;

}

int add1_array(int* iptr){
    for(int j = 0; j < 10; j++){
        *iptr = *iptr + 1;
        iptr++;
    }
}