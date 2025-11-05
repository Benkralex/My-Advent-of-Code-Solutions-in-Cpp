#include <iostream>
#include <chrono>
#include "../graph.cpp"

long now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
};

int main() {
    std::time_t start = now();

    /* CODE START */
    std::cout << "Dijkstra's Algorithm Test\n";
    Graph g(17);
    g.addEdge(0, 15, 10);
    g.addEdge(0, 4, 50);
    g.addEdge(0, 5, 30);

    g.addEdge(1, 11, 10);

    g.addEdge(2, 14, 5);

    g.addEdge(3, 16, 1000);
    g.addEdge(3, 13, 70);

    g.addEdge(4, 16, 2000);

    g.addEdge(5, 12, 0);
    g.addEdge(5, 4, 10);
    
    g.addEdge(6, 16, 50);
    g.addEdge(6, 8, 10);

    g.addEdge(7, 10, 30);

    g.addEdge(8, 10, 10);

    g.addEdge(9, 12, 20);
    g.addEdge(9, 7, 10);

    g.addEdge(10, 7, 100);
    g.addEdge(10, 16, 30);
    g.addEdge(10, 6, 10);

    g.addEdge(11, 3, 200);

    g.addEdge(12, 16, 500);

    g.addEdge(13, 6, 500);
    g.addEdge(13, 8, 30);

    g.addEdge(15, 11, 20);

    g.addEdge(16, 10, 10);
    g.addEdge(16, 3, 5);

    Path p = g.dijkstraSearch(0, 16);
    std::cout << "Total cost: " << p.totalCost << std::endl;
    std::cout << "Path: ";
    for (int node : p.nodes) {
        std::cout << node << " ";
    }
    /* CODE END */

    std::time_t end = now();
    std::cout << "\nTime taken: " << (end - start) << " ms\n";

    std::cout << std::endl;
    return 0;
};