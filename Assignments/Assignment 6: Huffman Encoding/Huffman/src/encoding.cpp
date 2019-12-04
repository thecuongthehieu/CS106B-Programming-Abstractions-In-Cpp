// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include "bitstream.h"
#include "filelib.h"

// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    Map<int, int> freqTable;   // this is just a placeholder so it will compile
    char c;
    while (input.get(c)) {
        int intChar = c;
        freqTable[intChar] += 1;
    }
    freqTable[PSEUDO_EOF] = 1;

    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function
    PriorityQueue<HuffmanNode*> pQueue;
    for (int i = 0; i < freqTable.keys().size(); ++i) {
        HuffmanNode* newNode = new HuffmanNode(freqTable.keys()[i], freqTable[freqTable.keys()[i]], NULL, NULL);
        pQueue.enqueue(newNode, newNode->count);
    }

    HuffmanNode* root;
    while (!pQueue.isEmpty()) {
        HuffmanNode* leftChild = pQueue.dequeue();
        if (pQueue.isEmpty()) {
            root = leftChild;
            break;
        }
        HuffmanNode* rightChild = pQueue.dequeue();
        HuffmanNode* newNode = new HuffmanNode(NOT_A_CHAR, leftChild->count + rightChild->count, leftChild, rightChild);
        root = newNode;
        pQueue.enqueue(root, root->count);
    }

    return root;   // this is just a placeholder so it will compile
}

void traverseTree(const HuffmanNode* encodingTree, Map<int, string>& encodingMap,const string& code) {
    //Traverse encodingTree recursively

    if (encodingTree == NULL)
        return;
    if (encodingTree->isLeaf()) {
        encodingMap[encodingTree->character] = code;
    } else {
        traverseTree(encodingTree->zero, encodingMap, code + "0");
        traverseTree(encodingTree->one, encodingMap, code + "1");
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    traverseTree(encodingTree, encodingMap, ""); //
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
    char c;
    while (input.get(c)) {
        int intChar = c;
        string code = encodingMap[intChar];
        for (char bit : code) {
            if (bit == '0')
                output.writeBit(0);
            else
                output.writeBit(1);
        }
    }
    string eofCode = encodingMap[PSEUDO_EOF];
    for (char bit : eofCode) {
        if (bit == '0')
            output.writeBit(0);
        else
            output.writeBit(1);
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
    int bit = input.readBit();
    HuffmanNode* root = encodingTree;
    while (bit != -1) {
        if (bit == 0)
            root = root->zero;
        else
            root = root->one;
        if (root->isLeaf()) {
            int intChar = root->character;
            if (intChar != PSEUDO_EOF) {
                output.put(intChar);
            }
            root = encodingTree;
        }
        bit = input.readBit();
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    Map<int, int> frequencyTable = buildFrequencyTable(input);
    output << frequencyTable;
    rewindStream(input);

    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    Map<int, int> frequencyTable;
    input >> frequencyTable;
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if (node != NULL) {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
