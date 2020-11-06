#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    
    //ensure user uses 1 argument
    if (argc != 2)
    {
        printf("Usage ./recover file\n");
        return 1;
    }
    
    //open memory card
    FILE *inputPtr = fopen(argv[1], "r");
    if (inputPtr == NULL)
    {
        printf("Can't open the file!\n");
        return 1;
    }
    
    //defining variables
    int counter = 0;
    char filename[8];
    FILE *outputPtr = NULL; //output pointer to the jpgs
    uint8_t buffer[BLOCKSIZE];
    
    //reading a block at a time and checking if its EOF (feof returns non-zero if its EOF)
    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputPtr) || feof(inputPtr) == 0)
    {

        // Check first four bytes for a jpg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outputPtr != NULL) //checks if isnt the first jpg
            {
                fclose(outputPtr);    //close the file if it isnt the first jpg
            }
            //writing the file name
            sprintf(filename, "%03i.jpg", counter);
        
            //creating a new jpeg file and count +1
            outputPtr = fopen(filename, "w");
            counter++;
        }
        
        if (outputPtr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outputPtr);
        }

    }
    
    //close files to avoid memory leaks
    if (outputPtr != NULL)
    {
        fclose(outputPtr);    
    }
    
    if (outputPtr != NULL)
    {
        fclose(inputPtr); 
    }
    
    return 0;
}
