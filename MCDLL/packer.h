#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

#include <vector>
#include <queue>
using namespace std;

class tree;
class packeredge;
const double eps = 1 / 5.0;

class MCDLL_API packergraph
{
public:
	int n, m;
	vector<packeredge*> E;
	packergraph(int _n, int _m, vector<packeredge*>& _E);
	~packergraph();
};

class MCDLL_API packeredge
{
public:
	int u, v, idx;
	priority_queue<double> l;
	packeredge(int _u, int _v, int _idx, priority_queue<double>& _l);
	~packeredge(void);
};

static inline int root(int x, vector<int>& P);
MCDLL_API void dsu(int x, int y, vector<int>& P, vector<int>& sz);
MCDLL_API pair<double, vector<tree*>> packer(packergraph* G);
