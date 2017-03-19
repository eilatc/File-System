#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void cd(char *inp){}

void previousDirectory(){}

void pwd(){}

void mkfile(char *inp){}

void mkdir(char *inp){}

void ls(){}


void printMenu(){
    printf("\tMain Menu:\n");
    printf("1. Change Sub Directory (cd command)\n");
    printf("2. Change To Previous Directory (cd.. command)\n");
    printf("3. Current Directory\n");
    printf("4. Create New Directory\n");
    printf("5. Create New File\n");
    printf("6. Print directory and file list\n");
    printf("7. Quit\n");


}


int main()
{
    char inp[100] = {0};
    char choice;
    bool notTerminated = true;


    while(notTerminated) {
        printMenu();
        inp[0] = '\0';

        do
            choice = getchar();
        while (isspace(choice));

        fflush(stdout);

        switch (choice) {

            case '1':
                printf("Enter Sub Dir: ");
                scanf("%s",inp);
                cd(inp);
                printf("\n");
                break;

            case '2':
                previousDirectory();
                printf("\n");
                break;

            case '3':
                printf("Current Directory: ");
                pwd();
                printf("\n");
                break;

            case '4':
                printf("Enter New Directory Name: ");
                scanf("%s",inp);
                mkdir(inp);
                printf("\n");
                break;

            case '5':
                printf("Enter New File Name: ");
                scanf("%s",inp);
                mkfile(inp);
                printf("\n");
                break;

            case '6':
                ls();
                printf("\n");
                break;

            case '7':
                notTerminated = false;
                break;
            default:
                break;
        }
    }
    return 0;
}