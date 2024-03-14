/**
 * @file borderColorPicker_private.h
 * @description student declarations of private functions
 *              for BorderColorPicker, CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below

 bool isWithinTolerance(const RGBAPixel &p1, const RGBAPixel &p2, double tolerance);
 bool isNearBorder(const PixelPoint &p, const PNG &img, double borderwidth, double tolerance, const RGBAPixel &seedcolor);
