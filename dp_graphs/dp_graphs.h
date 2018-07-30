#include "draw_queue.h"

drawQueue drawQ;

double x[] = {0, -0.6, 0.6, -1.2, 0, -0.6};
double y[] = {4, 3, 3, 2, 2, 1};

const int MAXN = 100;

vector<int> edges[MAXN];
vector<int> costs[MAXN];
int used[MAXN];

string dir[MAXN][MAXN];
int d[MAXN][MAXN];

string curve[MAXN][MAXN];
