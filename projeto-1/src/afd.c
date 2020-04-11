/* 
 * LINGUAGENS FORMAIS E AUTOMATOS
 * 
 * Daniel Dias de Lima      31687679
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define INTEGER 1
#define FLOAT 2
#define ERROR 0

char* format_result (int result)
{
    return 
        result == INTEGER ? "<INTEIRO>" : 
        result == FLOAT ? "<P.FLUTUANTE>" : "<ERRO>";
}

/**
 * utility function for better readability on AFD (scanner)
 * checks if char is plus or minus sign
*/
bool is_signal (char c)
{
    return c == '-' || c == '+';
}

/**
 * utility function for better readability on AFD (scanner)
 * checks if char is point in float point number
 * 
 * commas are not accepted as points
*/
bool is_point (char c)
{
    return c == '.';
}

/**
 * utility function for better readability on AFD (scanner)
 * checks if we reached the end of string on AFD
*/
bool is_end_str (char c)
{
    return c == '\0';
}

int scanner (char *input)
{
    int i = -1;

    q0:
        i++;

        if (is_end_str(input[i])) return ERROR; /*empty string, assuming error*/

        else if (isdigit(input[i])) goto q2;
        else if (is_signal(input[i])) goto q1;
        else goto q5;

    q1:
        i++;

        if (is_end_str(input[i])) return ERROR; /*just a signal, not a number*/
        
        else if (isdigit(input[i])) goto q2;
        else goto q5;

    q2:
        i++;

        if (is_end_str(input[i])) return INTEGER;

        else if (isdigit(input[i])) goto q2;
        else if (is_point(input[i])) goto q3;
        else goto q5;

    q3:
        i++;

        if (is_end_str(input[i])) return ERROR;

        else if (isdigit(input[i])) goto q4;
        else goto q5;

    q4:
        i++;

        if (is_end_str(input[i])) return FLOAT;

        else if (isdigit(input[i])) goto q4;
        else goto q5;

    q5:
        /*dead state or 'poço'*/
        return ERROR;
}

int main(int argc, char **argv)
{
    /*
    "Como resultado, deverá ser gerado um arquivo
    contendo a sequência de itens identificados."
    
    As stated in the assignment, printing the results
    to a external file (on the same dir, named "results.txt")
    as well as printing on the console
    */
    FILE *file;
    char *token;
    char string[50] = "-21 +45.67 0.123 .456 42 23. xx 01234 +00234";

    file = fopen("results.txt", "w");

    if (file == NULL)
    {
        printf("Couldn't open file to print the results");
        exit(EXIT_FAILURE);
    }

    for (token = strtok(string, " "); token != NULL; token = strtok(NULL, " "))
    {
        char *result = format_result(scanner(token));
        fprintf(file, "%s\n", result);
        printf("%s\n", result);
    }

    fclose(file);
    return 0;
}