/*
 * CS 106B Trailblazer
 * WorldDisplay is a class representing map-based types of world graphs
 * that draw an image background with circular vertices on top.
 * See WorldDisplay.cpp for implementation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Chris Piech, Marty Stepp, Keith Schwarz, et al
 * @version 2017/03/09 (initial version for Win17)
 */

#ifndef _WorldMap_h
#define _WorldMap_h

#include "gbufferedimage.h"
#include "gobjects.h"
#include "graph.h"
#include "Color.h"
#include "RoadGraph.h"
#include "hashset.h"
#include <string>
#include <fstream>

/* Enumerated type representing different events that the UI might need to respond to. */
enum class UIEvent {
    VERTEX_COLORED,
    PATH_SELECTION_READY
};

class WorldDisplay: public Observable<UIEvent>, public Observer<Color> {
public:
    /* px of margin around the window */
    static const int WINDOW_MARGIN;

    /*
     * Constructor; creates a new empty world on the given graphical window.
     */
    explicit WorldDisplay(GWindow* gwnd);

    /*
     * Destructor; frees the memory used by the world.
     */
    ~WorldDisplay();

    /*
     * Removes any lines from the screen indicating a searched-for path.
     * If redraw is true, also repaints the entire graph.
     */
    void clearPath(bool redraw = true);

    /*
     * Removes any shapes from the screen indicating a selected vertex.
     * If redraw is true, also repaints the entire graph.
     */
    void clearSelection(bool redraw = true);

    /*
     * Returns the graph that represents this world.
     */
    Graph<RoadNode, RoadEdge>* getGraph() const;

    /*
     * Returns the width/height in pixels that this graph would like to be.
     * Used to set the window's canvas size.
     */
    const GDimension& getPreferredSize() const;

    /*
     * Returns the ending vertex that is currently selected in the graph (NULL if none).
     */
    RoadNode* getSelectedEnd() const;

    /*
     * Returns the starting vertex that is currently selected in the graph (NULL if none).
     */
    RoadNode* getSelectedStart() const;

    /*
     * Sets the ending vertex that is currently selected in the graph
     * to the given vertex.
     */
    void setSelectedEnd(RoadNode* v);

    /*
     * Sets the starting vertex that is currently selected in the graph
     * to the given vertex.
     */
    void setSelectedStart(RoadNode* v);

    /*
     * Reads graph data from the given filename.
     * This method simply forwards to read(istream&).
     */
    bool read(const std::string& filename);
    
    /*
     * Draws this world on the screen.
     */
    void draw();

    /*
     * Draws the given path on the screen.
     */
    void drawPath(Vector<RoadNode*>& path, std::string color);

    /*
     * Returns a description of this type of world, such as "two-dimensional mazes".
     */
    std::string getDescription(double x, double y) const;

    /*
     * Returns a description of this type of world, such as "maze" or "map".
     */
    std::string getType() const;

    /*
     * Called by the GUI when the user clicks on the graph.
     */
    void handleClick(double x, double y);

    /*
     * Tries to read a world file from the specified stream.  On success, returns
     * true and updates the input parameters to mark the type of the world and
     * the world contents.  On failure, returns false.
     */
    bool read(std::istream& input);

    /*
     * Updates the world in response to a node changing color.
     */
    void update(Observable<Color>* obs, const Color& c = Color());

    /*
     * Returns the number of yellow / green nodes in the world.
     */
    int numGreenNodes() const;
    int numYellowNodes() const;

    /*
     * Resets any internal algorithmic state tracked from one run to the next.
     */
    void resetState();

private:
    GWindow* gwnd;                    // graphical window for drawing graph
    double windowWidth;               // width/height to use for display
    double windowHeight;
    GDimension preferredSize;         // size graph would like to be
    Graph<RoadNode, RoadEdge>* graph; // the graph itself
    RoadNode* selectedStart;          // currently selected start/end vertices
    RoadNode* selectedEnd;            // from clicks (nullptr if none)
    Vector<GLine*> highlightedPath;   // highlighted path lines (empty if none)
    GImage* backgroundImage;          // background image to draw behind vertices
    bool largeMapDisplay;             // whether we're in "large map mode" or not.

    /* Nodes that are reported to be yellow or green. We store this information because
     * the nodes themselves do not and at the end of the run we need to report the sizes
     * of each set.
     */
    HashSet<RoadNode*> yellowNodes, greenNodes;

    /*
     * Draws the given edge as a line with arrowhead at the end.
     */
    void drawEdgeArrow(RoadEdge* e) const;

    /*
     * Draws the arrow head.
     */
    void drawArrowHead(RoadEdge* e) const;

    /*
     * Gets the radius of a node for the current graph
     */
    double getNodeRadius() const;
    
    /*
     * Draws the given vertex as a possibly filled circle of a given color.
     */
    void drawVertexCircle(RoadNode* v, std::string color, bool fill = true);
    
    /*
     * Maps from x/y positions on screen to vertices in the graph.
     */
    RoadNode* getVertex(double x, double y) const;
};

#endif // _WorldMap_h
