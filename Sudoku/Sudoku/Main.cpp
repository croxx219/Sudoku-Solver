#include "Sudoku.h"

int main() {
    cout << "*********Welcome to the Sudoku Solver*******" << endl;
    string input = "";
    while(true){
          cout << "\nPlease enter file name(exit to abort): ";
          cin >> input;
          if(input == "exit") {
                cout << "Aborting...\n" << endl;
                break;
          }
          else{
                try{
                      Sudoku<int> * first = new Sudoku<int>(input);
                      cout << "\nThis is the solution:\n " << endl;
                      first->Track();
                 }
                 catch(int e){
                       if(e == 0){
                             cout << "\nTry again" << endl;
                             continue;
                       }
                 }

          }
    }
    // To keep cmd window open in VS
    cin.get();
    cin.get();
    return 0;
}
