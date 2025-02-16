/**
 * @file node.h
 * @brief Header file for the node of the stack, which stores a 2D dynamically allocated array and more infortation needed for our algorithm.
 */

#ifndef DEF_H
#define DEF_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @struct Node
 * @brief Represents a node for solving a Latin Square.
 */
typedef struct Node {
    /**
     * @brief 2D array for the Latin Square.
     */
    int **square;

    /**
     * @brief Size of the Latin Square (NxN).
     */
    int size;

    /**
     * @brief Row of the last placed number.
     */
    int row;

    /**
     * @brief Column of the last placed number.
     */
    int col;

    /**
     * @brief Array of valid moves.
     */
    int *moves;

    /**
     * @brief Pointer to the next node in the stack or list.
     */
    struct Node *next;
} Node;


/**
 * @brief Prints the entire 2D array to the console.
 *
 * @param node A pointer to the Node to be printed.
 */
void printNode(Node *node);

/**
 * @brief Initializes a new Node structure.
 *
 * Allocates memory for a new Node, including its matrix (`square`)
 * and auxiliary data. If `node` is provided, its data is copied to the new Node.
 * 
 * @param newNode Pointer to the pointer of the Node being initialized.
 * @param node Pointer to an existing Node to copy data from, or NULL.
 * @param size Size of the square matrix (NxN).
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on memory allocation failure.
 */
int initNode(Node **newNode, Node *node, int size);

/**
 * @brief Updates the Node with a new value at the specified position.
 *
 * Updates the matrix value and resets the `moves` array.
 *
 * @param node Pointer to the Node to be updated.
 * @param row Row index of the value to update.
 * @param col Column index of the value to update.
 * @param num Value to place in the matrix.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if `node` is NULL.
 */
int updateNode(Node *node, int row, int col, int num);

/**
 * @brief Frees the memory associated with a Node.
 *
 * Releases all dynamically allocated memory, including the matrix, moves array,
 * and the Node itself.
 *
 * @param node Pointer to the Node to be freed.
 */
void freeNode(Node *node);

/**
 * @brief Creates a copy of an existing Node.
 *
 * Deep copies the `square` matrix and `moves` array into a new Node.
 *
 * @param node Pointer to the Node to clone.
 * @return Pointer to the cloned Node, or NULL if memory allocation fails.
 */
Node *cloneNode(Node *node);

#endif
