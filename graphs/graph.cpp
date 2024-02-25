#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class undirected_Graph {
public:
	undirected_Graph(int size) : adj(size,std::vector<int>(0)), size(size) {}
	undirected_Graph() : adj(0,std::vector<int>(0)), size(0) {}
	void addEdge(int u, int v);
	void addVertex(int u = 0);
	void bfs(int v);
	void dfs(int v, std::vector<bool>& visited);
	bool isCyclic();
	int connectedComponents();
	int countNodesAtLevel(int v, int level);
	std::vector<int> shortestPathBetween2Nodes(int u, int v);

private:
	bool isCyclicHelper(int v, int parent, std::vector<bool>& visited);
	int size;
	std::vector<std::vector<int>> adj;
};

void undirected_Graph::addEdge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void undirected_Graph::addVertex(int u) {
	adj.emplace_back();
	++size;
}

int undirected_Graph::countNodesAtLevel(int v, int lvl) {
	std::vector<bool> visited(size,0);
	std::vector<int> level(size,0);
	std::queue<int> qu;

	qu.push(v);
	visited[v] = true;
	
	while (!qu.empty()) {
		int u = qu.front();
		qu.pop(); 

		for (auto n : adj[u]) {
			if (!visited[n]) {
				qu.push(n);
				visited[n] = true;
				level[n] = level[u] + 1;
			}
		}
	}
	int count{};
	for (int i = 0; i < size; ++i) {
		if (level[i] == lvl) {
			++count;
		}
	}
	return count;
}

void undirected_Graph::dfs(int v, std::vector<bool>& visited) {
	visited[v] = true;
	//std::cout << v << " ";
	for (auto u : adj[v]) {
		if (!visited[u]) {
			dfs(u, visited);
		}
	}
	//std::cout << v << " ";
}

bool undirected_Graph::isCyclicHelper(int v, int parent, std::vector<bool>& visited) {
	visited[v] = true;
	for (auto u : adj[v]) {
		if (!visited[u]) {
			if(isCyclicHelper(u,v,visited)) {
				return true; 
			}
		} else {
			if (u != parent) {
				return true;
			}
		}
	}
	return false;
}

bool undirected_Graph::isCyclic() {
	std::vector<bool> visited(size,0);
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			if (isCyclicHelper(i,-1,visited)) {
				return true;
			}
		}
	}
	return false;
}

int undirected_Graph::connectedComponents() {
	std::vector<bool> visited(size, 0);
	int count{};
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			dfs(i, visited);
			++count;
		}
	}
	return count;
}

std::vector<int> undirected_Graph::shortestPathBetween2Nodes(int u, int v) {
        std::vector<int> visited(size, 0);
	std::vector<int> parents(size,-1);
        std::vector<int> path;
        std::queue<int> qu;

        qu.push(u);
        visited[u] = 1;

        while (!qu.empty()) {
            int s = qu.front();
            qu.pop();

            if (s == v) {
                break;
            }

            for (auto neigh : adj[s]) {
                if (!visited[neigh]) {
                    qu.push(neigh);
                    visited[neigh] = 1;
		    parents[neigh] = s;
                }
            }
        }
	path.push_back(v);
	int p = parents[v];
	while (p != -1) {
		path.push_back(p);
		p = parents[p];
	}
	std::reverse(path.begin(), path.end());
		
        return path;
    }

int main() {
	std::vector<bool> visited(7, 0);
	undirected_Graph g(7);
	g.addEdge(0,1);
	g.addEdge(0,3);
	g.addEdge(0,4);
	g.addEdge(0,5);
	//g.addEdge(0,6);
	g.addEdge(5,6);
	std::cout << g.countNodesAtLevel(0,2) << std::endl;
/*	std::vector<int> res = g.shortestPathBetween2Nodes(0,3);
	for (auto v : res) {
		std::cout << v << ' ';
	} */ 
//	std::cout << std::endl;
//	std::cout << std::boolalpha << g.isCyclic() << std::endl;
//	std::cout << g.connectedComponents() << std::endl;
}
