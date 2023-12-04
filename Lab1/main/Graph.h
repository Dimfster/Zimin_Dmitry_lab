#pragma once
#include "Utilites.h"
#include <unordered_map>
#include <set>

class Graph;
class GTS;

class Edge
{
	friend Graph;
	friend GTS;
	friend std::ofstream& operator << (std::ofstream& file, const Edge& edge);
	friend std::ifstream& operator >> (std::ifstream& file, Edge& edge);
public:
	Edge() {};

private:
	int from, to, pipe;
	Edge(int from, int to, int pipe) : from(from), to(to), pipe(pipe) {};
};

class Graph
{
	friend GTS;
public:
	Graph() {};
	bool UncorrectNodes(int from, int to);
	void ViewConnections();
	void CreateEdge(int from, int to, int id);
	void DeleteEdge(int id);

	std::vector<int> TopologicalSort();

	friend std::ofstream& operator << (std::ofstream& out, const Graph& graph);

private:
	std::vector< std::vector<int> > CreateAdjMatrix(std::vector<std::vector<int>>& adj_matrix);

	bool DFS_Cycle(int node, std::vector<bool>& visited , int);
	void DFS_Sort(int v, std::vector<bool>& visited, std::vector<int>& nodes);

	bool Has—ycle();
	std::set<int> nodes;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<int>> adj_matrix;
	int sizeGraph;	
};



