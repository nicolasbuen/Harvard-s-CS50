#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //user input card number
	long card_number = get_long("Number: ");    
    
    long temp_num = card_number;
    int nDigits = 2;
    
    while (temp_num > 100)
    {
        temp_num = temp_num / 10;
        nDigits++;
    }
    
    //nDigits is now the number of digits
    long temp_num2 = card_number;
    int sum = 0;
    int digit;
    int first_two;
    
    for (int i = 0; i < nDigits; i++)
    {
        if (i % 2 == 0)                    
        {
            digit = (temp_num2 % 10);
        }
        else
        {
            digit = (temp_num2 % 10);
            if ((digit * 2) > 9)
            {
                digit = (digit * 2) - 9;
            }
            else
            {
                digit = digit * 2;
            }
        }
        sum = sum + digit;
        temp_num2 = temp_num2 / 10;
        
		//getting the first two digits
        if (temp_num2 < 1000 && temp_num2 > 100) 
        {
            first_two = temp_num2 / 10;
        }
    }
    
    if (sum % 10 == 0)
    {
        if (nDigits == 15 && (first_two == 34 || first_two == 37))
        {
            printf("AMEX\n");
        }
        else if (nDigits == 16 && (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((nDigits == 13 || nDigits == 16) && (first_two / 10) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

