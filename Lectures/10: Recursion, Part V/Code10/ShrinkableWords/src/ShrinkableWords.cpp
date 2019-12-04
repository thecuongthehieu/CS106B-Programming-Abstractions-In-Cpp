/* File: ShrinkableWords.cpp
 *
 * A program to list off all long shrinkable words in English.
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
using namespace std;

/**
 * Given a word, returns whether that word can be reduced down to a single-letter
 * word by removing one character at a time.
 *
 * This will add the words in the reverse order of what you might expect - the word will
 * seem to grow rather than shrink. Good exercise - how might you change this so that that
 * isn't the case?
 *
 * @param word The word in question.
 * @param english All legal English words.
 * @param shrinkingSequence An outparameter holding the shrinking sequence, if one exists.
 * @return Whether the string is a shrinkable word.
 */
bool isShrinkable(const string& word, const Lexicon& english, Vector<string>& shrinkingSequence);

/* Constant controlling how long the words have to be before we include them. */
const int kMinimumWordLength = 10;

int main() {
    Lexicon english("EnglishWords.dat");

    for (string word: english) {
        Vector<string> shrinkingSequence;
        if (word.length() >= kMinimumWordLength &&
            isShrinkable(word, english, shrinkingSequence)) {

            for (string word: shrinkingSequence) {
                cout << word << endl;
            }
        }
    }

    return 0;
}

bool isShrinkable(const string& word, const Lexicon& english, Vector<string>& shrinkingSequence) {
    /* Base case 1: Non-words can't be shrinkable words. */
    if (!english.contains(word)) return false;

    /* Base case 2: Any word of length 1 is shrinkable. */
    if (word.length() == 1) {
        shrinkingSequence.add(word);
        return true;
    }

    /* Recursive step: look at all words you can form by removing a single letter.
     * If any of them are shrinkable, the whole word is shrinkable!
     */
    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) + word.substr(i+1);
        if (isShrinkable(shrunken, english, shrinkingSequence)) {
            shrinkingSequence.add(word);
            return true;
        }
    }

    /* If none of those options worked, this string cannot be shrunk. */
    return false;
}








