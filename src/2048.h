#ifndef F2048_C
#define F2048_C

typedef struct field{
    int ** matriz;
    int fieldSize;
    int nNumbers;
    int highestNum;
    int score;
    int nMoves;
}field;
void end_game_input(field * campo);
void end_game(field * campo);

void save_input(field * campo);
void save_game(field * campo, char * file_name);

void load_input(field * campo);
field * load_save(char * file_name);

void calc_game_params(field * campo);
int is_board_full(field * campo);

void print_game_params(field * campo);
field * build_field(int field_size);
int generate_cicle(field * campo);
int get_input(field * campo);
void left_right(field * campo);
void right_left(field * campo);
void top_down(field * campo);
void bottom_up(field * campo);
void print_field(field * campo);
char *** convert_matrix_2048(int ** matrix, int n_lines, int n_columns);

#endif /*F2048*/