#include "graph_theory.h"

int tout[MAXN];

void dfs(int v){
    used[v] = 1;
    tin[v] = timer++;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, to_string(tin[v]), -1.75 + 0.5 * v, 0, "lightgray", "draw");
    // drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        drawQ.addEdge(v, next, "blue", true);
        // drawQ.increaseTimer();

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            dfs(next);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
            drawQ.addEdge(v, next, "black");
        }
        else {
            drawQ.removeEdge(v, next);
        }
    }
    tout[v] = timer++;
    // drawQ.increaseTimer();
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
    drawQ.addRectangleNode(12 + v, to_string(tout[v]), -1.75 + 0.5 * v, -1, "lightgray", "draw");
}

void solve() {
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[2].push_back(4);
    edges[2].push_back(5);
    edges[5].push_back(6);
    x[5] = x[5] = x[1];

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            if (next > i) {
                edges[next].push_back(i);
            }
        }
        sort(edges[i].begin(), edges[i].end());
    }

    for (int i = 1; i <= 6; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "", -1.75 + 0.5 * i, 0, "white", "draw");
        drawQ.addRectangleNode(12 + i, "", -1.75 + 0.5 * i, -1, "white", "draw");
    }

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    dfs(1);
    drawQ.increaseTimer();
}

int main() {
    solve();

    drawQ.draw();
}
