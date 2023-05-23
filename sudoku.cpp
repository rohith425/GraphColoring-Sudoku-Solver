#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to check if a number can be placed in a particular cell
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    int n = grid.size();

    // Check if the number already exists in the row or column
    for (int i = 0; i < n; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the corresponding sub-grid
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

// Function to solve the Sudoku puzzle using backtracking and graph coloring
bool solveSudoku(vector<vector<int>>& grid) {
    int n = grid.size();
    int emptyRow = -1, emptyCol = -1;

    // Find the first empty cell in the grid
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

    // If no empty cell is found, the puzzle is solved
    if (emptyRow == -1) {
        return true;
    }

    // Try numbers from 1 to n in the empty cell
    for (int num = 1; num <= n; num++) {
        if (isSafe(grid, emptyRow, emptyCol, num)) {
            grid[emptyRow][emptyCol] = num;

            // Recursively solve the Sudoku puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // Backtrack if the solution is not valid
            grid[emptyRow][emptyCol] = 0;
        }
    }

    return false;
}

// Function to read Sudoku puzzle from input file
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

// Function to write Sudoku solution to output file
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


int main() {
int n; // Size of Sudoku grid (n x n)
cout << "Enter the size of the Sudoku grid: ";
cin >> n;

vector<vector<int>> grid(n, vector<int>(n, 0));

string inputFilename, outputFilename;
cout << "Enter the name of the input file: ";
cin >> inputFilename;
cout << "Enter the name of the output file: ";
cin >> outputFilename;

// Read Sudoku puzzle from input file
readSudokuFromFile(grid, inputFilename);

// Solve the Sudoku puzzle
if (solveSudoku(grid)) {
    cout << "Sudoku solved successfully!" << endl;

    // Write Sudoku solution to output file
    writeSudokuToFile(grid, outputFilename);
    cout << "Solution written to " << outputFilename << endl;
} else {
    cout << "Unable to solve the Sudoku puzzle." << endl;
}

return 0;

}
