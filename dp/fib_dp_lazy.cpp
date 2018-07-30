#include "dp.h"

vector<string> curves[MAXN];

void dfs(int v, int p = -1){
    used[v] = 1;
    drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = blue, thick", 1.7);
    drawQ.addNode(18 + v, "\\tiny \\alert{" + to_string(fi[v]) + "}", fx[v], fy[v] + 0.5);
    drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        string curve = curves[v][i];
        drawQ.addEdge(v, next, "blue", true, curve);
        drawQ.addCircleNode(next, "", fx[next], fy[next], "lightgray", "draw", 1.7);
        drawQ.addNode(18 + next, "\\tiny \\alert{" + to_string(fi[next]) + "}", fx[next], fy[next] + 0.5);
        drawQ.increaseTimer();

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true, curve);
            drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = red, thick", 1.7);
            dfs(next, v);
            drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = blue, thick", 1.7);
        }
        drawQ.addEdge(v, next, "red", true, curve);
    }
    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        string curve = curves[v][i];
        drawQ.addEdge(v, next, "blue", true, curve);
        drawQ.addCircleNode(next, "", fx[next], fy[next], "lightgray", "draw = red, thick", 1.7);
        drawQ.addNode(9 + next, to_string(fl[next]), fx[next], fy[next]);
    }
    if (edges[v].size() > 0) {
        drawQ.increaseTimer();
    }
    string vcolor = (p == -1) ? "darkgray" : "lightgray";
    string voptions = (p == -1) ? "text = white" : "";
    drawQ.addCircleNode(v, "", fx[v], fy[v], vcolor, "draw = blue, thick", 1.7);
    drawQ.addNode(9 + v, to_string(fl[v]), fx[v], fy[v], "", "", voptions);
    drawQ.increaseTimer();
    drawQ.addCircleNode(v, "", fx[v], fy[v], vcolor, "draw", 1.7);
    drawQ.addNode(9 + v, to_string(fl[v]), fx[v], fy[v], "", "", voptions);
    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        string curve = curves[v][i];
        drawQ.addEdge(v, next, "black", true, curve);
        drawQ.addCircleNode(next, "", fx[next], fy[next], "lightgray", "draw", 1.7);
        drawQ.addNode(9 + next, to_string(fl[next]), fx[next], fy[next]);
    }
}

void drawfib() {
    for (int v = 1; v <= 9; v++) {
        if (v == 3 || v == 5 || v == 6 || v == 7) {
            continue;
        }
        string vcolor = (v == 1) ? "darkgray" : "lightgray";
        string voptions = (v == 1) ? "text = white" : "";
        drawQ.addCircleNode(v, "", fx[v], fy[v], vcolor, "draw", 1.7);
        drawQ.addNode(9 + v, to_string(fl[v]), fx[v], fy[v], "", "", voptions);
        drawQ.addNode(18 + v, "\\tiny \\alert{" + to_string(fi[v]) + "}", fx[v], fy[v] + 0.5);
    }
    for (int v = 1; v <= 9; v++) {
        if (v == 3 || v == 5 || v == 6 || v == 7) {
            continue;
        }
        for (int i = 0; i < edges[v].size(); i++){
            int next = edges[v][i];
            string curve = curves[v][i];
            drawQ.addEdge(v, next, "black", true, curve);
        }
    }
}

void solve() {
    edges[1].push_back(2);
    edges[1].push_back(4);
    edges[2].push_back(4);
    edges[2].push_back(8);
    edges[4].push_back(8);
    edges[4].push_back(9);
    curves[1].push_back("--");
    curves[1].push_back(".. controls (0, -1.2) ..");
    curves[2].push_back("--");
    curves[2].push_back(".. controls (-2.5, -1.9) ..");
    curves[4].push_back("--");
    curves[4].push_back("--");

    for (int i = 1; i <= 9; i++) {
        if (i == 5) {
            continue;
        }
        drawQ.addCircleNode(i, "", fx[i], fy[i], "white", "", 1.7);
    }

    // dfs(1);

    drawfib();
}

int main() {
    solve();

    drawQ.draw();
}
