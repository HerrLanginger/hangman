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

void InputLetter(Word *word)
{
    char input[MAX_WORD_SIZE] = "";
    char letter = ' ';
    int letter_ascii_code = 0;

INPUT:
    scanf("%s", &input);
    letter_ascii_code = (int)input[0];
    fflush(stdin);
    printf("\n");

    if (input[0] == ' ')
    {
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
    return;
}

void GameLoop(Word *word)
{

}

void IntializeWord(char *selected_word)
{
    
}

int main()
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
        // fgets(word_list_content, 100, word_list);

        while (!feof(word_list) && !ferror(word_list))
            while (fgets(word_list_line, MAX_WORD_SIZE, word_list))
            {
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
    Word *word1;
    word1 = (Word *)malloc(WORD_COUNT * sizeof(Word));
    word1->length = strlen(word_list_items[0]) - 1;

    strncpy(word1->letters, word_list_items[0], MAX_WORD_SIZE);

    for (int i = 0; i <= word1->length; i++)
        word1->revealed[i] = false;

    word1->errors = 0;

    printf("%d\n", word1->length);

    // WORD LOOP
    do
    {

        printf("Errors: %d\n", word1->errors);
        PrintWord(word1);

        InputLetter(word1);

        if (CheckWord(word1))
        {
            printf("\nWord solved with %d Errors!\nIt was %s\n\n", word1->errors, word1->letters);
            break;
        }

    } while (1);

    return 0;
}