#include <iostream> 
#include <vector>
#include <stack>
using namespace std;

void dfs_pass_one(vector<vector<int>>& graph, int vertex, stack<int>& stack, vector<bool>& visited) {
    visited[vertex] = true;
    for (int neighbor : graph[vertex]) {
        if (!visited[neighbor]) {
            dfs_pass_one(graph, neighbor, stack, visited);
        }
    }
    stack.push(vertex);
}

void dfs_pass_two(vector<vector<int>>& graph, int vertex, vector<bool>& visited, vector<int>& scc) {
    visited[vertex] = true;
    scc.push_back(vertex);
    for (int neighbor : graph[vertex]) {
        if (!visited[neighbor]) {
            dfs_pass_two(graph, neighbor, visited, scc);
        }
    }
}

vector<vector<int>> kosaraju(vector<vector<int>>& graph) {
    // Step 1: Create an empty stack and mark all vertices as unvisited.
    stack<int> stack;
    vector<bool> visited(graph.size(), false);

    // Step 2: For each unvisited vertex in the graph, perform a depth-first search.
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        if (!visited[vertex]) {
            dfs_pass_one(graph, vertex, stack, visited);
        }
    }

    // Step 3: Create a reverse graph by reversing the direction of all edges.
    vector<vector<int>> reverse_graph(graph.size());
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        for (int neighbor : graph[vertex]) {
            reverse_graph[neighbor].push_back(vertex);
        }
    }

    // Step 4: Pop vertices from the stack and perform a depth-first search on the reverse graph.
    visited.assign(graph.size(), false);
    vector<vector<int>> strongly_connected_components;
    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex]) {
            vector<int> scc;
            dfs_pass_two(reverse_graph, vertex, visited, scc);
            strongly_connected_components.push_back(scc);
        }
    }

    // Step 5: Return the set of strongly connected components.
    return strongly_connected_components;
}

int main() {
    // Example usage
    vector<vector<int>> graph = {{1}, {2}, {0, 3}, {4}, {5}, {3}};
    vector<vector<int>> scc = kosaraju(graph);
    for (auto& component : scc) {
        cout << "SCC: ";
        for (int vertex : component) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    return 0;
}
