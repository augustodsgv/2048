#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "2048.h"
#include "table_library/table.h"

field * build_field(int field_size){
    field * new_field = malloc(sizeof(field));
    new_field->fieldSize = field_size;
    new_field->matriz = malloc(sizeof(int**) * field_size);
    for(int i = 0; i < field_size; i++) new_field->matriz[i] = malloc(sizeof(int) * field_size);
    for(int i = 0; i < field_size; i++)
        for(int j = 0; j < field_size; j++)
            new_field->matriz[i][j] = -1;
    srand(time(NULL));
    generate_cicle(new_field);
    return new_field;
}

int generate_cicle(field * campo){
    int random;
    if(campo->nNumbers >= pow(campo->fieldSize, 2)) return 0;       // O campo está cheio

    random = rand() % (int)(pow(campo->fieldSize, 2));  // size² is so  0 < (random / f_size) < f_size and 0 < (random % f_size) < f_size
    do{
        if(campo->matriz[(int)random / campo->fieldSize][random % campo->fieldSize] == -1)
            campo->matriz[(int)random / campo->fieldSize][random % campo->fieldSize] = 2;
            return 1;
        random++;
    }while(1);
}

int get_input(field * campo){
    char input[10];
    scanf("%s", &input);
    if(!strcmp("up", input) || !strcmp("u", input) || !strcmp("W", input) || !strcmp("cima", input)){
        bottom_up(campo);
        return 1;
    }
    if(!strcmp("down", input) || !strcmp("d", input) || !strcmp("S", input) || !strcmp("baixo", input)){
        up_down(campo);
        return 1;
    }
    if(!strcmp("right", input) || !strcmp("r", input) || !strcmp("D", input) || !strcmp("direita", input)){
        left_right(campo);
        return 1;
    }
    if(!strcmp("left", input) || !strcmp("l", input) || !strcmp("A", input) || !strcmp("esquerda", input)){
        right_left(campo);
        return 1;
    }
    printf("Comando inválido! Tente novamente!\n");
    return 0;
}

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
                    }else if(campo->matriz[i][k] != -1) break;
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
                    }else if(campo->matriz[i][k] != -1) break;
                    
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
                    }else if(campo->matriz[i][k] != -1) break;
                    
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
            if(campo->matriz[j][i] != -1)
                for(int k = j - 1; k >= 0; k--){
                    if(campo->matriz[k][i] == campo->matriz[j][i]){
                        campo->matriz[j][i] += campo->matriz[k][i];   // We could just 2x that, but what if we want something else later...
                        campo->matriz[k][i] = -1;
                    break;                      // It might seem horrible but otherwise we would need to make that "for" ugly   
                    }else if(campo->matriz[k][i] != -1) break;
                    
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
                    }else if(campo->matriz[k][i] != -1) break;
                    
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