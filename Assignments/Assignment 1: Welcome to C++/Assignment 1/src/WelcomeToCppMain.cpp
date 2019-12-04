/*
 * CS106B Assignment 1: Welcome to C++!
 *
 * This client program contains a text menu for running your
 * code for the different problems in this assignment.
 *
 * You don't need to modify this file.
 * 
 * @author Marty Stepp, Anton Apostolatos, Keith Schwarz
 * @version 2017
 * - modified for 17win version
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include "console.h"
#include "filelib.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "WelcomeToCpp.h"
using namespace std;

// provided helpers
bool ask(string prompt);

// testing function prototype declarations
void test_flipHeads();
void test_combinations();
void test_strToInt();
void test_intToStr();
void test_stackOverflow();
void test_fleschKincaidFile();
void test_fleschKincaidDirect();


int main() {
    cout << "CS106B Assignment 1: Welcome to C++!" << endl;
    while (true) {
        cout << endl;
        cout << "Choose a problem:" << endl;
        cout << "1) Flip Heads" << endl;
        cout << "2) Combinations and Pascal's Triangle" << endl;
        cout << "3) Trigger a Stack Overflow" << endl;
        cout << "4) String to Integer" << endl;
        cout << "5) Integer to String" << endl;
        cout << "6) Flesch-Kincaid Grade-Level Test (on a file)" << endl;
        cout << "7) Flesch-Kincaid Grade-Level Test (on direct input)" << endl;

        int choice = getInteger("Enter your choice (or 0 to quit): ");
        cout << endl;
        if (choice == 0)      { break; }
        else if (choice == 1) { test_flipHeads(); }
        else if (choice == 2) { test_combinations(); }
        else if (choice == 3) { test_stackOverflow(); }
        else if (choice == 4) { test_strToInt(); }
        else if (choice == 5) { test_intToStr(); }
        else if (choice == 6) { test_fleschKincaidFile(); }
        else if (choice == 7) { test_fleschKincaidDirect(); }
    }

    cout << "Exiting." << endl;
    return 0;
}

/*
 * This function tests your flip heads function
 */
void test_flipHeads() {
    flipHeads();
}

/* Prompts the user for a natural number (a nonnegative integer) */
int getNaturalNumber(string prompt) {
    while (true) {
        int value = getInteger(prompt);
        if (value >= 0) return value;

        cout << "Please enter a nonnegative value." << endl;
    }
}

/*
 * This function tests your combination function
 */
void test_combinations() {
    do {
        int n = getNaturalNumber("Enter n (the number of people in the big group): ");

        int k;
        while (true) {
            k = getNaturalNumber("Enter k (the number of people to choose from the group): ");
            if (k <= n) break;

            cout << "Please enter a number less than or equal to " << n << endl;
        }
        cout << "Result (the number of ways to pick " << k << " people from an " << n << "-person group): " << nChooseK(n, k) << endl;
        cout << endl;
    } while (ask("Continue"));
}

/* Determines whether a string is a valid number. We use this to
 * filter bad inputs out so that you don't have to worry about
 * them in stringToInt.
 */
bool isNumericString(string line) {
    try {
        /* Try converting the string to an integer. If it succeeds,
         * great!
         */
        (void) stringToInteger(line);
        return true;
    } catch (...) {
        /* If it fails, it's not a valid integer. */
        return false;
    }
}

/*
 * This function tests your string to int function
 */
void test_strToInt() {
    while (true) {
        string line = getLine("Provide a number (or Enter to quit): ");
        if (line.length() == 0) break;

        if (isNumericString(line)) {
            int integer = stringToInt(line);
            cout << "Result: " << integer << endl;
        } else {
            cout << "Please enter a valid number." << endl;
        }
    }
}


/*
 * This function tests your int to string function
 */
void test_intToStr() {
    do {
        int line = getInteger("Provide a number: ");
        string str = intToString(line);
        cout << "Result: " << str << endl;
    } while (ask("Continue"));
}

/* The "Goto Table" for the Stack Overflow example. This is essentially a function
 * that given a number between 0 and 1023 gives back a number between 0 and 1023.
 * Our function uses this table to make it hard to predict what's going to happen
 * next. Use the debugger to find out!
 */
static const int kGotoTable[] = {
    456,  841,  205,  326,  999,  935,   16,  497,  825,  218,  719,  204,  722,  792,  889,  779,  195, 1008,  776,  834,  587,  652,  498,  973,  428,  676,  876,  148,  126,  374,  190,   76,
    530,  994,  898,  806,   75,  865,   30,  863,   36,  167,    7,  414,  496,  391,  103,  111,  679,   35,  953,   65, 1013,   45,  263,  736,  760,  648,  983,   78,  626,   83,  571,  595,
     73,  877,  887,  666,  319,  275,  443,    9,  646,  257,  746,  526,  163,   53,    6,  726,   51,  485, 1014,  665,  738,  198,  493,  337,  761,  971,   31, 1009,   88,  325,  151,  177,
   1007,  466,  988,  897,  644,  696,  630,  998,  193,  924,  769,  459,  107,  710,  519,  281,  390,  934,  632,  297,  484,  554,  314,  949,   47,   87,  400,  900,  931,  856,  470,   81,
    191,  101,  780,  342,   82,  693,  528,  701,  499,  164,  671,  181,  395,   34,  481,  614,  547,  478,  588,   43,  673,  440,  258,  568,  196,  790,  479,  844,  728,  365,  896,  868,
    592,  283, 1000,  720,  685,  913,  387,  527,  796,  583,   79,   13,  334,  805,  929,  921,  610,  521,  364,  791,  253,  811,  773,  309,  637,  749,  421,  942,  729,  694,  940,  122,
    393,  525, 1012,   74,  559,  371,  869,   12,  581,   24, 1011,  327,  681,  893,  835,  704,   62,  492,  293,  389,  977,  429,  458,  357,  347,  129,  274,  222,   23,  851,  301,  578,
     70,  550,  946,  797,    2,  882,   40,  923, 1017,  885,  173,  462,  133,  329,  503,  997,  402,  359,   32,  132,  970,  185,  490,  225,  565,   28,  843,  510,  223,  707,  532,  338,
     64,  154,  627,  483,  700,  697,  477,  545,  937,  702,    5,  494,  705,  926,  596,   22,  143,  118,  202,  169,  854,  939,  867,  188,  212,  145, 1021,  830,  114,  833,  316,  925,
    649,  708,  838,  373,  216,  658,   77,  757,  340,  514,  339,  380,  593,  403,  566,  230,  981,  616,  174,  277,  706,   71,  640,  352,  576,  460,   14,  333,  574,   46,  793,  131,
    439,  692,  123,  376,   52,  457,   99,  549,   27,  713,  320,  752,  147,  775,   89,  961,  384,   38,  672,  142,  135,   97,  589,  157,  699,  430,  635,  287,  846,  817,  995,  422,
    758,  209,  991,  801,  300,  434,  562,  323,  546,  860,  450,  121,  812,  563,  905, 1006,  611,  508,  774,  310,  754,  990,  798, 1005,  271,  954,  770,  426,  500,  883,  660,  467,
     67,  920,  886,  161,  687,  584,  409,  141,  350,  711,  410,  698,  245,  482,  535,  351,  511,  986,  515,  659,  778,  955,  264,  331,  911,  267,  189,  231,  162,  594,  788,  782,
    794,  677,  747,  814,  399,  992,  468,   18,  850,  891,  144,  582,  343,  522,  613,   92,  839,  168,  909,   93,  933,  972,  247, 1004,  739,  115,  654,  454,  534,  906,  907,  695,
    819,  802,  591,  406,  227,   37,  290,  194,  404,   41,   20,  888,  918,  941,  601,  771,  480,  826,  488,   68,  952,  232,  255,  269,  871,  307,  762,  378,  600,  237,  899,  849,
    932,  413,  980,  186,  950,  651,  415,  645,  784,    0,  551,  725,  670,  661,  930,  721,  564,  620,  233,  317,  197,  976,  242,   44,  506,  433,    1,  140,  318,  328,   95,  653,
    464,  292,  249,  423,  146,  254,  299,   54,  213,  996,   21,  200,  948,  446,  149,  741,  866,  870,  878,  624,  285,  416,  507,  279,  647,  612,  455,  767,  602,   58,   42,  786,
    974,  447,  282,  354,  742,  137,  727,  407, 1002,  915,  348,  539,  385,  335,  236,  912,  577,  689,  813,  958,  628,  548,  124,  884,  179,   26,  605,  465,  951,  171,  441,  420,
    418,  502,  718,  987,  531,  716,  243,  211,   94,  822,  358,   56,  982,  541,  842,  452,  268,  353,  435,  408,  895,  730,   90,  816,  669,  759,  117,  240,  743,  288,  251,  638,
    542,  927,  824,  270,   80,  618,  379,  857, 1019,  967,  278,   39,   15,  853,  375,  308,  208,  349,  960,  158,  425,  524,  294,  703,  228,  733,  445, 1022,  709,  615,  787,  266,
    804,  680,  453,  262,  968,  295,  621,  712,  210,  803,  280,   98,  303,  105,  362,  682,  377,  401,  807,  370,   86,  489,  139,  963,  463,  643,  943,  155,  113,  772,  538,  127,
    599,  634,  633,  567,  715,   50,  663,  206,  427,   29,  112,  523,  272,  203,  845,  346,  580,  956,  229,  902,  777,    3,  109,  650,  381,  674,  872,  558,  723,  737,  472,  892,
    664,   10,  827,   17,  631,  286,  607,  265,  207,  336,  215,  572,  984,  182,  947,  916,  848,  609,  248,  914,  363,  486,  604,   33,  261,  684,  315, 1001,  569,  852,  432,  586,
    537,  516,   57,   60,  160,  120,  110,  556,  517,  656,  306,  451,  509,  298,  642,  828,  745,  629,   66,   96,   84,  361, 1003, 1020,  180,  276,  667,  166,   72,  394,  904,  219,
    192, 1010,  321,  688,  224,  259,  691,  405,  382,  178,  964,  544,  585,    4,  220,  879,  732,  832,  978,  606,  104,  910,  809,  100,  799,  862,  861,  431,  890,  199,  324,  360,
     49,  183,  471,  138,  617,  244,  847,  449,  529,   61,  768,  800,  969,  505,   11,  234,  102,  625,  836,  756,  678,  875,  573,  125, 1016,  683,  579,  312,  962,  473,  152,  686,
    273,  740,  150,  201,  136,  821,  355,  724,  859,  116,  461,  858,  397,  881,  570,   55,  134,  388,  755,  332,  356,  438,  221,   85,  386,  979,  831,  226,  873,  396,  789,  945,
    655,  763,  424,  330,  476,  170,  444,  748,  557,  561,  823,  657,  908,  553,  985,  735,  469,  619,  304, 1018,  130,  781,  874,   69,   48,  810,  598,  957,  217,  345,  623,  734,
     59,  936,  322,  106,  690,  829,  785,  305,  917,  383,  296,  989,  487,  555,  668,  820,  520,  837,  518,  491,   91,  714,  540,  543,  608,  903,   25,  284,  159,  501,  367,  765,
     19,  864,  959,  675,  536,  641,  241,  411,  214,  256,  419,  250,  344,  153,  176,  437,  764,  944,  880, 1015,  165,  840,  108,  533,  965,  235,  815,  442,  302,  291,  922,  560,
    753,  750,  260,  993,  475,  172,  639,  369,  590,  938,  855,  238,  504,  184,  119,  368,  448,  744,  975,  928,  603,  128,  795,  187,  436, 1023,  552,  808,  783,  398,  662,  622,
    311,  372,  392,  513,  289,  366,  495,  474,  597,  246,  417,  575,  894,  512,  717,  731,  751,  313,  252,  175,  966,  412,  636,  818,  239,  766,  341,   63,  901,  919,  156,    8,
};

/**
 * This function is going to trigger a stack overflow. The function takes its argument,
 * uses it as an index into the table, then calls itself using that new index. This
 * recursion never stops, so it eventually crashes the program. We've chosen the
 * particular numbers above because the program eventually calls this function on
 * a certain sequence over and over and over again. Your job is to use the debugger,
 * the stack trace, and the variables window to figure out what the numbers in
 * the sequence are.
 *
 * Once you've found them, update the header file comments in WelcomeToCpp.cpp
 * to list them out in the order they're called, starting with 137.
 */
void triggerStackOverflow(int index) {
    triggerStackOverflow(kGotoTable[index]);
}

void test_stackOverflow() {
    cerr << "Warning! This is going to crash your program." << endl;
    cerr << "Make sure you ran your program using the \"Debug\" option," << endl;
    cerr << "the green triangle with the little bug icon on it." << endl;
    if (ask("Do you want to continue? ")) {
        triggerStackOverflow(137);
    }
}

/* Returns a sentinel document that indicates failure. */
DocumentInfo sentinelDoc() {
    return { -1, -1, -1 };
}

/**
 * Given a line constisting of a single string followed by a number,
 * extracts that number.
 */
void extractSecond(string line, int& dest) {
    istringstream extractor(line);

    /* Pull off the first part, then extract the second. */
    string dummy;
    extractor >> dummy >> dest;
}

/**
 * Looks for an analyzed version of a file. If it can find it, reports statistics
 * gathered from that file. If not, returns a sentinel DocumentInfo indicating
 * failure.
 */
DocumentInfo referenceFor(string filename) {
    ifstream refFile(filename + ".analyzed");

    DocumentInfo result = sentinelDoc();
    for (string line; getline(refFile, line); ) {
        if (startsWith(line, "Sentences:")) {
            extractSecond(line, result.numSentences);
        } else if (startsWith(line, "Words:")) {
            extractSecond(line, result.numWords);
        } else if (startsWith(line, "Syllables:")) {
            extractSecond(line, result.numSyllables);
        }
    }

    return (result.numWords != -1 &&
            result.numSentences != -1 &&
            result.numSyllables != -1)? result : sentinelDoc();
}

/* Reports a number as compared against our reference solution. */
void reportStat(int studentVal, int ourVal, string label) {
    if (ourVal == -1 || studentVal == ourVal) {
        cout << "  " << label << ": " << studentVal << endl;
    } else {
        cerr << "  " << label << ": " << studentVal << " (we got " << ourVal << ")" << endl;
    }
}

/* Computes and displays the Flesch-Kincaid grade level for a
 * piece of text given its statistics.
 */
void showLevelFor(DocumentInfo stats) {
    static const double C_0 = -15.59;
    static const double C_1 =   0.39;
    static const double C_2 =  11.80;

    double gradeLevel = C_0 +
                        C_1 * stats.numWords / stats.numSentences +
                        C_2 * stats.numSyllables / stats.numWords;

    cout << "Flesch-Kincaid Grade Level: " << gradeLevel << endl;
    cout << endl;
}

/* Given a file stream and the name of a file, compares your
 * implementation of statisticsFor against the reference and
 * lets you know how you did!
 */
void reportStatsOnFile(istream& source, string filename) {
    DocumentInfo studentAnswer = statisticsFor(source);
    DocumentInfo ourAnswer     = referenceFor(filename);

    cout << "Statistics for file " << getTail(filename) << ":" << endl;
    reportStat(studentAnswer.numSentences, ourAnswer.numSentences, "Sentences");
    reportStat(studentAnswer.numWords, ourAnswer.numWords, "Words");
    reportStat(studentAnswer.numSyllables, ourAnswer.numSyllables, "Syllables");

    showLevelFor(studentAnswer);
}

/* Given a string of text, runs your statisticsFor function and
 * reports the statistics you computed.
 */
void reportStatsOnString(string text) {
    /* Wrap the text in an istringstream, a stream object that
     * reads from a text string rather than a file.
     */
    istringstream stream(text);
    DocumentInfo stats = statisticsFor(stream);

    cout << "Statistics for direct input:" << endl;
    cout << "  Sentences: " << stats.numSentences << endl;
    cout << "  Words:     " << stats.numWords << endl;
    cout << "  Syllables: " << stats.numSyllables << endl;
    showLevelFor(stats);
}

/* Reports whether a filename is likely a text file. Text files either
 * end in .txt or have no suffix.
 */
bool isLikelyTextFile(string filename) {
    string tail = getTail(filename);
    return tail.find('.') == string::npos ||
           tail.substr(tail.find('.')) == ".txt";
}

/* Warns a student that a file doesn't look like a text file and asks
 * them whether they want to proceed.
 */
bool studentAcceptsRisk() {
    cout << "You've chosen a file that doesn't seem to be a text file." << endl;
    cout << "Text files typically end with the .txt suffix." << endl;
    cout << "You may get unusual results running your code on this file." << endl;
    return ask("Do you still want to proceed? ");
}

/*
 * This function tests your Flesch-Kincaid function on a file
 * chosen from dish.
 */
void test_fleschKincaidFile() {
    do {
        while (true) {
            ifstream input;
            string filename = promptUserForFile(input, "Enter name of file to analyze: ");

            /* Make sure this isn't a garbage file. */
            if (isLikelyTextFile(filename) || studentAcceptsRisk()) {
                reportStatsOnFile(input, filename);
                break;
            }
        }
    } while (ask("Read another file?"));
}

/*
 * Reads a block of text from the user. The text is read until
 * a blank line is entered.
 */
string getParagraphText() {
    cout << endl;
    cout << "Enter some text in the space below. Anything you enter" << endl;
    cout << "will be sent to the statisticsFor function. When you're" << endl;
    cout << "done entering things, enter a blank line." << endl;

    string accumulatedText;
    while (true) {
        string line = getLine();
        if (line.empty()) return accumulatedText;

        /* Append what we just read. */
        accumulatedText += line + '\n';
    }
}

/*
 * Prompts the user for a string, then scores it.
 */
void scoreOneString() {
    reportStatsOnString(getParagraphText());
}

/*
 * This function tests your Flesch-Kincaid function on input that's
 * directly provided by the user.
 */
void test_fleschKincaidDirect() {
    do {
        scoreOneString();
    } while (ask("Score another piece of text?"));
}

/*
 * This function asks the user with a yes/no prompt and returns the answer.
 */
bool ask(string prompt) {
    while (true) {
        string answer = toLowerCase(getLine(prompt + " (Y/n): "));
        if (answer.length() == 0 || answer.at(0) == 'y') {
            return true;
        } else if (answer.at(0) == 'n') {
            return false;
        } else {
            cout << "Invalid answer. Please answer either \"y\" or \"n\"" << endl;
        }
    }
}
