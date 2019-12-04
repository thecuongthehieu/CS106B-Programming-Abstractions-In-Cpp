/* File: LibraryOfBabel.cpp
 *
 * A program that, in principle, could generate all pieces of text
 * that could ever be written!
 */
#include <iostream>
#include <string>
#include <iomanip>
#include "queue.h"
#include "stack.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Be careful about making this larger than 4 - it can dramatically
 * slow down your system!
 *
 * However, if you use a Stack instead of a Queue, everything will
 * work out just great!
 */
const int kMaxLength = 2;

int main() {
    /* For an alternative approach, try doing this with a stack
     * and not a queue!
     */
    Queue<string> worklist;
    worklist.enqueue("");

    while (!worklist.isEmpty()) {
        /* Report the current string. */
        string curr = worklist.dequeue();
        cout << curr << " ";

        /* If we haven't hit our length limit, put back into the
         * worklist all of the strings that are one character
         * longer than us.
         */
        if (curr.length() < kMaxLength) {
            for (char ch = 'A'; ch <= 'Z'; ch++) {
                worklist.enqueue(curr + ch);
            }
        }
    }

    return 0;
}
