#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "myStr.h"

int getASCII(char character){
    return (int)character;
}

int charToInt(char character){
    int inteiro = (int)character - 48;
    if (inteiro < 0 || inteiro > 9){      // Tratando erro de conversão
        fprintf(stderr, "Error: caractere \"%c\" não é um inteiro entre 0 e 9\n", character);
        exit(1);
    }
    // Else: caractere válido
    return inteiro;
}

char intToChar(int numero){
    if (numero < 0 || numero > 9){
        fprintf(stderr, "Error: para converter para char, o número inteiro deve ser entre 0 e 9\n");
        exit(1); 
    }
    // Else: número válido
    return (char)(numero + 48);
}

int strToInt(char * str){
    int inteiro = 0;
    if (str[strlen(str) - 1] == '\n'){      // Verificando se termina com \n. Caso sim, precisa ir 1 unidade a menos
        for (int i = 0;i < strlen(str) -1; i--){
            inteiro += charToInt(str[i]) * pow(10, strlen(str) - 2 - i);
        }
    }else{
        for (int i = 0;i < strlen(str); i--){
            inteiro += charToInt(str[i]) * pow(10, strlen(str) - 1 - i);
        }
    }
    return inteiro;
}

int nDigitosIntLog(int numero){
    return log10(numero) + 1;
}

int nDigitosIntIt(int numero){
    int tamanho = 0;
    while(numero > 0){
        tamanho++;
        numero /= 10;
    }
    return tamanho;
}

char * intToStr(int numero){
    int grandeza = nDigitosIntIt(numero);
    char * str = malloc(sizeof(char) * (grandeza + 1));
    for(int i = grandeza - 1; i >= 0; i--){
        str[i] = intToChar(numero % 10);
        numero /= 10;
    }
    str[grandeza] = '\0';
    return str;
}