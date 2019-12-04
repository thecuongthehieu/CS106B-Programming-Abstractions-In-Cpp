/* File: BalancedParentheses.cpp
 *
 * A program that checks whether the parentheses in a string are
 * balanced.
 */
#include <iostream>
#include <string>
#include "stack.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given a line of text, returns whether the parentheses
 * (), [], and {} are balanced within that text.
 */
bool parensAreBalancedIn(string line);

int main() {
    while (true) {
        string text = getLine("Enter some text: ");
        if (parensAreBalancedIn(text)) {
            cout << "Yep!" << endl;
        } else {
            cout << "Nah" << endl;
        }
    }
}

/* Nice little helper functions that check whether a character
 * is an open or close parenthesis character.
 */
bool isOpenParenthesis(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

bool isCloseParenthesis(char ch) {
    return ch == ')' || ch == '}' || ch == ']';
}

/* Given a parenthesis character, returns a character that
 * matches it.
 */
char matchFor(char ch) {
    switch (ch) {
    case '(': return ')';
    case '{': return '}';
    case '[': return ']';
    case ')': return '(';
    case '}': return '{';
    case ']': return '[';
    default:
        error("Invalid argument!");
        return '?'; // Unreachable
    }
}

bool parensAreBalancedIn(string line) {
    /* Maintain a stack of the open parenthesis characters. */
    Stack<char> parens;
    for (char ch: line) {
        /* If this is an open parenthesis, then we need to remember
         * it for later on.
         */
        if (isOpenParenthesis(ch)) {
            parens.push(ch);
        }

        /* If it's a close parentheses, try to match it against the
         * top of the stack.
         */
        if (isCloseParenthesis(ch)) {
            if (parens.isEmpty()) return false;
            if (parens.pop() != matchFor(ch)) return false;
        }
    }

    /* When we're done, everything is balanced, provided that
     * there aren't any leftover open parens on the stack.
     */
    return parens.isEmpty();
}
