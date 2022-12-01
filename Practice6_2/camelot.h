#pragma once

#include <string>

#define INF (0x1fffffff)
#define TDIR_SIZE (8)
#define TABLE_SIZE (64)

constexpr int knightMovements[TDIR_SIZE][2] = { {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2} };
constexpr int kingMovements[TDIR_SIZE][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

void move(int** dirs, const int(&movements)[TDIR_SIZE][2]);

void floyd(int** dist);

int setKingPos(const std::string& str);

int* setKnightPos(const std::string& str, int& cnt);

int getMinSteps(int** kingDir, int** knightDir, const int kingPos, const int cnt, const int* knightPos);

void print_matrix(int** matrix);

int tournament();