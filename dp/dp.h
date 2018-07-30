#include "draw_queue.h"

drawQueue drawQ;

double x[] = {0, 0, -1, 1, 0.2};
double y[] = {0, 0, -1.4, -1.4, -2.4};
double s[] = {0, 3, 2, 1.7, 1.5};

int p[] = {4, 3, 2, 1};

double fx[] = {0, 0, -1, 1, -1.5, -0.5, 0.5, 1.5, -2, -1};
double fy[] = {0, 0, -1, -1, -2, -2, -2, -2, -3, -3};
int fl[] = {0, 3, 2, 1, 1, 1, 1, 0, 1, 0};
int fi[] = {0, 4, 3, 2, 2, 1, 1, 0, 1, 0};

const int MAXN = 100;

int dp[MAXN];

vector<int> edges[MAXN];
int used[MAXN];
