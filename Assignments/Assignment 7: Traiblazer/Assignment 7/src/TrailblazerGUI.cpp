/*
 * CS 106B Trailblazer
 * This file implements functions to perform drawing in the graphical user
 * interface (GUI).
 * See TrailblazerGUI.h for documentation of each public function.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Chris Piech, Marty Stepp, Keith Schwarz
 * @version 2016/03/09 (updated version for Win17)
 */

#include "TrailblazerGUI.h"
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "error.h"
#include "filelib.h"
#include "gevents.h"
#include "gfilechooser.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gwindow.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "timer.h"
#include "vector.h"
#include "console.h"

#include "Trailblazer.h"
#include "WorldDisplay.h"

const int TrailblazerGUI::ANIMATION_DELAY_MIN = 0;
const int TrailblazerGUI::ANIMATION_DELAY_MAX = 2000;
const int TrailblazerGUI::ANIMATION_DELAY_DEFAULT = 200;

/* File-local constants, helper functions, etc. */
namespace {
    // various UI strings and settings
    const std::string GUI_STATE_FILE("trailblazer-gui-state.sav");
    const std::string OTHER_FILE_LABEL("Other file ...");

    const bool SHOULD_SAVE_GUI_STATE = true;
}

/*
 * Initializes state of the GUI subsystem.
 */
TrailblazerGUI::TrailblazerGUI(std::string windowTitle) {
    world = nullptr;
    animationDelay = 0;
    gtfPositionText = " ";
    
    int windowWidth = 800;
    int windowHeight = 600;

    gWindow = new GWindow(windowWidth, windowHeight);
    gWindow->setWindowTitle(windowTitle);
    gWindow->setExitOnClose(true);

    // Add the algorithms list.
    gcAlgorithm = new GChooser();
    gcAlgorithm->addItem("BFS");
    gcAlgorithm->addItem("Dijkstra");
    gcAlgorithm->addItem("A*");
    gcAlgorithm->addItem("Alternative Route");

    gsDelay = new GSlider(ANIMATION_DELAY_MIN, ANIMATION_DELAY_MAX, ANIMATION_DELAY_DEFAULT);

    gtfPosition = new GTextField(7);
    gtfPosition->setText(gtfPositionText);
    gtfPosition->setEditable(false);

    // Add in the list of existing world files.
    gcWorld = new GChooser();
    Set<std::string> worldFiles = getFiles("map");// + getFiles("terrain");
    for (std::string worldFile : worldFiles) {
        gcWorld->addItem(worldFile);
    }
    gcWorld->addItem(OTHER_FILE_LABEL);

    gcWorld->setSelectedItem("map-usa.txt");   // initially selected

    // north layout
    gWindow->addToRegion(gcAlgorithm, "NORTH");
    glDelay = new GLabel("Delay:");
    gWindow->addToRegion(glDelay, "NORTH");
    gWindow->addToRegion(gsDelay, "NORTH");
    gbRun = new GButton("Run");
    gbRun->setIcon("play.gif");
    gWindow->addToRegion(gbRun, "NORTH");
    gbClear = new GButton("Clear");
    gbClear->setIcon("cancel.gif");
    gWindow->addToRegion(gbClear, "NORTH");

    // south layout
    glWorld = new GLabel("World:");
    gWindow->addToRegion(glWorld, "SOUTH");
    gWindow->addToRegion(gcWorld, "SOUTH");
    gbLoad = new GButton("Load");
    gbLoad->setIcon("load.gif");
    gWindow->addToRegion(gbLoad, "SOUTH");
    gWindow->addToRegion(gtfPosition, "SOUTH");

    setAnimationDelay(ANIMATION_DELAY_DEFAULT);
    gsDelay->setValue(animationDelay);
    if (SHOULD_SAVE_GUI_STATE) {
        stateLoad();
    }

    gWindow->pack();   // correct the window size
    
    loadCurrentlySelectedWorld();
}

TrailblazerGUI::~TrailblazerGUI() {
    if (gWindow) {
        delete gcAlgorithm;
        delete gcWorld;
        delete gsDelay;
        delete gtfPosition;
        delete glDelay;
        delete glWorld;
        delete gbClear;
        delete gbLoad;
        delete gbRun;
        delete gWindow;
    }
    delete world;
}

GWindow* TrailblazerGUI::getGWindow() const {
    return gWindow;
}

void TrailblazerGUI::loadCurrentlySelectedWorld() {
    std::string worldFile = gcWorld->getSelectedItem();
    std::cout << std::endl;
    if (worldFile == OTHER_FILE_LABEL) {
        // prompt for file name
        worldFile = GFileChooser::showOpenDialog(getCurrentDirectory());
    }
    loadWorld(worldFile);
}

void TrailblazerGUI::processActionEvent(GActionEvent e) {
    /* Don't do anything if we're in the middle of a search operation. */
    if (pathSearchInProgress) {
        return;
    }

    std::string cmd = e.getActionCommand();
    if (cmd == "Load") {
        // load a world and update the UI
        loadCurrentlySelectedWorld();
    } else if (cmd == "Run") {
        // rerunning the search is only possible if we already did a search
        if (areEndpointsSelected()) {
            std::string algorithmLabel = gcAlgorithm->getSelectedItem();
            if(algorithmLabel != "Alternative Route") {
                world->clearPath();
            }
            runPathSearch();
        } else {
            std::cout << "You must select a start and end vertex first." << std::endl;
        }

    } else if (cmd == "Clear") {
        // clearing the display just sets us back to the fresh state
        world->clearSelection(/* redraw */ false);
        world->clearPath(/* redraw */ true);
    } else if (cmd == "Exit") {
        shutdown();
    }
}

void TrailblazerGUI::processMouseEvent(GMouseEvent e) {
    if (e.getEventType() == MOUSE_CLICKED) {
        world->handleClick(e.getX(), e.getY());
    } else if (e.getEventType() == MOUSE_MOVED) {
        // update display of current mouse row/col position to aid map creation
        std::string desc = world->getDescription(e.getX(), e.getY());
        if (desc != gtfPositionText) {
            gtfPositionText = desc;
            gtfPosition->setText(desc);
        }
    }
}

void TrailblazerGUI::processWindowEvent(GWindowEvent e) {
    if (e.getEventType() == WINDOW_CLOSED || e.getEventType() == CONSOLE_CLOSED) {
        shutdown();
    }
}

Set<std::string> TrailblazerGUI::getFiles(std::string prefix) const {
    prefix = toLowerCase(prefix);
    Vector<std::string> files = listDirectory(".");

    Set<std::string> result;
    for (std::string file : files) {
        std::string fileLC = toLowerCase(file);
        if (startsWith(fileLC, prefix) && endsWith(fileLC, ".txt")) {
            result.add(file);
        }
    }
    return result;
}

bool TrailblazerGUI::areEndpointsSelected() const {
    RoadNode* start = world->getSelectedStart();
    RoadNode* end = world->getSelectedEnd();
    return (start && end);
}

bool TrailblazerGUI::loadWorld(std::string worldFile) {
    if (worldFile.empty() || !fileExists(worldFile)) {
        std::cout << "File not found; aborting." << std::endl;
        return false;
    }

    if (world) {
        delete world;
        world = nullptr;
        gWindow->repaint();
    }
    
    std::cout << "Loading world from " << getTail(worldFile) << " ..." << std::endl;
    gbLoad->setIcon("progress.gif");

    if (stringContains(worldFile, "map")) {
        // WorldSize not needed for maps
        world = new WorldDisplay(gWindow);
    } else {
        error("Couldn't find the map section in the world file.");
    }
    
    bool result = true;
    bool readSuccessful = world->read(worldFile);
    if (readSuccessful) {
        std::cout << "Preparing world model ..." << std::endl;
        snapConsoleLocation();
        
        gWindow->clearCanvas();
        world->addObserver(this);
        world->draw();

        std::cout << "World model completed." << std::endl;
        result = true;
        world->clearSelection(/* redraw */ false);
        world->clearPath(/* redraw */ true);
    } else {
        std::cerr << worldFile << " is not a valid world file." << std::endl;
        result = false;
    }
    
    gbLoad->setIcon("load.gif");
    return result;
}

double TrailblazerGUI::costOf(const Vector<RoadNode*>& path) const {
    auto* graph = world->getGraph();
    double result = 0.0;
    for (int i = 1; i < path.size(); i++) {
        auto* edge = graph->getArc(path[i - 1], path[i]);
        result += edge->cost();
    }
    return result;
}

void TrailblazerGUI::displayPathInfo(Vector<RoadNode*>& path) {
    std::cout << "Path length: " << path.size() << std::endl;
    std::cout << "Path cost: " << costOf(path) << std::endl;

    std::cout << "Locations explored (green nodes):   " << world->numGreenNodes() << std::endl;
    std::cout << "Locations in fringe (yellow nodes): " << world->numYellowNodes() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
}

bool TrailblazerGUI::pathVerify(Vector<RoadNode *> &path) const {
    auto* graph = world->getGraph();
    for (int i = 0; i < path.size(); i++) {
        auto* v = path[i];
        if (!v) {
            std::cerr << "Invalid path: null vertex at index " << i << std::endl;
            return false;
        }
        auto* vcheck = graph->getNode(v->nodeName());
        if (vcheck != v) {
            std::cerr << "Invalid path: vertex " << v->nodeName() << " at index " << i
                      << " points to memory not found in the graph" << std::endl;
            return false;
        }
        
        if (i > 0) {
            auto* prev = path[i - 1];
            auto* edge = graph->getArc(prev, v);
            if (!edge) {
                std::cerr << "Invalid path: no edge exists from "
                          << prev->nodeName() << " to " << v->nodeName() << std::endl;
                return false;
            }
        }
    }
    return true;
}

Vector<RoadNode*> TrailblazerGUI::runPathSearch() {
    updateAnimationDelayFromSlider(/* forbidZero */ false);
    pathSearchInProgress = true;
    std::string algorithmLabel = gcAlgorithm->getSelectedItem();

    Vector<RoadNode*> path;
    auto* start = world->getSelectedStart();
    auto* end = world->getSelectedEnd();
    if (!start || !end) {
        return path;
    }
    
    std::cout << std::endl;
    std::cout << "Looking for a path from " << start->nodeName()
              << " to " << end->nodeName() << "." << std::endl;

    RoadGraph graph(world->getGraph());
    world->resetState();

    if (algorithmLabel == "BFS") {
        std::cout << "Executing breadth-first search algorithm ..." << std::endl;

        path = breadthFirstSearch(graph, start, end);
    } else if (algorithmLabel == "Dijkstra") {
        std::cout << "Executing Dijkstra's algorithm ..." << std::endl;
        path = dijkstrasAlgorithm(graph, start, end);
    } else if (algorithmLabel == "A*") {
        std::cout << "Executing A* algorithm ..." << std::endl;
        path = aStar(graph, start, end);
    } else if (algorithmLabel == "Alternative Route") {
        std::cout << "Executing Alternative Route Search algorithm ..." << std::endl;
        path = alternativeRoute(graph, start, end);
    }
    std::cout << "Algorithm complete." << std::endl;
    
    bool shouldDraw = true;
    if (path.isEmpty()) {
        std::cout << "No path was found. (The returned path is empty.)" << std::endl;
        shouldDraw = false;
    } else {
        auto* studentStart = path[0];
        auto* studentEnd = path[path.size() - 1];
        if (path[0] != start) {
            std::cout << "Warning: Start of path is not the start location." << std::endl;
            std::cout << "         (Expected " << "START" << ", found "
                      << (studentStart ? studentStart->nodeName() : "NULL") << std::endl;
            shouldDraw = false;
        }
        if (path[path.size() - 1] != end) {
            std::cout << "Warning: End of path is not the end location." << std::endl;
            std::cout << "         (Expected " << "END" << ", found "
                      << (studentEnd ? studentEnd->nodeName() : "NULL") << std::endl;
            shouldDraw = false;
        }
    }
    
    if (shouldDraw) {
        std::string color = algorithmLabel == "Alternative Route" ? "Blue" : "Red";
        world->drawPath(path, color);
    }
    
    pathSearchInProgress = false;
    
    displayPathInfo(path);
    if (animationDelay == 0) {
        // GUI will not have repainted itself to show the path being drawn;
        // manually repaint it
        gWindow->repaint();
    }
    
    return path;
}

void TrailblazerGUI::setAnimationDelay(int delayMS) {
    int oldDelay = animationDelay;
    animationDelay = delayMS;

    // tell the window whether or not to repaint on every square colored
    if ((animationDelay == 0) != (oldDelay == 0)) {
        gWindow->setRepaintImmediately(animationDelay != 0);
        if (animationDelay == 0) {
            std::cout << "(Running at max speed; node colors won't update)" << std::endl;
        }
    }
}

void TrailblazerGUI::snapConsoleLocation() {
    gtfPositionText = " ";
    gtfPosition->setText(gtfPositionText);
    GDimension size = world->getPreferredSize();
    gWindow->setCanvasSize(size.getWidth(), size.getHeight());

    Point guiLoc = gWindow->getLocation();
    GDimension guiSize = gWindow->getSize();
    setConsoleLocation(
                guiLoc.getX() + guiSize.getWidth() + WorldDisplay::WINDOW_MARGIN,
                guiLoc.getY());
}

void TrailblazerGUI::shutdown() {
    std::cout << std::endl;
    std::cout << "Exiting." << std::endl;
    if (SHOULD_SAVE_GUI_STATE) {
        stateSave();
    }
    exitGraphics();
}

bool TrailblazerGUI::stateLoad() {
    std::ifstream input;
    input.open(GUI_STATE_FILE.c_str());
    if (input.fail()) {
        return false;
    }
    std::string algorithm;
    getline(input, algorithm);
    if (input.fail()) {
        return false;
    }

    std::string line;
    getline(input, line);
    if (input.fail()) {
        return false;
    }
    setAnimationDelay(stringToInteger(line));

    std::string worldFile;
    getline(input, worldFile);
    if (input.fail()) {
        return false;
    }
    input.close();

    // delete the save state file in case there is a crash loading a world
    deleteFile(GUI_STATE_FILE);

    gcAlgorithm->setSelectedItem(algorithm);
    gsDelay->setValue(animationDelay);
    if (worldFile != OTHER_FILE_LABEL) {
        gcWorld->setSelectedItem(worldFile);
    }
    
    return true;
}

bool TrailblazerGUI::stateSave() {
    std::string algorithm = gcAlgorithm->getSelectedItem();
    int delay = gsDelay->getValue();
    std::string worldFile = gcWorld->getSelectedItem();
    std::ofstream output;
    output.open(GUI_STATE_FILE.c_str());
    if (output.fail()) {
        return false;
    }
    output << algorithm << std::endl;
    output << delay << std::endl;
    output << worldFile << std::endl;
    if (output.fail()) {
        return false;
    }
    output.flush();
    output.close();
    return true;
}

void TrailblazerGUI::update(Observable<UIEvent>*, const UIEvent& event) {
    if (event == UIEvent::VERTEX_COLORED) {
        if (animationDelay > 0) {
            updateAnimationDelayFromSlider(/* forbidZero */ false);
            pause(animationDelay);
        }
    } else if (event == UIEvent::PATH_SELECTION_READY) {
        if (areEndpointsSelected()) {
            runPathSearch();
        }
    } else {
        error("Unknown event: " + std::to_string(static_cast<int>(event)));
    }
}

void TrailblazerGUI::updateAnimationDelayFromSlider(bool forbidZero) {
    int delay = gsDelay->getValue();
    double percent = 100.0 * delay / ANIMATION_DELAY_MAX;
    
    // convert scale so delays don't increase so rapidly
    if (percent == 0.0) {
        delay = forbidZero ? 1 : 0;
    } else if (percent <= 10) {
        delay = ANIMATION_DELAY_MAX / 1000;
    } else if (percent <= 20) {
        delay = ANIMATION_DELAY_MAX / 500;
    } else if (percent <= 30) {
        delay = ANIMATION_DELAY_MAX / 200;
    } else if (percent <= 40) {
        delay = ANIMATION_DELAY_MAX / 100;
    } else if (percent <= 50) {
        delay = ANIMATION_DELAY_MAX / 50;
    } else if (percent <= 60) {
        delay = ANIMATION_DELAY_MAX / 25;
    } else if (percent <= 70) {
        delay = ANIMATION_DELAY_MAX / 10;
    } else if (percent <= 80) {
        delay = ANIMATION_DELAY_MAX / 5;
    } else if (percent <= 90) {
        delay = ANIMATION_DELAY_MAX / 2;
    } else {  // percent > 90
        delay = ANIMATION_DELAY_MAX;
    }

    setAnimationDelay(delay);
}
