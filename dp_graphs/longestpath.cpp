#include "dp_graphs.h"

int dp[MAXN];

void dfs_longestpath(int v, int p = -1){
    used[v] = 1;
    dp[v] = 0;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, "0", -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
    if (v != 1 && v != 4)
        drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs_longestpath(next, v);
            dp[v] = max(dp[v], dp[next] + 1);
            drawQ.addRectangleNode(6 + v, to_string(dp[v]), -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
            drawQ.addEdge(v, next, "black");
            drawQ.increaseTimer();
        }
    }
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void dfs_draw_longestpath(int v, int p = -1){
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw = red, thick, text = white");

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];

        if (dp[next] == dp[v] - 1) {
            drawQ.addEdge(v, next, "red");
            dfs_draw_longestpath(next, v);
            return;
        }
    }
}

int longestpath(int r) {
    dfs_longestpath(r);

    drawQ.addCircleNode(r, to_string(r), x[r], y[r], "darkgray", "draw, text = white");
    drawQ.addRectangleNode(6 + r, to_string(dp[r]), -1.5 + 0.5 * r, -0.5, "darkgray", "draw", 2.0, "text = white");
    drawQ.increaseTimer();

    dfs_draw_longestpath(r);

    return dp[r];
}

void solve() {
    edges[0].push_back(1);
    edges[0].push_back(2);
    edges[1].push_back(3);
    edges[1].push_back(4);
    edges[4].push_back(5);

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            if (next > i) {
                edges[next].push_back(i);
            }
        }
        sort(edges[i].begin(), edges[i].end());
    }

    for (int i = 0; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "0", -1.5 + 0.5 * i, -0.5, "white", "draw");
    }

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    longestpath(0);
}

int main() {
    solve();

    drawQ.draw();
}
