#include <iostream>
#include <map>
#include <vector>
#include <fstream>

#define print(x) std::cout << x;
using namespace std;

map<int,vector<int>> LoadGraphFromFile(std::string& path)
{
	ifstream file;
	map<int, vector<int>> graph;

	file.open(path);
	if (file.is_open())
	{
		int v, e = 0;
		file >> v;
		file >> e;
		graph.get_allocator().allocate(v);

		int iv, nv;
		for (size_t i = 0; i < e; i++)
		{
			file >> iv; file >> nv;
			graph[iv].push_back(nv);
			graph[nv].push_back(iv);
		}
		file.close();
	}
	return graph;
}

void printGraph(map<int,vector<int>> graph) {
	
	map<int, vector<int>>::iterator it;
	for (it = graph.begin(); it != graph.end(); ++it)
	{
		cout << it->first << " : ";
		for (auto e : it->second)
		{
			 cout << e << " ";
		}
		cout << "\n";
	}
}

int main()
{
	//std::string path_g1 = "Day1/Task1/g1_1.in";
	//map<int, vector<int>> graph1 = LoadGraphFromFile(path_g1);
	//printGraph(graph1);

	std::string path_g2 = "Day1/Task2/g2_1.in";
	map<int, vector<int>> graph2 = LoadGraphFromFile(path_g2);
	printGraph(graph2);

	system("PAUSE");
	return 0;
}