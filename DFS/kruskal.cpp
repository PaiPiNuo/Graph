#include "kruskal.h"

using namespace std;

/*
功能：根据输入图G,邻接表形式存储的，
	 得到边的集合EdgeList，按照权值从小到大排列
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
	//验证边的集合是否正确
	/*int j = 0;
	while (j<EdgeList.size()){
		cout << EdgeList[j].littleNode << "  " << EdgeList[j].bigNode << "   " << EdgeList[j].edgeValue << endl;
		j++;
	}*/
	//需要按照边权值对边集合进行从小到大的排序,冒泡排序
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
	//验证排序后 边的集合是否正确
	unsigned int j = 0;
	while (j<EdgeList.size()){
		cout << EdgeList[j].littleNode << "  " << EdgeList[j].bigNode << "   " << EdgeList[j].edgeValue << endl;
		j++;
	}

}

/*
返回x的根节点，并进行路径压缩
*/
int find(int x,int* pre){//pre中存储着每个节点上一级节点号
	int r = x;//委托r去找根节点
	while (pre[r]!=r){//r的根节点不是自己
		r = pre[r];//那么继续往上一级寻找，直到找到根节点为止
	}
	//至此，r成为根节点
	//路径压缩，让每个节点都直接与根节点相连，避免查找根节点时需要多级查找才能找到
	int w = x, j;
	while (w!=r){
		j = pre[w];
		pre[w] = r;//把w的根节点改为r
		w = j;
	}
	return r;
}
/*
  判断两端点是否在同一棵树中，
  如果已经连通，就不用管了 ;如果不连通，就把它们所在的连通分支合并起,
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
kruskal算法生成最小生成树
input:EdgeList存储了权值从小到大的边的集合
      smallTree存储最小生成树的结果-边的集合
*/
void kruskal(GraphAdjList G, vector<Edge> &smallTree, vector<Edge> EdgeList){
	if (smallTree.size() != 0){//确保smallTree是空的，用来存储最小树结构
		cout << "Error,Please make sure EdgeList is Empty!" << endl;
		return;
	}
	
	int *pre = new int[G.numVertex];
	for (int j = 0; j < G.numVertex;j++){//初始化所有的节点根节点为自己
		pre[j] = j;
	}
	unsigned int i = 0;
	Edge smallEdge;
	while (smallTree.size()<(G.numVertex - 1)){
		smallEdge = EdgeList[i];
		//找到权值最小的边，判断该边的两个端点是否拥有同一个根节点，即是否在同一棵树中，如果不在，那么选择该边，并把两点加入到同一棵树中
		if (join(smallEdge.littleNode, smallEdge.bigNode, pre)){
			smallTree.push_back(smallEdge);
		}
		i++;//在边集合中依次向后搜索
	}

	//验证最小生成树
	cout << "smallTree.size：  " << smallTree.size() << endl;
	i = 0;
	while (i<smallTree.size()){
		cout << smallTree[i].littleNode << "  " << smallTree[i].bigNode << "   " << smallTree[i].edgeValue << endl;
		i++;
	}

}