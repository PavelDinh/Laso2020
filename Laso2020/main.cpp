#include "Dijkstra.h"
#include <map>
#include <fstream>
#include <sstream>
#include <regex>
#include <stack>
#include <ctime>
#include <chrono>
#include "BinaryHeap.h"

#define print(x) std::cout << x;
using namespace std;

map<int, vector<int>> load_unoriented_graph(string& path)
{
	ifstream file(path);
	map<int, vector<int>> graph;

	if (file.is_open())
	{
		int v, e = 0;
		file >> v;
		file >> e;
		static_cast<void>(graph.get_allocator().allocate(v));

		int iv, nv;
		for (int i = 0; i < e; i++)
		{
			file >> iv; file >> nv;
			graph[iv].push_back(nv);
			graph[nv].push_back(iv);
		}
		file.close();
	}
	return graph;
}

map<int, vector<int>> load_weighted_unoriented_graph(string& path, int& alloc)
{
	ifstream file(path);
	map<int, vector<int>> graph;
	vector<int> vals;
	if (file.is_open())
	{
		int e = 0;
		file >> alloc;
		file >> e;
		graph.get_allocator().allocate(alloc);

		for (int i = 0; i < alloc; i++)
		{
			for (int j = 0; j < alloc; j++)
			{
				graph[i].push_back(0);
			}			
		}
		int iv, nv, ev;
		for (int i = 0; i < e; i++)
		{
			file >> iv; file >> nv; file >> ev;
			graph[iv][nv] = ev;
			graph[nv][iv] = ev;
		}
		file.close();
	}
	return move(graph);
}

map<int, vector<int>> load_oriented_graph(string& path)
{
	ifstream file(path);
	map<int, vector<int>> graph;

	if (file.is_open())
	{
		int v, e = 0;
		file >> v;
		file >> e;
		static_cast<void>(graph.get_allocator().allocate(v));

		int iv, nv;
		for (int i = 0; i < e; i++)
		{
			file >> iv; file >> nv;
			graph[iv].push_back(nv);
		}
		file.close();
	}
	return graph;
}

void print_unoriented_dijkstra_from_file(string& path, int& src)
{
	ifstream file(path);
	
	if (file.is_open())
	{
		int v, e = 0;
		file >> v;
		file >> e;
		DijkstraGraph g(v);

		for (size_t i = 0; i < e; i++)
		{
			int v, nv, ev = 0;
			file >> v; file >> nv; file >> ev;
			g.addEdge(v, nv, ev);
			g.addEdge(nv, v, ev);
		}
		file.close();
		g.shortestPath(src);
	}
}

void print_graph(map<int, vector<int>>& graph) {

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

bool is_number(const string& s)
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
					std::cout << "Top value of a queue is: " << s.back() << "\n";
				}
			}
			else if (com == "remove")
			{
				std::cout << "Top value of a queue " << s.back() << " was removed.\n";
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

void heap_example(bool& print)
{
	ifstream file("Day2/seq.txt");

	if (file.is_open())
	{
		BinaryHeap h(1000);
		string com, nextCom;
		while (file >> com)
		{
			int v = 0;
			if (com == "insert")
			{
				file >> nextCom;
				if (is_number(nextCom)) {
					v = std::stoi(nextCom);
					h.insertKey(v);
					if (print)
						std::cout << "Min value of a heap is: " << h.getMin() << "\n";
				}
			}
			else if (com == "remove")
			{
				if (print)
					std::cout << "Min value of a heap: " << h.getMin() << " was removed.\n";
				h.extractMin();
			}
		}
	}
}

void array_example(bool& print)
{
	ifstream file("Day2/seq.txt");

	if (file.is_open())
	{
		vector<int> arr;

		string com, nextCom;
		int temp = 0;
		while (file >> com)
		{
			int v = 0;

			if (com == "insert")
			{
				file >> nextCom;
				if (is_number(nextCom)) {
					v = std::stoi(nextCom);
					arr.push_back(v);
					for (size_t i = 0; i < arr.size(); i++)
					{
						if (arr[i] == v)
						{
							if (print)
								std::cout << "Element : " << arr[i] << " added.\n";
							temp = v;
							break;
						}
					}
				}
			}
			else if (com == "remove")
			{
				for (size_t i = 0; i < arr.size(); i++)
				{
					if (arr[i] == temp)
					{
						if (print)
							std::cout << "Element : " << arr[i] << " was removed.\n";
						arr.erase(arr.begin() + i);
						break;
					}
				}
			}
		}
	}
}

void bfs(string& path, map<int, vector<int>>& graph, int s, int v, int& alloc)
{
	// Load graph
	graph = load_weighted_unoriented_graph(path, alloc);
	vector<bool> visited(alloc);
	vector<int> values(alloc);

	for (int i = 0; i < alloc; i++)
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

void dfs(string& path, map<int, vector<int>>& graph, int s, int v)
{
	// Load graph
	graph = load_unoriented_graph(path);
	int size = graph.size();
	vector<bool> visited(size);
	vector<int> values(size);

	for (int i = 0; i < size; i++)
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

vector<bool> create_false_vector(const int& size)
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

// DIJKSTRA FUNCTIONS
int minDistance(vector<int>& dist, vector<bool>& sptSet, int& s)
{
	int min = INT_MAX, min_index = 0;
	for (int i = 0; i < s; i++)
	{
		if (sptSet[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	}
	return min_index;
}

void print_solution(vector<int> dist, int& s)
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < s; i++)
			printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void dijkstra(map<int,vector<int>>& graph, int src, int& s)
{
	vector<int> dist(s);// The output array.  dist[i] will hold the shortest 
	// distance from src to i 

	vector<bool> sptSet(s); // sptSet[i] will be true if vertex i is included in shortest 
	// path tree or shortest distance from src to i is finalized 

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < s; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0 
	dist[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < s - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not 
		// yet processed. u is always equal to src in the first iteration. 
		int u = minDistance(dist, sptSet, s);

		// Mark the picked vertex as processed 
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int v = 0; v < s; v++)
		{
			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
	// print the constructed distance array
	print_solution(dist, s);
}

int main()
{
	/////////////////////////////////// DAY 1 ////////////////////////////////////////

	/*
	* 1. Načtěte nevážený graf ze souboru a vypište k každému uzlu jeho seznam hran.
	* 2. Načtěte vážený graf ze souboru a vypište k každému uzlu jeho seznam hran.
	* 3. V daném grafu zjistěte pro každý možný stupeň uzlu D, kolik je takových hran, jejichž oba koncové uzly mají tento stupeň D.
	Pro každý stupeň tento počet hran vypište. Porovnejte své výsledky s ukázkovými.
	* 4.Jindra vyrazí z uzlu A, který má určitý stupeň D.
	Pak jde do některého jeho sousedního uzlu B a nezajímá se o stupeň uzlu B.
	Z uzlu B se přesune do uzlu C, který je sousedem B a není to A. Jindra trvá na tom, že stupeň D startovního uzlu A i stupeň cílového uzlu C musejí být stejné.
	Určete, kolik je v daném grafu možností procházek podle Jindrových pravidel. Vypište toto jediné číslo na výstup.
	* 5.Řekneme, že hrana H je lokálně minimální, pokud její váha je striktně menší než váha kterékoli hrany, která s H sdíli jeden uzel. Task5
	Najděte v daném váženém grafu všechny lokálně minimální hrany a vypište je v rostoucím lexikografickém pořadí jejich krajních uzlů.
	* 6.Určete, kolik je trojúhelníků v každém grafu úlohy 4.
	Trojúhelník je trojice uzlů, v níž každý uzel sousedí se zbylými dvěma uzly.
	* 7.Určete, kolik je kružnic délky 4 v každém grafu úlohy 4.
	Kružnice nesmí obsahovat příčku, tj. první a třetí uzel v kružnici nesmí spolu sousedit a druhý a čtvrtý uzel v kružnici spolu nesmí sousedit.
	*/

	// TASK 1
	//string path_g = "Day1/Task1/g1_1.in"; // To test other graphs, just rename the .in file
	//map<int, vector<int>> graph = load_unoriented_graph(path_g);
	//print_graph(graph);

	// TASK 2
	//string path_g2 = "Day1/Task2/g2_1.in";
	//map<int, vector<int>> graph2 = load_unoriented_weighted_graph(path_g2);
	//print_graph(graph2);

	// TASK 3

	//////////////////////////////////// DAY 2 //////////////////////////////////////

	/*
	* 1. Načti soubor Day2
	* 2. Nalezněte výchozí implementaci zásobníku. Poté načtěte soubor seq.txt. Na každém řádku máte jeden z příkazů insert <number> a remove.
	Příkaz insert <number> vloží číslo <number> do zásobníku. Příkaz remove odstraní prvek ze zásobníku a vypíše ho na standardní výstup.
	* 3. [Dobrovolné] Sami naimplementujte zásobník a zopakujte úkoly z bodu 2. s vaší implementací. Zkontrolujte, že se výsledky shodují.
	* 4. To samé jako 2., pouze použijte frontu.
	* 5. [Dobrovolné] To samé jako 3., pouze implementujte frontu.
	* 6. Načtěte graf graph.txt jako neorientovaný graf. Ten je definovaný ve stejném formátu jako včera.
	* 7. Určete jaké vrcholy lze navštívit z vrcholu 0. Kolik jich je?
	* 8. Jaká je délka nejkratší cesty z vrcholu 0 do vrcholu 7.
	* 9. Kolik je komponent souvislosti v grafu? Komponenta souvislosti je množina vrcholů, že mezi každou dvojicí z nich vede cesta.
	Přitom platí, že do komponenty souvislosti již nelze přidat žádný další vrchol grafu tak, aby tato vlastnost zůstala zachována.
	* 10. Nyní načtěte graf 'graph.txt' jako orientovaný graf.
	* 11.Zopakujte úkoly 7. a 8. (abychom zvládli 9. pro orientovaný graf, museli bychom umět buď Tarjanův algoritmus nebo Kosarajiho algoritmus)
	*/

	// Task 2
	// stack_example();

	// Task 4
	// queue_example();

	// Task 6
	//string path = "Day2/graph.txt";
	//map<int, vector<int>> graph = load_unoriented_graph(path);
	//print_graph(graph);

	// Task 7
	//int counter = graph[0].size();
	//cout << counter << endl;

	// Task 8 
	//int alloc = 0;
	//map<int, vector<int>> graph;
	//bfs("Day2/graph.txt", graph, 0, 7, alloc);

	// Task 10
	//string path = "Day2/graph.txt";
	//map<int, vector<int>> graph = load_oriented_graph(path);
	//print_graph(graph);

	/////////////////////////////////// DAY 2 - AFTERNOON ////////////////////////////////////////

	// HEAP 
	/*
	* 1. Zopakujte úkol 2. z rána, pouze místo zásobníku použijte haldu. Operaci remove chápejte jako extract-min.
	* 2. Zopakujte předchozí úkol, ale místo haldy použijte pole. Prvky přidávejte nakonec a při implementaci extract-min hledejte minimum naivně pomocí procházení celého pole.
	* 3. Porovnejte časy běhu z kroků 1. a 2.
	* 4. Naimplementujte Median Maintenance, o kterém jsme mluvili na přednášce. Jako vstup můžete použít čísla ze souboru seq.txt, operace remove ignorujte
	* 5. Naimplementuje sami haldu. Zkuste dodržet kostru z 20170919_heap.zip. Zkuste poté použít vaší implementaci v předchozích úkolech a zkontrolujte, že dává stejné výsledky.
	*/

	// Task 1
	//heap_example();

	// Task 2
	//array_example();

	// Task 3
	//bool print = false;
	//auto start = chrono::high_resolution_clock::now();
	//heap_example(print);
	//auto stop = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	//cout << "Heap time complexity: " << duration.count() << " ms.\n";

	//start = chrono::high_resolution_clock::now();
	//array_example(print);
	//stop = chrono::high_resolution_clock::now();
	//duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	//cout << "Array time complexity: " << duration.count() << " ms.\n";

	// Task 5 --> Task 1

	//////////////////////////////////// DAY 3 //////////////////////////////////////

	// Dijkstra Algorithm implementing HEAP
	/*
	* 1. Dijkstrův algoritmus bez prioritní fronty v čase O(m⋅n).
	* 2. Dijkstrův algoritmus s prioritní frontou v čase O((m+n)⋅logn), možná souvislost s Primovým algoritmem.
	*/

	// Task 1
	//string path = "Day1/Task2/g2_1.in";
	//int alloc;
	//map<int, vector<int>> graph = load_weighted_unoriented_graph(path, alloc);
	//dijkstra(graph, 0, alloc); // Doesnt work on 0 edge values;
	//print_graph(graph);
	
	// Task 2
	//string path = "Day1/Task2/g2_1.in";
	//int src = 0;
	//print_unoriented_dijkstra_from_file(path, src);
	
	system("PAUSE");
	return 0;
}