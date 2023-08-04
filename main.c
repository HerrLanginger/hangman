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

unsigned CountFileLines(FILE *file)
{
      unsigned line_count = 1;
      char c;
      for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            line_count++;
      puts("cfl1");
      return line_count;
}

char** ReadWordListFile()
{
      //unsigned word_list_items_count = 0;
     
      FILE *word_list;
      char word_list_line[MAX_WORD_SIZE];
      unsigned line = 0;
      puts("cfl1");
      word_list = fopen("word_list1.txt", "r");
       
      printf("Lines%d", CountFileLines(word_list));
    
      unsigned file_lines = CountFileLines(word_list);
      char **words = malloc(file_lines * sizeof(char));
      for (int i = 0; i < file_lines; i++)
      {
            words[i] = (char *)malloc (file_lines * sizeof(char *));
      }
    
      if (word_list != NULL)
      {
            while (!feof(word_list) && !ferror(word_list))
                  while (fgets(word_list_line, MAX_WORD_SIZE, word_list))
                  {
                        word_list_line[strcspn(word_list_line, "\n")] = 0;
                        strncpy(words[line], word_list_line, MAX_WORD_SIZE);
                        line++;
                        puts(word_list_line);
                  }
      }
      else
      {
            printf("Opening files failed!");
      }

      fclose(word_list);
      return words;
}

unsigned CountStringArray(char *array)
{
      //char word[MAX_WORD_SIZE];

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
      return 0;

      GameLoop(words[RANDOM(0, (5 - 1))]);

      return EXIT_SUCCESS;
}