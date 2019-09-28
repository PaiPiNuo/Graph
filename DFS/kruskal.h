#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "main.h"
using namespace std;

struct Edge{//�Ա�Ϊ��������
	int littleNode;
	int bigNode;
	int edgeValue;
};

/*
���ܣ���������ͼG,�ڽӱ���ʽ�洢�ģ�
�õ��ߵļ���EdgeList������Ȩֵ��С��������
*/
void init_EdgeSet(GraphAdjList G, vector<Edge> &EdgeList);
/*
����x�ĸ��ڵ㣬����x�ĸ��ڵ㣬������·��ѹ��
*/
int find(int x, int* pre);
/*
�ж����˵��Ƿ���ͬһ�����У�
����Ѿ���ͨ���Ͳ��ù��� ;�������ͨ���Ͱ��������ڵ���ͨ��֧�ϲ���,
*/
bool join(int x, int y, int* pre);
/*
kruskal�㷨������С������
input:EdgeList�洢��Ȩֵ��С����ıߵļ���
smallTree�洢��С�������Ľ��-�ߵļ���
*/
void kruskal(GraphAdjList G, vector<Edge> &smallTree, vector<Edge> EdgeList);

#endif