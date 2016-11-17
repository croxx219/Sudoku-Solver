#include "Sudoku.h"

int main() {
    cout << "*********Welcome to the Sudoku Solver*******" << endl;
    Sudoku<int> * first = new Sudoku<int>();
    cout << "\nThis is the solution:\n " << endl;
    first->Track();
    // To keep cmd window open in VS
    cin.get();
    cin.get();
    return 0;
}