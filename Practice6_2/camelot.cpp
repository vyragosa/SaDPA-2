#include "camelot.h"
#include <iostream>

void move(int** dirs, const int (&movements)[TDIR_SIZE][2]) {
	for (int i = 0; i < TABLE_SIZE; i++)
		for (int j = 0; j < TABLE_SIZE; j++)
			dirs[i][j] = i == j ? 0 : INF;
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (const int* movement : movements) {
			if (int y = i % TDIR_SIZE + movement[1],
			        x = i / TDIR_SIZE + movement[0];
				x >= 0 && x < TDIR_SIZE && y >= 0 && y < TDIR_SIZE) {
				dirs[i][x * TDIR_SIZE + y] = 1;
			}
		}
	}
}

void floyd(int** dist) {
	for (int k = 0; k < TABLE_SIZE; k++)
		for (int i = 0; i < TABLE_SIZE; i++)
			for (int j = 0; j < TABLE_SIZE; j++)
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
}

int setKingPos(const std::string& str) {
	return ('8' - str[1]) * 8 + str[0] - 'A';
}

int* setKnightPos(const std::string& str, int& cnt) {
	auto knightPos = new int[TABLE_SIZE];
	for (int i = 2; i < str.length(); i += 2) {
		knightPos[cnt++] = ('8' - str[i + 1]) * 8 + str[i] - 'A';
	}
	return knightPos;
}

int getMinSteps(int** kingDir, int** knightDir, const int kingPos, const int cnt, const int* knightPos) {
	int minStep = INF;
	for (int i = 0; i < cnt; i++) {
		for (int x = 0; x < TABLE_SIZE; x++) {
			int kingStep = kingDir[kingPos][x] + knightDir[knightPos[i]][x];
			for (int y = 0; y < TABLE_SIZE; y++) {
				int knightStep = 0;
				for (int k = 0; k < cnt; k++) {
					if (k != i)
						knightStep += knightDir[knightPos[k]][y];
				}
				minStep = std::min(minStep, kingStep + knightStep + knightDir[x][y]);
			}
		}
	}
	return minStep;
}

void print_matrix(int** matrix) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int tournament() {
	auto kingDir = new int*[TABLE_SIZE + 1];
	auto knightDir = new int*[TABLE_SIZE + 1];
	for (int i = 0; i < TABLE_SIZE + 1; i++) {
		kingDir[i] = new int[TABLE_SIZE + 1];
		knightDir[i] = new int[TABLE_SIZE + 1];
	}

	move(kingDir, kingMovements);
	move(knightDir, knightMovements);
	floyd(kingDir);
	floyd(knightDir);
	std::string str;
	std::cout << "Enter cells: ";
	std::cin >> str; //D4A3A8H1H8
	const int kingPos = setKingPos(str);
	int cnt = 0;
	const int* knightPos = setKnightPos(str, cnt);
	std::cout << "Minimal steps: " << getMinSteps(kingDir, knightDir, kingPos, cnt, knightPos) << '\n';
	delete[] knightPos;
	for (int i = 0; i < TABLE_SIZE + 1; i++) {
		delete[] kingDir[i];
		delete[] knightDir[i];
	}
	delete[] kingDir;
	delete[] knightDir;
	return 0;
}
