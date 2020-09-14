#include "Node.h"
#include <string>
#include <fstream>
#include <map>

#define print(x) std::cout << x;

std::vector<Node> LoadGraphFromFile(std::string& path)
{
	std::ifstream file;
	std::vector<Node> nodes;
	
	file.open(path);
	if (file.is_open())
	{
		
		int v, e = 0;
		file >> v;
		file >> e;
		nodes.resize(v);

		int iv, nv;
		for (size_t i = 0; i < v; i++)
		{
			file >> iv; file >> nv;
			if (nodes[i].getValue() == nv)
			{

			}
		}
		
		file.close();
	}
	return nodes;
}

void printGraph(std::map<int, std::vector<int>> graph) {
	int sameIndex = 0;
	for (auto v = 0; v < graph.size(); v++) {
		for (auto e : graph[v]) {

		}
	}
}

int main()
{
	std::string path = "g1/g1_1.in";
	std::map<int,std::vector<int>> graph1 = LoadGraphFromFile(path);
	printGraph(graph1);
	return 0;
}