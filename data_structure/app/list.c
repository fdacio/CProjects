/**
 * gcc list.c ..\list\src\list.c ..\list\src\l_utils.c ..\mfw\src\mfw.c -I..\list\include -I..\mfw\include -o .\build\list.exe; .\build\list.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mfw.h"
#include "mfw_limits.h"
#include "list.h"
#include "l_utils.h"

unsigned long long get_time_microseconds() {
    struct timespec ts;
    // Get the current wall-clock time
    clock_gettime(CLOCK_REALTIME, &ts);
    
    // Convert seconds to microseconds and add fractional nanoseconds converted to microseconds
    return (unsigned long long)ts.tv_sec * 1000000ULL + (unsigned long long)ts.tv_nsec / 1000ULL;
}

int main(int argc, char *argv[]) {  
    
    if (argc < 2) {
        printf("Usage: %s <word_search>\n", argv[0]);
        return 1;
    }

    char **words = alloc_words();
    int result = parse_file_words(words);
    if (result != 0) {
        printf("Error! Could not parse words from the file.\n");
        return 1;
    }

    char *_text_search = argv[1];

    char *sort_method = argc > 2 ? argv[2] : "s"; // Default to selection sort

    TItemList *list = NULL;

    // Exibe as palavras carregadas
    printf("Adding words to the list...\n");
    srand(time(NULL));
    for (int i = 0; i < MAX_WORDS && words[i][0] != '\0'; i++) {
        int pontos = (rand() % 99) + 1;
        char *nome = words[i];
        int id = get_next_id();
        TItemList *a = new_item_list(id, nome, pontos); // Adiciona a palavra à lista com pontos aleatórios
        add_start_sing_linked(a, &list);

    }
    unsigned long long _time_start = 0;
    unsigned long long _time_end = 0;

    if (strcmp(sort_method, "s") == 0) {
        printf("Sorting list by points using selection sort:\n");
        _time_start = get_time_microseconds();
        sort_list_by_points(list);
        _time_end = get_time_microseconds();      
        printf("Time taken selection sort: %llu microseconds\n", _time_end - _time_start);
    } else if (strcmp(sort_method, "b") == 0) {
        printf("Sorting list by points using bubble sort:\n");
        _time_start = get_time_microseconds();
        bubble_sort_by_points(list);
        _time_end = get_time_microseconds();      
        printf("Time taken bubble sort: %llu microseconds\n", _time_end - _time_start);
    } else {
        printf("Invalid sorting method specified. Use 's' for selection sort or 'b' for bubble sort.\n");
    }

    TItemList *_found = find_item_by_name(_text_search, list);
    if (_found != NULL) {
        printf("Found item '%s' Pointer: %p\n", _text_search, (void *)_found);
    } else {
        printf("Item '%s' not found.\n", _text_search);
    }

    // Libera a memória alocada
    free_words(words);
    free_list(&list);

    return 0;
}

