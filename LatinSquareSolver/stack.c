/**
 * @file stack.c
 * @brief C file for the stack methods
 *
 */


#include "stack.h"

int initStack(Stack **stack) {
    // Allocate memory for the stack
    *stack = (Stack *)malloc(sizeof(Stack));
    if (*stack == NULL) {
        printf("[ERROR] Failed to allocate memory for stack\n");
        return EXIT_FAILURE;
    }

    (*stack)->top = NULL; // Initialize the top pointer
    (*stack)->size = 0;   // Initialize the stack size
    return EXIT_SUCCESS;
}

bool isEmpty(Stack *stack) {
    // Check if the stack is empty
    return stack->size == 0;
}

int push(Stack *stack, Node *newNode) {
    if (stack == NULL) {
        printf("[ERROR] Stack is not initialized\n");
        return EXIT_FAILURE;
    }

    if (newNode == NULL) {
        printf("[ERROR] Node is not initialized\n");
        return EXIT_FAILURE;
    }

    // Clone the newNode to ensure its integrity
    Node *pushedNode = cloneNode(newNode);

    // If the stack is empty, set the top to the new node
    if (stack->top == NULL) {
        stack->top = pushedNode;
    } else {
        pushedNode->next = stack->top; // Link the new node to the current top
        stack->top = pushedNode;       // Update the top pointer
    }

    stack->size++; // Increment the stack size
    return EXIT_SUCCESS;
}

int pop(Stack *stack, Node *retNode) {
    if (stack == NULL || isEmpty(stack)) {
        printf("[ERROR] Stack is empty or not initialized\n");
        return EXIT_FAILURE;
    }

    if (retNode == NULL) {
        printf("[ERROR] retNode is not initialized\n");
        return EXIT_FAILURE;
    }

    Node *temp = stack->top;        // Get the top node
    stack->top = temp->next;        // Update the top pointer to the next node
    stack->size--;                  // Decrement the stack size

    // Copy data from the popped node to retNode
    retNode->row = temp->row;
    retNode->col = temp->col;
    retNode->size = temp->size;

    // Allocate memory for retNode's square matrix and moves array
    retNode->square = (int **)malloc(retNode->size * sizeof(int *));
    retNode->moves = (int *)malloc(retNode->size * sizeof(int));
    if (retNode->square == NULL || retNode->moves == NULL) {
        perror("[ERROR] Failed to allocate memory for retNode in pop");
        free(retNode);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < retNode->size; i++) {
        retNode->square[i] = (int *)malloc(retNode->size * sizeof(int));
        if (retNode->square[i] == NULL) {
            perror("[ERROR] Memory allocation failed for row in retNode's square array");
            for (int j = 0; j < i; j++) {
                free(retNode->square[j]);
            }
            free(retNode->square);
            free(retNode->moves);
            return EXIT_FAILURE;
        }
        for (int j = 0; j < retNode->size; j++) {
            retNode->square[i][j] = temp->square[i][j]; // Copy values
        }
    }

    // Copy the moves array
    for (int i = 0; i < retNode->size; i++) {
        retNode->moves[i] = temp->moves[i];
    }

    retNode->next = NULL; // Ensure retNode's next is NULL

    // Free the memory of the popped node
    freeNode(temp);

    return EXIT_SUCCESS;
}

void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        return; // No nodes to print if the stack is empty
    }

    Node *current = stack->top;

    while (current != NULL) {
        // Print the current node's matrix
        printNode(current);

        // If there's a next node, print an arrow
        if (current->next != NULL) {
            int middle = (current->size * 6) / 2; // Center the arrow
            for (int i = 0; i < middle; i++) {
                printf(" ");
            }
            printf("↓\n"); // Print the arrow
        }

        current = current->next; // Move to the next node
    }
}

void freeStack(Stack *stack) {
    if (stack == NULL) {
        printf("[ERROR] Stack is null\n");
        return;
    }

    // Free each node in the stack
    while (stack->top != NULL) {
        Node *temp = stack->top;
        stack->top = stack->top->next;
        freeNode(temp);
    }

    free(stack); // Free the stack structure itself
    stack = NULL; // Avoid dangling pointer
}

#ifdef DEBUG_STACK

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "node.h" // Assuming `Node` and its helpers like `cloneNode` and `freeNode` are defined here

int main() {
    printf("Debugging Stack Implementation...\n");

    Stack *stack = NULL;

    // Test stack initialization
    if (initStack(&stack) != EXIT_SUCCESS) {
        printf("[ERROR] Stack initialization failed\n");
        return EXIT_FAILURE;
    }
    printf("[INFO] Stack initialized successfully\n");

    // Create and push some nodes
    for (int i = 0; i < 3; i++) {
        Node *node = NULL;

        // Initialize a new node
        if (initNode(&node, NULL, 3) != EXIT_SUCCESS) {
            printf("[ERROR] Failed to initialize node %d\n", i);
            continue;
        }

        // Set up the node data
        for (int row = 0; row < node->size; row++) {
            for (int col = 0; col < node->size; col++) {
                node->square[row][col] = i + row + col; // Example data
            }
        }

        if (push(stack, node) == EXIT_SUCCESS) {
            printf("[INFO] Pushed node %d onto the stack\n", i);
        } else {
            printf("[ERROR] Failed to push node %d\n", i);
        }

        freeNode(node); // Free the local copy since `push` clones the node
    }

    // Print the stack
    printf("\n[INFO] Stack after pushing nodes:\n");
    printStack(stack);

    // Pop and print nodes
    while (!isEmpty(stack)) {
        Node *retNode;

        // Initialize the `retNode` for the `pop` operation
        if (initNode(&retNode, NULL, 3) != EXIT_SUCCESS) {
            printf("[ERROR] Failed to initialize retNode for pop\n");
            break;
        }

        if (pop(stack, retNode) == EXIT_SUCCESS) {
            printf("[INFO] Popped node (row: %d, col: %d, size: %d)\n", retNode->row, retNode->col, retNode->size);
            printNode(retNode);
        } else {
            printf("[ERROR] Failed to pop node\n");
        }

        freeNode(retNode); // Free the memory allocated during pop
    }

    // Print the stack after popping
    printf("\n[INFO] Stack after popping all nodes:\n");
    printStack(stack);

    // Free the stack
    freeStack(stack);
    printf("[INFO] Stack freed successfully\n");

    return EXIT_SUCCESS;
}

#endif
