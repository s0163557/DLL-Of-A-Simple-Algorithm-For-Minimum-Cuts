#include"pch.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include "graph.h"
#include "packer.h"
#include "framework.h"
using namespace std;

packeredge::packeredge(int _u, int _v, int _idx, priority_queue<double>& _l) { u = _u, v = _v, idx = _idx, l = _l; }

packergraph::packergraph(int _n, int _m, vector<packeredge*>& _E)
{
	n = _n, m = _m, E = _E;
}

static inline int root(int x, vector<int>& P) { return (P[x] == x) ? x : (P[x] = root(P[x], P)); }

void dsu(int x, int y, vector<int>& P, vector<int>& sz)
{
	x = root(x, P);
	y = root(y, P);
	if (sz[x] > sz[y]) 
		swap(x, y);
	P[x] = y;
	sz[y] += sz[x];
}

// Algorithm 1: Given an unweighted, undirected graph, compute packing of weight at least .4c
pair<double, vector<tree*>> packer(packergraph* G)
{
	double W = 0;
	vector<vector<packeredge*>> packerEdges;

	vector<int> P(G->n), sz(G->n);
	vector<pair<int, int>> sorter(G->m);
	vector<packeredge*> href(G->m);
	for (auto it : G->E) href[it->idx] = it;
	while (true)
	{
		for (auto it : G->E) sorter[it->idx] = { -it->l.top(), it->idx };
		sort(sorter.begin(), sorter.end());
		vector<packeredge*> T;
		for (int i = 0; i < G->n; i++) P[i] = i, sz[i] = 1;
		for (auto idx : sorter)
		{
			auto it = href[idx.second];
			int a = it->u, b = it->v;
			if (root(a, P) != root(b, P))
			{
				dsu(a, b, P, sz);
				T.emplace_back(it);
				double newl = -it->l.top() + (eps * eps) / (3.0 * log(G->m));
				if (newl > 1)
				{
					pair<double, vector<tree*>> res;
					res.first = W;
					for (auto kt : packerEdges)
					{
						vector<edge*> tmpedges;
						for (auto gt : kt)
						{
							edge* tmp = new edge(gt->u, gt->v, gt->idx, 0);
							tmpedges.emplace_back(tmp);
						}

						tree* tmp = new tree(G->n, tmpedges);
						res.second.emplace_back(tmp);
					}

					return res;
				}

				it->l.pop();
				it->l.emplace(-newl);
			}
		}

		packerEdges.emplace_back(T);
		W += (eps * eps) / (3.0 * log(G->m));
	}
}
packergraph::~packergraph(){}
packeredge::~packeredge(){}