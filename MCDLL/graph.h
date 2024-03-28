#include <vector>
using namespace std;

#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

class edge;

// This class is exported from the dll
class MCDLL_API graph {
public:
	int n, m;
	vector<vector<edge*>> adj;
	vector<edge*> E;
	graph(int _n, int _m, vector<edge*>& _E);

};

class MCDLL_API edge
{
public:
	int u, v, idx;
	double w;
	edge(int _u, int _v, int _idx, double _w);
};

class MCDLL_API tree : public graph
{
public:
	tree(int _n, vector<edge*>& _E);
};
/*
extern MCDLL_API int nMCDLL;

MCDLL_API int fnMCDLL(void);
*/