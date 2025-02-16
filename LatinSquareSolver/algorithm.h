/**
 * @file algorithm.h
 * @brief Header file for solving the Latin square puzzle.
 *
 * Contains function declarations for solving the puzzle using a stack-based approach
 * and helper functions for validation and cell finding.
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "node.h"

/**
 * @brief Solves the Latin square puzzle.
 *
 * Uses a stack-based approach to solve the puzzle by iterating over possible numbers
 * and backtracking when necessary.
 *
 * @param stack A pointer to the stack used for state management during solving.
 * @return bool Returns true if a solution is found, false otherwise.
 */
bool solveLatinSquare(Stack *stack);

/**
 * @brief Finds the next empty cell in the puzzle.
 *
 * Searches the matrix for the first cell with a value of zero, starting from
 * the position of the last inserted value.
 *
 * @param node A pointer to the current puzzle node.
 * @param row A pointer to store the row index of the next empty cell.
 * @param col A pointer to store the column index of the next empty cell.
 * @return int Returns EXIT_SUCCESS if an empty cell is found, EXIT_FAILURE otherwise.
 */
int findNextEmptyCell(Node *node, int *row, int *col);

/**
 * @brief Checks for duplicate values in the row and column of a given cell.
 *
 * Validates whether placing a given number in a specific cell violates the
 * Latin square rules.
 *
 * @param node A pointer to the current puzzle node.
 * @param num The number to check for duplicates.
 * @param row The row index of the cell to check.
 * @param col The column index of the cell to check.
 * @return bool Returns true if a duplicate is found, false otherwise.
 */
bool checkDuplicates(Node *node, int num, int row, int col);

#endif // ALGORITHM_H
