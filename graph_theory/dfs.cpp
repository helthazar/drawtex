#include "graph_theory.h"

void dfs(int v, int p = -1){
    used[v] = 1;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(5 + v, "1", -1.5 + 0.5 * v, 0.5, "lightgray", "draw");
    drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        if (next == p) {
            continue;
        }

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs(next, v);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
        }
        drawQ.addEdge(v, next, "black");
    }
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
}

void solve() {
    vector<pair<int, int> > vp = {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {4, 5}};
    for (int i = 0; i < vp.size(); i++) {
        edges[vp[i].first].push_back(vp[i].second);
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            if (next > i) {
                edges[next].push_back(i);
            }
        }
        sort(edges[i].begin(), edges[i].end());
    }

    for (int i = 1; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(5 + i, "0", -1.5 + 0.5 * i, 0.5, "white", "draw");
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    dfs(1);
}

int main() {
    solve();

    drawQ.draw();
}
