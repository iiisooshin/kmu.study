// (A (B(D E) C(F G))
// (A(B(DE)C(FG)) 띄워쓰기 없는 형태로 변경
// 위반 사항 검사 -> 괄호 개수, 루트 개수 이상 (AB(DE)) -> 일단 트리 형태
// 이진 트리 검사 (재귀적 방식)

/*
 * S-expression(괄호 표기법)으로 표현된 트리가
 * 특정 규칙을 따르는 유효한 이진 트리인지 검사하는 프로그램입니다.
 *
 * [규칙]
 * 1. 트리는 전체가 괄호 '()'로 감싸여야 합니다.
 * 2. 괄호 안에는 선택적으로 알파벳 대문자 루트 노드가 하나 올 수 있습니다.
 * 3. 노드의 자식은 0개, 1개, 또는 2개일 수 있습니다. (이진 트리)
 * 4. 모든 자식은 반드시 괄호로 감싸인 서브트리 형태여야 합니다.
 * (예: (A B)는 유효하지 않음. (A (B))는 유효함)
 */

#include <stdio.h>    // 표준 입출력 함수 사용
#include <ctype.h>    // 문자 판별 함수 사용
#include <string.h>   // 문자열 처리 함수 사용

// 논리 값(참/거짓)을 나타내는 상수 정의
#define FALSE 0
#define TRUE 1

/**
 * @brief 문자열에서 모든 공백 문자를 제거합니다.
 */
void trim(char* buf) {
    char* src = buf; // 원본을 읽는 포인터
    char* dst = buf; // 결과를 쓰는 포인터
    
    // 원본 문자열 끝까지 반복
    while (*src != '\0') {
        // 공백이 아닌 문자만 복사
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0'; // 문자열 끝에 널 문자 추가
}

/**
 * @brief 문자열 내의 괄호 쌍이 올바르게 짝지어졌는지 검사합니다.
 */
int check_paren(const char* buf, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (buf[i] == '(') count++;      // 여는 괄호: 카운트 증가
        else if (buf[i] == ')') count--; // 닫는 괄호: 카운트 감소
        
        // 닫는 괄호가 더 많아지면 오류
        if (count < 0) return FALSE;
    }
    // 최종 카운트가 0이어야 유효
    return count == 0 ? TRUE : FALSE;
}

/**
 * @brief 재귀적으로 서브트리의 구조적 유효성을 검사하는 핵심 함수입니다.
 * @brief 비어있지 않은 트리는 반드시 루트로 시작해야 하며, 모든 자식은 서브트리 형태여야 합니다.
 */
int check_binary_tree_recursive(const char* buf, int* pos, int len) {
    // 모든 서브트리는 '('로 시작
    if (*pos >= len || buf[*pos] != '(') return FALSE;
    (*pos)++;

    // 베이스 케이스: 빈 트리 "()"는 유효
    if (buf[*pos] == ')') {
        (*pos)++;
        return TRUE;
    }
    
    // 규칙: 비어있지 않다면 반드시 알파벳 루트로 시작
    if (!isalpha((unsigned char)buf[*pos])) return FALSE;
    (*pos)++;

    // 규칙: 루트 이름은 한 글자여야 함 (예: 'AB' 불가)
    if (isalpha((unsigned char)buf[*pos])) return FALSE;

    // 자식 노드 검사 (최대 2개)
    int child_count = 0;
    while (*pos < len && buf[*pos] == '(') { // 규칙: 자식은 반드시 서브트리('('로 시작)여야 함
        child_count++;
        // 규칙: 자식은 2개를 초과할 수 없음
        if (child_count > 2) return FALSE;
        
        // 자식 서브트리에 대해 재귀 호출
        if (check_binary_tree_recursive(buf, pos, len) == FALSE) return FALSE;
    }

    // 모든 검사 후 ')'로 끝나야 함
    if (*pos >= len || buf[*pos] != ')') return FALSE;
    (*pos)++;

    return TRUE; // 모든 규칙 통과
}

/**
 * @brief 재귀 함수를 호출하고, 문자열 전체가 올바른 트리 구조인지 최종 확인하는 진입점 함수입니다.
 */
int check_binary_tree(const char* buf) {
    int len = strlen(buf);
    if (len == 0) return FALSE; // 빈 문자열은 유효하지 않음

    int pos = 0;
    // 재귀 함수로 구조 검사 시작
    if (check_binary_tree_recursive(buf, &pos, len) == FALSE) return FALSE;
    
    // 중요: 문자열 전체가 소모되었는지 확인 (예: "(A)B" 같이 뒤에 찌꺼기 글자가 있는지)
    if (pos != len) return FALSE;

    return TRUE;
}

/**
 * @brief 프로그램의 시작점. 사용자 입력을 받아 유효성 검사를 거친 후 최종 결과를 출력합니다.
 */
int main() {
    char buf[1000];
    
    // 사용자로부터 한 줄 입력
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 1;
    
    // 공백 제거 및 기본 괄호 검사
    trim(buf);
    if (check_paren(buf, strlen(buf)) == FALSE) {
        printf("FALSE");
        return 0;
    }

    // 최종 트리 구조 검사 및 결과 출력
    if (check_binary_tree(buf) == TRUE) {
        printf("TRUE");
    } else {
        printf("FALSE");
    }
    
    return 0;
}