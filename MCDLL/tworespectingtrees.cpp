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
#include <queue>
#include "graph.h"
#include "packer.h"
#include "tworespectingtrees.h"
#include "framework.h"
using namespace std;

double compute_U(const graph* G)
{
	double res = inf;
	for (auto it : G->adj)
	{
		double tmp = 0;
		for (auto gt : it) tmp += gt->w;
		res = min(res, tmp);
	}
	return res;
}

// inverse transform sampling in O(ceil) time
lli binom(lli trials, long double p, lli ceil)
{
	if (p > 1 - cmpeps)
		return trials;

	uniform_real_distribution<double> distribution(0.0, 1.0);
	double u = distribution(generator);

	long double prob = pow(1 - p, trials);
	long double cum_prob = prob;
	for (int i = 0; i <= ceil; ++i) {
		if (cum_prob >= u - cmpeps) {
			return i;
		}
		prob *= (long double)(trials - i) / (i + 1) * p / (1 - p);
		cum_prob += prob;
	}

	return ceil;
}

vector<tree*> sample(const vector<tree*>& packing, double d, int n)
{
	uniform_int_distribution<int> distribution(0, int(packing.size()) - 1);
	vector<tree*> res;
	vector<bool> marker(int(packing.size()));
	int req = ceil(-d * log(n) / log(1 - f));
	for (int i = 0; i < req; i++)
	{
		int tmp = distribution(generator);
		marker[tmp] = 1;
		res.emplace_back(packing[tmp]);
	}

	for (int i = 0; i < int(packing.size()); i++)
	{
		if (!marker[i])
		{
			for (auto it : packing[i]->E) delete(it);
			delete(packing[i]);
		}
	}

	return res;
}

// Algorithm 2: Obtain spanning trees with probability of success 1 − 1/(G->n)^d
vector<tree*> tworespectingtrees(double d, graph* _G)
{
	vector<tree*> res;
	vector<edge*> Edash;
	double normaliser = inf;
	for (auto it : _G->E)
	{
		if (it->w >= cmpeps) normaliser = min(normaliser, it->w);
	}

	normaliser = 1.0 / normaliser;
	for (auto it : _G->E)
	{
		auto tmp = new edge(it->u, it->v, it->idx, it->w * normaliser);
		Edash.emplace_back(tmp);
	}
	graph* Gdash = new graph(_G->n, _G->m, Edash);

	double b = 3.0 * (d + 2.0) * log(Gdash->n) / (eps2 * eps2);

	for (auto it : Gdash->E)
	{
		it->w = round(it->w * (1 / eps1));
	}
	double c = compute_U(Gdash);
	bool lastrun = 0;
	vector<packeredge*> HE;
	vector<packeredge*> href(Gdash->m);

	priority_queue<double> tmpl;
	for (auto it : Gdash->E)
	{
		auto tmp = new packeredge(it->u, it->v, it->idx, tmpl);
		HE.emplace_back(tmp);
		href[it->idx] = HE.back();
	}
	packergraph* H = new packergraph(Gdash->n, Gdash->m, HE);

	while (true)
	{
		//cout << c << " " << lastrun << " " << b/c << "\n";
		double p = min(1.0, b / c);
		for (auto it : Gdash->E)
		{
			double wt = binom(it->w, p, lli(ceil((1 + eps2) * 12.0 * b)));
			//if(lastrun) cout << it->idx << " " << wt << "\n";
			priority_queue<double> l;
			for (int i = 0; i < wt; i++) l.emplace(0);
			href[it->idx]->l = l;
		}

		H->E = HE;
		pair<double, vector<tree*>> packing = packer(H);

		if (lastrun || p >= 1.0 - cmpeps)
		{
			res = sample(packing.second, d, Gdash->n);
			break;
		}
		else
		{
			for (auto it : packing.second)
			{
				for (auto gt : it->E) delete(gt);
				delete(it);
			}
			if (packing.first >= ((1 - eps3) * b / (2.0 * (1 + eps2))))
			{
				c /= 6.0;
				lastrun = 1;
			}
			else c /= 2.0;
		}
	}
	for (auto it : Edash) delete(it);
	for (auto it : HE) delete(it);
	delete(H);
	delete(Gdash);

	return res;
}
