#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <stack>
#include <queue>
#include "BinaryHeap.h"

#define print(x) std::cout << x;
using namespace std;

map<int, vector<int>> LoadGraphFromFile(std::string& path)
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

void printGraph(map<int, vector<int>> graph) {

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

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void queue_example()
{
	ifstream file("Day2/seq.txt");

	if (file.is_open())
	{
		queue<int> s;
		string com, nextCom;
		while (file >> com)
		{
			int v = 0;
			if (com == "insert")
			{
				file >> nextCom;
				if (is_number(nextCom)) {
					v = std::stoi(nextCom);
					s.push(v);
					std::cout << "Top value of a stack is: " << s.back() << "\n";
				}
			}
			else if (com == "remove")
			{
				std::cout << "Top value of a stack " << s.back() << " was removed.\n";
				s.pop();
			}
		}
	}
}

void stack_example()
{
	ifstream file("Day2/seq.txt");

	if (file.is_open())
	{
		stack<int> s;
		string com, nextCom;
		while (file >> com)
		{
			int v = 0;
			if (com == "insert")
			{
				file >> nextCom;
				if (is_number(nextCom)) {
					v = std::stoi(nextCom);
					s.push(v);
					std::cout << "Top value of a stack is: " << s.top() << "\n";
				}
			}
			else if (com == "remove")
			{
				std::cout << "Top value of a stack " << s.top() << " was removed.\n";
				s.pop();
			}
		}
	}
}

void bfs(string path, map<int, vector<int>> graph, int s, int v)
{
	// Load graph
	graph = LoadGraphFromFile(path);
	size_t size = graph.size();
	vector<bool> visited(size);
	vector<int> values(size);

	for (size_t i = 0; i < size; i++)
	{
		visited[i] = false;
		values[i] = INT_MAX;
	}

	queue<int> Q;
	Q.push(s);

	visited[Q.front()] = true;
	values[Q.front()] = 0;

	while (!Q.empty())
	{
		int temp = Q.front();
		for (int val : graph[temp])
		{
			if (visited[val] == false)
			{
				Q.push(val);
				visited[val] = true;
				values[val] = values[temp] + 1;
			}
		}
		Q.pop();
	}

	if (v != -1)
	{
		cout << v << " : " << values[v] << "\n";
	}
	else
	{
		for (size_t i = 0; i < values.size(); i++)
		{
			if (values[i] != INT_MAX)
				cout << i << ": " << values[i] << "\n";
		}
	}
}

void dfs(string path, map<int, vector<int>> graph, int s, int v)
{
	// Load graph
	graph = LoadGraphFromFile(path);
	size_t size = graph.size();
	vector<bool> visited(size);
	vector<int> values(size);

	for (size_t i = 0; i < size; i++)
	{
		visited[i] = false;
		values[i] = INT_MAX;
	}

	stack<int> S;
	S.push(s);
	visited[S.top()] = true;
	values[S.top()] = 0;

	while (!S.empty())
	{
		int temp = S.top();
		S.pop();
		for (int val : graph[temp])
		{
			if (visited[val] == false)
			{
				S.push(val);
				visited[val] = true;
				values[val] = values[temp] + 1;
			}
		}
	}

	if (v != -1)
	{
		cout << v << " : " << values[v] << "\n";
	}
	else
	{
		for (size_t i = 0; i < values.size(); i++)
		{
			if (values[i] != INT_MAX)
				cout << i << ": " << values[i] << "\n";
		}
	}
}

vector<bool> create_false_vector(int size)
{
	vector<bool> falseVec(size);
	for (bool b : falseVec)
	{
		b = false;
	}
	return falseVec;
}

void recursive_dfs(map<int, vector<int>>& graph, int s, vector<bool>& visited)
{
	visited[s] = true;

	for (int val : graph[s])
	{
		if (visited[val] == false)
			recursive_dfs(graph, val, visited);
	}
}

int main()
{
	/////////////////////////////////// DAY 1 ////////////////////////////////////////

	//std::string path_g1 = "Day1/Task1/g1_1.in";
	//map<int, vector<int>> graph1 = LoadGraphFromFile(path_g1);
	//printGraph(graph1);

	std::string path_g2 = "Day1/Task1/g1_1.in";
	map<int, vector<int>> graph2 = LoadGraphFromFile(path_g2);
	printGraph(graph2);

	//////////////////////////////////// DAY 2 //////////////////////////////////////

	/*
	* Nalezněte výchozí implementaci zásobníku ve vašem oblíbeném jazyce.
	* Poté načtěte soubor seq.txt. Na každém řádku máte jeden z příkazů insert <number> a remove.
	* Příkaz insert <number> vloží číslo <number> do zásobníku.
	* Příkaz remove odstraní prvek ze zásobníku a vypíše ho na standardní výstup.
	*/

	//stack_example();

	/*
	*	Použij frontu
	*/

	// queue_example();


	/*
	* 6. Načtěte graf graph.txt jako neorientovaný graf. Ten je definovaný ve stejném formátu jako včera.
	* 7. Určete jaké vrcholy lze navštívit z vrcholu 0. Kolik jich je?
	* 8. Jaká je délka nejkratší cesty z vrcholu 0 do vrcholu 7.
	*/

	map<int, vector<int>> graph;
	string path = "Day1/Task1/g1_1.in";
	// @param0 cesta k souboru
	// @param1 graph, ke zpracovani
	// @param2 pocatecni bod
	// @param3 koncovy bod, -1 pro vypsani vsech moznych cest
	/*bfs(path, graph, 0, 7);
	cout << "////////////////////////////////////////////////////" << "\n";
	dfs(path, graph, 3, 3);*/


	// REKURZIVNI DFS
	/*graph = LoadGraphFromFile(path);
	vector<bool> visited = create_false_vector(graph.size());
	recursive_dfs(graph, 0, visited);*/

	// HEAP 
	/*
	* 1. Zopakujte úkol 2. z rána, pouze místo zásobníku použijte haldu. Operaci remove chápejte jako extract-min.
	* 2. Zopakujte předchozí úkol, ale místo haldy použijte pole. Prvky přidávejte nakonec a při implementaci extract-min hledejte minimum naivně pomocí procházení celého pole.
	* 3. Porovnejte časy běhu z kroků 1. a 2.
	* 5. Naimplementuje sami haldu. Zkuste dodržet kostru z 20170919_heap.zip. Zkuste poté použít vaší implementaci v předchozích úkolech a zkontrolujte, že dává stejné výsledky.
	*/

	system("PAUSE");
	return 0;
}