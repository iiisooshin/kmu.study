// (A (B(D E) C(F G))
// (A(B(DE)C(FG)) ������� ���� ���·� ����
// ���� ���� �˻� -> ��ȣ ����, ��Ʈ ���� �̻� (AB(DE)) -> �ϴ� Ʈ�� ����
// ���� Ʈ�� �˻� (����� ���)

/*
 * S-expression(��ȣ ǥ���)���� ǥ���� Ʈ����
 * Ư�� ��Ģ�� ������ ��ȿ�� ���� Ʈ������ �˻��ϴ� ���α׷��Դϴ�.
 *
 * [��Ģ]
 * 1. Ʈ���� ��ü�� ��ȣ '()'�� ���ο��� �մϴ�.
 * 2. ��ȣ �ȿ��� ���������� ���ĺ� �빮�� ��Ʈ ��尡 �ϳ� �� �� �ֽ��ϴ�.
 * 3. ����� �ڽ��� 0��, 1��, �Ǵ� 2���� �� �ֽ��ϴ�. (���� Ʈ��)
 * 4. ��� �ڽ��� �ݵ�� ��ȣ�� ������ ����Ʈ�� ���¿��� �մϴ�.
 * (��: (A B)�� ��ȿ���� ����. (A (B))�� ��ȿ��)
 */

#include <stdio.h>    // ǥ�� ����� �Լ� ���
#include <ctype.h>    // ���� �Ǻ� �Լ� ���
#include <string.h>   // ���ڿ� ó�� �Լ� ���

// �� ��(��/����)�� ��Ÿ���� ��� ����
#define FALSE 0
#define TRUE 1

/**
 * @brief ���ڿ����� ��� ���� ���ڸ� �����մϴ�.
 */
void trim(char* buf) {
    char* src = buf; // ������ �д� ������
    char* dst = buf; // ����� ���� ������
    
    // ���� ���ڿ� ������ �ݺ�
    while (*src != '\0') {
        // ������ �ƴ� ���ڸ� ����
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0'; // ���ڿ� ���� �� ���� �߰�
}

/**
 * @brief ���ڿ� ���� ��ȣ ���� �ùٸ��� ¦���������� �˻��մϴ�.
 */
int check_paren(const char* buf, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (buf[i] == '(') count++;      // ���� ��ȣ: ī��Ʈ ����
        else if (buf[i] == ')') count--; // �ݴ� ��ȣ: ī��Ʈ ����
        
        // �ݴ� ��ȣ�� �� �������� ����
        if (count < 0) return FALSE;
    }
    // ���� ī��Ʈ�� 0�̾�� ��ȿ
    return count == 0 ? TRUE : FALSE;
}

/**
 * @brief ��������� ����Ʈ���� ������ ��ȿ���� �˻��ϴ� �ٽ� �Լ��Դϴ�.
 * @brief ������� ���� Ʈ���� �ݵ�� ��Ʈ�� �����ؾ� �ϸ�, ��� �ڽ��� ����Ʈ�� ���¿��� �մϴ�.
 */
int check_binary_tree_recursive(const char* buf, int* pos, int len) {
    // ��� ����Ʈ���� '('�� ����
    if (*pos >= len || buf[*pos] != '(') return FALSE;
    (*pos)++;

    // ���̽� ���̽�: �� Ʈ�� "()"�� ��ȿ
    if (buf[*pos] == ')') {
        (*pos)++;
        return TRUE;
    }
    
    // ��Ģ: ������� �ʴٸ� �ݵ�� ���ĺ� ��Ʈ�� ����
    if (!isalpha((unsigned char)buf[*pos])) return FALSE;
    (*pos)++;

    // ��Ģ: ��Ʈ �̸��� �� ���ڿ��� �� (��: 'AB' �Ұ�)
    if (isalpha((unsigned char)buf[*pos])) return FALSE;

    // �ڽ� ��� �˻� (�ִ� 2��)
    int child_count = 0;
    while (*pos < len && buf[*pos] == '(') { // ��Ģ: �ڽ��� �ݵ�� ����Ʈ��('('�� ����)���� ��
        child_count++;
        // ��Ģ: �ڽ��� 2���� �ʰ��� �� ����
        if (child_count > 2) return FALSE;
        
        // �ڽ� ����Ʈ���� ���� ��� ȣ��
        if (check_binary_tree_recursive(buf, pos, len) == FALSE) return FALSE;
    }

    // ��� �˻� �� ')'�� ������ ��
    if (*pos >= len || buf[*pos] != ')') return FALSE;
    (*pos)++;

    return TRUE; // ��� ��Ģ ���
}

/**
 * @brief ��� �Լ��� ȣ���ϰ�, ���ڿ� ��ü�� �ùٸ� Ʈ�� �������� ���� Ȯ���ϴ� ������ �Լ��Դϴ�.
 */
int check_binary_tree(const char* buf) {
    int len = strlen(buf);
    if (len == 0) return FALSE; // �� ���ڿ��� ��ȿ���� ����

    int pos = 0;
    // ��� �Լ��� ���� �˻� ����
    if (check_binary_tree_recursive(buf, &pos, len) == FALSE) return FALSE;
    
    // �߿�: ���ڿ� ��ü�� �Ҹ�Ǿ����� Ȯ�� (��: "(A)B" ���� �ڿ� ��� ���ڰ� �ִ���)
    if (pos != len) return FALSE;

    return TRUE;
}

/**
 * @brief ���α׷��� ������. ����� �Է��� �޾� ��ȿ�� �˻縦 ��ģ �� ���� ����� ����մϴ�.
 */
int main() {
    char buf[1000];
    
    // ����ڷκ��� �� �� �Է�
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 1;
    
    // ���� ���� �� �⺻ ��ȣ �˻�
    trim(buf);
    if (check_paren(buf, strlen(buf)) == FALSE) {
        printf("FALSE");
        return 0;
    }

    // ���� Ʈ�� ���� �˻� �� ��� ���
    if (check_binary_tree(buf) == TRUE) {
        printf("TRUE");
    } else {
        printf("FALSE");
    }
    
    return 0;
}