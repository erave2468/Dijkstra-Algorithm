#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100 //최대 정점의 수
#define INF	1000000	// 간선이 연결되어있지 않는 경우 무한대.

typedef struct GraphType {
	int n;
	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
	//네트워크의 인접 행렬
} GraphType;

int distance[MAX_VERTICES];//시작 정점으로부터 최단경로의 거리.
int found[MAX_VERTICES];//방문한 정점을 표시합니다.
int choose(int distance[], int n, int found[]) //현재 distance배열에서 최소 가중치 값에 있는 노드를 골라 인덱스를 반환.
{
	int i, min, minpos;
	//각 노드를 나타내는 변수를 설정합니다.

	min = INT_MAX;
	//min에 INT_MAX(무한대와 유사, 간선이 연결되지 않은 경우)를 삽입합니다.
	minpos = -1;
	for (i = 0; i < n; i++)
		//최소값 min을 찾는 for문입니다.
		//방문한 적 없는 노드들에 대해 distance 배열의 값을 비교.
		if (distance[i] < min && !found[i]) {
			//만약 현재 방문하지 않는 노드 중 i로까지의 거리가 현재 최소값 min보다 작다면,
			min = distance[i];
			//최소 거리인 i로까지의 거리를 min으로 설정합니다.
			minpos = i;
			//최소값을 가진 노드의 인덱스 i를 minpos에 저장합니다.
		}
	return minpos;
	//최소 거리 노드 인덱스인 i를 반환.
}

void print_status(GraphType* g) //최단 경로를 출력하는 함수.
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		//만약 거리가 무한대(간선이 연결되지 않은 경우)로 표시되어있다면 "*"을 출력하고,
		else
			printf("%2d ", distance[i]);
		//아니라면 거리값을 출력합니다.
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);//노드 인덱스 i를 방문했으면 1을, 방문하지 않았으면 0을 출력합니다.
	printf("\n\n");
}
void shortest_path(GraphType* g, int start) //그래프에서 start노드부터 각 노드를 거친 최단 경로를 찾는 알고리즘. 
{
	int i, u, w;
	for (i = 0; i < g->n; i++) // distance 배열을 초기화.
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; 
	//시작 정점을 방문했으므로 방문 여부를 True로 지정.
	distance[start] = 0;
	//시작 정점의 distance배열 값은 0
	for (i = 0; i <= g->n - 1; i++) {//위에서 시작 정점을 설정했으므로 하나를 뺀 n-1만큼 반복.
		print_status(g);//그래프의 최단 경로를 출력.
		u = choose(distance, g->n, found);//최소값의 인덱스를 u로 지정.
		found[u] = TRUE;//인덱스u를 방문 표시.
		for (w = 0; w < g->n; w++)
			//가중치가 가장 적은 값을 가진 정점을 집합S에 추가한 뒤 계속하여 새롭게 발견되는 최소 가중치 정보를 수정
			if (!found[w])
				//아직 선택되지 않은 정점 w
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
		//만약 u까지의 최단 거리와 u에서 w의 거리를 합친 거리가 기존의 기준점에서 w까지의 거리보다 가깝다면 그 값으로 정보를 수정.
	}
}
int main(void)
{
	GraphType g = { 7,
	{{ 0,  7,  INF, INF,   3,  10, INF },
	{ 7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{ 3,  2,  INF,  11,   0, INF,   5 },
	{ 10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 } }
	}; // 그래프 인접행렬
	shortest_path(&g, 0);
	return 0;
}