#include "SudokuSolver.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    int n = grid.size();

    for (int i = 0; i < n; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    int subgridSize = sqrt(n);
    int subgridRow = (row / subgridSize) * subgridSize;
    int subgridCol = (col / subgridSize) * subgridSize;
    for (int i = 0; i < subgridSize; i++) {
        for (int j = 0; j < subgridSize; j++) {
            if (grid[subgridRow + i][subgridCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& grid) {
    int n = grid.size();
    int emptyRow = -1, emptyCol = -1;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == 0) {
                emptyRow = row;
                emptyCol = col;
                break;
            }
        }
        if (emptyRow != -1) {
            break;
        }
    }

    if (emptyRow == -1) {
        return true;
    }

    for (int num = 1; num <= n; num++) {
        if (isSafe(grid, emptyRow, emptyCol, num)) {
            grid[emptyRow][emptyCol] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[emptyRow][emptyCol] = 0;
        }
    }

    return false;
}

void readSudokuFromFile(vector<vector<int>>& grid, const string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        int n = grid.size();
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                inputFile >> grid[row][col];
            }
        }
        inputFile.close();
    } else {
        cerr << "Error opening input file.";
    }
}

void writeSudokuToFile(const vector<vector<int>>& grid, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        int n = grid.size();
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                outputFile << grid[row][col] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    } else {
        cerr << "Error opening output file.";
    }
}
