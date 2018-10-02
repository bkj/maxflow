
// C++ program for implementation of Ford Fulkerson algorithm 
#include <cstdio>
#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 
#include <limits>
#include <algorithm>
#include <cassert>
using namespace std; 
  
// Number of vertices in given graph 
#define V 17
  
/* Returns true if there is a path from source 's' to sink 't' in 
  residual graph. Also fills parent[] to store the path */
bool bfs(double rGraph[V][V], int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[V]; 
    memset(visited, 0, sizeof(visited)); 
  
    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
  
    // Standard BFS Loop 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
  
        for (int v=0; v<V; v++) 
        { 
            if (visited[v]==false && rGraph[u][v] > 0) 
            { 
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
double fordFulkerson(double graph[V][V], int s, int t) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    double rGraph[V][V]; // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++){
        for (v = 0; v < V; v++){
             rGraph[u][v] = graph[u][v]; 
             printf("%3.3f ", rGraph[u][v]);
        }
        cout << endl;
    }
  
    int parent[V];  // This array is filled by BFS and to store path 
  
    double max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        double path_flow = numeric_limits<double>::max();
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    }

     
    for (u = 0; u < V; ++u){
		for (v = 0; v < V; ++v){
            if(u == 15 || v == 16)
	    	cout << "u: " << u << " v: " << v << ' ' <<rGraph[u][v] << endl;

        }
    }
    
  
    // Return the overall flow 
    return max_flow; 
} 
  
    // Let us create a graph shown in the above example 
   // double graph[V][V] = { {0, 16, 13, 0, 0, 0}, 
   //                     {0, 0, 10, 12, 0, 0}, 
   //                     {0, 4, 0, 0, 14, 0}, 
   //                     {0, 0, 9, 0, 0, 20}, 
   //                     {0, 0, 0, 7, 0, 4}, 
   //                     {0, 0, 0, 0, 0, 0} 
   //                   }; 
  

int main(int argc, char* argv[]){
    printf("hello world\n");
    int source = 0, sink = 1;
    if (argc < 3){
	printf("argc < 3\n");
	exit(1);
    }else{
	if (sscanf(argv[1], "%i", &source) != 1){
	    printf("error not an integer");
	}
	if (sscanf(argv[2], "%i", &sink) != 1){
	    printf("error not an integer");
	}
    }
    printf("source %d, sink %d\n", source, sink);
    int n, m;
    std::scanf("%d %d %d", &n, &n, &m);
    assert(source < n && sink < n);
    std::printf("n = %d, m = %d\n", n, m);
    double graph[V][V];
    for (int i=0; i<V; ++i)
	for (int j=0; j<V; ++j)
	    graph[i][j] = 0;
   for (int i = 0; i < m; ++i){
	int u, v;
	double c;
	std::scanf("%d %d %lf", &u, &v, &c);
	--u; --v;
	graph[u][v] = c;
	graph[v][u] = c;
    }
    cout << V << ' ' << V << endl;
    cout << "The maximum possible flow is " << 
	fordFulkerson(graph, source, sink) << "\n";
    return 0;
}
