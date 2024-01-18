/*Purpose of code: This program emulates a typical calculator. It can carry out lots of calculations just like a normal calculator would (addition, subtraction, multiplication, division, etc),
                   and there are also extra calculations that it can perform (matrix operations, solving quadratic equations, etc). The user is greeted with a main menu where they can choose one of the options depending on the
                   calculation they would like to carry out. The user might also be met with a sub-menu after choosing one of the options (depends on the option). After the calculation has been
                   performed, the user would be asked if they would like to carry out a calculation of the same type. If the user decides not to carry out a calculation of the same type, they will
                   be asked if they would like to return to the main menu. If the user chooses not to return to the main menu, the program will terminate. The program checks for correct input at every
                   instance where the user is prompted to enter information using the keyboard, and the user will be prompted to enter the information again if the input is incorrect (checking out of range vales, checking type of input).
                   You are free to alter the height of the console, but please keep the width to its default position as the program has been coded to be visually pleasing for the default width of the console.
/*Author: Zaid Daghash
/*Date written: 18/04/2022 */

#include <stdio.h>
#include <windows.h>
#include <math.h>

struct MatrixOp /*Defining 'MatrixOp' as a structure*/
{
    float elements[10][10]; /*Stores elements of matrix up to 10x10*/
    int rows; /*Stores the number of rows*/
    int cols; /*Stores the number of columns*/
};

/*Function prototypes*/
void empty_std_buffer(); /*Clears stdn so that the program does not loop endlessly after a char or string has been entered*/
void main_menu(int *scanfvalue, int *response); /*Displays the main menu*/
void addition(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response); /*Displays addition menu and carries out addition of numbers*/
void subtraction(int *scanfvalue, int *scanfvalue2, int *response); /*Displays subtraction menu and carries out subtraction of numbers*/
void multiplication(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response); /*Displays multiplication menu and multiplies numbers together*/
void division(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response); /*Displays division menu and divides two numbers*/
void matrixoperationsmenu(int *scanfvalue, int *response); /*Displays the 'Matrix operations' menu*/
void addmatrices(struct MatrixOp sum[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Matrix addition' menu and finds the sum of two matrices*/
void subtractmatrices(struct MatrixOp difference[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Matrix subtraction' menu and finds the difference of two matrices*/
void multiplymatrices(struct MatrixOp times[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Matrix multiplication' menu and finds the product of two matrices*/
void DandImatrix(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Determinant & inverse of a matrix' menu and finds the determinant and inverse of a given matrix*/
void transposematrix(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response); /*Displays the 'Transpose of a matrix' menu and find the transpose of a given matrix*/
void quadeqs(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Quadratic equation solver' and finds the roots of a quadratic equation*/
void squareroot(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Square root' menu and finds the square root of a number*/
void raisetopower(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response); /*Displays the 'Raise to a power' menu and raises a certain number to a certain power*/
void trigmenu(int *scanfvalue, int *response); /*Displays the 'Trigonometric functions' menu*/
void sine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Sine' menu and computes arguments of sin*/
void cosine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Cosine' menu and computes arguments of cos*/
void tangent(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Tangent' menu and computes arguments of tan*/
void arcsine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Arc-sine' menu and computes arguments for the inverse of sin*/
void arccosine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Arc-cosine' menu and computes arguments for the inverse of cos*/
void arctangent(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Arc-tangent' menu and computes arguments for the inverse of tan*/
void hsine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Hyperbolic sine' menu and computes arguments for sinh*/
void hcosine(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Hyperbolic cosine' menu and computes arguments for cosh*/
void htangent(int *scanfvalue, int *scanfvalue2, int *response); /*Displays the 'Hyperbolic tangent' menu and computes arguments for tanh*/
void logarithm(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response); /*Displays the 'Logarithm' menu and computes the logarithm of base 10 or base e*/

void main()
{
    struct MatrixOp matrixinfo[3]; /*Declaring an array of structures with the name 'matrixinfo' of type 'MatrixOp'*/

    int choice, stop, answer, response, status; /*Variables for looping different parts of the program*/
    int savescanf = 0, savescanf1 = 0, savescanf2 = 0, savescanf3 = 0, savescanf4 = 0, savescanf5 = 0, savescanf6 = 0; /*Variables for checking the input type of the 'scanf' function*/

    FILE *fIN;

    system("color 30"); /*Changing the color of the system to be a green background with black text*/

    fIN=fopen("options.txt","r");

    if(fIN==NULL) /*Checking if the file exists*/
    {
        printf("Error: File doesn't exist");
    }
    else
    {
        do
        {
            main_menu(&savescanf,&choice); /*Calling the 'main_menu' function*/

            if (choice==1) /*Taking user input to decide type of calculation*/
            {
                do
                {
                    addition(&savescanf,&savescanf1,&savescanf2,&answer); /*Calling the 'addition' function*/

                }while(answer==1);
            }
            else if (choice==2)
            {
                do
                {
                    subtraction(&savescanf,&savescanf1,&answer); /*Calling the 'subtraction' function*/

                }while(answer==1);
            }
            else if (choice==3)
            {
                do
                {
                    multiplication(&savescanf,&savescanf2,&savescanf3,&answer); /*Calling the 'multiplication' function*/

                }while(answer==1);
            }
            else if (choice==4)
            {
                do
                {
                    division(&savescanf,&savescanf1,&savescanf2,&answer); /*Calling the 'division' function*/

                }while(answer==1);
            }
            else if (choice==5)
            {
                FILE *fo;
                fo=fopen("matrixoperationsmenu.txt","r");

                if (fo==NULL) /*Checking if the file exists*/
                {
                    system("cls");
                    printf("%*s",60+strlen("Error: File doesn't exist.")/2, "Error: File doesn't exist.", 60-strlen("Error: File doesn't exist.")/2, ""); /*Printing an error message in the center of the console if the file does not exist*/
                }
                else
                {
                    do
                    {
                        matrixoperationsmenu(&savescanf,&response); /*Calling the 'matrixoperationsmenu' function*/

                        if (response==1)
                        {
                            do
                            {
                                addmatrices(matrixinfo,&savescanf,&savescanf1,&savescanf2,&savescanf3,&status); /*Calling the 'addmatrices' function*/

                            }while(status==1);
                        }
                        else if (response==2)
                        {
                            do
                            {
                                subtractmatrices(matrixinfo,&savescanf,&savescanf1,&savescanf2,&savescanf3,&status); /*Calling the 'subtractmatrices' function*/

                            }while(status==1);
                        }
                        else if (response==3)
                        {
                            do
                            {
                                multiplymatrices(matrixinfo,&savescanf,&savescanf1,&savescanf2,&savescanf3,&status); /*Calling the 'multiplymatrices' function*/

                            }while(status==1);
                        }
                        else if (response==4)
                        {
                            do
                            {
                                DandImatrix(&savescanf,&savescanf1,&savescanf2,&savescanf3,&status); /*Calling the 'DandImatrix' function*/

                            }while(status==1);
                        }
                        else
                        {
                            do
                            {
                                transposematrix(&savescanf,&savescanf1,&savescanf2,&status); /*Calling the 'transposematrix' function*/

                            }while (status==1);
                        }

                        fflush(stdin); /*Clearing the buffer*/
                        printf("\n________________________________________________________________________________________________________________________\n");

                        do
                        {
                            printf("%*s",60+strlen("Would you like to return to the 'Matrix operations' menu? (1 for yes, 0 for no): ")/2, "Would you like to return to the 'Matrix operations' menu? (1 for yes, 0 for no): ", 60-strlen("Would you like to return to the 'Matrix operations' menu? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to return to the 'Matrix operations' menu*/
                            savescanf4=scanf("%d",&answer);

                            if (savescanf4==0 || answer<0 || answer>1) /*Checking the user input*/
                            {
                                printf("\n");
                                printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
                                printf("\n\n");
                                empty_std_buffer(); /*Calling the 'empty_std_buffer' in order to read all elements the user has typed in case a char or string has been entered. This stops the program from looping endlessly*/
                            }
                            else
                            {
                                empty_std_buffer();
                            }

                        }while(savescanf4==0 || answer<0 || answer>1);

                    }while(answer==1);
                }
            }
            else if (choice==6)
            {
                do
                {
                    quadeqs(&savescanf,&savescanf1,&savescanf2,&savescanf3,&answer); /*Calling the 'quadeqs' function*/

                }while(answer==1);
            }
            else if (choice==7)
            {
                do
                {
                    squareroot(&savescanf,&savescanf1,&answer); /*Calling the 'squareroot' function*/

                }while(answer==1);
            }
            else if (choice==8)
            {
                do
                {
                    raisetopower(&savescanf,&savescanf1,&savescanf2,&savescanf3,&answer); /*Calling the 'raisetopower' function*/

                }while(answer==1);
            }
            else if (choice==9)
            {
                FILE *fo;
                fo=fopen("trigoptions.txt","r");

                if (fo==NULL) /*Checking if the file exists*/
                {
                    system("cls");
                    printf("%*s",60+strlen("Error: File doesn't exist.")/2, "Error: File doesn't exist.", 60-strlen("Error: File doesn't exist.")/2, ""); /*Printing an error message in the center of the console if the file does not exist*/
                }
                else
                {
                    do
                    {
                        int tf,status; /*'tf' represents the user's choice out of the options given, status is used to loop back to the 'Trigonometric functions' menu*/

                        trigmenu(&savescanf,&tf); /*Calling the 'trigmenu' function*/

                        if (tf==1)
                        {
                            do
                            {
                                sine(&savescanf,&savescanf1,&status); /*Calling the 'sine' function*/

                            }while(status==1);
                        }
                        else if (tf==2)
                        {
                            do
                            {
                                cosine(&savescanf,&savescanf1,&status); /*Calling the 'cosine' function*/

                            }while(status==1);
                        }
                        else if (tf==3)
                        {
                            do
                            {
                                tangent(&savescanf,&savescanf1,&status); /*Calling the 'tangent' function*/

                            }while(status==1);
                        }
                        else if (tf==4)
                        {
                            do
                            {
                                arcsine(&savescanf,&savescanf1,&status); /*Calling the 'arcsine' function*/

                            }while(status==1);
                        }
                        else if (tf==5)
                        {
                            do
                            {
                                arccosine(&savescanf,&savescanf1,&status); /*Calling the 'arccosine' function*/

                            }while(status==1);

                        }
                        else if (tf==6)
                        {
                            do
                            {
                                arctangent(&savescanf,&savescanf1,&status); /*Calling the 'arctangent' function*/

                            }while(status==1);

                        }
                        else if (tf==7)
                        {
                            do
                            {
                                hsine(&savescanf,&savescanf1,&status); /*Calling the 'hsine' function*/

                            }while(status==1);
                        }
                        else if (tf==8)
                        {
                            do
                            {
                                hcosine(&savescanf,&savescanf1,&status); /*Calling the 'hcosine' function*/

                            }while(status==1);
                        }
                        else
                        {
                            do
                            {
                                htangent(&savescanf,&savescanf1,&status); /*Calling the 'htangent' function*/

                            }while(status==1);
                        }
                        fflush(stdin); /*Clearing the buffer*/
                        printf("\n________________________________________________________________________________________________________________________\n");

                        do
                        {
                            printf("%*s",60+strlen("Would you like to return to the 'Trigonometric function' menu? (1 for yes, 0 for no): ")/2, "Would you like to return to the 'Trigonometric function' menu? (1 for yes, 0 for no): ", 60-strlen("Would you like to return to the 'Trigonometric function' menu? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to return to the 'Trigonometric functions' menu*/
                            savescanf5 = scanf("%d",&answer);

                            if (savescanf5==0 || answer<0 || answer>1) /*Checking the user input*/
                            {
                                printf("\n");
                                printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
                                printf("\n\n");
                                empty_std_buffer(); /*Calling the 'empty_std_buffer' in order to read all elements the user has typed in case a char or string has been entered. This stops the program from looping endlessly*/
                            }
                            else
                            {
                                empty_std_buffer();
                            }

                        }while(savescanf5==0 || answer<0 || answer>1);

                    }while(answer==1);
                }
            }
            else
            {
                do
                {
                    logarithm(&savescanf,&savescanf1,&savescanf2,&answer); /*Calling the 'logarithm' function*/

                }while(answer==1);
            }

            fflush(stdin); /*Clearing the buffer*/
            printf("\n________________________________________________________________________________________________________________________\n");
            do
            {
                printf("%*s",60+strlen("Would you like to return to the main menu? (1 for yes, 0 to exit program): ")/2, "Would you like to return to the main menu? (1 for yes, 0 to exit program): ", 60-strlen("Would you like to return to the main menu? (1 for yes, 0 to exit program): ")/2, ""); /*Prompting the user to return to the main menu*/
                savescanf6=scanf("%d",&stop);
                if (savescanf6==0 || stop<0 || stop>1) /*Checking the user input*/
                {
                    printf("\n");
                    printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
                    printf("\n\n");
                    empty_std_buffer(); /*Calling the 'empty_std_buffer' in order to read all elements the user has typed in case a char or string has been entered. This stops the program from looping endlessly*/
                }
                else
                {
                    empty_std_buffer();
                }

            }while(savescanf6==0 || stop<0 || stop>1);

        }while(stop==1);

        system("cls"); /*Clearing the console*/
    }
}

void empty_std_buffer() /*Clears stdn so that the program does not loop endlessly after a char or string has been entered*/
{
    int storecharacters; /*Used for storing values from the scanf function*/
    storecharacters = getchar();

    while (storecharacters != EOF && storecharacters != '\n') /*Reading all characters entered through the 'scanf' function*/
    {
        storecharacters = getchar();
    }
}

void main_menu(int *scanfvalue, int *response) /*Displays the 'main menu'*/
{
    FILE *in; /*File pointer*/
    char c; /*Stores characters read from the file*/
    int value, status;

    system("cls"); /*Clearing the console*/

    printf("\n");
    printf("%*s",60+strlen("Calculator")/2, "Calculator", 60-strlen("Calculator")/2, ""); /*Title*/
    printf("\n________________________________________________________________________________________________________________________\n");
    printf("\n");

    in = fopen("options.txt","r"); /*Opening the file for reading*/
    c = fgetc(in);

    while (c!=EOF) /*Printing all characters in the file*/
    {
       printf("%c",c);
       c = fgetc(in);
    }

    fclose(in); /*Closing the file*/
    printf("\n");
    printf("\n");

    do
    {
        printf("%*s",60+strlen("Please choose one of the options from above (Type a number from 1 to 10): ")/2, "Please choose one of the options from above (Type a number from 1 to 10): ", 60-strlen("Please choose one of the options from above (Type a number from 1 to 10): ")/2, ""); /*Prompting the user to choose one of the options*/
        value = scanf("%d",&status);
        printf("\n");

        if (value == 0 || status<1 || status>10) /*Checking the user input*/
        {
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();

        }
        else
        {
            empty_std_buffer();
        }

    }while (value == 0 || status<1 || status>10);

    *scanfvalue = value;
    *response = status;
}

void addition(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response) /*Displays the 'Addition' menu and finds the sum of numbers*/
{
    int i,n,value, value2, value3, status;
    float num[100],sum=0;

    system("cls"); /*Clearing the console*/
    printf("\n");
    printf("%*s",60+strlen("Addition")/2, "Addition", 60-strlen("Addition")/2, ""); /*Title*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nType the amount of numbers you would like to add together (maximum of 100 numbers): "); /*Prompting the user to choose the amount of numbers they would like to add*/
        value = scanf("%d",&n);
        if (value==0 || n<2 || n>100) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }

        else
        {
            empty_std_buffer();
        }

    }while(value==0 || n<2 || n>100);

    *scanfvalue = value;

    printf ("\nPlease type the %d numbers (one row at a time):\n\n",n); /*Prompting the user to type all numbers*/

    do
    {
        for(i=0; i<n; i++)
        {
            value2 = scanf("%f",&num[i]); /*Prompting the user to type all numbers*/
        }

        if (value2==0) /*Checking user input*/
        {
            printf("\nError: Invalid input. Type all numbers again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while (value2==0);

    for(i=0; i<n; i++)
    {
        sum=sum+num[i]; /*Calculating the sum*/
    }

    *scanfvalue2 = value2;

    printf("\nThe sum of the %d numbers above is: %.2f\n",n,sum);
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to carry out another addition? (1 for yes, 0 for no): ")/2, "Would you like to carry out another addition? (1 for yes, 0 for no): ", 60-strlen("Would you like to carry out another addition? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to carry out another addition*/
        value3 = scanf("%d",&status);
        printf("\n");

        if (value3==0 || status<0 || status>1) /*Checking the user input*/
        {
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3==0 || status<0 || status>1);

    *scanfvalue3 = value3;
    *response = status;
}

void subtraction(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Subtraction' menu and finds the difference between a set of numbers*/
{
    int status, value, value2;
    int i,n;
    int savescanf2 = 0,savescanf3 = 0,savescanf4 = 0,savescanf5 = 0,savescanf6 = 0,savescanf7 = 0,savescanf8 = 0,savescanf9 = 0,savescanf10 = 0,savescanf11=0;
    float difference,num1,num2,num3,num4,num5,num6,num7,num8,num9,num10;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Subtraction")/2, "Subtraction", 60-strlen("Subtraction")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nPlease type the amount of numbers you would like to subtract from each other (maximum of 10 numbers): "); /*Prompting the user to type the amount of numbers they would like to subtract*/
        value = scanf("%d",&n);

        if(value == 0 || n<2 || n>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value == 0 || n<2 || n>10);

    *scanfvalue = value;

    printf ("\nPlease type the %d numbers one row at a time (Numbers will be subtracted from top to bottom):\n\n",n); /*Prompting the user to type the numbers*/

    if (n==10)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);
            savescanf7 = scanf("%f",&num6);
            savescanf8 = scanf("%f",&num7);
            savescanf9 = scanf("%f",&num8);
            savescanf10 = scanf("%f",&num9);
            savescanf11 = scanf("%f",&num10);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0 || savescanf10==0 || savescanf11==0 ) /*Checking user input*/
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0 || savescanf10==0 || savescanf11==0 );

        difference=num1-num2-num3-num4-num5-num6-num7-num8-num9-num10; /*Finding the difference*/
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,num6,num7,num8,num9,num10,difference);

    }
    else if (n==9)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);
            savescanf7 = scanf("%f",&num6);
            savescanf8 = scanf("%f",&num7);
            savescanf9 = scanf("%f",&num8);
            savescanf10 = scanf("%f",&num9);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0 || savescanf10==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0 || savescanf10==0);

        difference=num1-num2-num3-num4-num5-num6-num7-num8-num9;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,num6,num7,num8,num9,difference);

    }
    else if (n==8)
    {
        do
        {

            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);
            savescanf7 = scanf("%f",&num6);
            savescanf8 = scanf("%f",&num7);
            savescanf9 = scanf("%f",&num8);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0 || savescanf9==0);

        difference=num1-num2-num3-num4-num5-num6-num7-num8;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,num6,num7,num8,difference);
    }
    else if (n==7)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);
            savescanf7 = scanf("%f",&num6);
            savescanf8 = scanf("%f",&num7);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0 || savescanf8==0);

        difference=num1-num2-num3-num4-num5-num6-num7;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,num6,num7,difference);

    }
    else if (n==6)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);
            savescanf7 = scanf("%f",&num6);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0 || savescanf7==0);

        difference=num1-num2-num3-num4-num5-num6;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,num6,difference);

    }
    else if (n==5)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);
            savescanf6 = scanf("%f",&num5);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0 || savescanf6==0);

        difference=num1-num2-num3-num4-num5;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,num5,difference);
    }
    else if (n==4)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);
            savescanf5 = scanf("%f",&num4);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0 || savescanf5==0);

        difference=num1-num2-num3-num4;
        printf("\nResult: %.2f - %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,num4,difference);
    }
    else if (n==3)
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);
            savescanf4 = scanf("%f",&num3);

            if (savescanf2==0 || savescanf3==0 || savescanf4==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0 || savescanf4==0);

        difference=num1-num2-num3;
        printf("\nResult: %.2f - %.2f - %.2f = %.2f\n",num1,num2,num3,difference);
    }
    else
    {
        do
        {
            savescanf2 = scanf("%f",&num1);
            savescanf3 = scanf("%f",&num2);

            if (savescanf2==0 || savescanf3==0)
            {
                printf("\nError: Invalid input. Please type the numbers again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(savescanf2==0 || savescanf3==0);

        difference=num1-num2;
        printf("\nResult: %.2f - %.2f = %.2f\n",num1,num2,difference);
    }

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
       printf("%*s",60+strlen("Would you like to subtract more numbers? (1 for yes, 0 for no): ")/2, "Would you like to subtract more numbers? (1 for yes, 0 for no): ", 60-strlen("Would you like to subtract more numbers? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to subtract more numbers*/
       value2 = scanf("%d",&status);
       printf("\n");

       if (value2==0 || status<0 || status>1) /*Check the user's input*/
       {
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
       }
       else
       {
            empty_std_buffer();
       }

    }while(value2==0 || status<0 || status>1);

    *scanfvalue2 = value2;
    *response = status;

}

void multiplication(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response) /*Displays the 'Multiplication' menu and finds the product of a set of numbers*/
{
    int i,n, value, value2, value3, status;
    float num[100],product=1;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Multiplication")/2, "Multiplication", 60-strlen("Multiplication")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nType the amount of numbers you would like to multiply together (maximum of 100 numbers): "); /*Prompting the user to type the amount of numbersthey would like to multiply together*/
        value = scanf("%d",&n);

        if (value == 0 || n<2 || n>100) /*Checking user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value == 0 || n<2 || n>100);

    *scanfvalue = value2;

    printf ("\nPlease type the %d numbers (one row at a time):\n\n",n); /*Prompting the user to type the numbers*/

     do
     {
        for(i=0; i<n; i++)
        {
            value2 = scanf("%f",&num[i]);
        }

        if(value2 == 0) /*Checking user's input*/
        {
            printf("\nError: Invalid input. Please type all numbers again\n");
            empty_std_buffer();
        }

     }while(value2 == 0);

     for(i=0; i<n; i++)
     {
         product=product*num[i]; /*Calculating the product*/
     }

    *scanfvalue2 = value2;
    printf("\nThe product of the %d numbers above is: %.2f\n",n,product);
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to multiply more numbers? (1 for yes, 0 for no): ")/2, "Would you like to multiply more numbers? (1 for yes, 0 for no): ", 60-strlen("Would you like to multiply more numbers? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to re-run the multiplication program*/
        value3 = scanf("%d",&status);

        if (value3 == 0 || status<0 || status>1)
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input", 60-strlen("Error: Invalid input")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3 == 0 || status<0 || status>1);

    *scanfvalue3 = value3;
    *response = status;
}

void division(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response) /*Displays the 'Division' menu and proceeds to divide two numbers*/
{
    float num1,num2, divisor;
    int value, value1,value2, status;
    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Division")/2, "Division", 60-strlen("Division")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    printf("\nPlease type the 2 numbers (one row at a time):\n\n"); /*Prompting the user to type the two numbers*/

    do
    {
        value1 = scanf("%f",&num1);
        value2 = scanf("%f",&num2);

        if (value1==0 || value2==0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all numbers again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value1==0 || value2==0);

    if (num2==0) /*Checking if the denominator is 0*/
    {
        printf("\nMATH ERROR!\n");
    }
    else
    {
        divisor=num1/num2; /*Performing the calculation*/
        printf("\nResult: %.2f / %.2f = %.2f\n",num1,num2,divisor);
    }

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to divide more numbers? (1 for yes, 0 for no): ")/2, "Would you like to divide more numbers? (1 for yes, 0 for no): ", 60-strlen("Would you like to divide more numbers? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to divide more numbers*/
        value = scanf("%d",&status);

        if(value==0 || status<0 || status>1) /*Checking the user's input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || status<0 || status>1);

    *scanfvalue = value;
    *scanfvalue2 = value1;
    *scanfvalue3 = value2;
    *response = status;
}

void matrixoperationsmenu(int *scanfvalue, int *reply) /*Displays the 'Matrix operations' menu*/
{
    FILE *in; /*File pointer*/
    char c;
    int status, value;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Matrix operations")/2, "Matrix operations", 60-strlen("Matrix operations")/2, ""); /*Title*/
    printf("\n________________________________________________________________________________________________________________________\n");

    in = fopen("matrixoperationsmenu.txt","r"); /*Opens the file for reading*/
    c = fgetc(in);

    while (c!=EOF)
    {
       printf("%c",c); /*Printing the characters from the file*/
       c = fgetc(in);
    }

    fclose(in); /*Closing the file*/
    printf("\n");
    printf("\n");

    do
    {
        printf("%*s",60+strlen("Please choose one of the options from above (Type a number from 1 to 5): ")/2, "Please choose one of the options from above (Type a number from 1 to 5): ", 60-strlen("Please choose one of the options from above (Type a number from 1 to 5): ")/2, ""); /*Prompting the user to choose one of the options from the menu*/
        value = scanf("%d",&status);

        if (value == 0 || status<1 || status>5) /*Checking the user's input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while (value == 0 || status<1 || status>5);

    *scanfvalue = value;
    *reply = status;
}

void addmatrices(struct MatrixOp sum[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays the 'Matrix addition' menu and adds two matrices together*/
{
    int i, j;
    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Matrix addition")/2, "Matrix addition", 60-strlen("Matrix addition")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    printf("\n");

    do
    {
        printf("Enter the number of rows for both matrices (Maximum of 10): ");
        value = scanf("%d",&sum[0].rows);

        if (value == 0 || sum[0].rows<1 || sum[0].rows>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value == 0 || sum[0].rows<1 || sum[0].rows>10);

    do
    {
        printf("\nEnter the number of columns for both matrices (Maximum of 10): ");
        scanf("%d",&sum[0].cols);

        if (value == 0 || sum[0].cols<1 || sum[0].cols>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || sum[0].cols<1 || sum[0].cols>10);

    printf("\nEnter the elements of the first matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the matrix*/

    do
    {
        for (i=0; i<sum[0].rows; i++)
        {
            for (j=0; j<sum[0].cols; j++)
            {
                value2 = scanf("%f",&sum[0].elements[i][j]);
            }
        }

        if (value2 == 0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all elements again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0);


    sum[1].rows = sum[0].rows;
    sum[1].cols = sum[0].cols;

    printf("\nEnter the elements of the second matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the matrix*/

    do
    {
        for (i=0; i<sum[1].rows; i++)
        {
            for (j=0; j<sum[1].cols; j++)
            {
                value3 = scanf("%f",&sum[1].elements[i][j]);
            }
        }

        if (value3 == 0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all elements again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3==0);



    printf("\nThe first matrix is:\n\n");

    for (i=0; i<sum[0].rows; i++)
    {
        printf("|          ");
        for (j=0; j<sum[0].cols; j++)
        {
            printf("%8.2f\t",sum[0].elements[i][j]); /*Printing the first matrix*/
        }
        printf("\t|\n");
    }
    printf("\n");

    printf("The second matrix is:\n\n");

    for (i=0; i<sum[1].rows; i++)
    {
        printf("|          ");
        for (j=0; j<sum[1].cols; j++)
        {
            printf("%8.2f\t",sum[1].elements[i][j]); /*Printing the second matrix*/
        }
        printf("\t|\n");
    }
    printf("\n");

    printf("The result of adding the first and second matrix is:\n\n");

    sum[2].rows = sum[0].rows;
    sum[2].cols = sum[0].cols;

    for (i=0; i<sum[2].rows; i++)
    {
        printf("|          ");
        for(j=0; j<sum[2].cols; j++)
        {
            sum[2].elements[i][j]=sum[0].elements[i][j]+sum[1].elements[i][j]; /*Finding the sum*/
            printf("%8.2f\t",sum[2].elements[i][j]); /*Printing the sum*/
        }
        printf("\t|\n");
    }

    *scanfvalue = value;
    *scanfvalue2 = value2;
    *scanfvalue3 = value3;

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to add more matrices? (1 for yes, 0 for no): ")/2, "Would you like to add more matrices? (1 for yes, 0 for no): ", 60-strlen("Would you like to add more matrices? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to add more matrices*/
        value4 = scanf("%d",&reply);

        if (value4==0 || reply<0 || reply>1) /*Checking the user's input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value4==0 || reply<0 || reply>1);

    *response = reply;
    *scanfvalue4 = value4;
}

void subtractmatrices(struct MatrixOp difference[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays the 'Matrix subtraction' menu and finds the difference between two matrices*/
{
    int i, j;
    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Matrix subtraction")/2, "Matrix subtraction", 60-strlen("Matrix subtraction")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    printf("\n");

    do
    {
        printf("Enter the number of rows for both matrices (Maximum of 10): ");
        value = scanf("%d",&difference[0].rows);

        if (value == 0 || difference[0].rows<1 || difference[0].rows>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value == 0 || difference[0].rows<1 || difference[0].rows>10);

    do
    {
        printf("\nEnter the number of columns for both matrices (Maximum of 10): ");
        scanf("%d",&difference[0].cols);

        if (value == 0 || difference[0].cols<1 || difference[0].cols>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || difference[0].cols<1 || difference[0].cols>10);

    printf("\nEnter the elements of the first matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the first matrix*/

    do
    {
        for (i=0; i<difference[0].rows; i++)
        {
            for (j=0; j<difference[0].cols; j++)
            {
                value2 = scanf("%f",&difference[0].elements[i][j]);
            }
        }

        if (value2 == 0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all elements again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0);


    difference[1].rows = difference[0].rows;
    difference[1].cols = difference[0].cols;

    printf("\nEnter the elements of the second matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the matrix*/

    do
    {
        for (i=0; i<difference[1].rows; i++)
        {
            for (j=0; j<difference[1].cols; j++)
            {
                value3 = scanf("%f",&difference[1].elements[i][j]);
            }
        }

        if (value3 == 0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all elements again\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3==0);

    printf("\nThe first matrix is:\n\n");

    for (i=0; i<difference[0].rows; i++)
    {
        printf("|          ");
        for (j=0; j<difference[0].cols; j++)
        {
            printf("%8.2f\t",difference[0].elements[i][j]); /*Printing the first matrix*/
        }
        printf("\t|\n");
    }
    printf("\n");

    printf("The second matrix is:\n\n");

    for (i=0; i<difference[1].rows; i++)
    {
        printf("|          ");
        for (j=0; j<difference[1].cols; j++)
        {
            printf("%8.2f\t",difference[1].elements[i][j]); /*Printing the second matrix*/
        }
        printf("\t|\n");
    }
    printf("\n");

    printf("The result of subtracting the second matrix from the first matrix is:\n\n");

    difference[2].rows = difference[0].rows;
    difference[2].cols = difference[0].cols;

    for (i=0; i<difference[2].rows; i++)
    {
        printf("|          ");
        for(j=0; j<difference[2].cols; j++)
        {
            difference[2].elements[i][j]=difference[0].elements[i][j]-difference[1].elements[i][j]; /*Finding the difference*/
            printf("%8.2f\t",difference[2].elements[i][j]); /*Printing the result*/
        }
        printf("\t|\n");
    }

    *scanfvalue = value;
    *scanfvalue2 = value2;
    *scanfvalue3 = value3;

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to subtract more matrices? (1 for yes, 0 for no): ")/2, "Would you like to subtract more matrices? (1 for yes, 0 for no): ", 60-strlen("Would you like to subtract more matrices? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to subtract more matrices*/
        value4 = scanf("%d",&reply);

        if (value4==0 || reply<0 || reply>1) /*Checking the user's input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value4==0 || reply<0 || reply>1);

    *response = reply;
    *scanfvalue4 = value4;

}

void multiplymatrices(struct MatrixOp times[3], int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays the 'Matrix multiplication' menu and finds the product of two matrices*/
{
    int i, j, z, product = 0;
    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Matrix multiplication")/2, "Matrix multiplication", 60-strlen("Matrix multiplication")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    printf("\n");

    do
    {
        printf("\nEnter the number of rows for the first matrix (Maximum of 10): ");
        value = scanf("%d",&times[0].rows);

        if (value==0 || times[0].rows<1 || times[0].rows>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || times[0].rows<1 || times[0].rows>10);

    do
    {
        printf("\nEnter the number of columns for the first matrix (Maximum of 10): ");
        scanf("%d",&times[0].cols);

        if (value==0 || times[0].cols<1 || times[0].cols>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || times[0].cols<1 || times[0].cols>10);

    do
    {
        printf("\nEnter the number of rows for the second matrix (Maximum of 10): ");
        scanf("%d",&times[1].rows);

        if (value==0 || times[1].rows<1 || times[1].rows>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || times[1].rows<1 || times[1].rows>10);

    do
    {
        printf("\nEnter the number of columns for the second matrix (Maximum of 10): ");
        value = scanf("%d",&times[1].cols);

        if (value==0 || times[1].cols<1 || times[1].cols>10) /*Checking the user's input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || times[1].cols<1 || times[1].cols>10);

    *scanfvalue = value;

    if (times[0].cols!=times[1].rows) /*Checking if the columns of the first matrix is equal to the rows of the second matrix*/
    {
        printf("\nError: Matrices can't be multiplied together since the number of columns in the first matrix is not equal to the number of rows in the second matrix.\n");
    }
    else
    {
        printf("\nEnter the elements of the first matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the first matrix*/

        do
        {
            for (i=0; i<times[0].rows; i++)
            {
                for (j=0; j<times[0].cols; j++)
                {
                value2 = scanf("%f",&times[0].elements[i][j]);
                }
            }

            if (value2 == 0) /*Checking the user's input*/
            {
                printf("\nError: Invalid input. Please type all elements again\n");
                empty_std_buffer();
            }
            else
            {
            empty_std_buffer();
            }

        }while(value2==0);

        *scanfvalue2 = value2;

        printf("\nEnter the elements of the second matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the second matrix*/

        do
        {
            for (i=0; i<times[1].rows; i++)
            {
                for (j=0; j<times[1].cols; j++)
                {
                    value3 = scanf("%f",&times[1].elements[i][j]);
                }
            }

            if (value3 == 0) /*Checking the user's input*/
            {
                printf("\nError: Invalid input. Please type all elements again\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value3==0);

        *scanfvalue3 = value3;

        printf("\nThe first matrix is:\n\n");

        for (i=0; i<times[0].rows; i++)
        {
            printf("|          ");
            for (j=0; j<times[0].cols; j++)
            {
                printf("%8.2f\t",times[0].elements[i][j]); /*Printing the first matrix*/
            }
            printf("\t|\n");
        }
        printf("\n");

        printf("The second matrix is:\n\n");

        for (i=0; i<times[1].rows; i++)
        {
            printf("|          ");
            for (j=0; j<times[1].cols; j++)
            {
                printf("%8.2f\t",times[1].elements[i][j]); /*Printing the second matrix*/
            }
            printf("\t|\n");
        }
        printf("\n");

        for(i=0; i<times[0].rows; i++)
        {
            for(j=0; j<times[1].cols; j++)
            {
                for(z=0; z<times[1].rows; z++)
                {
                    product = product + times[0].elements[i][z]*times[1].elements[z][j]; /*Finding the product*/
                }
                times[2].elements[i][j] = product;
                product = 0;
            }
        }

        printf("The result of multiplying the first and second matrix together is:\n\n");

        for (i=0; i<times[0].rows; i++)
        {
            printf("|          ");
            for(j=0; j<times[1].cols; j++)
            {
                printf("%8.2f\t",times[2].elements[i][j]); /*Printing the result*/
            }
            printf("\t|\n");
        }
    }
    fflush(stdin);
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to multiply more matrices? (1 for yes, 0 for no): ")/2, "Would you like to multiply more matrices? (1 for yes, 0 for no): ", 60-strlen("Would you like to multiply more matrices? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to carry out another matrix multiplication*/
        value4 = scanf("%d",&reply);

        if (value4==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value4==0 || reply<0 || reply>1);

    *response = reply;
    *scanfvalue4 = value4;
}

void DandImatrix(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays the 'Determinant & inverse of a matrix' menu, and calculates the determinant and the inverse for a 2x2 or 3x3 matrix*/
{
    float determinant,matrix1[2][2],matrix2[3][3],adj1[2][2],adj2[3][3],invmat1[2][2],invmat2[3][3],cof[3][3],trp[3][3]; /*Variables for storing the determinant, the two matrices entered by the user, the adjugate matrices, the cofactor matrix, the transpose matrix, and the inverse of the matrices*/
    float A11,A12,A13,A21,A22,A23,A31,A32,A33; /*Storing the minors of a 3x3 matrix*/
    int option, i, j;
    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Determinant & inverse of a matrix")/2, "Determinant & inverse of a matrix", 60-strlen("Determinant & inverse of a matrix")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nType '2' for a '2x2' matrix, or '3' for a '3x3' matrix: "); /*Prompting the user to choose between a 2x2 or 3x3 matrix*/
        value = scanf("%d",&option);
        if (value == 0 || option<2 || option>3) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || option<2 || option>3);

    *scanfvalue = value;

    if (option==2)
    {
        printf("\nEnter the elements of the '2x2' matrix (one row at a time):\n"); /*Prompting the user to enter the elements of a 2x2 matrix*/

        do
        {
            for (i=0; i<2; i++)
            {
                for (j=0; j<2; j++)
                {
                    value2 = scanf("%f",&matrix1[i][j]);
                }
            }

            if (value2==0) /*Checking user input*/
            {
                printf("\nError: Invalid input. Please type all elements again.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0);

        *scanfvalue2 = value2;

        determinant = (matrix1[0][0]*matrix1[1][1])-(matrix1[0][1]*matrix1[1][0]); /*Finding the determinant*/
        printf("\nThe determinant for the matrix below is: %.2f\n\n",determinant); /*Printing the determinant*/

        for (i=0; i<2; i++)
        {
            printf("|          ");
            for (j=0; j<2; j++)
            {
                printf("%8.2f\t",matrix1[i][j]); /*Printing the matrix entered by the user*/
            }
            printf("\t|\n");
        }

        if (determinant==0) /*Scenario where the determinant is zero*/
        {
            printf("\nError: the inverse can't be found (determinant is 0).\n");
        }
        else
        {
            /*Calculating the adjugate matrix*/
            adj1[0][0] = matrix1[1][1];
            adj1[0][1] = -matrix1[0][1];
            adj1[1][0] = -matrix1[1][0];
            adj1[1][1] = matrix1[0][0];

            printf("\nThe inverse of the matrix above is:\n\n");

            for (i=0; i<2; i++)
            {
                printf("|          ");
                for (j=0; j<2; j++)
                {
                    invmat1[i][j]=adj1[i][j]/determinant; /*Calculating the inverse*/
                    printf("%8.2f\t",invmat1[i][j]); /*Printing the inverse matrix*/
                }
                printf("\t|\n");
            }
        }
    }
    else
    {
        printf("\nEnter the elements of the '3x3' matrix (one row at a time):\n"); /*Prompting the user to enter the elements of a 3x3 matrix*/

        do
        {
            for (i=0; i<3; i++)
            {
                for (j=0; j<3; j++)
                {
                    value3 = scanf("%f",&matrix2[i][j]);
                }
            }

            if (value3 == 0) /*Checking user input*/
            {
                printf("\nError: Invalid input. Please type all elements again.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value3==0);

        *scanfvalue3 = value3;

        determinant = matrix2[0][0]*((matrix2[1][1]*matrix2[2][2])-(matrix2[1][2]*matrix2[2][1]))-matrix2[0][1]*((matrix2[1][0]*matrix2[2][2])-(matrix2[1][2]*matrix2[2][0]))+matrix2[0][2]*((matrix2[1][0]*matrix2[2][1])-(matrix2[1][1]*matrix2[2][0])); /*Calculating the determinant*/
        printf("\nThe determinant for the matrix below is: %.2f\n\n",determinant); /*Printing the determinant*/

        for (i=0; i<3; i++)
        {
            printf("|          ");
            for (j=0; j<3; j++)
            {
                printf("%8.2f\t",matrix2[i][j]); /*Printing the matrix entered by the user*/
            }
        printf("\t|\n");
        }

        if (determinant==0) /*Scenario where the determinant is zero*/
        {
            printf("\nError: the inverse can't be found (determinant is 0).\n");
        }
        else
        {
            /*Calculating the minors of a 3x3 matrix*/
            A11 = ((matrix2[1][1]*matrix2[2][2]) - (matrix2[1][2]*matrix2[2][1]));
            A12 = ((matrix2[1][0]*matrix2[2][2]) - (matrix2[1][2]*matrix2[2][0]));
            A13 = ((matrix2[1][0]*matrix2[2][1]) - (matrix2[1][1]*matrix2[2][0]));
            A21 = ((matrix2[0][1]*matrix2[2][2]) - (matrix2[0][2]*matrix2[2][1]));
            A22 = ((matrix2[0][0]*matrix2[2][2]) - (matrix2[0][2]*matrix2[2][0]));
            A23 = ((matrix2[0][0]*matrix2[2][1]) - (matrix2[0][1]*matrix2[2][0]));
            A31 = ((matrix2[0][1]*matrix2[1][2]) - (matrix2[0][2]*matrix2[1][1]));
            A32 = ((matrix2[0][0]*matrix2[1][2]) - (matrix2[0][2]*matrix2[1][0]));
            A33 = ((matrix2[0][0]*matrix2[1][1]) - (matrix2[0][1]*matrix2[1][0]));

            /*Creating the matrix of cofactors*/
            cof[0][0] = A11;
            cof[0][1] = A12;
            cof[0][2] = A13;
            cof[1][0] = A21;
            cof[1][1] = A22;
            cof[1][2] = A23;
            cof[2][0] = A31;
            cof[2][1] = A32;
            cof[2][2] = A33;

            /*Transposing the matrix*/
            trp[0][0] = cof[0][0];
            trp[0][1] = -cof[1][0];
            trp[0][2] = cof[2][0];
            trp[1][0] = -cof[0][1];
            trp[1][1] = cof[1][1];
            trp[1][2] = -cof[2][1];
            trp[2][0] = cof[0][2];
            trp[2][1] = -cof[1][2];
            trp[2][2] = cof[2][2];

            printf("\nThe inverse of the matrix above is:\n\n");
            for (i=0; i<3; i++)
            {
                printf("|          ");
                for (j=0; j<3; j++)
                {
                    invmat2[i][j] = (1/determinant)*(trp[i][j]); /*Calculating the inverse matrix*/
                    printf("%8.2f\t",invmat2[i][j]); /*Printing the inverse matrix*/
                }
                printf("\t|\n");
            }

        }

    }
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to find the determinant & inverse of another matrix? (1 for yes, 0 for no): ")/2, "Would you like to find the determinant & inverse of another matrix? (1 for yes, 0 for no): ", 60-strlen("Would you like to find the determinant & inverse of another matrix? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to find the determinant and inverse of another matrix*/
        value4 = scanf("%d",&reply);

        if(value4==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value4==0 || reply<0 || reply>1);

    *scanfvalue4 = value4;
    *response = reply;
}

void transposematrix(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response) /*Displays the 'Transpose matrix' menu and finds the transpose of a matrix*/
{
    int rows, cols, i, j; /*Storing the number of rows and columns, i and j are used to access the elements of a matrix using nested for loops*/
    float matrix1[10][10], transpose[10][10]; /*Storing the matrix entered by the user and storing the transpose matrix*/
    int value, value2, value3, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Transpose of a matrix")/2, "Transpose of a matrix", 60-strlen("Transpose of a matrix")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nEnter the number of rows (Maximum of 10): ");
        value = scanf("%d",&rows);

        if(value==0 || rows<1 || rows>10) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || rows<1 || rows>10);

    do
    {
        printf("\nEnter the number of columns (Maximum of 10): ");
        scanf("%d",&cols);

        if(value==0 || cols<1 || cols>10) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || cols<1 || cols>10);

    *scanfvalue = value;

    printf("\nEnter the elements of the matrix (one row at a time):\n"); /*Prompting the user to enter the elements of the matrix*/

    do
    {
        for (i=0; i<rows; i++)
        {
            for (j=0; j<cols; j++)
            {
                value2 = scanf("%f",&matrix1[i][j]);
            }
        }

        if(value2==0) /*Checking the user's input*/
        {
            printf("\nError: Invalid input. Please type all elements again.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while (value2==0);

    *scanfvalue2 = value2;

    printf("\nThe matrix is:\n\n");

    for (i=0; i<rows; i++)
    {
        printf("|          ");
        for (j=0; j<cols; j++)
        {
            printf("%8.2f\t",matrix1[i][j]); /*Printing the matrix entered by the user*/
        }
        printf("\t|\n");
    }

    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            transpose[j][i] = matrix1[i][j]; /*Finding the transpose of the matrix*/
        }
    }

    printf("\nThe transpose of the matrix above is:\n\n");

    for (i=0; i<cols; i++)
    {
        printf("|          ");
        for (j=0; j<rows; j++)
        {
            printf("%8.2f\t",transpose[i][j]); /*Printing the transpose matrix*/
        }
        printf("\t|\n");
    }

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to find the transpose of another matrix? (1 for yes, 0 for no): ")/2, "Would you like to find the transpose of another matrix? (1 for yes, 0 for no): ", 60-strlen("Would you like to find the transpose of another matrix? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to find the transpose of another matrix*/
        value3 = scanf("%d",&reply);

        if(value3==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3==0 || reply<0 || reply>1);

    *scanfvalue3 = value3;
    *response = reply;
}

void quadeqs(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays  the 'Quadratic equation solver' menu and finds the roots of a polynomial*/
{
    float a,b,c,discriminant,firstroot,secondroot,complex1,complex2; /*a,b,and c represent the coefficients in a polynomial. discriminant is used to find the discriminant of the quadratic equation. firstroot and secondroot are used for storing the roots of the equation. complex1 and complex2 are used for storing the complex numbers if the equation does not have any real roots*/
    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Quadratic equation solver")/2, "Quadratic equation solver", 60-strlen("Quadratic equation solver")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nType the values for a, b, and c, one row at a time (where a is the coefficient of x^2, b is the coefficient of x, and c is the constant):\n\n"); /*Prompting the user to enter the coefficients of the quadratic equation*/
        value=scanf("%f",&a);
        value3=scanf("%f",&b);
        value4=scanf("%f",&c);

        if (value==0 || value3==0 || value4==0) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while (value==0 || value3==0 || value4==0);

    *scanfvalue=value;
    *scanfvalue3=value3;
    *scanfvalue4=value4;

    printf("\nThe quadratic equation is: ");
    printf("(%.2f)x^2 + (%.2f)x + (%.2f) = 0",a,b,c); /*Printing the quadratic equation*/
    discriminant = (b*b)-4*a*c; /*Calculating the discriminant of the polynomial*/

    if (discriminant==0) /*If there are two repeated roots*/
    {
        printf("\nThere are 2 repeated roots.\n");
        firstroot = ((-b)/((2*a))); /*Calculating the root*/
        printf("\nThe one and only root of the quadratic equation is: %.2f\n",firstroot); /*Printing the root*/
    }
    else if (discriminant<0) /*If there are no real roots*/
    {
        printf("\nBoth roots are not real (complex numbers).\n");
        firstroot = ((-b)/((2*a))); /*Calculating the first root*/
        complex1 = sqrt(-discriminant)/(2*a); /*Finding the complex part of the first root*/
        secondroot = ((-b)/((2*a))); /*Calculating the second root*/
        complex2 = -sqrt(-discriminant)/(2*a); /*Finding the complex part of the second root*/
        printf("The roots of the quadratic equation are:\n");
        /*Printing the roots*/
        printf("%.2f%+.2fi & ",firstroot,complex1);
        printf("%.2f%+.2fi",secondroot,complex2);
    }
    else /*If both roots are different and real*/
    {
        printf("\nBoth roots are real.\n");
        firstroot = (((-b)+sqrt(discriminant))/(2*a));/*Calculating the first root*/
        secondroot = (((-b)-sqrt(discriminant))/(2*a));/*Calculating the second root*/
        printf("The roots of the quadratic equation are: %.2f & %.2f\n",firstroot,secondroot); /*Printing the roots*/
    }

    fflush(stdin);
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to solve another quadratic equation? (1 for yes, 0 for no): ")/2, "Would you like to solve another quadratic equation? (1 for yes, 0 for no): ", 60-strlen("Would you like to solve another quadratic equation? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to solve another quadratic equation*/
        value2=scanf("%d",&reply);

        if (value2==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;

}

void squareroot(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Square root' menu and determines the square root of a number*/
{
    float num,squareroot;
    int value, value2, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Square root")/2, "Square root", 60-strlen("Square root")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nPlease Enter the number you would like to find the square root of: "); /*Prompting the user to enter a number*/
        value=scanf("%f",&num);

        if(value==0) /*Checking user input*/
        {
            printf("\nError: Invalid input\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    if (num<0) /*If a negative number has been entered*/
    {
        printf("\nMath ERROR\n");
    }
    else
    {
        squareroot = sqrt(num); /*Calculating the square root*/
        printf("\nThe square root of %.2f is: %.2f\n",num,squareroot); /*Printing the result*/
    }

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to find the square root of another number? (1 for yes, 0 for no): ")/2, "Would you like to find the square root of another number? (1 for yes, 0 for no): ", 60-strlen("Would you like to find the square root of another number? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to find the square root of another number*/
        value2 = scanf("%d",&reply);

        if (value2==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();

        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue=value2;
    *response=reply;

}

void raisetopower(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *scanfvalue4, int *response) /*Displays the 'Raise to a power' menu and raises a certain number or 'e' to a certain power*/
{
    int basechoice;
    float num, power, Result;

    int value, value2, value3, value4, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Raising to a power")/2, "Raising to a power", 60-strlen("Raising to a power")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("\nType 1 for a number or 2 for 'e': "); /*Prompting the user to choose a number or 'e'*/
        value=scanf("%d",&basechoice);

        if (value==0 || basechoice<1 || basechoice>2) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0 || basechoice<1 || basechoice>2);

    *scanfvalue = value;

    if (basechoice==1) /*If the user chooses a number*/
    {
        do
        {
            printf("\nPlease type the number that you would like to raise to a certain power: "); /*Prompting the user to type a number*/
            value2 = scanf("%f",&num);

            if (value2==0) /*Checking the user input*/
            {
                printf("\nError: Invalid input.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0);

        do
        {
            printf("\nPlease type the desired power that you would like to raise your number to: "); /*Prompting the user to type the power*/
            value3 = scanf("%f",&power);

            if (value3==0) /*Checking user input*/
            {
                printf("\nError: Invalid input.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value3==0);

        Result = pow(num,power); /*Calculating the result*/
        printf("\nThe results of raising %.2f to a power of %.2f is: %.2f\n",num,power,Result); /*Printing the result*/
    }
    else /*If the user chooses 'e'*/
    {
        do
        {
            printf("\nPlease type the desired power that you would like to raise 'e' to: "); /*Prompting the user to enter the power*/
            value3 = scanf("%f",&power);

            if (value3==0) /*Checking user input*/
            {
                printf("\nError: Invalid input.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value3==0);

        Result = exp(power); /*Calculating the result*/
        printf("\nThe results of raising e to a power of %.2f is: %.2f\n",power,Result); /*Printing the result*/
    }

    *scanfvalue2 = value2;
    *scanfvalue3 = value3;

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to raise another number or 'e' to a certain power? (1 for yes, 0 for no): ")/2, "Would you like to raise another number or 'e' to a certain power? (1 for yes, 0 for no): ", 60-strlen("Would you like to raise another number or 'e' to a certain power? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to carry out another calculation*/
        value4 = scanf("%d",&reply);

        if (value4==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value4==0 || reply<0 || reply>1);

    *scanfvalue4 = value4;
    *response = reply;

}

void trigmenu(int *scanfvalue, int *response) /*Displays the 'Trigonometric functions' menu*/
{
    FILE *in; /*File pointer*/
    char c; /*Stores characters read from the file*/
    int value, status;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Trigonometric functions")/2, "Trigonometric functions", 60-strlen("Trigonometric functions")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");

    in = fopen("trigoptions.txt","r"); /*Opening the file for reading*/
    c = fgetc(in);

    while (c!=EOF)
    {
       printf("%c",c); /*Printing the characters in the file*/
       c = fgetc(in);
    }

    fclose(in); /*Closing the file*/

    do
    {
        printf("%*s",60+strlen("Please choose one of the options from above (Type a number from 1 to 9): ")/2, "Please choose one of the options from above (Type a number from 1 to 9): ", 60-strlen("Please choose one of the options from above (Type a number from 1 to 9): ")/2, ""); /*Prompting the user to choose one of the options from the 'Trigonometric functions' menu*/
        value = scanf("%d",&status);
        printf("\n");

        if (value == 0 || status<1 || status>9) /*Checking the user input*/
        {
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input.")/2, "");
            printf("\n\n");
            empty_std_buffer();

        }
        else
        {
            empty_std_buffer();
        }

    }while (value == 0 || status<1 || status>9);

    *scanfvalue = value;
    *response = status;
}

void sine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Sine' menu and computes the argument of sin*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Sine")/2, "Sine", 60-strlen("Sine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the sine function in radians: "); /*Prompting the user to type the argument*/
        value=scanf("%f",&arg);
        if (value==0) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = sin(arg); /*Computing the result*/
    printf("\nThe results of computing sin(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the sine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the sine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the sine function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
        scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();

        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void cosine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Cosine' menu and computes the argument of cos*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Cosine")/2, "Cosine", 60-strlen("Cosine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the cosine function in radians: "); /*Prompting the user to enter the argument*/
        value=scanf("%f",&arg);
        if (value==0) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = cos(arg); /*Computing the result*/
    printf("\nThe results of computing cos(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the cosine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the cosine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the cosine function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
        scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();

        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void tangent(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Tangent' menu and computes the argument of tan*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Tangent")/2, "Tangent", 60-strlen("Tangent")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the tangent function in radians: "); /*Prompting the user to enter the argument*/
        value=scanf("%f",&arg);
        if (value==0) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = tan(arg); /*Computing the result*/
    printf("\nThe results of computing tan(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the tangent function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the tangent function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the tangent function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
        scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1) /*Checking the user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void arcsine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Arc - Sine' menu and computes an argument for the inverse of sin*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Arc - sine")/2, "Arc - sine", 60-strlen("Arc - sine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the arc - sine function in radians (must be between -1 & 1): "); /*Prompting the user to enter the argument*/
        value = scanf("%f",&arg);

        if (value==0) /*Checking the user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    if (arg<-1 || arg>1) /*If the argument is greater than 1 or less than -1*/
    {
        printf("\nMath ERROR.\n");
    }
    else
    {
        result = asin(arg); /*Computing the result*/
        printf("\nThe results of computing arcsin(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    }
        fflush(stdin); /*Clearing the buffer*/
        printf("\n________________________________________________________________________________________________________________________\n");
        do
        {
            printf("%*s",60+strlen("Would you like to compute a different argument for the arc - sine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the arc - sine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the arc - sine function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to carry out another calculation*/
            value2 = scanf("%d",&reply);

            if (value2==0 || reply<0 || reply>1) /*Checking user input*/
            {
                printf("\n");
                printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
                printf("\n\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0 || reply<0 || reply>1);

        *scanfvalue2 = value2;
        *response = reply;

}

void arccosine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Arc - Cosine' menu and computes the argument for the inverse of cos*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Arc - cosine")/2, "Arc - cosine", 60-strlen("Arc - cosine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the arc - cosine function in radians (must be between -1 & 1): "); /*Prompting the user to type the argument*/
        value = scanf("%f",&arg);

        if (value==0) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    if (arg<-1 || arg>1) /*If argument is greater than 1 or less than -1*/
    {
        printf("\nMath ERROR.\n");
    }
    else
    {
        result = acos(arg); /*Computing the result*/
        printf("\nThe results of computing arccos(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    }
        fflush(stdin); /*Clearing the buffer*/
        printf("\n________________________________________________________________________________________________________________________\n");
        do
        {
            printf("%*s",60+strlen("Would you like to compute a different argument for the arc - cosine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the arc - cosine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the arc - cosine function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
            value2 = scanf("%d",&reply);

            if (value2==0 || reply<0 || reply>1) /*Checking user input*/
            {
                printf("\n");
                printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
                printf("\n\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0 || reply<0 || reply>1);

        *scanfvalue2 = value2;
        *response = reply;

}

void arctangent(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Arc - Tangent' menu and computes the inverse of tan*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Arc - Tangent")/2, "Arc - Tangent", 60-strlen("Arc - Tangent")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the arc - tangent function in radians: "); /*Prompting the user to enter the argument*/
        value=scanf("%f",&arg);
        if (value==0) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = atan(arg); /*Computing result*/
    printf("\nThe results of computing arctan(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the arc - tangent function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the arc - tangent function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the arc - tangent function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
        scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void hsine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Hyperbolic sine' menu and computes the argument of sinh*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Hyperbolic - sine")/2, "Hyperbolic - sine", 60-strlen("Hyperbolic - sine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the hyperbolic sine function in radians: "); /*Prompting the user to enter the argument*/
        value=scanf("%f",&arg);
        if (value==0) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = sinh(arg); /*Computing the result*/
    printf("\nThe results of computing sinh(%.3f) is: %.3f\n",arg,result); /*Printing the result*/
    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the hyperbolic sine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the hyperbolic sine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the hyperbolic sine function? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to compute another argument*/
        scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void hcosine(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Hyperbolic cosine' menu and computes the argument of cosh*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Hyperbolic - cosine")/2, "Hyperbolic - cosine", 60-strlen("Hyperbolic - cosine")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the hyperbolic cosine function in radians: ");
        value=scanf("%f",&arg);
        if (value==0)
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = cosh(arg);
    printf("\nThe results of computing cosh(%.3f) is: %.3f\n",arg,result);
    fflush(stdin);
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the hyperbolic cosine function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the hyperbolic cosine function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the hyperbolic cosine function? (1 for yes, 0 for no): ")/2, "");
        value2 = scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1)
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void htangent(int *scanfvalue, int *scanfvalue2, int *response) /*Displays the 'Hyperbolic tangent' menu and computes the argument of tanh*/
{
    int value, value2, reply;
    float arg, result;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Hyperbolic - tangent")/2, "Hyperbolic - tangent", 60-strlen("Hyperbolic - tangent")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease type the argument of the hyperbolic tangent function in radians: ");
        value=scanf("%f",&arg);
        if (value==0)
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value==0);

    *scanfvalue = value;

    result = tanh(arg);
    printf("\nThe results of computing tanh(%.3f) is: %.3f\n",arg,result);
    fflush(stdin);
    printf("\n________________________________________________________________________________________________________________________\n");

    do
    {
        printf("%*s",60+strlen("Would you like to compute a different argument for the hyperbolic tangent function? (1 for yes, 0 for no): ")/2, "Would you like to compute a different argument for the hyperbolic tangent function? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute a different argument for the hyperbolic tangent function? (1 for yes, 0 for no): ")/2, "");
        value2=scanf("%d",&reply);
        if (value2==0 || reply<0 || reply>1)
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value2==0 || reply<0 || reply>1);

    *scanfvalue2 = value2;
    *response = reply;
}

void logarithm(int *scanfvalue, int *scanfvalue2, int *scanfvalue3, int *response) /*Displays the 'Logarithm' menu and computes the argument of log10 or loge*/
{
    int base;
    float arg, result;
    int value, value2, value3, reply;

    system("cls");
    printf("\n");
    printf("%*s",60+strlen("Logarithm")/2, "Logarithm", 60-strlen("Logarithm")/2, "");
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("\nPlease choose the base (Type '1' for base-e or '2' for base-10): "); /*Prompting the user to choose either log10 or loge*/
        value = scanf("%d",&base);
        if (value==0 || base<1 || base>2) /*Checking user input*/
        {
            printf("\nError: Invalid input.\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }
    }while(value==0 || base<1 || base>2);

    *scanfvalue = value;

    if (base==1) /*If the user selects loge*/
    {
        do
        {
            printf("\nPlease type the argument of the natural logarithm function: "); /*Prompting the user to enter the argument*/
            value2 = scanf("%f",&arg);

            if (value2==0) /*Checking user input*/
            {
                printf("\nError: Invalid input.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0);
        result = log(arg); /*Calculating the result*/
        printf("\nThe natural logarithm of %.2f (loge[%.2f]) is: %.3f\n",arg,arg,result); /*Printing the result*/
    }
    else /*If the user selects log10*/
    {
        do
        {
            printf("\nPlease type the argument of the base-10 logarithm function: "); /*Prompting the user to enter the argument*/
            value2 = scanf("%f",&arg);

            if (value2==0) /*Checking user input*/
            {
                printf("\nError: Invalid input.\n");
                empty_std_buffer();
            }
            else
            {
                empty_std_buffer();
            }

        }while(value2==0);
        result = log10(arg); /*Calculating the result*/
        printf("\nThe base-10 logarithm of %.2f (log10[%.2f]) is: %.3f\n",arg,arg,result); /*Printing the result*/
    }

    *scanfvalue2 = value2;

    fflush(stdin); /*Clearing the buffer*/
    printf("\n________________________________________________________________________________________________________________________\n");
    do
    {
        printf("%*s",60+strlen("Would you like to compute another logarithm? (1 for yes, 0 for no): ")/2, "Would you like to compute another logarithm? (1 for yes, 0 for no): ", 60-strlen("Would you like to compute another logarithm? (1 for yes, 0 for no): ")/2, ""); /*Prompting the user to carry out another calculation*/
        value3 = scanf("%d",&reply);
        if (value3==0 || reply<0 || reply>1) /*Checking user input*/
        {
            printf("\n");
            printf("%*s",60+strlen("Error: Invalid input.")/2, "Error: Invalid input.", 60-strlen("Error: Invalid input. ")/2, "");
            printf("\n\n");
            empty_std_buffer();
        }
        else
        {
            empty_std_buffer();
        }

    }while(value3==0 || reply<0 || reply>1);
    *scanfvalue3 = value3;
    *response = reply;
}
