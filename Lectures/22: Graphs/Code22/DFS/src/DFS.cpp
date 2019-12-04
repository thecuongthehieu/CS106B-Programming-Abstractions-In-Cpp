/*****************************************************
 * File: DFS.cpp
 *
 * A program to play around with depth-first search!
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "map.h"
#include "set.h"
#include "console.h"
#include "simpio.h"
#include <fstream>
using namespace std;

/**
 * Loads the Word Ladder graph from disk.
 *
 * @return The graph structure from Word Ladders.
 * @throws ErrorException If the data can't be read.
 */
Map<string, Set<string>> wordLadderGraph() {
    ifstream input("word-graph.txt");

    /* Pull the map from disk. How nice! How elegant! */
    Map<string, Set<string>> graph;
    input >> graph;

    /* Remove self-loops. */
    for (string word: graph) {
        graph[word] -= word;
    }

    if (!input) error("Couldn't read graph.");
    return graph;
}

/* Runs a depth-first search from the specified word. */
void dfsFrom(const Map<string, Set<string>>& graph, const string& word, Set<string>& visited) {
    /* If we've already seen this word, we're done. */
    if (visited.contains(word)) return;

    /* This is the first time we've seen this word! Record it as such. */
    visited.add(word);
    cout << word << "  "; ////Process NODE

    /* Visit all neighbors. */
    for (string next: graph[word]) {
        dfsFrom(graph, next, visited);
    }
}

/* Runs a DFS from the specified word, printing all the words reachable from it. */
void dfs(const Map<string, Set<string>>& graph, const string& word) {
    Set<string> visited;
    dfsFrom(graph, word, visited);
    cout << endl;
}

int main() {
    Map<string, Set<string>> graph = wordLadderGraph();

    while (true) {
        string word = getLine("Enter a word: ");
        if (graph.containsKey(word)) {
            dfs(graph, word);
        } else {
            cerr << "Sorry, I don't know that word." << endl;
        }
    }

    return 0;
}
