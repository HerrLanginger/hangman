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
            printf("%c ", current->val);
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

bool SearchList(node_t *head, const char val)
{
      node_t *current = head;
      while (current != NULL)
      {
            if (tolower(val) == current->val || toupper(val) == current->val)
            {
                  return true;
            }
            current = current->next;
      }
      return false;
}

typedef struct Word
{
      unsigned difficulty;
      unsigned errors;
      unsigned length;
      char letters[MAX_WORD_SIZE];
      node_t *wrong_letters;
      bool revealed[MAX_WORD_SIZE];

} Word;

struct Word *InitWord(const char *selected_word)
{
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

      word->wrong_letters = NULL;
      word->wrong_letters = (node_t *)malloc(sizeof(node_t));
      if (word->wrong_letters == NULL)
            return NULL;

      word->wrong_letters->next = NULL;

      printf("\nLength:%d\n", word->length);
      return word;
}

void PrintWord(Word *word)
{
      if (word->errors > 0)
      {
            printf("%d Errors: ", word->errors);
            PrintList(word->wrong_letters);
            printf("\n");
      }

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

      if (strncmp(word->letters, input, MAX_WORD_SIZE))
      {
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
      }

      if (!right_answer)
      {
            if (!SearchList(word->wrong_letters, input[0]))
            {
                  word->errors++;
                  PushList(word->wrong_letters, input[0]);
            }
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
            if (SearchList(word->wrong_letters, input[0]))
            {
                  printf("Letter already entered! Try again:\n");
                  goto INPUT;
            }
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
      Word *word = InitWord(selected_word);

      do
      {
            PrintWord(word);

            if (InputLetter(word) == 'S')
                  return;

            if (SolveWord(word))
            {
                  printf("\nWord solved with %d errors!\nIt was %s\n\n", word->errors, word->letters);
                  break;
            }

      } while (1);
}