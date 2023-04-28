#include "checkFunctions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <math.h>


int checkCircleNum(char* line)
{

    //Проверяем точки центра
    line = realloc(line, (strlen(line) + 1) * sizeof(char));
    line[strlen(line) + 1] = '\n';

    int commas = 0;
    int center_digits = 0, radius_digits = 0;
    int flag_comma = 0;
    int i = 0;
    //Проверяем корректность ввода координат центра

    while(line[i] != '\n')
    {

        if(isalpha(line[i]))
        {
            return 0;
        }

        if(isblank(line[i]))
        {
            i++;
            continue;
        }

        if(line[i] == ',')
        {
            commas++;
            i++;
            flag_comma = 1;
            continue;
        }

        if(line[i] == '-')
        {
            if(flag_comma)
            {
                return 0;
            }

            if(!(isdigit(line[i+1])))
            {
                return 0;
            }
            i++;
            continue;
        }

        if(isdigit(line[i]))
        {
            if(flag_comma)
            {
                radius_digits++;
            }
            else
            {
                center_digits++;
            }
            while((isdigit(line[i])) || line[i] == '.')
            {
                i++;
            }
            continue;
        }

        i++;
    }

    //For circle
    if(center_digits != 2 || radius_digits != 1 || commas != 1)
    {
        return 0;
    }

    return 1;
}

// checkNumber(char* string, int n_line)
// {
//     if (!(strcmp(string, "circle")))
//     {
//         checkCircleNum(line, n_line);
//     }
//     if (!(strcmp(string, "triangle")))
//     {
//         //
//     }
//     if (!(strcmp(string, "polygon")))
//     {
//         //
//     }

// }

void structLetters(char* line)
{
    for(size_t i = 0; i < strlen(line); i++)
    {
        if(isupper(line[i]))
        {   
            line[i] = tolower(line[i]);
        }
    }
}

int figureNameCheck(char* string, int n_line, char** structs) //проверяем название фигур
{

    int flag_founded = 0;
    for(int i = 0; i < 2; i++)
    {
        if(!(strcmp(structs[i], string)))
        {
            flag_founded = 1;
            break;
        }
    }

    if(!(flag_founded))
    {
        printf("[%d line]: ERROR! Syntaxis problem: %s\n\n", n_line, string);
        return 0;
    }

    return 1;

}

int checkLine(char* line, int n_line)
{
    char* structs[2] = {
        "circle", "triangle"
    };

    int pointer = 0;
    int flag_a = 0;
    int n_word = 0;
    int o_brackets = 0, c_brackets = 0;
    char* buffer = (char*)malloc(2);
    for(int j = 0; line[pointer] != '(' ; pointer++)
    {   
        if(!(isblank(line[pointer])))
        {
            if(!flag_a)
            {
                n_word++;
                flag_a = 1;
            }
            buffer[j] = line[pointer];
            buffer = (char*)realloc(buffer, 2*(j + 1));
            buffer[2*(j+1)] = '\0';
            j++;
        }
        else
        {
            flag_a = 0;
        }

        if(line[pointer] == '\0' || line[pointer] == '\n')
        {
            
            printf("[%d line]: ERROR! Expected \'(\'\n: %s", n_line, line);
            free(buffer);
            return 0;
        }
    }

    if(n_word == 0)
    {
        printf("[%d line]: ERROR! No struct: %s\n", n_line, line);
        free(buffer);
        return 0;
    }

    if(n_word != 1)
    {
        printf("[%d line]: ERROR! Too many structs or there is extra space between letters: %s\n", n_line, line);
        free(buffer);
        return 0;
    }


    structLetters(buffer); //регистр

    if(!(figureNameCheck(buffer, n_line, structs)))
    {
        free(buffer);  
        return 0;
    }
 

    
    for(int j = 0; (line[pointer] != '\n'); pointer++)
    {
        if(line[pointer] == '\0')
        {
            break;
        }

        if(line[pointer] == '(')
        {
            o_brackets++;
            continue;
        }

        if(line[pointer] == ')')
        {
            c_brackets++;
            continue;
        }

        buffer[j] = line[pointer];
        j++;

    }


    if(c_brackets != o_brackets)
    {
        printf("[%d line]: ERROR! Lost \'(\' or \')\\n': %s", n_line, line);
        free(buffer);
        return 0;
    }

    if(!(checkCircleNum(buffer)))
    {
        printf("[%d line]: ERROR! Parametr problem: %s\n", n_line, line);
        free(buffer);
        return 0;
    }

    free(buffer);
    return 1;
}




// int checking(int argc, char* argv[])
// {

//     if (argc != 2) {
//         printf("You have not entered the FILE\n");
//         return 1;
//     }

//     FILE* file;
//     file = fopen(argv[1], "r");

//     if (file == NULL) {
//         printf("Couldn't open the FILE\n");
//         return 2;
//     }
//     int n_line = 0;
//     char line[256];
//     while((fgets(line, 256, file))!=NULL)
//     {
//         n_line ++;
//         if(!(checkLine(line, n_line)))
//         {

//         }
//         else 
//         {
//             printf("[%d line]: Everyting is okay\n", n_line);
//         }

//     }

//     fclose(file);
// }
