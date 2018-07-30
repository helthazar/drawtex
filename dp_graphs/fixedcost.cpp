#include "dp_graphs.h"

const int MAXC = 10001;
int dp[MAXN][MAXC];

void dfs_fixedcost(int v, int c) {
    if (used[v]) {
        return;
    }
    used[v] = 1;
    dp[v][0] = 1;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v * 5, "1", -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
    // if (v != 1 && v != 3)
    //     drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++) {
        int next = edges[v][i];
        int cost = costs[v][i];

        if (!used[next]) {
            drawQ.addEdgeWeighted(v, next, "red", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs_fixedcost(next, c);
        }

        for (int j = cost; j <= c; j++) {
            dp[v][j] = max(dp[v][j], dp[next][j - cost]);
        }
        for (int j = 0; j <= c; j++) {
            if (dp[v][j] == 1) {
                drawQ.addRectangleNode(6 + v * 5 + j, to_string(dp[v][j]), -1.5 + 0.5 * v, -0.5 - 0.5 * j, "lightgray", "draw");
            }
        }
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
        drawQ.addEdgeWeighted(v, next, "black", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
        // drawQ.increaseTimer();
    }
    // drawQ.decreaseTimer();
    for (int j = 0; j <= c; j++) {
        if (dp[v][j] == 1) {
            drawQ.addRectangleNode(6 + v * 5 + j, to_string(dp[v][j]), -1.5 + 0.5 * v, -0.5 - 0.5 * j, "lightgray", "draw");
        }
    }
    // drawQ.increaseTimer();
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void dfs_draw_fixedcost(int v, int c){
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw = red, thick, text = white");
    if (c == 0) {
        return;
    }

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        int cost = costs[v][i];

        if (cost <= c && dp[next][c - cost]) {
            drawQ.addEdgeWeighted(v, next, "red", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
            dfs_draw_fixedcost(next, c - cost);
        }
    }
}

int fixedcost(int s, int c) {
    dfs_fixedcost(s, c);
    drawQ.increaseTimer();

    drawQ.addCircleNode(s, to_string(s), x[s], y[s], "darkgray", "draw, text = white");
    drawQ.addRectangleNode(6 + s * 5 + c, to_string(dp[s][c]), -1.5 + 0.5 * s, -0.5 - 0.5 * c, "darkgray", "draw", 2.0, "text = white");
    drawQ.increaseTimer();

    if (dp[s][c]) {
        dfs_draw_fixedcost(s, c);
    }

    return dp[s][c];
}

void solve() {
    edges[0].push_back(3);
    costs[0].push_back(5);
    dir[0][3] = "near start, above,";
    curve[0][3] = ".. controls (-1.5, 3.6) ..";
    edges[0].push_back(1);
    costs[0].push_back(2);
    dir[0][1] = "near start, left,";
    curve[0][1] = "--";
    edges[0].push_back(2);
    costs[0].push_back(1);
    dir[0][2] = "near start, right,";
    curve[0][2] = "--";
    edges[1].push_back(3);
    costs[1].push_back(2);
    dir[1][3] = "near start, left,";
    curve[1][3] = "--";
    edges[1].push_back(4);
    costs[1].push_back(1);
    dir[1][4] = "near start, right,";
    curve[1][4] = "--";
    edges[3].push_back(5);
    costs[3].push_back(2);
    dir[3][5] = "near start, right,";
    curve[3][5] = "--";

    for (int i = 0; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        for (int j = 0; j <= 4; j++) {
            drawQ.addRectangleNode(6 + i * 5 + j, "0", -1.5 + 0.5 * i, -0.5 - 0.5 * j, "white", "draw");
        }
    }

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            int cost = costs[i][j];
            if (dir[i][next] != "") {
                drawQ.addEdgeWeighted(i, next, "black", "\\footnotesize " + to_string(cost), dir[i][next], true, curve[i][next]);
            }
        }
    }

    fixedcost(0, 4);
}

int main() {
    solve();

    drawQ.draw();
}
