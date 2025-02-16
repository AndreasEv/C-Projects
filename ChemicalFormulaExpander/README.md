/**
 * @author Andreas Evagorou
 * @file README.dox
 * @mainpage  Documentation for the Chemical Formula Processor project
 *
 * # Overview
 * A C program that processes chemical formulas with functionalities including:
 * - **Parentheses Validation**: Checks for balanced parentheses.
 * - **Formula Expansion**: Expands condensed formulas into an explicit format.
 * - **Proton Count Calculation**: Computes total proton counts based on element atomic numbers.
 *  
 * # Usage
 * To compile:
 * 
 * gcc -o parseFormula parseFormula.c formulaUsages.c periodicTable.c stack.c
 * 
 *
 * Run with one of the following commands:
 * 
 * ./parseFormula periodicTable.txt -v input.txt                # Validate parentheses
 * ./parseFormula periodicTable.txt -ext input.txt output.txt   # Expand formulas
 * ./parseFormula periodicTable.txt -pn input.txt output.txt    # Calculate protons
 * 
 */
