# 🚍 City Route Finder — College Project

An interactive **C++ console application** that helps users find the **shortest route between cities** using **Dijkstra’s Algorithm**.  
It displays the **distance**, **optimal paths**, and **estimated travel time** — just like a simplified version of **Google Maps!** 🗺️  

---

## 🎯 Features
- 📍 View all connected cities and routes  
- 🧭 Find the **shortest distance** and **multiple shortest paths**  
- ⏱️ Estimate travel time (customizable speed)  
- 💡 Simple menu-driven interface for easy use  

---

## 🧠 Algorithm Used
This project implements **Dijkstra’s Algorithm**, a well-known **graph shortest path algorithm**.  
It uses a **min-heap (priority queue)** to always pick the next nearest city efficiently.

---

## 🧩 Data Structures Used

| Data Structure | Purpose |
|----------------|----------|
| `struct City` | Stores each city’s name and ID (Convert id → name while printing the paths) |
| `struct RouteResult` | To represent the route result |
| `vector<pair<int,int>> adj[]` | Adjacency list to store connected cities and distances |
| `vector<int>` | To store distances and temporary paths |
| `vector<vector<int>>` | To store all parent nodes for multiple shortest paths |
| `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>` | Min-heap for selecting the next city with the smallest distance (core of Dijkstra’s Algorithm) |
| `unordered_map<string,int>` | Maps city names to numeric IDs for quick lookup (Convert name → id to get the id immediately in O(1) lookup as the user types the src & dest) |

These data structures make the program **efficient**, **organized**, and **scalable** for multiple cities.

---

## 🖥️ Sample Output
```bash
==============================
🚍 CITY ROUTE FINDER MENU
==============================
1. View all cities
2. Find shortest route between two cities
3. Exit
Enter your choice: 2

Enter source city: Mumbai
Enter destination city: Nagpur

✅ Shortest Distance from Mumbai to Nagpur = 700 km
🛣️  Route: Mumbai → Pune → Nashik → Nagpur
🛣️  Route: Mumbai → Aurangabad → Nagpur
⏱️  Estimated Travel Time (at 60 km/hr): 11.67 hours
