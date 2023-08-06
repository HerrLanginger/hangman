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

unsigned CountFileLines()
{
      FILE *file = fopen("word_list1.txt", "r");

      unsigned lines = 1;
      char ch;
      while (!feof(file))
      {
            ch = fgetc(file);
            if (ch == '\n')
            {
                  lines++;
            }
      }
      return lines;
}

char **ReadWordListFile()
{
      FILE *word_list;
      char word_list_line[MAX_WORD_SIZE];
      unsigned line = 0;

      word_list = fopen("word_list1.txt", "r");

      unsigned file_lines = CountFileLines(word_list);
      printf("%d", file_lines);
      char **words = malloc(file_lines * sizeof *words);
      if (!words)
      {
            return NULL;
      }
      for (int i = 0; i < file_lines; i++)
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
      puts("test after RWLF");
      printf("%s", words[0]);

      GameLoop(words[RANDOM(0, (5 - 1))]);

      return EXIT_SUCCESS;
}