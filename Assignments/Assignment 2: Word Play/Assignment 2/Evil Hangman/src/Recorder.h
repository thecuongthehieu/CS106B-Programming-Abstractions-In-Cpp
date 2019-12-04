/*
 * Header: Recorder.h
 *
 * Exports the recordTurnInfo and recordGameEnd functions. You'll need
 * to call these functions as part of the assignment, since they'll
 * hook into our autograder.
 */

#ifndef Recorder_Included
#define Recorder_Included

#include <string>

/**
 * Records information about how this particular turn went.
 *
 * This function is a template function. You can specify the used
 * letters in any format that you'd like, and this function will
 * still be able to accept it as a parameter.
 *
 * @param turnNumber  Which turn it is.
 * @param blankedWord The currently blanked-out version of the word.
 *                    You can represent this pretty much however you'd
 *                    like, and we'll figure out how to interpret it.
 * @param guessed     Which letters have been guessed so far, including
 *                    both correct and incorrect guesses. You can
 *                    represent this however you'd like, and we'll
 *                    figure out how to interpret it.
 * @param wordsLeft   How many words remaining in your master word list.
 * @param guessesLeft How many remaining guesses the player has.
 */
template <typename UsedLetterType>
void recordTurnInfo(int turnNumber,
                    const std::string& blankedWord,
                    const UsedLetterType& guessed,
                    int wordsLeft,
                    int guessesLeft) {
    // This has no effect now, but when we're grading, we'll
    // use this function to test your code!
    //
    // These lines suppress compiler warning messages about
    // unused parameters, but have no effect otherwise.
    (void) turnNumber;
    (void) blankedWord;
    (void) guessed;
    (void) wordsLeft;
    (void) guessesLeft;
}

/**
 * Records that the game has ended, along with the result.
 *
 * @param word The final word, which is either one of the remaining
 *             words from the word list (if the player lost) or the
 *             word the player ultimately figured out (if they won)
 * @param won  Whether the player won (true) or lost (false).
 */
inline void recordGameEnd(const std::string& word, bool won) {
    // This has no effect now, but when we're grading, we'll
    // use this function to test your code!
    //
    // These lines suppress compiler warning messages about
    // unused parameters, but have no effect otherwise.
    (void) word;
    (void) won;
}

#endif
