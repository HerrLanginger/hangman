#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "game.c"

#define bool int
#define false 0
#define true 1

#define WORD_LENGTH 5
#define WORD_COUNT 1
#define MAX_WORD_SIZE 50
#define MAX_WORD_LIST_ITEMS 100


int main(int argc, char **argv)
{
    printf("HANGMAN Version 0.1\n\n");

    // READ FILE: WORD-LIST
    FILE *word_list;
    char word_list_items[MAX_WORD_LIST_ITEMS][MAX_WORD_SIZE];
    char word_list_line[MAX_WORD_SIZE];
    int line = 0;

    word_list = fopen("word_list1.txt", "r");
    char word_list_content[100];
    if (word_list != NULL)
    {
        while (!feof(word_list) && !ferror(word_list))
            while (fgets(word_list_line, MAX_WORD_SIZE, word_list))
            {
                word_list_line[strcspn(word_list_line, "\n")] = 0;
                strncpy(word_list_items[line], word_list_line, MAX_WORD_SIZE);
                line++;
            }
    }
    else
    {
        printf("Opening files failed!");
        return 0;
    }

    fclose(word_list);

    for (int i = 0; i < line; i++)
        printf("%s", word_list_items[i]);

    // INITIALIZE WORD

    GameLoop(word_list_items[1]);

    // WORD LOOP

    return EXIT_SUCCESS;
}