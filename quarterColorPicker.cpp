/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"
#include "quarterColorPicker_private.h"
using namespace cs221util;

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
	
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
    PNG scaledImage(referenceimg.width() / 2, referenceimg.height() / 2);

    for (unsigned int y = 0; y < referenceimg.height(); y += 2) {
        for (unsigned int x = 0; x < referenceimg.width(); x += 2) {
            RGBAPixel interpolatedPixel = bilinearInterpolation(referenceimg, x, y);

            *scaledImage.getPixel(x / 2, y / 2) = interpolatedPixel;
        }
    }

    RGBAPixel pixel = *scaledImage.getPixel(p.x % scaledImage.width(), p.y % scaledImage.height());

    pixel.r = std::min(255, pixel.r + brightamount);
    pixel.g = std::min(255, pixel.g + brightamount);
    pixel.b = std::min(255, pixel.b + brightamount);

    return pixel;
   
}



/**
 * Add your private QuarterColorPicker function implementations below
 */

RGBAPixel QuarterColorPicker::bilinearInterpolation(const PNG& img, unsigned int x, unsigned int y) {

    RGBAPixel p1 = *img.getPixel(x, y);
    RGBAPixel p2 = *img.getPixel(x + 1, y);
    RGBAPixel p3 = *img.getPixel(x, y + 1);
    RGBAPixel p4 = *img.getPixel(x + 1, y + 1);

    RGBAPixel interpolatedColor;
    interpolatedColor.r = ((p1.r+p2.r)/2 + (p3.r+p4.r)/2)/2;

    interpolatedColor.g = ((p1.g+p2.g)/2 + (p3.g+p4.g)/2)/2;

    interpolatedColor.b = ((p1.b+p2.b)/2 + (p3.b+p4.b)/2)/2;

    
    interpolatedColor.r = static_cast<unsigned int>(interpolatedColor.r);
    interpolatedColor.g = static_cast<unsigned int>(interpolatedColor.g);
    interpolatedColor.b = static_cast<unsigned int>(interpolatedColor.b);

    return interpolatedColor;
}
