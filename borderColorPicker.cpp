/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"
#include "borderColorPicker_private.h"

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    // Complete your implementation below

    borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    int x = p.x;
    int y = p.y;
    int imgWidth = img.width();
    int imgHeight = img.height();

    if (borderwidth >  x || borderwidth > y || x >= imgWidth - borderwidth || y >= imgHeight - borderwidth) {
        RGBAPixel pixel1 = *img.getPixel(x, y);
        double dist = pixel1.distanceTo(seedcolor);
        if (dist <= tolerance) {
            return bordercolor;
        } else {
            return *img.getPixel(x,y);
        }
    }

    int euclidDist = borderwidth*borderwidth;

    for (int currY = y - borderwidth; currY <= y + borderwidth; currY++) {
        for (int currX = x - borderwidth; currX <= x + borderwidth; currX++) {
            if ((currX-x)*(currX-x) + (currY-y)*(currY-y) <= euclidDist) {
                RGBAPixel *currPixel = img.getPixel(currX, currY);
                if (currPixel->distanceTo(seedcolor) > tolerance) {
                    if (img.getPixel(p.x, p.y)->distanceTo(seedcolor) > tolerance) {
                        return *img.getPixel(x, y);
                    }
                    return bordercolor;
                }
            }
        }
    }

    return *img.getPixel(x, y);
}





// RGBAPixel originPixel = *img.getPixel(p.x, p.y);
//     // Replace the line below with your implementation
//     if (isNearBorder(p, img, borderwidth, tolerance, seedcolor) && isWithinTolerance(originPixel, seedcolor, tolerance)) {
//         if (img.getPixel(p.x, p.y)->distanceTo(seedcolor) > tolerance) {
//             return *img.getPixel(p.x, p.y);
//         }
//         return bordercolor;
//     }
//     else {
//         return *img.getPixel(p.x, p.y);
//     }
// }

// /**
//  * Add your private BorderColorPicker function implementations below
//  */

// bool BorderColorPicker::isWithinTolerance(const RGBAPixel &p1, const RGBAPixel &p2, double tolerance){
//     int redDiff = abs(p1.r - p2.r);
//     int greenDiff = abs(p1.g - p2.g);
//     int blueDiff = abs(p1.b - p2.b);



//     if (redDiff <= tolerance && greenDiff <= tolerance && blueDiff < tolerance) {
//         return true;
//     }

//     return false;
// }

// bool BorderColorPicker::isNearBorder(const PixelPoint &p, const PNG &img, double borderwidth, double tolerance, const RGBAPixel &seedcolor){
//     int x = p.x;
//     int y = p.y;
//     int imgWidth = img.width();
//     int imgHeight = img.height();

//     // Calculate the distances from the nearest edges
//     int distanceFromLeftEdge = x;
//     int distanceFromRightEdge = imgWidth - x - 1; // -1 to account for 0-based indexing
//     int distanceFromTopEdge = y;
//     int distanceFromBottomEdge = imgHeight - y - 1; // -1 to account for 0-based indexing

//     // Calculate the minimum distance from any edge
//     int minDistance = min(min(distanceFromLeftEdge, distanceFromRightEdge), min(distanceFromTopEdge, distanceFromBottomEdge));

//     // Check if the pixel is within the border width using Euclidean distance
//     if (minDistance <= borderwidth) {
//         return true;
//     }

//     return false;