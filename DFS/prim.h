#ifndef PRIM_H
#define PRIM_H
#include "main.h"
#include "ConstructGraph.h"

using namespace std;


//候选边存储
struct MinEdge{
	int v;
	int valueEdge;
};


void Init_MinEdges(GraphAdjList &G, MinEdge* MinEdges,int v); 
//判断顶点v与顶点i之间是否有连接
int haveEdge(AdjList v0, int v);
//从候选边集中选出最短的顶点
int Get_MinEdge(GraphAdjList &G, MinEdge* MinEdges, vector<int> &SelectedNode);
void update_MinEdges(GraphAdjList &G, MinEdge* MinEdges, int k, vector<int> SelectedNode);
void Prim(GraphAdjList &G, int v0);

#endif