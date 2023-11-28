#pragma once
#include "Utilites.h"
#include <unordered_map>

class Graph;

class Edge
{
	friend Graph;

public:
	Edge() {};

private:
	int from, to, weight;
	Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {};
};

class Graph
{
public:
	Graph(std::string& name);
	Edge CreateEdge(int from, int to, int id);

private:
	std::vector< std::vector<int> > CreateAdjMatrix();
	int sizeGraph;
	std::unordered_map<int, Edge> edges;
	
};



