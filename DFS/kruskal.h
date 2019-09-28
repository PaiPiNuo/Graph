#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "main.h"
using namespace std;

struct Edge{//以边为描述对象
	int littleNode;
	int bigNode;
	int edgeValue;
};

/*
功能：根据输入图G,邻接表形式存储的，
得到边的集合EdgeList，按照权值从小到大排列
*/
void init_EdgeSet(GraphAdjList G, vector<Edge> &EdgeList);
/*
返回x的根节点，返回x的根节点，并进行路径压缩
*/
int find(int x, int* pre);
/*
判断两端点是否在同一棵树中，
如果已经连通，就不用管了 ;如果不连通，就把它们所在的连通分支合并起,
*/
bool join(int x, int y, int* pre);
/*
kruskal算法生成最小生成树
input:EdgeList存储了权值从小到大的边的集合
smallTree存储最小生成树的结果-边的集合
*/
void kruskal(GraphAdjList G, vector<Edge> &smallTree, vector<Edge> EdgeList);

#endif