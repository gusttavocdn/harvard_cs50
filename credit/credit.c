#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t ft_find_size(long int n);
char *ft_itoa(long n);
int validate_card_number(string card_number_string);
int calc_digits_higher_than_ten(int nb);

int main(void)
{

    long card_number = -1;

    while (card_number < 0)
    {
        card_number = get_long("CARD: ");
    }

    string card_number_string = ft_itoa(card_number);
    int card_len = strlen(card_number_string);

    if (card_len != 13 && card_len != 15 && card_len != 16)
    {
        printf("INVALID\n");
        return (0);
    }

    if (!validate_card_number(card_number_string))
    {
        printf("INVALID\n");
        return (0);
    }

    if (card_len == 15)
    {
        if (card_number_string[0] == '3' &&
            (card_number_string[1] == '4' || card_number_string[1] == '7'))
            printf("AMEX\n");

        else
            printf("INVALID\n");

        return (0);
    }

    if (card_number_string[0] == '5' && card_len == 16)
    {
        if (card_number_string[1] < '6')
            printf("MASTERCARD\n");
        else
            printf("INVALID\n");
        return (0);
    }

    printf("VISA\n");
    return (0);
}

int validate_card_number(string card)
{
    int card_len = strlen(card);
    int final_product = 0;
    int i;

    i = card_len - 1;
    while (i > 0)
    {
        int digit = card[i - 1] - '0';
        if (digit * 2 > 9)
            final_product += calc_digits_higher_than_ten(digit * 2);
        else
            final_product += digit * 2;
        i -= 2;
    }

    i = card_len - 1;
    while (i >= 0)
    {
        final_product += card[i] - '0';
        i -= 2;
    }

    return final_product % 10 == 0;
}

int calc_digits_higher_than_ten(int nb)
{
    int result;

    result = 0;
    while (nb > 0)
    {
        result += nb % 10;
        nb = nb / 10;
    }

    return result;
}
char *ft_itoa(long n)
{
    char *str;
    size_t size;
    long int nb;
    size_t i;

    nb = n;
    size = ft_find_size(nb);
    str = (char *)calloc(size, sizeof(char));
    if (nb == 0)
        str[0] = '0';
    if (!str)
        return (NULL);
    i = size - 1;
    if (nb < 0)
    {
        nb *= -1;
        str[0] = '-';
    }
    while (nb > 0)
    {
        str[--i] = (nb % 10) + '0';
        nb = nb / 10;
    }
    str[size - 1] = '\0';
    return (str);
}

size_t ft_find_size(long int n)
{
    size_t i;

    i = 1;
    if (n <= 0)
        i++;
    while (n)
    {
        n = n / 10;
        i++;
    }
    return (i);
}
