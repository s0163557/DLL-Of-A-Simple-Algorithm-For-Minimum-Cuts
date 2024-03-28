#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

#include<vector>
using namespace std;

class tree;
typedef long long int lli;

class MCDLL_API lemma8ds
{
public:
	const lli inf = lli(1e12) + 5;
	tree* T;
	int curst = 0, totchain = 0, maxlog;
	double totdelta = 0;
	vector<int> sz, H, inchain, inst, head;
	vector<double> st, lz, val;
	vector<vector<int>> jmp;
	lemma8ds(tree* _T);
	void build(int node, int L, int R);
	inline int left(int node);
	inline int right(int node);
	void shift(int node, int L, int R);
	void upd(int node, int L, int R, int a, int b, double v);
	double qry(int node, int L, int R, int a, int b);
	void dfs0(int node, int par, int ht);
	void dfs1(int node, int par, int chain, double inc);
	void init();
	void pathupd(int x, int y, double delta);
	void ancestryupd(int node, int anc, double delta);
	void PathAdd(int u, int v, double x);
	void NonPathAdd(int u, int v, double x);
	double QueryMinimum();
	double QueryEdge(int node);
};