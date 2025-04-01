#include<stdio.h>
#include<stdlib.h>


//재귀 (ex. 하노이의탑, 정렬 알고리즘) 
//피보나치는 재귀(recursion)방식으로 좋지않음

//재귀함수 사용

int plus_count;

int fact_rec(int n){
    if(n == 1) return 1;
    else{
        return (n * fact_rec(n - 1));
    }
}

//단순 반복문 사용
int fact_itr(int n){
    int f = 1;

    for(int i = 1; i <= n; i++){
        f = f * i;
    }
    return f;
}

//피보나치 recursion
//m = 15일때 덧셈 986번 실행
//이미 구한 값을 재귀하여 똑같이 새로 구함
//쓸데없는 일을 많이 반복 -> 오래걸린다
//호출 5 4 3 2 1 -> 다시 1 2 3 4 5 줄어듬 -> 시간 증가(스택)
//시간을 줄이는데는 재귀보단 반복문
int fibo_rec(int n){
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else {
        plus_count++;
        return(fibo_rec(n - 1) + fibo_rec(n - 2));
    }
}

//피보나치 itr
//m = 15일때 덧셈 14번 실행
int fibo_itr(int n){
    int f_n_2 = 0;
    int f_n_1 = 1;
    int f_n;

    for(int i = 2; i <= n; i++){
        plus_count++;
        f_n = f_n_1 + f_n_2;
        f_n_2 = f_n_1;
        f_n_1 = f_n;
    }
    if(n == 0)
        return f_n_2;
    else if(n == 1)
        return f_n_1;
    else return f_n;
}



void main(){

    int m;

    printf("m 값을 입력하세요. : ");
    scanf("%d", &m); //m의 위치에 넣어라
    getchar();

    printf("%d! = %d by recursion\n", m, fact_rec(m));
    printf("%d! = %d by interative\n", m, fact_itr(m));


    plus_count = 0;
    printf("f(%d) = %d by recursion(plus : %d)\n", m, fibo_rec(m), plus_count);
    plus_count = 0;
    printf("f(%d) = %d by interative(plus : %d)\n", m, fibo_itr(m), plus_count);

}