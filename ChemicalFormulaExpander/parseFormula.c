/**
 * @file parseFormula.c
 * @brief A program to process chemical formulas based on a periodic table of elements.
 *
 * This program reads a file containing element data and performs one of three functions:
 * - Validates balanced parentheses in chemical formulas.
 * - Expands chemical formulas into their extended format.
 * - Calculates the total number of protons in chemical formulas.
 * 
 * The appropriate function is chosen based on command-line arguments.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formulaUsages.h"

/**
 * @brief Main function that processes chemical formulas based on user input.
 * 
 * This function parses command-line arguments to determine the desired operation:
 * - "-v": Validate balanced parentheses in formulas.
 * - "-ext": Expand formulas to a detailed format.
 * - "-pn": Calculate the total number of protons in each formula.
 * 
 * @param argc Argument count.
 * @param argv Argument vector containing input arguments:
 *   - argv[1]: Path to periodic table file (e.g., periodicTable.txt).
 *   - argv[2]: Operation type ("-v", "-ext", or "-pn").
 *   - argv[3]: Input file with chemical formulas.
 *   - argv[4]: Output file (only for "-ext" and "-pn" options).
 * 
 * @return int Exit status: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */

#ifndef DEBUG_PERIODICTABLE
#ifndef DEBUG_STACK

int main(int argc, char *argv[]) {
    
    if(!(argc == 4 || argc == 5)){ 
        printf("Arguments usages:\n");
        printf("./parseFormula periodicTable.txt -v <input.txt>\n");
        printf("./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
        printf("./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
        return EXIT_FAILURE;
    }

    ELEMENT *elements=NULL;
    int size=0;
    elements = readFile(&size, argv[1]);
    if (size==0)
        return EXIT_FAILURE;
    
    sortElements(elements, size);

    if (strcmp(argv[2],"-v")==0){

        if (argc!=4){
            printf("Correct input for parenthesis validation: ./parseFormula periodicTable.txt -v <input.txt>\n");
            freeElements(elements, size);
            return EXIT_FAILURE;
        }

        printf("Verify balanced parentheses in %s\n", argv[3]);

        if(isValidParentheses(argv[3]))
            printf("Parentheses are balanced for all chemical formulas.\n");
         
    }
    else if(strcmp(argv[2], "-ext") == 0){
        if (argc!=5){
            printf("Correct input for expantion: ./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
            freeElements(elements, size);
            return EXIT_FAILURE;
        }

        printf("Compute extended version of formulas in %s\n", argv[3]);
        formulaExpander(argv[3], argv[4], elements);
        printf("Writing formulas to %s\n", argv[4]);
    }
    else if(strcmp(argv[2], "-pn") == 0){ // Calculate Total Protons Number
        if(argc != 5){
            printf("Correct input for calculating total proton number: ./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
            freeElements(elements, size);
            return EXIT_FAILURE;
        }

       
        printf("Compute total proton number of formulas in %s\n", argv[3]);
        countProtons(argv[3], argv[4], elements, size);
        printf("Writing total proton numbers of the formulas to %s\n", argv[4]);

    }

    else{
        printf("3 Usages:\n");
        printf("Parenthesis validation: ./parseFormula periodicTable.txt -v <input.txt>\n");
        printf("Formula Expantion: ./parseFormula periodicTable.txt -ext <input.txt> <output.txt>\n");
        printf("Total proton number of a formula: ./parseFormula periodicTable.txt -pn <input.txt> <output.txt>\n");
        freeElements(elements, size);
        return EXIT_FAILURE;
    }

    freeElements(elements, size);

    return EXIT_SUCCESS;

}

#endif
#endif
