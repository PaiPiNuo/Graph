#include <iostream>
#include "ConstructGraph.h"

using namespace std;
/*
���ڽӱ����ʽ����ͼ
�����ʽ���Ȱ�˳����������ڵ��ֵ����1 8 8 1 1 3 1
���������붥�ڵ����ı߽ڵ��Լ�Ȩֵ����Node0:1(�߽ڵ�) 12(Ȩֵ) 4(�߽ڵ�) 9(Ȩֵ) 5(�߽ڵ�) 9(Ȩֵ) -1
Node1:0 12 -1
-1�ǽ�����־
*/
void CreateGraph(GraphAdjList &G) {
	cout << "Please input node value in turn:" << endl;
	for (int i = 0; i < G.numVertex; i++) {
		cin >> G.adjList[i].data;
		G.adjList[i].firstEdge = NULL;
		G.adjList[i].visited = false;
	}
	cout << "Please input relationship in turn(\"-1\" means no next Node):" << endl;

	int tempInput;
	EdgeNode *e, *p;
	for (int i = 0; i < G.numVertex; i++) {
		cout << "Relationship of the node " << i << " :" << endl;
		cin >> tempInput;
		while (tempInput != -1) {
			if (G.adjList[i].firstEdge == NULL) {
				e = new EdgeNode;
				e->adjvex = tempInput;
				cin >> tempInput;
				e->valueEdge = tempInput;
				G.adjList[i].firstEdge = e;
				e->next = NULL;
				cin >> tempInput;
			}
			else {
				p = new EdgeNode;
				p->adjvex = tempInput;
				cin >> tempInput;
				p->valueEdge = tempInput;
				p->next = NULL;
				e->next = p;
				e = p;
				cin >> tempInput;
			}
		}
	}
}

/*
���ڽӱ����ʽ����ͼ,���ַ�ʽ�ڹ������ڵ�֮���ϵʱ���Ӽ��һ��
�����ʽ���Ȱ�˳����������ڵ��ֵ����1 8 8 1 1 3 1
����������ÿ�������˵ĵĶ��ڵ��Լ�Ȩֵ����1(���ڵ�) 2(���ڵ�) 6(Ȩֵ)
3(���ڵ�) 4(���ڵ�) 4(Ȩֵ)
������������
��������ֹͣ��������ıߵ���ָ������ʱ���Զ�ֹͣ��
*/
void CreateGraph_Edge(GraphAdjList &G) {
	cout << "Please input Node VALUE VALUE VALUE  in turn:" << endl;
	for (int i = 0; i < G.numVertex; i++) {
		cin >> G.adjList[i].data;
		G.adjList[i].indegree = 0;//���Ϊ��
		G.adjList[i].outdegree = 0;//����Ϊ��
		G.adjList[i].firstEdge = NULL;
		G.adjList[i].visited = false;
		G.adjList[i].keyPathPoint = false;
		G.adjList[i].solved = false;
	}
	if (1 == G.networkFlag)
		cout << "Please input relationship in turn(such as (Node)0 (Node)1 (value)9 ENTER):" << endl;
	else
		cout << "Please input relationship in turn(such as (Node)0 (Node)1 ENTER):" << endl;
	int firstNode, SecondNode, edgeValue;
	EdgeNode *e, *p;
	for (int i = 0; i < G.numEdge; i++) {
		cin >> firstNode;
		cin >> SecondNode;
		if (1 == G.networkFlag)
			cin >> edgeValue;
		else
			edgeValue = 0;

		if (G.adjList[firstNode].firstEdge == NULL) {
			e = new EdgeNode;
			e->adjvex = SecondNode;
			e->valueEdge = edgeValue;
			e->next = NULL;
			G.adjList[firstNode].firstEdge = e;
		}
		else {
			e = G.adjList[firstNode].firstEdge;
			while (e->next != NULL)
				e = e->next;
			p = new EdgeNode;
			p->adjvex = SecondNode;
			p->valueEdge = edgeValue;
			p->next = NULL;
			e->next = p;
		}

		if (G.directedFlag == 1) {
			G.adjList[SecondNode].preEdge.push(firstNode);//��ǰ���ڵ��ż��뵽preEdgeջ��
			G.adjList[firstNode].outdegree++;//�ö��ڵ���ȼ�1��
			G.adjList[SecondNode].indegree++;//�ö��ڵ���ȼ�1��ֻ��������ͼ�в����ۡ���ȡ��������ȡ�
		}

		if (G.directedFlag == 0) {
			if (G.adjList[SecondNode].firstEdge == NULL) {
				e = new EdgeNode;
				e->adjvex = firstNode;
				e->valueEdge = edgeValue;
				e->next = NULL;
				G.adjList[SecondNode].firstEdge = e;
			}
			else {
				e = G.adjList[SecondNode].firstEdge;
				while (e->next != NULL)
					e = e->next;
				p = new EdgeNode;
				p->adjvex = firstNode;
				p->valueEdge = edgeValue;
				p->next = NULL;
				e->next = p;
			}
		}
	}
}

/*
���ͼ�Ƿ���ȷ����
*/
void checkGraph(GraphAdjList G) {
	for (int i = 0; i < G.numVertex; i++) {
		cout << "Node:" << i << endl;
		if (G.directedFlag == 1) {//���������ͼ����ô����������
			cout << "The Indegree : " << G.adjList[i].indegree << endl;
			cout << "The Outdegree : " << G.adjList[i].outdegree << endl;
		}
		cout << "PreNode: ";
		while (!G.adjList[i].preEdge.empty()) {//������ڵ��ǰ���ڵ���
			cout << G.adjList[i].preEdge.top() << " <-- ";
			G.adjList[i].preEdge.pop();
		}
		cout << i << endl;

		EdgeNode* edgeNode = G.adjList[i].firstEdge;
		cout << "Relationship: " << i;
		while (edgeNode != NULL) {
			if (1 == G.networkFlag)
				cout << " --> " << edgeNode->adjvex << "(value: " << edgeNode->valueEdge << ")";
			else
				cout << " --> " << edgeNode->adjvex;
			edgeNode = edgeNode->next;
		}
		cout << endl;
	}
}
