/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
#include "lexicon.h"
#include "random.h"


using namespace std;

int gcd(int a, int b) {
    // your code here
    cout << "gcd(" << a << ", " << b << ")";
    if (b == 0) {
        cout << " = " << a << endl;
        return a;
    }
    else {
        cout << " = " << "gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a % b);
    }
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    // your code here
    //cout << "[recursion serpinskii called]" << endl;
    if (order == 0)
        return;
    else if (order == 1) {
        w.drawLine(leftX, leftY, leftX + size, leftY);
        w.drawLine(leftX + size, leftY, leftX + size / 2, leftY + size * sqrt(3) / 2);
        w.drawLine(leftX + size / 2, leftY + size * sqrt(3) / 2, leftX, leftY);
        return;
    } else {
        serpinskii(w, leftX, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 2, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 4, leftY + size * sqrt(3) / 4, size / 2, order -1 );
    }
}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    // your code here
    //cout << "[recursion flood fill called]" << endl;
    int coloredNum = 0;
    int currentColor = image.getRGB(x, y);
    if (currentColor == newColor)
        return 0;
    else {
        coloredNum += 1;
        int width = image.getWidth();
        int height = image.getHeight();
        image.setRGB(x, y, newColor);
        if (x > 0)
            if (image.getRGB(x - 1, y) == currentColor)
                coloredNum += floodFill(image, x - 1, y, newColor);
        if (x < width)
            if (image.getRGB(x + 1, y) == currentColor)
                coloredNum += floodFill(image, x + 1, y, newColor);
        if (y > 0)
            if (image.getRGB(x, y - 1) == currentColor)
                coloredNum += floodFill(image, x, y - 1, newColor);
        if (y < height)
            if (image.getRGB(x, y + 1) == currentColor)
                coloredNum += floodFill(image, x, y + 1, newColor);
    }
    return coloredNum;
}


Map<string, int> isPrinted;

void printPaths (const Map<string, Vector<string> >& prereqMap,const string& goal) {
    if (prereqMap.containsKey(goal)) {
        for (string word : prereqMap[goal]) {
            if (!isPrinted.containsKey(goal))
                printPaths(prereqMap, word);
        }
    }
    if (!isPrinted.containsKey(goal)) {
        cout << goal << endl;
        isPrinted[goal] = 1;
    }
}

void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    // your code here
    //cout << "[recursion personal curriculum called]" << endl;
    Map<string, int> clearedMap;
    isPrinted = clearedMap;
    printPaths(prereqMap, goal);
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    // your code here
    //cout << "[recursion generate called]" << endl;
    string expansion = "";
    int choose = randomInteger(0, grammar[symbol].size() - 1);

    TokenScanner scanner(grammar[symbol][choose]);
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (!grammar.containsKey(token))
            expansion += token;
        else
            expansion += generate(grammar, token);
    }

    return expansion;
}
