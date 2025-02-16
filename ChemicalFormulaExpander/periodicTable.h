/**
 * @file periodicTable.h
 * @brief Header file for managing a periodic table of elements.
 *
 * This file contains the definition of the ELEMENT structure and declares functions
 * for sorting, reading, validating, and finding elements, as well as freeing memory.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#include <stdbool.h>

#define MAX_TABLE_LENGTH 118 /**< Maximum number of elements in the periodic table */

/**
 * @struct ELEMENT
 * @brief Structure representing an element in the periodic table.
 *
 * Contains the name and atomic number of an element.
 */
typedef struct {
    char *name; /**< Element name (e.g., "H" for Hydrogen) */
    int num;    /**< Atomic number of the element */
} ELEMENT;

/**
 * @brief Sorts an array of ELEMENT structs by atomic number in ascending order.
 * 
 * @param elements Array of ELEMENT structs to sort.
 * @param size The number of elements in the array.
 */
void sortElements(ELEMENT *elements, int size);

/**
 * @brief Frees memory allocated for an array of ELEMENT structs.
 * 
 * Deallocates each element's name and then the array itself.
 * 
 * @param elements Array of ELEMENT structs to free.
 * @param size The number of elements in the array.
 */
void freeElements(ELEMENT* elements, int size);

/**
 * @brief Reads elements from a file and stores them in a dynamically allocated array.
 * 
 * Reads each line of the file, parsing the element's name and atomic number, and
 * resizes the array to accommodate each new element.
 * 
 * @param size Pointer to an integer to store the number of elements read.
 * @param filename Name of the file containing the element data.
 * @return Pointer to an array of ELEMENT structs with the elements read from the file.
 */
ELEMENT* readFile(int *size, char *filename);

/**
 * @brief Checks if a given element name exists in the periodic table.
 * 
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @param str String containing the element name to validate.
 * @return true if the element name exists in the table, false otherwise.
 */
bool isValidElement(ELEMENT *elements, char* str);

/**
 * @brief Searches for and returns an ELEMENT by name from the periodic table.
 * 
 * Returns an ELEMENT with an atomic number of -1 if not found.
 * 
 * @param elements Array of ELEMENT structs representing the periodic table.
 * @param str String containing the name of the element to find.
 * @return The ELEMENT struct corresponding to the element name, or a default element if not found.
 */
ELEMENT findElement(ELEMENT *elements, char* str, int size);

#endif
