#include "graph_theory.h"

bool cutpoint[MAXN];

void dfs_cutpoint(int v, bool root = true, int p = -1) {
    used[v] = 1;
    fout[v] = tin[v] = timer++;
    cutpoint[v] = false;
    int directedges = 0;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + v, to_string(tin[v]), -1.75 + 0.5 * v, 0, "lightgray", "draw");
    drawQ.addRectangleNode(12 + v, to_string(fout[v]), -1.75 + 0.5 * v, -1, "lightgray", "draw");
    // drawQ.increaseTimer();

    string vcolor = "lightgray";
    string vtext = "";
    for (int i = 0; i < edges[v].size(); i++) {
        int next = edges[v][i];
        drawQ.addEdge(v, next, "blue", true);
        // drawQ.increaseTimer();

        if (!used[next]){
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = red, thick" + vtext);

            dfs_cutpoint(next, false, v);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = blue, thick" + vtext);
            drawQ.addEdge(v, next, "blue", true);
            // drawQ.increaseTimer();

            fout[v] = min(fout[v], fout[next]);
            if (tin[v] <= fout[next] && !root) {
                cutpoint[v] = true;
                vcolor = "darkgray";
                vtext = ", text = white";
                drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = blue, thick" + vtext);
            }
            directedges++;
            drawQ.addEdge(v, next, "black");
            drawQ.addRectangleNode(12 + v, to_string(fout[v]), -1.75 + 0.5 * v, -1, "lightgray", "draw");
        }
        else {
            fout[v] = min(fout[v], tin[next]);
            drawQ.addRectangleNode(12 + v, to_string(fout[v]), -1.75 + 0.5 * v, -1, "lightgray", "draw");
            if (next == p) {
                drawQ.removeEdge(v, next);
            }
            else {
                drawQ.addEdge(v, next, "black");
            }
        }
    }

    // drawQ.increaseTimer();
    if (root && directedges >= 2) {
        cutpoint[v] = true;
        vcolor = "darkgray";
        vtext = ", text = white";
    }
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw" + vtext);
}
void solve() {
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[2].push_back(3);
    edges[2].push_back(5);
    edges[4].push_back(5);
    edges[5].push_back(6);

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

    dfs_cutpoint(1);
    drawQ.increaseTimer();
}

int main() {
    solve();

    drawQ.draw();
}
