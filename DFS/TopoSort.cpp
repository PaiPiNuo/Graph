#include "TopoSort.h"

using namespace std;

bool topSort(GraphAdjList G){
	stack<AdjList> S_noIndegree;//��ʼ�����Ϊ��Ķ�ջΪ��
	AdjList tempAdjNode;
	EdgeNode *tempEdgeNode;
	unsigned int count = 0;
	unsigned int i = 0;
	while (i<G.numVertex){
		if (0==G.adjList[i].indegree){
			S_noIndegree.push(G.adjList[i]);//�����Ϊ��Ķ��ڵ���ջ
		}
		i++;
	}
	
	while (!S_noIndegree.empty()){
		tempAdjNode = S_noIndegree.top();//����ջ�����Ϊ��Ķ��ڵ㵯��
		S_noIndegree.pop();
		count++;//�����������ڵ�������
		tempEdgeNode = tempAdjNode.firstEdge;
		while (tempEdgeNode!=NULL){
			G.adjList[tempEdgeNode->adjvex].indegree--;//���ö��ڵ�ÿ����̽ڵ����ȼ�1
			if (0 == G.adjList[tempEdgeNode->adjvex].indegree)
				S_noIndegree.push(G.adjList[tempEdgeNode->adjvex]);
			tempEdgeNode = tempEdgeNode->next;
		}
	}

	if (count == G.numVertex){//�������Ķ��ڵ���������ͼG�Ķ��ڵ�����ʱ��˵��ͼGû��û�л�����Լ
		cout <<"There is No mutual condition in this Graph" << endl;
		return true;
	}
	else{
		cout <<"Warning:Mutual Condition!" << endl;
		return false;
	}
}