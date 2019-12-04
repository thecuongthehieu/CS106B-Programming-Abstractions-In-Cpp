/*
 * CS 106B Trailblazer
 * This file contains implementations of the members of the WorldDisplay class.
 * See WorldDisplay.h for declarations and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Chris Piech, Marty Stepp, Keith Schwarz, et al
 * @version 2017/03/09 (updated version for Win17)
 */

#include "WorldDisplay.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "filelib.h"
#include "gmath.h"
#include "strlib.h"

/* Private constants and helper functions needed only in this file. */
namespace {
    /* constants for vertex/edge colors, sizes, thickness, fonts, etc. */
    const std::string COLOR_BACKGROUND_STR("Black");
    const std::string COLOR_HOVER_STR("#bbbb00");
    const std::string COLOR_PATH_STR("Red");
    const std::string COLOR_SELECTION_STR("Red");
    const int COLOR_BACKGROUND = 0x0;
    const int COLOR_HOVER = 0xbbbb00;
    const int COLOR_PATH = 0xff0000;
    const int COLOR_SELECTION = 0xff0000;

    const std::string EDGE_COLOR("#888888");
    const double VERTEX_RADIUS = 8;
    const double VERTEX_RADIUS_LARGE_MAP = 3;
    const double EDGE_LINE_WIDTH = 1;
    const double VERTEX_LINE_WIDTH = 2;
    const std::string VERTEX_FILL_COLOR("White");
    const std::string VERTEX_FILL_COLOR_HIGHLIGHTED("Red");
    const std::string LABEL_FONT_NAME = "SansSerif";
    const int LABEL_FONT_SIZE = 11;
    const std::string LABEL_FONT_STRING = LABEL_FONT_NAME + "-" + integerToString(LABEL_FONT_SIZE);

    const double PATH_LINE_WIDTH = 3.0;

    void polarMove(double x, double y, double r, double theta, double& newX, double& newY) {
        double dx = std::cos(theta) * r;
        double dy = std::sin(theta) * -r;
        newX = x + dx;
        newY = y - dy;
    }

    /* Reads files from the stream until a non-empty, non-comment line is read. */
    bool getMeaningfulLine(std::istream& input, std::string& line) {
        std::string lineOut;
        while (getline(input, lineOut)) {
            trimInPlace(lineOut);
            if (!lineOut.empty() && lineOut[0] != '#') {
                line = lineOut;
                return true;
            }
        }
        return false;
    }
}

const int WorldDisplay::WINDOW_MARGIN = 5;

/* Private helper functions and constants */
WorldDisplay::WorldDisplay(GWindow* gwnd)
    : gwnd(gwnd),
      windowWidth(0),
      windowHeight(0),
      graph(nullptr),
      selectedStart(nullptr),
      selectedEnd(nullptr),
      backgroundImage(nullptr) {
    largeMapDisplay = true;
    windowWidth = gwnd->getWidth() - 2 * WINDOW_MARGIN;
    windowHeight = gwnd->getHeight() - 2 * WINDOW_MARGIN;
}

WorldDisplay::~WorldDisplay() {
    clearSelection(false);
    clearPath(false);
    
    delete backgroundImage;
    delete graph;
}

void WorldDisplay::clearPath(bool redraw) {
    for (GLine* line : highlightedPath) {
        gwnd->remove(line);
        delete line;
    }
    highlightedPath.clear();

    if (redraw) {
        draw();
    }
}

void WorldDisplay::clearSelection(bool redraw) {
    setSelectedStart(nullptr);
    setSelectedEnd(nullptr);
    if (redraw) {
        draw();
    }
}

Graph<RoadNode, RoadEdge>* WorldDisplay::getGraph() const {
    return graph;
}

const GDimension& WorldDisplay::getPreferredSize() const {
    return preferredSize;
}

RoadNode* WorldDisplay::getSelectedStart() const {
    return selectedStart;
}

RoadNode* WorldDisplay::getSelectedEnd() const {
    return selectedEnd;
}

bool WorldDisplay::read(const std::string& filename) {
    std::ifstream input;
    input.open(filename.c_str());
    if (input.fail()) {
        return false;
    }
    return read(input);
}

void WorldDisplay::setSelectedStart(RoadNode* v) {
    selectedStart = v;
}

void WorldDisplay::setSelectedEnd(RoadNode* v) {
    selectedEnd = v;
}

void WorldDisplay::drawEdgeArrow(RoadEdge* e) const {
    Point p1 = e->from()->location();
    Point p2 = e->to()->location();
    double p1x = p1.getX();
    double p1y = p1.getY();
    double p2x = p2.getX();
    double p2y = p2.getY();
    
    // shift the line's endpoints inward a bit to the edges of the ovals
    double dy = p2y - p1y;
    double dx = p2x - p1x;
    double theta = std::atan2(dy, dx);
    double r = getNodeRadius() + VERTEX_LINE_WIDTH;
    polarMove(p1x, p1y, r, theta, p1x, p1y);        // start
    polarMove(p2x, p2y, r, theta - PI, p2x, p2y);   // end
    
    GLine line(p1x, p1y, p2x, p2y);
    line.setColor(EDGE_COLOR);
    line.setLineWidth(EDGE_LINE_WIDTH);
    gwnd->draw(&line);
    
    // draw edge weight in middle
    if (!largeMapDisplay && (e->cost() >= 0.00000001 || e->cost() < -0.00000001)) {
        double midx = p1x + (p2x - p1x) / 2;
        double midy = p1y + (p2y - p1y) / 2;
        GLabel weightLabel(realToString(e->cost()), midx, midy);
        weightLabel.setFont(LABEL_FONT_STRING);
        weightLabel.setColor(EDGE_COLOR);
        gwnd->draw(&weightLabel);
    }

    // don't draw the arrow head on large maps (goes out of bounds)
    if(largeMapDisplay) return;
    
    // draw arrowhead (arrow flails separated by 20 degrees)
    bool CLOSED_ARROWHEAD = true;
    double ARROWHEAD_LENGTH = 6;
    double ARROWHEAD_ANGLE = PI / 8.0;
    double backward = std::atan2(-dy, -dx);

    // polar to cartesian: x is cos, y is sin
    double backLX, backLY, backRX, backRY;
    polarMove(p2x, p2y, ARROWHEAD_LENGTH, backward + ARROWHEAD_ANGLE, backLX, backLY);
    polarMove(p2x, p2y, ARROWHEAD_LENGTH, backward - ARROWHEAD_ANGLE, backRX, backRY);

    if (CLOSED_ARROWHEAD) {
        GPolygon arrowhead;
        arrowhead.addVertex(p2x, p2y);
        arrowhead.addEdge(backLX - p2x, backLY - p2y);
        arrowhead.addEdge(backRX - backLX, backRY - backLY);
        arrowhead.setLineWidth(EDGE_LINE_WIDTH);
        arrowhead.setColor(EDGE_COLOR);
        arrowhead.setFilled(true);
        arrowhead.setFillColor(EDGE_COLOR);
        gwnd->draw(&arrowhead);
    } else {
        GLine arrowheadLine1(p2x, p2y, backLX, backLY);
        arrowheadLine1.setColor(EDGE_COLOR);
        arrowheadLine1.setLineWidth(EDGE_LINE_WIDTH);
        gwnd->draw(&arrowheadLine1);

        GLine arrowheadLine2(p2x, p2y, backRX, backRY);
        arrowheadLine2.setColor(EDGE_COLOR);
        arrowheadLine2.setLineWidth(EDGE_LINE_WIDTH);
        gwnd->draw(&arrowheadLine2);
    }
}

void WorldDisplay::drawVertexCircle(RoadNode* v, std::string color, bool fill) {
    Point p = v->location();
    double vertexR = getNodeRadius();
    GOval oval(p.getX() - vertexR,
               p.getY() - vertexR,
               2 * vertexR, 2 * vertexR);
    oval.setLineWidth(VERTEX_LINE_WIDTH);
    oval.setFilled(fill);
    if (v == selectedStart || v == selectedEnd) {
        oval.setColor(COLOR_SELECTION_STR);
    }
    
    if (fill) {
        oval.setFillColor(color);
    } else {
        oval.setColor(color);
    }
    gwnd->draw(&oval);
}

void WorldDisplay::draw() {
    bool before = gwnd->isRepaintImmediately();
    gwnd->setRepaintImmediately(false);
    if (backgroundImage) {
        gwnd->draw(backgroundImage);
    }

    for (auto* e : graph->getArcSet()) {
        drawEdgeArrow(e);
    }

    for (auto* v : *graph) {
        // draw oval for vertex
        drawVertexCircle(v, VERTEX_FILL_COLOR);
        
        // draw text label of vertex name
        if(!largeMapDisplay) {
            Point p = v->location();
            GLabel label(v->nodeName(),
                         p.getX() + getNodeRadius() + 2,
                         p.getY() + getNodeRadius());
            label.setFont(LABEL_FONT_STRING);
            gwnd->draw(&label);
        }
    }
    gwnd->setRepaintImmediately(before);
    gwnd->repaint();
}

void WorldDisplay::drawPath(Vector<RoadNode*>& path, std::string color) {
    bool before = gwnd->isRepaintImmediately();
    gwnd->setRepaintImmediately(false);
    for (int i = 1; i < path.size(); i++) {
        // highlight connection between path[i - 1] and path[i]
        Point p1 = path[i - 1]->location();
        Point p2 = path[i]->location();
        GLine* connection = new GLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
        connection->setColor(color);
        connection->setLineWidth(PATH_LINE_WIDTH);
        gwnd->add(connection);
        highlightedPath.add(connection);
    }
    gwnd->repaint();
    gwnd->setRepaintImmediately(before);
}

std::string WorldDisplay::getDescription(double x, double y) const {
    std::ostringstream out;
    out << "(" << (int) x << "," << (int) y << ")";
    return out.str();
}

double WorldDisplay::getNodeRadius() const {
    if(largeMapDisplay) {
        return VERTEX_RADIUS_LARGE_MAP;
    }
    return VERTEX_RADIUS;
}

std::string WorldDisplay::getType() const {
    return "map";
}

RoadNode* WorldDisplay::getVertex(double x, double y) const {
    for (auto* v : *graph) {
        Point p = v->location();
        GOval oval(p.getX() - VERTEX_RADIUS,
                   p.getY() - VERTEX_RADIUS,
                   2 * VERTEX_RADIUS, 2 * VERTEX_RADIUS);
        if (oval.contains(x, y)) {
            return v;
        }
    }
    return nullptr;
}

void WorldDisplay::handleClick(double x, double y) {
    // figure out what vertex was clicked
    RoadNode* v = getVertex(x, y);
    if (!v) {
        return;
    }

    if (!selectedStart) {
        selectedStart = v;
        std::cout << "Start location: " << v->nodeName() << std::endl;
        drawVertexCircle(v, COLOR_SELECTION_STR, /* fill */ false);
        gwnd->repaint(); // Necessary if speed slider is cranked all the way down
    } else if (!selectedEnd) {
        selectedEnd = v;
        std::cout << "End location: " << v->nodeName() << std::endl;
        drawVertexCircle(v, COLOR_SELECTION_STR, /* fill */ false);
        gwnd->repaint(); // Necessary if speed slider is cranked all the way down
        
        // both click vertices are ready now, so notify GUI
        // so that it can do its path search
        notifyObservers(UIEvent::PATH_SELECTION_READY);
    } else {
        clearSelection(false);
        clearPath(true);
        selectedStart = v;
        std::cout << "Start location: " << v->nodeName() << std::endl;
        drawVertexCircle(v, COLOR_SELECTION_STR, /* fill */ false);
        gwnd->repaint(); // Necessary if speed slider is cranked all the way down
    }
}

bool WorldDisplay::read(std::istream& input) {
    if (graph) {
        delete graph;
    }
    graph = new Graph<RoadNode, RoadEdge>();
    largeMapDisplay = false;
    
    std::string line;
    if (!getMeaningfulLine(input, line)) {   // "FLAGS or IMAGE"
        std::cerr << "Invalid input file; file is empty" << std::endl;
        return false;
    }
    if(line == "FLAGS") {
        std::string flagLine;
        while (true) {
            if(!getMeaningfulLine(input, flagLine)) {
                std::cerr << "Invalid input file; missing \"IMAGE\" header" << std::endl;
                return false;
            }
            if(flagLine == "IMAGE") break;
            Vector<std::string> parts = stringSplit(flagLine, "=");
            if(parts[0] == "largeMapDisplay") {
                largeMapDisplay = parts[1] == "true";
            }
        }
    }


    std::string imageFile;
    if (!getMeaningfulLine(input, imageFile)) {
        std::cerr << "Invalid input file; missing image file name" << std::endl;
        return false;
    }
    if (!fileExists(imageFile)) {
        std::cerr << "Invalid input file; specified image file \""
                  << imageFile << "\" does not exist" << std::endl;
        return false;
    }
    backgroundImage = new GImage(imageFile);
    
    int width = 0;
    if (!getMeaningfulLine(input, line)) {
        std::cerr << "Invalid input file; missing width" << std::endl;
        return false;
    }
    if (!stringIsInteger(line)) {
        std::cerr << "Invalid input file; non-integer width \""
                  << line << "\"" << std::endl;
        return false;
    }
    width = stringToInteger(line);
    
    int height = 0;
    if (!getMeaningfulLine(input, line)) {
        std::cerr << "Invalid input file; missing height" << std::endl;
        return false;
    }
    if (!stringIsInteger(line)) {
        std::cerr << "Invalid input file; non-integer height \""
                  << line << "\"" << std::endl;
        return false;
    }
    height = stringToInteger(line);
    preferredSize = GDimension(width, height);
    windowWidth = width;
    windowHeight = height;
    
    getline(input, line);  // VERTICES
    while (getMeaningfulLine(input, line)) {
        // "Hobbiton;147;86"
        std::vector<std::string> tokens = stringSplit(line, ";");
        if (tokens.size() >= 1 && (tokens[0] == "ARCS" || tokens[0] == "EDGES")) {
            break;
        } else if (tokens.size() < 3) {
            continue;
        }
        
        std::string name = trim(tokens[0]);
        if (graph->containsNode(name)) {
            std::cerr << "Invalid input file; duplicate vertex \""
                      << name << "\"" << std::endl;
            return false;
        }
        
        if (!stringIsInteger(tokens[1]) || !stringIsInteger(tokens[2])) {
            std::cerr << "Invalid input file; non-integer coordinates for vertex \""
                      << name << "\"" << std::endl;
            return false;
        }
        int vertexX = stringToInteger(tokens[1]);
        int vertexY = stringToInteger(tokens[2]);
        if (vertexX < 0 || vertexY < 0) {
            std::cerr << "Invalid input file; negative coordinates for vertex \""
                      << name << "\"" << std::endl;
            return false;
        }

        RoadNode* node = new RoadNode(name, {vertexX, vertexY});
        node->addObserver(this);
        graph->addNode(node);
    }
    
    while (getMeaningfulLine(input, line)) {
        // "Hobbiton;Southfarthing;1"
        std::vector<std::string> tokens = stringSplit(line, ";");
        if (tokens.size() < 3) {
            break;
        }
        std::string name1 = trim(tokens[0]);
        std::string name2 = trim(tokens[1]);
        
        if (!graph->containsNode(name1)) {
            std::cerr << "Invalid input file; when reading edge between \""
                      << name1 << "\" and \"" << name2
                      << "\", graph does not contain a vertex named \""
                      << name1 << "\"" << std::endl;
            return false;
        }
        if (!graph->containsNode(name2)) {
            std::cerr << "Invalid input file; when reading edge between \""
                      << name1 << "\" and \"" << name2
                      << "\", graph does not contain a vertex named \""
                      << name2 << "\"" << std::endl;
            return false;
        }
        
        if (!stringIsReal(tokens[2])) {
            std::cerr << "Invalid input file; non-numeric weight for edge between \""
                      << name1 << "\" and \"" << name2 << "\"" << std::endl;
            return false;
        }
        
        double weight = stringToReal(tokens[2]);
        if (weight < 0) {
            std::cerr << "Invalid input file; negative weight for edge between \""
                      << name1 << "\" and \"" << name2 << "\"" << std::endl;
            return false;
        }



        // edges are undirected (both ways) by default
        bool directed = false;
        if (tokens.size() >= 4 && stringIsBool(tokens[3])) {
            directed = stringToBool(tokens[3]);
        }

        /* Add the forward edge. */
        RoadEdge* edge = new RoadEdge(graph->getNode(name1), graph->getNode(name2), weight);
        graph->addArc(edge);

        /* The graph might be undirected, in which case we should add the reverse edge as
         * well.
         */
        if (!directed) {
            RoadEdge* revEdge = new RoadEdge(graph->getNode(name2), graph->getNode(name1), weight);
            graph->addArc(revEdge);
        }
    }


    return true;
}

int WorldDisplay::numGreenNodes() const {
    return greenNodes.size();
}

int WorldDisplay::numYellowNodes() const {
    return yellowNodes.size();
}

void WorldDisplay::resetState() {
    yellowNodes.clear();
    greenNodes.clear();
}

void WorldDisplay::update(Observable<Color>* obs, const Color& c) {
    auto* v = static_cast<RoadNode*>(obs);

    int r, g, b;
    colorToRGB(c, r, g, b);
    std::string color = rgbToColor(r, g, b);
    drawVertexCircle(v, color);

    /* Record the color for posterity.
     *
     * TODO: There has to be a cleaner way to do this!
     */
    yellowNodes.remove(v);
    greenNodes.remove(v);
    if (c == Color::YELLOW) yellowNodes.add(v);
    if (c == Color::GREEN) greenNodes.add(v);

    /* Don't notify the observers if a node is colored gray. The observers
     * are only notified in cases where the animation delay should be put into
     * effect, and no (correct) implementation of these algorithms ever does
     * this as part of routine processing.
     */
    if (c != Color::GRAY) notifyObservers(UIEvent::VERTEX_COLORED);
}
