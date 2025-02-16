/**
 * @file periodicTable.c
 * @brief Implementation of functions for managing a periodic table of elements.
 *
 * This file contains functions for reading, sorting, and validating elements, as well as 
 * freeing dynamically allocated memory for element structures.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "periodicTable.h"

/**
 * @brief Sorts an array of ELEMENT structs by atomic number in ascending order.
 * 
 * Uses selection sort to reorder the elements based on their atomic number.
 * 
 * @param elements Array of ELEMENT structs to sort.
 * @param size The number of elements in the array.
 */
void sortElements(ELEMENT *elements, int size) {

    int min, index;
    ELEMENT temp;
    for (int k=0; k<size; k++){
        min= elements[k].num;
        index = k;
        for (int i=k+1; i<size; i++)
            if (elements[i].num < min){
                index=i;
                min=elements[i].num;
            }
        temp=elements[k];
        elements[k]=elements[index];
        elements[index]=temp;
    }
}

/**
 * @brief Frees memory allocated for an array of ELEMENT structs.
 * 
 * This function deallocates each element's name and then the array itself.
 * 
 * @param elements Array of ELEMENT structs to free.
 * @param size The number of elements in the array.
 */
void freeElements(ELEMENT* elements, int size) {
    for (int k = 0; k < size; k++) 
        free((elements+k)->name);
    
    free(elements);
}

/**
 * @brief Reads elements from a file and stores them in a dynamically allocated array.
 * 
 * The function reads each line of the file, parses the element's name and atomic number, and
 * dynamically resizes the array to accommodate each new element.
 * 
 * @param size Pointer to an integer to store the number of elements read.
 * @param filename Name of the file containing the element data.
 * @return Pointer to an array of ELEMENT structs containing the elements read from the file.
 */
ELEMENT* readFile(int *size, char * filename){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Error! Unable to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    *size=0;
    char *line = (char*)malloc(20);
    if (line == NULL) {
        perror("Memory allocation failed for line");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 10, fp)!=NULL)
        (*size)++;
    
    ELEMENT* elements = (ELEMENT*)malloc((*size) * sizeof(ELEMENT));
    if (elements == NULL) {
        printf("Memory allocation failed for elements!\n");
        free(line);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    rewind(fp);

    int i = 0;

    while (fgets(line, 10, fp)!=NULL){
    
        char *name = malloc(strlen(line)+1);
        if (name==NULL){
            perror("Memory allocation failed for name");
            freeElements(elements, i);
            free(line);
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        int num;
        sscanf(line, "%s %d",name, &num);


        elements[i].num = num;
        elements[i].name = name;
        i++;
        
    }
    free(line);
    
    fclose(fp);

    return elements;
}

/**
 * @brief Checks if a given element name exists in the periodic table.
 * 
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @param str String containing the element name to validate.
 * @return true if the element name exists in the table, false otherwise.
 */
bool isValidElement(ELEMENT *elements, char* str){
    for (int k=0; k<MAX_TABLE_LENGTH;  k++)
        if(strcmp(elements[k].name, str)==0)
            return true;
    return false;
 }

/**
 * @brief Searches for and returns an ELEMENT by name from the periodic table.
 * 
 * If the element name is not found, returns an ELEMENT with a default atomic number of -1.
 * 
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @param str String containing the name of the element to find.
 * @return The ELEMENT struct corresponding to the element name, or a default element if not found.
 */
ELEMENT findElement(ELEMENT *elements, char* str, int size){
   
   ELEMENT emptyElement;
   emptyElement.num = -1;
   emptyElement.name = "\0";
   for (int k=0; k<size;  k++)
        if(strcmp(elements[k].name, str)==0)
            return elements[k];
    return emptyElement;
}

#ifdef DEBUG_PERIODICTABLE

int main() {
    int size;
    char filename[] = "periodicTable.txt";

    ELEMENT *elements = readFile(&size, filename);
    if (elements == NULL) {
        printf("Failed to read elements from file.\n");
        return EXIT_FAILURE;
    }
    printf("Elements read from file:\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", elements[i].name, elements[i].num);
    }

    sortElements(elements, size);
    printf("\nElements sorted by atomic number:\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", elements[i].name, elements[i].num);
    }

    char elementToCheck[] = "O";
    if (isValidElement(elements, elementToCheck)) {
        printf("\n%s is a valid element.\n", elementToCheck);
    } else {
        printf("\n%s is not a valid element.\n", elementToCheck);
    }

    char elementToFind[] = "H";
    ELEMENT foundElement = findElement(elements, elementToFind, size);
    if (foundElement.num != -1) {
        printf("\nFound element %s with atomic number %d.\n", foundElement.name, foundElement.num);
    } else {
        printf("\nElement %s not found.\n", elementToFind);
    }

    freeElements(elements, size);
    printf("\nMemory for elements has been freed.\n");

    return EXIT_SUCCESS;
}
#endif
