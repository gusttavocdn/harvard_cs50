#include <cs50.h>
#include <stdio.h>
#include <math.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float value;
    float tax_value = (bill * tax) / 100;
    float bill_after_tax = bill + tax_value;
    float tip_value = (bill_after_tax * tip) / 100;

    value = (bill + tax_value + tip_value) / 2;

    return value;
}
