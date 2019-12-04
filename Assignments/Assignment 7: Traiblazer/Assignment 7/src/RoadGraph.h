/*
 * CS 106B Trailblazer
 * This file declares the graph type used in trailblazer
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Chris Piech, Keith Schwarz
 * @version 2017/03/09 (updated version for Win17)
 */

#pragma once

#include "set.h"
#include "graph.h"
#include "point.h"
#include "observable.h"
#include "Color.h"
#include <string>

/* Forward declarations of the relevant types so that RoadNode can reference RoadEdge
 * and vice-versa.
 */
class RoadNode;
class RoadEdge;

class RoadNode: public Observable<Color> {
public:
    /* Constructs a new RoadNode with the given name that appears at the given location
     * on the screen.
     */
    RoadNode(const std::string& name, const Point& location);

    /* Returns the name of this node, for debugging purposes. */
    std::string nodeName() const;

    /* Returns the set of all edges leaving this node. */
    Set<RoadEdge*> outgoingEdges() const;

    /* Changes the color of this node in the display. Note that the color information is not
     * actually stored anywhere in the node; this is just for display purposes.
     */
    void setColor(Color c);

    /* Returns the location, on screen, where the point is. You should not need to use this
     * function, since the node's on-screen location has no bearing on the lengths of the
     * edges reaching it.
     */
    Point location() const;

    /* Returns a human-readable string describing this node. */
    std::string toString() const;

private:
    /* The Graph and RoadGraph classes need to be able to read and write
     * internal state. The friend keyword allows them to do this.
     */
    friend class Graph<RoadNode, RoadEdge>;
    friend class RoadGraph;

    /* The Graph class expects a no-argument constructor, so we provide the default. */
    RoadNode() = default;

    std::string name;
    Point myLocation;
    Set<RoadEdge*> arcs;
};

class RoadEdge {
public:
    /* Constructs a new edge from the start node to the destination node that has the
     * given cost.
     */
    RoadEdge(RoadNode* start, RoadNode* finish, double edgeCost);

    /* Returns the node at which this edge begins. */
    RoadNode* from() const;

    /* Returns the node at which this edge ends. */
    RoadNode* to()   const;

    /* Returns the cost of this edge. */
    double cost() const;

    /* Returns a human-readable representation of this edge. */
    std::string toString() const;

private:
    /* The Graph and RoadGraph classes need to be able to read and write
     * internal state. The friend keyword allows them to do this.
     */
    friend class Graph<RoadNode, RoadEdge>;
    friend class RoadGraph;

    /* The Graph class expects a no-arg constructor, so we provide one. */
    RoadEdge() = default;

    RoadNode* start = nullptr;
    RoadNode* finish = nullptr;
    double edgeCost;
};

class RoadGraph {
public:
    /*
     * Makes a new RoadGraph based on BasicGraph data
     */
    explicit RoadGraph(Graph<RoadNode, RoadEdge>* data);

    /*
     * Returns all of the verticies that can be reached by a
     * a direct path from v.
     */
    Set<RoadNode *> neighborsOf(RoadNode* v) const;

    /*
     * Returns a pointer to the edge that connects start to end
     */
    RoadEdge* edgeBetween(RoadNode* start, RoadNode* end) const;

    /*
     * Returns the maximum speed of any edge on the road graph.
     */
    double maxRoadSpeed() const;

    /*
     * The geodesic distance between the two nodes. This is the
     * distance that a crow would travel if it flew from start to
     * end. Units are not standarized, but are consistent within
     * a graph.
     */
    double crowFlyDistanceBetween(RoadNode* start, RoadNode* end) const;

private:
    // underlying data
    Graph<RoadNode, RoadEdge>* data;

    // the saved max rate of the graph
    mutable bool maxRateCached = false;
    mutable double maxRate = 0.0;
};
