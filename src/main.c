#include "2048.h"
#include <stdlib.h>

int main(int argc, const char * argv[]){
    // field * campo = load_field_save("saved.txt");

    // /*
    int fieldSize = 4;
    if(argc > 1) fieldSize = (int)strtol(argv[1], NULL, 10);
    field * campo = build_field(fieldSize);
    while(1){
        system("clear");
        calc_game_params(campo);
        print_game_params(campo);
        print_field(campo);
        get_input(campo);
        generate_cicle(campo);
    }
    //*/

    return 0;
}