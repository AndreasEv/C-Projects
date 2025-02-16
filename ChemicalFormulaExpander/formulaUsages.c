/**
 * @file formulaUsages.c
 * @brief Implementation of functions for chemical formula processing.
 *
 * This file contains the implementations of functions that handle parsing and processing
 * chemical formulas, including balanced parentheses validation, proton counting, and formula expansion.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "formulaUsages.h"

/**
 * @brief Parses a string to extract an integer value.
 * 
 * This function converts the initial numeric characters in a string to an integer.
 * 
 * @param str A pointer to the string containing the number.
 * @return The integer representation of the numeric part of the string.
 */
int parseInt(char *str)
{
    if (!isdigit(*str))
        return 1;

    int num = 0;

    while (isdigit(*str))
    {
        num *= 10;
        num += (*str - '0');
        str++;
    }
    return num;
}

/**
 * @brief Replaces all occurrences of a substring in a string with a new substring.
 * 
 * This function searches for occurrences of `oldSubstr` in `str` and replaces them
 * with `newSubstr`.
 * 
 * @param str The string to modify.
 * @param oldSubstr The substring to replace.
 * @param newSubstr The substring to replace `oldSubstr` with.
 */
void replaceSubstring(char str[], const char oldSubstr[], const char newSubstr[])
{
    char buffer[2048]; // Increase buffer size to handle larger replacements
    char *pos;

    buffer[0] = '\0';  // Initialize the buffer to an empty string
    char *start = str; // Pointer to the current start of the string

    // Loop to replace all occurrences of oldSubstr
    while ((pos = strstr(start, oldSubstr)) != NULL)
    {
        // Copy everything before the old substring into the buffer
        int lengthBefore = pos - start;
        strncat(buffer, start, lengthBefore);

        // Append the new substring to the buffer
        strcat(buffer, newSubstr);

        // Move the start pointer to the part after the old substring
        start = pos + strlen(oldSubstr);
    }

    // Append the remainder of the original string after the last occurrence
    strcat(buffer, start);

    // Copy the result back into the original string
    strcpy(str, buffer);
}

/**
 * @brief Expands chemical formulas without parentheses by replicating elements based on counts.
 * 
 * Processes a line containing a chemical formula, expanding any element groups with numeric
 * counts. Uses stack to handle each parenthesis.
 * 
 * @param line The line of the chemical formula to process.
 */
void noParenthesisExtender(char line[]) {
    STACK *stack = NULL;
    initStack(&stack);

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '(') {
            push(stack, i); // Track opening parenthesis index
        } else if (line[i] == ')') {
            int openIndex = topStack(stack);
            pop(stack);

            // Extract content inside the innermost parentheses
            int contentLen = i - openIndex - 1;
            char insideParenthesis[contentLen + 1];
            strncpy(insideParenthesis, line + openIndex + 1, contentLen);
            insideParenthesis[contentLen] = '\0';

            // Parse multiplier (if any) immediately after ')'
            int multiplierIndex = i + 1;
            int multiplier = 1; // Default multiplier
            if (isdigit(line[multiplierIndex])) {
                multiplier = parseInt(line + multiplierIndex);
            }

            // Create expanded content based on multiplier
            int expandedLen = contentLen * multiplier;
            char expandedStr[expandedLen + 1];
            expandedStr[0] = '\0';
            for (int j = 0; j < multiplier; j++) {
                strcat(expandedStr, insideParenthesis);
            }

            // Calculate how much of the string to shift and replace
            int replaceLen = contentLen + 2; // length of "(...)" part
            if (multiplier > 1)  // If a multiplier is found, calculate its length
                while (isdigit(line[multiplierIndex])) {
                    replaceLen++;
                    multiplierIndex++;
                }
            

            // Shift remaining content in line to fit the expanded content
            memmove(line + openIndex + expandedLen, line + openIndex + replaceLen, strlen(line) - openIndex - replaceLen + 1);
            strncpy(line + openIndex, expandedStr, expandedLen);

            i = openIndex + expandedLen - 1; // Reset index to the end of the expanded content
        }
    }

    while (!isEmptyStack(stack)) 
        pop(stack);
    
    free(stack);
}
/**
 * @brief Checks if parentheses in a file of chemical formulas are balanced.
 * 
 * Reads formulas from a file and verifies if each formula has balanced parentheses.
 * 
 * @param filename The name of the file with chemical formulas.
 * @return true if all formulas have balanced parentheses, false otherwise.
 */
bool isValidParentheses(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Unable to open the file\n");
        return false;
    }

    bool flag = true;
    STACK *stack = NULL;
    if (initStack(&stack) != EXIT_SUCCESS){
        printf("Stack initialization failed.\n");
        fclose(fp);
        return false;
    }
    char line[256];
    int lineIndex = 1;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        bool isValidLine = true;

        for (int k = 0; k < strlen(line); k++){

            if (line[k] == '(')
                push(stack, 1); // push 1 into the stack. The number doesn't matter all we care about is that the stack isn't empty
            
            else if (line[k] == ')' && !isEmptyStack(stack))
                pop(stack);             // Pop after checking the top
            

            //if we found a ')' and the stack is empty it means it doesnt have an '(' so the line is wrong
            else if(line[k] == ')' && isEmptyStack(stack))
                isValidLine = false;
            
        }

        //if the stack isn't empty it means we have more '(' than ')'  
        if (!isEmptyStack(stack) || !isValidLine){  
            printf("Parentheses NOT balanced in line: %d\n", lineIndex);
            flag = false;
        }

        while (!isEmptyStack(stack)){ 
            pop(stack);
        }

        lineIndex++;
    }

    free(stack);
    fclose(fp);

    return flag;
}

/**
 * @brief Calculates the total number of protons in each formula from an input file.
 * 
 * This function reads formulas from the input file, calculates the total number of protons
 * based on atomic numbers, and writes the result to the output file.
 * 
 * @param inputFile The name of the file with formulas.
 * @param outputFile The name of the file to write proton totals to.
 * @param elements The array of ELEMENT structs representing the periodic table.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int countProtons(const char *inputFile, const char *outputFile, ELEMENT *elements, int sizeOfPeriodicTable) {
    FILE *fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printf("Unable to open the %s file\n", inputFile);
        return EXIT_FAILURE;
    }

    FILE *fout = fopen(outputFile, "w");
    if (fout == NULL) {
        printf("Unable to open the %s file\n", outputFile);
        fclose(fin);
        return EXIT_FAILURE;
    }

    char line[256];
   
    while (fgets(line, sizeof(line), fin) != NULL) {
        
        noParenthesisExtender(line);

        // Initialize the total proton count for the line
        int totalProtons = 0;

        // Parse the extended formula and calculate proton count
        int i = 0;
        char element[4];  
        while (line[i] != '\0') {
            if (isupper(line[i])) {
                // Detect if it's a one-letter, two-letter, or three-letter element
                if (islower(line[i + 1])) {
                    if (islower(line[i + 2])) {
                        // 3-letter element
                        element[0] = line[i];
                        element[1] = line[i + 1];
                        element[2] = line[i + 2];
                        element[3] = '\0';
                        i += 3;
                    } else {
                        // 2-letter element
                        element[0] = line[i];
                        element[1] = line[i + 1];
                        element[2] = '\0';
                        i += 2;
                    }
                } else {
                    // 1-letter element
                    element[0] = line[i];
                    element[1] = '\0';
                    i++;
                }

                // Find the element's proton number
                ELEMENT foundElement = findElement(elements, element, sizeOfPeriodicTable);

                // Parse the quantity following the element name, default to 1 if no number
                int count = parseInt(&line[i]);
                while (isdigit(line[i])) 
                    i++; // Move index past the digits

                // Add to total proton count
                if (foundElement.num != -1)
                    totalProtons += (foundElement.num * count);
            }
            else 
                i++;
            
        }

        // Write the total proton count to the output file
        fprintf(fout, "%d\n", totalProtons);
    }

    // Close the files
    fclose(fin);
    fclose(fout);

    return EXIT_SUCCESS;
}

/**
 * @brief Expands chemical formulas from condensed format to extended format.
 * 
 * Reads condensed formulas from an input file, expands each formula to display each element
 * explicitly, and writes the expanded formulas to an output file.
 * 
 * @param inputFile The name of the file with condensed formulas.
 * @param outputFile The name of the file to write expanded formulas to.
 * @param elements The array of ELEMENT structs representing the periodic table.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int formulaExpander(const char *inputFile, const char *outputFile, ELEMENT *elements)
{
    FILE *fin = fopen(inputFile, "r");

    if (fin == NULL)
    {
        printf("Unable to open the %s file\n", inputFile);
        fclose(fin);
        return EXIT_FAILURE;
    }

    FILE *fout = fopen(outputFile, "w");

    if (fout == NULL)
    {
        printf("Unable to open the %s file\n", outputFile);
        fclose(fout);
        return EXIT_FAILURE;
    }

    char *line=(char*)malloc(256);
   
    while (fgets(line, 256, fin) != NULL)
    {
        int i = 0; // Declare 'i' before using it
 
        noParenthesisExtender(line);

        char *finalExtended = (char*) calloc(512,1);

        
       i = 0;
        char *element = (char *)malloc(4);
        while (line[i] != '\0') {
            if (isupper(line[i]) && islower(line[i + 1])) {
        // Two-letter element
            element[0] = line[i];
            element[1] = line[i + 1];
            element[2] = '\0';
            i += 2;
        }
        else if (isupper(line[i])) {
        
            element[0] = line[i];
            element[1] = '\0';
            i++;
        } 
        else {
            i++;
            continue;
        }

        if (!isValidElement(elements, element)) {
            printf("%s is Not an element\n", element);
            free(element);
            return EXIT_FAILURE;
        }

    
        int count = parseInt(line + i);
        if (count == 0) {
            count = 1;  // Default to 1 if no number follows the element
        }

    
        for (int k = 0; k < count; k++) {
            strcat(finalExtended, element);
            strcat(finalExtended, " ");
        }
    }

    free(element);

    fprintf(fout, "%s\n", finalExtended);
    free(finalExtended);
}
free(line);
fclose(fin);
fclose(fout);

return EXIT_SUCCESS;
}
