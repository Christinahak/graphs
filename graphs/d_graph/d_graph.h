#ifndef DIR_GRAPH
#define DIR_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>


class directed_Graph {
public:
	directed_Graph(int size) : adj(size,std::vector<int>(0)), size(size) {}
	directed_Graph() : adj(0,std::vector<int>(0)), size(0) {}
	void addEdge(int u, int v);
	void addVertex(int u = 0);
	void bfs(int v);
	void dfs(int v, std::vector<bool>& visited);
	bool isCyclic();
	int connectedComponents();
	int countNodesAtLevel(int v, int level);
	std::vector<int> shortestPathBetween2Nodes(int u, int v);
	std::vector<int> topSort();
	int countAllPathsBetween2Nodes(int u, int v);
	std::vector<std::vector<int>> allPaths(int u, int v);
	std::vector<std::vector<int>> kosaraju();
	std::vector<std::vector<int>> SCC_Tarjan();

private:
	void dfs_Tarjan(int u, std::vector<int>& low, std::vector<int>& ids, std::vector<bool>& recStack
		, std::stack<int>& st, std::vector<std::vector<int>>& res);
	void allPathsHelper(int u, int v,std::vector<bool> visited,
		       	std::vector<int> curr, std::vector<std::vector<int>>& res);
	int countPathsHelper(int u, int v, int& count, std::vector<bool> visited);
	
	bool isCyclicHelper(int v, std::vector<bool> st, std::vector<bool>& visited);

	void k_dfs_1(int u, std::vector<bool>& visited, std::stack<int>& st);
	void k_dfs_2(int u, std::vector<std::vector<int>> transposed
			, std::vector<bool>& visited, std::vector<int>& scc);
	std::vector<std::vector<int>> transpose();

	int size;
	std::vector<std::vector<int>> adj;
};

#include "d_graph.cpp"

#endif
