#pragma once
#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <cstdlib>
#include <algorithm>
#include "graph.h"
#include "tworespectingtrees.h"
#include "lemma8ds-slow.h"
#include "mincut.h"
#include "main.h"
#include "framework.h"
using namespace std;
// Read tree from stdin
// Format:
// n
// u_1 v_1 idx_1 w_1
// u_2 v_2 idx_2 w_2
// .
// .
// .
// u_{n-1} v_{n-1} idx_{n-1} w_{n-1}
tree* tree_reader()
{
	int n;
	scanf_s("%d", &n);
	vector<edge*> E;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v, idx;
		double c;
		scanf_s("%d%d%d%lf", &u, &v, &idx, &c);
		//u--, v--;
		//cout << u << " " << v << " " << c << "\n";
		edge* tmp = new edge(u, v, idx, c);
		E.emplace_back(tmp);
	}

	tree* res = new tree(n, E);
	return res;
}

void tester_lemma8ds()
{
	tree* T = tree_reader();
	lemma8ds D(T);

	int m;
	scanf_s("%d", &m);

	while (m--)
	{
		int t, u, v;
		double x;
		scanf_s("%d", &t);
		if (t == 0) printf("%lf\n", D.QueryMinimum());
		else if (t == 1)
		{
			scanf_s("%d%d%lf", &u, &v, &x);
			D.PathAdd(u, v, x);
		}
		else if (t == 2)
		{
			scanf_s("%d%d%lf", &u, &v, &x);
			D.NonPathAdd(u, v, x);
		}
	}
}

double tester(graph* G, double d)
{
	vector<tree*> trees = tworespectingtrees(d, G);
	//printf("%d\n", int(trees.size()));

	// Fix wts using edge index
	for (auto it : trees)
	{
		for (auto gt : it->E)
		{
			gt->w = G->E[gt->idx]->w;
			//cout << gt->u << " " << gt->v << " " << gt->idx << " " << gt->w << "\n";
		}
		//cout << "\n";
	}

	//vector<ptree> trees;
	//trees.push_back(tree_reader());

	double res = double(1e9) + 5;
	for (auto it : trees)
	{
		mincut mc(G, it);
		res = min(res, mc.compute());
		mc.clear();
	}

	for (auto it : trees)
	{
		for (auto gt : it->E) delete(gt);
		delete(it);
	}
	for (auto it : G->E) delete(it);
	delete(G);

	return res;
}

// Read graph from stdin
// Format:
// n m
// u_1 v_1 w_1
// u_2 v_2 w_2
// .
// .
// .
// u_m v_m w_m
graph* graph_reader(int n, int m, int* edges)
{
	vector<edge*> E;
	for (int i = 0; i < m * 3; i+=3)
	{
		int u, v;
		double c;
		//Четвертая переменная - вес, но нам все равно потмоу что наш граф не взвешен
		edge* tmp = new edge(edges[i], edges[i+1], i / 3, edges[i+2]);
		E.emplace_back(tmp);
	}

	graph* res = new graph(n, m, E);
	return res;
}

extern "C" double MinCutStart(int n, int m, int* edges, double d)
{
	srand(time(NULL));
	/*
	for (int i = 0; i < m*3; i+=3)
		printf("%d: %d-%d-%d\n", i/3, edges[i], edges[i+1], edges[i+2]);
		*/
	graph* G = graph_reader(n, m, edges);
	return tester(G, d);
}