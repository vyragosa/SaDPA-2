#pragma once

class Graph {
	struct tNode {
		int dest;
		int weight;
		tNode* next;
	};

	tNode** head;
	int size;
	void isStronglyConnected(int v, bool visited[]);
	int hamiltonianCycle(int v, bool*& visited, int path[], int pos);
	bool isAcyclic(int i, bool* visited, bool* recStack);
public:
	Graph(int size);
	int add(int src, int dest, int weight) const;
	void print() const;
	int get(int src, int dest) const;
	int remove(int src, int dest) const;
	void resize(int size);
	bool isStronglyConnected();
	int hamiltonianCycle(int v);
	bool isAcyclic();
	~Graph();
};

int testGraph();
