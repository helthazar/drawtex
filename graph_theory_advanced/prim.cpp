#include "graph_theory_advanced.h"

void prim(int s, int n) {
    fill(from, from + n + 1, - 1);
    fill(dis, dis + n + 1, INF);
    dis[s] = 0;
    from[s] = s;

    while (1) {
        int cur = - 1;
        for (int i = 0; i <= n; i++) {
            if (used[i]) continue;
            if (cur == -1 || dis[cur] > dis[i])
                cur = i;
        }

        if (cur == -1 || dis[cur] == INF)
            break;
        used[cur] = 1;

        drawQ.addRectangleNode(10 + cur, to_string(dis[cur]), -1.5 + 0.5 * cur, 0, "lightgray", "draw");
        drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], "lightgray", "draw = blue, thick");
        drawQ.addRectangleNode(5 + cur, "1", -1.5 + 0.5 * cur, 1, "lightgray", "draw");

        for (int i = 0; i < edges[cur].size(); i++) {
            int next = edges[cur][i];

            if (dis[next] > d[cur][next]) {
                if (from[next] != -1) {
                    drawQ.addEdgeWeighted(from[next], next, "black", to_string(d[from[next]][next]), dir[from[next]][next]);
                }

                drawQ.addCircleNode(next, to_string(next), x[next], y[next], "lightgray", "draw = red, thick");
                drawQ.addEdgeWeighted(cur, next, "blue", "\\footnotesize " + to_string(d[cur][next]), dir[cur][next]);
            }
        }

        drawQ.increaseTimer();
        drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], "lightgray", "draw = red, thick");

        for (int i = 0; i < edges[cur].size(); i++) {
            int next = edges[cur][i];

            if (dis[next] > d[cur][next]) {
                from[next] = cur;
                dis[next] = d[cur][next];

                drawQ.addRectangleNode(10 + next, to_string(dis[next]), -1.5 + 0.5 * next, 0, "lightgray", "draw");
                drawQ.addEdgeWeighted(cur, next, "red", "\\footnotesize " + to_string(d[cur][next]), dir[cur][next]);
            }
        }
    }
}

void solve() {
    vector<pair<int, int> > vp = {{0, 2}, {0, 3}, {1, 2}, {2, 4}, {3, 2}, {3, 4}, {4, 1}};
    d[0][2] = 7;
    dir[0][2] = "near end, above,";
    d[0][3] = 5;
    dir[0][3] = "midway, above,";
    d[1][2] = 1;
    dir[1][2] = "near start, above,";
    d[2][4] = 9;
    dir[2][4] = "near end, above,";
    d[3][2] = 6;
    dir[3][2] = "near end, above,";
    d[3][4] = 2;
    dir[3][4] = "midway, right,";
    d[4][1] = 4;
    dir[4][1] = "midway, above,";
    for (int i = 0; i < vp.size(); i++) {
        edges[vp[i].first].push_back(vp[i].second);
    }

    for (int i = 0; i <= 4; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(5 + i, "0", -1.5 + 0.5 * i, 1, "white", "draw");
        drawQ.addRectangleNode(10 + i, "\\tiny $\\infty$", -1.5 + 0.5 * i, 0, "white", "draw");
    }

    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdgeWeighted(i, next, "black", "\\footnotesize " + to_string(d[i][next]), dir[i][next]);
        }
    }

    prim(0, 4);
}

int main() {
    solve();

    drawQ.draw();
}
