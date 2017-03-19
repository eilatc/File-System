#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Forward Deceleration
void pwd();
void cd(char *inp);
void previousDirectory();
void mkfile(char *inp);
void mkdir(char *inp);
void ls();

struct Node{
    char *nameOfTheFile;
    Node *firstChild;
    Node *nextSibling;
    Node *parent;
    bool isFile;
};

struct Root{
    static Node* root;
    static Node* currentLocation;
};
Node* Root::root = nullptr;
Node* Root::currentLocation = nullptr;

bool validFolderName(char *inp){


    //Empty String
    if(strlen(inp) == 0){
        printf("Invalid name of folder.\n");
        return false;
    }

    //struct of file name
    if(strchr(inp,'.') != nullptr){
        printf("This is a file. try not to use '.' \n");
        return false;
    }

    //Duplicate root
    if(strcmp(inp,"/") == 0){
        printf("Try not to use /. there is only one root folder.\n");
        return false;
    }

    return true;




}

void prepend(char* s, const char* t, bool lastWordBeforeRoot)
{


    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);


    for (i = 0 ; i < len ; ++i)
    {
        s[i] = t[i];
    }

    if(!lastWordBeforeRoot && strcmp(t,"/") != 0){

        memmove(s + 1, s, strlen(s) + 1);
        s[0] = '/';

    }



}



void cd(char *inp){

    if(!validFolderName(inp)) {
        printf("cd: Invalid folder name. \n");
        return;}

    Node *currentFolder = Root::currentLocation->firstChild;

    while(currentFolder != nullptr){

        if(strcmp(currentFolder->nameOfTheFile,inp)==0){
            Root::currentLocation = currentFolder;
            printf("Entering %s \n",inp);
            break;
        }

        currentFolder = currentFolder->nextSibling;

    }


}

void previousDirectory(){

    if(Root::currentLocation->parent == nullptr){
        printf("You already at the root folder.\n");
        return;
    } else{
        Root::currentLocation = Root::currentLocation->parent;
        printf("You are now at: ");
        pwd();
    }

}

void pwd(){

    char currentPath[100] = {0};

    Node *currentFolder = Root::currentLocation;

    while(currentFolder != nullptr){

        if(currentFolder->parent != nullptr && strcmp(currentFolder->parent->nameOfTheFile,"/") == 0){

            prepend(currentPath,currentFolder->nameOfTheFile,true);  }

        else {

            prepend(currentPath, currentFolder->nameOfTheFile, false);
        }

        currentFolder = currentFolder->parent;

    }

    printf("%s \n",currentPath);


}

void mkfile(char *inp){}

void mkdir(char *inp){


    char *nameOfTheFolder;
    nameOfTheFolder = (char *) malloc(sizeof(char) * strlen(inp));
    strcpy(nameOfTheFolder,inp);

    if(!validFolderName(inp)) return;

    Node **currentFolder = &Root::currentLocation;

    //firstChild is nullptr. no nodes at all
    if ((*currentFolder)->firstChild == nullptr){

        (*currentFolder)->firstChild = new Node;
        (*currentFolder)->firstChild->nameOfTheFile = nameOfTheFolder;
        (*currentFolder)->firstChild->firstChild = nullptr;
        (*currentFolder)->firstChild->nextSibling = nullptr;
        (*currentFolder)->firstChild->parent = (*currentFolder);
        (*currentFolder)->firstChild->isFile = false;

    } else {

        Node *newFolder;

            //The name of the new node is less than firstChild so its suppose to be first in the list
            if(strcmp(nameOfTheFolder,(*currentFolder)->firstChild->nameOfTheFile) < 0){

                newFolder = new Node;
                newFolder->nameOfTheFile = nameOfTheFolder;
                newFolder->firstChild = nullptr;
                newFolder->nextSibling = (*currentFolder)->firstChild;
                newFolder->parent = (*currentFolder)->firstChild->parent;
                newFolder->isFile = false;
                (*currentFolder)->firstChild = newFolder;

            } else {
                //finding the right spot for the new node

                Node *prevPointer = (*currentFolder)->firstChild;

                Node *currentLocation = (*currentFolder)->firstChild->nextSibling;

                while(currentLocation != nullptr && strcmp(nameOfTheFolder,currentLocation->nameOfTheFile) > 0 ){

                    prevPointer = currentLocation;

                    currentLocation = currentLocation->nextSibling;

                }

                //Node in between two nodes
                if(currentLocation != nullptr){

                    newFolder = new Node;
                    newFolder->nameOfTheFile = nameOfTheFolder;
                    newFolder->firstChild = nullptr;
                    newFolder->nextSibling = currentLocation;
                    newFolder->parent = currentLocation->parent;
                    newFolder->isFile = false;
                    prevPointer->nextSibling = newFolder;


                }
                //Last Node
                else {

                    currentLocation = new Node;
                    currentLocation->nameOfTheFile = nameOfTheFolder;
                    currentLocation->firstChild = nullptr;
                    currentLocation->nextSibling = nullptr;
                    currentLocation->parent = prevPointer->parent;
                    currentLocation->isFile = false;
                    prevPointer->nextSibling = currentLocation;


                }





            }

        



    }



}

void ls(){

    Node *currentFolder = Root::currentLocation->firstChild;

    printf(". \n");
    printf(".. \n");

    while(currentFolder){

        printf("%s \n",currentFolder->nameOfTheFile);
        currentFolder = currentFolder->nextSibling;

    }


}



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

void initRoot()
{
    Root::root = new Node;
    Root::root->nameOfTheFile = "/";
    Root::root->firstChild = nullptr;
    Root::root->nextSibling = nullptr;
    Root::root->isFile = false;
    Root::root->parent = nullptr;
    Root::currentLocation = Root::root;
}

int main()
{
    char inp[100] = {0};
    char choice;
    bool notTerminated = true;

    initRoot();

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