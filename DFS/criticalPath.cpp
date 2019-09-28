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
		G.adjList[i].happenTime = 0;//初始化，每个顶节点的最早发生时间为0；
		indegree_G.push(G.adjList[i].indegree);
		if (0 == G.adjList[i].indegree){//如果该顶节点的入度为0，那么入栈
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
		G.adjList[topVertNum].lastHappenTime = finalTime;//初始化，每个顶节点的最迟发生时间为finalTime；
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
		G.adjList[i].visited = false;//初始化，将所有结点置为未访问，并将入度为零的节点加入到栈allVertex
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
			while (!PathNode.empty() && top_preNode != PathNode.top()){//保证PathNode非空，因为下面会不断弹出元素，导致PathNode可能为空
				G.adjList[PathNode.top()].visited = false;
				PathNode.pop();
			}
			PathNode.push(top_allVert);
		}

		if (0 == G.adjList[PathNode.top()].outdegree){//出度为0，该条路径结束
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
功能：显示有向图中所有路径，起点：入度为零的节点，终点，出度为零的节点
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
		G.adjList[i].visited = false;//初始化，将所有结点置为未访问，并将入度为零的节点加入到栈allVertex
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
			while (!PathNode.empty()&&top_preNode != PathNode.top()){//保证PathNode非空，因为下面会不断弹出元素，导致PathNode可能为空
				G.adjList[PathNode.top()].visited = false;
				PathNode.pop();
			}
			PathNode.push(top_allVert);
		}

		if (0 == G.adjList[PathNode.top()].outdegree){//出度为0，该条路径结束
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
	
	//检查每个顶节点最早发生时间
	/*for (int i = 0; i < G.numVertex;i++){
		cout << "Vertex " << i << ": happenTime" << G.adjList[i].happenTime << "  lastHappenTime: " << G.adjList[i].lastHappenTime << endl;
	}*/

}