#include<stdio.h>

//int a, b, c 선언
//사칙연산을 수행할 식 a b c 입력
//연산자 b 기호에 따라 add sub mul div 실행
//계산된 결과 출력
//추상자료형??

void add(int a, int c);
void sub(int a, int c);
void mul(int a, int c);
void div(int a, int c);


int main(){

    int a, c;
	char b;
	
    printf("계산할 간단한 사칙연산을 입력하세요 : ");
	scanf("%d %c %d", &a, &b, &c);

	printf("계산된 결과값은 : ");

	switch(b){
		case '+':{
			add(a, c);
			break;
		}
		case '-':{
			sub(a, c);
			break;
		}
		case '*':{
			mul(a, c);
			break;
		}
		case '/':{
			div(a, c);
			break;
		}
		default:
		printf("잘못된 연산자입니다.\n");
		}
	
		return 0;


	}


	void add(int a, int c) {
		printf("%d\n", a + c);
	}
	
	void sub(int a, int c) {
		printf("%d\n", a - c);
	}
	
	void mul(int a, int c) {
		printf("%d\n", a * c);
	}
	
	void div(int a, int c) {
		if (c != 0) {
			printf("%d\n", a / c);
		} else {
			printf("0으로 나눌 수 없습니다.\n");
		}
	}
