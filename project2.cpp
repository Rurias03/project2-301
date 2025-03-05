/*
 * CSC-301
 * project2.cpp
 * Spring 2025
 *
 * Partner 1: Princess Alexander
 * Partner 2: Rene Urias Jr.
 * Date: 05-03-2025 (dd-mm-yyyy)
 */

#include "project2.hpp"

using namespace std;

/**
 * Depth First Search (DFS)
 * 
 * DFS finds a path through the maze from the start vertex to the exit vertex.
 * 
 * @param adjList The adjacency list representation of the maze (vector of Vertex objects).
 * @param start The starting vertex of the maze.
 * @param exit The exit vertex of the maze.
 * @return A vector<int> containing the path from start to exit, or an empty 
 *         vector if no path exists.
 */
vector<int> DFS(vector<Vertex> &adjList, Vertex &start, Vertex &exit) {
    stack<int> s;            // a stack to store DFS traversal
    vector<int> path;        // a vector to store the final path

    // Initialize all the vertices to have no previous and no pointer
    for (Vertex &v : adjList) {
        v.visited = false;
        v.previous = -1;     // -1 means that there was no vertex before it
    } // for

    // Start DFS from the start vertex
    start.visited = true;
    s.push(start.label);

    // Traversing through the maze
    while (!s.empty()) {
        int currentLabel = s.top();  // grab the top element
        s.pop();
        Vertex &currentVertex = adjList[currentLabel];

        // when we reach the exit, we should stop the search
        if (currentLabel == exit.label) {
            break;
        } // if

        // Visit all unvisited neighbors (LIFO order)
        for (int neighborLabel : currentVertex.neighbors) {
            Vertex &neighborVertex = adjList[neighborLabel];
            if (!neighborVertex.visited) {
                neighborVertex.visited = true;
                neighborVertex.previous = currentLabel;  // keeps track of the path
                s.push(neighborLabel);
            } // if
        } // for
    } // while

    // Trace/ step back up the tree from the exit to start
    int trace = exit.label;
    if (!adjList[trace].visited) {
        // If exit was never visited, there is no path through the maze that exists
        return path;
    } // if
    while (trace != -1) {
        path.push_back(trace);
        trace = adjList[trace].previous;
    } // while

    // traversing the path the opposite way from start to exit
    reverse(path.begin(), path.end());

    return path;
} // DFS

/*
 * Breadth First Search
 */
vector<int> BFS(vector<Vertex> &adjList, Vertex &start, Vertex &exit) {
    queue<int> q;               // Queue to manage BFS
    vector<int> path;           // To store the final path

    // Step 1: Reset all vertices
    for (Vertex &v : adjList) {
        v.visited = false;
        v.previous = -1;        // -1 indicates no previous vertex
    }

    // Step 2: Initialize BFS with the start vertex
    start.visited = true;
    q.push(start.label);

    // Step 3: BFS Traversal
    while (!q.empty()) {
        int currentLabel = q.front();
        q.pop();
        Vertex &currentVertex = adjList[currentLabel];

        // If we've reached the exit, stop the search
        if (currentLabel == exit.label) {
            break;
        }

        // Visit all unvisited neighbors
        for (int neighborLabel : currentVertex.neighbors) {
            Vertex &neighborVertex = adjList[neighborLabel];
            if (!neighborVertex.visited) {
                neighborVertex.visited = true;
                neighborVertex.previous = currentLabel;
                q.push(neighborLabel);
            }
        }
    }

    // Step 4: Reconstruct the path from exit to start
    int trace = exit.label;
    if (!adjList[trace].visited) {
        // If exit was never visited, no path exists
        return path;
    }
    while (trace != -1) {
        path.push_back(trace);
        trace = adjList[trace].previous;
    }

    // Step 5: Reverse the path to be from start to exit
    reverse(path.begin(), path.end());

    return path;
}
