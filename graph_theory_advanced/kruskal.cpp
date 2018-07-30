#include "graph_theory_advanced.h"

int parent[MAXN], rang[MAXN];

void make_set (int v) {
    parent[v] = v;
    rang[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rang[a] == rang[b])
            ++rang[a];
        if (rang[a] < rang[b])
            swap(a, b);
        parent[b] = a;
        return true;
    }
    return false;
}

struct edge {
    int from, to, cost;
    edge() {}
    edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

bool cmp_edge(edge a, edge b) {
    return a.cost < b.cost;
}

void kruskal(vector<edge> &edgelist, int n) {
    for (int i = 0; i <= n; i++)
        make_set(i);
    sort(edgelist.begin(), edgelist.end(), cmp_edge);
    for (int i = 0; i < edgelist.size(); i++) {
        int from = edgelist[i].from;
        int to = edgelist[i].to;
        int cost = edgelist[i].cost;
        drawQ.addRectangleNode(5 + i, to_string(from), -1, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(15 + i, to_string(to), -0.5, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(25 + i, to_string(cost), 0, 1 - 0.5 * i, "white", "draw");
        drawQ.addEdgeWeighted(from, to, "black", to_string(cost), dir[from][to], false);
    }
    drawQ.increaseTimer();

    for (int i = 0; i < edgelist.size(); i++) {
        int from = edgelist[i].from;
        int to = edgelist[i].to;
        int cost = edgelist[i].cost;
        drawQ.addRectangleNode(5 + i, to_string(from), -1, 1 - 0.5 * i, "lightgray", "draw");
        drawQ.addRectangleNode(15 + i, to_string(to), -0.5, 1 - 0.5 * i, "lightgray", "draw");
        drawQ.addRectangleNode(25 + i, to_string(cost), 0, 1 - 0.5 * i, "lightgray", "draw");
        drawQ.addEdgeWeighted(from, to, "blue", to_string(cost), dir[from][to], false);
        drawQ.increaseTimer();
        if (union_sets(from, to)) {
            drawQ.addEdgeWeighted(from, to, "red", to_string(cost), dir[from][to], false);
            drawQ.addCircleNode(from, to_string(from), x[from], y[from], "lightgray", "draw =red, thick");
            drawQ.addCircleNode(to, to_string(to), x[to], y[to], "lightgray", "draw = red, thick");
        }
        else {
            drawQ.addEdgeWeighted(from, to, "black", to_string(cost), dir[from][to], false);
        }
        drawQ.addRectangleNode(5 + i, to_string(from), -1, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(15 + i, to_string(to), -0.5, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(25 + i, to_string(cost), 0, 1 - 0.5 * i, "white", "draw");
    }
}

void solve() {
    vector<edge> edgelist;

    edgelist.push_back(edge(0, 2, 7));
    edgelist.push_back(edge(0, 3, 5));
    dir[0][2] = "near end, above,";
    dir[0][3] = "midway, above,";
    edgelist.push_back(edge(1, 4, 4));
    dir[1][4] = "midway, above,";
    edgelist.push_back(edge(2, 1, 1));
    edgelist.push_back(edge(2, 4, 9));
    dir[2][1] = "near end, above,";
    dir[2][4] = "near end, above,";
    edgelist.push_back(edge(3, 2, 6));
    dir[3][2] = "near end, above,";
    edgelist.push_back(edge(4, 3, 2));
    dir[4][3] = "midway, right,";

    for (int i = 0; i <= 4; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
    }

    for (int i = 0; i < edgelist.size(); i++) {
        int from = edgelist[i].from;
        int to = edgelist[i].to;
        int cost = edgelist[i].cost;
        drawQ.addRectangleNode(5 + i, to_string(from), -1, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(15 + i, to_string(to), -0.5, 1 - 0.5 * i, "white", "draw");
        drawQ.addRectangleNode(25 + i, to_string(cost), 0, 1 - 0.5 * i, "white", "draw");
        drawQ.addEdgeWeighted(from, to, "black", to_string(cost), dir[from][to], false);
    }
    drawQ.increaseTimer();

    kruskal(edgelist, 4);
}

int main() {
    solve();

    drawQ.draw();
}
