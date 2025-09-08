//입력받을 정수 int a, c 선언
//입력받을 연산자 char b 선언
//사칙연산을 수행할 식 a b c 입력
//연산자 b 기호에 따라 add sub mul div 실행
//계산된 결과 출력
//추상자료형??
//연산자식 입력 -> 양의정수 2개 입력으로 코드 변경

#include<stdio.h>

//추상자료형
void add(int a, int b); //덧셈 선언
void sub(int a, int b); //뺄셈 선언
void mul(int a, int b); //곱셈 선언
void div(float a, float b); //나눗셈 선언

//메인 코드
int main(){

	//계산 받을 양의 정수 2개 입력받기
	int a, b;
	printf("첫 번째 양의 정수를 입력하세요 : ");
	scanf("%d", &a);
	printf("두 번째 양의 정수를 입력하세요 : ");
	scanf("%d", &b);


	//입력 받은 양의 정수 a, b를 활용해 각 사칙연산 계산하여 출력
	printf("덧셈 : ");
	add(a, b);
	printf("뺄셈 : ");
	sub(a, b);
	printf("곱셈 : ");
	mul(a, b);
	printf("나눗셈 : ");
	div(a, b);

	return 0;

	//정수 a 연산자 b 정수 c를 받았을 때 코드

    // int a, c; //입력 받을 정수
	// char b;   //입력 받을 연산자(문자)
	
    // printf("계산할 간단한 사칙연산을 입력하세요 : ");
	// scanf("%d %c %d", &a, &b, &c); //정수 a, c와 연산자 b 입력받기

	// printf("계산된 결과값은 : ");

	// //연산자 b의 종류에 따라 각 연산 실행
	// //사칙연산 외의 다른 연산자 사용 시 오류 문구 출력
	// switch(b){

	// 	// b에 + 기호를 입력 받으면 덧셈 실행
	// 	case '+':{
	// 		add(a, c);
	// 		break;
	// 	}

	// 	// b에 -기호를 입력 받으면 뺄셈 실행
	// 	case '-':{
	// 		sub(a, c);
	// 		break;
	// 	}

	// 	// b에 *기호를 입력 받으면 곱셈 실행
	// 	case '*':{
	// 		mul(a, c);
	// 		break;
	// 	}

	// 	// b에 /기호를 입력 받으면 나눗셈 실행
	// 	case '/':{
	// 		div(a, c);
	// 		break;
	// 	}

	// 	// b에 연산자가 없거나 사칙연산기호가 아니면 오류문구 출력
	// 	default:
	// 	printf("잘못된 연산자입니다.\n");
	// 	}

	//return 0;
	

	} //메인코드 종료



	
	//추상자료형

	//a + b를 계산하여 출력
	void add(int a, int b) {
		printf("%d\n", a + b);
	}
	
	//a - b를 계산하여 출력
	void sub(int a, int b) {
		printf("%d\n", a - b);
	}
	
	//a * b를 계산하여 출력
	void mul(int a, int b) {
		printf("%d\n", a * b);
	}
	
	//a / b를 계산하여 출력, 단 0으로 나눌 시 계산불가 문구 출력
	void div(float a, float b) {
		if (b != 0) {
			printf("%.2f\n", a / b);
		} else {
			printf("0으로 나눌 수 없습니다.\n");
		}
	}
