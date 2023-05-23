#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <vector>
#include <string>
using namespace std;

bool isSafe(vector<vector<int>>& grid, int row, int col, int num);
bool solveSudoku(vector<vector<int>>& grid);
void readSudokuFromFile(vector<vector<int>>& grid, const string& filename);
void writeSudokuToFile(const vector<vector<int>>& grid, const string& filename);

#endif