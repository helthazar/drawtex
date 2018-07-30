#include "dp_graphs.h"

const int INF = 100000000;
int dp[MAXN];

void dfs_shortestpath(int v, int t){
    used[v] = 1;
    dp[v] = (v == t) ? 0 : INF;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, (dp[v] == INF) ? "\\tiny $\\infty$" : to_string(dp[v]), -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
    if (v != 1 && v != 3)
        drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        int cost = costs[v][i];

        if (!used[next]) {
            drawQ.addEdgeWeighted(v, next, "red", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs_shortestpath(next, t);
        }
        if (dp[next] != INF) {
            dp[v] = min(dp[v], cost + dp[next]);
        }
        drawQ.addRectangleNode(6 + v, (dp[v] == INF) ? "\\tiny $\\infty$" : to_string(dp[v]), -1.5 + 0.5 * v, -0.5, "lightgray", "draw");
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
        drawQ.addEdgeWeighted(v, next, "black", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
        drawQ.increaseTimer();

    }
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void dfs_draw_shortestpath(int v){
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw = red, thick, text = white");

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        int cost = costs[v][i];

        if (dp[v] == dp[next] + cost) {
            drawQ.addEdgeWeighted(v, next, "red", "\\footnotesize " + to_string(cost), dir[v][next], true, curve[v][next]);
            dfs_draw_shortestpath(next);
        }
    }
}

int shortestpath(int s, int t) {
    dfs_shortestpath(s, t);

    drawQ.addCircleNode(s, to_string(s), x[s], y[s], "darkgray", "draw, text = white");
    drawQ.addRectangleNode(6 + s, (dp[s] == INF) ? "\\tiny $\\infty$" : to_string(dp[s]), -1.5 + 0.5 * s, -0.5, "darkgray", "draw", 2.0, "text = white");
    drawQ.increaseTimer();

    if (dp[s] != INF) {
        dfs_draw_shortestpath(s);
    }

    return dp[s];
}

void solve() {
    edges[0].push_back(3);
    costs[0].push_back(-2);
    dir[0][3] = "near start, above,";
    curve[0][3] = ".. controls (-1.5, 3.6) ..";
    edges[0].push_back(1);
    costs[0].push_back(-3);
    dir[0][1] = "near start, left,";
    curve[0][1] = "--";
    edges[0].push_back(2);
    costs[0].push_back(1);
    dir[0][2] = "near start, right,";
    curve[0][2] = "--";
    edges[1].push_back(3);
    costs[1].push_back(3);
    dir[1][3] = "near start, left,";
    curve[1][3] = "--";
    edges[1].push_back(4);
    costs[1].push_back(-1);
    dir[1][4] = "near start, right,";
    curve[1][4] = "--";
    edges[3].push_back(5);
    costs[3].push_back(-5);
    dir[3][5] = "near start, right,";
    curve[3][5] = "--";

    for (int i = 0; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "\\tiny $\\infty$", -1.5 + 0.5 * i, -0.5, "white", "draw");
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

    shortestpath(0, 5);
}

int main() {
    solve();

    drawQ.draw();
}
