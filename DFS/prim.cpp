#include "prim.h"

//判断顶点v与顶点i之间是否有连接
int haveEdge(AdjList v0,int v){
	if (v0.firstEdge == NULL)
		return 0;
	else{
		EdgeNode *w = v0.firstEdge;
		while (w!=NULL){
			if (w->adjvex == v)
				return w->valueEdge;
			w = w->next;
		}
		return 0;
	}
}

//默认从顶点0开始
void Init_MinEdges(GraphAdjList &G, MinEdge* MinEdges, int v){
	cout <<"The starting Node is: "<<v << endl;
	for (int i = 0; i <G.numVertex ;i++){
		int valueEdge = haveEdge(G.adjList[v], i );
		if (valueEdge){
			MinEdges[i].v = v;
			MinEdges[i].valueEdge = valueEdge;
			cout << "MinEdges[" << i << "]  " << MinEdges[i].v << "  " << MinEdges[i].valueEdge << endl;
		}
		else{
			MinEdges[i].valueEdge = INFTY;
			cout << "MinEdges[" << i << "]  "<< MinEdges[i].valueEdge << endl;
		}
	}
}

//从候选边集中选出最短的顶点
int Get_MinEdge(GraphAdjList &G, MinEdge* MinEdges, vector<int> &SelectedNode){
	bool selectedFlag=false;
	int ind = 0, MMin = INFTY,k;
	for (int i = 0; i < G.numVertex;i++){
		selectedFlag = false;
		ind = 0;
		//确认i点是否是未选点
		while (ind < SelectedNode.size()){
			if (i == SelectedNode[ind]){//默认从0节点开始
				selectedFlag = true;
				break;
			}
			ind++;
		}

		if (selectedFlag==false&&MinEdges[i].valueEdge<MMin){//i是未选点
			k = i;
			MMin = MinEdges[i].valueEdge;
		}
	}
	SelectedNode.push_back(k);//把刚得到的K点加入已选点集合
	cout << "The Selected Node is: " << k << "   His old brother is: " << MinEdges [k].v<< endl;

	return k;
}

//更新候选边集合
void update_MinEdges(GraphAdjList &G, MinEdge* MinEdges, int k, vector<int> SelectedNode){
	bool selectedFlag = false;
	int ind = 0;
	for (int i = 0; i < G.numVertex;i++){
		selectedFlag = false;
		ind = 0;
		//确认i点是否是未选点
		while (ind < SelectedNode.size()){
			if (i == SelectedNode[ind]){//默认从0节点开始
				selectedFlag = true;
				break;
			}
			ind++;
		}
		if (selectedFlag==false){//i是未选点
			int valueEdge = haveEdge(G.adjList[k], i);
			if (valueEdge&&valueEdge<MinEdges[i].valueEdge){
				MinEdges[i].valueEdge = valueEdge;
				MinEdges[i].v = k;
			}
		}
	}
}

void Prim(GraphAdjList &G, int v0){
	vector<int> SelectedNode;//存储已选顶点的集合
	int k;
	SelectedNode.push_back(v0);
	MinEdge *MinEdges = new MinEdge[G.numVertex];
	Init_MinEdges(G, MinEdges, v0);
	for (int i = 0; i < (G.numVertex-1);i++){
		k = Get_MinEdge(G, MinEdges, SelectedNode);
		update_MinEdges(G, MinEdges, k, SelectedNode);
	}

}
