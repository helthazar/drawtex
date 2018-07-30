#include "graph_theory.h"

vector<int> edgind[MAXN];
int ind[MAXN];
vector<int> euler, path;

void dfs_euler(int v){
    path.push_back(v);
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    if (v == 1 || v == 2 && ind[v] != 0)
        drawQ.increaseTimer();

    for ( ; ind[v] < edges[v].size(); ind[v]++) {
        int next = edges[v][ind[v]];
        int e = edgind[v][ind[v]];
        if (!used[e]) {
            drawQ.removeEdge(next, v);
            drawQ.addEdge(v, next, "blue", true);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            used[e] = 1;
            dfs_euler(next);
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
            drawQ.removeEdge(v, next);
            drawQ.addEdge(next, v, "red", true);
            if (v == 2 && ind[v] != 2)
                drawQ.increaseTimer();
        }
    }
    euler.push_back(v);
    path.pop_back();
    if (find(path.begin(), path.end(), v) == path.end())
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
    else
        drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
    drawQ.addRectangleNode(10 + euler.size(), to_string(v), -2 + 0.5 * euler.size(), 0.75, "lightgray", "draw");
}

void solve() {
    vector<pair<int, int> > vp = {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {4, 5}};
    for (int i = 0; i < vp.size(); i++) {
        int a = vp[i].first, b = vp[i].second;
        edges[a].push_back(b);
        edges[b].push_back(a);
        edgind[a].push_back(i);
        edgind[b].push_back(i);
    }

    for (int i = 1; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    dfs_euler(1);
}

int main() {
    solve();

    drawQ.draw();
}
