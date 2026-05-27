#include <stdio.h>
#include <stdlib.h>

#define BIT_0 (1 << 0) // bit 0
#define BIT_3 (1 << 3) // bit 3
#define BIT_4 (1 << 4) // bit 4
#define BIT_5 (1 << 5) // bit 5

int read_bit(int value, int bit_position) {
    // Desloca o bit para a direita e isola com o operador AND (&)
    return (value >> bit_position) & 1;
}

int read_bit_char(unsigned char value, int bit_position) {
    // Desloca o bit para a direita e isola com o operador AND (&)
    return (value >> bit_position) & 1;
}

void byte_to_binary(unsigned char byte, char *result) {
    // Um byte tem 8 bits (do bit 7 ao bit 0)
    for (int i = 7; i >= 0; i--) {
        int bit = read_bit(byte, i); // Isola o bit na posição i
        result[7 - i] = bit ? '1' : '0';
    }
    result[8] = '\0'; // Finaliza a string
}

char *to_binary(unsigned char decimal) {
    static char result[10]; 
    // Um byte tem 8 bits (do bit 7 ao bit 0)
    for (int i = 7; i >= 0; i--) {
        int bit = read_bit(decimal, i); // Isola o bit na posição i
        result[7 - i] = bit ? '1' : '0';
    }
    result[8] = 'b';
    result[9] = '\0'; // Finaliza a string
    return result;
}


int main() {

    printf(" *** Início do programa - bitwise ***.\n\n");

    printf("(1<<0) - %s - %d\n", to_binary(1<<0), (1<<0));
    printf("(1<<1) - %s - %d\n", to_binary(1<<1), (1<<1));
    printf("(1<<2) - %s - %d\n", to_binary(1<<2), (1<<2));
    printf("(1<<3) - %s - %d\n", to_binary(1<<3), (1<<3));
    printf("(1<<4) - %s - %d\n", to_binary(1<<4), (1<<4));
    printf("(1<<5) - %s - %d\n", to_binary(1<<5), (1<<5));
    printf("(2<<2) - %s - %d\n", to_binary(2<<2), (2<<2));
    printf("(3<<2) - %s - %d\n", to_binary(3<<2), (3<<2));  
    printf("\n");


    printf("Leitura de bits usando shift e AND:\n");
    printf("-------------------------------------------------\n");
    
    unsigned char value = 47; // 0 a 255
    char *binary_1 = "00000001b";
    
    printf("%8d in binary %s\n", value, to_binary(value));
    printf("(%d>>0): %3d - %s & %s = %d\n", value, (value >> 0), to_binary((value >> 0)), binary_1, (value >> 0) & 1);
    printf("(%d>>1): %3d - %s & %s = %d\n", value, (value >> 1), to_binary((value >> 1)), binary_1, (value >> 1) & 1);
    printf("(%d>>2): %3d - %s & %s = %d\n", value, (value >> 2), to_binary((value >> 2)), binary_1, (value >> 2) & 1);
    printf("(%d>>3): %3d - %s & %s = %d\n", value, (value >> 3), to_binary((value >> 3)), binary_1, (value >> 3) & 1);
    printf("(%d>>4): %3d - %s & %s = %d\n", value, (value >> 4), to_binary((value >> 4)), binary_1, (value >> 4) & 1);
    printf("(%d>>5): %3d - %s & %s = %d\n", value, (value >> 5), to_binary((value >> 5)), binary_1, (value >> 5) & 1);
    printf("(%d>>6): %3d - %s & %s = %d\n", value, (value >> 6), to_binary((value >> 6)), binary_1, (value >> 6) & 1);
    printf("(%d>>7): %3d - %s & %s = %d\n", value, (value >> 7), to_binary((value >> 7)), binary_1, (value >> 7) & 1);
    printf("\n");


    unsigned char PORT1 =  0; //00000000b
    unsigned char PORT2 = 10; //00001010b
    unsigned char PORT3 = 35; //00100100b
    unsigned char PORT4 = 21; //00010101b
    
    char string_binaria[9]; // Espaço para 8 caracteres + o terminador '\0'

    byte_to_binary(PORT1, string_binaria);
    printf("PORT1: %s\n", string_binaria);

    byte_to_binary(PORT2, string_binaria);
    printf("PORT2: %s\n", string_binaria);

    byte_to_binary(PORT3, string_binaria);
    printf("PORT3: %s\n", string_binaria);

    byte_to_binary(PORT4, string_binaria);
    printf("PORT4: %s\n\n", string_binaria);

    byte_to_binary(BIT_0, string_binaria);
    printf("BIT_0: %s\n", string_binaria);
 
    byte_to_binary(BIT_3, string_binaria);
    printf("BIT_3: %s\n", string_binaria);
 
    byte_to_binary(BIT_5, string_binaria);
    printf("BIT_5: %s\n", string_binaria);

    byte_to_binary(BIT_4, string_binaria);
    printf("BIT_4: %s\n\n", string_binaria);

    //BIT_0(1<<0) - liga bit 0 do PORT1
    printf("(PORT1 |= BIT_0)-> Ligar BIT_0 do PORT1\n");
    PORT1 |= BIT_0; // Equivale a PORT1 = PORT1 | BIT_0, operação PORT1 = 00000000b | 00000001b -> PORT1 = 00000001b
    byte_to_binary(PORT1, string_binaria);
    printf("Novo valor do PORT1: %s\n", string_binaria);
    printf("\n");
    
    // BIT_3(1<<3) - desliga bit 3 do PORT2
    printf("(PORT2 &= ~BIT_3)-> Desligar BIT_3 do PORT2\n");
    PORT2 &= ~BIT_3; // Equivale a PORT2 = PORT2 & ~BIT_3, operação PORT2 = 00001010b & 11110111b -> PORT2 = 00000010b
    byte_to_binary(PORT2, string_binaria);
    printf("Novo valor de PORT2: %s\n", string_binaria);
    printf("\n");

    // BIT_5(1<<5) - alterna o bit 5 do PORT3
    printf("(PORT3 ^= BIT_5)-> Toggle o estado do BIT_5 do PORT3\n");
    PORT3 ^= BIT_5; // Equivale a PORT3 = PORT3 ^ BIT_5, operação PORT3 = 00100100b ^ 00100000b -> PORT3 = 00000100b
    byte_to_binary(PORT3, string_binaria);
    printf("Toggle 1 valor de PORT3: %s\n", string_binaria);
    PORT3 ^= BIT_5; 
    byte_to_binary(PORT3, string_binaria);
    printf("Toggle 2 valor de PORT3: %s\n", string_binaria);
    PORT3 ^= BIT_5; 
    byte_to_binary(PORT3, string_binaria);
    printf("Toggle 3 valor de PORT3: %s\n", string_binaria);
    printf("\n");

    printf("(PORT4 & BIT_4) -> Leitura do bit 4 de PORT4:\n");
    int bit4_in_port4 = (PORT4 & BIT_4) ? 1 : 0; // Verifica se o bit 4 de PORT4 está ligado
    if (bit4_in_port4) {
        printf("O bit 4 de PORT4 está ligado.\n");
    } else {
        printf("O bit 4 de PORT4 está desligado.\n");
    }
    byte_to_binary(bit4_in_port4, string_binaria);
    printf("Valor binário do bit 4 de PORT4: %s\n\n", string_binaria);

    printf("(PORT4 & BIT_5) -> Leitura do bit 5 de PORT4:\n");
    if ((PORT4 & BIT_5)) {
        printf("O bit 5 de PORT4 está ligado.\n");
    } else {
        printf("O bit 5 de PORT4 está desligado.\n");
    }
    byte_to_binary((PORT4 & BIT_5), string_binaria);
    printf("Valor binário do bit 5 de PORT4: %s\n\n", string_binaria);

    printf(" *** Fim do programa. *** \n");
    return 0;
}
