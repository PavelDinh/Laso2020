#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>
# define INF 0x3f3f3f3f 
// iPair ==>  Integer Pair 
typedef std::pair<int, int> iPair;

class DijkstraGraph
{
private:
	int v;
	std::list <std::pair<int, int>>* adj;

public:
	DijkstraGraph(int v);

	// function to add an edge to graph 
	void addEdge(int u, int v, int w);

	// prints shortest path from s 
	void shortestPath(int s);
};

