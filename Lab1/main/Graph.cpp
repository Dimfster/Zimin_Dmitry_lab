#include "Graph.h"
#include <stack>
using namespace std;

// ��� �����
ofstream& operator << (std::ofstream& file, const Edge& edge) {
	if (file.is_open()) {
		file << edge.pipe << " ";
		file << edge.from << " ";
		file << edge.to << std::endl;
	}
	return file;
}
ifstream& operator >> (std::ifstream& file, Edge& edge) {
	if (file.is_open()) {
		file >> edge.pipe;
		file >> edge.from;
		file >> edge.to;
	}
	return file;
}

// ��� ����
bool Graph::UncorrectNodes(int from, int to)
{
	if (nodes.contains(from) && nodes.contains(to)) {
		cout << "������� ��� �������������!" << endl; return true;
	}
	else if (from == to) {
		cout << "������ ��������� ����� � ��� �� �������!" << endl; return true;
	}
	else { return false; }
}

void Graph::CreateEdge(int from, int to, int id){
	if (UncorrectNodes(from, to)) { return; }
	if (edges.contains(id)){ 
		cout << "������� ��� ����� ��� �������������!" << endl; return;
	}
	Edge edge = Edge(from,to, id);
	edges.insert({ id, edge });
	nodes.insert(from);
	nodes.insert(to);
	sizeGraph = edges.size();
	cout << endl << "����� �������!" << endl;
	return;
}

void Graph::ViewConnections()
{
	if (edges.empty()) { cout << "��� ������!" << endl; }
	for (auto& edge : edges) {
		cout << "�����: ����� " << edge.second.pipe << " ��������� ������� " << edge.second.from << " -> " << edge.second.to << endl;
	}
}

void Graph::DeleteEdge(int id) { 
	if (edges.contains(id)) { 
		edges.erase(id); 
		cout << endl << "����� �������!" << endl;
	}
}

vector< vector<int> > Graph::CreateAdjMatrix(std::vector<std::vector<int>>& adj_matrix)
{
	sizeGraph = edges.size();
	adj_matrix.resize(sizeGraph, vector<int>(sizeGraph, 0.0));

	for (int i = 0; i < edges.size(); i++)
	{
		Edge& edge = edges[i + 1];
		adj_matrix[edge.from - 1][edge.to - 1] = edge.pipe;
	}
	return adj_matrix;
}

bool Graph::DFS_Cycle(int node, vector<bool>& visited, int parent = -1) {
	visited[node] = true;

	for (int i = 0; i < sizeGraph; ++i) {
		if (adj_matrix[node][i] && !visited[i]) {
			DFS_Cycle(node, visited, i);
		}
		else if (node != parent) {
			return true;
		}
	}
	return false;
}

bool Graph::Has�ycle() {
	vector<bool> visited(sizeGraph, false);

	for (int i = 0; i < sizeGraph; ++i) {
		if (!visited[i]) {
			if (DFS_Cycle(i, visited)) { return true; }
		}
	}
}

void Graph::DFS_Sort(int node, vector<bool>& visited, vector<int>& nodes) {
	// �������� ������� ������� ��� ����������
	visited[node] = true;

	// ���������� ������� ��� ������� �������
	for (int i = 0; i < sizeGraph; ++i) {
		if (adj_matrix[node][i] && !visited[i]) {
			DFS_Sort(node, visited, nodes);
		}
	}
	// �������� ������� ������� � ������
	nodes.push_back(node);
}

vector<int> Graph::TopologicalSort(){
	CreateAdjMatrix(adj_matrix);
	if (edges.empty()) {
		cout << endl << "� ����� ��� ����. �������������� ���������� ����������" << endl;
		adj_matrix.clear();
		return vector<int>();
	}
	else if (Has�ycle()) {
		cout << endl << "� ����� ���� ����. �������������� ���������� ����������" << endl;
		adj_matrix.clear();
		return vector<int>();
	}
	
	vector<bool> visited(sizeGraph, false);
	vector<int> result;

	for (int i = 0; i < sizeGraph; ++i) {
		if (!visited[i]) {
			DFS_Sort(i, visited, result);
		}
	}
	reverse(result.begin(), result.end());
	adj_matrix.clear();
	return result;
}


ofstream& operator << (ofstream& file, const Graph& graph) {
	if (file.is_open()) {
		for (auto& edge : graph.edges) { file << edge.second; }
	}
	return file;
}