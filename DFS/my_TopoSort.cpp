#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "my_TopoSort.h"


using namespace std;
void my_TopoSort(GraphAdjList G) {
	stack<int> NoInputNode;
	vector<int> OutputNode;
	for (int i = 0; i < G.numVertex;i++) {
		if (G.adjList[i].indegree == 0) {
			NoInputNode.push(i);
		}
	}
	EdgeNode *e;
	while (!NoInputNode.empty()) {
		int IndexTmp = NoInputNode.top();
		NoInputNode.pop();
		OutputNode.push_back(G.adjList[IndexTmp].data);
		e = G.adjList[IndexTmp].firstEdge;
		while (e!=NULL) {
			if (--G.adjList[e->adjvex].indegree==0) {
				NoInputNode.push(e->adjvex);
			}
			e = e->next;
		}	
	}

	copy(OutputNode.begin(), OutputNode.end(),ostream_iterator<int>(cout,"  "));

}