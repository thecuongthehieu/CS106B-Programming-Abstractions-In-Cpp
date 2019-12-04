/*
 * File: EvilHangman.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: write some documentation!]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"

#include <vector>
#include <map>

using namespace std;

Lexicon english("EnglishWords.dat");

struct gameInfor {
    int wordLength;
    int guessesNum;
    string showcountAns;
};
// Original words List is List of words that one has wordLength from user
vector<string> originalwordsList(const int& wordLength) {
    vector<string> listWord;
    for (string word : english) {
        string lowerWord = toLowerCase(word);
        if (word.length() == wordLength)
            listWord.push_back(lowerWord);
    }
    return listWord;
}

void displayWord (string& currentDisplay,const string& addDisplay) {
//upate Display -----
    for (int i = 0; i < addDisplay.length(); ++i) {
            if (addDisplay[i] != '-') {
                currentDisplay[i] = addDisplay[i];
        }
    }
    cout << currentDisplay << endl;
}

pair<string, vector<string> > getwordList (const vector<string>& wordsLeft, const vector<string>& usedCharacters ) {
    string newCharacter = *(usedCharacters.end() - 1);
    map<string, vector<string> > wordFamilies;
    for (int i = 0; i < wordsLeft.size(); ++i) {
        string tmpWord = wordsLeft[i];
        int tmpwordSize = tmpWord.length();
        string tmpwordKey = "";
        for (int j = 0;j < tmpwordSize; ++j) {
            string tmp(1,tmpWord[j]); // convert char to string;
            if (tmp != newCharacter)
                tmpwordKey += "-";
            else
                tmpwordKey += newCharacter;
        }
        wordFamilies[tmpwordKey].push_back(tmpWord);
    }
    //cout << wordFamilies.size();
    //for (map<string, vector<string> >::iterator it = wordFamilies.begin(); it != wordFamilies.end(); ++it)
    //    cout << it->first << "  ";

    map<string, vector<string> >::iterator idexOflargest;
    int largest = 0;
    for (map<string, vector<string> >::iterator it = wordFamilies.begin(); it != wordFamilies.end(); ++it) {
        if (it->second.size() > largest) {
            largest = it->second.size();
            idexOflargest = it;
        }
    }

    return *idexOflargest;
}

int checkGuess(const string& addDisplay) {
    int count = 0;
    for (int i = 0; i < addDisplay.length(); ++i) {
        if (addDisplay[i] != '-')
            count += 1;
    }
    return count; //return the number of new input character;
}

void playGame(const gameInfor& infor) {
    int wordLength = infor.wordLength;
    int guessesNum = infor.guessesNum;
    string showcountAns = infor.showcountAns;
    int turn = 1;
    vector<string> wordsLeft = originalwordsList(wordLength); //left = wordsLeft.size()
    vector<string> usedCharacters;
    Lexicon used_Characters;

    string currentDisplay = "";
    for (int i = 0; i < wordLength; ++i)
        currentDisplay += "-";
    string addDisplay = currentDisplay;

    int rightAnswer = 0;

    while (guessesNum > 0) {
        cout << "Turn " << turn << ": " << endl;
        turn += 1;
        cout << "  Current Word: ";
        displayWord(currentDisplay, addDisplay);
        cout << "  Guesses left: ";
        cout << guessesNum << endl;
        cout << "  Guessed: " << "   ";
        for (int i = 0; i < usedCharacters.size(); ++i)
            cout << usedCharacters[i] << " ";
        cout << endl;
        if (showcountAns == "yes") {
            cout << "  Words left:  ";
            cout << wordsLeft.size();
        }
        string guessedCharacter;
        while (true) {
            cout << endl;
            cout << "Enter a guess: ";
            string tmp;
            cin >> tmp;
            if (!used_Characters.contains(tmp)) {
                guessedCharacter = tmp;
                usedCharacters.push_back(guessedCharacter);
                used_Characters.add(guessedCharacter);
                break;
            } else {
                cout << "Please enter a letter you haven't already guessed";
            }
        }
        wordsLeft = getwordList(wordsLeft, usedCharacters).second;
        addDisplay = getwordList(wordsLeft, usedCharacters).first;

        int check = checkGuess(addDisplay);
        rightAnswer += check;

        if (check == 0) {
            cout << "Sorry, thre are no " << "'" << guessedCharacter << "'s." << endl;
            guessesNum -= 1;
        } else if (check == 1){
            cout << "Yes, there is one " << "'" << guessedCharacter << "'." << endl;
        } else {
            cout << "Yes, there are " << check << " '" << guessedCharacter << "'s." << endl;
        }
        if (rightAnswer == wordLength) {
            cout << "Wow! You won! The word was indeed " << "'" << wordsLeft[0] << "'" << endl; //the remaining one
            return;
        }
    }
    cout << "Game over! You lost. The word was " << "'" << wordsLeft[0] << "'" << endl; //pick any one
}

int main() {
    // [TODO: Fill this in!]
    // [TODO: Don't forget to call the recordTurnInfo function
    //        at the start of each turn and the recordGameEnd
    //        function at the end of the game! It's necessary
    //        for our autograders to function.]

    while (true) {
        gameInfor infor;
        cout << "Enter word length: ";
        cin >> infor.wordLength;
        cout << "How many guesses would you like? ";
        cin >> infor.guessesNum;

        while (true) {
            cout << "Show word count? ";
            string tmp;
            cin >> tmp;
            tmp = toLowerCase(tmp);
            if (tmp != "yes" && tmp != "no") {
                cout << "Sorry! I didn't understand that" << endl;
            } else {
                infor.showcountAns = tmp;
                break;
            }
        }
        playGame(infor);  //PLAY
        cout << endl;
        while (true) {
            cout << "Want to play again? ";
            string answer;
            cin >> answer;
            answer = toLowerCase(answer);
            if (answer == "no")
                goto END;
            else if (answer != "yes")
                cout << "Sorry, I didn't understand that. " << endl;
        }
    }
    END:
    cout << "Have a great day! " << endl;


    //int wordLength = 4;
    //cout << originalwordsList(wordLength).size();
    //vector<string> wordsLeft;
    //wordsLeft.push_back("ally");
    //wordsLeft.push_back("beta");
    //wordsLeft.push_back("cool");
    //wordsLeft.push_back("deal");
    //wordsLeft.push_back("else");
    //wordsLeft.push_back("flew");
    //wordsLeft.push_back("good");
    //wordsLeft.push_back("hope");
    //wordsLeft.push_back("ibex");
    //vector<string> usedCharacters;
    //usedCharacters.push_back("e");
    //usedCharacters.push_back("o");
    //(void) getwordList(wordsLeft, usedCharacters);
    //string currentDisplay = "-e--";
    //string addDisplay = "--";
    //displayWord(currentDisplay, addDisplay);
    //cout << checkGuess(addDisplay);

    return 0;
}

