#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "2048.h"
#include "table_library/table.h"

void left_right(field * campo){
    // TODO : investigate use of parallelism here
    // Here, we are adopting a two step approach : first, we add the equals, later, we shift them right
    for(int i = 0; i < campo->fieldSize; i++){  
        // Adding the equals
        for(int j = campo->fieldSize; j >= 1; j--){
            if(campo->matriz[i][j] != -1)  
                for(int k = j - 1; k >= 0; k--){
                    if(campo->matriz[i][k] == campo->matriz[i][j]){
                        campo->matriz[i][j] += campo->matriz[i][k];   // We could just 2x that, but what if we want something else later...
                        campo->matriz[i][k] = -1;
                    break;                      // It might seem horrible but otherwise we would need to make that "for" ugly   
                    }
                }
        }
        // Shifting left
        for(int j = campo->fieldSize; j >= 1; j--){
            if(campo->matriz[i][j] == -1){
                for(int k = j - 1; k >= 0; k--){
                    if(campo->matriz[i][k] != -1){
                        campo->matriz[i][j] = campo->matriz[i][k];
                        campo->matriz[i][k] = -1;
                        break;                  // Again, give it a change, it would be a ugly for  
                    }
                }
            }
        }
    }
}

void right_left(field * campo){
    // TODO : investigate use of parallelism here
    // Here, we are adopting a two step approach : first, we add the equals, later, we shift them right
    for(int i = 0; i < campo->fieldSize; i++){  
        // Adding the equals
        for(int j = 0; j < campo->fieldSize - 1; j++){
            if(campo->matriz[i][j] != -1)  
                for(int k = j + 1; k < campo->fieldSize; k++){
                    if(campo->matriz[i][k] == campo->matriz[i][j]){
                        campo->matriz[i][j] += campo->matriz[i][k];   // We could just 2x that, but what if we want something else later...
                        campo->matriz[i][k] = -1;
                    break;                      // It might seem horrible but otherwise we would need to make that "for" ugly   
                    }
                }
        }
        // Shifting left
        for(int j = 0; j < campo->fieldSize - 1; j++){
            if(campo->matriz[i][j] == -1){
                for(int k = j + 1; k < campo->fieldSize; k++){
                    if(campo->matriz[i][k] != -1){
                        campo->matriz[i][j] = campo->matriz[i][k];
                        campo->matriz[i][k] = -1;
                        break;                  // Again, give it a change, it would be a ugly for  
                    }
                }
            }
        }
    }
}

void up_down(field * campo){
    // TODO : investigate use of parallelism here
    // Here, we are adopting a two step approach : first, we add the equals, later, we shift them right
    for(int i = 0; i < campo->fieldSize; i++){
        // Adding the equals
        for(int j = campo->fieldSize - 1; j >= 1; j--){
            if(campo->matriz[i][j] != -1)
                for(int k = j - 1; k >= 0; k--){
                    if(campo->matriz[k][i] == campo->matriz[j][i]){
                        campo->matriz[j][i] += campo->matriz[k][i];   // We could just 2x that, but what if we want something else later...
                        campo->matriz[k][i] = -1;
                    break;                      // It might seem horrible but otherwise we would need to make that "for" ugly   
                    }
                }
        }

        // Shifting down
        for(int j = campo->fieldSize - 1; j >= 1; j--){
            if(campo->matriz[j][i] == -1){
                for(int k = j - 1; k >= 0; k--){
                    if(campo->matriz[k][i] != -1){
                        campo->matriz[j][i] = campo->matriz[k][i];
                        campo->matriz[k][i] = -1;
                        break;                  // Again, give it a change, it would be a ugly for  
                    }
                }
            }
        }
    }
}

void bottom_up(field * campo){
    // TODO : investigate use of parallelism here
    // Here, we are adopting a two step approach : first, we add the equals, later, we shift them right
    for(int i = 0; i < campo->fieldSize; i++){  
        // Adding the equals
        for(int j = 0; j < campo->fieldSize - 1; j++){
            if(campo->matriz[j][i] != -1)  
                for(int k = j + 1; k < campo->fieldSize; k++){
                    if(campo->matriz[k][i] == campo->matriz[j][i]){
                        campo->matriz[j][i] += campo->matriz[k][i];   // We could just 2x that, but what if we want something else later...
                        campo->matriz[k][i] = -1;
                    break;                      // It might seem horrible but otherwise we would need to make that "for" ugly   
                    }
                }
        }
        // Shifting left
        for(int j = 0; j < campo->fieldSize - 1; j++){
            if(campo->matriz[j][i] == -1){
                for(int k = j + 1; k < campo->fieldSize; k++){
                    if(campo->matriz[k][i] != -1){
                        campo->matriz[j][i] = campo->matriz[k][i];
                        campo->matriz[k][i] = -1;
                        break;                  // Again, give it a change, it would be a ugly for  
                    }
                }
            }
        }
    }
}

void print_field(field * campo){
    char *** converted_matrix = convert_matrix_2048(campo->matriz, campo->fieldSize, campo->fieldSize);
    table_config print_configs;
    print_configs.data_type = "%s";
    print_configs.header = 0;
    print_configs.line_division = 1;
    print_configs.column_division = 0;
    print_table((void***)converted_matrix, campo->fieldSize, campo->fieldSize, NULL, &print_configs);

}
// Função que converte a matriz para string para que as demais funções funcionem adequadamente
// Adaptação da função da biblioteca
char *** convert_matrix_2048(int ** matrix, int n_lines, int n_columns){
    print_matrix((void***)&matrix, n_lines, n_columns, "%d");
    // Alocando a matrix de strings. É necessário um vetor de 3 dimensões pois a string é um vetor unidimensional
    char *** char_matrix = malloc(sizeof(char**) * n_lines);
    for (int i = 0; i < n_lines; i++){
        char_matrix[i] = malloc(sizeof(char*) * n_columns);
        for(int j = 0; j < n_columns; j++){
            char_matrix[i][j] = malloc(sizeof(char) * 5);
            if(matrix[i][j] != -1)
                sprintf(char_matrix[i][j], "%d", matrix[i][j]);
            else
                strcat(char_matrix[i][j], " ");
        }
    }
    return char_matrix;
}