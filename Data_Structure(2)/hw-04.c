#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 트리 노드 구조체 정의
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 새 노드 생성 및 데이터 삽입
TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newNode == NULL) {
		fprintf(stderr, "메모리 할당 오류\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// 이진 탐색 트리에 노드 삽입
TreeNode* insertNode(TreeNode* root, int data) {
	if (root == NULL) {
		return createNode(data);
	}

	if (data < root->data) {
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		root->right = insertNode(root->right, data);
	}
	// 데이터가 같은 경우, 중복 삽입을 방지 (정책에 따라 다를 수 있음)
	return root;
}

// 중위 순회 (In-order Traversal)
void inorderTraversal(TreeNode* root) {
	if (root != NULL) {
		inorderTraversal(root->left);
		printf("%d ", root->data);
		inorderTraversal(root->right);
	}
}

// 트리 메모리 해제
void freeTree(TreeNode* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

// --- 추가된 함수들 ---

/**
 * @brief 이진 탐색 트리에서 특정 데이터를 탐색합니다.
 * @param root 트리의 루트 노드
 * @param data 찾으려는 데이터
 * @param count 탐색 횟수(비교 횟수)를 저장할 변수의 포인터
 * @return 데이터를 찾으면 해당 노드의 포인터를, 찾지 못하면 NULL을 반환합니다.
 */
TreeNode* searchBST(TreeNode* root, int data, int* count) {
	(*count)++; // 함수 호출 자체를 1회의 탐색(비교)으로 간주
	if (root == NULL || root->data == data) {
		return root;
	}

	if (data < root->data) {
		return searchBST(root->left, data, count);
	}
	else {
		return searchBST(root->right, data, count);
	}
}

/**
 * @brief 배열에서 특정 데이터를 선형 탐색합니다.
 * @param arr 탐색할 배열
 * @param size 배열의 크기
 * @param target 찾으려는 데이터
 * @param count 탐색 횟수(비교 횟수)를 저장할 변수의 포인터
 * @return 데이터를 찾으면 1을, 찾지 못하면 0을 반환합니다.
 */
int searchArray(int arr[], int size, int target, int* count) {
	for (int i = 0; i < size; i++) {
		(*count)++; // 배열의 각 요소와 비교할 때마다 카운트 증가
		if (arr[i] == target) {
			return 1; // 찾았음
		}
	}
	return 0; // 찾지 못했음
}


int main() {
	TreeNode* root = NULL;
	int numberArray[100]; // 난수를 저장할 일반 배열
	int i;
	int rand_num;

	srand(time(NULL));

	printf("## 1~1000 사이의 랜덤 숫자 100개로 이진 탐색 트리와 배열 생성 ##\n");
	printf("삽입된 숫자들 (생성 순서) :\n");

	for (i = 0; i < 100; i++) {
		rand_num = rand() % 1000 + 1;
		printf("%d ", rand_num);

		// 1. 이진 탐색 트리에 삽입
		root = insertNode(root, rand_num);
		// 2. 일반 배열에 저장
		numberArray[i] = rand_num;
	}
	printf("\n\n");

	printf("## 생성된 이진 탐색 트리 중위 순회 결과 (오름차순 정렬) ##\n");
	inorderTraversal(root);
	printf("\n\n");

	// --- 탐색 및 비교 로직 ---
	int target_index = rand() % 100; // 배열의 인덱스를 무작위로 선택
	int target_num = numberArray[target_index]; // 해당 인덱스의 값을 탐색 대상으로 지정

	int array_search_count = 0;
	int bst_search_count = 0;

	printf("## 임의의 숫자 [%d] 탐색 시작 ##\n\n", target_num);

	// 배열 탐색
	printf("1. 배열 (선형 탐색)...\n");
	searchArray(numberArray, 100, target_num, &array_search_count);
	printf("   -> 탐색 완료! 비교 횟수: %d\n", array_search_count);

	// 이진 탐색 트리 탐색
	printf("2. 이진 탐색 트리...\n");
	searchBST(root, target_num, &bst_search_count);
	printf("   -> 탐색 완료! 비교 횟수: %d\n\n", bst_search_count);

	printf("## 결과 비교 ##\n");
	printf("배열 탐색 횟수: %d\n", array_search_count);
	printf("이진 탐색 트리 탐색 횟수: %d\n", bst_search_count);


	// 동적 할당된 트리 메모리 해제
	freeTree(root);

	return 0;
}
