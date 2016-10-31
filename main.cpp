//Fidel Coria

//7 January 2016

//Sudoku Solver v 1.0
// Memory Intensive

#include <iostream>
#include "SBoard.h"

using namespace std;

int main() {

    SBoard trunk;

    trunk.print();

    trunk.solve();

    trunk.print();

    return 0;
}
