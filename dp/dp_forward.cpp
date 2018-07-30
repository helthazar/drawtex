#include "dp.h"

vector<int> redges[MAXN];

void solve() {
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[1].push_back(4);
    edges[2].push_back(4);

    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            redges[next].push_back(i);
        }
    }

    for (int i = 1; i <= 4; i++) {
        drawQ.addCircleNode(i, "", x[i], y[i], "white", "draw", s[i]);
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black", true);
        }
    }

    for (int j = 0; j < 4; j++) {
        int v = p[j];
        drawQ.addCircleNode(v, "", x[v], y[v], "darkgray", "draw = blue, thick", s[v]);

        for (int i = 0; i < redges[v].size(); i++){
            int next = redges[v][i];
            drawQ.removeEdge(next, v);
            drawQ.addEdge(v, next, "blue", true);
            drawQ.addCircleNode(next, "", x[next], y[next], "lightgray", "draw = red, thick", s[next]);
        }

        drawQ.increaseTimer();

        drawQ.addCircleNode(v, "", x[v], y[v], "darkgray", "draw", s[v]);

        for (int i = 0; i < redges[v].size(); i++){
            int next = redges[v][i];
            drawQ.removeEdge(v, next);
            drawQ.addEdge(next, v, "black", true);
            drawQ.addCircleNode(next, "", x[next], y[next], "lightgray", "draw", s[next]);
        }
    }
}

int main() {
    solve();

    drawQ.draw();
}
