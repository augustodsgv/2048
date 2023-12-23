#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "2048.h"
#include "myStr.h"
#include <math.h>
#include "table_library/table.h"

int main(){
    field * campo = build_field(4);
    /*
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
    */

    while(1){
        print_field(campo);
        get_input(campo);
        generate_cicle(campo);
    }


    return 0;
}