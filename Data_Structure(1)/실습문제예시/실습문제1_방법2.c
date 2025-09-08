#include <stdio.h>

int main() {
	int input;
	int result = 0;
	printf("정수를 입력하세요 : ");
	scanf_s("%d", &input);

	printf("입력된 정수의 32비트 표현 : ");
	//비트 연산자
	for (int i = 31; i >= 0; --i) {
		result = input >> i & 1;
		printf("%d", result);
	}
	

	return 0;
}