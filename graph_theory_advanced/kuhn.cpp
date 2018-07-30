#include "graph_theory_advanced.h"

const int MAXM = 40000;

int match[MAXN];
int matchto[MAXM];

#define x oldx
#define y oldy
double x[] = {0, 0, 0, 2.5, 2.5, 2.5, 2.5};
double y[] = {2, 3, 4, 1.5, 2.5, 3.5, 4.5};

bool dfs_kuhn(int v) {
    used[v] = 1;

    for (int i = 0; i < edges[v].size(); i++) {
        int next = edges[v][i];
        int mtnext = matchto[next];

        if (mtnext == -1 || (!used[mtnext] && dfs_kuhn(mtnext))) {
            drawQ.addEdge(v, 3 + next, "blue");
            if (mtnext == -1) {
                drawQ.addCircleNode(3 + next, to_string(next), x[3 + next], y[3 + next], "lightgray", "draw = blue, thick");
            }
            drawQ.increaseTimer();
            drawQ.addEdge(v, 3 + next, "red");
            // draw_uedge(timer, v, 3 + next, "blue");
            // draw_uedge(timer + 1, v, 3 + next, "red");
            if (mtnext == -1) {
                // draw_node_circle(timer, x[3 + next], y[3 + next], 3 + next, "lightgray", ", draw = blue", next);
                // draw_node_circle(timer + 1, x[3 + next], y[3 + next], 3 + next, "lightgray", ", draw = red", next);
                drawQ.addCircleNode(3 + next, to_string(next), x[3 + next], y[3 + next], "lightgray", "draw = red, thick");
            }
            else {
                drawQ.addEdge(mtnext, 3 + next, "black");
                // draw_uedge(timer + 1, mtnext, 3 + next, "black");
            }
            matchto[next] = v;
            match[v] = next;
            drawQ.addRectangleNode(10 + v, to_string(next), 1 + 0.5 * v, -0.5, "lightgray", "draw");
            drawQ.addRectangleNode(13 + next, to_string(v), 1 + 0.5 * next, -1.25, "lightgray", "draw");
            // draw_node_rectangle(timer + 1, 1 + 0.5 * v, -0.5, -1, "lightgray");
            // draw_node_clear(timer + 1, 1 + 0.5 * v, -0.5, next);
            // draw_node_rectangle(timer + 1, 1 + 0.5 * next, -1.25, -1, "lightgray");
            // draw_node_clear(timer + 1, 1 + 0.5 * next, -1.25, v);
            drawQ.decreaseTimer();
            return true;
        }
    }

    return false;
}

int match_kuhn(int n, int m) {
    fill(match, match + n, - 1);
    fill(matchto, matchto + m, - 1);

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        drawQ.increaseTimer();
        fill(used, used + n, 0);

        if (match[i] == -1) {
            drawQ.addCircleNode(i, to_string(i), x[i], y[i], "lightgray", "draw = blue, thick");
            // draw_node_circle(timer, x[i], y[i], i, "lightgray", ", draw = blue", i);
        }
        if (dfs_kuhn(i)) {
            cnt++;
            drawQ.increaseTimer();
            drawQ.addCircleNode(i, to_string(i), x[i], y[i], "lightgray", "draw = red, thick");
            // timer++;
            // draw_node_circle(timer, x[i], y[i], i, "lightgray", ", draw = red", i);
        }
        if (match[i] == -1) {
            drawQ.addCircleNode(i, to_string(i), x[i], y[i], "lightgray", "draw = black, thick");
            // draw_node_circle(timer + 1, x[i], y[i], i, "lightgray", ", draw = black", i);
        }
    }

    return cnt;
}

void solve() {
    edges[2].push_back(2);
    edges[1].push_back(1);
    edges[1].push_back(3);
    edges[0].push_back(2);
    edges[0].push_back(0);

    for (int i = 0; i < 7; i++) {
        drawQ.addCircleNode(i, to_string((i < 3) ? i : i - 3), x[i], y[i], "lightgray", "draw");
        // draw_node_circle(1, x[i], y[i], i, "lightgray", "", (i < 3) ? i : i - 3);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int k = edges[i][j];
            drawQ.addEdge(i, 3 + k, "black");
            // draw_uedge(1, i, 3 + k, "black");
        }
    }

   for (int i = 0; i < 3; i++) {
      drawQ.addRectangleNode(10 + i, "-1", 1 + 0.5 * i, -0.5, "white", "draw");
       // draw_node_rectangle(timer, 1 + 0.5 * i, -0.5, -1, "white");
       // draw_node_clear(timer, 1 + 0.5 * i, -0.5, -1);
   }

   for (int i = 0; i < 4; i++) {
      drawQ.addRectangleNode(13 + i, "-1", 1 + 0.5 * i, -1.25, "white", "draw");
       // draw_node_rectangle(timer, 1 + 0.5 * i, -1.25, -1, "white");
       // draw_node_clear(timer, 1 + 0.5 * i, -1.25, -1);
   }

    match_kuhn(3, 4);
}

int main() {
    solve();

    drawQ.draw();
}
