#include "d_graph.h"

int main() {
	std::vector<bool> visited(4, 0);
	directed_Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,0);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(5,3);
	//std::cout << g.countNodesAtLevel(0,1) << std::endl;
	//g.dfs(0,visited)
	auto res = g.SCC_Tarjan();
	for (auto v : res) {
		for(auto ver : v) {
			std::cout << ver << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	auto res1 = g.kosaraju();

	for (auto v : res1) {
		for(auto ver : v) {
			std::cout << ver << ' ';
		}
		std::cout << std::endl;
	}
	std::vector<int> sPath =  g.shortestPathBetween2Nodes(0,3);
	for (auto node : sPath) {
		std::cout << node;
	}
//       	std::cout << g.countAllPathsBetween2Nodes(0,5);	
//	std::cout << std::endl;
	//std::cout << std::boolalpha << g.isCyclic() << std::endl;
	//std::cout << g.connectedComponents() << std::endl;
}

