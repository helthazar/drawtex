#include "graph_theory.h"

int path[MAXN];
int cyclic[MAXN];
vector<int> cycle;

bool dfs_cycle(int v, int h = 0) {
    used[v] = 1;
    path[h] = v;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
    drawQ.addRectangleNode(6 + h, to_string(v), -1.75 + 0.5 * h, -0.5, "lightgray", "draw");
    if (v != 2 && v != 5 && v != 6)
        drawQ.increaseTimer();

    for (int i = 0; i < edges[v].size(); i++) {
        int next = edges[v][i];

        if (used[next] == 1 && cycle.empty()) {
            drawQ.decreaseTimer();
            drawQ.addEdge(v, next, "blue", true);
            drawQ.increaseTimer();

            int oldh = h;
            while (true) {
                cycle.push_back(path[h]);
                drawQ.addCircleNode(path[h], to_string(path[h]), x[path[h]], y[path[h]], "darkgray", "draw = blue, thick, text = white");
                drawQ.addRectangleNode(12 + cycle.size(), to_string(path[h]), -1.75 + 0.5 * cycle.size(), -1.5, "lightgray", "draw");
                if (path[h--] == next) {
                    break;
                }
                drawQ.addEdge(path[h], path[h + 1], "blue", true);
            }
            drawQ.addEdge(v, next, "blue", true);
            drawQ.increaseTimer();

            reverse(cycle.begin(), cycle.end());
            for (int i = 0; i < cycle.size(); i++) {
                drawQ.addRectangleNode(12 + i + 1, to_string(cycle[i]), -1.75 + 0.5 * (i + 1), -1.5, "lightgray", "draw");
            }
            drawQ.increaseTimer();

            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "darkgray", "draw, text = white");
            drawQ.addEdge(v, next, "black", true);
            drawQ.addRectangleNode(6 + oldh, "", -1.75 + 0.5 * oldh, -0.5, "white", "draw");
            return true;
        }
        else if (used[next] == 0) {
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");
            drawQ.addEdge(v, next, "red", true);

            if (dfs_cycle(next, h + 1)) {
                string vcolor = "lightgray";
                string vtext = "";
                if (find(cycle.begin(), cycle.end(), v) != cycle.end()) {
                    vcolor = "darkgray";
                    vtext = ", text = white";
                }

                drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw" + vtext);
                drawQ.addEdge(v, next, "black", true);
                drawQ.addRectangleNode(6 + h, "", -1.75 + 0.5 * h, -0.5, "white", "draw");
                return true;
            }
            drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
        }
        drawQ.addEdge(v, next, "black", true);
    }

    used[v] = 2;
    drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
    return false;
}

void solve() {
    vector<pair<int, int> > vp = {{1, 2}, {2, 3}, {2, 5}, {4, 2}, {5, 6}, {6, 4}};
    for (int i = 0; i < vp.size(); i++) {
        edges[vp[i].first].push_back(vp[i].second);
    }

   for (int i = 1; i <= 6; i++) {
       drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
       drawQ.addRectangleNode(6 + i, "", -1.75 + 0.5 * i, -0.5, "white", "draw");
       drawQ.addRectangleNode(12 + i, "", -1.75 + 0.5 * i, -1.5, "white", "draw = white");
   }

   for (int i = 1; i <= 6; i++) {
       for (int j = 0; j < edges[i].size(); j++) {
           int next = edges[i][j];
           drawQ.addEdge(i, next, "black", true);
       }
   }

   dfs_cycle(1, 1);
}

int main() {
    solve();

    drawQ.draw();
}
