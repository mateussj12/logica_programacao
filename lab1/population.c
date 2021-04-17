#include <cs50.h>
#include <stdio.h>

int main(void)
{

    //Variables
    int start;
    int end;
    int year;
    int new_year;
    int old_year;

    //Get Dados
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    //Swap Data
    year = 0;
    new_year = start;


    //Algorithm to calculate received values
    for (old_year = start; new_year < end; year++)
    {
        new_year = new_year + old_year/3 - old_year/4;
        old_year = new_year;
    }

    //Data output
    printf("Years: %i\n ", year);



}

