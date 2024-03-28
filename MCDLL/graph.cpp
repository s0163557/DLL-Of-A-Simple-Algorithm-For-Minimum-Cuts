// Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
#include "graph.h"
#include <vector>
using namespace std;
/*
// This is an example of an exported variable
MCDLL_API int nMCDLL=0;

// This is an example of an exported function.
MCDLL_API int fnMCDLL(void)
{
    return 0;
}
*/

edge::edge(int _u, int _v, int _idx, double _w) { u = _u, v = _v, idx = _idx, w = _w; }

graph::graph(int _n, int _m, vector<edge*>& _E)
{
	n = _n, m = _m, E = _E;
	adj.clear(); adj.resize(n);
	for (auto it : E) adj[it->u].push_back(it), adj[it->v].push_back(it);
}

tree::tree(int _n, vector<edge*>& _E) : graph(_n, _n - 1, _E) { }
