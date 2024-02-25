#include "d_graph.h"

void directed_Graph::addEdge(int u, int v) {
	adj[u].push_back(v);
}

void directed_Graph::addVertex(int u) {
	adj.emplace_back();
	++size;
}

int directed_Graph::countNodesAtLevel(int v, int level) {
	std::vector<bool> visited(size,0);
	std::vector<int> levels(size,0);
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
				levels[n] = levels[u] + 1;
			}
		}
	}
	
	int count{};
	for (int i = 0; i < size; ++i) {
		if (levels[i] == level) {
			++count;
		}
	}
	return count;
}

void directed_Graph::dfs(int v, std::vector<bool>& visited) {
	visited[v] = true;
	//std::cout << v << " ";
	for (auto u : adj[v]) {
		if (!visited[u]) {
			dfs(u, visited);
		}
	}
	//std::cout << v << " ";
}

bool directed_Graph::isCyclicHelper(int v, std::vector<bool> onstack, std::vector<bool>& visited) {
	visited[v] = true;
	onstack[v] = true;
	for (auto u : adj[v]) {
		if (!visited[u]) {
			if(isCyclicHelper(u,onstack,visited)) {
				return true; 
			}
		} else {
			if (onstack[u]) {
				return true;
			}
		}
	}
	return false;
}

bool directed_Graph::isCyclic() {
	std::vector<bool> visited(size,0);
	std::vector<bool> onStack(size,0);

	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			if (isCyclicHelper(i,onStack,visited)) {
				return true;
			}
		}
	}
	return false;
}

int directed_Graph::connectedComponents() {
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

 std::vector<int> directed_Graph::shortestPathBetween2Nodes(int u, int v) {
        std::vector<bool> visited(size, 0);
        std::vector<int> path;
	std::vector<int> parents(size,-1);
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
			visited[neigh] = true;
			parents[neigh] = s;
                }
            }
        }

	path.push_back(v);
	while (parents[v] != -1) {
		v = parents[v];
		path.push_back(v);
	}
	std::reverse(path.begin(),path.end());
        return path;
    }

int directed_Graph::countAllPathsBetween2Nodes(int u, int v) {
	std::vector<bool> visited(size,0);
	int count{};
	countPathsHelper(u,v,count,visited);
	return count;
}

int directed_Graph::countPathsHelper(int u, int v, int& count, std::vector<bool> visited) {
	visited[u] = true;
	if (u == v) { 
		++count; 
	}
	else {
		for (auto neigh : adj[u]) {
			if (!visited[neigh]) {
				countPathsHelper(neigh,v,count,visited);
			}
		}
	}
	return count;	
}

std::vector<int> directed_Graph::topSort() {
	std::vector<int> topsort;
	std::vector<int> inDegree(size,0);
	std::queue<int> qu;

	for (auto vect : adj) {
		for (auto v : vect) {
			++inDegree[v];
		}
	}

	for (int i = 0; i < size; ++i) {
		if (inDegree[i] == 0) {
			qu.push(i);
		}
	}

	while (!qu.empty()) {
		int u = qu.front();
		qu.pop();
		topsort.push_back(u);
		
		for (auto neigh : adj[u]) {
			--inDegree[neigh];
			if (inDegree[neigh] == 0) {
				qu.push(neigh);
			}
		}	
	}

	if (topsort.size() != size) {
		throw std::exception();
	}
	return topsort;
}

std::vector<std::vector<int>> directed_Graph::allPaths(int u, int v) {
	std::vector<int> curr;
	std::vector<std::vector<int>> res;
	std::vector<bool> visited(size,0);
	allPathsHelper(u, v, visited, curr, res);
	return res;
}

void directed_Graph::allPathsHelper(int u, int v, std::vector<bool> visited, std::vector<int> curr, std::vector<std::vector<int>>& res) {
	visited[u] = true;
	curr.push_back(u);
	if (u == v) {
		res.push_back(curr);
	} else {
		for (auto neigh : adj[u]) {
			if (!visited[neigh]) {
				allPathsHelper(neigh,v,visited,curr,res);
			}
		}
	}
}

std::vector<std::vector<int>> directed_Graph::transpose() {
	std::vector<std::vector<int>> adjacence(size);
	for (int i = 0; i < size; ++i) {
		for (int v : adj[i]) {
			adjacence[v].push_back(i);
		}
	}
	return adjacence;
}

void directed_Graph::k_dfs_1(int u, std::vector<bool>& visited, std::stack<int>& st) {
	visited[u] = true;
	for (auto v : adj[u]) {
		if (!visited[v]) {
			k_dfs_1(v,visited,st);
		}
	}
	st.push(u);
}

void directed_Graph::k_dfs_2(int u, std::vector<std::vector<int>> transposed
			, std::vector<bool>& visited, std::vector<int>& scc) {
	visited[u] = true;
	scc.push_back(u);
	for (auto v : transposed[u]) {
		if (!visited[v]) {
			k_dfs_2(v,transposed,visited,scc);
		}
	}
}

std::vector<std::vector<int>> directed_Graph::kosaraju() {
	std::stack<int> st;
	std::vector<bool> visited(size,0);
	std::vector<std::vector<int>> result;
	
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			k_dfs_1(i,visited,st);
		}
	}

	std::vector<std::vector<int>> transposed = transpose();
	visited.assign(size,0);
	while (!st.empty()) {
		int v = st.top();
		st.pop();
		if (!visited[v]) {
			std::vector<int> curr;
			k_dfs_2(v,transposed,visited, curr);
			result.push_back(curr);
		}
	}
	return result;
}

std::vector<std::vector<int>> directed_Graph::SCC_Tarjan() {
	std::vector<int> low(size, 0);
    	std::vector<int> ids(size, -1);
	std::vector<bool> recStack(size, false);
    	std::stack<int> st;
    	std::vector<std::vector<int>> res;

    	for (int i = 0; i < size; ++i) {
        	if(ids[i] == -1) {
            		dfs_Tarjan(i, low, ids, recStack, st, res);
        	}
    	}
    	return res;
}

void directed_Graph::dfs_Tarjan(int u, std::vector<int>& low, std::vector<int>& ids, std::vector<bool>& recStack
		, std::stack<int>& st, std::vector<std::vector<int>>& res) {
	static int id = 0;
	recStack[u] = true;
	st.push(u);
    	low[u] = ids[u] = id++;
    	for (auto v : adj[u]) {
        	if (ids[v] == -1) {
        		dfs_Tarjan(v, low, ids, recStack, st, res);
        	}
        	if (recStack[v]) {
            		low[u] = std::min(low[u], low[v]);
        	}
    	}
    	if (low[u] == ids[u]) {
        	std::vector<int> tmp;
        	while(true) {
			int i = st.top();
            		st.pop();
            		tmp.push_back(i);
            		recStack[i] = false;
            		if (i == u) break;
        	}
        	res.push_back(tmp);
	}
}
