#include "dijkstras.h"

std::vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){ // finds shortest path
    int numVerts = G.size();
    std::vector<int> distances(numVerts , INF);
    std::vector<bool> visited(numVerts , false);
    distances[source] = 0; 
    previous[source] = UNDEFINED;
    std::priority_queue<pair<int,int> , vector<pair<int,int>> , weightComparison > minHeap; // will probably have to do a comparator fn to have the minheap pull the vertex with the least weight out 
    minHeap.push({source , 0});
    while(!minHeap.empty()){
        int u = minHeap.top().first; 
        //int d = minHeap.top().second; 
        minHeap.pop();
        if(visited[u] /*|| d > distances[u]*/){
            continue;
        }
        visited[u] = true;
        for(Edge e : G[u]){
            int v  = e.dst;
            int weight = e.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v,distances[v]});
            }
        }

    }
    return distances; 
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){ // builds the returned path of dijkstras shortest path
    if(distances[destination] == INF){
        std::cerr << "not found" << std::endl;  
    }

    std::vector<int> sp;
    bool exitBeforeFirstIndex = false; 
    for(auto i = destination; i > previous[1] /*&& distances[i] != 0*/; i=previous[i]){
        if(i == UNDEFINED){
            exitBeforeFirstIndex = true; 
            break;
        }
        sp.push_back(i); 
    }
    if(exitBeforeFirstIndex == false && previous[1] != UNDEFINED){
        sp.push_back(previous[1]);
    }

    std::reverse(sp.begin() , sp.end());

    return sp; 
}



void print_path(const std::vector<int>& v, int total){
    for(auto i : v){
        std::cout << i << ' '; 
    }
    std::cout << "\nTotal cost is " << total << std::endl; 
}

/*
g++ -c ./src/dijkstras.cpp -o ./src/dijkstras.o
g++ ./src/dijkstras.o ./src/dijkstras_main.cpp -o ./src/dijkstras_main.exe
./src/dijkstras_main.exe

*/
