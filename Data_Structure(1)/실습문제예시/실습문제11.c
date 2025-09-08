#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int id;
    int score;
} Student;

int main() {
    int n;
    printf("몇명의 학생 정보를 입력하시나요? ");
    scanf_s("%d", &n);

    // 학생 수만큼 구조체 메모리 한 번에 할당
    Student* students = (Student*)malloc(n * sizeof(Student));
    if (students == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("[%d] 학생의 정보를 입력하세요 (이름 학번 점수): ", i + 1);
        scanf_s("%s %d %d", students[i].name, (unsigned)_countof(students[i].name),
            &students[i].id, &students[i].score);
    }

    while (1) {
        int query;
        printf("학번을 입력하세요 (0이면 종료)? ");
        scanf_s("%d", &query);

        if (query == 0) break;

        int found = 0;
        for (int i = 0; i < n; i++) {
            if (students[i].id == query) {
                printf("%s %d %d\n", students[i].name, students[i].id, students[i].score);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("해당 학번의 학생이 없습니다.\n");
        }
    }

    free(students);
    return 0;
}
