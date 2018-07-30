#include "graph_theory.h"

string dir[MAXN][MAXN];
int d[MAXN][MAXN];

void bfs(int s) {
   deque<int> q;
   used[s] = 1;
   from[s] = s;
   q.push_back(s);

   while (!q.empty()) {
       int cur = q.front();

       if (cur == 1 || cur == 2 || cur == 4)
           drawQ.eraseNode(5 + cur);
       drawQ.addRectangleNode(5 + cur, to_string(used[cur]), -1.5 + 0.5 * cur, 0.5, "lightgray", "draw");
       drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], "lightgray", "draw = blue, thick");
       int qsz = q.size();
       for (int i = 0; i < q.size(); i++) {
           drawQ.addRectangleNode(10 + q.size() - i, to_string(q[i]), -1.5 + 0.5 * (i + 1), -0.5, "lightgray", "draw");
       }
       q.pop_front();

       for (int i = 0; i < edges[cur].size(); i++) {
           int next = edges[cur][i];

           if (!used[next] || used[next] > used[cur] + d[cur][next]) {
               used[next] = used[cur] + d[cur][next];
               if (from[next]) {
                   drawQ.addEdgeWeighted(from[next], next, "black", "\\footnotesize " + to_string(d[from[next]][next]), dir[from[next]][next]);
               }
               from[next] = cur;
               if (d[cur][next] == 0)
                   q.push_front(next);
               else
                   q.push_back(next);

               drawQ.addEdgeWeighted(cur, next, "blue", "\\footnotesize " + to_string(d[cur][next]), dir[cur][next], true);
               drawQ.addCircleNode(next, to_string(next), x[next], y[next], "lightgray", "draw = red, thick");
           }
       }
       drawQ.increaseTimer();
       drawQ.addCircleNode(cur, to_string(cur), x[cur], y[cur], "lightgray", "draw");
       drawQ.removeNode(10 + qsz);

       for (int i = 0; i < edges[cur].size(); i++) {
           int next = edges[cur][i];

           if (from[next] == cur) {
               drawQ.addEdgeWeighted(cur, next, "red", "\\footnotesize " + to_string(d[cur][next]), dir[cur][next], true);
               drawQ.addRectangleNode(5 + next, to_string(used[next]), -1.5 + 0.5 * next, 0.5, "lightgray", "draw");
           }
       }
   }
}

void solve() {
    vector<pair<int, int> > vp = {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {4, 5}};
    dir[1][2] = "near start, left,";
    d[1][2] = d[2][1] = 0;
    dir[1][3] = "near start, right,";
    d[1][3] = d[1][3] = 1;
    dir[2][3] = "midway, above,";
    d[2][3] = d[3][2] = 1;
    dir[2][4] = "near start, left,";
    d[2][4] = d[4][2] = 0;
    dir[2][5] = "near start, below,";
    d[2][5] = d[5][2] = 1;
    dir[4][5] = "midway, below,";
    d[4][5] = d[5][4] = 0;
    for (int i = 0; i < vp.size(); i++) {
        edges[vp[i].first].push_back(vp[i].second);
        edges[vp[i].second].push_back(vp[i].first);
    }
    for (int i = 1; i <= 5; i++) {
        sort(edges[i].begin(), edges[i].end());
    }

    for (int i = 1; i <= 5; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(5 + i, "0", -1.5 + 0.5 * i, 0.5, "white", "draw");
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            if (i < next)
                drawQ.addEdgeWeighted(i, next, "black", "\\footnotesize " + to_string(d[i][next]), dir[i][next]);
        }
    }

    bfs(1);

    // drawQ.removeNode(12);
        // drawQ.removeNode(13);
}

int main() {
    solve();

    drawQ.draw();
}
