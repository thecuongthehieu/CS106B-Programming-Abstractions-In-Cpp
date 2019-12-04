/*
 * File: WelcomeToCpp.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the first assignment of CS106B.
 * [TODO: rewrite the documentation]
 *
 * The repeating call sequence is
 *    triggerStackOverflow(137), which calls
 *    [TODO: fill this in], which calls
 *    triggerStackOverflow(137) again.
 */

// Please feel free to add any other #includes you need!
#include "WelcomeToCpp.h"
#include <iostream>
#include <string>
#include <random.h>
#include <tokenscanner.h>

using namespace std;


void flipHeads() {
    // [TODO: fill in the code]
    int count = 0;
    int sum = 0;
    while (count < 3) {
        sum += 1;
        bool value = randomBool();
        if (value == true) {
            count += 1;
            cout << "heads" << endl;
        } else {
            count = 0;
            cout << "tails" << endl;
        }
        if (count == 3) {
            cout << "It tooks " << sum << " to get 3 consecutive heads";
        }
    }
}


int nChooseK(int n, int k) {
    // [TODO: fill in the code]
    if (n <= 1) return 1;
    else if (k == 0 || k == n) return 1;
    else return nChooseK(n - 1, k - 1) + nChooseK(n - 1, k);
}


int stringToInt(string str) {
    // [TODO: fill in the code]
    if (str.at(0) == '-') {
        int abs = stringToInt(str.substr(1));
        return -abs;
    } else if (str.length() == 1) {
        return str.at(0) - '0'; //str.at is of type CHAR
    } else {
        return 10 * (stringToInt(str.substr(0, str.length() - 1))) + stringToInt(str.substr(str.length() - 1));
    }
}


string intToString(int n) {
    // [TODO: fill in the code]
    if (n < 0)
        return string("-") + intToString(-n);
    else if (n < 10)
        return string("") + char(n + '0');
    else {
        return intToString(n / 10) + char(n % 10 + '0');
    }
}


DocumentInfo statisticsFor(istream& source) {
    DocumentInfo docInfo = { 0, 0, 0 };
    // [TODO: fill in the code]
    TokenScanner scanner(source);
    vector<string> vowels;
    vowels.push_back("u");
    vowels.push_back("U");
    vowels.push_back("e");
    vowels.push_back("E");
    vowels.push_back("o");
    vowels.push_back("O");
    vowels.push_back("a");
    vowels.push_back("A");
    vowels.push_back("i");
    vowels.push_back("I");
    vowels.push_back("y");
    vowels.push_back("Y");

        scanner.addWordCharacters("'");
        while (scanner.hasMoreTokens()) {
            string token = scanner.nextToken();
            if (token == "!" || token == "?" || token == ".") {
                docInfo.numSentences += 1;
            }
            TokenType type = scanner.getTokenType(token);
            if (type == WORD) {
                docInfo.numWords += 1;
                int* check = new int[token.length()]();
                int syllable = 0;
                for (int i = 0; i < token.length(); ++i) {
                    string c = string("") + token[i];
                    //cout << c << endl;
                    for (int j = 0; j < vowels.size(); ++j) {
                        if (c == vowels[j]) {
                            if (i == 0) {
                                syllable += 1;
                            } else if (i > 0) {
                                if (check[i - 1] == 0) {
                                    if (i == token.length() - 1)
                                        if (c == vowels[2] || c == vowels[3])
                                            continue;
                                    syllable += 1;
                                }
                            }
                            check[i] = 1;
                        }
                    }
                }
                //cout << token << "  " << syllable << endl;
                if (syllable == 0)
                    docInfo.numSyllables += 1;
                else
                    docInfo.numSyllables += syllable;
            }
        }
        if (docInfo.numSentences == 0)
            docInfo.numSentences = 1;
        if (docInfo.numWords == 0)
            docInfo.numWords = 1;
    return docInfo;
}

