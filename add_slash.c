#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* add_slash(const char *text);

void main() {
    
    char frase[80];
    char key;

    do {
        printf("Informe uma frase(exit para sair): ");
        //scanf("%s", &frase);
        fgets(frase, 80, stdin);
        frase[strcspn(frase, "\n")] = '\0';
        printf("Frase original: %s\n", frase);
        printf("Frase com slash: %s\n", add_slash(frase));

    } while (strcmp("exit",frase));
}

// Adiciona um slash(-) onde houver um espaço no parâmetro passado text  
char* add_slash(const char *text) {
    char *aux = (char*)malloc(sizeof(text));
    if (!aux) return NULL;
    char *p = aux;
    while (*text) {
        char c = *text;
        *aux = (c == ' ') ? '-' : c;
        text++;
        aux++;
    }
    return p;

}
