/*
 * CS 106B Trailblazer
 * This file declares the functions you will write in this assignment.
 * 
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * !!!IF YOU MODIFY THIS FILE, YOU *WILL* LOSE POINTS ON YOUR GRADE!!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Chris Piech, Marty Stepp, Keith Schwarz
 * @version 2017/03/09 (updated version for Win17)
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include "vector.h"
#include "RoadGraph.h"

/**
 * Type: Path
 *
 * A type representing a path. This type literally is a Vector<Vertex*>, but we've given
 * it the convenient name "Path" for simplicity.
 */
using Path = Vector<RoadNode*>;

/*
 * The path-searching algorithms you must implement.
 */

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end);
Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end);
Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end);
Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end);

#endif

/*
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 */

