#include <stack>
#include <queue>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "my_KeyPath.h"

int My_EarliestTime(GraphAdjList &G,stack<int> &InverseTopo) {
	stack<int> No_Indegree;
	for (int i = 0; i < G.numVertex;i++) {
		if (G.adjList[i].indegree==0) {
			No_Indegree.push(i);
			G.adjList[i].happenTime = 0;
		}
	}
	EdgeNode *e;
	int IndexTmp;
	while (!No_Indegree.empty()) {
		IndexTmp = No_Indegree.top();
		No_Indegree.pop();
		InverseTopo.push(IndexTmp);
		e = G.adjList[IndexTmp].firstEdge;
		while (e!=NULL) {
			if (--G.adjList[e->adjvex].indegree==0) {
				No_Indegree.push(e->adjvex);
			}
			if (G.adjList[e->adjvex].happenTime < (e->valueEdge + G.adjList[IndexTmp].happenTime)) {
				G.adjList[e->adjvex].happenTime = e->valueEdge + G.adjList[IndexTmp].happenTime;
			}
			e = e->next;
		}
	}
	cout << "The Least Time of this Project is: " << G.adjList[IndexTmp].happenTime << endl;

	/*for (int i = 0; i < G.numVertex; i++) {
		cout << G.adjList[i].data << "  " << G.adjList[i].happenTime << endl;
	}*/
	return G.adjList[IndexTmp].happenTime;
}

void My_SlowliestTime(GraphAdjList &G) {
	stack<int> InverseTopo;
	int TotalLeastTime=My_EarliestTime(G, InverseTopo);
	for (int i = 0; i < G.numVertex; i++) {
		G.adjList[i].lastHappenTime = TotalLeastTime;
	}
	EdgeNode *e;
	while (!InverseTopo.empty()) {
		int IndexTmp = InverseTopo.top();
		InverseTopo.pop();
		e = G.adjList[IndexTmp].firstEdge;
		while (e!=NULL) {
			if (G.adjList[IndexTmp].lastHappenTime>(G.adjList[e->adjvex].lastHappenTime-e->valueEdge)) {
				G.adjList[IndexTmp].lastHappenTime = G.adjList[e->adjvex].lastHappenTime - e->valueEdge;
			}
			e = e->next;
		}
	}
	/*for (int i = 0; i < G.numVertex; i++) {
		cout << G.adjList[i].data << "  " << G.adjList[i].lastHappenTime << endl;
	}*/
}

//Topo Sort
//one start point,one end point
void showAllPath(GraphAdjList G, int v0) {
	queue<vector<int>> PathAll;
	EdgeNode *e = G.adjList[v0].firstEdge;
	while (e != NULL) {
		vector<int> tmp;
		tmp.push_back(v0);
		tmp.push_back(e->adjvex);
		e = e->next;
		PathAll.push(tmp);
	}
	bool endFlag = false;
	while (!endFlag) {
		if (G.adjList[PathAll.front().back()].outdegree == 0) {
			endFlag = true;
			break;
		}
		vector<int> tmp;
		tmp = PathAll.front();
		e = G.adjList[tmp.back()].firstEdge;
		
		PathAll.pop();
		while (e != NULL) {
			vector<int> tmp2 = tmp;
			tmp2.push_back(e->adjvex);
			PathAll.push(tmp2);
			e = e->next;
		}
	}

	while (!PathAll.empty()) {
		vector<int> tmp3 = PathAll.front();
		PathAll.pop();
		copy(tmp3.begin(), tmp3.end(),ostream_iterator<int>(cout,"  "));
		cout << endl;
	}
}

