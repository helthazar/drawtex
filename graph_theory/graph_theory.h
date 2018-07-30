#include "draw_queue.h"

drawQueue drawQ;

double x[] = {0, 0, -0.5, 0.5, -1, 1, 0};
double y[] = {0, 4.25, 3, 3, 2, 2, 1};

const int MAXN = 100;

vector<int> edges[MAXN];
int used[MAXN];

int from[MAXN];

int tin[MAXN], fout[MAXN];

int timer = 1;

vector<int> topsort;
