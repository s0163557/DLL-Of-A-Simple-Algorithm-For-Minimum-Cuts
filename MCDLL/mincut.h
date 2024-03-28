#include <vector>
using namespace std;

#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

class graph;
class tree;
class lemma8ds;

class MCDLL_API mincut
{
public:
	const double inf = 1e12 + 5;
	tree* T;
	graph* G;
	lemma8ds* D;
	int totchain = 0, maxlog;
	vector<int> sz, H, inchain, inst, head, st;
	vector<double> val;
	vector<vector<int>> jmp;
	mincut(graph* _G, tree* _T);
	void clear();
	void dfs0(int node, int par, int ht);
	void dfs1(int node, int par, int chain, double inc);
	void init();
	vector<pair<int, int>> pathbreakdown(int x, int y);
	vector<pair<int, int>> ancestrybreakdown(int node, int anc);
	double compute();
};