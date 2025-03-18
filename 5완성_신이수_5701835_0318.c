//입력받을 정수 int a, c 선언
//입력받을 연산자 char b 선언
//사칙연산을 수행할 식 a b c 입력
//연산자 b 기호에 따라 add sub mul div 실행
//계산된 결과 출력
//추상자료형??

#include<stdio.h>

//추상자료형
void add(int a, int c); //덧셈 선언
void sub(int a, int c); //뺄셈 선언
void mul(int a, int c); //곱셈 선언
void div(int a, int c); //나눗셈 선언

//메인 코드
int main(){


    int a, c; //입력 받을 정수
	char b;   //입력 받을 연산자(문자)
	
    printf("계산할 간단한 사칙연산을 입력하세요 : ");
	scanf("%d %c %d", &a, &b, &c); //정수 a, c와 연산자 b 입력받기

	printf("계산된 결과값은 : ");

	//연산자 b의 종류에 따라 각 연산 실행
	//사칙연산 외의 다른 연산자 사용 시 오류 문구 출력
	switch(b){

		// b에 + 기호를 입력 받으면 덧셈 실행
		case '+':{
			add(a, c);
			break;
		}

		// b에 -기호를 입력 받으면 뺄셈 실행
		case '-':{
			sub(a, c);
			break;
		}

		// b에 *기호를 입력 받으면 곱셈 실행
		case '*':{
			mul(a, c);
			break;
		}

		// b에 /기호를 입력 받으면 나눗셈 실행
		case '/':{
			div(a, c);
			break;
		}

		// b에 연산자가 없거나 사칙연산기호가 아니면 오류문구 출력
		default:
		printf("잘못된 연산자입니다.\n");
		}
	
		return 0;


	} //메인코드 종료



	
	//추상자료형

	//a + c를 계산하여 출력
	void add(int a, int c) {
		printf("%d\n", a + c);
	}
	
	//a - c를 계산하여 출력
	void sub(int a, int c) {
		printf("%d\n", a - c);
	}
	
	//a * c를 계산하여 출력
	void mul(int a, int c) {
		printf("%d\n", a * c);
	}
	
	//a / c를 계산하여 출력, 단 0으로 나눌 시 계산불가 문구 출력
	void div(int a, int c) {
		if (c != 0) {
			printf("%d\n", a / c);
		} else {
			printf("0으로 나눌 수 없습니다.\n");
		}
	}
