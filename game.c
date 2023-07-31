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


typedef struct Word
{
    unsigned difficulty;
    unsigned errors;
    unsigned length;
    char letters[MAX_WORD_SIZE];
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
        else if (word->letters[i] == '-')
        {
            printf("-");
        }
        else if ((int)word->letters[i] == 39)
        {
            putchar((char)39);
        }
        else
        {
            printf("_");
        }
        printf(" ");
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

void CheckLetter(Word *word, char input[MAX_WORD_SIZE], char check_mode[10])
{
    bool right_answer = false;
    if (check_mode == "letter_check")
    {

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
            word->errors++;
        }
    }
    else if (check_mode == "word_check")
    {
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

    return;
}

char InputLetter(Word *word)
{
    char input[MAX_WORD_SIZE] = "";
    char letter = ' ';
    int letter_ascii_code = 0;

INPUT:
    scanf("%s", &input);
    letter_ascii_code = (int)input[0];
    fflush(stdin);
    printf("\n");

    if (input[0] == '0')
    {
        return 'S';
    }
    else if (input[0] == '1')
    {
        scanf("%s", &input);
        fflush(stdin);

        CheckLetter(word, input, "word_check");
    }
    else if (input[0] >= 'a' && input[0] <= 'z' || input[0] >= 'A' && input[0] <= 'Z')
    {
        CheckLetter(word, input, "letter_check");
    }
    else
    {
        puts("Input failed! Try again:");
        goto INPUT;
    }
    return ' ';
}

void GameLoop(char selected_word[MAX_WORD_SIZE])
{
    //puts("\n");
    //puts(selected_word);
    //printf("%s \n%d", selected_word, selected_word[13]);
    for (int i = 0; i <= 20; i++)
    {
        printf("%d: %d\n", i, selected_word[i]);
    }
    
    Word *word;
    word = (Word *)malloc(WORD_COUNT * sizeof(Word));
    word->length = strlen(selected_word);
    

    strncpy(word->letters, selected_word, MAX_WORD_SIZE);

    for (int i = 0; i <= word->length; i++)
        word->revealed[i] = false;

    word->errors = 0;

    printf("\nLength:%d\n", word->length);

    do
    {

        printf("Errors: %d\n", word->errors);
        PrintWord(word);

        if (InputLetter(word) == 'S')
            return;

        if (CheckWord(word))
        {
            printf("\nWord solved with %d Errors!\nIt was %s\n\n", word->errors, word->letters);
            break;
        }

    } while (1);
}