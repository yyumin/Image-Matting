/**
 * @file negativeBorderColorPicker.cpp
 * @description Implements the NegativeBorderColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "negativeBorderColorPicker.h"
#include <math.h>

NegativeBorderColorPicker::NegativeBorderColorPicker(PNG &inputimg, PixelPoint src_px, unsigned int width, double tol)
{
    // Complete your implementation below
    referenceimg = inputimg;
    source_px = src_px;
    borderwidth = width;
    tolerance = tol;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Leaves a pixel unchanged if it is not on the border of a fill region
 *
 * If a pixel is on the border of a fill region, change it to the "negative"
 * of the original colour value in the Hue and Luminance channels.
 * Saturation and Alpha should remain unchanged.
 * Based on your understanding of HSL colour space from Lab_intro,
 * think about what would be an appropriate "negative" transformation for the
 * Hue and Luminance channels.
 *
 * Hint: a pixel is on the border of a fill region, if it is within "width"
 * pixels of a pixel which is NOT in the fill region!
 *
 * Also: the border of the image is considered to be a border of the fill region.
 */
HSLAPixel NegativeBorderColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    // return HSLAPixel();

    HSLAPixel point = *referenceimg.getPixel(p.x, p.y);

    if (onBorder(p))
    {
        double colorH;

        if (point.h <= 180)
        {
            colorH = point.h + 180.0;
        }
        else
        {
            colorH = point.h - 180.0;
        }

        double colorL = 1 - point.l;

        return HSLAPixel(colorH, point.s, colorL, p.color.a);
    }
    else
    {
        return *referenceimg.getPixel(p.x, p.y);
    }
}

bool NegativeBorderColorPicker::onBorder(PixelPoint p)
{

    int width = int(borderwidth);
    int px = int(p.x);
    int py = int(p.y);

    for (int x = px - width; x <= px + width; x++)
    {
        for (int y = py - width; y <= py + width; y++)
        {
            // if (x < 0 || x >= referenceimg.width() || y < 0 || y >= referenceimg.height())
            // {
            //     return true;
            // }

            // within the circle of radius = width
            if (((x - px) * (x - px) + (y - py) * (y - py)) <= width * width)
            {
                if (x < 0 || x >= referenceimg.width() || y < 0 || y >= referenceimg.height()) {
                return true;
                }

                if (source_px.color.distanceTo((*referenceimg.getPixel(x, y))) >= tolerance)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
