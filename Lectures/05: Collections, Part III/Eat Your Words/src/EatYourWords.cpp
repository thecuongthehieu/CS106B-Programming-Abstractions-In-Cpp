/* File: EatYourWords.cpp
 *
 * A program that clusters words into anagram clusters
 * to let the user find all anagrams of a word, plus
 * a bunch of other nifty little functions!
 */
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "map.h"
using namespace std;

/**
 * Given a word, returns a string formed by sorting the letters
 * in that word.
 *
 * @param word The input word
 * @return A sorted version of the word
 */
string sortedVersionOf(const string& input) {
    /* This algorithm is an implementation of an algorithm called
     * "Counting Sort." It's described in the slides for Lecture 05.
     * For more information, take CS161!
     */

    /* Build a frequency table of the letters in the word. */
    Map<char, int> letterFreq;
    for (char ch: input) {
        letterFreq[ch]++;
	}
	
    /* Iterate over the frequency table and build the result
     * string from the information it contains.
     */
	string result;
    for (char ch: letterFreq) {
        for (int i = 0; i < letterFreq[ch]; i++) {
			result += ch;
		}
	}
	
	return result;
}

/**
 * Given a word, returns whether that word is a tautonym, a word
 * that consists of the same string repeated twice.
 *
 * @param word The word to check.
 * @return Whether it's a tautonym.
 */
bool isTautonym(const string& word) {
    /* If the word length isn't even, it can't be a tautonym. */
    if (word.length() % 2 != 0) {
        return false;
    }

    /* Check if the first and second halves of the word are equal. */
    return word.substr(0, word.length() / 2) ==
           word.substr(word.length() / 2);
}

int main() {
    Lexicon english("EnglishWords.dat");

    /* Distribute words into their anagram clusters. This uses
     * the handy map autoinsertion feature.
     */
    Map<string, Lexicon> anagramClusters;
    for(string word: english) {
        anagramClusters[sortedVersionOf(word)].add(word);
    }

    while (true) {
        string word = getLine("Enter a word: ");
        /* The key we'll use will be the sorted version of the word.
         * Question to ponder: why convert to lower case, then
         * sort, rather than the other way around?
         */
        string key = sortedVersionOf(toLowerCase(word));

        if (anagramClusters.containsKey(key)) {
            cout << anagramClusters[key] << endl;
        } else {
            cout << "Alas, such words are not to be found here." << endl;
        }
    }
    return 0;
}







		
	
