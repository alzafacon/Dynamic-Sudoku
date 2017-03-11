# Dynamic-Sudoku
Dynamic Programming example: solving a sudoku puzzle

Example of using backtracking to solve a sudoku puzzle.
When deciding if a given value is valid given the context, tables (maintained by the SBoard object) are used to look up occurences.

This is also an example of dynamic programming because the occurences of the numbers are not determined by traversing the board, instead look up tables are used.

<strong>I was wrong about his being a dynamic program. This is not really a dynamic program because there is not a divide and conquer algorithm. [SubsetSum](https://github.com/fidelcoria/SubsetSum "SubsetSum Repo") <em>is</em> an example of dynamic programming.</strong>

