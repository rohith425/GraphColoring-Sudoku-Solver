#include <iostream>
#include <vector>
#include "SudokuSolver.hpp"

#define inputFilepath "input.txt"
#define outputFilepath "output.txt"

using namespace std;

int main() {
    int n; 
    cout << "Enter the size of the Sudoku grid: ";
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n, 0));

    string inputFilename, outputFilename;

    /*
    cout << "Enter the name of the input file: ";
    cin >> inputFilename;
    cout << "Enter the name of the output file: ";
    cin >> outputFilename;
    */

    // Read Sudoku puzzle from input file
    readSudokuFromFile(grid, inputFilepath);

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully!" << endl;

        // Write Sudoku solution to output file
        writeSudokuToFile(grid, outputFilepath);
        cout << "Solution written to " << outputFilepath << endl;
    } else {
        cout << "Unable to solve the Sudoku puzzle." << endl;
    }

    return 0;
}
