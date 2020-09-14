#include "Node.h"

Node::Node(int value)
{
	this->m_value = value;
}

Node::~Node()
{
}

std::vector<int> Node::getNeighbours()
{
	return neighbours;
}

int Node::addNeighbour(int value)
{
	return value;
}

int Node::getValue()
{
	return m_value;
}
