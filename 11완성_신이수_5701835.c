//vscode에서 작성

#include<stdio.h>
#include<stdlib.h>

typedef struct StdType{
    char name[20];
    int id;
    int score;
}StdType;




int main(){

    int n;
    // StdType* sptr = students;

    printf("몇명의 학생 정보를 입력하시나요? : ");
    scanf("%d",&n);

    for(int i = 0; i < n; i++){
        printf("[%d] 학생의 정보를 입력하세요 (이름 학번 점수) : ", i + 1);

    }



    while(1){
        int input = 0;
        printf("학번을 입력하세요 (0이면 종료)? ");
        scanf("%d", &input);

        if(input == (*sptr).id){
            printf("%c %d %d", (*sptr).name, (*sptr).id, (*sptr).score)
        }else if(input == 0)
            break;
    }




    return 0;
}