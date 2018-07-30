#include "dp.h"

void dfs(int v, int p = -1){
    used[v] = 1;
    drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = blue, thick", 1.7);
    drawQ.addNode(18 + v, "\\tiny \\alert{" + to_string(fi[v]) + "}", fx[v], fy[v] + 0.5);
    drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        drawQ.addEdge(v, next, "blue", true);
        drawQ.addCircleNode(next, "", fx[next], fy[next], "lightgray", "draw", 1.7);
        drawQ.addNode(18 + next, "\\tiny \\alert{" + to_string(fi[next]) + "}", fx[next], fy[next] + 0.5);
        drawQ.increaseTimer();

        if (!used[next]) {
            drawQ.addEdge(v, next, "red", true);
            drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = red, thick", 1.7);
            dfs(next, v);
            drawQ.addCircleNode(v, "", fx[v], fy[v], "lightgray", "draw = blue, thick", 1.7);
        }
        drawQ.addEdge(v, next, "red", true);
    }
    for (int i = 0; i < edges[v].size(); i++){
        int next = edges[v][i];
        drawQ.addEdge(v, next, "blue", true);
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
        drawQ.addEdge(v, next, "black", true);
        drawQ.addCircleNode(next, "", fx[next], fy[next], "lightgray", "draw", 1.7);
        drawQ.addNode(9 + next, to_string(fl[next]), fx[next], fy[next]);
    }
}

void drawfib() {
    for (int v = 1; v <= 9; v++) {
        string vcolor = (v == 1) ? "darkgray" : "lightgray";
        string voptions = (v == 1) ? "text = white" : "";
        drawQ.addCircleNode(v, "", fx[v], fy[v], vcolor, "draw", 1.7);
        drawQ.addNode(9 + v, to_string(fl[v]), fx[v], fy[v], "", "", voptions);
        drawQ.addNode(18 + v, "\\tiny \\alert{" + to_string(fi[v]) + "}", fx[v], fy[v] + 0.5);
    }
    for (int v = 1; v <= 9; v++) {
        for (int i = 0; i < edges[v].size(); i++){
            int next = edges[v][i];
            drawQ.addEdge(v, next, "black", true);
        }
    }
}

void solve() {
    edges[1].push_back(2);
    edges[1].push_back(3);
    edges[2].push_back(4);
    edges[2].push_back(5);
    edges[3].push_back(6);
    edges[3].push_back(7);
    edges[4].push_back(8);
    edges[4].push_back(9);

    for (int i = 1; i <= 9; i++) {
        drawQ.addCircleNode(i, "", fx[i], fy[i], "white", "", 1.7);
    }

    //dfs(1);

    drawfib();
}

int main() {
    solve();

    drawQ.draw();
}
