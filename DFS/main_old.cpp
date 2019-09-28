//#include <iostream>
//#include <vector>
//using namespace std;
//
//struct adjlink{
//	int data;
//	adjlink *next;
//};
//
//void gen_graph(int num, vector<int> &graphData, int** relationGraph){
//	/*用邻接矩阵的形式先构建图
//	*/
//	int input;
//	cout << "Please input the Graph data in turn:"<<endl;
//	for (int i = 0; i < num;i++){
//		cin >> input;
//		graphData.push_back(input);
//	}
//	cout << "The Graph data has been input successfully!" << endl;
//	cout << "Please input the relationship of the graph data:"<< endl;
//	//int relationGraph[graphData.size][graphData.size];
//	for (int i = 0; i < graphData.size();i++){
//		for (int j = 0; j < graphData.size(); j++){
//			cin >> input;
//			relationGraph[i][j] = input;
//		}
//	}
//	cout << "The relationship of Graph data has been input!"<< endl;
//
//}
//
//class graphTable{
//	public:
//		graphTable(int num, vector<int> graphData, int** relationGraph);
//		~graphTable();
//	private:
//		vector<adjlink> vertex;
//		int numVertex;
//};
//graphTable::graphTable(int num, vector<int> graphData, int** relationGraph){
//
//}
//
//int main(){
//	vector<int> graphData;
//
//	int numData;
//	cout << "Please input the number of the graph:"<< endl;
//	cin >> numData;
//	/*用指针的方式开辟未知大小的二维数组空间，注意通过这种方式开辟的数组内存不连续，注意访问时越界
//	array2D[i * width + j]这样的访问就不要使用了，容易造成访问越界
//	*/
//	int **relationGraph = new int*[numData];
//	for (int i = 0; i < numData;i++){
//		relationGraph[i] = new int[numData];
//	}
//
//	gen_graph(numData, graphData, relationGraph);
//	/*for (int i = 0; i < numData;i++){
//		cout << graphData[i]<< endl;
//	}*/
//
//	system("pause");
//	return 0;
//}