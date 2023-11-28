#include "Graph.h"

using namespace std;


Graph::Graph(string& name)
{
	ifstream file;
	file.open(name);
	if (file.is_open())
	{
		int from, to, weight, count = 0;
		unordered_set<int> nodes;
		while (!file.eof())
		{
			if (file >> from >> to >> weight)
			{
				nodes.insert(from);
				nodes.insert(to);
				Edge edge = Edge(from, to, weight);
				edges.insert({ ++count, edge });
			}
		}
		sizeGraph = nodes.size();
	}
	file.close();
}

Edge Graph::CreateEdge(int from, int to, int id)
{

	return Edge();
}

vector< vector<int> > Graph::CreateAdjMatrix()
{
	vector< vector<int> > adj_matrix;
	adj_matrix.clear();
	adj_matrix.resize(sizeGraph);
	for (int i = 0; i < sizeGraph; i++)
	{
		adj_matrix[i].resize(sizeGraph);
	}

	for (int i = 0; i < edges.size(); i++)
	{
		Edge& edge = edges[i + 1];
		adj_matrix[edge.from - 1][edge.to - 1] = edge.weight;
	}

	return adj_matrix;
}