/*
 * CS 106B Trailblazer
 * This file implements code related to colors for the assignment.
 * See Color.h for documentation of each public function.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, Keith Schwarz
 * @version 2017/03/09 (updated for Win17)
 */

#include "Color.h"
#include "error.h"
#include <iomanip>
#include <sstream>

void colorToRGB(Color color, int& r, int& g, int& b) {
    switch (color) {
        case Color::GRAY:   r = 255; g = 255; b = 255; break;
        case Color::YELLOW: r = 255; g = 255; b = 0;   break;
        case Color::GREEN:  r = 0;   g = 255; b = 0;   break;
        default: error("Unknown color?");
    }
}

std::string rgbToColor(int r, int g, int b) {
    std::ostringstream hexValue;
    hexValue << '#' << std::hex << std::setfill('0');
    hexValue << std::setw(2) << r << std::setw(2) << g << std::setw(2) << b;
    return hexValue.str();
}
