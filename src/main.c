#include "2048.h"
#include <stdlib.h>

int main(int argc, const char * argv[]){
    int fieldSize = 4;
    if(argc > 1) fieldSize = (int)strtol(argv[1], NULL, 10);
    field * campo = build_field(fieldSize);
    do{
        system("clear");
        calc_game_params(campo);
        print_game_params(campo);
        print_field(campo);
        get_input(campo);
        calc_game_params(campo);
        generate_cicle(campo);
    }while(!is_board_full(campo));
    end_game(campo);
    //*/

    return 0;
}