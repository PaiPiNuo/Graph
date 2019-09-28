#include "Dijkstra.h"

/*
Dijkstra算法，求解单个顶点到其余各顶点之间的最短路径
*/
void dij(GraphAdjList G,int v0){
	G.adjList[v0].solved = true;
	int *distance = new int[G.numVertex];
	vector<int> *path=new vector<int>[G.numVertex];
	//初始化，将与V0有直接联系的节点初始化其路径和权值，没有直接联系的节点距离初始化为无穷大
	for (int i = 0; i < G.numVertex;i++){
		distance[i] = INFTY;
	}
	distance[v0] = 0;
	EdgeNode *tempEdge = G.adjList[v0].firstEdge;
	while (tempEdge != NULL){
		distance[tempEdge->adjvex] = tempEdge->valueEdge;
		path[tempEdge->adjvex].push_back(v0);
		path[tempEdge->adjvex].push_back(tempEdge->adjvex);
		tempEdge = tempEdge->next;
	}

	int minInd;
	int min = INFTY;
	for (int i = 1; i < G.numVertex; i++){//主循环执行n-1次即可，因为V0点已经选定，依次选定其余n-1个顶点即可		
		for (int j = 0; j < G.numVertex;j++){
			if (G.adjList[j].solved == false && distance[j] < min){					
				min = distance[j];
				minInd = j;
			}
		}
		G.adjList[minInd].solved = true;

		tempEdge = G.adjList[minInd].firstEdge;
		while (tempEdge!=NULL){
			if ((distance[minInd] + tempEdge->valueEdge)<distance[tempEdge->adjvex]){
				distance[tempEdge->adjvex] = distance[minInd] + tempEdge->valueEdge;
				path[tempEdge->adjvex] = path[minInd];
				path[tempEdge->adjvex].push_back(tempEdge->adjvex);
			}
			tempEdge = tempEdge->next;
		}
		min = INFTY;

		//验证
		cout << "------------------check-------------------" << endl;
		for (int k = 0; k < G.numVertex; k++){
			cout << "Dist " << k << " : " << distance[k] <<"  Path: ";
			for (int m = 0; m < path[k].size(); m++){
				cout << path[k][m] << "  ";
			}
			cout << endl;
		}		
	}

	delete[] distance;
	delete[] path;
}

/*
Floyd算法，求各顶点之间的最短路径
*/
void Floyd(GraphAdjList G){
	vector<vector<stack<int>>> pathMatrix;
	pathMatrix.resize(G.numVertex);//给整幅图的路径申请地址空间
	int **dist_Matrix=new int*[G.numVertex];
	//给邻接矩阵申请地址，并初始化初始值为无穷大
	for (int i = 0; i < G.numVertex;i++){
		pathMatrix[i].resize(G.numVertex);
		dist_Matrix[i] = new int[G.numVertex];
		for (int j = 0; j < G.numVertex; j++){
			if (i == j){
				dist_Matrix[i][j] = 0;
				pathMatrix[i][j].push(i);//初始化，某节点自己到自己的路径为：本身
			}
			else
				dist_Matrix[i][j] = INFTY;
		}
	}

	EdgeNode *tempEdge;
	for (int i = 0; i < G.numVertex;i++){
		tempEdge = G.adjList[i].firstEdge;
		while (tempEdge!=NULL){
			dist_Matrix[i][tempEdge->adjvex] = tempEdge->valueEdge;
			pathMatrix[i][tempEdge->adjvex].push(i);
			pathMatrix[i][tempEdge->adjvex].push(tempEdge->adjvex);
			tempEdge = tempEdge->next;
		}
	}
	/*cout << "-----------check Paths--------------" << endl;
	for (int i = 0; i < G.numVertex; i++){
		for (int j = 0; j < G.numVertex; j++){
			if (pathMatrix[i][j].empty()){
				cout << " * ";
			}
			else{
				cout << pathMatrix[i][j].top() <<"  ";
				pathMatrix[i][j].pop();
				while (!pathMatrix[i][j].empty()){
					cout << " <-- "<<pathMatrix[i][j].top();
					pathMatrix[i][j].pop();
				}
			}
		}
		cout << endl;
	}*/
	stack<int> tempPath,tempPath_Inverse;
	for (int k = 0; k < G.numVertex;k++){
		for (int i = 0; i < G.numVertex;i++){
			for (int j = 0; j < G.numVertex;j++){
				if (dist_Matrix[i][k] != INFTY && dist_Matrix[k][j] != INFTY && (dist_Matrix[i][k] + dist_Matrix[k][j])<dist_Matrix[i][j]){
					dist_Matrix[i][j] = dist_Matrix[i][k] + dist_Matrix[k][j];
					pathMatrix[i][j] = pathMatrix[i][k];
					tempPath = pathMatrix[k][j];
					while (!tempPath.empty()){
						tempPath_Inverse.push(tempPath.top());
						tempPath.pop();
					}
					tempPath_Inverse.pop();
					while (!tempPath_Inverse.empty()){
						pathMatrix[i][j].push(tempPath_Inverse.top());
						tempPath_Inverse.pop();
					}
					//cout << "dist_Matrix[" << i << "][" << j << "]: " << dist_Matrix[i][j] << endl;
				}
			}
		}
	}

	//验证最短距离结果-邻接矩阵
	cout << "-----------check Distance--------------"<< endl;
	for (int i = 0; i < G.numVertex;i++){
		for (int j = 0; j < G.numVertex; j++){
			cout << dist_Matrix[i][j] << "  ";
		}
		cout << endl;
	}
	//验证最短路径结果
	cout << "-----------check Paths--------------" << endl;
	for (int i = 0; i < G.numVertex; i++){
		for (int j = 0; j < G.numVertex; j++){
			if (pathMatrix[i][j].empty()){
				cout << " * ";
			}
			else{
				cout << pathMatrix[i][j].top() ;
				pathMatrix[i][j].pop();
				while (!pathMatrix[i][j].empty()){
					cout << " <-- " << pathMatrix[i][j].top();
					pathMatrix[i][j].pop();
				}
			}
			cout << "     ";
		}
		cout << endl;
	}


	for (int i = 0; i < G.numVertex;i++){
		delete[] dist_Matrix[i];
	}
	delete[] dist_Matrix;
}

/*
求DAG有向无环图中指定起点---->指定终点的距离,这里假定只有一个起点和一个终点
拓扑排序+动态规划思想
*/
void DP_bestPath(GraphAdjList G){
	stack<int> topoSort;
	vector<vector<int>> path;
	path.resize(G.numVertex);
	int i = 0,topStack;
	int *distance=new int[G.numVertex];//记录从起点到每个其余点的最短距离
	memset(distance, INFTY-1000, sizeof(int)*G.numVertex);//初始化起点至每一个节点的距离为无穷大
	distance[0] = 0;
	
	//将入度为零的节点进栈
	while (i < G.numVertex){
		if (0 == G.adjList[i].indegree){
			topoSort.push(i);
			path[0].push_back(i);
			break;
		}
		i++;
	}
	if (topoSort.empty()){
		cout <<"Error:There is no a Node with 0 indegree!" << endl;
		return;
	}
	
	EdgeNode* tempEdge;
	while (!topoSort.empty()){
		topStack = topoSort.top();
		if (0==G.adjList[topStack].outdegree)//如果弹出元素到了终点，那么结束这个循环
			break;
		
		topoSort.pop();
		tempEdge = G.adjList[topStack].firstEdge;
		while (tempEdge!=NULL){
			G.adjList[tempEdge->adjvex].indegree--;
			if (0 == G.adjList[tempEdge->adjvex].indegree)
				topoSort.push(tempEdge->adjvex);
			//-----------
			if (distance[tempEdge->adjvex]>(distance[topStack] + tempEdge->valueEdge)){
				distance[tempEdge->adjvex] = distance[topStack] + tempEdge->valueEdge;
				path[tempEdge->adjvex] = path[topStack];
				path[tempEdge->adjvex].push_back(tempEdge->adjvex);
			}
			//-----------
			tempEdge = tempEdge->next;
		}
	}
	i = 0;
	int j = 0;
	while (i<G.numVertex){
		cout <<i<<" :  "<< distance[i]<<"  ";
		j = 0;
		while (j<path[i].size()){
			cout << path[i][j]<<"  " ;
			j++;
		}
		cout << endl;
		i++;
	}

	delete[] distance;
}