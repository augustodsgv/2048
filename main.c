#include "2048.h"

int main(){
    field * campo = build_field(4);
    while(1){
        print_field(campo);
        get_input(campo);
        generate_cicle(campo);
    }


    return 0;
}