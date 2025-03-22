//입력받을 정수 int a, c 선언
//입력받을 연산자 char b 선언
//사칙연산을 수행할 식 a b c 입력
//연산자 b 기호에 따라 add sub mul div 실행
//계산된 결과 출력
//추상자료형??
//연산자식 입력 -> 양의정수 2개 입력으로 코드 변경
//사칙연산 식 입력받아 우선순위 고려하여 계산하는 코드 추가


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


	char str[100]; //수식 저장 배열
	int num[50] = {0}; //정수 저장 배열
	char op[50] = {0}; //연산자 저장 배열
	int numC = 0;
	int opC = 0;

	printf("계산할 수식을 입력하세요 (예 : 3 + 5 * 2 - 8 / 4) : ");
	fgets(str, sizeof(str), stdin);
	//사용하지 않는 배열 문자 제거
	for(int i = 0; i < sizeof(str); i++){
		if(str[i] == '\n'){
			str[i] = '\0';
			break;
		}


	printf("계산된 결과값은 : %.2f", result);

	
	return 0;
	}
}
	
	// //사칙연산 시행
	// for(int i = 0; i <= 3; i++){
	// 	switch(op[i]){

	// 		// + 기호를 입력 받으면 덧셈 실행
	// 		case '+':{
	// 			num[i+1] = add(num[i], num[i+1]);
	// 			break;
	// 		}

	// 		// -기호를 입력 받으면 뺄셈 실행
	// 		case '-':{
	// 			num[i+1] = (float)sub(num[i], num[i+1]);
	// 			break;
	// 		}

	// 		// *기호를 입력 받으면 곱셈 실행
	// 		case '*':{
	// 			num[i+1] = (float)mul(num[i], num[i+1]);
	// 			break;
	// 		}

	// 		// /기호를 입력 받으면 나눗셈 실행
	// 		case '/':{
	// 			num[i+1] = (float)div(num[i], num[i+1]);
	// 			break;
	// 		}

	// 		// 사칙연산기호가 아닌 다른기호면 오류문구 출력
	// 		default:
	// 		printf("잘못된 연산자입니다.\n");
	// 		}
	



	
	//추상자료형

	//a + b를 계산하여 출력
	void add(int a, int b){
		printf("%d\n", a + b);
	}
	
	//a - b를 계산하여 출력
	void sub(int a, int b){
		printf("%d\n", a - b);
	}
	
	//a * b를 계산하여 출력
	void mul(int a, int b){
		printf("%d\n", a * b);
	}
	
	//a / b를 계산하여 출력, 단 0으로 나눌 시 계산불가 문구 출력
	void div(float a, float b) {
		if (b != 0){
			printf("%.2f\n", a / b);
		}else{
			printf("0으로 나눌 수 없습니다.\n");
		}
	}
