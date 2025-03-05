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

/*
 * Depth First Search
 */
vector<int> DFS(vector<Vertex> &adjList, Vertex &start, Vertex &exit) {
    vector<int> path;
    return path;
}

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
