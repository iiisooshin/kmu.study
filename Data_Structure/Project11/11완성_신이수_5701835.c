//vscode에서 작성

#include<stdio.h>
#include<stdlib.h>


typedef struct StdType{
    char name[20];
    int id;
    int score;
}StdType; //구조체


int main(){

    int size, i;

    printf("몇명의 학생 정보를 입력하시나요? : ");
    scanf("%d",&size);
    getchar(); //버퍼 비우기

    StdType* students = (StdType*)malloc(size * sizeof(StdType)); //동적할당 배열생성

    if(students == NULL){
        printf("메모리 할당 실패\n");
        return 1; //오류 발생시 종료
    }


    for(int i = 0; i < size; i++){
        printf("[%d] 학생의 정보를 입력하세요 (이름 학번 점수) : ", i + 1);
        scanf("%s %d %d", students[i].name, &students[i].id, &students[i].score); //name은 배열이라 & 불필요
        getchar(); //버퍼 비우기
    }


    while(1){
        int input;
        printf("학번을 입력하세요(0이면 종료) : ");
        scanf("%d", &input);
        getchar(); //버퍼 비우기

        if(input == 0)
            break; //입력이 0이면 종료

        int found = 0; //입력 학생 유무 파악 변수
        if(input != 0){
            for(i = 0; i < size; i++){
                if(input == students[i].id){
                    printf("%s %d %d\n", students[i].name, students[i].id, students[i].score); //입력한 학생을 찾으면 출력 후 파악 변수 변경
                    found = 1;
                }
            }
            
            if(!found){
                printf("해당 학번의 학생이 없습니다.\n"); //found가 0일때(해당 학생이 없을때) 출력
            }
        }
    }




    free(students); //메모리 해제
    return 0;
}