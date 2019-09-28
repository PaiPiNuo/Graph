#include "kruskal.h"

using namespace std;

/*
���ܣ���������ͼG,�ڽӱ���ʽ�洢�ģ�
	 �õ��ߵļ���EdgeList������Ȩֵ��С��������
*/
void init_EdgeSet(GraphAdjList G, vector<Edge> &EdgeList){	
	int i = 0;
	while (i<G.numVertex){
		EdgeNode *edgeW = G.adjList[i].firstEdge;
		while (edgeW != NULL){
			if (i<edgeW->adjvex){
				Edge *Ed = new Edge;
				Ed->littleNode = i;
				Ed->bigNode = edgeW->adjvex;
				Ed->edgeValue = edgeW->valueEdge;
				EdgeList.push_back(*Ed);
			}
			edgeW = edgeW->next;
		}
		i++;
	}
	//��֤�ߵļ����Ƿ���ȷ
	/*int j = 0;
	while (j<EdgeList.size()){
		cout << EdgeList[j].littleNode << "  " << EdgeList[j].bigNode << "   " << EdgeList[j].edgeValue << endl;
		j++;
	}*/
	//��Ҫ���ձ�Ȩֵ�Ա߼��Ͻ��д�С���������,ð������
	Edge tempEdge;
	for (unsigned int i = 0; i < EdgeList.size(); i++){
		for (unsigned int j = i + 1; j<EdgeList.size(); j++){
			if (EdgeList[j].edgeValue < EdgeList[i].edgeValue){
				tempEdge = EdgeList[i];
				EdgeList[i] = EdgeList[j];
				EdgeList[j] = tempEdge;
			}
		}
	}
	//��֤����� �ߵļ����Ƿ���ȷ
	unsigned int j = 0;
	while (j<EdgeList.size()){
		cout << EdgeList[j].littleNode << "  " << EdgeList[j].bigNode << "   " << EdgeList[j].edgeValue << endl;
		j++;
	}

}

/*
����x�ĸ��ڵ㣬������·��ѹ��
*/
int find(int x,int* pre){//pre�д洢��ÿ���ڵ���һ���ڵ��
	int r = x;//ί��rȥ�Ҹ��ڵ�
	while (pre[r]!=r){//r�ĸ��ڵ㲻���Լ�
		r = pre[r];//��ô��������һ��Ѱ�ң�ֱ���ҵ����ڵ�Ϊֹ
	}
	//���ˣ�r��Ϊ���ڵ�
	//·��ѹ������ÿ���ڵ㶼ֱ������ڵ�������������Ҹ��ڵ�ʱ��Ҫ�༶���Ҳ����ҵ�
	int w = x, j;
	while (w!=r){
		j = pre[w];
		pre[w] = r;//��w�ĸ��ڵ��Ϊr
		w = j;
	}
	return r;
}
/*
  �ж����˵��Ƿ���ͬһ�����У�
  ����Ѿ���ͨ���Ͳ��ù��� ;�������ͨ���Ͱ��������ڵ���ͨ��֧�ϲ���,
*/
bool join(int x,int y,int* pre){
	int rootX = find(x,pre);
	int rootY = find(y,pre);
	if (rootX != rootY){
		pre[rootX] = rootY;
		return true;
	}
	return false;
}

/*
kruskal�㷨������С������
input:EdgeList�洢��Ȩֵ��С����ıߵļ���
      smallTree�洢��С�������Ľ��-�ߵļ���
*/
void kruskal(GraphAdjList G, vector<Edge> &smallTree, vector<Edge> EdgeList){
	if (smallTree.size() != 0){//ȷ��smallTree�ǿյģ������洢��С���ṹ
		cout << "Error,Please make sure EdgeList is Empty!" << endl;
		return;
	}
	
	int *pre = new int[G.numVertex];
	for (int j = 0; j < G.numVertex;j++){//��ʼ�����еĽڵ���ڵ�Ϊ�Լ�
		pre[j] = j;
	}
	unsigned int i = 0;
	Edge smallEdge;
	while (smallTree.size()<(G.numVertex - 1)){
		smallEdge = EdgeList[i];
		//�ҵ�Ȩֵ��С�ıߣ��жϸñߵ������˵��Ƿ�ӵ��ͬһ�����ڵ㣬���Ƿ���ͬһ�����У�������ڣ���ôѡ��ñߣ�����������뵽ͬһ������
		if (join(smallEdge.littleNode, smallEdge.bigNode, pre)){
			smallTree.push_back(smallEdge);
		}
		i++;//�ڱ߼����������������
	}

	//��֤��С������
	cout << "smallTree.size��  " << smallTree.size() << endl;
	i = 0;
	while (i<smallTree.size()){
		cout << smallTree[i].littleNode << "  " << smallTree[i].bigNode << "   " << smallTree[i].edgeValue << endl;
		i++;
	}

}