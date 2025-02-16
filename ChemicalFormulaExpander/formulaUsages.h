/**
 * @file formulaUsages.h
 * @brief Header file for chemical formula processing functions.
 *
 * This file contains declarations for functions that handle various chemical formula
 * operations, including validating balanced parentheses, counting protons, and expanding
 * formulas to an extended format.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#ifndef FORMULA_USAGES
#define FORMULA_USAGES

#include <stdio.h>
#include "stack.h"
#include "periodicTable.h"

/**
 * @brief Validates if the parentheses in chemical formulas within a file are balanced.
 * 
 * This function checks for balanced parentheses in each formula provided in the file.
 * 
 * @param filename The name of the file containing chemical formulas.
 * @return `true` if all formulas in the file have balanced parentheses, `false` otherwise.
 */
bool isValidParentheses(const char *filename);

/**
 * @brief Calculates the total number of protons for each formula in the input file.
 * 
 * This function reads formulas from an input file, calculates the total number of protons
 * based on the periodic table information, and writes the results to an output file.
 * 
 * @param inputFile The name of the file containing chemical formulas.
 * @param outputFile The name of the file where the proton counts will be written.
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @return `EXIT_SUCCESS` on success, `EXIT_FAILURE` if an error occurs.
 */
int countProtons(const char *inputFile, const char *outputFile, ELEMENT *elements, int sizeOfPeriodicTable);

/**
 * @brief Expands chemical formulas from condensed to detailed format.
 * 
 * This function reads chemical formulas from an input file, expands each formula to 
 * show each element explicitly, and writes the expanded formulas to an output file.
 * 
 * @param inputFile The name of the file containing condensed chemical formulas.
 * @param outputFile The name of the file where expanded formulas will be written.
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @return `EXIT_SUCCESS` on success, `EXIT_FAILURE` if an error occurs.
 */
int formulaExpander(const char *inputFile, const char *outputFile, ELEMENT *elements);

#endif
