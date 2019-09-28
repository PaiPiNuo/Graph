#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INFTY 2147483647

typedef int dataType;
//�߱�ڵ�-�ṹ�壬adjvex�����洢�ڽӵ��λ��
typedef struct EdgeNode{
	int adjvex;
	int valueEdge;
	struct EdgeNode *next;
}EdgeNode;
//�����-�ṹ�壬data�洢�������ݣ�
typedef struct{
	dataType data;
	int happenTime;//���緢��ʱ�䣬���ؼ�·��ʱ���õ����󹤳�����ʱ��ʱ���õ�
	int lastHappenTime;//������ʱ�䣬���ؼ�·��ʱ���õ�
	int indegree;
	int outdegree;
	bool visited;
	bool keyPathPoint;//���ؼ�·��ʱ���õ�
	bool solved;//������·��Dijkstraʱ���õ�
	EdgeNode *firstEdge;
	stack<int> preEdge;//��¼ǰ���ڵ�
}AdjList;
typedef struct{
	AdjList *adjList;
	int numVertex;
	int numEdge;
	int directedFlag;
	int networkFlag;
}GraphAdjList;

/*
���ڽӱ����ʽ����ͼ
�����ʽ���Ȱ�˳����������ڵ��ֵ����1 8 8 1 1 3 1
         ���������붥�ڵ����ı߽ڵ��Լ�Ȩֵ����Node0:1(�߽ڵ�) 12(Ȩֵ) 4(�߽ڵ�) 9(Ȩֵ) 5(�߽ڵ�) 9(Ȩֵ) -1
                                            Node1:0 12 -1
         -1�ǽ�����־
*/
void CreateGraph(GraphAdjList &G);
/*
���ڽӱ����ʽ����ͼ,���ַ�ʽ�ڹ������ڵ�֮���ϵʱ���Ӽ��һ��
�����ʽ���Ȱ�˳����������ڵ��ֵ����1 8 8 1 1 3 1
         ����������ÿ�������˵ĵĶ��ڵ��Լ�Ȩֵ����1(���ڵ�) 2(���ڵ�) 6(Ȩֵ)
                                              3(���ڵ�) 4(���ڵ�) 4(Ȩֵ)
                                               ������������
*/
void CreateGraph_Edge(GraphAdjList &G);
/*
���ͼ�Ƿ���ȷ����
*/
void checkGraph(GraphAdjList G);
void Travel_BFS(GraphAdjList G);

/*
��ȱ����㷨
*/
void dfs(GraphAdjList &G, int v);
void Travel_DFS(GraphAdjList G);
/*
��ȱ����㷨
*/
void bfs(GraphAdjList &G, int v);
void Travel_BFS(GraphAdjList G);
#endif
