#ifndef SBOARD_H
#define SBOARD_H

class SBoard {

private:
    //all private attributes have a '_' prefix

    int _filledCells;   //counts number of occupied cells (non-zero)

	int _cell[9][9];    //represents 9x9 sudoku board

	bool _isClue[9][9]; //table to identify clues and non-clues (guess cells)

	bool _isInHouse[9][9];  //tables reporting values present (includes clues and guesses)
	bool _isInRow  [9][9];  //the first index is th house, row, and column (each numbered 0-8)
	bool _isInCol  [9][9];  //the second index is the value (minus one)
	//ex. "does row 4 have the number 8?" ==> _isInRow[4][8-1]

	bool isClue(int r, int c);  //getter methods
    bool rowHas(int r, int n);
	bool colHas(int c, int n);
	bool houseHas(int h, int n);

	void setCell(int r, int c, int n);  //sets cell value of a clue cell
	void eraseCell(int r, int c);       //resets cell and updates tables

	bool isValid(int r, int c, int n);  //checks bounds and tables to justify guess

	void backtrack(int& r, int& c, int& g); //it's a long story

public:
	SBoard();

    void print();

    void solve();

    bool isSolved();
    int getCell(int r, int c);
    static int getHouse(int r, int c);
};

#endif  //SBOARD_H
