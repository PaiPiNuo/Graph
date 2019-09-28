#ifndef CRITICALPATH_H
#define CRITICALPATH_H
#include "main.h"

int EarliestTime(GraphAdjList &G);
void criticalPath(GraphAdjList G);
void showCriticalPath(GraphAdjList G);
/*
功能：显示有向图中所有路径，起点：入度为零的节点，终点，出度为零的节点
*/
void showAllPath(GraphAdjList G);
#endif