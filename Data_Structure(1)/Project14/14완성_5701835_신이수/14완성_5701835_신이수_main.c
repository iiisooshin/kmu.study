#include <stdio.h>
#include <stdlib.h>

#include "linearList.h"




//첫번째 알고리즘
//첫번째 다항식의 첫번째 항을 두번째 다항식의 각 항에 곱하고
//첫번째 다항식의 두번째 항을 두번째 다항식의 각 항에 곱하고... 반복하여 새로운 리스트에 저장
//이후 만들어진 각 리스트를 polyadd()를 활용해 더한 값?을 출력


//두번째 알고리즘
// 다항식 곱셈 +- 기준으로 항 나누기
// 나눈 항을 곱한다 계수끼리 곱하고 차수끼리 더하고 반복
// 첫번째 다항식을 두번째 다항식의 첫 항에 곱하고 리스트에 넣기
// 첫번째 다항식을 두번째 다항식의 두번째 항에 곱하고 리스트에 넣기... 반복후 종료
// 만들어진 리스트끼리 비교해서 같은 차수 항 끼리 더하고 ordered_insertList


//부족한부분, 문제가생기는부분 수정 후 최종 알고리즘
//식을 배열로 받아서 x기준으로 x앞은 계수로 받고 x^이후 숫자는 차수로 받고
//+는 무시하고 -면 계수에다가 합쳐서 받기 (-1)
//첫 글자 숫자 coef (숫자가 아니라 x가 바로 오면 1) x뒤에 ^가 있으면 ^이후 숫자는 expo (^가 없으면 1)
//만약에 x도 ^도 없으면 숫자 coef, expo = 0
//계산 결과를 한개의 리스트로 받은 후 리스트 내에서 같은 차수가 있으면 서로 더하기(리스트를 따로 만들어 polyadd() 사용하려니까 메모리 문제 발생)

//알고리즘을 이해하고 완성은 했으나 코딩지식 부족으로 코드 자체를 완전히 이해하지 못함. 추가로 코드 분석이 필요하다.
//코드 전체를 프린트해서 한줄한줄 해석해보기



//다항식 곱셈
listType* polymul(listType* f, listType* s) {
	listType* temp = createList((f->last + 1) * (s->last + 1));

	for (int i = 0; i <= f->last; i++) {
		for (int j = 0; j <= s->last; j++) {
			elementType f_item = readItem(f, i);
			elementType s_item = readItem(s, j);

			int new_coef = f_item.coef * s_item.coef;
			int new_expo = f_item.expo + s_item.expo;

			if (new_coef != 0) {
				ordered_insertItem(temp, (elementType) { new_coef, new_expo });
			}
		}
	}
	

	// 동일 차수의 항 합치기
	mergeSameExpo(temp);

	// 결과를 새로운 리스트에 복사
	listType* result = createList(temp->last + 1);
	for (int k = 0; k <= temp->last; k++) {
		ordered_insertItem(result, readItem(temp, k));
	}

	destroyList(temp);

	return result;
}


int mergeSameExpo(listType* list) {
	if (list->last <= 0) return; // 항이 1개 이하면 처리 불필요

	int newLast = 0; // 새로운 리스트의 마지막 인덱스
	for (int i = 1; i <= list->last; i++) {
		if (list->array[i].expo == list->array[newLast].expo) {
			// 동일 차수면 계수 합치기
			list->array[newLast].coef += list->array[i].coef;
		}
		else {
			// 차수가 다르면 다음 위치로 이동
			newLast++;
			list->array[newLast] = list->array[i];
		}
	}
	list->last = newLast;

	// 계수가 0인 항 제거
	int writePos = 0;
	for (int i = 0; i <= list->last; i++) {
		if (list->array[i].coef != 0) {
			list->array[writePos] = list->array[i];
			writePos++;
		}
	}
	list->last = writePos - 1;
}


// 동적 할당으로 문자열 입력받기
char* getDynamicString(int* len) {
	int capacity = 10;
	char* str = (char*)malloc(capacity * sizeof(char));
	if (str == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	int size = 0;
	char ch;

	while ((ch = getchar()) != '\n' && ch != EOF) {
		if (size >= capacity - 1) {
			capacity *= 2;
			char* temp = (char*)realloc(str, capacity * sizeof(char));
			if (temp == NULL) {
				fprintf(stderr, "Memory reallocation failed\n");
				free(str);
				exit(1);
			}
			str = temp;
		}
		str[size++] = ch;
	}

	str[size] = '\0';

	char* finalStr = (char*)realloc(str, (size + 1) * sizeof(char));
	if (finalStr == NULL) {
		fprintf(stderr, "Memory reallocation failed\n");
		free(str);
		exit(1);
	}

	*len = size;
	return finalStr;
}

// 숫자인지 확인
int isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

// 공백인지 확인
int isSpace(char ch) {
	return ch == ' ' || ch == '\t';
}

// 다항식 파싱
void parsePoly(listType* poly, const char* input, int len) {
	int pos = 0;
	int sign = 1;

	while (pos < len) {
		while (pos < len && isSpace(input[pos])) pos++;
		if (pos >= len) break;

		int coef = 1, expo = 0;

		if (input[pos] == '+' || input[pos] == '-') {
			sign = (input[pos] == '-') ? -1 : 1;
			pos++;
			while (pos < len && isSpace(input[pos])) pos++;
		}

		if (pos < len && isDigit(input[pos])) {
			coef = 0;
			while (pos < len && isDigit(input[pos])) {
				coef = coef * 10 + (input[pos] - '0');
				pos++;
			}
			coef *= sign;
			sign = 1;
		}
		else if (pos < len && input[pos] == 'x') {
			coef = sign;
			sign = 1;
		}

		if (pos < len && input[pos] == 'x') {
			pos++;
			expo = 1;
			if (pos < len && input[pos] == '^') {
				pos++;
				expo = 0;
				while (pos < len && isDigit(input[pos])) {
					expo = expo * 10 + (input[pos] - '0');
					pos++;
				}
			}
		}
		else {
			expo = 0;
		}

		if (coef != 0) {
			ordered_insertItem(poly, (elementType) { coef, expo });
		}
	}
}



int main() {

	listType* poly1, * poly2, * result;

	poly1 = createList(20);
	poly2 = createList(20);



	printf("첫 번째 다항식을 입력하세요 (예 : 3x^2+4x+1)\n");
	int len1;
	char* input1 = getDynamicString(&len1);
	parsePoly(poly1, input1, len1);
	
	
	
	
	printf("두 번째 다항식을 입력하세요 (예 : 2x^2+5x+3)\n");
	int len2;
	char* input2 = getDynamicString(&len2);
	parsePoly(poly2, input2, len2);
	




	printf("[곱셈 결과]\n");
	result = polymul(poly1, poly2);
	printList(result);


	destroyList(poly1);
	destroyList(poly2);
	destroyList(result); 
	free(input1);
	free(input2);




	return 0;


}