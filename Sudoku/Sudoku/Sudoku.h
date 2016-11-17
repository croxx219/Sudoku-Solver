#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "CyclicList.h"

#define ROWS 9
#define COLS 9
using namespace std;

struct coord
{
	int x;
	int y;

	bool operator!=(const coord &rs) { return (rs.x != x || rs.y != y); };
	int dist() { return (y - x); };
	coord() { x = 0; y = 0; };
	coord(int a, int b) { x = a; y = b; };
};

template<class Type>
class Sudoku {
private:
	Type matrix[ROWS][COLS];    // Matrix that holds Sudoku, empty space is 0
public:
	Sudoku(string filename);
	void readFile(string input);
	void print();
	bool IsFinished();
	void RemainingNumbers(unsigned int block, int row, int col, CyclicList<int> &t);
	void GetIncompatibleNumbers(unsigned int row, unsigned int column, CyclicList<int> &t);
	void GetBlockStart(unsigned int block, unsigned int &row, unsigned int &column);
	unsigned int GetBlockFromCoord(int i, int j);
	coord CheckConflict(unsigned int number, unsigned int block, unsigned int row, unsigned int column);
	bool Track();
};

template<class T>
Sudoku<T>::Sudoku(string filename) {
	cout << endl;
	this->readFile(filename);
	this->print();
}

template<class T>
void Sudoku<T>::readFile(string input) {
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
				line = line.substr(pos + 1);         // Trim the read line to start after first comma
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
		throw 0;
	}
}
template<class T>
void Sudoku<T>::print() {
	for (int i = 0; i < ROWS; i++) {
		if(i == 3 || i==6){
			cout << "-------------------------------\n";
		}
		for (int j = 0; j < COLS; j++) {
			if(j==0 || j== 6 || j == 3)
				cout << "|";
			if(this->matrix[i][j] == 0)
				cout << " * ";
			else
				cout << " " << this->matrix[i][j] << " ";
		}
		cout << "|\n";
	}
}
template<class T>
void Sudoku<T>::GetIncompatibleNumbers(unsigned int row, unsigned int col, CyclicList<int> &tar)
{
	CyclicList<int> numList;

	for (int i = 0; i < 9; i++)
	{
		if (col != i && matrix[row][i] > 0 && numList.NumberOf(matrix[row][i]) == 0)
			numList.push_front(matrix[row][i]);
	}

	for (int i = 0; i < 9; i++)
	{
		if (row != i && matrix[i][col] > 0 && numList.NumberOf(matrix[i][col]) == 0)
			numList.push_front(matrix[i][col]);
	}

	tar.TransferList(numList);
}

template<class T>
unsigned int Sudoku<T>::GetBlockFromCoord(int i, int j)
{
	if (i < 3)
	{
		if (j < 3)
			return 0;

		else if (j < 6)
			return 1;

		else return 2;
	}

	if (i >= 3 && i < 6)
	{
		if (j < 3)
			return 3;

		else if (j < 6)
			return 4;

		else return 5;
	}

	if (i >= 6 && i < 9)
	{
		if (j < 3)
			return 6;

		else if (j < 6)
			return 7;

		else return 8;
	}

	cout << "Critical error: invalid block" << endl;
	return 9;
}

template<class T>
bool Sudoku<T>::Track()
{
	if (IsFinished()) //check if finished
	{
		print();
		return true;
	}

	coord loc(0, 0);

	for (int i = 0; i < 9; i++) //find next spot to fill
		for (int j = 0; j < 9; j++)
			if (matrix[i][j] == 0)
			{
				loc = coord(i, j);
				break;
			}

	CyclicList<int> varList;
	RemainingNumbers(GetBlockFromCoord(loc.x, loc.y), loc.x, loc.y, varList); //get unassigned variable

	for (int i = 0; i < varList.GetSize(); i++)
	{
		matrix[loc.x][loc.y] = varList.GetNthNodeData(i);

		if (Track())
			return true;

		matrix[loc.x][loc.y] = 0; //backtrack
	}

	return false;
}

template<class T>
coord Sudoku<T>::CheckConflict(unsigned int number, unsigned int block, unsigned int row, unsigned int column)
{
	if (number > 9)
		return coord(-1, -1);

	unsigned int r;
	unsigned int c;

	GetBlockStart(block, r, c);

	for (unsigned int i = r, j = c, counter = 0; counter < 9; i++, j++, counter++)
	{
		if (matrix[i][j] == number)
			return coord(i, j);

		if (counter % 3 == 0 && counter > 0)
		{
			i = r + 1;
			j = c;
		}
	}

	for (unsigned int i = 0, j = row; i < 9; i++)
	{
		if (matrix[j][i] == number)
			return coord(i, j);
	}

	for (unsigned int i = 0, j = column; i < 9; i++)
	{
		if (matrix[i][j] == number)
			return coord(i, j);
	}

	return coord(9, 9);
}

template<class T>
void Sudoku<T>::GetBlockStart(unsigned int block, unsigned int &row, unsigned int &column)
{
	if (block > 8)
		row = column = 9;

	switch (block)
	{
	case 0:
		row = 0;
		column = 0;
		break;
	case 1:
		row = 0;
		column = 3;
		break;
	case 2:
		row = 0;
		column = 6;
		break;
	case 3:
		row = 3;
		column = 0;
		break;
	case 4:
		row = 3;
		column = 3;
		break;
	case 5:
		row = 3;
		column = 6;
		break;
	case 6:
		row = 6;
		column = 0;
		break;
	case 7:
		row = 6;
		column = 3;
		break;
	case 8:
		row = 6;
		column = 6;
		break;
	}
}

template<class T>
bool Sudoku<T>::IsFinished()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			if (matrix[i][j] == 0)
				return false;

	return true;
}

template<class T>
void Sudoku<T>::RemainingNumbers(unsigned int block, int row, int col, CyclicList<int> &tar)
{
	CyclicList<int> numlist;

	if (block > 8)
	{
		numlist.push_front(-1);
		return;
	}

	unsigned int startrow;
	unsigned int startcol;

	GetBlockStart(block, startrow, startcol);

	for (int i = 1; i <= 9; i++)
		numlist.push_front(i);

	for (unsigned int i = startcol, counter = 0, k = startrow, j = 0; j < 9; j++, i++)
	{
		if (matrix[k][i] > 0 )
		numlist.erase(matrix[k][i], false);

		counter++;

		if (counter > 2)
		{
			counter = 0;
			k++;
			i = startcol - 1;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		if (col != i && matrix[row][i] > 0)
			numlist.erase(matrix[row][i], true);
	}

	for (int i = 0; i < 9; i++)
	{
		if (row != i && matrix[i][col] > 0)
			numlist.erase(matrix[i][col], true);
	}

	tar.TransferList(numlist);
}
