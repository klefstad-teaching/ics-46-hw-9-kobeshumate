vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){ // finds shortest path
    int numVerts = G.size();
    std::vector<int> distances(numVerts , INF);
    std::vector<bool> visited(numVerts , false);
    distances[source] = 0; 
    previous[source] = UNDEFINED;
    std::priority_queue<pair<int,int>> minHeap;
    minHeap.push({source , 0});
    while(!minHeap.empty()){
        int u = minHeap.top(); 
        minHeap.pop();
        if(visited[u]){
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
    for(auto i : previous[destination]){
        sp.push_back(i); 
    }
    return sp; 
}



void print_path(const vector<int>& v, int total){
    std::cout << " Total cost is " << total << std::endl; 
    for(auto i : v){
        std::cout << i << ' '; 
    }
}
