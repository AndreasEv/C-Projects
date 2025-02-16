/**
 * @file stack.c
 * @brief Implementation of a stack that stores integers.
 *
 * This file provides functions for initializing, pushing to, popping from, 
 * and displaying a stack designed specifically for integer storage.
 * 
 * @author Andreas Evagorou
 * @date 27/10/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief Initializes an integer stack.
 * 
 * Allocates memory for the stack and sets its top pointer to NULL.
 * 
 * @param stack Double pointer to the STACK structure to initialize.
 * @return EXIT_SUCCESS if initialization is successful, EXIT_FAILURE otherwise.
 */
int initStack(STACK **stack){
    *stack=(STACK*)malloc(sizeof(STACK));
    if ((*stack)==NULL) return EXIT_FAILURE;

    (*stack)->top = NULL;
    (*stack)->size = 0;
    return EXIT_SUCCESS;
}


/**
 * @brief Checks if the integer stack is empty.
 * 
 * @param stack Pointer to the STACK structure.
 * @return true if the stack is empty, false otherwise.
 */
bool isEmptyStack(STACK *stack){
    return (stack->size==0 || stack->top ==NULL)? true : false;
}

/**
 * @brief Retrieves the integer at the top of the stack without removing it.
 * 
 * @param stack Pointer to the STACK structure.
 * @return The integer at the top of the stack, or EXIT_FAILURE if the stack is empty.
 */
int topStack(STACK *stack){

    if (isEmptyStack(stack) ) {
        printf("Empty Stack\n");
        return EXIT_FAILURE;
    }

    return stack->top->data;
}

/**
 * @brief Removes the integer at the top of the stack.
 * 
 * @param stack Pointer to the STACK structure.
 * @return EXIT_SUCCESS if the operation is successful, EXIT_FAILURE if the stack is empty or uninitialized.
 */
int pop(STACK *stack){
    if (stack == NULL){
        printf("The stack isn't initialized\n");
        return EXIT_FAILURE;
    }

    if (isEmptyStack(stack) ) {
        printf("Empty Stack\n");
        return EXIT_FAILURE;
    }

    NODE* temp =  stack->top;
    stack->top = stack->top->next;
    (stack->size)--;
    free(temp);
    return EXIT_SUCCESS;
}

/**
 * @brief Pushes an integer onto the stack.
 * 
 * @param stack Pointer to the STACK structure.
 * @param val The integer to push onto the stack.
 * @return EXIT_SUCCESS if the operation is successful, EXIT_FAILURE if the stack is uninitialized or memory allocation fails.
 */
int push(STACK *stack, int val){

    if (stack == NULL){
        printf("The stack isn't initialized\n");
        return EXIT_FAILURE;
    }

    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode==NULL){
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    newNode->data = val;
    newNode->next = stack->top;
    stack->top = newNode;
    (stack->size)++;
    return EXIT_SUCCESS;
}

/**
 * @brief Prints all integers in the stack from top to bottom.
 * 
 * @param stack Pointer to the STACK structure.
 * @return EXIT_SUCCESS if the stack is printed successfully, EXIT_FAILURE if the stack is empty or uninitialized.
 */
int printStack(STACK *stack){

     if (stack == NULL){
        printf("The stack isn't initialized\n");
        return EXIT_FAILURE;
    }

    if (isEmptyStack(stack)) {
        printf("Empty Stack\n");
        return EXIT_FAILURE;
    }

    NODE* temp = stack->top;
    printf("Print Stack:\n");
    while(temp != NULL){
        printf("%d\n",temp->data);
        temp = temp->next;
    }

    // free(temp);
    return EXIT_SUCCESS;
}

#ifdef DEBUG_STACK
int main() {
    STACK *stack = NULL;

    if (initStack(&stack) == EXIT_SUCCESS) {
        printf("Stack initialized successfully.\n");
    } else {
        printf("Stack initialization failed.\n");
        return EXIT_FAILURE;
    }


    for (int i = 1; i <= 5; i++) {
        push(stack, i * 10);
        printf("Pushed %d onto the stack.\n", i * 10);
    }


    if (printStack(stack) == EXIT_SUCCESS) 
        printf("Stack printed successfully.\n");
    
    printf("Popping elements from the stack\n");
    while (!isEmptyStack(stack)){
        printf("Top: %d\n", topStack(stack));
        pop(stack);
    }

   
    // Free the stack
    free(stack);
    printf("Stack memory freed.\n");

    return EXIT_SUCCESS;
}
#endif
