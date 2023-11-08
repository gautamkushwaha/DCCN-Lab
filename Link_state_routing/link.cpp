#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int INFINITY = 9999; // Represents an infinite distance

class Router {
public:
  int routerID;                     // Router ID
  map<int, int> LSD;                 // Link state database: [destination router ID] -> [link cost]
  map<int, int> routingTable;        // [destination router ID] -> [next hop router ID]
  vector<int> neighbors;            // List of neighbors

  void handleLSA(const LSA& lsa);       // Method to handle received LSAs
  void updateRoutingTable();          // Method to update routing table using Dijkstra's algorithm
  void forwardPacket(const Packet& packet); // Method to forward packets
};

class LSA {
public:
  int routerID;       // Router ID of the originating router
  map<int, int> links;   // Link costs: [neighbor router ID] -> [link cost]
};

void createAndFloodLSA(Router& router) {
  LSA lsa;
  lsa.routerID = router.routerID;
  lsa.links = router.LSD;

  // Flood LSA to all neighbors
  for (int neighborID : router.neighbors) {
    sendLSA(lsa, neighborID);
  }
}

void handleReceivedLSAs(vector<Router>& routers) {
  for (Router& router : routers) {
    // Process received LSAs and update LSD
    while (true) {
      LSA lsa; // Receive LSA from neighbor
      if (!receiveLSA(lsa)) {
        break;
      }

      router.handleLSA(lsa);
    }
  }
}

void Router::handleLSA(const LSA& lsa) {
  for (const auto& [neighborID, cost] : lsa.links) {
    // Update LSD entry for the neighbor
    LSD[neighborID] = cost;
  }
}

void Router::updateRoutingTable() {
  // Initialize all distances to infinity
  for (int i = 0; i < routingTable.size(); i++) {
    routingTable[i] = INFINITY;
  }

  // Initialize distance to self as 0
  routingTable[routerID] = 0;

  // Run Dijkstra's algorithm to calculate shortest paths
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
  queue.emplace(routerID, 0);

  while (!queue.empty()) {
    int currentRouterID = queue.top().first;
    int currentDistance = queue.top().second;
    queue.pop();

    // Update routing table for current router
    routingTable[currentRouterID] = currentDistance;

    // Relax edges for neighbors
    for (const auto& [neighborID, cost] : LSD) {
      int newDistance = currentDistance + cost;
      if (newDistance < routingTable[neighborID]) {
        queue.emplace(neighborID, newDistance);
        routingTable[neighborID] = newDistance;
        // Update next hop for this destination
        routingTable[currentRouterID] = neighborID;
      }
    }
  }
}

void Router::forwardPacket(const Packet& packet) {
  int destinationID = packet.destination;
  int nextHopID = routingTable[destinationID];

  // Forward packet to the next hop router
  sendPacket(packet, nextHopID);
}

void forwardPacket(vector<Router>& routers) {
  for (Router& router : routers) {
    while (true) {
      Packet packet; // Receive packet from neighbor
      if (!receivePacket(packet)) {
        break;
      }

      router.forwardPacket(packet);
    }
  }
}