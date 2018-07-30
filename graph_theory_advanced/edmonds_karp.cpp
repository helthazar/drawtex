#include "graph_theory_advanced.h"

void draw_edge_residual(int from, int to, string color, string dirr[MAXN][MAXN], int add) {
    if (f[from][to] == c[from][to]) {
        drawQ.removeEdgeWeighted(add + from, add + to);
        return;
    }
    if (c[from][to] > 0) {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(c[from][to] - f[from][to]), dirr[from][to], true);
    }
    else if (f[to][from] == c[to][from] && c[to][from] > 0) {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(c[from][to] - f[from][to]), dirr[from][to], true);
    }
    else {
        drawQ.addEdgeWeighted(add + from, add + to, color, "\\footnotesize " + to_string(c[from][to] - f[from][to]), dirr[from][to], true, curve[from][to]);
    }
}

void edmonds_karp(int s, int t, int n) {
    while (true) {
        vector<int> from(n, -1);
        queue<int> q;
        q.push(s);
        from[s] = s;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int next = 0; next < n; next++) {
                if (from[next] == -1 && c[cur][next] - f[cur][next] > 0) {
                    q.push(next);
                    from[next] = cur;
                }
            }
        }

        if (from[t] == -1)
            break;

        int cf = 100;
        for (int cur = t; cur != s; ) {
            int prev = from[cur];
            cf = min(cf, c[prev][cur] - f[prev][cur]);
            draw_edge_residual(prev, cur, "red", dirr, 10);
            cur = prev;
        }
        for (int cur = t; cur != s; ) {
            int prev = from[cur];
            f[prev][cur] += cf;
            f[cur][prev] -= cf;
            if (c[prev][cur] > 0) {
                drawQ.addEdgeWeighted(prev, cur, "red", "\\footnotesize " + to_string(f[prev][cur]) + "/" + to_string(c[prev][cur]), dirf[prev][cur], true);
            }
            if (c[cur][prev] > 0) {
                drawQ.addEdgeWeighted(cur, prev, "red", "\\footnotesize " + to_string(f[cur][prev]) + "/" + to_string(c[cur][prev]), dirf[cur][prev], true);
            }
            cur = prev;
        }

        drawQ.increaseTimer();
        for (int cur = t; cur != s; ) {
            int prev = from[cur];
            if (c[prev][cur] > 0) {
                drawQ.addEdgeWeighted(prev, cur, "black", "\\footnotesize " + to_string(f[prev][cur]) + "/" + to_string(c[prev][cur]), dirf[prev][cur], true);
            }
            if (c[cur][prev] > 0) {
                drawQ.addEdgeWeighted(cur, prev, "black", "\\footnotesize " + to_string(f[cur][prev]) + "/" + to_string(c[cur][prev]), dirf[cur][prev], true);
            }
            draw_edge_residual(prev, cur, "black", dirr, 10);
            draw_edge_residual(cur, prev, "black", dirr, 10);
            cur = prev;
        }
    }
}

void solve() {
    c[0][1] = 3;
    dirf[0][1] = "near start, above,";
    dirr[0][1] = "midway, above,";
    dirr[1][0] = "midway, above,";
    curve[1][0] = ".. controls (6, 4.5) ..";
    c[0][2] = 3;
    dirf[0][2] = "near start, below,";
    dirr[0][2] = "midway, below,";
    dirr[2][0] = "midway, below,";
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
    dirf[3][4] = "midway, left,";
    dirr[3][4] = "midway, left,";
    dirr[4][3] = "midway, left,";
    curve[4][3] = ".. controls (8.75, 3.5) ..";
    c[3][5] = 2;
    dirf[3][5] = "near end, above,";
    dirr[3][5] = "midway, above,";
    dirr[5][3] = "midway, above,";
    c[4][5] = 3;
    dirf[4][5] = "near end, below,";
    dirr[4][5] = "midway, below,";
    dirr[5][4] = "midway, below,";
    curve[5][4] = ".. controls (10.75, 2.5) ..";

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (c[i][j] > 0) {
                drawQ.addEdgeWeighted(i, j, "black", "\\footnotesize 0/" + to_string(c[i][j]), dirf[i][j], true);
                drawQ.addEdgeWeighted(10 + i, 10 + j, "black", "\\footnotesize " + to_string(c[i][j]), dirr[i][j], true);
            }
        }
    }

    drawQ.increaseTimer();

    edmonds_karp(0, 5, 6);

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (c[i][j] > 0 && f[i][j] > 0) {
                drawQ.addEdgeWeighted(i, j, "red", "\\footnotesize " + to_string(f[i][j]) + "/" + to_string(c[i][j]), dirf[i][j], true);
            }
        }
    }
      for (int j = 0; j <= 5; j++) {
          if (c[0][j] > 0 && f[0][j] < c[0][j]) {
            draw_edge_residual(0, j, "red", dirr, 10);
          }
      }
}

int main() {
    solve();

    drawQ.draw();
}
