#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "main.h"

void dij(GraphAdjList G, int v0);
void Floyd(GraphAdjList G);
/*
��DAG�����޻�ͼ��ָ�����---->ָ���յ�ľ���
��������+��̬�滮˼��
*/
void DP_bestPath(GraphAdjList G);

#endif