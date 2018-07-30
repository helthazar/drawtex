#include "draw_queue.h"

drawQueue drawQ;

double x[] = {-1.75, -1.75, -0.5, 0.75, 0.75};
double y[] = {4.5, 2.75, 3.6, 4.5, 2.75};

const int MAXN = 100;

int d[MAXN][MAXN];

vector<int> edges[MAXN];
vector<int> costs[MAXN];

int used[MAXN];
int dis[MAXN];
int from[MAXN];

string dir[MAXN][MAXN];

const int INF = 100000000;

int f[MAXN][MAXN];
int c[MAXN][MAXN];
string dirf[MAXN][MAXN];
string dirr[MAXN][MAXN];
string curve[MAXN][MAXN];
int nf[MAXN][MAXN];
