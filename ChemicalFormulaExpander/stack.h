/**
 * @file stack.h
 * @brief Header file for a stack that stores integers.
 *
 * This file contains the definitions of the NODE and STACK structures and declares functions
 * for initializing, pushing to, popping from, and displaying the stack.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */

#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

/**
 * @struct node
 * @brief Node structure for stack elements.
 *
 * This structure represents a single node in the stack, holding an integer
 * data value and a pointer to the next node.
 */
typedef struct node {
    struct node* next;
    int data;
} NODE;

/**
 * @struct stack
 * @brief Structure representing the stack itself.
 *
 * This structure holds the top pointer to the first node in the stack
 * and tracks the size of the stack.
 */
typedef struct stack {
   NODE* top;
   int size;
} STACK;  

/**
 * @brief Initializes an integer stack.
 * 
 * Allocates memory for the stack and sets its top pointer to NULL.
 * 
 * @param stack Double pointer to the STACK structure to initialize.
 * @return EXIT_SUCCESS if initialization is successful, EXIT_FAILURE otherwise.
 */
int initStack(STACK **stack);

/**
 * @brief Removes the integer at the top of the stack.
 * 
 * @param stack Pointer to the STACK structure.
 * @return EXIT_SUCCESS if the operation is successful, EXIT_FAILURE if the stack is empty or uninitialized.
 */
int pop(STACK *stack);

/**
 * @brief Retrieves the integer at the top of the stack without removing it.
 * 
 * @param stack Pointer to the STACK structure.
 * @return The integer at the top of the stack, or EXIT_FAILURE if the stack is empty.
 */
int topStack(STACK *stack);

/**
 * @brief Checks if the integer stack is empty.
 * 
 * @param stack Pointer to the STACK structure.
 * @return true if the stack is empty, false otherwise.
 */
bool isEmptyStack(STACK *stack);

/**
 * @brief Pushes an integer onto the stack.
 * 
 * @param stack Pointer to the STACK structure.
 * @param val The integer to push onto the stack.
 * @return EXIT_SUCCESS if the operation is successful, EXIT_FAILURE if the stack is uninitialized or memory allocation fails.
 */
int push(STACK *stack, int val);

/**
 * @brief Prints all integers in the stack from top to bottom.
 * 
 * @param stack Pointer to the STACK structure.
 * @return EXIT_SUCCESS if the stack is printed successfully, EXIT_FAILURE if the stack is empty or uninitialized.
 */
int printStack(STACK *stack);

#endif 
