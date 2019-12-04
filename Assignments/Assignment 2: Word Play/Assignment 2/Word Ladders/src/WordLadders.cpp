/*
 * File: WordLadders.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "RecordLadders.h"

#include <queue>
#include <algorithm>

using namespace std;

Lexicon english("EnglishWords.dat");

int main() {
    // [TODO: Fill this in!]
    // Don't forget to call the recordLadderBetween and
    // recordNoLadderBetween functions in your solution!
    // We'll be using them to run automated tests on your
    // code.

    cout << "Welcome to CS106B Word Ladders!" << endl << endl;
    cout << "Give me two English words, and I will change the first" << endl << "into the second by replacing one letter at a time." << endl << endl;
    string word1, word2;

    while (true) {
        cout << "Word 1: ";
        cin >> word1;
        cout << "Word 2: ";
        cin >> word2;

        // TO LOWER CASE
        word1 = toLowerCase(word1);
        word2 = toLowerCase(word2);
        bool found = false;

        queue<vector<string> > myqueue;
        vector<string> initLadder;
        Lexicon usedWords;
        usedWords.add(word1);

        initLadder.push_back(word1);
        myqueue.push(initLadder);


        while (!myqueue.empty()) {
            if (word1.length() != word2.length())
                break;
            vector<string> currentLadder = myqueue.front();
            myqueue.pop();
            if (*(currentLadder.end() - 1) == word2) {
                cout << "Found the shortest ladder! Here it is:" << endl;
                for (int i = 0; i < currentLadder.size() - 1; ++i)
                    cout << currentLadder[i] << " -> ";
                cout << *(currentLadder.end() - 1) << endl;
                //recordLadderBetween(word1, word2, shortestPath);
                found = true;
                break;
            }
            string lastWord = *(currentLadder.end() - 1);
            for (int i = 0; i < lastWord.length(); ++i) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    string nextWord = lastWord;
                    nextWord[i] = c;
                    if (english.contains(nextWord) && !usedWords.contains(nextWord)) {
                        vector<string> tmpLadder = currentLadder;
                        tmpLadder.push_back(nextWord);
                        myqueue.push(tmpLadder);
                        usedWords.add(nextWord);
                    }

                }
            }
        }

        if (!found)
            cout << "Sorry, there aren't any ladders between those words." << endl;

        string continueAns;
        cout << "Want to find another word ladder? ";
        cin >> continueAns;
        if (continueAns == "no")
            break;
    }

    cout << "Have a great day!";

//    Lexicon::iterator it = english.begin();
//    cout << *it;

    return 0;
}
