/*Purpose of code: This code prompts the user to create their own square or non square matrix by reading in float numbers
                   from a given text file. The dimensions of the matrix depend on the user input for the number of rows
                   and columns. The program will prompt the user to select a 2x2 subset matrix from the original matrix. The
                   user will be able to extract the desired 2x2 matrix by telling the program the exact location of the
                   matrix. This is done by once again typing in the row and column number. Finally the program will
                   calculate and display the determinant and the inverse of the matrix.
Name: Zaid Daghash
Date Written: 20/03/2022 */


#include <stdio.h>

struct matrix /*Defining a structure.*/
{
    float mValues[10][10]; /*Stores elements of a matrix up to 10x10.*/
    int nrows; /*Stores the number of rows.*/
    int ncols; /*Stores the number of columns.*/
};

void matrixInput(struct matrix *mat, FILE *in); /*Function prototype for a void function ('matrixInput').*/
void matrixDisplay(struct matrix mat); /*Function prototype for a void function ('matrixDisplay').*/
float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check); /*Function prototype for a float function ('matrixDeterminant').*/
void matrixInverse(struct matrix m2, float determinant, struct matrix *m3); /*Function prototype for a void function ('matrixInverse').*/


void main()
{
    struct matrix A; /*Declaring a structure variable 'A' of type matrix for storing the original matrix.*/
    struct matrix B; /*Declaring a structure variable 'B' of type matrix for storing the 2x2 matrix.*/
    struct matrix C; /*Declaring a structure variable 'C' of type matrix for storing the inverse matrix.*/
    float determinant,inverse; /*Declaring float variables for storing the determinant and inverse matrix.*/
    int check,i,j,stop=1; /*Declaring integers for storing the row & column values (i & j),for determining how the inverse will be displayed (check), and for looping the program (stop).*/
    FILE *in; /*Declaring 'in' as a file pointer.*/

    in=fopen("matrix1.txt","r"); /*Opening the file for reading.*/

    if (in==NULL) /*Checking if the file exists.*/
    {
        printf("Error: File does not exist."); /*If the file does not exist, an error message will be displayed.*/
    }
    else /*If the file does exist, carry on with the rest of the program.*/
    {
        do /*Using a 'do-while' loop for looping the program.*/
        {
            in=fopen("matrix1.txt","r"); /*Opening the file for reading again.*/

            matrixInput(&A,in); /*Calling the function 'matrixInput' to allow the user to select the dimensions of the matrix.*/
            fclose(in); /*Closing the file.*/
            matrixDisplay(A); /*Calling the function 'matrixDisplay' for displaying the original matrix.*/
            determinant=matrixDeterminant(A,&B,&check); /*Calling the function 'matrixDeterminant' for calculating the determinant.*/

            if(check==0) /*Catering for the condition where the original matrix is less than 2x2 (check=0).*/
            {
                if (A.nrows==1 && A.ncols==1) /*Catering for the condition where the matrix is a 1x1.*/
                {
                    determinant=A.mValues[0][0]; /*Determinant is equal to the one and only element.*/
                    printf("\nThe determinant is:\n\n%.2f\n",determinant); /*Printing the determinant.*/
                    inverse=1/determinant; /*Calculating the inverse of the 1x1 matrix.*/
                    printf("\nThe inverse of the matrix is:\n\n|     %.2f      |\n",inverse); /*Printing the inverse.*/
                }
                else /*Catering for the condition where the matrix is less than 2x2 and not 1x1.*/
                {
                    printf("\nError: No square matrices have been found, therefore the determinant can't be calculated.\n"); /*Printing an error message.*/
                }
            }
            else /*If check is not equal to '0'(matrix is greater than or equal to 2x2), carry on with the rest of the program.*/
            {
                printf("\nThe determinant is %.2f for the following 2x2 matrix:\n\n", determinant); /*Printing the determinant.*/

                for( i=0; i<2; i++ ) /*Using nested 'for' loops in-order to Print the 2x2 matrix.*/
                {
                    printf("|  "); /*Placing vertical bars to the left of the matrix.*/
                    for(j=0; j<2; j++)
                    {
                        printf("%8.2f",B.mValues[i][j]); /*Printing the 2x2 matrix.*/
                    }
                printf("\t|\n"); /*Placing vertical bars to the right of the matrix.*/
                }

                if (check==2) /*Checking if the determinant is 0 (check=2).*/
                {
                    printf("\nError: The inverse can't be calculated.\n"); /*Printing an error message if the inverse can't be found due to the determinant being equal to 0.*/
                }
                else if (check==1) /*Checking if the determinant is not equal to 0 (check=1). If yes, then carry on with the rest of the program.*/
                {
                    matrixInverse(B,determinant,&C); /*Calling the function 'matrixInverse' for calculating the inverse of the 2x2 matrix.*/

                    printf("\nThe inverse of the matrix is:\n\n");
                    for (i=0; i<C.nrows; i++) /*Using nested 'for' loops in-order to Print the inverse of the 2x2 matrix.*/
                    {
                        printf("|  "); /*Placing vertical bars to the left of the matrix.*/
                        for (j=0; j<C.ncols; j++)
                        {
                            printf("%8.2f",C.mValues[i][j]); /*Printing the inverse of the 2x2 matrix.*/
                        }
                    printf("\t|\n"); /*Placing vertical bars to the right of the matrix.*/
                    }
                }
            }

            fflush(stdin); /*Clearing the memory buffer.*/

            do
            {
                printf("\nWould you like to input another matrix (type '1' for yes or '0' for no): "); /*Prompting the user to re-run the program.*/
                scanf("%d",&stop);
                if (stop<0 || stop>1) /*Checking if the user input is withing the range.*/
                {
                    printf("\nError: Invalid input.\n"); /*Printing an error message if the user input is outside of the range.*/
                }
            }
            while(stop<0 || stop>1);
        }
        while(stop==1); /*The program will restart if the user types '1', and ends if the user types '0'.*/
    }
}

void matrixInput(struct matrix *mat, FILE *in) /*Function for inputting the dimension of the original matrix.*/
{
    struct matrix m1; /*Declaring a structure variable 'm1' of type matrix for storing the original matrix (This is local to the function only).*/
    int i, j; /*'i' controls the number of rows, and 'j' controls the number of columns.*/
    float z; /*'z' will be used to store the float numbers from the file.*/
    FILE *fin;/*Declaring 'fin' as a file pointer (local to this function).*/
    fin=in; /*Setting the pointer 'fin' equal to the pointer 'in'.*/

    do
    {
        printf("Please enter the desired number of rows (Between 1 & 10): "); /*Prompting the user to choose how many rows they would like.*/
        scanf("%d",&m1.nrows);
        if (m1.nrows<1 || m1.nrows>10) /*Checking if the user input is within the range.*/
        {
            printf("\nError: Invalid input.\n\n"); /*Printing an error message if the user input is outside of the range.*/
        }
    }
    while(m1.nrows<1 || m1.nrows>10);

    do
    {
        printf("Please enter the desired number of columns (Between 1 & 10): "); /*Prompting the user to choose how many columns they would like.*/
        scanf("%d",&m1.ncols);
        if (m1.ncols<1 || m1.ncols>10) /*Checking if the user input is within the range.*/
        {
            printf("\nError: Invalid input.\n\n"); /*Printing an error message if the user input is outside of the range.*/
        }
    }
    while(m1.ncols<1 || m1.ncols>10);

    mat->nrows=m1.nrows; /*Setting the rows in the pointer 'mat' equal to the rows of the local variable 'm1'.*/
    mat->ncols=m1.ncols; /*Setting the columns in the pointer 'mat' equal to the rows of the local variable 'm1'.*/

    for(i=0; i<m1.nrows; i++) /*Using nested 'for' loops in-order to read the numbers from the file and store them in the original matrix.*/
    {
        for(j=0; j<m1.ncols; j++)
        {
            fscanf(fin, "%f", &z); /*Reading the numbers from the file.*/
            m1.mValues[i][j]=z; /*Setting the elements in the matrix 'm1' equal to the numbers that have been read from the file.*/
            mat->mValues[i][j]=m1.mValues[i][j]; /*Setting the elements in the matrix pointer 'mat' equal to the elements of the local matrix variable 'm1'.*/
        }
    }
}

void matrixDisplay(struct matrix mat) /*Function for displaying the original matrix.*/
{
    int i, j; /*'i' controls the number of rows, and 'j' controls the number of columns.*/

    printf("\nThe matrix is:\n\n"); /*Printing the original matrix.*/

    for(i=0; i<mat.nrows; i++) /*Using nested 'for' loops in-order to print the original matrix.*/
    {
        printf("|  "); /*Placing vertical bars to the left of the matrix.*/
        for(j=0; j<mat.ncols; j++)
        {
            printf("%8.2f", mat.mValues[i][j]); /*Printing the original matrix.*/
        }
        printf("\t|\n"); /*Placing bars to the right of the matrix.*/
    }
}

float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check) /*Function for calculating and returning the determinant of the 2x2 matrix.*/
{
    struct matrix m3; /*Declaring a structure variable 'm3' of type matrix for storing the 2x2 matrix (This is local to the function only).*/
    int i, j,condition; /*'i' controls the number of rows, and 'j' controls the number of columns. The variable 'condition' will be used as an indicator to the different scenarios when calculating the determinant.*/
    float determinant; /*Variable 'determinant' will be used to store the determinant, 'diagonalL' represents the product of the top left and bottom right elements of the 2x2 matrix. 'diagonalR' represents the product of the top right and bottom left elements of the 2x2 matrix.*/
    int x=m1.nrows-2,y=m1.ncols-2; /*Declaring x and y as integer variables. x will be used to choose the row number, and y will be used to choose the column number. This is done to determine the location of the 2x2 matrix.*/

    m3.nrows=m2->nrows; /*Setting the rows in the pointer 'm2' equal to the rows of the local variable 'm3'.*/
    m3.ncols=m2->ncols; /*Setting the columns in the pointer 'm2' equal to the rows of the local variable 'm3'.*/

    if (m1.nrows==1 || m1.ncols==1) /*This if statement caters for the condition when the original matrix is less than 2x2.*/
    {
        condition=0;/*Setting the variable condition equal to 0.*/
        *check=condition;/*Setting the pointer 'check' equal to the variable 'condition'.*/
    }
    else if (m1.nrows==2 && m1.ncols==2) /*This if statement caters for the condition when the original matrix is a 2x2.*/
    {
        printf("\nWarning: Only one 2x2 matrix can be selected.\n"); /*Warning the user that they can choose only one 2x2 matrix.*/

        do
        {
            printf("\nPlease enter '0' for the row number: "); /*Prompting the user to enter the row number.*/
            scanf("%d",&m3.nrows);
            if (m3.nrows<0 || m3.nrows>0) /*Checking the row number is in range*/
            {
                printf("\nError: Invalid input.\n"); /*Printing an error message if the value is out of range.*/
            }
        }
        while(m3.nrows<0||m3.nrows>0);

        do
        {
            printf("Please enter '0' for the column number: "); /*Prompting the user to enter the column number.*/
            scanf("%d",&m3.ncols);
            if (m3.ncols<0 || m3.ncols>0) /*Checking the column number is in range*/
            {
                printf("\nError: Invalid input.\n"); /*Printing an error message if the value is out of range.*/
            }
        }
        while(m3.ncols<0||m3.ncols>0);

        for( i=0; i<2; i++ ) /*Using nested 'for' loops in-order to extract the 2x2 matrix from the original matrix and store it in a new structure.*/
        {
            for(j=0; j<2; j++)
                {
                    m3.mValues[i][j]=m1.mValues[i+m3.nrows][j+m3.ncols]; /*Setting the elements in the matrix m3 equal to the elements of the original matrix with the addition of the number of rows and columns of 'm3'.*/
                    m2->mValues[i][j]=m3.mValues[i][j]; /*Setting the elements in the pointer matrix 'm2' equal to the local variable matrix 'm3'.*/
                }
        }

        determinant=(m3.mValues[0][0])*(m3.mValues[1][1])-(m3.mValues[0][1]*m3.mValues[1][0]); /*Calculating the determinant.*/

        if (determinant==0) /*Scenario when the determinant is equal to '0'.*/
        {
            condition=2; /*Setting the variable 'condition' equal to '2'.*/
            *check=condition; /*Setting the pointer 'check' equal to the variable 'condition'.*/
        }
        else if (determinant!=0) /*Scenario when the determinant is not equal to '0'.*/
        {
            condition=1; /*Setting the variable 'condition' equal to '1'.*/
            *check=condition; /*Setting the pointer 'check' equal to the variable 'condition'.*/
        }
    }
    else /*If the original matrix is greater than 2x2, then carry on with the rest of the program.*/
    {
        do
        {
            printf("\nPlease enter the desired row number in-order to locate the 2x2 matrix (number must be between 0 and %d): ", x); /*Prompting the user to enter the row number.*/
            scanf("%d",&m3.nrows);
            if (m3.nrows<0 || m3.nrows>x) /*Checking the row number is in range*/
            {
                printf("\nError: Invalid input.\n"); /*Printing an error message if the value is out of range.*/
            }
        }
        while(m3.nrows<0||m3.nrows>x);

        do
        {
            printf("Please enter the desired column number in-order to locate the 2x2 matrix (number must be between 0 and %d): ", y); /*Prompting the user to enter the column number.*/
            scanf("%d",&m3.ncols);
            if (m3.ncols<0 || m3.ncols>y) /*Checking the column number is in range*/
            {
                printf("\nError: Invalid input.\n"); /*Printing an error message if the value is out of range.*/
            }
        }
        while(m3.ncols<0||m3.ncols>y);

        for( i=0; i<2; i++ ) /*Using nested 'for' loops in-order to extract the 2x2 matrix from the original matrix and store it in a new structure.*/
        {
            for(j=0; j<2; j++)
                {
                    m3.mValues[i][j]=m1.mValues[i+m3.nrows][j+m3.ncols]; /*Setting the elements in the matrix m3 equal to the elements of the original matrix with the addition of the number of rows and columns of 'm3'.*/
                    m2->mValues[i][j]=m3.mValues[i][j]; /*Setting the elements in the pointer matrix 'm2' equal to the local variable matrix 'm3'.*/
                }
        }

        determinant=(m3.mValues[0][0])*(m3.mValues[1][1])-(m3.mValues[0][1]*m3.mValues[1][0]); /*Calculating the determinant.*/

        if (determinant==0) /*Scenario when the determinant is equal to '0'.*/
        {
            condition=2; /*Setting the variable 'condition' equal to '2'.*/
            *check=condition; /*Setting the pointer 'check' equal to the variable 'condition'.*/
        }
        else if (determinant!=0) /*Scenario when the determinant is not equal to '0'.*/
        {
            condition=1; /*Setting the variable 'condition' equal to '1'.*/
            *check=condition; /*Setting the pointer 'check' equal to the variable 'condition'.*/
        }
    }
    return determinant; /*Returning the value of the determinant to main.*/
}

void matrixInverse(struct matrix m2, float determinant, struct matrix *m3) /*Function for finding the inverse of the 2x2 matrix.*/
{
    int i, j; /*'i' controls the number of rows, and 'j' controls the number of columns.*/
    struct matrix m4; /*Declaring a structure variable 'm4' of type matrix for storing the inverse matrix (This is local to the function only).*/
    float adjugate[2][2]; /*Declaring a variable for storing the adjugate of the 2x2 matrix.*/

    adjugate[0][0]=m2.mValues[1][1]; /*Setting the first element in the 'adjugate' matrix equal to the last element of the 2x2 matrix.*/
    adjugate[0][1]=-m2.mValues[0][1]; /*Setting the second element in the 'adjugate' matrix equal to the negative value of the second element of the 2x2 matrix.*/
    adjugate[1][0]=-m2.mValues[1][0]; /*Setting the third element in the 'adjugate' matrix equal to the negative value of the third element of the 2x2 matrix.*/
    adjugate[1][1]=m2.mValues[0][0]; /*Setting the fourth element in the 'adjugate' matrix equal to the first element of the 2x2 matrix.*/

    m4.nrows=2; /*Setting the rows of the local matrix 'm4' equal to 2.*/
    m4.ncols=2; /*Setting the columns of the local matrix 'm4' equal to 2.*/
    m3->nrows=m4.nrows; /*Setting the rows in the pointer matrix 'm3' equal to the rows of the local matrix 'm4'.*/
    m3->ncols=m4.ncols; /*Setting the columns in the pointer matrix 'm3' equal to the rows of the local matrix 'm4'.*/

    printf("\nFinding the inverse of the 2x2 matrix...\n");

    for (i=0; i<m4.nrows; i++) /*Using nested 'for' loops in-order to calculate the inverse of the 2x2 matrix and store it a new structure.*/
    {
        for (j=0; j<m4.ncols; j++)
        {
            m4.mValues[i][j]=(adjugate[i][j])/determinant; /*Calculating the inverse and storing it in the local matrix 'm4'.*/
            m3->mValues[i][j]=m4.mValues[i][j]; /*Setting the elements in the pointer matrix 'm3' equal to the elements of the local matrix 'm4'.*/
        }
    }
}



