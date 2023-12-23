#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "2048.h"
#include "myStr.h"
#include <math.h>
#include "table_library/table.h"

int main(){
    int ** matrix = malloc(sizeof(int*) * 20);
    field campo;
    campo.fieldSize = 4;
    campo.matriz = matrix;
    for(int i = 0; i < 4; i++) matrix[i] = malloc(sizeof(int) * 4);
    matrix[0][0] = 2;
    matrix[0][1] = 2;
    matrix[0][2] = 2;
    matrix[0][3] = 2;
    matrix[1][0] = 2;
    matrix[1][1] = 2;
    matrix[1][2] = 2;
    matrix[1][3] = 2;
    matrix[2][0] = 2;
    matrix[2][1] = 2;
    matrix[2][2] = 2;
    matrix[2][3] = 2;
    matrix[3][0] = 2;
    matrix[3][1] = 2;
    matrix[3][2] = 2;
    matrix[3][3] = 2;

    print_matrix((void***)&matrix, campo.fieldSize, campo.fieldSize, "%d");

    print_field(&campo);

    up_down(&campo);

    print_field(&campo);

    bottom_up(&campo);

    print_field(&campo);

    right_left(&campo);

    print_field(&campo);

    left_right(&campo);

    print_field(&campo);


    return 0;
}