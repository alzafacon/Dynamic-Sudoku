#include "SBoard.h"
#include <iostream>

SBoard::SBoard(){

    _filledCells = 0;

	for(int i=0; i < 9; i++){
		for(int j=0; j < 9; j++){
			_cell[i][j] = 0;

            _isClue[i][j] = false;

			_isInHouse[i][j] = false;
			_isInRow  [i][j] = false;
			_isInCol  [i][j] = false;
		}
	}

	//hard coded test input
	int test[9][9] = {
    {5,3,0, 0,7,0, 0,0,0},
    {6,0,0, 1,9,5, 0,0,0},
    {0,9,8, 0,0,0, 0,6,0},

    {8,0,0, 0,6,0, 0,0,3},
    {4,0,0, 8,0,3, 0,0,1},
    {7,0,0, 0,2,0, 0,0,6},

    {0,6,0, 0,0,0, 2,8,0},
    {0,0,0, 4,1,9, 0,0,5},
    {0,0,0, 0,8,0, 0,7,9}};

    for (int i=0; i < 9; i++){
        for (int j=0; j < 9; j++){
            if (test[i][j] != 0){
                setCell(i, j, test[i][j]);
                _isClue[i][j] = true;
            }
        }
    }
}

bool SBoard::isClue(int r, int c){
    return _isClue[r][c];
}

void SBoard::setCell(int r, int c, int n){

    if (n < 1 || 9 < n)
        return;

    if (isClue(r, c) == true)
        return;

    eraseCell(r, c);

    if (n != 0){
		_cell[r][c] = n;

		_isInHouse[getHouse(r, c)][n-1] = true;
		_isInRow[r][n-1] = true;
		_isInCol[c][n-1] = true;

		_filledCells++;
	}
}

void SBoard::eraseCell(int r, int c){

	int n = _cell[r][c];

	_cell[r][c] = 0;

	_isInHouse[getHouse(r, c)][n-1] = false;
	_isInRow[r][n-1] = false;
	_isInCol[c][n-1] = false;

    if (n != 0)
        _filledCells--;
}

bool SBoard::rowHas(int r, int n){
	return _isInRow[r][n-1];
}

bool SBoard::colHas(int c, int n){
	return _isInCol[c][n-1];
}

bool SBoard::houseHas(int h, int n){
	return _isInHouse[h][n-1];
}

bool SBoard::isValid(int r, int c, int n){

    //the board may contain only numbers between 1 and 9
	if ( !(1 <= n && n <= 9) ){
        return false;
	}

    //the row index should be between 0 and 8
	else if ( !(0 <= r && r <= 8) ){
        return false;
	}

    //the column index should be between 0 and 8
    else if ( !(0 <= c && c <= 8) ){
        return false;
    }

    //the number should not occur in the house
    else if ( houseHas(getHouse(r, c), n) ){
        return false;
    }

    //the number should not occur in the row
    else if( rowHas(r, n) ){
        return false;
    }

    //the number should not occur in the column
    else if( colHas(c, n) ){
        return false;
    }

    //all constraints passed, n is valid at (r, c)
    // a valid value does not mean that value is correct (this is why we need backtrack)
    else {
        return true;
    }
}

void SBoard::backtrack(int& r, int& c, int& g){

    do {
        c--;
        if (c < 0) {
            c = 8;
            r--;
        }
    } while ( isClue(r, c) == true );

    g = getCell(r, c) + 1;
    eraseCell(r, c);
}

void SBoard::print(){
    std::cout << "   1  2  3   4  5  6   7  8  9" << std::endl;
    std::cout << " +---------+---------+---------+" << std::endl;

    for (int i=0; i < 9; i++){
        std::cout << i+1 << '|';
        for (int j=0; j < 9; j++){

            if (isClue(i, j) == true){
                std::cout << "[" << getCell(i, j) << "]";
            } else {
                std::cout << " " << getCell(i, j) << " ";
            }

            if ((j+1)%3 == 0)//house row spacing
                std::cout << "|";
        }

        if ((i+1)%3 == 0)//house col spacing
            std::cout << "\n +---------+---------+---------+";

        std::cout << std::endl;
    }
}

void SBoard::solve(){

    int guess = 1;
    int row = 0;
    int col = 0;

    while (isSolved() == false){

        if (isClue(row, col) == true){
            col++;
            if (col > 8) {
                col = 0;
                row++;
            }
        } else {
            if ( isValid(row, col, guess) ){
                setCell(row, col, guess);

                col++;
                if (col > 8) {
                    col = 0;
                    row++;
                }

                guess = 1;
            } else {
                do {
                    guess++;
                } while(!isValid(row, col, guess) and guess <= 9);

                if (guess > 9){
                    backtrack(row, col, guess);
                }
            }
        }
    }
}

bool SBoard::isSolved(){
    return (_filledCells == 81);
}

int SBoard::getCell(int r, int c){
    return _cell[r][c];
}

int SBoard::getHouse(int r, int c){

    /*
    houses numbered as
    012
    345
    678

    correspondingly the row and column pairs for each house are
    [0-2,0-2] [0-2,3-5] [0-2,6-8]
    [3-5,0-2] [3-5,3-5] [3-5,6-8]
    [6-8,0-2] [6-8,3-5] [6-8,6-8]

    integer division of row and column index by three 'r/3' 'c/3'
    [0,0] [0,1] [0,2]
    [1,0] [1,1] [1,2]
    [2,0] [2,1] [2,2]

    the product of r value and 3
    [0,0] [0,1] [0,2]
    [3,0] [3,1] [3,2]
    [6,0] [6,1] [6,2]

    the sum of the r and c values
    012
    345
    678
    */

    return 3*(r/3) + c/3;
}
