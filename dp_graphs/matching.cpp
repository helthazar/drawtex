#include "dp_graphs.h"

int dp[MAXN][2];

void dfs_matching(int v, int p = -1){
    used[v] = 1;
    dp[v][0] = dp[v][1] = 0;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, "0", -1.5 + 0.5 * v, -1.5, "lightgray", "draw");
    // if (v != 1 && v != 4)
        // drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs_matching(next, v);
            dp[v][0] += max(dp[next][0], dp[next][1]);
            drawQ.addRectangleNode(6 + v, to_string(dp[v][0]), -1.5 + 0.5 * v, -1.5, "lightgray", "draw");
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
            drawQ.addEdge(v, next, "black");
            // drawQ.increaseTimer();
        }
    }

    drawQ.decreaseTimer();
    drawQ.addRectangleNode(12 + v, "0", -1.5 + 0.5 * v, -2, "lightgray", "draw");

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        if (next != p) {
            dp[v][1] = max(dp[v][1], 1 + dp[next][0] + dp[v][0] -
                                 max(dp[next][0], dp[next][1]));
        }
    }
    drawQ.addRectangleNode(12 + v, to_string(dp[v][1]), -1.5 + 0.5 * v, -2, "lightgray", "draw");
    drawQ.increaseTimer();
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void dfs_draw_matching(int v, int p = -1, bool matched = false){
    int nextmatched = -1;
    if (!matched && dp[v][0] < dp[v][1]) {
        for (int i = 0; i < edges[v].size(); i++){
            int next = edges[v][i];

            if (dir[v][next] != "" && dp[v][1] == 1 + dp[next][0] + dp[v][0] -
                                 max(dp[next][0], dp[next][1])) {
                nextmatched = next;
                break;
            }
        }
    }
    if (matched || nextmatched != -1) {
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw = red, thick, text = white");
    }
    else {
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
    }

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];

        if (dir[v][next] == "") {
            continue;
        }
        if (next == nextmatched) {
            drawQ.addEdge(v, next, "red");
            dfs_draw_matching(next, v, true);
        }
        else {
            dfs_draw_matching(next, v, false);
        }
    }
}

int matching(int r) {
    dfs_matching(r);
    drawQ.increaseTimer();

    int ri = (dp[r][0] >= dp[r][1]) ? 0 : 1;
    drawQ.addCircleNode(r, to_string(r), x[r], y[r], "darkgray", "draw, text = white");
    drawQ.addRectangleNode(6 + r + 6 * ri, to_string(dp[r][ri]), -1.5 + 0.5 * r, -1.5 - 0.5 * ri, "darkgray", "draw", 2.0, "text = white");
    drawQ.increaseTimer();

    dfs_draw_matching(r);

    return max(dp[r][0], dp[r][1]);
}

void solve() {
    edges[0].push_back(1);
    dir[0][1] = "x";
    edges[0].push_back(2);
    dir[0][2] = "x";
    edges[1].push_back(3);
    dir[1][3] = "x";
    edges[1].push_back(4);
    dir[1][4] = "x";
    edges[4].push_back(5);
    dir[4][5] = "x";

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
        drawQ.addRectangleNode(6 + i, "0", -1.5 + 0.5 * i, -1.5, "white", "draw");
        drawQ.addRectangleNode(12 + i, "0", -1.5 + 0.5 * i, -2, "white", "draw");
    }

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    matching(0);
}

int main() {
    solve();

    drawQ.draw();
}
