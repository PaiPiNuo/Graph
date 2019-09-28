#ifndef PRIM_H
#define PRIM_H
#include "main.h"
#include "ConstructGraph.h"

using namespace std;


//��ѡ�ߴ洢
struct MinEdge{
	int v;
	int valueEdge;
};


void Init_MinEdges(GraphAdjList &G, MinEdge* MinEdges,int v); 
//�ж϶���v�붥��i֮���Ƿ�������
int haveEdge(AdjList v0, int v);
//�Ӻ�ѡ�߼���ѡ����̵Ķ���
int Get_MinEdge(GraphAdjList &G, MinEdge* MinEdges, vector<int> &SelectedNode);
void update_MinEdges(GraphAdjList &G, MinEdge* MinEdges, int k, vector<int> SelectedNode);
void Prim(GraphAdjList &G, int v0);

#endif