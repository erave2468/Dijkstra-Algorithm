#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100 //�ִ� ������ ��
#define INF	1000000	// ������ ����Ǿ����� �ʴ� ��� ���Ѵ�.

typedef struct GraphType {
	int n;
	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
	//��Ʈ��ũ�� ���� ���
} GraphType;

int distance[MAX_VERTICES];//���� �������κ��� �ִܰ���� �Ÿ�.
int found[MAX_VERTICES];//�湮�� ������ ǥ���մϴ�.
int choose(int distance[], int n, int found[]) //���� distance�迭���� �ּ� ����ġ ���� �ִ� ��带 ��� �ε����� ��ȯ.
{
	int i, min, minpos;
	//�� ��带 ��Ÿ���� ������ �����մϴ�.

	min = INT_MAX;
	//min�� INT_MAX(���Ѵ�� ����, ������ ������� ���� ���)�� �����մϴ�.
	minpos = -1;
	for (i = 0; i < n; i++)
		//�ּҰ� min�� ã�� for���Դϴ�.
		//�湮�� �� ���� ���鿡 ���� distance �迭�� ���� ��.
		if (distance[i] < min && !found[i]) {
			//���� ���� �湮���� �ʴ� ��� �� i�α����� �Ÿ��� ���� �ּҰ� min���� �۴ٸ�,
			min = distance[i];
			//�ּ� �Ÿ��� i�α����� �Ÿ��� min���� �����մϴ�.
			minpos = i;
			//�ּҰ��� ���� ����� �ε��� i�� minpos�� �����մϴ�.
		}
	return minpos;
	//�ּ� �Ÿ� ��� �ε����� i�� ��ȯ.
}

void print_status(GraphType* g) //�ִ� ��θ� ����ϴ� �Լ�.
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		//���� �Ÿ��� ���Ѵ�(������ ������� ���� ���)�� ǥ�õǾ��ִٸ� "*"�� ����ϰ�,
		else
			printf("%2d ", distance[i]);
		//�ƴ϶�� �Ÿ����� ����մϴ�.
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);//��� �ε��� i�� �湮������ 1��, �湮���� �ʾ����� 0�� ����մϴ�.
	printf("\n\n");
}
void shortest_path(GraphType* g, int start) //�׷������� start������ �� ��带 ��ģ �ִ� ��θ� ã�� �˰���. 
{
	int i, u, w;
	for (i = 0; i < g->n; i++) // distance �迭�� �ʱ�ȭ.
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; 
	//���� ������ �湮�����Ƿ� �湮 ���θ� True�� ����.
	distance[start] = 0;
	//���� ������ distance�迭 ���� 0
	for (i = 0; i <= g->n - 1; i++) {//������ ���� ������ ���������Ƿ� �ϳ��� �� n-1��ŭ �ݺ�.
		print_status(g);//�׷����� �ִ� ��θ� ���.
		u = choose(distance, g->n, found);//�ּҰ��� �ε����� u�� ����.
		found[u] = TRUE;//�ε���u�� �湮 ǥ��.
		for (w = 0; w < g->n; w++)
			//����ġ�� ���� ���� ���� ���� ������ ����S�� �߰��� �� ����Ͽ� ���Ӱ� �߰ߵǴ� �ּ� ����ġ ������ ����
			if (!found[w])
				//���� ���õ��� ���� ���� w
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
		//���� u������ �ִ� �Ÿ��� u���� w�� �Ÿ��� ��ģ �Ÿ��� ������ ���������� w������ �Ÿ����� �����ٸ� �� ������ ������ ����.
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
	}; // �׷��� �������
	shortest_path(&g, 0);
	return 0;
}