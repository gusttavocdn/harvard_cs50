#include <cs50.h>
#include <stdio.h>

int growth_rate(int start, int end)
{
    int population;
    int years;

    population = start;
    years = 0;
    while (population < end)
    {
        population += (population / 3) - (population / 4);
        years++;
    }
    return (years);
}

int main(void)
{
    int start_size;
    int end_size;
    int years;

    start_size = get_int("Start size: ");
    end_size = get_int("End size: ");

    while (start_size < 9)
    {
        printf("The start size should be greater than 9\n");
        start_size = get_int("Start size: \n");
    }
    while (end_size < start_size)
    {
        printf("The end size should not be less than start size\n");
        end_size = get_int("End size: \n");
    }

    years = growth_rate(start_size, end_size);
    printf("Years: %d", years);
}
