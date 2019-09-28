#include "main.h"
#include "prim.h"
#include "kruskal.h"
#include "TopoSort.h"
#include "CriticalPath.h"
#include "Dijkstra.h"
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
	checkGraph(G);
	//cout << "Starting visitting the Graph in depth first search:"<< endl;
	//Travel_DFS(G);//��ȱ���
	//Travel_BFS(G);//��ȱ���
	//cout << "The number of Edges in Graph is: " << num_Edge /2<< endl;
	//Prim(G, 0);//��С������
	/*Kruskal��С������*/
	/*vector<Edge> EdgeList;
	vector<Edge> smallTree;
	init_EdgeSet(G, EdgeList);
	kruskal(G, smallTree, EdgeList);*/
	//topSort(G);//��������
	//criticalPath(G);
	//dij(G, 0);//�ӵ������㵽����������·��
	DP_bestPath(G);
	//Floyd(G);//�����������·��
	delete[] G.adjList;
	cout << "HelloWorld!"<< endl;
	system("pause");
	return 0;
}
/*
���ڽӱ����ʽ����ͼ
�����ʽ���Ȱ�˳����������ڵ��ֵ����1 8 8 1 1 3 1
         ���������붥�ڵ����ı߽ڵ��Լ�Ȩֵ����Node0:1(�߽ڵ�) 12(Ȩֵ) 4(�߽ڵ�) 9(Ȩֵ) 5(�߽ڵ�) 9(Ȩֵ) -1
		                                    Node1:0 12 -1
         -1�ǽ�����־
*/
void CreateGraph(GraphAdjList &G){
	cout << "Please input node value in turn:" << endl;
	for (int i = 0; i < G.numVertex; i++){
		cin >> G.adjList[i].data;
		G.adjList[i].firstEdge = NULL;
		G.adjList[i].visited = false;
	}
	cout << "Please input relationship in turn(\"-1\" means no next Node):" << endl;

	int tempInput;
	EdgeNode *e, *p;
	for (int i = 0; i < G.numVertex; i++){
		cout << "Relationship of the node " << i << " :" << endl;
		cin >> tempInput;
		while (tempInput != -1){
			if (G.adjList[i].firstEdge == NULL){
				e = new EdgeNode;
				e->adjvex = tempInput;
				cin >> tempInput;
				e->valueEdge = tempInput;
				G.adjList[i].firstEdge = e;
				e->next = NULL;
				cin >> tempInput;
			}
			else{
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
void CreateGraph_Edge(GraphAdjList &G){
	cout << "Please input Node VALUE VALUE VALUE  in turn:" << endl;
	for (int i = 0; i < G.numVertex; i++){
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
	int firstNode,SecondNode,edgeValue;
	EdgeNode *e, *p;
	for (int i = 0; i < G.numEdge; i++){
		cin >> firstNode;
		cin >> SecondNode;
		if (1==G.networkFlag)
			cin >> edgeValue;
		else
			edgeValue=0;
		
		if (G.adjList[firstNode].firstEdge == NULL){
			e = new EdgeNode;
			e->adjvex = SecondNode;
			e->valueEdge = edgeValue;
			e->next = NULL;
			G.adjList[firstNode].firstEdge = e;
		}
		else{
			e = G.adjList[firstNode].firstEdge;
			while (e->next != NULL)
				e = e->next;
			p = new EdgeNode;
			p->adjvex = SecondNode;
			p->valueEdge = edgeValue;
			p->next = NULL;
			e->next = p;
		}

		if (G.directedFlag == 1){
			G.adjList[SecondNode].preEdge.push(firstNode);//��ǰ���ڵ��ż��뵽preEdgeջ��
			G.adjList[firstNode].outdegree++;//�ö��ڵ���ȼ�1��
			G.adjList[SecondNode].indegree++;//�ö��ڵ���ȼ�1��ֻ��������ͼ�в����ۡ���ȡ��������ȡ�
		}

		if (G.directedFlag==0){
			if (G.adjList[SecondNode].firstEdge == NULL){
				e = new EdgeNode;
				e->adjvex = firstNode;
				e->valueEdge = edgeValue;
				e->next = NULL;
				G.adjList[SecondNode].firstEdge = e;
			}
			else{
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
void checkGraph(GraphAdjList G){
	for (int i = 0; i < G.numVertex;i++){
		cout << "Node:"<<i<< endl;
		if (G.directedFlag == 1){//���������ͼ����ô����������
			cout << "The Indegree : " << G.adjList[i].indegree << endl;
			cout << "The Outdegree : " << G.adjList[i].outdegree << endl;
		}
		cout << "PreNode: " ;
		while (!G.adjList[i].preEdge.empty()){//������ڵ��ǰ���ڵ���
			cout << G.adjList[i].preEdge.top() << " <-- ";
			G.adjList[i].preEdge.pop();
		}
		cout << i << endl;

		EdgeNode* edgeNode = G.adjList[i].firstEdge;
		cout << "Relationship: " << i;
		while(edgeNode!=NULL){			
			if (1 == G.networkFlag)
				cout << " --> "<<edgeNode->adjvex << "(value: " << edgeNode->valueEdge <<")";
			else
				cout << " --> " << edgeNode->adjvex;
			edgeNode = edgeNode->next;
		}
		cout << endl;
	}
}

/*
��ȱ����㷨
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
��ȱ����㷨
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