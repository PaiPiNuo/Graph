#include "Dijkstra.h"

/*
Dijkstra�㷨����ⵥ�����㵽���������֮������·��
*/
void dij(GraphAdjList G,int v0){
	G.adjList[v0].solved = true;
	int *distance = new int[G.numVertex];
	vector<int> *path=new vector<int>[G.numVertex];
	//��ʼ��������V0��ֱ����ϵ�Ľڵ��ʼ����·����Ȩֵ��û��ֱ����ϵ�Ľڵ�����ʼ��Ϊ�����
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
	for (int i = 1; i < G.numVertex; i++){//��ѭ��ִ��n-1�μ��ɣ���ΪV0���Ѿ�ѡ��������ѡ������n-1�����㼴��		
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

		//��֤
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
Floyd�㷨���������֮������·��
*/
void Floyd(GraphAdjList G){
	vector<vector<stack<int>>> pathMatrix;
	pathMatrix.resize(G.numVertex);//������ͼ��·�������ַ�ռ�
	int **dist_Matrix=new int*[G.numVertex];
	//���ڽӾ��������ַ������ʼ����ʼֵΪ�����
	for (int i = 0; i < G.numVertex;i++){
		pathMatrix[i].resize(G.numVertex);
		dist_Matrix[i] = new int[G.numVertex];
		for (int j = 0; j < G.numVertex; j++){
			if (i == j){
				dist_Matrix[i][j] = 0;
				pathMatrix[i][j].push(i);//��ʼ����ĳ�ڵ��Լ����Լ���·��Ϊ������
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

	//��֤��̾�����-�ڽӾ���
	cout << "-----------check Distance--------------"<< endl;
	for (int i = 0; i < G.numVertex;i++){
		for (int j = 0; j < G.numVertex; j++){
			cout << dist_Matrix[i][j] << "  ";
		}
		cout << endl;
	}
	//��֤���·�����
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
��DAG�����޻�ͼ��ָ�����---->ָ���յ�ľ���,����ٶ�ֻ��һ������һ���յ�
��������+��̬�滮˼��
*/
void DP_bestPath(GraphAdjList G){
	stack<int> topoSort;
	vector<vector<int>> path;
	path.resize(G.numVertex);
	int i = 0,topStack;
	int *distance=new int[G.numVertex];//��¼����㵽ÿ����������̾���
	memset(distance, INFTY-1000, sizeof(int)*G.numVertex);//��ʼ�������ÿһ���ڵ�ľ���Ϊ�����
	distance[0] = 0;
	
	//�����Ϊ��Ľڵ��ջ
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
		if (0==G.adjList[topStack].outdegree)//�������Ԫ�ص����յ㣬��ô�������ѭ��
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