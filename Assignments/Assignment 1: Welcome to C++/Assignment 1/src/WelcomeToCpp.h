/*
 * Header: WelcomeToCpp.h
 *
 * Contains function prototypes and definitions for types that you'll need in
 * the course of working through this assignment.
 *
 * You should not change the function prototypes here, since the driver code
 * assumes that the interface exactly matches what's shown here.
 */

#ifndef WelcomeToCpp_Included
#define WelcomeToCpp_Included

#include <string>
#include <istream>
using namespace std;

/**
 * Type: DocumentInfo
 *
 * Information about the number of words, sentences, and syllables
 * in a document.
 */
struct DocumentInfo {
    int numSentences;
    int numWords;
    int numSyllables;
};

/**
 * Simulates flipping a coin until three heads are flipped, printing out
 * the coin flips at each step, and ultimately reports how many total coins
 * were flipped.
 */
void flipHeads();

/**
 * Recursively computes and returns n choose k.
 *
 * @param n The number of people in the overall group.
 * @param k The number of people to select.
 * @return The number of ways to pick k people out of n.
 */
int nChooseK(int n, int k);

/**
 * Recursively converts the number n into a string representation of itself.
 *
 * @param n The number to convert.
 * @return A string representation of the number n.
 */
string intToString(int n);

/**
 * Recursively converts the string str, which is presumed to represent an integer,
 * into its numeric value.
 *
 * @param str The string to convert.
 * @return The numeric value of that string.
 */
int stringToInt(string str);

/**
 * Reads the specified file, computes statistics about it, and returns
 * those statistics.
 *
 * @param source A stream containing the file contents.
 * @return A DocumentInfo struct containing information about that file.
 */
DocumentInfo statisticsFor(istream& source);

#endif
