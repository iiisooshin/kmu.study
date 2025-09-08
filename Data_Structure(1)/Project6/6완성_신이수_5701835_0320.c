//입력값 정수 n 이하의 모든 소수 출력

//정수 n을 입력받는다.
//for문을 이용하여 1부터 n까지 나눠지는 수가 있는지 확인한다.
//나눠지면 출력하지 않고, 나눠지지 않으면 출력한다.

//int n 선언
//for문에 활용할 i, j 선언
//정수 n을 입력받는다.
//for문을 이용하여 n을 2부터 차례로 나누어 나누어떨어지는 수가 되면 멈춘다
//만약 n까지 반복하기 전에 나누어 떨어진다면 소수가 아니다 -> 출력하지않음
//계속 반복되다가 n에서 나누어 떨어진다면 소수 -> 출력
//for i -> 소수 출력 반복
//for j -> 나누어 떨어질때까지 반복 계산

/*
int n, i, j
scanf n
for i
    for j
        if n % j == 0
            break;
    if n == j
        print n
*/







//의사코드
/*
scanf n                         //1
for i <- 2 to n do              //n
    prime = 1                   //n
    for j <- 2 to i-1 do        //n(n-1)
        if i % j == 1           //n(n-1)
            prime = 0           //n(n-1)
            break;              //n(n-1)
    if prime == 1               //n
        printf n;               //n
*/

/*
O(n)예측 
1 + 4n + 4*n(n-1) = 4n^2 + 1(예상)
O(n)은 최소 4n^2이 예상된다
*/

#include<stdio.h>


//메인코드
int main(){

    int n, i, j; //입력받을 정수 n과 for문에 사용할 i, j 변수 선언

    printf("정수 n을 입력하세요 : ");
    scanf_s("%d", &n); //정수 n 입력받기
    printf("%d 이하의 소수 : ", n);

    
    for(i=2; i <= n; i++){
        //소수를 판별하는 prime 선언 prime이 1일때, 소수
        int prime = 1;
        
        //2부터 i-1까지 순차적으로 나누어보다가 나누어떨어지는 지점이 있으면 for문 종료
		for(j = 2; j < i; j++) {
			if(i % j == 0){
                prime = 0; //소수가 아니다
				break;
			}
		}

        //i = j 즉 정수 n이 n으로 나누어 떨어졌을 때 소수이므로 출력
		if(prime){
			printf("%d ", i);
		}
    }

    return 0;
}