
// C++ program for implementation of Ford Fulkerson algorithm
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <limits.h>
#include <limits>
#include <queue>
#include <string.h>
using namespace std;

#define V 6
double data[V][V] = {
  {0, 16, 13, 0, 0, 0},
  {0, 0, 10, 12, 0, 0},
  {0, 4, 0, 0, 14, 0},
  {0, 0, 9, 0, 0, 20},
  {0, 0, 0, 7, 0, 4},
  {0, 0, 0, 0, 0, 0}
};

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(double rGraph[V][V], int s, int t, int parent[]) {
  // Create a visited array and mark all vertices as not visited
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  // Create a queue, enqueue source vertex and mark source vertex
  // as visited
  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  // Standard BFS Loop
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++) {
      if (visited[v] == false && rGraph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  // If we reached sink in BFS starting from source, then return
  // true, else false
  return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
double fordFulkerson(double graph[V][V], int s, int t, bool verbose) {
  int u, v;

  double rGraph[V][V];
  for (u = 0; u < V; u++) {
    for (v = 0; v < V; v++) {
      rGraph[u][v] = graph[u][v];
    }
  }

  int parent[V]; // This array is filled by BFS and to store path

  double max_flow = 0; // There is no flow initially

  // Augment the flow while tere is path from source to sink
  while (bfs(rGraph, s, t, parent)) {
    // Find minimum residual capacity of the edges along the
    // path filled by BFS. Or we can say find the maximum flow
    // through the path found.
    double path_flow = numeric_limits<double>::max();
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    // update residual capacities of the edges and reverse edges
    // along the path
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    // Add path flow to overall flow
    max_flow += path_flow;
  }

  if(verbose) {
    printf("u v res\n");
    for (u = 0; u < V; ++u) {
      for (v = 0; v < V; ++v) {
        if(graph[u][v] != 0) {
          printf("%d %d %f\n", u, v, rGraph[u][v]);
        }
      }
    }
  }

  // Return the overall flow
  return max_flow;
}

int main(int argc, char *argv[]) {
  int source   = 0;
  int sink     = 5;
  bool verbose = true;

  double max_flow = fordFulkerson(data, source, sink, verbose);
  cerr << "max_flow=" << max_flow << endl;
  return 0;
}
