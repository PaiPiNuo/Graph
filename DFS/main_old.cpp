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
//	/*���ڽӾ������ʽ�ȹ���ͼ
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
//	/*��ָ��ķ�ʽ����δ֪��С�Ķ�ά����ռ䣬ע��ͨ�����ַ�ʽ���ٵ������ڴ治������ע�����ʱԽ��
//	array2D[i * width + j]�����ķ��ʾͲ�Ҫʹ���ˣ�������ɷ���Խ��
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