#include "graph_theory.h"

void solve() {
    for (int i = 1; i <= 6; i += 5) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "darkgray", "draw, text = white");
        drawQ.addRectangleNode(6 + i, "1", -1.75 + 0.5 * i, -0.5, "lightgray", "draw");
    }
    for (int i = 2; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "lightgray", "draw");
        drawQ.addRectangleNode(6 + i, (i == 3) ? "3" : "2", -1.75 + 0.5 * i, -0.5, "lightgray", "draw");
    }

    vector<pair<int, int> > ve = {{1, 2}, {2, 3}, {6, 4}, {6, 5}};
    for (int i = 0; i < ve.size(); i++) {
        drawQ.addEdge(ve[i].first, ve[i].second, "red", true);
    }
    vector<pair<int, int> > vp = {{2, 5}, {2, 4}};
    for (int i = 0; i < vp.size(); i++) {
        drawQ.addEdge(vp[i].first, vp[i].second, "black");
    }

    drawQ.increaseTimer();
}

int main() {
    solve();

    drawQ.draw();
}
