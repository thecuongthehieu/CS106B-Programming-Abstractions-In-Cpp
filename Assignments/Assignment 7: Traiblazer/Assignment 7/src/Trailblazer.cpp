// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment
// This is assignment 7

#include "Trailblazer.h"
#include "Color.h"
#include "pqueue.h"

#include <queue>
#include <string>



using namespace std;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Path thePath;
    if (start == end) {
        start->setColor(Color::GREEN);
        thePath.add(start);
        return thePath;
    }

    queue<RoadNode*> NodeQueue;
    Set<string> checkNode;
    Map<RoadNode*, RoadNode*> parentPointers;
    bool hasPath = false;

    start->setColor(Color::YELLOW);
    checkNode += start->nodeName();
    NodeQueue.push(start);

    while (!NodeQueue.empty()) {
        RoadNode* Node = NodeQueue.front();
        NodeQueue.pop();
        Node->setColor(Color::GREEN);

        if (Node->nodeName() == end->nodeName()) {
            hasPath = true;
            break;
        }

        for (RoadEdge* Edge : Node->outgoingEdges()) {
            RoadNode* newNode = Edge->to();
            if (!checkNode.contains(newNode->nodeName())) {
                newNode->setColor(Color::YELLOW);
                checkNode += newNode->nodeName();
                parentPointers[newNode] = Node;
                NodeQueue.push(newNode);
            }
        }
    }

    if (hasPath) {
       RoadNode* node = end;
       while (node->nodeName() != start->nodeName()) {
           thePath.insert(0, node);
           node = parentPointers[node];
       }
       thePath.insert(0,node);
    }
    return thePath;
}

struct NoDe {
    RoadNode* roadNode;
    NoDe* parent;
};

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Path minPath;
    if (start == end) {
        start->setColor(Color::GREEN);
        minPath.add(start);
        return minPath;
    }

    PriorityQueue<NoDe*> pQueue;
    Set<string> checkNode;
    bool hasPath = false;
    start->setColor(Color::YELLOW);
    NoDe* initNode = new NoDe;
    initNode->roadNode = start;
    initNode->parent = nullptr;
    pQueue.enqueue(initNode, 0);

    NoDe* endNode;

    while (!pQueue.isEmpty()) {
        double currentDist = pQueue.peekPriority();
        NoDe* dequeueNode = pQueue.dequeue();
        dequeueNode->roadNode->setColor(Color::GREEN);
        checkNode += dequeueNode->roadNode->nodeName();
        if (dequeueNode->roadNode->nodeName() == end->nodeName()) {
            endNode = dequeueNode;
            hasPath = true;
            break;
        }
        for (RoadEdge* Edge : dequeueNode->roadNode->outgoingEdges()) {
            RoadNode* neighborNode = Edge->to();
            if (!checkNode.contains(neighborNode->nodeName())) {
                neighborNode->setColor(Color::YELLOW);
                NoDe* newNode = new NoDe;
                newNode->roadNode = neighborNode;
                newNode->parent = dequeueNode;
                double newDist = currentDist + Edge->cost();
                pQueue.enqueue(newNode, newDist);
            }
        }
    }
    if (hasPath = true) {
        NoDe* tmp = endNode;
        while (tmp->roadNode != start) {
            minPath.insert(0, tmp->roadNode);
            tmp = tmp->parent;
        }
        minPath.insert(0, start);
    }
    return minPath;

}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */

    Path minPath;
    if (start == end) {
        start->setColor(Color::GREEN);
        minPath.add(start);
        return minPath;
    }

    PriorityQueue<NoDe*> pQueue;
    Set<string> checkNode;
    bool hasPath = false;
    start->setColor(Color::YELLOW);
    NoDe* initNode = new NoDe;
    initNode->roadNode = start;
    initNode->parent = nullptr;
    double initDist = 0 + graph.crowFlyDistanceBetween(start, end) / graph.maxRoadSpeed();
    pQueue.enqueue(initNode, initDist);

    NoDe* endNode;

    while (!pQueue.isEmpty()) {
        double currentDist = pQueue.peekPriority();
        NoDe* dequeueNode = pQueue.dequeue();
        dequeueNode->roadNode->setColor(Color::GREEN);
        checkNode += dequeueNode->roadNode->nodeName();
        if (dequeueNode->roadNode->nodeName() == end->nodeName()) {
            endNode = dequeueNode;
            hasPath = true;
            break;
        }
        for (RoadEdge* Edge : dequeueNode->roadNode->outgoingEdges()) {
            RoadNode* neighborNode = Edge->to();
            if (!checkNode.contains(neighborNode->nodeName())) {
                neighborNode->setColor(Color::YELLOW);
                NoDe* newNode = new NoDe;
                newNode->roadNode = neighborNode;
                newNode->parent = dequeueNode;
                // remove heuristic value of old Node
                double newDist = currentDist - graph.crowFlyDistanceBetween(dequeueNode->roadNode, end) / graph.maxRoadSpeed();
                // uptdate heuristic value of newNode
                newDist = newDist + Edge->cost() + graph.crowFlyDistanceBetween(neighborNode, end) / graph.maxRoadSpeed();
                pQueue.enqueue(newNode, newDist);
            }
        }
    }
    if (hasPath) {
        NoDe* tmp = endNode;
        while (tmp->roadNode != start) {
            minPath.insert(0, tmp->roadNode);
            tmp = tmp->parent;
        }
        minPath.insert(0, start);
    }
    return minPath;
}

bool uniquenessCheck (Path alternativePath, Path minPath) {
    if (alternativePath.size() == 0)
        return false;
    else {
        int differNum = 0;
        for (int i = 0; i < alternativePath.size(); ++i) {
            bool check = false;
            for (int j = 0; j < minPath.size(); ++j)
                if (alternativePath[i] == minPath[j]) {
                    check = true;
                    break;
                }
            if (!check)
                ++differNum;
        }

        double uniqueNess = double(differNum) / alternativePath.size();
        if (uniqueNess >= 0.2)
            return true;

        return false;
    }
}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end, RoadEdge* exceptEdge) {
    // Find alternative minPath which doen's have exceptEdge
    Path minPath;
    if (start == end) {
        start->setColor(Color::GREEN);
        minPath.add(start);
        return minPath;
    }

    PriorityQueue<NoDe*> pQueue;
    Set<string> checkNode;
    bool hasPath = false;
    start->setColor(Color::YELLOW);
    NoDe* initNode = new NoDe;
    initNode->roadNode = start;
    initNode->parent = nullptr;
    double initDist = 0 + graph.crowFlyDistanceBetween(start, end) / graph.maxRoadSpeed();
    pQueue.enqueue(initNode, initDist);

    NoDe* endNode;

    while (!pQueue.isEmpty()) {
        double currentDist = pQueue.peekPriority();
        NoDe* dequeueNode = pQueue.dequeue();
        dequeueNode->roadNode->setColor(Color::GREEN);
        checkNode += dequeueNode->roadNode->nodeName();

        if (dequeueNode->roadNode == end) {
            endNode = dequeueNode;
            hasPath = true;
            break;
        }

        for (RoadEdge* Edge : dequeueNode->roadNode->outgoingEdges()) {
            if (Edge != exceptEdge) {
                RoadNode* neighborNode = Edge->to();
                if (!checkNode.contains(neighborNode->nodeName())) {
                    neighborNode->setColor(Color::YELLOW);
                    NoDe* newNode = new NoDe;
                    newNode->roadNode = neighborNode;
                    newNode->parent = dequeueNode;
                    // remove heuristic value of old Node
                    double newDist = currentDist - graph.crowFlyDistanceBetween(dequeueNode->roadNode, end) / graph.maxRoadSpeed();
                    // uptdate heuristic value of newNode
                    newDist = newDist + Edge->cost() + graph.crowFlyDistanceBetween(neighborNode, end) / graph.maxRoadSpeed();
                    pQueue.enqueue(newNode, newDist);
                }
            }
        }
    }

    if (hasPath) {
        NoDe* tmp = endNode;
        while (tmp->roadNode != start) {
            minPath.insert(0, tmp->roadNode);
            tmp = tmp->parent;
        }
        minPath.insert(0, start);
    }
    return minPath;
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Path minPath = aStar(graph, start, end);

    //cout << start->nodeName() << " " << end->nodeName();

    Path alternativePath;
    if (minPath.size() <= 1) {
        return alternativePath;
    }

    for (int i = 0; i < minPath.size() - 1; ++i) {
        RoadEdge* exceptEdge = graph.edgeBetween(minPath[i], minPath[i + 1]);

        Path needCheckPath = aStar(graph, start, end, exceptEdge);
        if (uniquenessCheck(needCheckPath, minPath)) {
            alternativePath = needCheckPath;
            break;
        }
    }

    return alternativePath;
}

