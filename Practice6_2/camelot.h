#pragma once

#include <string>

constexpr int INF = 0x1FFFFFFF;
constexpr int TDIR_SIZE = 8;
constexpr int TABLE_SIZE = 64;
constexpr int MOV_KING[TDIR_SIZE][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
constexpr int MOV_KNIGHT[TDIR_SIZE][2] = { {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2} };

void move(int** dirs, const int(&movements)[TDIR_SIZE][2]);

void floyd(int** dist);

int setKingPos(const std::string& str);

int* setKnightPos(const std::string& str, int& cnt);

int getMinSteps(int** kingDir, int** knightDir, const int kingPos, const int cnt, const int* knightPos);

void print_matrix(int** matrix);

int tournament();