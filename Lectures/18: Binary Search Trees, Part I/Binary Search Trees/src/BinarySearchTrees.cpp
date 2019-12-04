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

/**
 * Given a pointer to the root of a binary search tree, returns whether the specified key
 * is present in that tree.
 *
 * @param root The root of the tree.
 * @param key The key to search for.
 * @return Whether the key is present in the tree.
 */
bool contains(Node* root, const string& key) {
    /* Base case: The empty tree contains nothing. */
    if (root == nullptr) return false;

    /* Recursive case: Decide how the key compares against the root of the tree and decide
     * whether to stop, go left, or go right.
     */
    if (root->value == key) return true;
    else if (key < root->value) return contains(root->left, key);
    else return contains(root->right, key);
}

/**
 * Inserts the specified value into the binary search tree, if it doesn't already exist.
 *
 * @param root The root of the tree, which may be modified to point to a new location if
 *             appropriate.
 * @param value The value to insert.
 */
void insert(Node*& root, const string& value) {
    /* Base case: Inserting into an empty tree conjures up a new node. */
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        root->left = root->right = nullptr;
    }
    /* Recursive cases: Decide whether to insert or the left or right subtrees. */
    else if (root->value < value) {
        insert(root->right, value);
    } else if (root->value > value) {
        insert(root->left, value);
    }
    /* Edge case: If the value is already present, we're done! */
    else /* root->value == value */ {
        // Do nothing!
    }
}

int main() {
    Node* root = nullptr;

    while (true) {
        string movie = getLine("Enter movie title: ");
        if (contains(root, movie)) {
            cout << "It's a contender!" << endl;
        } else {
            cout << "You don't understand! I could've had class!" << endl;
            insert(root, movie);
        }
    }

    /* TODO: Clean up the memory! We'll see how to do this on Monday of next week. */
	return 0;
}
