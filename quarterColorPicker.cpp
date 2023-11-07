/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG &inputimg)
{
    // Complete your implementation below
    referenceimg = inputimg;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image.
 *
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the H/S/L/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 *
 * Since interpolation will be the exact average between exactly two pixels, then
 * the Hue channel should be averaged over the shortest arc between the two values.
 * e.g. The average of H_1 = 10 and H_2 = 320 is H_avg = 345 and NOT 165.
 * In the case of two diametric hues being averaged, e.g. 10 and 190, the average will
 * have the smaller value, i.e. 100 and NOT 280.
 *
 * @pre referenceimg width and height are both even
 */
HSLAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    // return HSLAPixel();

    int x_scaled = referenceimg.width() / 2;
    int y_scaled = referenceimg.height() / 2;
    int x = p.x % x_scaled;
    int y = p.y % y_scaled;
    HSLAPixel p1 = *referenceimg.getPixel(x * 2, y * 2);
    HSLAPixel p2 = *referenceimg.getPixel(x * 2 + 1, y * 2);
    HSLAPixel p3 = *referenceimg.getPixel(x * 2, y * 2 + 1);
    HSLAPixel p4 = *referenceimg.getPixel(x * 2 + 1, y * 2 + 1);
    HSLAPixel avg1 = average(p1, p2);
    HSLAPixel avg2 = average(p3, p4);
    return average(avg1, avg2);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

HSLAPixel QuarterColorPicker::average(HSLAPixel p1, HSLAPixel p2)
{
    double avgH; /**< Hue of the pixel, in degrees [0, 360). */
    if (abs(p1.h - p2.h) <= 180)
    {
        avgH = (p1.h + p2.h) / 2.0;
    }
    else if (p1.h + p2.h > 360)
    {
        avgH = (p1.h + p2.h) / 2.0 + 180.0 - 360.0;
    }
    else
    {
        avgH = (p1.h + p2.h) / 2.0 + 180.0;
    }
    double avgS = (p1.s + p2.s) / 2.0; /**< Saturation of the pixel, [0, 1]. */
    double avgL = (p1.l + p2.l) / 2.0; /**< Luminance of the pixel, [0, 1]. */
    double avgA = (p1.a + p2.a) / 2.0; /**< Alpha of the pixel, [0, 1]. */

    return HSLAPixel(avgH, avgS, avgL, avgA);
}
