#include "CriticalPath.h"
#include "main.h"

#include <stack>
#include <queue>
using namespace std;

int EarliestTime(GraphAdjList &G){
	stack<int> VertNum;
	stack<int> inverseTopo;
	queue<int> indegree_G;
	for (int i = 0; i < G.numVertex;i++){
		G.adjList[i].happenTime = 0;//��ʼ����ÿ�����ڵ�����緢��ʱ��Ϊ0��
		indegree_G.push(G.adjList[i].indegree);
		if (0 == G.adjList[i].indegree){//����ö��ڵ�����Ϊ0����ô��ջ
			VertNum.push(i);
		}
	}

	int count = 0;
	int topVertNum,nextNode;
	EdgeNode *tempEdge;
	while (!VertNum.empty()){
		topVertNum = VertNum.top();
		inverseTopo.push(topVertNum);
		VertNum.pop();
		tempEdge = G.adjList[topVertNum].firstEdge;
		while (tempEdge!=NULL){
			nextNode = tempEdge->adjvex;
			G.adjList[nextNode].indegree--;
			if (G.adjList[nextNode].happenTime<(G.adjList[topVertNum].happenTime + tempEdge->valueEdge)){
				G.adjList[nextNode].happenTime = (G.adjList[topVertNum].happenTime + tempEdge->valueEdge);
			}
			if (0 == G.adjList[nextNode].indegree)
				VertNum.push(nextNode);
			tempEdge = tempEdge->next;
		}
		count++;
	}

	if (count==G.numVertex)
		cout << "No Loop"<< endl;
	else
		cout << "Warning:Looooop"<< endl;
	int finalTime= G.adjList[count - 1].happenTime;
	cout << "Fastest time is: " << finalTime << endl;
	//-----------------------------------
	while (!inverseTopo.empty()){
		topVertNum = inverseTopo.top();
		G.adjList[topVertNum].lastHappenTime = finalTime;//��ʼ����ÿ�����ڵ����ٷ���ʱ��ΪfinalTime��
		inverseTopo.pop();
		tempEdge = G.adjList[topVertNum].firstEdge;
		while (tempEdge != NULL){
			nextNode = tempEdge->adjvex;
			if (G.adjList[topVertNum].lastHappenTime>(G.adjList[nextNode].lastHappenTime - tempEdge->valueEdge)){
				G.adjList[topVertNum].lastHappenTime = G.adjList[nextNode].lastHappenTime - tempEdge->valueEdge;
			}			
			tempEdge = tempEdge->next;
		}
	}

	//------------------------------------
	for (int i = 0; i < G.numVertex;i++){
		G.adjList[i].indegree = indegree_G.front();
		indegree_G.pop();
		if (G.adjList[i].happenTime == G.adjList[i].lastHappenTime){
			G.adjList[i].keyPathPoint = true;
		}
	}
	cout << "Critical Paths in the Graph:" << endl;
	showCriticalPath(G);

	return finalTime;
}

void showCriticalPath(GraphAdjList G){
	stack<int> allVertex;
	stack<int> preNode;
	stack<int> PathNode;
	stack<int> outputPath;
	EdgeNode* tempEdge;
	int pathNum = 0;
	int top_allVert, top_preNode;
	for (int i = 0; i < G.numVertex; i++){
		G.adjList[i].visited = false;//��ʼ���������н����Ϊδ���ʣ��������Ϊ��Ľڵ���뵽ջallVertex
		if (G.adjList[i].keyPathPoint==true && 0 == G.adjList[i].indegree){
			allVertex.push(i);
			preNode.push(-1);
		}
	}

	while (!allVertex.empty()){
		top_allVert = allVertex.top();
		allVertex.pop();
		G.adjList[top_allVert].visited = true;
		top_preNode = preNode.top();
		preNode.pop();
		if (PathNode.empty()){
			PathNode.push(top_allVert);
		}
		else{
			while (!PathNode.empty() && top_preNode != PathNode.top()){//��֤PathNode�ǿգ���Ϊ����᲻�ϵ���Ԫ�أ�����PathNode����Ϊ��
				G.adjList[PathNode.top()].visited = false;
				PathNode.pop();
			}
			PathNode.push(top_allVert);
		}

		if (0 == G.adjList[PathNode.top()].outdegree){//����Ϊ0������·������
			pathNum++;
			while (!PathNode.empty()){
				outputPath.push(PathNode.top());
				PathNode.pop();
			}
			cout << "Start: " << outputPath.top();
			PathNode.push(outputPath.top());
			outputPath.pop();
			while (!outputPath.empty()){
				cout << " ---> " << outputPath.top();
				PathNode.push(outputPath.top());
				outputPath.pop();
			}
			cout << endl;
		}

		tempEdge = G.adjList[top_allVert].firstEdge;
		while (tempEdge != NULL){
			if (G.adjList[tempEdge->adjvex].keyPathPoint==true && G.adjList[tempEdge->adjvex].visited == false){
				allVertex.push(tempEdge->adjvex);
				preNode.push(top_allVert);
			}
			tempEdge = tempEdge->next;
		}
	}
	cout << "The total Number of Paths in the Graph is: " << pathNum << endl;
}
/*
���ܣ���ʾ����ͼ������·������㣺���Ϊ��Ľڵ㣬�յ㣬����Ϊ��Ľڵ�
*/
void showAllPath(GraphAdjList G){
	stack<int> allVertex;
	stack<int> preNode;
	stack<int> PathNode;
	stack<int> outputPath;
	EdgeNode* tempEdge;
	int pathNum=0;
	int top_allVert,top_preNode;
	for (int i = 0; i < G.numVertex; i++){
		G.adjList[i].visited = false;//��ʼ���������н����Ϊδ���ʣ��������Ϊ��Ľڵ���뵽ջallVertex
		if (0 == G.adjList[i].indegree){
			allVertex.push(i);
			preNode.push(-1);
		}
	}

	while (!allVertex.empty()){
		top_allVert = allVertex.top();
		allVertex.pop();
		G.adjList[top_allVert].visited = true;
		top_preNode = preNode.top();
		preNode.pop();
		if (PathNode.empty()){
			PathNode.push(top_allVert);
		}
		else{
			while (!PathNode.empty()&&top_preNode != PathNode.top()){//��֤PathNode�ǿգ���Ϊ����᲻�ϵ���Ԫ�أ�����PathNode����Ϊ��
				G.adjList[PathNode.top()].visited = false;
				PathNode.pop();
			}
			PathNode.push(top_allVert);
		}

		if (0 == G.adjList[PathNode.top()].outdegree){//����Ϊ0������·������
			pathNum++;
			while (!PathNode.empty()){
				outputPath.push(PathNode.top());
				PathNode.pop();
			}
			cout << "Start: " << outputPath.top();
			PathNode.push(outputPath.top());
			outputPath.pop();
			while (!outputPath.empty()){
				cout << " ---> " << outputPath.top();
				PathNode.push(outputPath.top());
				outputPath.pop();
			}
			cout << endl;
		}

		tempEdge = G.adjList[top_allVert].firstEdge;
		while (tempEdge!=NULL){
			if (G.adjList[tempEdge->adjvex].visited==false){
				allVertex.push(tempEdge->adjvex);
				preNode.push(top_allVert);
			}
			tempEdge = tempEdge->next;
		}
	}
	cout << "The total Number of Paths in the Graph is: " << pathNum << endl;
}
void criticalPath(GraphAdjList G){
	int finalTime;
	//cout <<"Show all Paths in the Graph:" << endl;
	//showAllPath(G);
	finalTime=EarliestTime(G);
	
	//���ÿ�����ڵ����緢��ʱ��
	/*for (int i = 0; i < G.numVertex;i++){
		cout << "Vertex " << i << ": happenTime" << G.adjList[i].happenTime << "  lastHappenTime: " << G.adjList[i].lastHappenTime << endl;
	}*/

}