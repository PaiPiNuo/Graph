#include "TopoSort.h"

using namespace std;

bool topSort(GraphAdjList G){
	stack<AdjList> S_noIndegree;//初始化入度为零的堆栈为空
	AdjList tempAdjNode;
	EdgeNode *tempEdgeNode;
	unsigned int count = 0;
	unsigned int i = 0;
	while (i<G.numVertex){
		if (0==G.adjList[i].indegree){
			S_noIndegree.push(G.adjList[i]);//将入度为零的顶节点入栈
		}
		i++;
	}
	
	while (!S_noIndegree.empty()){
		tempAdjNode = S_noIndegree.top();//将堆栈中入度为零的顶节点弹出
		S_noIndegree.pop();
		count++;//计数弹出顶节点数量，
		tempEdgeNode = tempAdjNode.firstEdge;
		while (tempEdgeNode!=NULL){
			G.adjList[tempEdgeNode->adjvex].indegree--;//将该顶节点每个后继节点的入度减1
			if (0 == G.adjList[tempEdgeNode->adjvex].indegree)
				S_noIndegree.push(G.adjList[tempEdgeNode->adjvex]);
			tempEdgeNode = tempEdgeNode->next;
		}
	}

	if (count == G.numVertex){//当弹出的顶节点数量等于图G的顶节点数量时，说明图G没有没有互相制约
		cout <<"There is No mutual condition in this Graph" << endl;
		return true;
	}
	else{
		cout <<"Warning:Mutual Condition!" << endl;
		return false;
	}
}