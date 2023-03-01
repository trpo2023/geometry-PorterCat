#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
void circle_zone(float x, float y, float* zone, float num)
{
    zone[0] = x + num;
    zone[1] = y + num;
    zone[2] = x - num;
    zone[3] = y - num;
}


float circle_square(float number) //Count square of sircle figure
{
    return M_PI * number * number;
}
float circle_per(float number) //Count perimetr of sircle figure
{
    return 2 * M_PI * number;
}


int is_it(char* string)
{
    if (!(strcmp(string, "circle")))
    {
        return 3;
    }
    if (!(strcmp(string, "triangle")))
    {
        return 4;
    }
    if (!(strcmp(string, "polygon")))
    {
        return 5;
    }
    return 0;

}

struct figure
{
    int number; // (1. - n.)...
    char* head; // figure(point point, number) from WKT-format file that is entered by terminal
    char figure_type[9]; //circle, triangle, polygon...
    float point[4]; // array = {point1, point2, .....};
    float perimetr; // number of perimetr depends on figure type;
    float area; // number of area depends on figure type;
    float zone[4]; // zone of figure = {point1 + ...., point2 + ...}, depends on figure type;
};

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("You have not entered FILE\n");
        return 1;
    }
    FILE* file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Couldn't open the FILE\n");
        return 2;
    }
    int size = 200; // constant
    char* file_in = malloc(size * sizeof(char)); // information from file
    struct figure* arr_of_fig = malloc(1 * sizeof(struct figure)); // make array of structs

    int index_of_struct = 0;
    int num = 1;
    int points;
    
    while ((file_in = fgets(file_in, size, file)) != NULL)
    {
        arr_of_fig = realloc(arr_of_fig, (index_of_struct + 2) * sizeof(struct figure));
        arr_of_fig[index_of_struct].number = num;
        file_in[strlen(file_in)] = '\0';
        // head into struct
        arr_of_fig[index_of_struct].head = malloc(strlen(file_in) * sizeof(char));
        strcpy(arr_of_fig[index_of_struct].head, file_in);
        //
        // getting
        char* token_del = strtok(file_in, "( ,)");
        int k = 0;
        int index_struct_arr = 0;
        while(token_del != NULL)
        {
            if (k == 0)
            {
                strcpy(arr_of_fig[index_of_struct].figure_type, token_del);
            }
            else
            {
                points = is_it(arr_of_fig[index_of_struct].figure_type);
                if (points == 0)
                {
                    printf("Figure type doesn't exit\n");
                    return 3;
                }
                arr_of_fig[index_of_struct].point[index_struct_arr] = atof(token_del);
                index_struct_arr++;
            }
            token_del = strtok(NULL, "( ,)");
            k++;
        }
        //
        if (points == 3)
        {
            arr_of_fig[index_of_struct].perimetr = circle_per(arr_of_fig[index_of_struct].point[2]);
            arr_of_fig[index_of_struct].area = circle_square(arr_of_fig[index_of_struct].point[2]);
            circle_zone(arr_of_fig[index_of_struct].point[0], 
            arr_of_fig[index_of_struct].point[1], 
            arr_of_fig[index_of_struct].zone, 
            arr_of_fig[index_of_struct].point[2]);
        }
        arr_of_fig = realloc(arr_of_fig, (index_of_struct + 1) * sizeof(struct figure));
        index_of_struct++;
        num++;
    }
    //Print
    for (int i = 0; i < index_of_struct; i++)
    {
        printf("[%i] %s\n", arr_of_fig[i].number, arr_of_fig[i].head);

        for(int j = 0; j < strlen(arr_of_fig[i].head) + 4; j++)
        {
            printf("_");
        }

        printf("\nFigure type: %s \nPerimetr: %f; \nSquare: %f\n", arr_of_fig[i].figure_type, arr_of_fig[i].perimetr, arr_of_fig[i].area);

        printf("\n");
    }
    printf("Complited!\n");
    
    free(arr_of_fig);
    free(file_in);
    fclose(file);
    return 0;
}
