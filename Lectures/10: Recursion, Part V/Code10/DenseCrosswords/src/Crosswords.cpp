/* File: Crosswords.cpp
 *
 * A program to generate dense crosswords.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "console.h"
using namespace std;

/**
 * Given a grid and a column, extracts the word at that column up to a certain
 * number of characters.
 *
 * @param grid The grid in question.
 * @param col Which column to extract
 * @param numRows How many rows to read
 * @return The contents of that column.
 */
string contentsOfColumn(const Grid<char>& grid, int col, int numRows) {
    string result;
    for (int row = 0; row < numRows; row++) {
        result += grid[row][col];
    }
    return result;
}

/**
 * Given a grid, reports whether each column is a valid English word.
 *
 * @param grid The grid in question.
 * @param colWords A collection of all words that can fit in a column.
 * @return Whether each column is a word.
 */
bool areColumnsLegal(const Grid<char>& grid, const Lexicon& colWords) {
    for (int col = 0; col < grid.numCols(); col++) {
        string word = contentsOfColumn(grid, col, grid.numRows());
        if (!colWords.contains(word)) return false;
    }
    return true;
}

/**
 * Given a grid, reports whether every column is a prefix of some legal
 * English word.
 *
 * @param grid The grid in question.
 * @param colWords A collection of all words that can fit in a column.
 * @param maxRow The maximum row to descend down to.
 * @return Whether all columns are feasible prefixes of real words.
 */
bool areColumnsFeasible(const Grid<char>& grid, int maxRow, const Lexicon& colWords) {
    for (int col = 0; col < grid.numCols(); col++) {
        string prefix = contentsOfColumn(grid, col, maxRow);
        if (!colWords.containsPrefix(prefix)) return false;
    }
    return true;
}

/**
 * Prints a crossword to the console.
 *
 * @param crossword The crossword in question.
 */
void printCrossword(const Grid<char>& crossword) {
    for (int row = 0; row < crossword.numRows(); row++) {
        for (int col = 0; col < crossword.numCols(); col++) {
            cout << crossword[row][col];
        }
        cout << endl;
    }
}

bool canMakeCrosswordRec(Grid<char>& grid, int row, const Lexicon& rowWords, const Lexicon& colWords) {
    /* Base case: If all rows are filled in, we're done! */
    if (row == grid.numRows()) {
        return areColumnsLegal(grid, colWords);
    }

    /* Base case: If any column is illegal, there is no solution. */
    if (!areColumnsFeasible(grid, row, colWords)) return false;

    /* Otherwise, try all words that might fit. */
    for (string word: rowWords) {
        /* Try out this word */
        for (int i = 0; i < word.length(); i++) {
            grid[row][i] = word[i];
        }

        /* Check whether this works. If so, we're done! */
        if (canMakeCrosswordRec(grid, row + 1, rowWords, colWords)) {
            return true;
        }
    }

    /* Oops, not possible with this setup. */
    return false;
}

/**
 * Reports whether it's possible to fill in the given grid with English words so that
 * each row and column is a valid word. If so, the grid is filled in with one such way
 * of doing so.
 *
 * @param grid The grid to fill in.
 * @param english A Lexicon of all English words.
 * @return Whether the grid could be filled in.
 */
bool canMakeCrossword(Grid<char>& grid, const Lexicon& english) {
    /* Begin by filtering the dictionary down into words that can fit in the rows
     * and columns of the grid. There's no reason to scan over 120,000+ strings
     * looking for a few ones that just coincidentally happen to fit.
     */
    Lexicon rowWords, colWords;
    for (const string& word: english) {
        /* A word fits in a row if its length is equal to the number of columns
         * and vice-versa.
         */
        if (word.length() == grid.numCols()) {
            rowWords += word;
        }
        if (word.length() == grid.numRows()) {
            colWords += word;
        }
    }
    //cout << "this" << endl << colWords << endl;

    return canMakeCrosswordRec(grid, 0, rowWords, colWords);
}

int main() {
    Lexicon english("EnglishWords.dat");
	
    /* The dimensions here are arbitrary but give rise to some pretty cool words! */
    Grid<char> crossword(4, 7);
    cout << "Starting..." << endl;

    if (canMakeCrossword(crossword, english)) {
        printCrossword(crossword);
	} else {
		cout << "No solution found." << endl;
	}

    return 0;
}


