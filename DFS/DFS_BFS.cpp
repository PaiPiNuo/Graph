#include <iostream>
#include <queue>
#include "DFS_BFS.h"

using namespace std;

void my_dfs(GraphAdjList &G, int v) {
	if (G.adjList[v].visited != true) {
		cout << G.adjList[v].data << "  ";
		G.adjList[v].visited = true;
	}
	EdgeNode *e = G.adjList[v].firstEdge;
	while (e != NULL) {
		if (G.adjList[e->adjvex].visited != true) 
			my_dfs(G, e->adjvex);
		e = e->next;
	}
}

void my_TravelDFS(GraphAdjList G) {
	for (int i = 0; i < G.numVertex;i++) {
		if (G.adjList[i].visited == false)
			my_dfs(G,i);
	}
	cout << endl;
}

void my_bfs(GraphAdjList &G, int v) {
	EdgeNode *e;
	queue<int> Que_Node;
	cout << G.adjList[v].data << "  ";
	G.adjList[v].visited = true;
	Que_Node.push(v);

	while (!Que_Node.empty()) {
		int tmpIndex = Que_Node.front();
		Que_Node.pop();
		e = G.adjList[tmpIndex].firstEdge;
		while (e != NULL) {
			if (G.adjList[e->adjvex].visited != true) {
				cout << G.adjList[e->adjvex].data << "  ";
				G.adjList[e->adjvex].visited = true;
				Que_Node.push(e->adjvex);
			}
			e = e->next;
		}
	}
}

void my_TravelBFS(GraphAdjList G) {
	for (int i = 0; i < G.numVertex; i++) {
		if (G.adjList[i].visited == false)
			my_bfs(G, i);
	}
	cout << endl;
}