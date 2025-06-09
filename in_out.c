#include <stdio.h>
#include <string.h>

unsigned long toBinario(const unsigned int decimal);
unsigned long toBinarioR(const unsigned int decimal);

void main() {

  char nome[80];
  char time[80];
  unsigned int idade;
  char key[1];  
  while (strcmp(key, "x")) {
 
    // printf("Informe uma frase: ");
    // scanf("%s", frase);
    // printf("Sua frase é: %s\n", frase);

    printf("Informe seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Informe seu time do coração: ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = '\0';

    printf("Informe sua idade: ");
    scanf("%d", &idade);    
    //idade[strcspn(idade, "\n")] = '\0';
    
    printf("Você é o(a) %s e torce para o %s e tem %d anos\n\n\n", nome, time, idade);


    printf("x para sair | enter para continuar:");
    scanf("%s", key);

  }
}

