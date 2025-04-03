//visual studio 2022 ���� �ۼ�

#include<stdio.h>
#include<stdlib.h>


//��� (ex. �ϳ�����ž, ���� �˰���) 
//�Ǻ���ġ�� ���(recursion)������� ��������

//����Լ� ���

int plus_count;


//�Ǻ���ġ recursion
//m = 15�϶� ���� 986�� ����
//�̹� ���� ���� ����Ͽ� �Ȱ��� ���� ����
//�������� ���� ���� �ݺ� -> �����ɸ���
//ȣ�� 5 4 3 2 1 -> �ٽ� 1 2 3 4 5 �پ�� -> �ð� ����(����)
//�ð��� ���̴µ��� ��ͺ��� �ݺ���
int fibo_rec(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else {
        plus_count++;
        return(fibo_rec(n - 1) + fibo_rec(n - 2));
    }
}

//�Ǻ���ġ itr
//m = 15�϶� ���� 14�� ����
int fibo_itr(int n) {
    int f_n_2 = 0;
    int f_n_1 = 1;
    int f_n;

    for (int i = 2; i <= n; i++) {
        plus_count++;
        f_n = f_n_1 + f_n_2;
        f_n_2 = f_n_1;
        f_n_1 = f_n;
    }
    if (n == 0)
        return f_n_2;
    else if (n == 1)
        return f_n_1;
    else return f_n;
}



int main() {

    int input;
    int num;
    int repeat = 1;

    while (repeat) {

        printf("�Ǻ���ġ ���� ��� ���� (1 : �����, 2 : ��ȯ��, 0 : ����) : ");
        scanf_s("%d", &input);

        switch (input) {
        case 0:
            printf("���α׷��� ����Ǿ����ϴ�.\n");
            repeat = 0;
            break;
        case 1:
            printf("���� n�� �Է��ϼ��� (�����Ϸ��� 0 �Է�) : ");
            scanf_s("%d", &num);
            if (num == 0) {
                printf("���α׷��� ����Ǿ����ϴ�.\n");
                break;
            }
            else if (num < 0) {
                printf("�߸��� �Է��Դϴ�.");
            }
            else if (num > 0) {
                printf("f(%d) = %d (����� ���)\n", num, fibo_rec(num));
                break;
            }

        case 2:
            printf("���� n�� �Է��ϼ��� (�����Ϸ��� 0 �Է�) : ");
            scanf_s("%d", &num);
            if (num == 0) {
                printf("���α׷��� ����Ǿ����ϴ�.\n");
                break;
            }
            else if (num < 0) {
                printf("�߸��� �Է��Դϴ�.");
            }
            else if (num > 0) {
                printf("f(%d) = %d (��ȯ�� ���)\n", num, fibo_itr(num));
                break;
            }
        default:
            printf("�߸��� �Է��Դϴ�.\n");
            break;


        }
    }

    

    

    return 0;

}