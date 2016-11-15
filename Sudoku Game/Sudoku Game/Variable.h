#pragma once

template <class Type>
class Variable {
private:
    int domain[9] = { 1,2,3,4,5,6,7,8,9 };
    int domaincount = 9;
    int rowLocation, colLocation;
    Type value;
public:
    Variable(Type value_, int row, int col) {
        this->value = value_;
        this->rowLocation = row;
        this->colLocation = col;
    }
    Variable(){
        this->value = 0;
        this->rowLocation = 0;
        this->colLocation = 0;
    }

    void printDomain() {
        for (int i = 0; i < 9; i++) {
            cout << domain[i] << " ";
        }
    }

    int getValue() { return value; }
    int getRow() { return rowLocation; }
    int getCol() { return colLocation; }
    int getDom() { return domaincount; }

    // This method needs to be called after calling findNextVar from Sudoku.h
    void assignValue() {
        for (int i = 0; i < 9; i++) {
            if (domain[i] != 0) this->value = domain[i];
        }
        
    }

    bool removeDom(Type x) {
        for (int i = 0; i < 9; i++) {
            if (domain[i] == x) {
                domain[i] = 0;
                domaincount--;
            }
        }

        return domaincount == 0;         // Returns true if domain became empty
    }
};