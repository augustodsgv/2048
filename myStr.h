/*
Arquivo: myStr.h
Autor: Augusto dos Santos
Descrição: Mini biblioteca para lidar com strings de maneira mais fácil em C
Data: 31/10/2023
*/
#ifndef MY_STR
#define MY_STR

int getASCII(char character);
int charToInt(char character);
int nDigitosIntLog(int numero);
int nDigitosIntIt(int numero);
char intToChar(int numero);
char * intToStr(int numero);
int strToint(char * str);   // Transforma uma string (ou char)



#endif  /*MY_STR*/