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


char **ReadWordListFile()
{
      FILE *word_list;
      char word_list_line[MAX_WORD_SIZE];
      unsigned line = 0;

      word_list = fopen("word_list1.txt", "r");

      char **words = malloc(MAX_WORD_LIST_ITEMS * sizeof *words);
      if (!words)
      {
            return NULL;
      }
      for (int i = 0; i < MAX_WORD_LIST_ITEMS; i++)
      {
            words[i] = malloc(MAX_WORD_SIZE * sizeof *words[i]);
      }

      if (word_list == NULL)
      {
            printf("Opening files failed!");
            return NULL;
      }

      while (fgets(word_list_line, MAX_WORD_SIZE, word_list))
      {
            word_list_line[strcspn(word_list_line, "\n")] = 0;
            strncpy(words[line], word_list_line, MAX_WORD_SIZE);
            line++;
      }

      fclose(word_list);
      return words;
}

unsigned CountStringArray(char *array)
{
      // char word[MAX_WORD_SIZE];

      return 0;
}

int main(int argc, char **argv)
{
      time_t t1;
      srand((unsigned)time(&t1));

      printf("HANGMAN Version 0.1\n\n");

      char **words = ReadWordListFile();
      puts("RWLF passed");
      printf("first list item: %s\n", words[0]);
      GameLoop(words[0]);

      return EXIT_SUCCESS;
}