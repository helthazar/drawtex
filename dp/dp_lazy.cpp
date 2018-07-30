#include "dp.h"

void dfs(int v){
    used[v] = 1;
    drawQ.addCircleNode(v, "", x[v], y[v], "white", "draw = red, thick", s[v]);

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            dfs(next);
            drawQ.addEdge(v, next, "black", true);
        }
    }

    drawQ.addCircleNode(v, "", x[v], y[v], "lightgray", "draw = blue, thick", s[v]);

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        drawQ.addEdge(v, next, "blue", true);
    }

    drawQ.increaseTimer();

    drawQ.addCircleNode(v, "", x[v], y[v], "darkgray", "draw", s[v]);
    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        drawQ.addEdge(v, next, "black", true);
    }
}

void solve() {
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[1].push_back(4);
    edges[2].push_back(4);

    for (int i = 1; i <= 4; i++) {
        drawQ.addCircleNode(i, "", x[i], y[i], "white", "draw", s[i]);
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black", true);
        }
    }

    dfs(1);
}

int main() {
    solve();

    drawQ.draw();
}
