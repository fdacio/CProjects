#include <stdio.h>

#define FLAG1 (1 << 0) // bit 0
#define FLAG2 (1 << 1) // bit 1
#define FLAG3 (1 << 2) // bit 2
#define FLAG7 (1 << 7) // bit 7

int read_bit(int value, int bit_position) {
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

int main() {
    int flags = 0; //00000000
    char string_binaria[9]; // Espaço para 8 caracteres + o terminador '\0'

    byte_to_binary(flags, string_binaria);
    printf("flags Binario: %s\n\n", string_binaria);

    // Ativar FLAG1
    flags |= FLAG1;
    byte_to_binary(FLAG1, string_binaria);
    printf("FLAG1 Binario: %s\n", string_binaria);
    byte_to_binary(flags, string_binaria);
    printf("flags Binario: %s\n", string_binaria);

    // Ativar FLAG2
    flags |= FLAG2;
    byte_to_binary(FLAG2, string_binaria);
    printf("FLAG2 Binario: %s\n", string_binaria);
    byte_to_binary(flags, string_binaria);
    printf("flags Binario: %s\n", string_binaria);

    // Verificar se FLAG3 está ativo
    if (flags & FLAG3) {
        printf("FLAG3 está ativo!\n");
    }

    byte_to_binary(FLAG3, string_binaria);
    printf("FLAG3 Binario: %s\n", string_binaria);

    byte_to_binary(FLAG7, string_binaria);
    printf("FLAG7 Binario: %s\n", string_binaria);

    byte_to_binary((FLAG7 | FLAG3), string_binaria);
    printf("FLAG7 | FLAG3 Binario: %s\n", string_binaria);

    byte_to_binary((FLAG7 & FLAG3), string_binaria);
    printf("FLAG7 & FLAG3 Binario: %s\n", string_binaria);

    byte_to_binary(~FLAG3, string_binaria);
    printf("~FLAG3 Binario: %s\n", string_binaria);

    byte_to_binary((FLAG7 | ~FLAG3) , string_binaria);
    printf("FLAG7 | ~FLAG3 Binario: %s\n", string_binaria);

    byte_to_binary((FLAG7 & ~FLAG3), string_binaria);
    printf("FLAG7 & ~FLAG3 Binario: %s\n", string_binaria);

    int flag3 = 0;
    byte_to_binary(flag3, string_binaria);
    printf("flag3: %s\n", string_binaria);    
    
    flag3 ^= FLAG3; // Toggle FLAG3
    byte_to_binary(flag3, string_binaria);
    printf("Toggle flag3: %s\n", string_binaria);

    flag3 ^= FLAG3; // Toggle FLAG3
    byte_to_binary(flag3, string_binaria);
    printf("Toggle flag3: %s\n", string_binaria);

    // int variavel = 0b00001010; // O valor 8 em decimal
    // int posicao_bit = 1; // Queremos ler o bit na posição 1 (contando do 0)

    // // Criando a máscara e testando o bit
    // int bit_lido = read_bit(variavel, posicao_bit);
    // printf("Bit na posição %d: %d\n", posicao_bit, bit_lido); // Deve imprimir 1

    // unsigned char meu_byte = 2; // Exemplo de valor (01101001 em binário)
    // char string_binaria[9];       // Espaço para 8 caracteres + o terminador '\0'

    // byte_to_binary(meu_byte, string_binaria);

    // printf("Decimal: %d\n", meu_byte);
    // printf("Binario: %s\n", string_binaria);

    return 0;
}
