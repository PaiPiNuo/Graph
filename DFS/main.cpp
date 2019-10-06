#include "main.h"
#include "prim.h"
#include "kruskal.h"
#include "TopoSort.h"
#include "CriticalPath.h"
#include "Dijkstra.h"
#include "ConstructGraph.h"
#include "DFS_BFS.h"

using namespace std;

int num_Edge=0;

int main(){
	GraphAdjList G;
	int input;
	cout << "Please input the number of Nodes:"<< endl;
	cin >> G.numVertex;
	G.adjList = new AdjList[G.numVertex];
	cout << "Please input the number of Edges:" << endl;
	cin >> G.numEdge;
	cout << "Please choose the type of the creating Graph:Directed(Press 1)  , Undirected(Press 0)" << endl;
	cin >> G.directedFlag;
	cout << "Is it a Network with Edge Value?Network(Press 1)  ,Not Network(Press 0)"<< endl;
	cin >> G.networkFlag;

	CreateGraph_Edge(G);
	//checkGraph(G);
	//my_TravelDFS(G);
	my_TravelBFS(G);
	//cout << "Starting visitting the Graph in depth first search:"<< endl;
	//Travel_DFS(G);//深度遍历
	//Travel_BFS(G);//广度遍历
	//cout << "The number of Edges in Graph is: " << num_Edge /2<< endl;
	//Prim(G, 0);//最小生成树
	/*Kruskal最小生成树*/
	/*vector<Edge> EdgeList;
	vector<Edge> smallTree;
	init_EdgeSet(G, EdgeList);
	kruskal(G, smallTree, EdgeList);*/
	//topSort(G);//拓扑排序
	//criticalPath(G);
	//dij(G, 0);//从单个顶点到各顶点的最短路径
	//DP_bestPath(G);
	//Floyd(G);//各顶点间的最短路径
	delete[] G.adjList;
	
	cout << "HelloWorld!"<< endl;
	system("pause");
	return 0;
}

/*
深度遍历算法
*/
void dfs(GraphAdjList &G, int v){
	cout << "visiting:" << G.adjList[v].data << endl;
	G.adjList[v].visited = true;

	EdgeNode *w = G.adjList[v].firstEdge;
	while (w != NULL){
		num_Edge++;
		if (G.adjList[w->adjvex].visited == false)
			dfs(G, w->adjvex);
		w = w->next;
	}
}

void Travel_DFS(GraphAdjList G){
	int num_Connect = 0;
	for (int i = 0; i < G.numVertex; i++){
		G.adjList[i].visited = false;
	}
	for (int i = 0; i < G.numVertex; i++){
		if (G.adjList[i].visited == false){
			dfs(G, i);
			num_Connect++;
		}
	}
	cout << "The number of connection branch is: " << num_Connect << endl;
}
//-----------------------------------------------------------------
/*
广度遍历算法
*/
void bfs(GraphAdjList &G, int v){
	queue<AdjList> Q;
	AdjList nodeAdj;
	EdgeNode* w;
	cout << "visiting:" << G.adjList[v].data << endl;
	G.adjList[v].visited = true;
	Q.push(G.adjList[v]);
	while (Q.empty() != true){
		nodeAdj = Q.front();
		Q.pop();
		w = nodeAdj.firstEdge;
		while (w != NULL){
			if (G.adjList[w->adjvex].visited == false){
				cout << "visiting:" << G.adjList[w->adjvex].data << endl;
				G.adjList[w->adjvex].visited = true;
				Q.push(G.adjList[w->adjvex]);
			}
			w = w->next;
		}
	}
}
void Travel_BFS(GraphAdjList G){
	for (int i = 0; i < G.numVertex; i++){
		G.adjList[i].visited = false;
	}
	for (int i = 0; i < G.numVertex; i++){
		if (G.adjList[i].visited == false)
			bfs(G, i);
	}
}
//-----------------------------------------------------------