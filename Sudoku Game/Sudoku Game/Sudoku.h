#include <iostream>
#include <string>
#include <fstream>
#define ROWS 9
#define COLS 9
using namespace std;

template<class Type>
class Sudoku {
private:
    Type matrix[ROWS][COLS];    // Matrix that holds Sudoku, empty space is 0
public:
    Sudoku() {
        string filename;
        cout << "\nPlease enter file name: ";
        cin >> filename;
        cout << endl;
        this->readFile(filename);
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
                    matrix[r][c] = value;
                    
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
           for (int j = 0; j < COLS; j++) {
               cout << "| " << this->matrix[i][j] << " ";
           }
           cout << "|\n";
       }
   }
};