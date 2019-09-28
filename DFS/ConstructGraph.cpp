#include <iostream>
#include "ConstructGraph.h"

using namespace std;
/*
用邻接表的形式构造图
输入格式：先按顺序输入各顶节点的值，如1 8 8 1 1 3 1
再依次输入顶节点后面的边节点以及权值，如Node0:1(边节点) 12(权值) 4(边节点) 9(权值) 5(边节点) 9(权值) -1
Node1:0 12 -1
-1是结束标志
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
用邻接表的形式构造图,这种方式在构建顶节点之间关系时更加简洁一点
输入格式：先按顺序输入各顶节点的值，如1 8 8 1 1 3 1
再依次输入每条边两端的的顶节点以及权值，如1(顶节点) 2(顶节点) 6(权值)
3(顶节点) 4(顶节点) 4(权值)
。。。。。。
不需输入停止符，输入的边到达指定边数时会自动停止。
*/
void CreateGraph_Edge(GraphAdjList &G) {
	cout << "Please input Node VALUE VALUE VALUE  in turn:" << endl;
	for (int i = 0; i < G.numVertex; i++) {
		cin >> G.adjList[i].data;
		G.adjList[i].indegree = 0;//入度为零
		G.adjList[i].outdegree = 0;//出度为零
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
			G.adjList[SecondNode].preEdge.push(firstNode);//将前驱节点编号加入到preEdge栈中
			G.adjList[firstNode].outdegree++;//该顶节点出度加1，
			G.adjList[SecondNode].indegree++;//该顶节点入度加1，只有在有向图中才讨论“入度”、“出度”
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
检查图是否正确构造
*/
void checkGraph(GraphAdjList G) {
	for (int i = 0; i < G.numVertex; i++) {
		cout << "Node:" << i << endl;
		if (G.directedFlag == 1) {//如果是有向图，那么输出它的入度
			cout << "The Indegree : " << G.adjList[i].indegree << endl;
			cout << "The Outdegree : " << G.adjList[i].outdegree << endl;
		}
		cout << "PreNode: ";
		while (!G.adjList[i].preEdge.empty()) {//输出各节点的前驱节点编号
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
