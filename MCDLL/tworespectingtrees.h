#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

#include <vector>
#include <random>
using namespace std;

class graph;
class tree;

typedef long long int lli;
const double inf = 1e12 + 5, eps1 = 1.0 / 100.0, eps2 = 1.0 / 6.0, eps3 = 1.0 / 5.0;
const double f = 3 / 2.0 - ((2.0 + eps1) * (1.0 + eps2)) / ((2.0 - eps1) * (1.0 - eps3));
const double cmpeps = 1e-11;
static default_random_engine generator(time(NULL));

MCDLL_API double compute_U(const graph* G);
MCDLL_API lli binom(lli trials, long double p, lli ceil);
MCDLL_API vector<tree*> sample(const vector<tree*>& packing, double d, int n);
MCDLL_API vector<tree*> tworespectingtrees(double d, graph* _G);
