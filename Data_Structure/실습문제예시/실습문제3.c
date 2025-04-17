#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 🔧 아스키코드로 대소문자 변환
char* translater(const char* input) {
    int len = strlen(input);
    char* result = (char*)malloc(len + 1);  // +1 for '\0'

    if (result == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            result[i] = input[i] + 32; // 대문자 → 소문자
        }
        else if (input[i] >= 'a' && input[i] <= 'z') {
            result[i] = input[i] - 32; // 소문자 → 대문자
        }
        else {
            result[i] = input[i]; // 공백, 기호 등은 그대로
        }
    }

    result[len] = '\0';
    return result;
}

// 🧪 main 함수
int main() {
    char input[1000];

    printf("문자열을 입력하세요: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // 개행 제거

    int len = strlen(input);
    printf("문자열의 길이: %d\n", len);

    char* converted = translater(input);
    printf("변환된 문자열: %s\n", converted);

    free(converted);  // 메모리 해제
    return 0;
}
