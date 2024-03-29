#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define bool int
#define false 0
#define true 1

#define WORD_LENGTH 5
#define WORD_COUNT 1
#define MAX_WORD_SIZE 50
#define MAX_WORD_LIST_ITEMS 100

typedef struct node
{
      char val;
      struct node *next;
} node_t;

void PrintList(node_t *head)
{
      node_t *current = head;

      while (current != NULL)
      {
            printf("%c", current->val);
            current = current->next;
      }
}

void PushList(node_t *head, char val)
{
      node_t *current = head;

      while (current->next != NULL)
      {
            current = current->next;
      }

      current->next = (node_t *)malloc(sizeof(node_t));
      current->next->val = val;
      current->next->next = NULL;
}

typedef struct Word
{
      unsigned difficulty;
      unsigned errors;
      unsigned length;
      char letters[MAX_WORD_SIZE];
      char wrong_letters[100];
      bool revealed[MAX_WORD_SIZE];

} Word;

void PrintWord(Word *word)
{
      for (int i = 0; i < word->length; i++)
      {
            if (word->revealed[i] == true)
            {
                  printf("%c", word->letters[i]);
            }
            else
            {
                  printf("_");
            }
            printf(" ");
      }
      printf("\n");
}

bool SolveWord(Word *word)
{
      unsigned revealed_count = 0;
      for (int i = 0; i < word->length; i++)
      {
            if (word->revealed[i])
                  revealed_count++;
      }
      return revealed_count >= word->length ? true : false;
}

void CheckWord(Word *word, char input[MAX_WORD_SIZE])
{
      bool right_answer = false;
      if (strncpy(word->letters, input, word->length))
      {
            puts("testi1");
            for (int i = 0; i <= word->length; i++)
            {
                  word->revealed[i] = true;
                  right_answer = true;
            }
      }

      if (!right_answer)
      {
            word->errors++;
      }
}

void CheckLetter(Word *word, char input[MAX_WORD_SIZE])
{
      bool right_answer = false;

      for (int i = 0; i < word->length; i++)
      {
            if (tolower(input[0]) == word->letters[i] || toupper(input[0]) == word->letters[i])
            {
                  word->revealed[i] = true;
                  right_answer = true;
            }
            else
            {
                  // linked list with error chars
            }
      }

      if (!right_answer)
      {
            word->errors++;
      }
}

char InputLetter(Word *word)
{
      char input[MAX_WORD_SIZE] = "";
      

INPUT:
      scanf("%s", input);
      fflush(stdin);
      printf("\n");

      if (input[0] == '0')
      {
            return 'S';
      }
      else if (input[0] == '1')
      {
            scanf("%s", input);
            fflush(stdin);

            CheckWord(word, input);
      }
      else if ((input[0] >= 'a' && input[0] <= 'z') || (input[0] >= 'A' && input[0] <= 'Z'))
      {
            CheckLetter(word, input);
      }
      else
      {
            puts("Input failed! Try again:");
            goto INPUT;
      }
      return ' ';
}

void GameLoop(const char *selected_word)
{
      // linked list test
      
      node_t *head = NULL;
      head = (node_t *)malloc(sizeof(node_t));
      if (head == NULL)
            return;

      head->next = NULL;

      //PushList(head, 'c');

      PrintList(head); 
      //
     

      Word *word;
      word = (Word *)malloc(WORD_COUNT * sizeof(Word));
      word->length = strlen(selected_word);

      strncpy(word->letters, selected_word, MAX_WORD_SIZE);

      for (int i = 0; i <= word->length; i++)
      {
            if (word->letters[i] == '-' || (int)word->letters[i] == 39)
            {
                  word->revealed[i] = true;
            }
            else
            {
                  word->revealed[i] = false;
            }
      }

      word->errors = 0;

      printf("\nLength:%d\n", word->length);

      do
      {

            printf("Errors: %d\n", word->errors);
            PrintWord(word);

            if (InputLetter(word) == 'S')
                  return;

            if (SolveWord(word))
            {
                  printf("\nWord solved with %d errors!\nIt was %s\n\n", word->errors, word->letters);
                  break;
            }

      } while (1);

      free(word);
}