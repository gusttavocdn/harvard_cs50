#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void char_to_binary(int c, char *binary);

int main(void)
{
    string phrase = get_string("Text: ");
    int phrase_len = strlen(phrase);
    char matriz[phrase_len][BITS_IN_BYTE + 1];

    for (int i = 0; i < phrase_len; i++)
    {
        char_to_binary(phrase[i], matriz[i]);
    }

    for (int i = 0; i < phrase_len; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
            print_bulb(matriz[i][j] - '0');
        printf("\n");
    }
}

void char_to_binary(int c, char *binary)
{
    int i = 8;

    binary[i] = '\0';
    while (i > 0)
    {
        binary[--i] = c % 2 + '0';
        c = c / 2;
    }
    binary[0] = '0';
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
