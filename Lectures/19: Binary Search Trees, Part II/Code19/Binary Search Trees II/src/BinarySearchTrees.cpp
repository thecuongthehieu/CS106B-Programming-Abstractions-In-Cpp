/*****************************************************
 * File: BinarySearchTrees.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include "set.h"
#include "vector.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
    string value;
    Node* left;
    Node* right;
};

/* Inserts a value into a BST. This is unmodified from Friday's lecture. */
void insert(Node*& root, const string& value) {
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        root->left = root->right = nullptr;
    } else if (root->value < value) {
        insert(root->right, value);
    } else if (root->value > value) {
        insert(root->left, value);
    } else /* root->value == value */ {
        // Do nothing!
    }
}

/* Recursively prints out all the values in the BST. */
void printTree(Node* root) {
    if (root == nullptr) return;

    printTree(root->left);
    cout << root->value << endl;
    printTree(root->right);
}

/* Prints all values in the BST that are within the specified range. */
void printBetween(Node* root, const string& low, const string& high) {
    if (root == nullptr) return;

    if (root->value >= low && root->value <= high) {
        printBetween(root->left, low, high);
        cout << root->value << endl;
        printBetween(root->right, low, high);
    } else if (root->value < low) {
        printBetween(root->right, low, high);
    } else if (root->value > high) {
        printBetween(root->left, low, high);
    }
}

/* Frees all memory allocated by this BST. */
void freeTree(Node* root) {
    if (root == nullptr) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

/* Creates and returns a BST of all the Executive Branch departments. */
Node* executiveDepartments() {
    Node* root = nullptr;
    insert(root, "State");
    insert(root, "Treasury");
    insert(root, "Justice");
    insert(root, "Interior");
    insert(root, "Agriculture");
    insert(root, "Commerce");
    insert(root, "Labor");
    insert(root, "Defense");
    insert(root, "Health and Human Services");
    insert(root, "Housing and Urban Development");
    insert(root, "Transportation");
    insert(root, "Energy");
    insert(root, "Education");
    insert(root, "Veterans Affairs");
    insert(root, "Homeland Security");
    return root;
}

int main() {
    Node* root = executiveDepartments();

    cout << "All the branches:" << endl;
    printTree(root);

    cout << "Just ones whose names are in a given range:" << endl;
    printBetween(root, "Efficient", "Inefficient");
    freeTree(root);

    return 0;
}
