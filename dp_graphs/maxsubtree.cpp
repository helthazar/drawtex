#include "dp_graphs.h"

int dp[MAXN];

void dfs_maxsubtree(int v, int p = -1){
    used[v] = 1;
    dp[v] = 0;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, "0", -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
    // if (v != 1 && v != 4)
    //     drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        int cost = costs[v][i];

        if (!used[next]) {
            drawQ.addEdgeWeighted(v, next, "red", to_string(cost), dir[v][next], true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs_maxsubtree(next, v);
            dp[v] += max(0, cost + dp[next]);
            drawQ.addRectangleNode(6 + v, to_string(dp[v]), -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
            drawQ.addEdgeWeighted(v, next, "black", "\\footnotesize " + to_string(cost), dir[v][next]);
            // drawQ.increaseTimer();
        }
    }
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void dfs_draw_maxsubtree(int v, int p = -1){
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw = red, thick, text = white");

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        int cost = costs[v][i];

        if (dir[v][next] != "" && dp[next] + cost >= 0) {
            drawQ.addEdgeWeighted(v, next, "red", "\\footnotesize " + to_string(cost), dir[v][next]);
            dfs_draw_maxsubtree(next, v);
        }
    }
}

int maxsubtree(int n) {
    dfs_maxsubtree(0);
    drawQ.increaseTimer();

    int r = 0;
    for (int i = 0; i < n; i++) {
        if (dp[r] < dp[i]) {
            r = i;
        }
    }

    drawQ.addCircleNode(r, to_string(r), x[r], y[r], "darkgray", "draw, text = white");
    drawQ.addRectangleNode(6 + r, to_string(dp[r]), -1.5 + 0.5 * r, -0.5, "darkgray", "draw", 2.0, "text = white");
    drawQ.increaseTimer();

    dfs_draw_maxsubtree(r);

    return dp[r];
}

void solve() {
    edges[0].push_back(1);
    d[0][1] = d[1][0] = -3;
    dir[0][1] = "near start, left,";
    edges[0].push_back(2);
    d[0][2] = d[2][0] = 1;
    dir[0][2] = "near start, right,";
    edges[1].push_back(3);
    d[1][3] = d[3][1] = 3;
    dir[1][3] = "near start, left,";
    edges[1].push_back(4);
    d[1][4] = d[4][1] = -2;
    dir[1][4] = "near start, right,";
    edges[4].push_back(5);
    d[4][5] = d[5][4] = 5;
    dir[4][5] = "near start, left,";

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            if (next > i) {
                edges[next].push_back(i);
            }
        }
        sort(edges[i].begin(), edges[i].end());
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            costs[i].push_back(d[next][i]);
        }
    }

    for (int i = 0; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "0", -1.5 + 0.5 * i, -0.5, "white", "draw");
    }

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            int cost = costs[i][j];
            if (dir[i][next] != "") {
                drawQ.addEdgeWeighted(i, next, "black", "\\footnotesize " + to_string(cost), dir[i][next], true);
            }
        }
    }

    maxsubtree(6);
}

int main() {
    solve();

    drawQ.draw();
}
