#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int readability(string phrase);
int count_sentences(string phrase);
int count_letters(string phrase);
int count_words(string phrase);

int main(void)
{
    string phrase = get_string("Text: ");
    int score = readability(phrase);

    if (score < 1)
        printf("Before Grade 1\n");
    else if (score >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", score);
}

int readability(string phrase)
{
    int letters = count_letters(phrase);
    int sentences = count_sentences(phrase);
    int words = count_words(phrase);

    float letter_per_words = (float)letters / words * 100;
    float sentences_per_words = (float)sentences / words * 100;

    return round(0.0588 * letter_per_words - 0.296 * sentences_per_words - 15.8);
}

int count_words(string phrase)
{
    int i = 0;
    int words = 1;

    while (phrase[i] != '\0')
    {
        if (isspace(phrase[i]))
            words++;
        i++;
    }

    return words;
}

int count_letters(string phrase)
{
    int i = 0;
    int letters = 0;

    while (phrase[i] != '\0')
    {
        if (isalpha(phrase[i]))
            letters++;
        i++;
    }

    return letters;
}

int count_sentences(string phrase)
{
    int i = 0;
    int sentences = 0;

    while (phrase[i] != '\0')
    {
        if (phrase[i] == '.' ||
            phrase[i] == '?' ||
            phrase[i] == '!')
            sentences++;
        i++;
    }

    return sentences;
}
