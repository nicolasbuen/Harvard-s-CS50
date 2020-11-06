#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include <ctype.h>

int get_validkey(string A);

int main(int argc, string argv[])
{
    
    //errors
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    
    int validation = get_validkey(argv[1]);
    if (validation == 1)
    {
        printf("key must contain 26 alphabetical characters\n");
        return 1;
    }
    
    //starting some variables
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int values[26];
    int alphalen = strlen(alphabet);
    string key = argv[1];
    
    //prompting the user a plaintext
    string plain_text = get_string("plaintext: ");
    
    //converting key to all uppercase
    char key_upper[alphalen];
    for (int i = 0; i < alphalen; i++)
    {
        if (isupper(key[i]))
        {
            key_upper[i] = key[i];
        }
        else
        {
            char c = (int)key[i] - 32;
            key_upper[i] = c;
        }
    }
    
    //creating the encrypting value array
    for (int i = 0; i < alphalen; i++)
    {
        if ((int)key_upper[i] > (65 + i))
        {
            values[i] = (int)key_upper[i] - (65 + i);
        }
            
        else
        {
            values[i] = ((65 + i) - (int)key_upper[i]) * (-1);
        }
    }
    
    //cyphering the plain text
    int pla1_len = strlen(plain_text); 
    printf("ciphertext: ");
    
    for (int j = 0; j < pla1_len; j++)
    {
        char letter = plain_text[j];
        char *e;
        int index;
        
        if (isalpha(letter))
        {
            if (isupper(letter))
            {
                e = strchr(alphabet, letter);
                index = (int)(e - alphabet);
                printf("%c", (int)letter + values[index]);
            }
            else
            {
                letter = (int)letter - 32;
                e = strchr(alphabet, letter);
                index = (int)(e - alphabet);
                printf("%c", (int)letter + values[index] + 32);
            }
        }
        else
        {
            printf("%c", letter);
        }
    } 
    printf("\n");
    return 0;
}

int get_validkey(string A)
{
    int inputlength = strlen(A);
    if (inputlength != 26)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            //checks if the character is non alphabetical
            if (isalpha(A[i]) == false)
            {
                return 1;
            }
            //checks all characters before A[i] to see if it has already been used 
            for (int j = (i - 1); j >= 0; j--)
            {
                if ((A[j] == A[i]) || (A[j] == A[i] + 32) || (A[j] == A[i] - 32))
                {
                    return 1;
                }
            }
        }
        return 0;
    }

}
