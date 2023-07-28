#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define false 0
#define true 1

#define WORD_LENGTH 5
#define WORD_COUNT 1

typedef struct Word
{
    char *word;
    unsigned length;
    char *letters;
    bool *revealed;
    unsigned errors;
} Word;

void PrintWord(Word *word)
{
    for (int i = 0; i < word->length; i++)
    {
        if (word->revealed[i] == true)
        {
            printf("%c ", word->letters[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
    return;
}

bool CheckWord(Word *word)
{
    unsigned revealed_count = 0;
    for (int i = 0; i < word->length; i++)
    {
        if (word->revealed[i])
            revealed_count++;
    }
    return revealed_count >= word->length ? true : false;
}

void InputLetter(Word *word)
{
    char input[100] = "";
    char letter = ' ';

INPUT:
    scanf("%s", &input);
    fflush(stdin);
    printf("\n");
    letter = input[0];

    switch (letter)
    {
    case ' ':
        puts("Input failed!");
        goto INPUT;
        break;

    case '1':
        scanf("%s", &input);
        fflush(stdin);

        if (strncpy(word->word, input, WORD_LENGTH))
        {
            puts("testi1");
            for (int i = 0; i <= word->length; i++)
            {
                word->revealed[i] = true;
            }
        }
        break;

    default:
        break;
    }
    

    bool right_answer = false;
        for (int i = 0; i < word->length; i++)
        {
            if (letter == word->letters[i])
            {
                word->revealed[i] = true;
                right_answer = true;
            }
        }

        if (!right_answer)
        {
            word->errors++;
        }
    return;
}

int main()
{
    printf("HANGMAN Version 0.1\n\n");

    // READ FILE: WORD-LIST
    FILE *word_list;
    word_list = fopen("word_list1.txt", "r");
    char word_list_content[100];
    if (word_list != NULL)
    {
        fgets(word_list_content, 100, word_list);
    }
    else
    {
        printf("Opening files failed!");
        return 0;
    }

    printf("%s", word_list_content);

    //INITIALIZE WORD
    Word *word1;
    word1 = (Word *)malloc(WORD_COUNT * sizeof(Word));
   
    strncpy(word1->word, word_list_content, 6);
 
    word1->letters = (char *)malloc(WORD_LENGTH * sizeof(char));
    word1->length = 0;
    for (int i = 0; i <= sizeof(word1->word); i++)
    {
        word1->letters[i] = word1->word[i];
        word1->length++;
    }
    
    word1->revealed = (bool *)malloc(WORD_LENGTH * sizeof(bool));
    puts("test");
    // CRASH HERE
    for (int i = 0; i <= word1->length; i++)
        word1->revealed[i] = false;


    word1->errors = 0;


    printf("%d", word1->length);

    //WORD LOOP
    do
    {

        printf("Errors: %d\n", word1->errors);
        PrintWord(word1);

        InputLetter(word1);

        if (CheckWord(word1))
        {
            printf("\nWord solved with %d Errors!\nIt was %s\n\n", word1->errors, word1->word);
            break;
        }

    } while (1);

    return 0;
}