/**
 * @file stack.h
 * @brief Header file for the stack data structure, which stores nodes containing 2D dynamically allocated arrays.
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "node.h"

/**
 * @struct Stack
 * @brief Represents a stack of nodes.
 *
 * A stack that stores nodes, each containing a 2D array and related metadata.
 */
typedef struct {
    Node *top; ///< Pointer to the top node in the stack.
    int size;  ///< Number of elements currently in the stack.
} Stack;

/**
 * @brief Initializes a new stack.
 *
 * Allocates memory for a stack and sets its initial state.
 *
 * @param stack A double pointer to the stack to be initialized.
 * @return int Returns 0 on success or an error code on failure.
 */
int initStack(Stack **stack);

/**
 * @brief Checks if the stack is empty.
 *
 * Determines whether the stack contains any elements.
 *
 * @param stack A pointer to the stack.
 * @return bool Returns true if the stack is empty, false otherwise.
 */
bool isEmpty(Stack *stack);

/**
 * @brief Pushes a new node onto the stack.
 *
 * Creates a copy of the provided node and adds it to the top of the stack.
 *
 * @param stack A pointer to the stack.
 * @param value A pointer to the node to be pushed.
 * @return int Returns 0 on success or an error code on failure.
 */
int push(Stack *stack, Node *value);

/**
 * @brief Removes the top node from the stack.
 *
 * Retrieves and removes the top node from the stack, copying its contents to the provided node.
 *
 * @param stack A pointer to the stack.
 * @param retNode A pointer to the node where the popped element's data will be stored.
 * @return int Returns 0 on success or an error code on failure.
 */
int pop(Stack *stack, Node *retNode);

/**
 * @brief Prints the contents of the stack.
 *
 * Traverses the stack and prints each node's data, including its 2D array, to the console.
 *
 * @param stack A pointer to the stack to be printed.
 */
void printStack(Stack *stack);

/**
 * @brief Frees all memory associated with the stack.
 *
 * Deallocates all nodes and their associated data, as well as the stack structure itself.
 *
 * @param stack A pointer to the stack to be freed.
 */
void freeStack(Stack *stack);

#endif // STACK_H
