#include<stdio.h>

//int a, b, result 선언
//char op 선언
//사칙연산을 수행할 식 a op b 입력
//만약 연산자가 + 이면 a + b 수행
//만약 연산자가 - 이면 a - b 수행
//만약 연산자가 * 이면 a * b 수행
//만약 연산자가 / 이면 a / b 수행
//계산된 결과 출력
//추상자료형??




int main(){

    int a, b, result = 0;
	char op;
	
    printf("계산할 간단한 사칙연산을 입력하세요 : ");
	scanf("%d %c %d", &a, &op, &b);


	if (op == '+'){
		result = a + b;
	}else if (op == '-'){
		result = a - b;
	}else if (op == '*'){
		result = a * b;
	}else if (op == '/'){
		result = a / b;
	}

	printf("%d", result);

	return 0;





}