/*Briefing on program: 1) This program reads the characters being typed by the user and then proceeds to store these characters in a text file.
                       2) The program then reads the file and only prints the numeric characters.
                       3) Finally the program carries out mathematical calculations to determine the mean, sum, and total number of the numbers being printed.
Date Written: 30/10/2021
Written By: Zaid Daghash */

#include <stdio.h>

float mean(float sum, float N); //Function prototype.

int main(){

    //Declaring 'answer' as a character in-order for the user to type their response when prompted to re-run the program.
    char answer;

    //Encasing the entire body of code with a 'do-while' loop in-order to re-run the program.
    do
    {
        //Declaring more variables.
        char i;
        float MeanVal, sum=0, count=0;

        //Declaring a pointer for the file.
        FILE *fIN;

        //Providing an 'if' condition in-case the file doesn't exist.
        if (fIN==NULL)
        {
            printf("\n The file doesn't exist");
        }

        //Opening the file for writing.
        fIN=fopen("File1.txt","w");

        //Instructing the user to type a set of characters.
        printf("Please type a set of characters without any spaces:\n",i);

        //Using a 'While' loop in-order to print all characters entered by the user to the file.
        while (i!='\n')
        {
            scanf("%c",&i);
            fprintf(fIN,"%c",i);
        }
            fclose(fIN);

        //Opening & reading the characters in the File.
        fIN=fopen("File1.txt","r");
        printf("\nThe File contains the following numbers:");

        //Using a 'Do-while' loop in-order to extract and print the numeric characters only.
        do
        {
            //Fetching one character at a time from the file.
            i=fgetc(fIN);

            //Providing an 'if' statement so that the program identifies the numeric characters based on their 'ASCI' code.
            if(i>=48 && i<=57)
            {
                printf("\n");
                putchar(i);

                //Calculating the sum & the total number of numbers being printed to the screen.
                count++;
                sum=sum+(i-48);
            }

        }while(i!=EOF);

        fclose(fIN);
        MeanVal=mean(sum,count); //Calling the function.
        printf("\nThe total number of numbers in the file is: %.1f",count); //Printing the total number of numbers in the file.
        printf("\nThe sum is: %.1f",sum); //Printing the sum of the numbers.
        printf("\nThe mean is: %.2f",MeanVal); //Printing the mean to two decimal places.
        printf("\nWould you like to run the program again? (y/n)\n",answer); //Prompting the user to re-run the program.
        scanf("%c",&answer);
        fflush(stdin); //Using fflush(stdin) so that the program doesn't display the same values from when the program was first run.

    }while(answer!='n' && answer=='y');

}

float mean(float sum, float N){
    return sum/N;
}

