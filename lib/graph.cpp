#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using std::vector;

class Edge {
public:
    int start;
    int end;
    int cost;

    Edge(int start_, int end_, int cost_) : 
        start(start_), end(end_), cost(cost_) {}
};

class Node {
public:
    int id;
    int cost;

    Node(int id_) : 
        id(id_), cost(INT_MAX) {}
    Node(int id_, int cost_) : 
        id(id_), cost(cost_) {}
};

class Path {
public:
    vector<int> nodes;
    int totalCost;

    Path(const vector<int>& nodes_, int totalCost_) : 
        nodes(nodes_), totalCost(totalCost_) {}
};

class Graph {
private:
    int nodeCount;
    vector<vector<Edge>> edgesOut;
    vector<vector<Edge>> edgesIn;
public:
    Graph(const int nodes) : 
        nodeCount(nodes), edgesOut(nodes), edgesIn(nodes) {}

    void addEdge(const Edge& e) {
        edgesOut[e.start].push_back(e); 
        edgesIn[e.end].push_back(e);
    }
    void addEdge(const int start, const int end, const int cost) { 
        edgesOut[start].emplace_back(start, end, cost);
        edgesIn[end].emplace_back(start, end, cost);
    }

    vector<Edge> getEdgesFromNode(const int node) {
        return edgesOut[node];
    }

    vector<Edge> getEdgesToNode(const int node) {
        return edgesIn[node];
    }

    vector<Edge> getEdges() const {
        vector<Edge> allEdges;
        for (const auto& edgeList : edgesOut) {
            allEdges.insert(allEdges.end(), edgeList.begin(), edgeList.end());
        }
        return allEdges;
    }

    vector<int> getNeighbours(const int node) const {
        vector<int> neighbours;
        for (const auto& edge : edgesOut[node]) {
            neighbours.push_back(edge.end);
        }
        return neighbours;
    }

    Path dijkstraSearch(const int startNode, const int goalNode) {
        vector<int> costs(nodeCount, INT_MAX);
        vector<int> predecessors(nodeCount, -1);
        vector<int> visitedNodes;
        std::priority_queue<std::pair<int, int>, 
                        vector<std::pair<int, int>>, 
                        std::greater<>> pq;

        costs[startNode] = 0;
        pq.push({0, startNode});

        while (!pq.empty()) {
            auto [currentCost, currentNode] = pq.top();
            pq.pop();
            visitedNodes.push_back(currentNode);

            if (currentNode == goalNode) {
                break;
            }

            // Update costs for neighbours of currentNode
            for (const auto& edge : getEdgesFromNode(currentNode)) {
                int cost = edge.cost + costs[currentNode];
                if (cost < costs[edge.end]) {
                    costs[edge.end] = cost;
                    predecessors[edge.end] = currentNode;
                    if (find(visitedNodes.begin(), visitedNodes.end(), edge.end) == visitedNodes.end()) {
                        pq.push({cost, edge.end});
                    }
                }
            }
        }

        // Backtrack to find path
        vector<int> path;
        int step = goalNode;
        while (step != -1) {
            path.push_back(step);
            step = predecessors[step];
        }
        std::reverse(path.begin(), path.end());

        return Path(std::move(path), costs[goalNode]);
    }
};