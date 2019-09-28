#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "main.h"

void dij(GraphAdjList G, int v0);
void Floyd(GraphAdjList G);
/*
求DAG有向无环图中指定起点---->指定终点的距离
拓扑排序+动态规划思想
*/
void DP_bestPath(GraphAdjList G);

#endif