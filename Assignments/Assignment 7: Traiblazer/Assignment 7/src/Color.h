/*
 * CS 106B Trailblazer
 * This file implements code related to colors for the assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Keith Schwarz, Marty Stepp
 * @version 2017/03/09 (initial version for 14au)
 */

#ifndef _color_h
#define _color_h

#include <string>

/*
 * An enumerated type representing a color for a node during an execution of
 * Dijkstra's algorithm or A* search.
 */
enum class Color {
    GRAY, YELLOW, GREEN
};

/*
 * Converts an integer color like 0xffdd88 into three separate red/green/blue
 * components from 0-255.
 */
void colorToRGB(Color color, int& r, int& g, int& b);

/*
 * Converts three RGB values from 0-255 into a hex color string like "#cccccc".
 */
std::string rgbToColor(int r, int g, int b);

#endif // _color_h
