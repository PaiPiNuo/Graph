#ifndef CRITICALPATH_H
#define CRITICALPATH_H
#include "main.h"

int EarliestTime(GraphAdjList &G);
void criticalPath(GraphAdjList G);
void showCriticalPath(GraphAdjList G);
/*
���ܣ���ʾ����ͼ������·������㣺���Ϊ��Ľڵ㣬�յ㣬����Ϊ��Ľڵ�
*/
void showAllPath(GraphAdjList G);
#endif