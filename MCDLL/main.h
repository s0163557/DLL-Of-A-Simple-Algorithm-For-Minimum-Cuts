#ifdef MCDLL_EXPORTS
#define MCDLL_API __declspec(dllexport)
#else
#define MCDLL_API __declspec(dllimport)
#endif

#include <utility>
#include <vector>
using namespace std;

class graph;
class tree;

extern "C" MCDLL_API double MinCutStart(int n, int m, int* edges, double d);
MCDLL_API void tester_lemma8ds();
MCDLL_API double tester(graph* G, double d);
MCDLL_API tree* tree_reader();
MCDLL_API graph * graph_reader(int n, int m, int* edges);
