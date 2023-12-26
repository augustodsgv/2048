#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "2048.h"
#include "table_library/table.h"

void end_game_input(field * campo){
    char user_input;
    printf("Are you sure you want to leave the game? [y | n]");
    scanf("%c", &user_input);
    while(user_input != 'y' && user_input != 'n'){
        printf("Invalid input \"%c\", type a valid input\n", user_input);
        printf("Are you sure you want to leave the game? [y | n]");
        scanf("%c", &user_input);
    }
    if(user_input == 'n') return;
    printf("Would you like to save this current game? [y | n]: ");
    scanf("%c", &user_input);
    while(user_input != 'y' && user_input != 'n'){
        printf("Invalid input \"%c\", type a valid input\n", user_input);
        printf("Would you like to save this current game? [y | n]: ");
        scanf("%c", &user_input);
    }
    if(user_input == 'y'){
        save_input(campo);
    }
    end_game(campo);
}

void end_game(field * campo){
    system("clear");
    print_field(campo);
    printf("End of the game!\n");
    printf("Your results:\n");
    printf("Score: %d\n", campo->score);
    printf("Hightest number: %d\n", campo->highestNum);
    printf("Moves: %d\n", campo->nMoves);
    exit(0);
}

// Wrapper function that recives the user input and call the save_game function
void save_input(field * campo){
    char * file_name = malloc(sizeof(char) * 10);
    int save_slot;
    printf("Choose a save slot (from 1 to 10): ");
    scanf("%d", &save_slot);
    sprintf(file_name, "saves/save%d.txt", save_slot);
    save_game(campo, file_name);
    printf("Game successfully saved at slot %d!\n", save_slot);
}

// Saves the game parameters in a file called "saveX", where X is a save slot
void save_game(field * campo, char * file_name){
    FILE * arquivo = fopen(file_name, "w");
    // Saving game parameters
    fprintf(arquivo, "%d\n", campo->fieldSize);
    fprintf(arquivo, "%d\n", campo->highestNum);
    fprintf(arquivo, "%d\n", campo->nMoves);
    fprintf(arquivo, "%d\n", campo->nNumbers);
    fprintf(arquivo, "%d\n", campo->score);

    // Saving the field matrix
    for(int i = 0; i < campo->fieldSize; i++){
        for(int j = 0; j < campo->fieldSize; j++){
            fprintf(arquivo, "%d ", campo->matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

// Wrapper function that recives the user input to load a saved game
// TODO : add a controll to do not allow user to load non existing saved games
void load_input(field * campo){
    char * file_name = malloc(sizeof(char) * 10);
    int save_slot;
    char user_input = ' ';
    printf("Choose a save slot to load a game (1 to 10): ");
    scanf("%d", &save_slot);
    sprintf(file_name, "save%d.txt", save_slot);
    printf("Would you like to save this current game? [y | n]: ");
    scanf("%c", &user_input);
    while(user_input != 'y' && user_input != 'n'){
        printf("Invalid input \"%c\", type a valid input\n", user_input);
        printf("Would you like to save this current game? [y | n]: ");
        scanf("%c", &user_input);
    }
    if(user_input == 'y'){
        save_input(campo);
    }
    free(campo);
    campo = load_save(file_name);
}

// Loads a game from a "save.txt" file
field * load_save(char * file_name){
    FILE * arquivo = fopen(file_name, "r");
    // Loading game parameters
    int fieldSize = read_integer_file(arquivo);
    field * campo = build_field(fieldSize);
    campo->highestNum = read_integer_file(arquivo);
    campo->nMoves = read_integer_file(arquivo);
    campo->nNumbers = read_integer_file(arquivo);
    campo->score = read_integer_file(arquivo);
    
    // Loading the game matrix
    for(int i = 0; i < campo->fieldSize; i++)
        for(int j = 0; j < campo->fieldSize; j++){
            campo->matriz[i][j] = read_integer_file(arquivo);
        }

    fclose(arquivo);

    return campo;
}

// Function that reads a number in file and transforms into integer
int read_integer_file(FILE * arquivo){
    int num;
    int i = 0;
    char * read_buffer = malloc(sizeof(char) * 20);
    char read_char = ' ';
    while(read_char == ' ' || read_char == '\n')    // Eliminating spacing characthers from first read
        fread(&read_char, sizeof(char), 1, arquivo);   
    
    // Here, we should verify the character before adding it to the string
    do{
        printf("%c\n", read_char);
        read_buffer[i++] = read_char;
        fread(&read_char, sizeof(char), 1, arquivo);
    }while(read_char != '\n' && read_char != ' ');

    num = strtol(read_buffer, NULL, 10);
    free(read_buffer);
    return num;
}

// Function that allocates and initializes a fiel with inital values
field * build_field(int fieldSize){
    field * new_field = malloc(sizeof(field));
    new_field->fieldSize = fieldSize;
    new_field->matriz = malloc(sizeof(int**) * fieldSize);
    for(int i = 0; i < fieldSize; i++) new_field->matriz[i] = malloc(sizeof(int) * fieldSize);
    for(int i = 0; i < fieldSize; i++)
        for(int j = 0; j < fieldSize; j++)
            new_field->matriz[i][j] = -1;       // -1 indicates a empty field
    srand(time(NULL));              // Initializes the rand genetation
    generate_cicle(new_field);
    generate_cicle(new_field);
    new_field->highestNum = 2;      // The first value starts with 2
    new_field->nMoves = 0;
    new_field->score = 0;           // The score will be calculated by each time you can combine two cells
    return new_field;
}

// Generates a new number in a random (and empty) place of the field
// TODO : the crash bug seems to be here, and about the random generation
int generate_cicle(field * campo){
    int random;
    if(campo->nNumbers >= pow(campo->fieldSize, 2)) return 0;       // O campo está cheio

    /*
    We can make a random position in a matrix by making a random
    between 0 and size² and associating the integer division to
    one index and the rest of the division to the other index.
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
    0, 0, 0, 0, 1, 1, 1, 1, 2, 2,  2,  2,  3,  3,  3,  3,  4
    A concern is about the n², that extrapolates the index.
    */
    random = rand() % (int)(pow(campo->fieldSize, 2));
    printf("ramdom : %d\n", random);
    do{
        int i = (random / campo->fieldSize) % campo->fieldSize;
        int j = random % campo->fieldSize;
        if(campo->matriz[i][j] == -1){
            campo->matriz[i][j] = 2;
            return 1;
        }
        random++;
    }while(1);
}

int is_board_full(field * campo){
    return campo->nNumbers >= pow(campo->fieldSize, 2);       // O campo está cheio
}

// Recieves and treats the user input
int get_input(field * campo){
    char input[10];
    scanf("%s", &input);
    if(!strcmp("up", input) || !strcmp("u", input) || !strcmp("W", input) || !strcmp("cima", input)){
        bottom_up(campo);
        campo->nMoves++;
        return 1;
    }
    if(!strcmp("down", input) || !strcmp("d", input) || !strcmp("S", input) || !strcmp("baixo", input)){
        top_down(campo);
        campo->nMoves++;
        return 1;
    }
    if(!strcmp("right", input) || !strcmp("r", input) || !strcmp("D", input) || !strcmp("direita", input)){
        left_right(campo);
        campo->nMoves++;
        return 1;
    }
    if(!strcmp("left", input) || !strcmp("l", input) || !strcmp("A", input) || !strcmp("esquerda", input)){
        right_left(campo);
        campo->nMoves++;
        return 1;
    }
    if(!strcmp("/SAVE", input)){
        save_input(campo);
        return 1;
    }
    if(!strcmp("/LOAD", input)){
        load_input(campo);
        return 1;
    }
    if(!strcmp("/QUIT", input)){
        end_game_input(campo);
        return 1;
    }
    printf("Comando inválido! Tente novamente!\n");
    return 0;
}

// Moves the cells from left to right
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
                        campo->score += campo->matriz[i][j];        // Increasing score
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

// Moves the cells from right to left
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
                        campo->score += campo->matriz[i][j];        // Increasing score
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

// Moves the cells from top to down
void top_down(field * campo){
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
                        campo->score += campo->matriz[j][i];        // Increasing score
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

// Moves the cells from bottom to up
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
                        campo->score += campo->matriz[j][i];        // Increasing score
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

// Calculates the game parameters according to current state of the field
void calc_game_params(field * campo){
    int nNumbers = 0;
    for(int i = 0; i < campo->fieldSize; i++)
        for(int j = 0; j < campo->fieldSize; j++){
            int currentCell = campo->matriz[i][j];
            if(currentCell != -1){
                nNumbers++;
                if(currentCell > campo->highestNum) campo->highestNum = currentCell;
            }
            
        }
    campo->nNumbers = nNumbers;
}

// Prints the game parameters
void print_game_params(field * campo){
    printf("Score: %d\n", campo->score);
    printf("Moves: %d\n", campo->nMoves);
}

// Prints the field in a grid formatted way
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
            char_matrix[i][j][0] = '\0';
            if(matrix[i][j] != -1)
                sprintf(char_matrix[i][j], "%d", matrix[i][j]);
            else
                strcat(char_matrix[i][j], " ");
        }
    }
    return char_matrix;
}