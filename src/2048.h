#ifndef F2048_C
#define F2048_C

typedef struct field{
    int ** matriz;
    int fieldSize;
    int nNumbers;
    int highestN;
}field;
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