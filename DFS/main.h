#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INFTY 2147483647

typedef int dataType;
//边表节点-结构体，adjvex用来存储邻接点的位置
typedef struct EdgeNode{
	int adjvex;
	int valueEdge;
	struct EdgeNode *next;
}EdgeNode;
//顶点表-结构体，data存储顶点数据，
typedef struct{
	dataType data;
	int happenTime;//最早发生时间，求解关键路径时会用到，求工程最少时间时会用到
	int lastHappenTime;//最晚发生时间，求解关键路径时会用到
	int indegree;
	int outdegree;
	bool visited;
	bool keyPathPoint;//求解关键路径时会用到
	bool solved;//求解最短路径Dijkstra时会用到
	EdgeNode *firstEdge;
	stack<int> preEdge;//记录前驱节点
}AdjList;
typedef struct{
	AdjList *adjList;
	int numVertex;
	int numEdge;
	int directedFlag;
	int networkFlag;
}GraphAdjList;

/*
用邻接表的形式构造图
输入格式：先按顺序输入各顶节点的值，如1 8 8 1 1 3 1
         再依次输入顶节点后面的边节点以及权值，如Node0:1(边节点) 12(权值) 4(边节点) 9(权值) 5(边节点) 9(权值) -1
                                            Node1:0 12 -1
         -1是结束标志
*/
void CreateGraph(GraphAdjList &G);
/*
用邻接表的形式构造图,这种方式在构建顶节点之间关系时更加简洁一点
输入格式：先按顺序输入各顶节点的值，如1 8 8 1 1 3 1
         再依次输入每条边两端的的顶节点以及权值，如1(顶节点) 2(顶节点) 6(权值)
                                              3(顶节点) 4(顶节点) 4(权值)
                                               。。。。。。
*/
void CreateGraph_Edge(GraphAdjList &G);
/*
检查图是否正确构造
*/
void checkGraph(GraphAdjList G);
void Travel_BFS(GraphAdjList G);

/*
深度遍历算法
*/
void dfs(GraphAdjList &G, int v);
void Travel_DFS(GraphAdjList G);
/*
广度遍历算法
*/
void bfs(GraphAdjList &G, int v);
void Travel_BFS(GraphAdjList G);
#endif
