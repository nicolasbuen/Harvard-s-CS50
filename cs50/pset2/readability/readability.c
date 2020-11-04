#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //define variables
    
    float count_letters = 0;
    float count_sentences = 0;
    float count_words = 0;
    float L;
    float S;
    
    //first, we need to prompt the user text
    
    string text = get_string("> ");
    int string_length = strlen(text);
    
    //getting the number of letter, words, and sentences
    
    for (int i = 0; i < string_length; i++)
    {
        if (((int)text[i] >= 65 && (int)text[i] <= 90) || ((int)text[i] >= 97 && (int)text[i] <= 122))
        {
            count_letters++;
        }
        else if (text[i] == ' ')
        {
            count_words++;
        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count_sentences++;
        }
    }
    
    //readability calculation
    count_words++;
    L = ((count_letters * 100) / count_words) / ((count_words * 100) / count_words) * 100;
    S = ((count_sentences * 100) / count_words) / ((count_words * 100) / count_words) * 100;
    
    
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    
    //print handle
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }
}