#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    printf("Ponteiros para strings\n");
    char *p1;
    char text[80] = "C completo e total";
    printf("%s\n", text);
    printf("%p\n", text);
    p1 = text;
    printf("%p\n", ++p1);
    printf("%p\n", ++p1);

    printf("\n\nPonteiros para inteiros\n");
    int *p2;
    int numbers[5] = {1, 2, 3, 4, 5};

    p2 = numbers;
    while(*p2) {
        printf("%d|%p - ", *p2, p2);
        p2++;
    }
    printf("\n");

    p2 = numbers;
    printf("%d\n",*numbers);
    printf("%p\n", numbers);
    printf("%p\n", ++p2);
    printf("%p\n", ++p2);

    /*
    char *text;
    text = (char*) malloc(80 * sizeof(char));
    if (!text) {
        printf("Memory erro!");
        return 1;
    }
    */
    do
    {
        p1 = text;
        printf("Informe uma palavra: ");
        //gets(text);
        scanf("%s", text);

        printf("Upper Case -> ");
        while (*p1) {   
            printf("%c%c|", (p1 - 1 == text ? '|' : (char)0), toupper(*p1++));
        }
        printf("\n");
        
        p1 = text;
        printf("ASCII -> ");
        while (*p1) {
            char c = *p1;
            printf("%c%c-%d|", (p1 == text) ? '|' : (char)0, c, c);
            p1++;
        }
        printf("\n");

       
        printf("Inverse -> ");
        for (p1 = text + strlen(text) - 1 ; p1 >= text; p1--) {
            printf("%c%c|", (p1 == text + strlen(text) - 1 ? '|' : (char)0), *(p1));
        }
        printf("\n");

    } while (strcmp(text, "done"));
}

