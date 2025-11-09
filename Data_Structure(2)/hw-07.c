#include <stdio.h>
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()
#include <stdbool.h> // bool 자료형 (true, false) 사용
#include <limits.h> // INT_MAX (더 안전한 INF 값)

// --- 상수 정의 ---
#define V 10
#define E 20
#define INF INT_MAX

// --- 연산 횟수 카운터 (전역 변수) ---
unsigned long long dijkstra_ops = 0;
unsigned long long floyd_ops = 0;

// --- 함수 프로토타입 ---
void printMatrix(int matrix[V][V]);
int minDistance(int dist[V], bool sptSet[V]);
void runDijkstraAllPairs(int graph[V][V]);
void floydWarshall(int graph[V][V]);

// --- 메인 함수 ---
int main() {
    // 1. 그래프 인접 행렬 초기화
    int graph[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    // 2. 난수 생성기 시드 설정
    srand(time(NULL));

    printf("무작위 그래프 생성 중... (V=%d, E=%d)\n", V, E);

    // 3. 무작위 간선 생성 (정확히 E개)
    int edges_added = 0;
    while (edges_added < E) {
        int u = rand() % V; // 출발 정점
        int v = rand() % V; // 도착 정점
        if (u != v && graph[u][v] == INF) {
            // (참고) 현재는 1~10의 양수 가중치만 생성합니다.
            int weight = (rand() % 10) + 1;
            graph[u][v] = weight;
            edges_added++;
        }
    }
    printf("그래프 생성 완료.\n\n");

    // 4. 생성된 초기 그래프(인접 행렬) 출력
    printf("--- [1] 생성된 무작위 그래프 (초기 인접 행렬) ---\n");
    printf("(INF는 직접 연결된 간선이 없음을 의미)\n");
    printMatrix(graph);

    // 5. 다익스트라 알고리즘 V번 실행 (All-Pairs)
    runDijkstraAllPairs(graph);

    // 6. 플로이드-워셜 알고리즘 실행
    floydWarshall(graph);

    return 0;
}


// --- 다익스트라 알고리즘 구현 ---

int minDistance(int dist[V], bool sptSet[V]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        // [카운트 1] 최소 거리를 찾기 위한 비교 연산
        dijkstra_ops++;
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void runDijkstraAllPairs(int graph[V][V]) {
    int all_pairs_dist[V][V];

    for (int src = 0; src < V; src++) {
        int dist[V];
        bool sptSet[V];

        for (int i = 0; i < V; i++) {
            dist[i] = INF;
            sptSet[i] = false;
        }
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            if (u == -1 || dist[u] == INF) {
                break;
            }
            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                // [카운트 2] 간선 완화(relaxation)를 위한 비교 연산
                dijkstra_ops++;
                if (!sptSet[v] && graph[u][v] != INF &&
                    dist[u] != INF &&
                    dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        for (int j = 0; j < V; j++) {
            all_pairs_dist[src][j] = dist[j];
        }
    }

    // [수정됨] 음수 가중치 가능 여부 및 연산 횟수 출력
    printf("\n\n--- [2] 다익스트라 (All-Pairs) 실행 결과 ---\n");
    printf("[음수 가중치: 사용 불가]\n");
    printf("[총 연산 횟수: %llu]\n", dijkstra_ops);
    printf("(각 행(i)은 i에서 출발하는 최단 경로)\n");
    printMatrix(all_pairs_dist);
}


// --- 플로이드-워셜 알고리즘 구현 ---

void floydWarshall(int graph[V][V]) {
    int dist[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // 2. 플로이드-워셜 알고리즘 핵심 로직
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                // [카운트 3] 3중 루프의 핵심 비교 연산
                floyd_ops++;

                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // [수정됨] 음수 가중치 가능 여부 및 연산 횟수 출력
    printf("\n\n--- [3] 플로이드-워셜 실행 결과 ---\n");
    printf("[음수 가중치: 사용 가능 (단, 음수 사이클은 불가)]\n");
    printf("[총 연산 횟수: %llu]\n", floyd_ops);
    printf("(INF는 경로가 존재하지 않음을 의미)\n");
    printMatrix(dist);
}

// --- (공통) 행렬 출력 함수 ---

void printMatrix(int matrix[V][V]) {
    printf("     ");
    for (int i = 0; i < V; i++) {
        printf("%5d ", i);
    }
    printf("\n");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < V; i++) {
        printf("%3d |", i);
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF) {
                printf("%5s ", "INF");
            }
            else {
                printf("%5d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}
