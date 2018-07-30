#include "graph_theory.h"

void bfs(int s) {
   deque<int> q;
   used[s] = 1;
   from[s] = s;
   q.push_back(s);

   drawQ.addRectangleNode(6 + s, "1", -1.75 + 0.5 * s, -0.5, "lightgray", "draw");

   while (!q.empty()) {
       int cur = q.front();

       string curcolor = (used[cur] == 1) ? "lightgray" : "darkgray";
       string curdraw = (used[cur] == 1) ? "black" : "white";
       drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], curcolor, "draw = blue, thick, text = " + curdraw);
       for (int i = 0; i < q.size(); i++) {
           drawQ.addRectangleNode(12 + q[i], to_string(q[i]), -1.75 + 0.5 * (i + 1), -1.5, "lightgray", "draw");
       }
       q.pop_front();

       for (int i = 0; i < edges[cur].size(); i++) {
           int next = edges[cur][i];

           if (!used[next]) {
               used[next] = 3 - used[cur];
               from[next] = cur;
               q.push_back(next);

               drawQ.addEdge(cur, next, "blue", true);
               string nextcolor = (used[next] == 1) ? "lightgray" : "darkgray";
               string nextdraw = (used[next] == 1) ? "black" : "white";
               drawQ.addCircleNode(next, to_string(next), x[next], y[next], nextcolor, "draw = red, thick, text = " + nextdraw);
           }
       }
       if (cur != 3 && cur != 5 && cur != 6)
           drawQ.increaseTimer();
       drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], curcolor, "draw, text = " + curdraw);
       drawQ.removeNode(12 + cur);

       for (int i = 0; i < edges[cur].size(); i++) {
           int next = edges[cur][i];
           if (from[next] == cur) {
               drawQ.addEdge(cur, next, "black");
               drawQ.addRectangleNode(6 + next, to_string(used[next]), -1.75 + 0.5 * next, -0.5, "lightgray", "draw");
           }
       }
   }
}

void solve() {
    vector<pair<int, int> > vp = {{1, 2}, {1, 3}, {2, 5}, {2, 4}, {4, 6}, {5, 6}};
    for (int i = 0; i < vp.size(); i++) {
        edges[vp[i].first].push_back(vp[i].second);
        edges[vp[i].second].push_back(vp[i].first);
    }
    for (int i = 1; i <= 5; i++) {
        sort(edges[i].begin(), edges[i].end());
    }

    for (int i = 1; i <= 6; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "0", -1.75 + 0.5 * i, -0.5, "white", "draw");
    }

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black");
        }
    }

    bfs(1);
}

int main() {
    solve();

    drawQ.draw();
}
