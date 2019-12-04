/********************************************************************
 * File: Main.cpp
 *
 * Testing code for the various priority queue classes. These tests
 * are written as template functions so that they can operate over
 * all different types of priority queues.
 */
#include "VectorPQueue.h"
#include "SinglyLinkedListPQueue.h"
#include "DoublyLinkedListPQueue.h"
#include "HeapPQueue.h"
#include "ExtraPQueue.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "console.h"
#include "error.h"
#include <iostream>
#include <string>
#include <sstream>    // For istringstream
#include <algorithm>  // For sort, reverse
#include <functional> // For greater
using namespace std;

/* Macro: checkCondition
 * ------------------------------------------------------------
 * A utility macro that makes it easier to diagnose and report
 * test failures.
 */
#define checkCondition(expr, reason) doCheckCondition((expr), (reason), #expr, __LINE__, __func__)

/* Function: docheckCondition
 * ------------------------------------------------------------
 * Checks whether the given condition is true.  If not, prints
 * a diagnostic error message.
 */
void doCheckCondition(bool expr, const string& reason,
                      const string& expression, int lineNumber,
                      const string& function) {
    if (expr) {
        cout << "  PASS: " << reason << endl;
    } else {
        cerr << "! FAIL: " << reason << endl;
        cerr << "     Test failed on line " << lineNumber << " of Main.cpp" << endl;
        cerr << "     Function: " << function << endl;
        cerr << "     Specific expression: " << expression << endl;
        cerr << "     Press ENTER to continue..." << endl;
        getLine();
    }
}

/* Function: beginTest
 * ------------------------------------------------------------
 * Displays a message indicating that a group of tests has
 * started.
 */
void beginTest(const string& testName) {
    cout << "================== BEGIN: " << testName << "==================" << endl;
}

/* Function: endTest
 * ------------------------------------------------------------
 * Displays a message indicating that a group of tests has
 * started.
 */
void endTest(const string& testName) {
    cout << "=================== END: " << testName << "===================" << endl;
    getLine("Press ENTER to continue...");
}

/* Function: logInfo
 * ------------------------------------------------------------
 * Displays an informational message.
 */
void logInfo(const string& message) {
    cout << "  info: " << message << endl;
}

/* Function: randomString
 * ------------------------------------------------------------
 * Returns a randomly-generated string of the given length.
 */
string randomString(int length = 16) {
    string result;
    for (int i = 0; i < length; i++) {
        result += char(randomInteger('A', 'Z'));
    }
    return result;
}


/* Function: basicStructuralTests
 * ------------------------------------------------------------
 * A function that does basic structural checks on a priority
 * queue.  It verifies that size/isEmpty agree, that the size
 * matches the number of elements, etc.
 *
 * If these tests are failing, it likely indicates that there
 * is a bug in your code that is causing your implementation
 * to remember size information correctly.
 */
template <typename PQueue>
void basicStructuralTests() {
    beginTest("Basic Structural Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates. It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {

        /* The use of curly braces here introduces a new block scope.  We
         * use this so that we can construct multiple different priority
         * queues.
         */

        /* Basic test: Add 5 elements to the queue and ensure that
         * the size is correct at each step.
         */
        {
            logInfo("These tests will check size() isEmpty() without calling dequeueMin().");

            PQueue queue;
            checkCondition(queue.isEmpty(), "New priority queue should be empty.");
            checkCondition(queue.size() == 0, "New priority queue should have size 0.");

            for (int i = 0; i < 5; i++) {
                queue.enqueue("Test String");

                checkCondition(queue.size() == i + 1, "Queue should have proper size after inserting a value.");
                checkCondition(!queue.isEmpty(), "Queue containing elements should not be empty.");
            }
        }

        /* Slightly more complex test: Enqueue and dequeue elements, ensuring the
         * size matches at each step.
         */
        {
            logInfo("We're about to start calling dequeueMin().");
            PQueue queue;

            for (int i = 0; i < 5; i++) {
                queue.enqueue("Test String");
            }

            for (int i = 5; i > 0; i--) {
                checkCondition(queue.size() == i, "Queue should have proper size after dequeues.");
                checkCondition(!queue.isEmpty(), "Queue should not be empty before all elements are removed.");
                queue.dequeueMin();
            }

            checkCondition(queue.size() == 0, "After removing all elements, the queue should have size 0.");
            checkCondition(queue.isEmpty(), "After removing all elements, the queue should be empty.");
        }

        /* Getting harder: The value dequeued should always match the value of peek(). */
        {
            logInfo("This next test will check whether peek() matches dequeueMin().");
            PQueue queue;

            for (int i = 0; i < 5; i++) {
                queue.enqueue(randomString());
            }

            while (!queue.isEmpty()) {
                string expected = queue.peek();
                checkCondition(queue.dequeueMin() == expected, "Value returned by peek() matches value returned by dequeueMin()");
            }
        }

        /* A different one - let's make sure that peeking at an empty queue causes an
         * error.
         */
        {
            PQueue queue;
            bool didThrow = false;
            try {
                logInfo("About to peek into an empty queue.  This may cause a crash");
                logInfo("if your implementation is incorrect.");
                queue.peek();
            } catch (ErrorException&) {
                didThrow = true;
            }

            checkCondition(didThrow, "Priority queue uses 'error' when peek() called on empty queue.");
        }

        /* In the same vein - what happens if we dequeue from an empty queue? */
        {
            PQueue queue;
            bool didThrow = false;
            try {
                logInfo("About to dequeue from an empty queue.  This may cause a crash");
                logInfo("if your implementation is incorrect.");
                queue.dequeueMin();
            } catch (ErrorException&) {
                didThrow = true;
            }

            checkCondition(didThrow, "Priority queue uses 'error' when dequeueMin() called on empty queue.");
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Basic Structural Tests");
}


/* Function: sortAscendingTests
 * ------------------------------------------------------------
 * A function that uses the priority queue to sort data that
 * has already been sorted.
 *
 * If your code is failing these tests, you probably have a bug
 * in either your enqueue() or dequeueMin() functions.
 */
template <typename PQueue>
void sortAscendingTests() {
    beginTest("Sort Ascending Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        /* The use of curly braces here introduces a new block scope.  We
         * use this so that we can construct multiple different priority
         * queues.
         */

        /* Basic test: Feed the strings A through H into the priority queue and confirm
         * that they come back in the same order.
         */
        {
            logInfo("Enqueuing A - H into the queue and confirming it comes back sorted.");
            PQueue queue;
            for (char ch = 'A'; ch <= 'H'; ch++) {
                /* The code
                 *
                 *    string(1, ch)
                 *
                 * converts the character ch into a one-character string.
                 */
                queue.enqueue(string(1, ch));
            }

            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Harder test: Sort 10 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Enqueuing ten sorted random strings and confirming it comes back sorted.");
            Vector<string> randomValues;
            for (int i = 0; i < 10; i++) {
                randomValues += randomString();
            }

            /* Use C++'s provided sorting routine to sort these values. */
            sort(randomValues.begin(), randomValues.end());

            /* Feed these values into the priority queue and pull them back out. */
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Confirm each comes back correctly. */
            for (int i = 0; i < randomValues.size(); i++) {
                checkCondition(queue.dequeueMin() == randomValues[i],
                               "Expecting to get value " + randomValues[i] + " from queue.");
            }
        }

        /* Much harder test: Sort 10000 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Generating 10000 random strings.");
            Vector<string> randomValues;
            for (int i = 0; i < 10000; i++) {
                randomValues += randomString();
            }

            /* Use C++'s provided sorting routine to sort these values. */
            logInfo("Sorting 10000 random strings.");
            sort(randomValues.begin(), randomValues.end());

            /* Feed these values into the priority queue and pull them back out. */
            logInfo("Enqueuing 10000 random strings.");
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Confirm each comes back correctly. */
            logInfo("Dequeuing 10000 random strings.");
            bool isCorrect = true;
            for (int i = 0; i < randomValues.size(); i++) {
                if (queue.dequeueMin() != randomValues[i]) {
                    isCorrect = false;
                    break;
                }
            }

            checkCondition(isCorrect, "Queue correctly sorted 10000 random strings.");
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Ascending Tests");
}

/* Function: sortDescendingTests
 * ------------------------------------------------------------
 * A function that uses the priority queue to sort data that
 * has already been sorted in reverse.
 *
 * If your code is failing these tests, you probably have a bug
 * in either your enqueue() or dequeueMin() functions.
 */
template <typename PQueue>
void sortDescendingTests() {
    beginTest("Sort Descending Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        /* The use of curly braces here introduces a new block scope.  We
         * use this so that we can construct multiple different priority
         * queues.
         */

        /* Basic test: Feed the strings H through A into the priority queue and confirm
         * that they come back in the same order.
         */
        {
            logInfo("Enqueuing A - H in reverse order and checking that it comes back sorted.");
            PQueue queue;
            for (char ch = 'H'; ch >= 'A'; ch--) {
                /* The code
                 *
                 *    string(1, ch)
                 *
                 * converts the character ch into a one-character string.
                 */
                queue.enqueue(string(1, ch));
            }

            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Harder test: Sort 10 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Enqueuing ten reverse sorted random strings and confirming it comes back sorted.");
            Vector<string> randomValues;
            for (int i = 0; i < 10; i++) {
                randomValues += randomString();
            }

            /* Use C++'s provided sorting routine to sort these values. */
            sort(randomValues.begin(), randomValues.end(), greater<string>());

            /* Feed these values into the priority queue and pull them back out. */
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Confirm each comes back correctly. */
            reverse(randomValues.begin(), randomValues.end());
            for (int i = 0; i < randomValues.size(); i++) {
                checkCondition(queue.dequeueMin() == randomValues[i],
                               "Expecting to get value " + randomValues[i] + " from queue.");
            }
        }

        /* Much harder test: Sort 10000 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Generating 10000 random strings.");
            Vector<string> randomValues;
            for (int i = 0; i < 10000; i++) {
                randomValues += randomString();
            }

            /* Use C++'s provided sorting routine to sort these values. */
            logInfo("Sorting 10000 random strings.");
            sort(randomValues.begin(), randomValues.end(), greater<string>());

            /* Feed these values into the priority queue and pull them back out. */
            logInfo("Enqueuing 10000 random strings.");
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Confirm each comes back correctly. */
            logInfo("Dequeuing 10000 random strings.");
            bool isCorrect = true;
            reverse(randomValues.begin(), randomValues.end());
            for (int i = 0; i < randomValues.size(); i++) {
                if (queue.dequeueMin() != randomValues[i]) {
                    isCorrect = false;
                    break;
                }
            }

            checkCondition(isCorrect, "Queue correctly sorted 10000 random strings.");
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Descending Tests");
}

/* Function: sortRandomTests
 * ------------------------------------------------------------
 * A function that uses the priority queue to sort data that
 * is stored in no particular order.
 *
 * If your code is failing these tests, you probably have a bug
 * in either your enqueue() or dequeueMin() functions.
 */
template <typename PQueue>
void sortRandomTests() {
    beginTest("Sort Random Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        /* The use of curly braces here introduces a new block scope.  We
         * use this so that we can construct multiple different priority
         * queues.
         */

        /* Basic test: Feed the strings H through A into the priority queue in some order,
         * then confirm that they come back in sorted order
         */
        {
            logInfo("Enqueuing a random permutation of A - H and checking whether it leaves sorted.");
            Vector<string> letters;
            for (char ch = 'A'; ch <= 'H'; ch++) {
                /* The code
                 *
                 *    string(1, ch)
                 *
                 * converts the character ch into a one-character string.
                 */
                letters += string(1, ch);
            }

            /* Scramble the letters with the STL random_shuffle algorithm. */
            random_shuffle(letters.begin(), letters.end());

            /* Load the letters into the priority queue. */
            PQueue queue;
            for (string letter: letters) {
                queue.enqueue(letter);
            }

            /* Confirm they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Harder test: Sort 10 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Enqueuing 10 random strings and checking whether it leaves sorted.");
            /* Create 10 random strings. */
            Vector<string> randomValues;
            for (int i = 0; i < 10; i++) {
                randomValues += randomString();
            }

            /* Feed these values into the priority queue and pull them back out. */
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Confirm each comes back correctly. */
            sort(randomValues.begin(), randomValues.end());
            for (int i = 0; i < randomValues.size(); i++) {
                checkCondition(queue.dequeueMin() == randomValues[i],
                               "Expecting to get value " + randomValues[i] + " from queue.");
            }
        }

        /* Much harder test: Sort 10000 random strings and confirm that the priority queue hands
         * them back in the same order.
         */
        {
            logInfo("Generating 10000 random strings.");
            Vector<string> randomValues;
            for (int i = 0; i < 10000; i++) {
                randomValues += randomString();
            }

            /* Feed these values into the priority queue and pull them back out. */
            logInfo("Enqueuing 10000 random strings.");
            PQueue queue;
            for (string value: randomValues) {
                queue.enqueue(value);
            }

            /* Use C++'s provided sorting routine to sort these values. */
            logInfo("Sorting 10000 random strings.");
            sort(randomValues.begin(), randomValues.end(), greater<string>());

            /* Confirm each comes back correctly. */
            logInfo("Dequeuing 10000 random strings.");
            bool isCorrect = true;
            reverse(randomValues.begin(), randomValues.end());
            for (int i = 0; i < randomValues.size(); i++) {
                if (queue.dequeueMin() != randomValues[i]) {
                    isCorrect = false;
                    break;
                }
            }

            checkCondition(isCorrect, "Queue correctly sorted 10000 random strings.");
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Random Tests");
}


/* Function: sortCraftedTests
 * ------------------------------------------------------------
 * A function that constructs specific inputs known to give
 * buggy priority queues trouble, then tests the given priority
 * queue on them.
 *
 * If your code is failing these tests, you probably have a bug
 * in either your enqueue() or dequeueMin() functions.
 */
template <typename PQueue>
void sortCraftedTests() {
    beginTest("Sort Crafted Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        /* The use of curly braces here introduces a new block scope.  We
         * use this so that we can construct multiple different priority
         * queues.
         */

        /* First test: Two concatenated sequences of ascending values that
         * interleave with one another.
         */
        {
            logInfo("Sorting two sequences that need to be interleaved.");
            Vector<string> sequence = {
                "A", "C", "E", "G", "B", "D", "F", "H"
            };

            /* Feed this sequence into the priority queue. */
            PQueue queue;
            for (string letter: sequence) {
                queue.enqueue(letter);
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Second test: Two interleaving sequences, alternate version.. */
        {
            logInfo("Sorting two sequences that need to be interleaved, version two.");
            Vector<string> sequence = {
                "B", "D", "F", "H", "A", "C", "E", "G"
            };

            /* Feed this sequence into the priority queue. */
            PQueue queue;
            for (string letter: sequence) {
                queue.enqueue(letter);
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Third test: Two decreasing interleaved sequences. */
        {
            logInfo("Sorting two decreasing sequences that need to be interleaved.");
            Vector<string> sequence = {
                "H", "F", "D", "B", "G", "E", "C", "A"
            };

            /* Feed this sequence into the priority queue. */
            PQueue queue;
            for (string letter: sequence) {
                queue.enqueue(letter);
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

        /* Fourth test: Two decreasing interleaved sequences, alternate version. */
        {
            logInfo("Sorting two decreasing sequences that need to be interleaved, version 2.");
            Vector<string> sequence = {
                "G", "E", "C", "A", "H", "F", "D", "B"
            };

            /* Feed this sequence into the priority queue. */
            PQueue queue;
            for (string letter: sequence) {
                queue.enqueue(letter);
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                string expected(1, ch);
                checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
            }
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Crafted Tests");
}

/* Function: sortDuplicateTests
     * ------------------------------------------------------------
     * A function that tests the priority queue's ability to handle
     * duplicate elements.
     *
     * If your code is failing these tests, you probably have a bug
     * in either your enqueue() or dequeueMin() functions.
     */
template <typename PQueue>
void sortDuplicateTests() {
    beginTest("Sort Duplicate Tests");

    /* This try ... catch system is designed to catch any errors that the
         * program explicitly generates.  It does not guard against runtime
         * crashes from errors like following a bad pointer, so if your
         * program crashes and pulls up the debugger, you should be looking
         * for memory errors.
         */
    try {
        /* The use of curly braces here introduces a new block scope.  We
             * use this so that we can construct multiple different priority
             * queues.
             */

        /* First test: Duplicate the letters A - D, in order, and see if they
             * come back correctly.
             */
        {
            logInfo("Loading a sorted sequence containing duplicates.");
            /* Populate a priority queue accordingly. */
            PQueue queue;
            for (char ch = 'A'; ch <= 'D'; ch++) {
                queue.enqueue(string(1, ch));
                queue.enqueue(string(1, ch));
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'D'; ch++) {
                for (int i = 0; i < 2; i++) {
                    string expected(1, ch);
                    checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
                }
            }
        }

        /* Second test: Duplicate the letters A - D, in reverse order, and see if they
             * come back correctly.
             */
        {
            logInfo("Loading a reverse sorted sequence containing duplicates.");

            /* Populate a priority queue accordingly. */
            PQueue queue;
            for (char ch = 'D'; ch >= 'A'; ch--) {
                queue.enqueue(string(1, ch));
                queue.enqueue(string(1, ch));
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'D'; ch++) {
                for (int i = 0; i < 2; i++) {
                    string expected(1, ch);
                    checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
                }
            }
        }

        /* Third test: Enqueue the letters A - H, then duplicate the sequence. */
        {
            logInfo("Loading two sorted sequences, one after the other.");
            /* Populate a priority queue accordingly. */
            PQueue queue;
            for (int i = 0; i < 2; i++) {
                for (char ch = 'A'; ch <= 'H'; ch++) {
                    queue.enqueue(string(1, ch));
                }
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                for (int i = 0; i < 2; i++) {
                    string expected(1, ch);
                    checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
                }
            }
        }

        /* Fourth test: Enqueue the letters A - H, in reverse order, then duplicate the sequence. */
        {
            logInfo("Loading two reverse sorted sequences, one after the other.");

            /* Populate a priority queue accordingly. */
            PQueue queue;
            for (int i = 0; i < 2; i++) {
                for (char ch = 'H'; ch >= 'A'; ch--) {
                    queue.enqueue(string(1, ch));
                }
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                for (int i = 0; i < 2; i++) {
                    string expected(1, ch);
                    checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
                }
            }
        }

        /* Fifth test: Load a sorted sequence, then duplicate the middle 50%. */
        {
            logInfo("Loading a sorted sequence, then repeating the middle.");

            /* Load the first range, then the second. */
            PQueue queue;
            for (char ch = 'A'; ch <= 'H'; ch++) {
                queue.enqueue(string(1, ch));
            }
            for (char ch = 'C'; ch <= 'F'; ch++) {
                queue.enqueue(string(1, ch));
            }

            /* Dequeue the elements and confirm that they come back sorted. */
            for (char ch = 'A'; ch <= 'H'; ch++) {
                int numTimes = (ch >= 'C' && ch <= 'F'? 2 : 1);
                for (int i = 0; i < numTimes; i++) {
                    string expected(1, ch);
                    checkCondition(queue.dequeueMin() == expected, "Queue should yield " + expected + ".");
                }
            }
        }


    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Duplicate Tests");
}

/* Function: sortBlankTests
 * ------------------------------------------------------------
 * A function that tests whether the priority queue can sort
 * a mixture of empty and nonempty strings. If you're failing
 * these tests, it might suggest that your code is using the
 * empty string as a sentinel (which it shouldn't!) or that you
 * are accidentally performing some comparisons that you
 * shouldn't be.
 */
template <typename PQueue>
void sortBlankTests() {
    beginTest("Sort Blanks Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        logInfo("Loading 10 elements, 5 blank, and 5 non-blank");

        /* Load the first range, then the second. */
        PQueue queue;
        for (int i = 0; i < 10; i++) {
            queue.enqueue((i % 2 == 0)? "A" : "");
        }

        /* Dequeue the elements and confirm that they come back sorted. */
        for (int i = 0; i < 5; i++) {
            checkCondition(queue.dequeueMin() == "", "Queue should return a blank string.");
        }
        for (int i = 0; i < 5; i++) {
            checkCondition(queue.dequeueMin() == "A", "Queue should return a non-blank string.");
        }

    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Sort Blanks Tests");
}

/* Function: reuseTests
 * ------------------------------------------------------------
 * A function that tests the priority queue's ability to fill
 * up, then empty, then fill up again.
 *
 * If your code is failing these tests, you probably have a bug
 * in either your enqueue() or dequeueMin() functions.
 */
template <typename PQueue>
void reuseTests() {
    beginTest("Reuse Tests");

    /* This try ... catch system is designed to catch any errors that the
     * program explicitly generates.  It does not guard against runtime
     * crashes from errors like following a bad pointer, so if your
     * program crashes and pulls up the debugger, you should be looking
     * for memory errors.
     */
    try {
        PQueue queue;

        bool isSorted = true;
        for (int i = 0; i < 5; i++) {
            /* Generate 10000 values to enter and remove. */
            logInfo("Generating 10000 random strings.");
            Vector<string> strings;
            for (int i = 0; i < 10000; i++) {
                strings += randomString();
            }

            /* Enqueue them into the priority queue. */
            logInfo("Enqueuing 10000 random strings.");
            for (string str: strings) {
                queue.enqueue(str);
            }

            /* Sort the strings so we can check that we have them in the right
             * order.
             */
            logInfo("Sorting 10000 random strings.");
            sort(strings.begin(), strings.end());

            /* Confirm they come back correctly. */
            logInfo("Dequeuing 10000 random strings.");
            for(string str: strings) {
                if (queue.dequeueMin() != str) {
                    isSorted = false;
                }
            }

            if (!isSorted) break;
        }

        checkCondition(isSorted, "Strings were consistently sorted.");


    } catch (const ErrorException& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.getMessage() << endl;
        cerr << "Stack trace: " << e.getStackTrace() << endl;
    } catch (const exception& e) {
        cerr << "TEST FAILURE: Unexpected exception: " << e.what() << endl;
    } catch (...) {
        cerr << "TEST FAILURE: Unknown exception." << endl;
    }

    endTest("Reuse Tests");
}

/* Function: myVeryOwnTests
 * ------------------------------------------------------------------
 * If you'd like to add any testing code of your own, feel free to
 * add them!  This test currently has no functionality associated
 * with it, but you can improve upon that if you'd like.
 */
template <typename PQueue>
void myVeryOwnTests() {
    beginTest("My Very Own Tests");

    PQueue queue;

    /* TODO: Add your own tests here, if you'd like. */

    endTest("My Very Own Tests");
}

/* Function: testPriorityQueue
 * ------------------------------------------------------------------
 * A function that runs the full battery of tests on a priority
 * queue of arbitrary type.
 */
template <typename PQueue>
void testPriorityQueue() {

    basicStructuralTests<PQueue> ();
    sortAscendingTests<PQueue> ();
    sortDescendingTests<PQueue> ();
    sortRandomTests<PQueue> ();
    sortCraftedTests<PQueue> ();
    sortDuplicateTests<PQueue> ();
    sortBlankTests<PQueue> ();
    reuseTests<PQueue> ();

    /* If you want to run your own custom tests, uncomment this line. */
    // myVeryOwnTests<PQueue> ();
}

/* Function: printReplInstructions
 * ------------------------------------------------------------------
 * Prints instructions on how to use the REPL environment.
 */
void printReplInstructions() {
    cout << "Interactive Priority Queue Test" << endl;
    cout << "===============================" << endl;
    cout << "This environment allows you to type in commands that will be" << endl;
    cout << "executed on your priority queue.  The interpreter knows the" << endl;
    cout << "following commands:" << endl;
    cout << endl;
    cout << "   isEmpty:        Reports whether the priority queue is empty." << endl;
    cout << "   size:           Reports the size of the priority queue" << endl;
    cout << "   enqueue <str>:  Enqueues the string <str>" << endl;
    cout << "   peek:           Peeks at the minimum element of the priority queue." << endl;
    cout << "   dequeueMin:     Dequeues the minimum element of the priority queue." << endl;
    cout << "   quit:           Quits the interpret and returns to the menu." << endl;
    cout << endl;
    cout << "The first letter of any command can be used as a substitute" << endl;
    cout << "for any command name." << endl;
}

/* Function: replTestPriorityQueue
 * ------------------------------------------------------------------
 * A function that executes a read/eval/print loop (REPL) that allows
 * you to manually test out the priority queue. Entering commands
 * like
 *
 *    enqueue This is a test
 *
 * or
 *
 *    peek
 *
 * will execute those corresponding commands on the priority queue.
 * You can use this code to interactively step through your priority
 * queue.
 */
template <typename PQueue>
void replTestPriorityQueue() {
    printReplInstructions();

    /* These curly braces introduce a new layer of scoping. This ensures that if
     * your priority queue's destructor causes an error, the error occurs before
     * this function returns.
     */
    {
        PQueue queue;
        while (true) {
            /* Get a command from the user. */
            istringstream command(getLine("Enter command: "));

            /* Extract the action. */
            string action;
            command >> action;

            if (!command) {
                cout << "Please enter a command." << endl;
            } else {
                try {
                    if (action == "peek" || action == "p") {
                        cout << "  Result: \"" << queue.peek() << "\"" << endl;
                    } else if (action == "isEmpty" || action == "i") {
                        cout << "  Result: " << boolalpha << queue.isEmpty() << endl;
                    } else if (action == "size" || action == "s") {
                        cout << "  Result: " << queue.size() << endl;
                    } else if (action == "dequeueMin" || action == "d") {
                        cout << "  Result: \"" << queue.dequeueMin() << "\"" << endl;
                    } else if (action == "quit" || action == "q") {
                        cout << "  Leaving tests...   " << flush;
                        break;
                    } else if (action == "enqueue" || action == "e") {
                        string toEnqueue;
                        command >> ws;               // Skip whitespace before the string to enqueue
                        getline(command, toEnqueue); // Silent failure (nothing to enqueue) is okay
                        queue.enqueue(toEnqueue);
                        cout << "  Enqueued \"" << toEnqueue << "\"." << endl;
                    } else {
                        cerr << "  Unknown command." << endl;
                    }

                } catch (const ErrorException& e) {
                    cerr << "ERROR: " << e.getMessage() << endl;
                    cerr << e.getStackTrace() << endl;
                } catch (const exception& e) {
                    cerr << "ERROR: " << e.what() << endl;
                } catch (...) {
                    cerr << "ERROR: Unknown error." << endl;
                }
            }
        }
    }

    /* If we made it here, the destructor didn't crash. */
    cout << "success." << endl;
    cout << endl;
}

/* Constants for the menu. */
enum {
    REPL_VECTOR = 1,
    TEST_VECTOR,
    REPL_LINKED_LIST,
    TEST_LINKED_LIST,
    REPL_DOUBLY_LINKED_LIST,
    TEST_DOUBLY_LINKED_LIST,
    REPL_HEAP,
    TEST_HEAP,
    REPL_EXTRA,
    TEST_EXTRA,
    QUIT
};

/* Function: displayMenu
 * ------------------------------------------------------------------
 * Displays the menu of testing options.
 */
void displayMenu() {
    cout << "CS106B Priority Queue Testing Harness" << endl;
    cout << "=====================================" << endl;
    cout << REPL_VECTOR << ": Manually test VectorPriorityQueue" << endl;
    cout << TEST_VECTOR << ": Automatically test VectorPriorityQueue" << endl;
    cout << REPL_LINKED_LIST << ": Manually test LinkedListPriorityQueue" << endl;
    cout << TEST_LINKED_LIST << ": Automatically test LinkedListPriorityQueue" << endl;
    cout << REPL_DOUBLY_LINKED_LIST << ": Manually test DoublyLinkedListPriorityQueue" << endl;
    cout << TEST_DOUBLY_LINKED_LIST << ": Automatically test DoublyLinkedListPriorityQueue" << endl;
    cout << REPL_HEAP << ": Manually test HeapPriorityQueue" << endl;
    cout << TEST_HEAP << ": Automatically test HeapPriorityQueue" << endl;
    cout << REPL_EXTRA << ": Manually test ExtraPriorityQueue" << endl;
    cout << TEST_EXTRA << ": Automatically test ExtraPriorityQueue" << endl;
    cout << QUIT << ": Quit" << endl;
}

/* Prompts you to choose which tests to run.  Please feel free to add or edit
 * the tests in this file.
 */
int main() {
    while (true) {
        displayMenu();

        /* Respond to the user's choice. */
        switch (getInteger("Enter choice: ")) {
        case TEST_VECTOR:
            testPriorityQueue<VectorPriorityQueue> ();
            break;
        case REPL_VECTOR:
            replTestPriorityQueue<VectorPriorityQueue> ();
            break;
        case TEST_LINKED_LIST:
            testPriorityQueue<SinglyLinkedListPriorityQueue> ();
            break;
        case REPL_LINKED_LIST:
            replTestPriorityQueue<SinglyLinkedListPriorityQueue> ();
            break;
        case TEST_DOUBLY_LINKED_LIST:
            testPriorityQueue<DoublyLinkedListPriorityQueue> ();
            break;
        case REPL_DOUBLY_LINKED_LIST:
            replTestPriorityQueue<DoublyLinkedListPriorityQueue> ();
            break;
        case TEST_HEAP:
            testPriorityQueue<HeapPriorityQueue> ();
            break;
        case REPL_HEAP:
            replTestPriorityQueue<HeapPriorityQueue> ();
            break;
        case TEST_EXTRA:
            testPriorityQueue<ExtraPriorityQueue> ();
            break;
        case REPL_EXTRA:
            replTestPriorityQueue<ExtraPriorityQueue> ();
            break;
        case QUIT:
            cout << "Have a nice day!" << endl;
            return 0;
        default:
            cerr << "Sorry, but I don't know how to do that." << endl;
            break;
        }
    }

    return 0;
}

