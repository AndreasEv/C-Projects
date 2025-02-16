/**
 * @file latinsquare.c
 * @brief A console-based Latin square puzzle game
 * 
 * This program reads a Latin square from a file, allows the user to play
 * by inserting numbers into the square while adhering to the Latin square rules, 
 * and saves the result back to a file.
 * 
 * @author Andreas Evagorou
 * @date 30/9/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define N 9 ///< Maximum size of the Latin square (N x N)

/**
 * @brief Checks if a number exists in a specific column of the square.
 * 
 * @param square The Latin square.
 * @param size The size of the Latin square.
 * @param col The column to check.
 * @param num The number to check for.
 * @return true if the number exists in the column, false otherwise.
 */
bool checkInCol(int square[N][N], int size, int col, int num)
{
    for (int k = 0; k < size; k++)
        if (abs(square[k][col]) == num && num != 0)
            return true;

    return false;
}

/**
 * @brief Checks if a number exists in a specific row of the square.
 * 
 * @param square The Latin square.
 * @param size The size of the Latin square.
 * @param row The row to check.
 * @param num The number to check for.
 * @return true if the number exists in the row, false otherwise.
 */
bool checkInRow(int square[N][N], int size, int row, int num)
{
    for (int k = 0; k < size; k++)
        if (abs(square[row][k]) == num && num != 0)
            return true;

    return false;
}

/**
 * @brief Validates whether a move is allowed in the Latin square.
 * 
 * @param square The Latin square.
 * @param size The size of the Latin square.
 * @param row The row of the move.
 * @param col The column of the move.
 * @param num The number to insert.
 * @return true if the move is valid, false otherwise.
 */
bool isValidMove(int square[N][N], int size, int row, int col, int num)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        printf("Error! Index out of bounds\n");
        return false;
    }

    if (square[row][col] < 0)
    {
        printf("The value in the %d,%d position cannot change by the user.\nGive a value in a position without () : \n", row + 1, col + 1);
        return false;
    }

    if (num > size || num < 0)
    {
        printf("Illegal value. Give a value again between [1...%d]: \n", size);
        return false;
    }

    if (checkInRow(square, size, row, num))
    {
        printf("The value already exists in the row. Give another value between [1...%d]: \n", size);
        return false;
    }

    if (checkInCol(square, size, col, num))
    {
        printf("The value already exists in the column. Give another value between [1...%d]: \n", size);
        return false;
    }

    return true;
}

/**
 * @brief Checks if the Latin square is fully solved.
 * 
 * @param square The Latin square.
 * @param size The size of the Latin square.
 * @return true if the square is solved, false otherwise.
 */
bool isSolvedSquare(int square[N][N], int size)
{
    for (int k = 0; k < size; k++)
        for (int i = 0; i < size; i++)
            if (square[k][i] == 0)
                return false;

    return true;
}

/**
 * @brief Reads a Latin square from a file.
 * 
 * @param square The Latin square to populate.
 * @param size Pointer to an integer to store the size of the square.
 * @param filename The name of the file to read from.
 */
void readLatinSquare(int square[N][N], int *size, const char *filename)
{
    FILE *fp = NULL;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error! Unable to open file: %s\n", filename);
        exit(-1);
    }

    // Correct fscanf usage to read the size
    if (fscanf(fp, "%d", size) != 1)
    {
        printf("Error reading size");
        fclose(fp);
        exit(-1);
    }

    // Check if the size exceeds the maximum allowed size
    if (*size > N)
    {
        printf("Error! This square has length bigger than 9");
        fclose(fp);
        exit(-1);
    }

    int num;
    for (int k = 0; k < *size; k++)
    {
        for (int i = 0; i < *size; i++)
        {
            // Correct fscanf usage to read integers into num
            if (fscanf(fp, "%d", &num) != 1)
            {
                printf("Error reading number");
                fclose(fp);
                exit(-1);
            }

            // Ensure the number is within valid range
            if (abs(num) <= *size)
                square[k][i] = num; // Correctly access the 2D array
            else
            {
                printf("Error! There is an illegal number in the file");
                fclose(fp);
                exit(-1);
            }
        }
        printf("\n");
    }

    fclose(fp);
}

/**
 * @brief Writes the Latin square to a file.
 * 
 * @param square The Latin square to write.
 * @param size The size of the Latin square.
 * @param input_filename The original input filename (used to create output filename).
 */
void writeLatinSquare(int square[N][N], int size, const char *input_filename)
{
    // Create a new filename by prepending "out-" to the input filename
    char output_filename[100] = "out-";
    strcat(output_filename, input_filename);

    // Open the new file for writing
    FILE *fp = fopen(output_filename, "w");

    if (fp == NULL)
    {
        printf("Error! Unable to open file for writing: %s\n", output_filename);
        exit(-1);
    }

    // Write the size to the file
    fprintf(fp, "%d\n", size);

    // Write the Latin square to the file
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            fprintf(fp, "%d ", square[k][i]);
        }
        fprintf(fp, "\n");
    }

    // Close the file
    fclose(fp);

    printf("Saving to %s\n", output_filename);
}

/**
 * @brief Displays the Latin square in a formatted grid.
 * 
 * @param square The Latin square to display.
 * @param size The size of the Latin square.
 */
void displayLatinSquare(int square[N][N], int size)
{
    for (int k = 0; k < size; k++)
        printf("+-----");

    printf("+\n");

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            if (square[k][i] < 0)
                printf("| (%d) ", abs(square[k][i]));
            else
                printf("|  %d  ", square[k][i]);
        }
        printf("|\n");

        for (int j = 0; j < size; j++)
            printf("+-----");

        printf("+\n");
    }
}

/**
 * @brief Handles the gameplay by allowing the user to enter values into the Latin square.
 * 
 * @param square The Latin square to modify.
 * @param size The size of the Latin square.
 * @return true if the game should continue, false if the user ends the game.
 */
bool play(int square[N][N], int size)
{
    int num, row, col;

    printf("Enter your command in the following format:\n");
    printf(">i,j=val: for entering val at position (i,j)\n");
    printf(">i,j=0 : for clearing cell (i,j)\n");
    printf(">0,0=0 : for saving and ending the game\n");
    printf("Notice: i,j,val numbering is from [1..4]\n");
    printf(">");

    if (scanf("%d,%d=%d", &row, &col, &num) != 3)
    {
        while (getchar() != '\n')
        {
        };
        printf("Wrong format of command\n");
        return true;
    }

    if (row == 0 && col == 0 && num == 0)
        return false;

    row--;
    col--;

    if (isValidMove(square, size, row, col, num))
    {
        square[row][col] = num;
        printf("Value inserted!\n");
    }

    return true;
}

/**
 * @brief The main function that initializes the game, reads the input, and starts the gameplay.
 * 
 * @param argc The argument count.
 * @param argv The argument vector, where the first argument is the input filename.
 * @return 0 on success, -1 on error.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: No input file provided\n");
        return -1;
    }

    int square[N][N] = {0}; // Initialize the array to 0 to avoid garbage values
    int size;
    char *inputFilename = argv[1];

    readLatinSquare(square, &size, inputFilename);

    do{
        displayLatinSquare(square, size);
    } while (play(square, size) && !isSolvedSquare(square, size));

    displayLatinSquare(square, size);

    if (isSolvedSquare(square, size))
        printf("Good Job :)\nYou Solved Latin Square\n\n");
    else
        printf("Unlucky :(\nMaybe Next time\n\n");

    writeLatinSquare(square, size, inputFilename);
    printf("Done\n");

    return 0;
}
