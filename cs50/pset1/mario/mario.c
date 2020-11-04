#include <stdio.h>
#include <cs50.h>

int get_num(void);
void draw_triangle(int height);

int main(void)
{
    int height = get_num();
    draw_triangle(height);
}


//functions below

int get_num(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void draw_triangle(int height)
{
    int control = 1;
    for (int i = 0; i < height; i++)
    {
        
        for (int j = 0; j < (height - control); j++)   //spaces @ beginning of the row
        {
            printf(" ");
        }
        
        for (int j = 0; j < control; j++) //left hashes
        {
            printf("#");
        }
        
        printf("  ");   //gap
        
        for (int j = 0; j < control; j++)   //right hashes
        {
            printf("#");
        }
        printf("\n");
        control++;
    }
}