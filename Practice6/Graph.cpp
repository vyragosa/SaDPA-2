#include "Graph.h"

#include <iostream>


void Graph::isStronglyConnected(int v, bool visited[]) {
	tNode* temp = head[v];

	while (temp != nullptr) {
		if (!visited[temp->dest] && temp->dest != v) {
			visited[temp->dest] = true;
			isStronglyConnected(temp->dest, visited);
		}
		temp = temp->next;
	}
}

Graph::Graph(int size) {
	this->size = size;
	head = new tNode*[size]{nullptr};
}

int Graph::add(int src, int dest, int weight) const {
	if (src >= size || dest >= size)
		return -1;
	head[src] = new tNode{dest, weight, head[src]};
	return 0;
}

void Graph::print() const {
	for (int dest = 0; dest < size; dest++) {
		tNode* node = head[dest];
		if (!node)
			continue;
		std::cout << dest << " -> ";
		while (node) {
			std::cout << node->dest << '(' << node->weight << ") ";
			node = node->next;
		}
		std::cout << '\n';
	}
}

int Graph::get(int src, int dest) const {
	tNode* node = head[src];
	while (node) {
		if (node->dest == dest)
			return node->weight;
		node = node->next;
	}
	return -1;
}

int Graph::remove(int src, int dest) const {
	tNode* node = head[src];
	tNode* prev = nullptr;
	while (node) {
		if (node->dest == dest) {
			if (!prev)
				head[src] = node->next;
			else
				prev->next = node->next;
			delete node;
			return 0;
		}
		prev = node;
		node = node->next;
	}
	return -1;
}

void Graph::resize(int size) {
	tNode** tmp = new tNode*[size]{nullptr};
	for (int i = 0; i < this->size; i++)
		tmp[i] = head[i];
	delete[] head;
	head = tmp;
	this->size = size;
}

bool Graph::isStronglyConnected() {
	bool* visited = new bool[size]{false};
	for (int i = 0; i < size; i++)
		if (head[i] != nullptr && !visited[i]) {
			isStronglyConnected(i, visited);
			break;
		}
	for (int i = 0; i < size; i++)
		if (head[i] != nullptr && !visited[i]) {
			delete[] visited;
			return false;
		}
	delete[] visited;
	return true;
}


int Graph::hamiltonianCycle(int v, bool*& visited, int path[], int pos) {
	if (pos == size) {
		if (get(path[pos - 1], path[0]) != -1)
			return 1;
		return 0;
	}
	tNode* node = head[v];
	while (node) {
		if (visited[node->dest] == false) {
			visited[node->dest] = true;
			path[pos] = node->dest;

			if (hamiltonianCycle(node->dest, visited, path, pos + 1))
				return 1;
			visited[node->dest] = false;
		}
		node = node->next;
	}
	return 0;
}

bool Graph::isAcyclic(int i, bool* visited, bool* recStack) {
	if (visited[i] == false) {
		visited[i] = true;
		recStack[i] = true;

		tNode* node = head[i];
		while (node) {
			if (!visited[node->dest] && isAcyclic(node->dest, visited, recStack))
				return true;
			if (recStack[node->dest])
				return true;
			node = node->next;
		}
	}
	recStack[i] = false;
	return false;
}

int Graph::hamiltonianCycle(int v) {
	int* path = new int[size];
	for (int i = 0; i < size; i++)
		path[i] = -1;
	path[0] = v;
	bool* visited = new bool[size]{false};
	visited[v] = true;
	const int res = hamiltonianCycle(v, visited, path, 1);
	delete[] visited;
	delete[] path;
	return res;

}

bool Graph::isAcyclic() {
	bool* visited = new bool[size]{false};
	bool* recStack = new bool[size]{false};
	for (int i = 0; i < size; i++)
		if (head[i] != nullptr && !visited[i])
			if (isAcyclic(i, visited, recStack)) {
				delete[] visited;
				delete[] recStack;
				return true;
			}
	delete[] visited;
	delete[] recStack;
	return false;
}


Graph::~Graph() {
	for (int i = 0; i < size; i++) {
		tNode* node = head[i];
		while (node) {
			tNode* tmp = node;
			node = node->next;
			delete tmp;
		}
	}
	delete[] head;
}

int testGraph() {
	int code = 0, menu = 1, num, num2, num3;
	Graph* graph = nullptr;
	while (menu) {
		std::cout << "Press 1 to create graph\n"
			<< "Press 2 to add edge\n"
			<< "Press 3 to remove edge\n"
			<< "Press 4 to print graph\n"
			<< "Press 5 to get edge weight\n"
			<< "Press 6 to resize graph\n"
			<< "Press 7 to check if graph is strongly connected\n"
			<< "Press 8 to check if graph is acyclic\n"
			<< "Press 9 to check if graph has hamiltonian cycle\n"
			<< "Press 10 to delete graph\n"
			<< "Press 0 to exit\n";
		std::cin >> menu;

		switch (menu) {
		case 1:
			std::cout << "Enter number of vertices: ";
			std::cin >> num;
			graph = new Graph(num);
			break;
		case 2:
			std::cout << "Enter source, destination and weight: ";
			std::cin >> num >> num2 >> num3;
			code = graph->add(num, num2, num3);
			break;
		case 3:
			std::cout << "Enter source and destination: ";
			std::cin >> num >> num2;
			code = graph->remove(num, num2);
			break;
		case 4:
			graph->print();
			break;
		case 5:
			std::cout << "Enter source and destination: ";
			code = graph->get(num, num2);
			std::cout << "Weight: " << code << std::endl;
			break;
		case 6:
			std::cout << "Enter new size: ";
			std::cin >> num;
			graph->resize(num);
			break;
		case 7:
			code = graph->isStronglyConnected();
			if (code)
				std::cout << "Graph is strongly connected\n";
			else
				std::cout << "Graph is not strongly connected\n";
			break;
		case 8:
			code = graph->isAcyclic();
			if (code)
				std::cout << "Graph is acyclic\n";
			else
				std::cout << "Graph is not acyclic\n";
			break;
		case 9:
			std::cout << "Enter starting vertex: ";
			std::cin >> num;
			code = graph->hamiltonianCycle(num);
			if (code)
				std::cout << "Graph has hamiltonian cycle\n";
			else
				std::cout << "Graph has no hamiltonian cycle\n";
		case 10:
			delete graph;
			break;
		default:
			break;
		}
		if (code == -1)
			std::cout << "There are some problems!\n";
		std::cout << std::endl;
	}
	return 0;
}
