#include <cs50.h>
#include <stdio.h>

void right_side(int column, int height)
{
    int i;

    i = height;
    while (i > 0)
    {
        if (i > column + 1)
            printf(" ");
        else
            printf("#");
        i--;
    }
}

void left_side(int column)
{
    int i;

    i = 0;
    while (i < column + 1)
    {
        printf("#");
        i++;
    }
}

void render_spaces(int quantity)
{
    int i;

    i = 0;
    while (i < quantity)
    {
        printf(" ");
        i++;
    }
}

void render_pyramid(int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        right_side(i, height);
        render_spaces(2);
        left_side(i);
        printf("\n");
        i++;
    }
}

int main(void)
{
    int height;

    height = 0;
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }
    render_pyramid(height);
}
