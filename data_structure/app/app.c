/**
 * gcc app.c ..\list\src\list.c ..\list\src\l_utils.c ..\mfw\src\mfw.c -I..\list\include -I..\mfw\include -o .\build\app.exe; .\build\app.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mfw.h"
#include "mfw_limits.h"
#include "list.h"
#include "l_utils.h"

int main(void) {

    char **words = alloc_words();
    int result = parse_file_words(words);
    if (result != 0) {
        printf("Erro ao carregar palavras do arquivo\n");
        return 1;
    }

    TItemList *list = NULL;
    // Exibe as palavras carregadas
    printf("Adding words to the list:\n");
    srand(time(NULL));
    for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
        int pontos = (rand() % 99) + 1;
        char *nome = words[i];
        int id = get_next_id();
        TItemList *a = new_item_list(id, nome, pontos); // Adiciona a palavra à lista com pontos aleatórios
        add_end_sing_linked(a, &list);
    }

    printf("Sorting list:\n");
    sort_list_by_name(list);
    print_list(list);

    // Libera a memória alocada
    free_words(words);
    free_list(&list);

    return 0;
}

