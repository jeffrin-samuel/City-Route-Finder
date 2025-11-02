#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip> // for setprecision
using namespace std;

#define INF 1e9 // A large number representing "infinity"

// -----------------------------
// Struct to represent a City
// -----------------------------
struct City {
    string name;
    int id;
};

// -----------------------------
// Function to print all shortest paths from source to current node
// -----------------------------
void printPaths(int node, int src, vector<vector<int>> &parents, vector<int> &path, vector<City> &cities) {
    path.push_back(node); // Add current node to path

    if (node == src) {
        // Base case: reached the source, print the path in correct order
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << cities[path[i]].name;
            if (i != 0) cout << " --> ";
        }
        cout << endl;
    } else {
        // Recurse for all parents of the current node
        for (int p : parents[node]) {
            printPaths(p, src, parents, path, cities);
        }
    }

    path.pop_back(); // Backtrack to explore other paths
}

// -----------------------------
// Dijkstra's algorithm to find all shortest paths
// -----------------------------
void dijkstraAllPaths(int V, vector<pair<int,int>> adj[], int src, int dest, vector<City> &cities, float avgSpeed) {
    vector<int> dist(V, INF);              // Distance from source to each node
    vector<vector<int>> parents(V);        // Store all parents for each node
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // Min-heap

    dist[src] = 0; // Distance to source is 0
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second; // Node with smallest distance
        int d = pq.top().first;  // Distance of that node
        pq.pop();

        if (d > dist[u]) continue; // Skip if we already found a shorter path

        for (auto edge : adj[u]) {
            int v = edge.first;   // Neighbor node
            int w = edge.second;  // Edge weight (distance)

            if (dist[u] + w < dist[v]) {
                // Found a strictly shorter path
                dist[v] = dist[u] + w;
                parents[v].clear();      // Remove old parents
                parents[v].push_back(u); // Store current node as parent
                pq.push({dist[v], v});
            } else if (dist[u] + w == dist[v]) {
                // Found another path with same minimum distance
                parents[v].push_back(u);
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path exists between " << cities[src].name << " and " << cities[dest].name << ".\n";
        return;
    }

    // Output shortest distance
    cout << "\nShortest Distance from " << cities[src].name << " to " << cities[dest].name << " = " << dist[dest] << " km\n";

    // Output all shortest paths
    cout << "\nAll shortest paths:\n";
    vector<int> path;
    printPaths(dest, src, parents, path, cities);

    // Estimate travel time
    float hours = dist[dest] / avgSpeed;
    cout << "\nEstimated Travel Time (at " << avgSpeed << " km/hr): " << fixed << setprecision(2) << hours << " hours\n";
}

// -----------------------------
// Function to display all cities
// -----------------------------
void displayCities(vector<City> &cities) {
    cout << "\n List of Cities:\n";
    for (int i = 0; i < cities.size(); i++)
        cout << i+1 << ". " << cities[i].name << endl;
}

// -----------------------------
// Main function
// -----------------------------
int main() {
    int V;

    cout << "Enter number of cities: ";
    cin >> V;

    vector<City> cities(V);                 // Vector of City structs
    unordered_map<string,int> cityToId;     // Map city name to index

    // Input city names
    cout << "Enter city names:\n";
    for (int i = 0; i < V; i++) {
        cin >> cities[i].name;
        cities[i].id = i;
        cityToId[cities[i].name] = i;
    }

    vector<pair<int,int>> adj[V]; // Adjacency list: pair(neighbor, distance)

    // Input roads dynamically
    cout << "\nEnter roads in format: city1 city2 distance\n";
    cout << "Type 'done' to finish entering roads.\n";
    while (true) {
        string c1;
        cin >> c1;
        if (c1 == "done") break;

        string c2;
        int dist;
        cin >> c2 >> dist;

        if (cityToId.find(c1) == cityToId.end() || cityToId.find(c2) == cityToId.end()) {
            cout << "Invalid city names, try again.\n";
            continue;
        }

        int u = cityToId[c1];
        int v = cityToId[c2];

        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist}); // Assuming undirected roads
    }

    float avgSpeed;
    cout << "\nEnter average travel speed (km/hr): ";
    cin >> avgSpeed;

    int choice;
    do {
        // Menu options
        cout << "\n==============================";
        cout << "\n CITY ROUTE FINDER MENU";
        cout << "\n==============================";
        cout << "\n1. View all cities";
        cout << "\n2. Find shortest route between two cities";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCities(cities);
                break;

            case 2: {
                string srcCity, destCity;
                cout << "\nEnter source city: ";
                cin >> srcCity;
                cout << "Enter destination city: ";
                cin >> destCity;

                // Validate city names
                if (cityToId.find(srcCity) == cityToId.end() || cityToId.find(destCity) == cityToId.end()) {
                    cout << "Invalid city name entered!\n";
                } else {
                    int src = cityToId[srcCity];
                    int dest = cityToId[destCity];
                    dijkstraAllPaths(V, adj, src, dest, cities, avgSpeed);
                }
                break;
            }

            case 3:
                cout << "\nExiting City Route Finder. Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
