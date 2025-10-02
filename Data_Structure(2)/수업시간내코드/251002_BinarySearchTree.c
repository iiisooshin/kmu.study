// 1~1000 사이의 100가지 수로 이진탐색트리 만들기

#include<stdio.h>
#include<stdlib.h>
#include<time.h>



typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;

} TreeNode;


// 새 노드 생성 및 데이터 삽입
TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

	if (newNode == (TreeNode*)NULL) {
		fprintf(stderr, "메모리 할당 오류\n");
		return NULL;
	}

	newNode->data = data;
	newNode->left = (TreeNode*)NULL;
	newNode->right = (TreeNode*)NULL;

	return newNode;
}


TreeNode* insertNode(TreeNode* root, int data) {
	if (root == (TreeNode*)NULL) {
		return createNode(data);
	}

	if (data < root->data) {
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		root->right = insertNode(root->right, data);
	}
	else printf("\n값이 중복되었습니다.\n");

	return root;

}

void inorderTraversal(TreeNode* root) {
	if (root != NULL) {
		inorderTraversal(root->left);
		printf("%d ", root->data);
		inorderTraversal(root->right);
	}
}


void freeTree(TreeNode* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}


int main() {

	TreeNode* root = NULL;
	int i;
	int rand_num;

	srand(time(NULL));


	printf("## 1~1000 사이의 랜덤 숫자 100개로 이진 탐색 트리 생성 ##\n");
	printf("삽입된 숫자들 (생성 순서) :\n");

	for (i = 0; i < 100; i++) {
		rand_num = rand() % 1000 + 1;
		printf("%d ", rand_num);
		root = insertNode(root, rand_num);
	}
	printf("\n\n");

	printf("## 생성된 이진 탐색 트리 중위 순회 결과 (오름차순 정렬) ##\n");
	inorderTraversal(root);
	printf("\n");

	freeTree(root);

	return 0;

}
