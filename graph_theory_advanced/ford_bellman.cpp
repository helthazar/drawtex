#include "graph_theory_advanced.h"

struct edge {
    int from, to;
    int cost;
    edge() {}
    edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};
vector<edge> edglist;

void ford_bellman(int s, int n) {
    fill(dis, dis + n + 1, INF);
    fill(from, from + n + 1, - 1);
    dis[s] = 0;
    drawQ.addCircleNode(s, to_string(s), x[s], y[s], "lightgray", "draw = red, thick");
    drawQ.addRectangleNode(5 + s, "0", -1.5 + 0.5 * s, 1, "lightgray", "draw");
    drawQ.increaseTimer();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < edglist.size(); i++) {
            int fr = edglist[i].from;
            int to = edglist[i].to;
            int cost = edglist[i].cost;
            if (dis[to] > dis[fr] + cost) {
                if (from[to] != -1)
                    drawQ.addEdgeWeighted(from[to], to, "black", to_string(d[from[to]][to]), dir[from[to]][to], true);
                drawQ.addCircleNode(fr, to_string(fr), x[fr], y[fr], "lightgray", "draw = blue, thick");
                drawQ.addCircleNode(to, to_string(to), x[to], y[to], "lightgray", "draw = blue, thick");
                drawQ.addEdgeWeighted(fr, to, "blue", "\\footnotesize " + to_string(cost), dir[fr][to], true);
                drawQ.increaseTimer();

                dis[to] = max(-INF, dis[fr] + cost);
                from[to] = fr;

                drawQ.addRectangleNode(5 + fr, to_string(dis[fr]), -1.5 + 0.5 * fr, 1, "lightgray", "draw");
                drawQ.addRectangleNode(5 + to, to_string(dis[to]), -1.5 + 0.5 * to, 1, "lightgray", "draw");
                drawQ.addCircleNode(fr, to_string(fr), x[fr], y[fr], "lightgray", "draw = red, thick");
                drawQ.addCircleNode(to, to_string(to), x[to], y[to], "lightgray", "draw = red, thick");
                drawQ.addEdgeWeighted(fr, to, "red", "\\footnotesize " + to_string(cost), dir[fr][to], true);
            }
        }
    }
}

void solve() {
    edglist = {edge(0, 2, 7), edge(0, 3, -3), edge(2, 1, 1), edge(1, 4, 3), edge(2, 4, -9), edge(4, 3, -5)};
    dir[0][2] = "near end, above,";
    dir[0][3] = "midway, above,";
    dir[1][4] = "midway, above,";
    dir[2][1] = "near end, above,";
    dir[2][4] = "midway, above,";
    dir[4][3] = "midway, right,";

    for (int i = 0; i <= 4; i++) {
        dis[i] = INF;
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(5 + i, "\\tiny $\\infty$", -1.5 + 0.5 * i, 1, "white", "draw");
    }

    for (int i = 0; i < edglist.size(); i++) {
        int fr = edglist[i].from;
        int to = edglist[i].to;
        int cost = edglist[i].cost;
        drawQ.addEdgeWeighted(fr, to, "black", "\\footnotesize " + to_string(cost), dir[fr][to], true);
        d[fr][to] = cost;
    }

    ford_bellman(0, 4);
}

int main() {
    solve();

    drawQ.draw();
}
