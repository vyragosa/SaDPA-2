// A simple representation of graph using STL
#include <iostream>
#include <vector>
using namespace std;


struct tNode {
	int dest;
	int weight;
	tNode* next;
};

class Graph {
	tNode** head;
	int size;
	void isStronglyConnected(int v, bool visited[]);
	int hamiltonianCycle(int v, bool visited[], int path[], int pos);
public:
	Graph(int size);
	int add(int src, int dest, int weight) const;
	void print() const;
	int get(int src, int dest) const;
	int remove(int src, int dest) const;
	void resize(int size);
	bool isStronglyConnected();
	int hamiltonianCycle(int v);
	~Graph();
};

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

int Graph::hamiltonianCycle(int v, bool visited[], int path[], int pos) {
	if (pos == size) {
		if (get(path[pos - 1], path[0]) != -1) {
			return 1;
		}
		else {
			return 0;
		}
	}

	tNode* temp = head[v];
	while (temp != nullptr) {
		if (!visited[temp->dest]) {
			visited[temp->dest] = true;
			path[pos] = temp->dest;
			if (hamiltonianCycle(temp->dest, visited, path, pos + 1)) {
				return 1;
			}
			visited[temp->dest] = false;
		}
		temp = temp->next;
	}
	return 0;
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
		cout << dest << " -> ";
		while (node) {
			cout << node->dest << '(' << node->weight << ") ";
			node = node->next;
		}
		cout << '\n';
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

int Graph::hamiltonianCycle(int v = 0) {
	int* path = new int[size];
	for (int i = 0; i < size; i++)
		path[i] = -1;
	path[0] = v;
	bool* visited = new bool[size] {false};
	visited[v] = true;
	int res = hamiltonianCycle(v, visited, path, 1);
	delete[] visited;
	delete[] path;
	return res;
	
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

int main() {
	Graph g(5);

	g.add(2, 1, 2);
	g.add(1, 2, 2);
	
	g.print();
	std::cout << g.isStronglyConnected() << std::endl;
	std::cout << g.hamiltonianCycle() << std::endl;
	return 0;
}
