#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //initializes a new 2D array
    RGBTRIPLE oldimage[height][width];
    
    //copy the image in the new 2D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oldimage[i][j] = image[i][j];
        }
    }
    
    //iterates through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculates the average value of the RGB in the pixel and assigns each color to it
            int avg = round((oldimage[i][j].rgbtBlue + oldimage[i][j].rgbtGreen + oldimage[i][j].rgbtRed)/3.0);
            
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //initializes a new 2D array
    RGBTRIPLE oldimage[height][width];
    
    //copy the image in the new 2D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oldimage[i][j] = image[i][j];
        }
    }
    
    //iterates through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //define the halfwidth of the image as a int (to round up)
            int halfwidth = width / 2;
            
            //define the new position of the pixel
            int newpos = width - j - 1;
            
            //inverts it widthpos
            image[i][j] = oldimage[i][newpos];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE imgCopy[height][width];
	float avgRed;
	float avgGreen;
	float avgBlue;

	//create a copy of original image to save original pixel values
	for (int row = 0; row < height; row++)
	{
		for (int w = 0; w < width; w++)
		{
			imgCopy[row][w].rgbtRed = image[row][w].rgbtRed;
			imgCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			imgCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;
		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			//if the pixel is on the top left edge
			if (w == 0 && h == 0)
			{
				avgRed = (float)(imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 4;

				avgGreen = (float)(imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgBlue = round(avgBlue);
				avgGreen = round(avgGreen);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on the lower left edge
			else if (w == 0 && h == (height - 1))
			{
				avgRed =(float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 4;

				avgGreen = (float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on top Right
			else if (h == 0 && w == (width - 1))
			{
				avgRed = (float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed)/ 4;

				avgGreen = (float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 4;

				avgBlue = (float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on lower right
			else if(h == (height - 1) && w == (width - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed) / 4;

		 		avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue) / 4;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on left side

			else if (w == 0 && (h > 0 && h < height - 1))
			{
				avgRed = (float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on right side
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
                                image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on upper side
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				avgRed = (float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on lower side
			else if (h == height - 1 && (w > 0 && w < width - 1))
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 6;

				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 6;
				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on the middle and can form a 3x3 grid
			else
			{
				avgRed = (float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 9;
				avgGreen = (float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 9;
				avgBlue = (float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 9;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //initializes a new 2D array
    RGBTRIPLE imgCopy[height][width];
    
    //copy the image in the new 2D array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgCopy[i][j] = image[i][j];
        }
    }
    
    //iterates through each pixel of the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gXRed = 0;
            int gYRed = 0;
            int gXBlue = 0;
            int gYBlue = 0;
            int gXGreen = 0;
            int gYGreen = 0;
            
            //if its a middle pixel
            if (h != 0 && h != (height - 1) && w != 0 && w != (width - 1))
            {
                //Gx calculation
                gXRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + 0*imgCopy[h-1][w].rgbtRed + 1*imgCopy[h-1][w+1].rgbtRed + (-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed + (-1)*imgCopy[h+1][w-1].rgbtRed + 0*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gXBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + 0*imgCopy[h-1][w].rgbtBlue + 1*imgCopy[h-1][w+1].rgbtBlue + (-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue + (-1)*imgCopy[h+1][w-1].rgbtBlue + 0*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gXGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + 0*imgCopy[h-1][w].rgbtGreen + 1*imgCopy[h-1][w+1].rgbtGreen + (-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen + (-1)*imgCopy[h+1][w-1].rgbtGreen + 0*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*imgCopy[h-1][w+1].rgbtRed + (0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (1)*imgCopy[h+1][w-1].rgbtRed + 2*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gYBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*imgCopy[h-1][w+1].rgbtBlue + (0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (1)*imgCopy[h+1][w-1].rgbtBlue + 2*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gYGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*imgCopy[h-1][w+1].rgbtGreen + (0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen +  (1)*imgCopy[h+1][w-1].rgbtGreen + 2*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //if its a top-mid pixel
            else if (h == 0 && w != 0 && w != (width - 1))
            {
                //Gx calculation
                gXRed = ((-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed + (-1)*imgCopy[h+1][w-1].rgbtRed + 0*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gXBlue = ((-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue + (-1)*imgCopy[h+1][w-1].rgbtBlue + 0*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gXGreen = ( (-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen + (-1)*imgCopy[h+1][w-1].rgbtGreen + 0*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (1)*imgCopy[h+1][w-1].rgbtRed + 2*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gYBlue = ((0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (1)*imgCopy[h+1][w-1].rgbtBlue + 2*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gYGreen = ((0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen + (1)*imgCopy[h+1][w-1].rgbtGreen + 2*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //if its a bottom-mid pixel
            else if (h == (height - 1) && w != 0 && w != (width - 1))
            {
                //Gx calculation
                gXRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + 0*imgCopy[h-1][w].rgbtRed + 1*imgCopy[h-1][w+1].rgbtRed + (-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed);
                gXBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + 0*imgCopy[h-1][w].rgbtBlue + 1*imgCopy[h-1][w+1].rgbtBlue + (-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue);
                gXGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + 0*imgCopy[h-1][w].rgbtGreen + 1*imgCopy[h-1][w+1].rgbtGreen + (-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*imgCopy[h-1][w+1].rgbtRed + (0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed);
                gYBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*imgCopy[h-1][w+1].rgbtBlue + (0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue);
                gYGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*imgCopy[h-1][w+1].rgbtGreen + (0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //if its a far left pixel
            else if (h != 0 && h != (height - 1) && w == 0)
            {
                //Gx calculation
                gXRed = ((-1)*0 + 0*imgCopy[h-1][w].rgbtRed + 1*imgCopy[h-1][w+1].rgbtRed + (-2)*0 + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed + (-1)*0 + 0*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gXBlue = ((-1)*0 + 0*imgCopy[h-1][w].rgbtBlue + 1*imgCopy[h-1][w+1].rgbtBlue + (-2)*0 + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue + (-1)*0 + 0*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gXGreen = ((-1)*0 + 0*imgCopy[h-1][w].rgbtGreen + 1*imgCopy[h-1][w+1].rgbtGreen + (-2)*0 + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen + (-1)*0 + 0*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*imgCopy[h-1][w+1].rgbtRed + (0)*0 + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (1)*0 + 2*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gYBlue = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*imgCopy[h-1][w+1].rgbtBlue + (0)*0 + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (1)*0 + 2*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gYGreen = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*imgCopy[h-1][w+1].rgbtGreen + (0)*0 + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen + (1)*0 + 2*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
           
           //if its a far right pixel
           else if (h != 0 && h != (height - 1) && w == (width - 1))
            {
                //Gx calculation
                gXRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + 0*imgCopy[h-1][w].rgbtRed + 1*0 + (-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*0 + (-1)*imgCopy[h+1][w-1].rgbtRed + 0*imgCopy[h+1][w].rgbtRed + 1*0);
                gXBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + 0*imgCopy[h-1][w].rgbtBlue + 1*0 + (-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*0 + (-1)*imgCopy[h+1][w-1].rgbtBlue + 0*imgCopy[h+1][w].rgbtBlue + 1*0);
                gXGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + 0*imgCopy[h-1][w].rgbtGreen + 1*0 +(-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*0 + (-1)*imgCopy[h+1][w-1].rgbtGreen + 0*imgCopy[h+1][w].rgbtGreen + 1*0);
                
                //Gy calculation
                gYRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*0 + (0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*0 + (1)*imgCopy[h+1][w-1].rgbtRed + 2*imgCopy[h+1][w].rgbtRed + 1*0);
                gYBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*0 + (0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*0 + (1)*imgCopy[h+1][w-1].rgbtBlue + 2*imgCopy[h+1][w].rgbtBlue + 1*0);
                gYGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*0 + (0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*0 + (1)*imgCopy[h+1][w-1].rgbtGreen + 2*imgCopy[h+1][w].rgbtGreen + 1*0);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //if its the top left corner pixel
            else if (h == 0 && w == 0)
            {
                //Gx calculation
                gXRed = ((0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed + (0)*imgCopy[h+1][w-1].rgbtRed + 0*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gXBlue = ((0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue + (0)*imgCopy[h+1][w-1].rgbtBlue + 0*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gXGreen = ((0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen + (0)*imgCopy[h+1][w-1].rgbtGreen + 0*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (0)*imgCopy[h+1][w-1].rgbtRed + 2*imgCopy[h+1][w].rgbtRed + 1*imgCopy[h+1][w+1].rgbtRed);
                gYBlue = ((0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (0)*imgCopy[h+1][w-1].rgbtBlue + 2*imgCopy[h+1][w].rgbtBlue + 1*imgCopy[h+1][w+1].rgbtBlue);
                gYGreen = ((0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen + (0)*imgCopy[h+1][w-1].rgbtGreen + 2*imgCopy[h+1][w].rgbtGreen + 1*imgCopy[h+1][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //if its the top right pixel
            else if (h == 0 && w == (width - 1))
            {
                //Gx calculation
                gXRed = ((-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (-1)*imgCopy[h+1][w-1].rgbtRed + 0*imgCopy[h+1][w].rgbtRed + 0*imgCopy[h+1][w+1].rgbtRed);
                gXBlue = ((-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (-1)*imgCopy[h+1][w-1].rgbtBlue + 0*imgCopy[h+1][w].rgbtBlue + 0*imgCopy[h+1][w+1].rgbtBlue);
                gXGreen = ((-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen + (-1)*imgCopy[h+1][w-1].rgbtGreen + 0*imgCopy[h+1][w].rgbtGreen + 0*imgCopy[h+1][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed + (1)*imgCopy[h+1][w-1].rgbtRed + 2*imgCopy[h+1][w].rgbtRed + 0*imgCopy[h+1][w+1].rgbtRed);
                gYBlue = ((0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue + (1)*imgCopy[h+1][w-1].rgbtBlue + 2*imgCopy[h+1][w].rgbtBlue + 0*imgCopy[h+1][w+1].rgbtBlue);
                gYGreen = ((0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen + (1)*imgCopy[h+1][w-1].rgbtGreen + 2*imgCopy[h+1][w].rgbtGreen + 0*imgCopy[h+1][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //bottom left
            else if (h == (height - 1) && w == 0)
            {
                //Gx calculation
                gXRed = ((-1)*0 + 0*imgCopy[h-1][w].rgbtRed + 1*imgCopy[h-1][w+1].rgbtRed + (-2)*0 + 0*imgCopy[h][w].rgbtRed + 2*imgCopy[h][w+1].rgbtRed);
                gXBlue = ((-1)*0 + 0*imgCopy[h-1][w].rgbtBlue + 1*imgCopy[h-1][w+1].rgbtBlue + (-2)*0 + 0*imgCopy[h][w].rgbtBlue + 2*imgCopy[h][w+1].rgbtBlue);
                gXGreen = ((-1)*0 + 0*imgCopy[h-1][w].rgbtGreen + 1*imgCopy[h-1][w+1].rgbtGreen + (-2)*0 + 0*imgCopy[h][w].rgbtGreen + 2*imgCopy[h][w+1].rgbtGreen);
                
                //Gy calculation
                gYRed = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*imgCopy[h-1][w+1].rgbtRed + (0)*0 + 0*imgCopy[h][w].rgbtRed + 0*imgCopy[h][w+1].rgbtRed);
                gYBlue = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*imgCopy[h-1][w+1].rgbtBlue + (0)*0 + 0*imgCopy[h][w].rgbtBlue + 0*imgCopy[h][w+1].rgbtBlue);
                gYGreen = ((-1)*0 + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*imgCopy[h-1][w+1].rgbtGreen + (0)*0 + 0*imgCopy[h][w].rgbtGreen + 0*imgCopy[h][w+1].rgbtGreen);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
            
            //bottom right
            else if (h == (height - 1) && w == (width - 1))
            {
                //Gx calculation
                gXRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + 0*imgCopy[h-1][w].rgbtRed + 1*0 + (-2)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 2*0);
                gXBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + 0*imgCopy[h-1][w].rgbtBlue + 1*0 + (-2)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 2*0);
                gXGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + 0*imgCopy[h-1][w].rgbtGreen + 1*0 + (-2)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 2*0);
                
                //Gy calculation
                gYRed = ((-1)*imgCopy[h-1][w-1].rgbtRed + (-2)*imgCopy[h-1][w].rgbtRed + (-1)*0 + (0)*imgCopy[h][w-1].rgbtRed + 0*imgCopy[h][w].rgbtRed + 0*0);
                gYBlue = ((-1)*imgCopy[h-1][w-1].rgbtBlue + (-2)*imgCopy[h-1][w].rgbtBlue + (-1)*0 + (0)*imgCopy[h][w-1].rgbtBlue + 0*imgCopy[h][w].rgbtBlue + 0*0);
                gYGreen = ((-1)*imgCopy[h-1][w-1].rgbtGreen + (-2)*imgCopy[h-1][w].rgbtGreen + (-1)*0 + (0)*imgCopy[h][w-1].rgbtGreen + 0*imgCopy[h][w].rgbtGreen + 0*0);
                
                int GRed = round(sqrt((gYRed*gYRed) + (gXRed*gXRed)));
                if (GRed > 255)
                {
                    GRed = 255;
                }
                int GBlue = round(sqrt((gYBlue*gYBlue) + (gXBlue*gXBlue)));
                if (GBlue > 255)
                {
                    GBlue = 255;
                }
                int GGreen = round(sqrt((gYGreen*gYGreen) + (gXGreen*gXGreen)));
                if (GGreen > 255)
                {
                    GGreen = 255;
                }

                image[h][w].rgbtRed = GRed;
			    image[h][w].rgbtBlue = GBlue;
			    image[h][w].rgbtGreen = GGreen;
            }
        }
    }
    
    return;
}
