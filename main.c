#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "game.c"

#define bool int
#define false 0
#define true 1

#define MAX_WORD_SIZE 50
#define MAX_WORD_LIST_ITEMS 100

#define RANDOM(min, max) \
      ((rand() % (int)(((max) + 1) - (min))) + (min))

void ReadWordListFile(char *word_list_items[MAX_WORD_LIST_ITEMS][MAX_WORD_SIZE], unsigned *word_list_items_count)
{
      
      return;
}

int main(int argc, char **argv)
{
      time_t t1;
      srand((unsigned)time(&t1));

      printf("HANGMAN Version 0.1\n\n");

      unsigned word_list_items_count = 0;
      char word_list_items[MAX_WORD_LIST_ITEMS][MAX_WORD_SIZE];

      FILE *word_list;
      char word_list_line[MAX_WORD_SIZE];
      unsigned line = 0;

      word_list = fopen("word_list1.txt", "r");
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
            return EXIT_FAILURE;
      }

      fclose(word_list);

      for (int i = 0; i < line; i++)
            printf("%s", word_list_items[i]);

      word_list_items_count = line;

      GameLoop(word_list_items[RANDOM(0, (word_list_items_count - 1))]);

      return EXIT_SUCCESS;
}