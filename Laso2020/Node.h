#pragma once
#include <vector>
#include <iostream>
class Node
{
private:
	std::vector<int> neighbours;
	int m_value;
public:
	Node(int value);
	~Node();
	std::vector<int> getNeighbours();
	int addNeighbour(int value);
	int getValue();
};

