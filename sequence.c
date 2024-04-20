
#include <string>
#include <stdlib.h>
#include <stdio.h>

//

// allows a program to execute unix cmd which may be the

// more usefule manner of say parsing

//

// to compile gcc file.c

// to run ./file.exe

//

// global types

const int  gc_line_length=256;

const int  gc_max_arg=10;

const char gc_print[2] = "%s";

char* gs_strings[11];

// prototypes

int input_file();

int parse_string(char ls_string[gc_line_length]);

int run_unix(char command[100]);

// -----------------------------------------------

int input_file()

{

char ls_myString[gc_line_length];

     while(fgets(ls_myString, gc_line_length, stdin))

        {

        parse_string(ls_myString);

        }

     return 0;

}

// -----------------------------------------------

int parse_string(char ls_string[gc_line_length])

{

    int result;

    int li_token_count;

    char delimiters[] = " ";

    printf(gc_print,ls_string);

    char* token = strtok(ls_string, delimiters);

    printf("Token: %s\n", token);

    li_token_count = 0;

    while (token != NULL) {

        gs_strings[li_token_count]=token;

        token = strtok(NULL, delimiters);

        li_token_count = li_token_count + 1;

        printf("Token: %s\n", token);

        for (int i=0;i<li_token_count;i++)

        {

           printf("array: %s\n", gs_strings[i]);

        }

    }
}