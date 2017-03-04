// Homework 1
// Color to Greyscale Conversion

//A common way to represent color images is known as RGBA - the color
//is specified by how much Red, Green, and Blue is in it.
//The 'A' stands for Alpha and is used for transparency; it will be
//ignored in this homework.

//Each channel Red, Blue, Green, and Alpha is represented by one byte.
//Since we are using one byte for each color there are 256 different
//possible values for each color.  This means we use 4 bytes per pixel.

//Greyscale images are represented by a single intensity value per pixel
//which is one byte in size.

//To convert an image from color to grayscale one simple method is to
//set the intensity to the average of the RGB channels.  But we will
//use a more sophisticated method that takes into account how the eye 
//perceives color and weights the channels unequally.

//The eye responds most strongly to green followed by red and then blue.
//The NTSC (National Television System Committee) recommends the following
//formula for color to greyscale conversion:

//I = .299f * R + .587f * G + .114f * B

//Notice the trailing f's on the numbers which indicate that they are 
//single precision floating point constants and not double precision
//constants.

//You should fill in the kernel as well as set the block and grid sizes
//so that the entire image is processed.

#include "reference_calc.cpp"
#include "utils.h"
#include <stdio.h>

__global__
void rgba_to_greyscale(const uchar4* const rgbaImage,
                       unsigned char* const greyImage,
                       int numRows, int numCols)
{
  
  int tidX = threadIdx.x + blockIdx.x*blockDim.x; //get the actual thread index along x axis
  int tidY = threadIdx.y + blockIdx.y*blockDim.y; //get the actual thread index along y axis
  
  int numRows_perT = numRows/(gridDim.y*blockDim.y); //get the number of rows per thread
  int numCols_perT = numCols/(gridDim.x*blockDim.x); //get the number of coloumns per thread
  
   for(int r = tidX;r<numRows; r += numRows_perT){
        for(int c = tidY ; c < numCols; c+=numCols_perT){
            uchar4 rgb_val = rgbaImage[r*numCols+c]; //get the correct element from input array
            char grey_val = 0.299f*rgb_val.x + 0.587f*rgb_val.y + 0.114f*rgb_val.z; //calculate gray scale value
            greyImage[r*numCols+c] = grey_val; //store the calculated value
        }
    }
}

__global__
void rgba_to_greyscale_lightness(const uchar4* const rgbaImage,
                       unsigned char* const greyImage,
                       int numRows, int numCols)
{
    int tidX = threadIdx.x + blockIdx.x*blockDim.x;
    int tidY = threadIdx.y + blockIdx.y*blockDim.y;
   
    int numRowsPart = numRows/(gridDim.y*blockDim.y);
    int numColsPart = numCols/(gridDim.x*blockDim.x);
    for(int r = tidX;r<numRows; r += numRowsPart){
        for(int c = tidY ; c < numCols; c+=numColsPart){
            uchar4 rgb_val = rgbaImage[r*numCols+c];
            int max = 0,min =0;
            // taking the Maximum and the minimum out of all the RGB values. 
            if(rgb_val.x>rgb_val.y)
                max = rgb_val.x, min = rgb_val.y;
            else
                max = rgb_val.y,min = rgb_val.x;
            if(max<rgb_val.z)
                max = rgb_val.z;
            if(min>rgb_val.z)
                min = rgb_val.z;
                
           // set the grey_val as per the requirement.
            char grey_val = (max + min)/2 ;
            greyImage[r*numCols+c] = grey_val;
        }
    }
 
}

void your_rgba_to_greyscale(const uchar4 * const h_rgbaImage, uchar4 * const d_rgbaImage,
                            unsigned char* const d_greyImage, size_t numRows, size_t numCols)
{
  const dim3 blockSize(16, 16, 1);  //Each block has 16*16 threads
  const dim3 gridSize( 2,2, 1);  //Divides the whole image into 4 blocks
  rgba_to_greyscale<<<gridSize, blockSize>>>(d_rgbaImage, d_greyImage, numRows, numCols);
  rgba_to_greyscale_lightness<<<gridSize, blockSize>>>(d_rgbaImage, d_greyImage, numRows, numCols);
  
  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}

