#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "geometrylib/geometrylib.h"


float circle_per(float radius)
{
    return 2 * M_PI * radius;
}

float circle_square(float radius)
{
    return M_PI * pow(radius, 2);
}

float polygon_tri_per(double** point, int n) //Count perimetr of triangle figure
{
    float sum = 0;

    for(int i = 0; i < n; i++)
    {
        if(i == n-1 )
        {
            sum += sqrt(pow(point[i][0] - point[0][0], 2) + pow(point[i][1] - point[0][1], 2));
        } 
        else 
        {
            sum += sqrt(pow(point[i][0] - point[i+1][0], 2) + pow(point[i][1] - point[i+1][1], 2));
        }
    }

    return sum;
}

float polygon_tri_square(double** point, int n) //Count square of triangle figure
{
    float sum = 0;
    
    //Алгоритм шнурования
    for(int i = 0; i < n; i++)
    {
        if(i != n-1)
        {
            sum += point[i][0] * point[i+1][1];
        }
        else
        {
            sum += point[i][0] * point[0][1];
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(i != n-1)
        {
            sum -= point[i][1] * point[i+1][0];
        }
        else
        {
            sum -= point[i][1] * point[0][0];
        }
    }
    sum = fabs(sum);
    return 0.5 * sum;
}

struct figure
{
    int number; // (1. - n.)...
    char* figure_type; //triangle, circle, polygon...
    char* head; // figure((point x, point y), (point x, point y), (point x, point y) ... ) from WKT-format file that is entered by terminal
    double** points; //array of {(x1, y1), (x2, y2), (x3, y3)...(xn, yn)}
    double radius;
    int n_points;
    float perimetr; 
    float square; 
};

int circle_intersection(struct figure circle1, struct figure circle2)
{
    double sum_radius, sum;
    sum_radius = circle1.radius + circle2.radius;
    sum = sqrt(pow(circle1.points[0][0] - circle2.points[0][0], 2) + pow(circle2.points[0][1] - circle2.points[0][1], 2));
    if (sum <= sum_radius)
    {
        return 1;
    } else
    {
        return 0;
    }
}

int type_is(char* string)
{
    if (!(strcmp(string, "circle")))
    {
        return 3;
    }
    if (!(strcmp(string, "triangle")))
    {
        return 4;
    }
    return 0;

}




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

    int input_size = 100;

    char* input = malloc(input_size * sizeof(char)); // information from file
    struct figure* figures = malloc(1 * sizeof(struct figure)); // make array of structs

    int index_of_struct = 0;
    int num = 1;
    int figure_type_index;

    while ((input = fgets(input, input_size, file)) != NULL)
    {
        if(checkLine(input, num))
        {
            char* token = "((, ),(, ),(, ))";
            figures = realloc(figures, (index_of_struct + 1)* sizeof(struct figure)); // remake array of structs of figures
            char str[strlen(input)];
            strcpy(str, input);
            char* i_str;
            //узнаём тип фигуры
            i_str = strtok(str, token);
            figures[index_of_struct].figure_type = malloc(strlen(i_str) * sizeof(char));
            str[strlen(str)] = '\0';
            figures[index_of_struct].head = malloc(strlen(str) * sizeof(char));
            strcpy(figures[index_of_struct].head, str);
            figures[index_of_struct].number = num;

            strcpy(figures[index_of_struct].figure_type, i_str);

            structLetters(figures[index_of_struct].figure_type); //регистр

            figure_type_index = type_is(figures[index_of_struct].figure_type);
            if (figure_type_index == 0)
            {
                printf("Figure type doesn't exit\n");
                return 3;
            }

            figures[index_of_struct].points = (double**)malloc(1 * sizeof(double*)); //выделяем память под массив координат (пока что под одну пару);
    
            figures[index_of_struct].n_points = 0;


            if(figure_type_index == 3) //круг (две точки + радиус)
            {
                token = "( ,)";
                int i = 0;
                while (i_str != NULL)
                {   
                    figures[index_of_struct].points[i] = (double*)malloc(2 * sizeof(double)); //выделяем память под пару координат;
                    i_str = strtok(NULL, token);
                    if(i_str != NULL)
                    {
                    figures[index_of_struct].points[i][0] = atof(i_str);
                    }
                    i_str = strtok(NULL, token);
                    if(i_str != NULL)
                    {
                    figures[index_of_struct].points[i][1] = atof(i_str);
                    }
                    i++;
                    i_str = strtok(NULL, token);
                    
                    if(i_str != NULL)
                    {
                    figures[index_of_struct].radius = atof(i_str); //радиус записываем, как третью координату 
                    }

                    figures[index_of_struct].points = (double**)realloc(figures[index_of_struct].points, (i + 1) * sizeof(double*));
                    figures[index_of_struct].n_points++ ;
                }
            }

            if(figure_type_index == 4 || figure_type_index == 5) //трегольник    
            {
                token = "( , )";
                int i = 0;
                while (i_str != NULL)
                {   
                    figures[index_of_struct].points[i] = (double*)malloc(2 * sizeof(double)); //выделяем память под пару координат;
                    i_str = strtok(NULL, token);
                    if(i_str != NULL)
                    {
                    figures[index_of_struct].points[i][0] = atof(i_str);
                    }
                    i_str = strtok(NULL, token);
                    if(i_str != NULL)
                    {
                    figures[index_of_struct].points[i][1] = atof(i_str);
                    }
                    i++;

                    figures[index_of_struct].points = (double**)realloc(figures[index_of_struct].points, (i + 1) * sizeof(double*));
                    figures[index_of_struct].n_points ++ ;
                }
            }

            figures[index_of_struct].n_points--;

            switch(figure_type_index)
            {
                case 3:
                    figures[index_of_struct].perimetr = circle_per(figures[index_of_struct].radius);
                    figures[index_of_struct].square = circle_square(figures[index_of_struct].radius);
                    break;
                case 4:
                    figures[index_of_struct].perimetr = polygon_tri_per(figures[index_of_struct].points, figures[index_of_struct].n_points);
                    figures[index_of_struct].square = polygon_tri_square(figures[index_of_struct].points, figures[index_of_struct].n_points);
                    break;
            }

            //print
            printf("[%d line] ", num);
            printf("%s\n", figures[index_of_struct].figure_type);
            printf("Perimetr: %f\n", figures[index_of_struct].perimetr);
            printf("Square: %f\n", figures[index_of_struct].square);
            printf("Number of points: %d\n", figures[index_of_struct].n_points);

            if (!(strcmp(figures[index_of_struct].figure_type, "circle")))
            {
                printf("Radius: %f\n", figures[index_of_struct].radius);
            }
        
            for(int i = 0; i < figures[index_of_struct].n_points; i++)
            {
                printf("{%.2f, %.2f} ", figures[index_of_struct].points[i][0], figures[index_of_struct].points[i][1]);
            }
            printf("\n\n");
            index_of_struct++;
        }
        index_of_struct++;
        num++;
    }



    return 0;

} 
