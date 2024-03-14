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
    int scaledWidth = referenceimg.width() / 2;
    int scaledHeight = referenceimg.height() / 2;

    int scaledX = p.x % scaledWidth;
    int scaledY = p.y % scaledHeight;

    int tiledX = scaledX * 2;
    int tiledY = scaledY * 2;

    // Get the four neighboring pixels for bilinear interpolation
    RGBAPixel* pixel00 = referenceimg.getPixel(tiledX, tiledY);
    RGBAPixel* pixel01 = referenceimg.getPixel(tiledX + 1, tiledY);
    RGBAPixel* pixel10 = referenceimg.getPixel(tiledX, tiledY + 1);
    RGBAPixel* pixel11 = referenceimg.getPixel(tiledX + 1, tiledY + 1);

    // Perform bilinear interpolation for each color channel
    float deltaX = (scaledX) / scaledWidth;
    float deltaY = (scaledY) / scaledHeight;

    int newR = ((1 - deltaX) * (1 - deltaY) * pixel00->r +
                                 deltaX * (1 - deltaY) * pixel01->r +
                                 (1 - deltaX) * deltaY * pixel10->r +
                                 deltaX * deltaY * pixel11->r) + brightamount;
    
    int newG = ((1 - deltaX) * (1 - deltaY) * pixel00->g +
                                 deltaX * (1 - deltaY) * pixel01->g +
                                 (1 - deltaX) * deltaY * pixel10->g +
                                 deltaX * deltaY * pixel11->g) + brightamount;

    int newB = ((1 - deltaX) * (1 - deltaY) * pixel00->b +
                                 deltaX * (1 - deltaY) * pixel01->b +
                                 (1 - deltaX) * deltaY * pixel10->b +
                                 deltaX * deltaY * pixel11->b) + brightamount;

    // Clamp the brightness values to the range [0, 255]
    newR = std::min(std::max(newR, 0), 255);
    newG = std::min(std::max(newG, 0), 255);
    newB = std::min(std::max(newB, 0), 255);

    // Create a new pixel with the adjusted brightness
    RGBAPixel newPixel(newR, newG, newB);

    return newPixel;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

 