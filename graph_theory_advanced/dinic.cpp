#include "graph_theory_advanced.h"

void draw_edge_residual(int from, int to, string color, string dirr[MAXN][MAXN], int add) {
    if (f[from][to] == c[from][to]) {
        drawQ.removeEdgeWeighted(add + from, add + to);
        return;
    }
    if (c[from][to] > 0) {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(nf[from][to]) + "/" + to_string(c[from][to] - f[from][to]), dirr[from][to], true);
    }
    else if (f[to][from] == c[to][from] && c[to][from] > 0) {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(nf[from][to]) + "/" + to_string(c[from][to] - f[from][to]), dirr[from][to], true);
    }
    else {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(nf[from][to]) + "/" + to_string(c[from][to] - f[from][to]), dirr[from][to], true, curve[from][to]);
    }
}

struct edge{
    int a, b, c, flow;
    edge(int a, int b, int c, int flow) : a(a), b(b), c(c), flow(flow) {}
};

int ptr[MAXN];
vector<edge> edgelist;
#define edges oldedges
vector<int> edges[MAXN];

bool bfs_dinic(int s, int t) {
    queue<int> q;
    q.push(s);
    dis[s] = 0;

    while (!q.empty() && dis[t] == -1) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < edges[v].size(); i++) {
            int ind = edges[v][i],
            next = edgelist[ind].b;

            if (dis[next] == -1 && edgelist[ind].flow < edgelist[ind].c) {
                q.push(next);
                dis[next] = dis[v] + 1;
            }
        }
    }

    for (int i = 0; i < edgelist.size(); i++) {
        int a = edgelist[i].a;
        int b = edgelist[i].b;
        int c = edgelist[i].c;
        int flow = edgelist[i].flow;
        if (dis[b] == dis[a] + 1 && dis[a] != -1) {
            draw_edge_residual(a, b, "blue", dirr, 10);
        }
    }

    return dis[t] != -1;
}

int dfs_dinic(int v, int t, int flow) {
    if (!flow) {
        return 0;
    }

    if (v == t) {
        return flow;
    }

    for (; ptr[v] < (int) edges[v].size(); ptr[v]++) {
        int ind = edges[v][ptr[v]];
        int next = edgelist[ind].b;

        if (dis[next] != dis[v] + 1) {
            continue;
        }

        int pushed = dfs_dinic(next, t, min(flow, edgelist[ind].c - edgelist[ind].flow));

        if (pushed) {
            edgelist[ind].flow += pushed;
            edgelist[ind ^ 1].flow -= pushed;
            nf[v][next] += pushed;
            nf[next][v] -= pushed;
            draw_edge_residual(v, next, "red", dirr, 10);
            return pushed;
        }
    }

    return 0;
}

long long dinic_flow(int n, int s, int t) {
    long long flow = 0;

    cerr << "!";
    while (true) {
        fill(dis, dis + n, - 1);

        if (!bfs_dinic(s, t)) {
            break;
        }

        drawQ.increaseTimer();

        fill(ptr, ptr + n, 0);

        while (int pushed = dfs_dinic(s, t, INF)) {
            flow += pushed;
        }

        for (int i = 0; i < edgelist.size(); i++) {
            int a = edgelist[i].a;
            int b = edgelist[i].b;
            int c = edgelist[i].c;
            int flow = edgelist[i].flow;
            if (c == 0) {
                continue;
            }
            if (flow > f[a][b]) {
                drawQ.addEdgeWeighted(a, b, "red", "\\footnotesize " + to_string(flow) + "/" + to_string(c), dirf[a][b], true);
            }
            else {
                drawQ.addEdgeWeighted(a, b, "black", "\\footnotesize " + to_string(flow) + "/" + to_string(c), dirf[a][b], true);
            }
        }

        drawQ.increaseTimer();

        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++)
            nf[i][j] = 0;

        for (int i = 0; i < edgelist.size(); i++) {
            int a = edgelist[i].a;
            int b = edgelist[i].b;
            int c = edgelist[i].c;
            int flow = edgelist[i].flow;
            f[a][b] = flow;
            draw_edge_residual(a, b, "black", dirr, 10);
        }
    }
    return flow;
}

void dinic_addedge(int a, int b, int c) {
    edges[a].push_back((int) edgelist.size());
    edgelist.push_back(edge(a, b, c, 0));
    edges[b].push_back((int) edgelist.size());
    edgelist.push_back(edge(b, a, 0, 0));
}

void solve() {
    c[0][1] = 3;
    dirf[0][1] = "near start, above,";
    dirr[0][1] = "near start, above,";
    dirr[1][0] = "midway, left,";
    curve[1][0] = ".. controls (6, 4.5) ..";
    c[0][2] = 3;
    dirf[0][2] = "near start, below,";
    dirr[0][2] = "near start, below,";
    dirr[2][0] = "near start, below,";
    curve[2][0] = ".. controls (6, 2.5) ..";
    c[1][2] = 2;
    dirf[1][2] = "midway, right,";
    dirr[1][2] = "midway, right,";
    c[1][3] = 3;
    dirf[1][3] = "midway, above,";
    dirr[1][3] = "midway, above,";
    dirr[3][1] = "midway, above,";
    curve[3][1] = ".. controls (8.4, 5.25) ..";
    c[2][4] = 2;
    dirf[2][4] = "midway, below,";
    dirr[2][4] = "midway, below,";
    dirr[4][2] = "midway, below,";
    c[3][4] = 4;
    dirf[3][4] = "midway, right,";
    dirr[3][4] = "midway, right,";
    dirr[4][3] = "midway, left,";
    curve[4][3] = ".. controls (8.75, 3.5) ..";
    c[3][5] = 2;
    dirf[3][5] = "near end, above,";
    dirr[3][5] = "near end, above,";
    dirr[5][3] = "near start, above,";
    c[4][5] = 3;
    dirf[4][5] = "near end, below,";
    dirr[4][5] = "near end, below,";
    dirr[5][4] = "midway, right,";
    curve[5][4] = ".. controls (10.75, 2.5) ..";

    dinic_addedge(0, 1, 3);
    dinic_addedge(0, 2, 3);
    dinic_addedge(1, 2, 2);
    dinic_addedge(1, 3, 3);
    dinic_addedge(2, 4, 2);
    dinic_addedge(3, 4, 4);
    dinic_addedge(3, 5, 2);
    dinic_addedge(4, 5, 3);

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (c[i][j] > 0) {
                drawQ.addEdgeWeighted(i, j, "black", "\\footnotesize 0/" + to_string(c[i][j]), dirf[i][j], true);
                drawQ.addEdgeWeighted(10 + i, 10 + j, "black", "\\footnotesize 0/" + to_string(c[i][j]), dirr[i][j], true);
            }
        }
    }

    dinic_flow(6, 0, 5);

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (c[i][j] > 0 && f[i][j] > 0) {
                drawQ.addEdgeWeighted(i, j, "red", "\\footnotesize " + to_string(f[i][j]) + "/" + to_string(c[i][j]), dirf[i][j], true);
            }
        }
    }
}

int main() {
    solve();

    drawQ.draw();
}
