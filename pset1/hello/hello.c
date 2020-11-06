#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    //This will get the user's name and greet him
    string name = get_string("What's your name?\n");
    printf("hello, %s\n", name);
}