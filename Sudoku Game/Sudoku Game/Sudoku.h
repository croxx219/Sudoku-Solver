#include <iostream>
#include <string>
#include <fstream>
#include "Variable.h"
#include "mQueue.h"
#define ROWS 9
#define COLS 9

using namespace std;

template<class Type>
class Sudoku {
private:
    Variable<Type> matrix[ROWS][COLS];    // Matrix that holds Sudoku, empty space is 0
public:
    Sudoku() {
        string filename;
        cout << "\nPlease enter file name: ";
        cin >> filename;
        cout << endl;
        this->readFile(filename);
        this->print();
        this->updateDom();
        // TODO debugging
        // this->print();
        //this->arcConst();
    }

    // Updates domain of initial sudoku for all variables
    void updateDom() {
        Variable<Type> *tmp;
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                tmp = &matrix[r][c];
                checkCol(c, tmp);
                checkRow(r, tmp);
                checkBlock(r, c, tmp);
            }
            
        }
    }

    void updateDom(Variable<Type> *tmp) {
        int row = tmp->getRow();
        int col = tmp->getCol();
        checkCol(col, tmp);
        checkRow(row, tmp);
        checkBlock(row, col, tmp);
    }

    void checkCol(int colIndex, Variable<Type> *var){
        for (int row = 0; row < ROWS; row++) {
            if (var->getValue() == 0)  // Position is empty
                var->removeDom(matrix[row][colIndex].getValue());
        }
    }

    void checkRow(int rowIndex, Variable<Type> *var) {
        for (int col = 0; col < COLS; col++) {
            if (var->getValue() == 0)  // Position is empty
                var->removeDom(matrix[rowIndex][col].getValue());
        }
    }

    void checkBlock(int rowIndex, int colIndex, Variable<Type> *var) {
        int row, col;
        switch(rowIndex / 3) {
        case 0: row = 0;
            break;
        case 1: row = 3;
            break;
        case 2: row = 6;
            break;
        }

        switch (colIndex / 3) {
        case 0: col = 0;
            break;
        case 1: col = 3;
            break;
        case 2: col = 6;
            break;
        }

        int rowStop = row + 3;
        int colStop = col + 3;
        for(; row < rowStop; row++)
            for (int c = col; c < colStop; c++) {
                if(var->getValue() == 0) // Position is empty
                   var->removeDom(matrix[row][c].getValue());
            }
    }

    // Finds next variable with domain of 1
    Variable<Type>* findNextVar() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (matrix[i][j].getDom() == 1)
                    return &matrix[i][j];
            }
        }
        return NULL;      // All variables assigned
    }


    void arcConst() {
        mQueue < Variable<Type>*> notchecked;

        Variable<Type> * mvar;
        while ((mvar = findNextVar()) != NULL) {
            mvar->assignValue();
            notchecked.enqueue(mvar);

            while (!notchecked.empty()) {
                Variable<Type> * tmp = notchecked.dequeue();
                checkCol(tmp->getCol(), tmp);
                checkRow(tmp->getRow(), tmp);
                checkBlock(tmp->getRow(), tmp->getCol(), tmp);
            }
        }

        cout << "Final solution: " << endl;
        this->print();
    }

   void readFile(string input) {
        string line;
        ifstream myfile(input);
        if (myfile.is_open())
        {
            // Reading sudoku from CSV file
            for (int r = 0; r<ROWS; r++)
            {
                // Reads a line at a time
                getline(myfile, line);
                for (int c = 0; c < COLS; c++) {
                    int pos = (int)line.find(',');
                    string data = line.substr(0, pos); // First value found
                   // cout << data << endl;              // TODO debug
                    line = line.substr(pos+1);         // Trim the read line to start after first comma
                   // cout << line << endl;              // TODO debug
                    int value = stoi(data);
                    Variable<Type> var(value,r,c);
                    matrix[r][c] = var;
                    
                }
            }
            // changing pointer position to be read to the beggining of the file
            myfile.close();
            
        }

        else
        {
            cout << "Unable to open file";
        }
    }

   void print() {
       for (int i = 0; i < ROWS; i++) {
           if (i == 3 || i == 6)
               cout << "---------------------------------------\n";
           for (int j = 0; j < COLS; j++) {
               if (this->matrix[i][j].getValue() == 0) {
                   cout << "| * ";
                   continue;
               }
               cout << "| " << this->matrix[i][j].getValue() << " ";
           }
          cout << "|\n";
       }

       // TODO debugging
       //for (int i = 0; i < ROWS; i++) {
       //    for (int j = 0; j < COLS; j++) {
       //        cout << i << "," << j << ": ";
       //        this->matrix[i][j].printDomain();
       //       cout << endl;
       //    }
       //    cout << "\n";
       //}
   }
};