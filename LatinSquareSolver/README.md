@mainpage

# Latin Square Solver

## Project Description

The **Latin Square Solver** is a C implementation for solving Latin square puzzles using a stack-based backtracking algorithm. It verifies, solves, and displays the solution for a Latin square provided in a text file. This project employs dynamic memory allocation and custom data structures to manage the puzzle's state during computation.

The main file, **latinsolver.c**, reads the Latin square puzzle from an input file, initializes the solving environment, and applies the solving algorithm. The algorithm uses a stack to explore potential solutions through backtracking, ensuring all constraints of a Latin square are met.

---

## Features

- **Dynamic Stack Implementation**: Manages the puzzle's states during backtracking.
- **Constraint Validation**: Ensures all Latin square rules are followed.
- **Backtracking Algorithm**: Efficiently explores possible solutions.
- **Readable Output**: Prints each step of the solving process, including pushes and pops on the stack.

---

## How to Build

To compile the project, use the following command:

```bash
gcc -o latinsolver latinsolver.c algorithm.c stack.c -Wall -Wextra -pedantic -std=c99
```

---

## Usage

### Input Format

- The input file should start with the size of the Latin square (an integer `n`), followed by an `n x n` grid.
- The grid can contain numbers from 1 to `n` or `0` to represent empty cells.

#### Example Input File:
```
4
1 2 3 4
0 0 0 0
0 0 0 0
0 0 0 0
```

### Running the Program

To run the solver:

```bash
./latinsolver <input_file>
```

#### Example Usage:
```bash
./latinsolver puzzle.txt
```

### Output

The program outputs the solution to the Latin square, if one exists. If no solution is found, it prints an appropriate message.

---

## File Overview

- **latinsolver.c**: The main file responsible for reading the input file, initializing the stack, and solving the Latin square.
- **algorithm.c**: Implements the core solving logic, including backtracking and constraint checking.
- **algorithm.h**: Header file declaring functions for the solving algorithm.
- **stack.c**: Implements the stack data structure used to manage puzzle states.
- **stack.h**: Header file defining the stack and its associated operations.

---

## Key Functions

### In algorithm.c

- `bool solveLatinSquare(Stack *stack)`: Uses backtracking to solve the Latin square.
- `int findNextEmptyCell(Node *node, int *row, int *col)`: Finds the next empty cell in the puzzle.
- `bool checkDuplicates(Node *node, int num, int row, int col)`: Checks for duplicate values in the same row or column.

### In stack.c

- `int initStack(Stack **stack)`: Initializes the stack.
- `int push(Stack *stack, Node *value)`: Pushes a new state onto the stack.
- `int pop(Stack *stack, Node *retNode)`: Pops the top state from the stack.
- `void freeStack(Stack *stack)`: Frees memory allocated for the stack.

---

## Dependencies

The project relies on the standard C library (`stdlib.h`, `stdbool.h`, and `stdio.h`) and includes no additional dependencies.

---

## Future Improvements

- Optimize the backtracking algorithm for larger puzzles.
- Extend support for additional constraints (e.g., Sudoku-like rules).

---

## Author

- **Spyros Gavriil**: Developer and maintainer of the project.
- **Andreas Evagorou**: Developer and maintainer of the project.
