/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
	//balls
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation



    

    int scaledWidth = referenceimg.width() / 2;
    int scaledHeight = referenceimg.height() / 2;

    int scaledX = p.x % scaledWidth;
    int scaledY = p.y % scaledHeight;

    int tiledX = scaledX * 2;
    int tiledY = scaledY * 2;

    // Get the pixel at the corresponding coordinates in the tiled image
    RGBAPixel* pixel = referenceimg.getPixel(tiledX, tiledY);

    // Calculate the new brightness for each color channel
    int newR = pixel->r + brightamount;
    int newG = pixel->g + brightamount;
    int newB = pixel->b + brightamount;

    // Clamp the brightness values to the range [0, 255]
    // pixel->r = (newR > 255) ? 255 : (newR < 0) ? 0 : newR;
    // pixel->g = (newG > 255) ? 255 : (newG < 0) ? 0 : newG;
    // pixel->b = (newB > 255) ? 255 : (newB < 0) ? 0 : newB;

    return *pixel;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
