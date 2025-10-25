#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define V 100 // 정점 수
#define E_SPARSE 100 // 희소 그래프 간선 수
#define E_DENSE 4000 // 밀집 그래프 간선 수

// 전역 비교 카운터
long long comparison_count;

// ======================= 인접 리스트 구조체 =======================
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adj_list[V];
} Graph;

// 인접 리스트 노드 생성
Node* create_node(int dest) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Node allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

// 인접 리스트에 간선 추가 (무방향)
void add_edge_list(Graph* graph, int u, int v) {
    // u -> v
    Node* new_node_v = create_node(v);
    new_node_v->next = graph->adj_list[u];
    graph->adj_list[u] = new_node_v;

    // v -> u
    Node* new_node_u = create_node(u);
    new_node_u->next = graph->adj_list[v];
    graph->adj_list[v] = new_node_u;
}

// 인접 리스트에서 간선 삭제 (무방향)
bool delete_edge_list(Graph* graph, int u, int v) {
    bool deleted = false;

    // u에서 v 삭제
    Node** current_ptr = &graph->adj_list[u];
    while (*current_ptr != NULL) {
        comparison_count++; // current_ptr != NULL 비교
        if ((*current_ptr)->dest == v) {
            comparison_count++; // dest 비교
            Node* temp = *current_ptr;
            *current_ptr = temp->next;
            free(temp);
            deleted = true;
            break;
        }
        comparison_count++; // dest 비교 (false인 경우)
        current_ptr = &(*current_ptr)->next;
    }

    // v에서 u 삭제
    current_ptr = &graph->adj_list[v];
    while (*current_ptr != NULL) {
        comparison_count++; // current_ptr != NULL 비교
        if ((*current_ptr)->dest == u) {
            comparison_count++; // dest 비교
            Node* temp = *current_ptr;
            *current_ptr = temp->next;
            free(temp);
            break;
        }
        comparison_count++; // dest 비교 (false인 경우)
        current_ptr = &(*current_ptr)->next;
    }
    return deleted;
}

// 인접 리스트에서 간선 존재 여부 확인
bool check_connection_list(Graph* graph, int u, int v) {
    Node* current = graph->adj_list[u];
    while (current != NULL) {
        comparison_count++; // current != NULL 비교
        if (current->dest == v) {
            comparison_count++; // dest 비교
            return true;
        }
        comparison_count++; // dest 비교 (false인 경우)
        current = current->next;
    }
    return false;
}

// 인접 리스트 인접 노드 출력 (실제 출력 대신 순회만 수행)
void print_neighbors_list(Graph* graph, int u) {
    Node* current = graph->adj_list[u];
    while (current != NULL) {
        comparison_count++; // current != NULL 비교
        // printf("%d -> %d\n", u, current->dest); // 실제 출력 로직
        current = current->next;
    }
}

// 인접 리스트 메모리 해제
long long free_list(Graph* graph) {
    long long total_nodes = 0;
    for (int i = 0; i < V; i++) {
        Node* current = graph->adj_list[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
            total_nodes++;
        }
    }
    return total_nodes;
}

// ======================= 인접 행렬 함수 =======================

// 인접 행렬 간선 삽입/삭제
void add_edge_matrix(int adj_matrix[V][V], int u, int v) {
    comparison_count++; // 간선 존재 여부 확인을 위한 비교 (0인지 1인지)
    adj_matrix[u][v] = 1;
    adj_matrix[v][u] = 1; // 무방향
}

void delete_edge_matrix(int adj_matrix[V][V], int u, int v) {
    comparison_count++; // 간선 존재 여부 확인을 위한 비교 (1인지 0인지)
    adj_matrix[u][v] = 0;
    adj_matrix[v][u] = 0;
}

// 인접 행렬 간선 존재 여부 확인
bool check_connection_matrix(int adj_matrix[V][V], int u, int v) {
    comparison_count++; // 배열 값 확인 (0인지 1인지)
    return adj_matrix[u][v] == 1;
}

// 인접 행렬 인접 노드 출력 (실제 출력 대신 순회만 수행)
void print_neighbors_matrix(int adj_matrix[V][V], int u) {
    for (int v = 0; v < V; v++) {
        comparison_count++; // v < V 비교
        comparison_count++; // adj_matrix[u][v] == 1 비교
        if (adj_matrix[u][v] == 1) {
            // printf("%d -> %d\n", u, v); // 실제 출력 로직
        }
    }
}

// ======================= 테스트 실행 함수 =======================

void perform_test(int case_num, const char* graph_type, const char* representation_type, int E_TARGET) {

    // 카운터 초기화
    comparison_count = 0;
    long long memory_bytes = 0;

    int u, v;

    // --- 1. 그래프 생성 및 메모리 계산 ---
    if (representation_type[3] == '행') { // 인접 행렬
        int adj_matrix[V][V] = { 0 };

        // 메모리 계산 (스택에 할당되지만, 필요한 최소 메모리로 가정)
        memory_bytes = sizeof(int) * V * V;

        // 그래프 생성
        int edges_added = 0;
        while (edges_added < E_TARGET) {
            u = rand() % V;
            v = rand() % V;

            if (u == v) continue;

            // 인접 행렬은 중복 확인이 O(1)이지만, 비교 횟수를 명시적으로 추가
            if (check_connection_matrix(adj_matrix, u, v) == false) {
                add_edge_matrix(adj_matrix, u, v);
                edges_added++;
            }
        }

        // --- 2. 간선 삽입/삭제 성능 측정 (랜덤 간선 10쌍 테스트) ---
        long long start_comp = comparison_count;
        for (int i = 0; i < 10; i++) {
            u = rand() % V;
            v = rand() % V;
            if (u == v) continue;

            // 삽입 (이미 있으면 중복 확인에서 걸림)
            if (check_connection_matrix(adj_matrix, u, v) == false) {
                add_edge_matrix(adj_matrix, u, v);
            }
            // 삭제 (항상 시도)
            delete_edge_matrix(adj_matrix, u, v);
        }
        long long insert_delete_comp = comparison_count - start_comp;

        // --- 3. 두 정점 연결 확인 성능 측정 (랜덤 100쌍 테스트) ---
        start_comp = comparison_count;
        for (int i = 0; i < 100; i++) {
            u = rand() % V;
            v = rand() % V;
            check_connection_matrix(adj_matrix, u, v);
        }
        long long check_connection_comp = comparison_count - start_comp;

        // --- 4. 인접 노드 출력 성능 측정 (모든 노드에 대해 수행) ---
        start_comp = comparison_count;
        for (int i = 0; i < V; i++) {
            print_neighbors_matrix(adj_matrix, i);
        }
        long long print_neighbors_comp = comparison_count - start_comp;

        printf("케이스 %d: %s 그래프 - %s\n", case_num, graph_type, representation_type);
        printf("메모리 %lld Bytes\n", memory_bytes);
        printf("간선 삽입/삭제 비교 %lld번\n", insert_delete_comp);
        printf("두 정점의 연결 확인 비교 %lld번\n", check_connection_comp);
        printf("한 노드의 인접 노드 출력 비교 %lld번\n", print_neighbors_comp);


    }
    else { // 인접 리스트
        Graph graph = { 0 };
        long long node_count = 0;

        // 메모리 계산 (헤드 포인터 배열 크기만, 노드 크기는 아래에서 계산)
        memory_bytes = sizeof(Node*) * V;

        // 그래프 생성
        int edges_added = 0;
        while (edges_added < E_TARGET) {
            u = rand() % V;
            v = rand() % V;

            if (u == v) continue;

            // 인접 리스트 중복 확인 (비교 횟수 포함)
            if (check_connection_list(&graph, u, v) == false) {
                add_edge_list(&graph, u, v);
                edges_added++;
            }
        }

        // --- 2. 간선 삽입/삭제 성능 측정 (랜덤 간선 10쌍 테스트) ---
        long long start_comp = comparison_count;
        for (int i = 0; i < 10; i++) {
            u = rand() % V;
            v = rand() % V;
            if (u == v) continue;

            // 삽입 (이미 있으면 중복 확인에서 걸림)
            if (check_connection_list(&graph, u, v) == false) {
                add_edge_list(&graph, u, v);
            }
            // 삭제 (항상 시도)
            delete_edge_list(&graph, u, v);
        }
        long long insert_delete_comp = comparison_count - start_comp;

        // --- 3. 두 정점 연결 확인 성능 측정 (랜덤 100쌍 테스트) ---
        start_comp = comparison_count;
        for (int i = 0; i < 100; i++) {
            u = rand() % V;
            v = rand() % V;
            check_connection_list(&graph, u, v);
        }
        long long check_connection_comp = comparison_count - start_comp;

        // --- 4. 인접 노드 출력 성능 측정 (모든 노드에 대해 수행) ---
        start_comp = comparison_count;
        for (int i = 0; i < V; i++) {
            print_neighbors_list(&graph, i);
        }
        long long print_neighbors_comp = comparison_count - start_comp;

        // 실제 동적 할당된 노드의 메모리 추가
        // 간선 삭제 로직이 복잡하여, 메모리 계산을 위해 그래프를 정리
        node_count = free_list(&graph);
        memory_bytes += node_count * sizeof(Node);

        printf("케이스 %d: %s 그래프 - %s\n", case_num, graph_type, representation_type);
        printf("메모리 %lld Bytes\n", memory_bytes);
        printf("간선 삽입/삭제 비교 %lld번\n", insert_delete_comp);
        printf("두 정점의 연결 확인 비교 %lld번\n", check_connection_comp);
        printf("한 노드의 인접 노드 출력 비교 %lld번\n", print_neighbors_comp);
    }
}

int main() {
    // 난수 시드 초기화
    srand(time(NULL));

    // 1. 희소그래프-인접행렬
    perform_test(1, "희소", "인접행렬", E_SPARSE);
    printf("\n");

    // 2. 희소그래프-인접리스트
    perform_test(2, "희소", "인접리스트", E_SPARSE);
    printf("\n");

    // 3. 밀집 그래프-인접행렬
    perform_test(3, "밀집", "인접행렬", E_DENSE);
    printf("\n");

    // 4. 밀집 그래프-인접리스트
    perform_test(4, "밀집", "인접리스트", E_DENSE);

    return 0;
}
