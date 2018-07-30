#include "graph_theory.h"

void dfs_topsort(int v){
   used[v] = 1;
   drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
   drawQ.addRectangleNode(6 + v, "1", -1.75 + 0.5 * v, 0, "lightgray", "draw");
   // drawQ.increaseTimer();

   for (int i = 0; i < edges[v].size(); i++){
       int next = edges[v][i];
       drawQ.addEdge(v, next, "blue", true);
       // drawQ.increaseTimer();

       if (!used[next]) {
           drawQ.addEdge(v, next, "red", true);
           drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = red, thick");

           dfs_topsort(next);

           drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw = blue, thick");
       }
       drawQ.addEdge(v, next, "black", true);
       // drawQ.increaseTimer();
   }

   topsort.push_back(v);
   drawQ.addCircleNode(v, to_string(v), x[v], y[v], "lightgray", "draw");
   drawQ.addRectangleNode(12 + v, to_string(topsort.back()), -1.75 + 0.5 * topsort.size(), -1, "lightgray", "draw");
}

void solve() {
   edges[1].push_back(2);
   edges[2].push_back(3);
   edges[2].push_back(4);
   edges[2].push_back(5);
   edges[5].push_back(6);
   edges[6].push_back(4);

   for (int i = 1; i <= 6; i++) {
       drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
       drawQ.addRectangleNode(6 + i, "0", -1.75 + 0.5 * i, 0, "white", "draw");
       drawQ.addRectangleNode(12 + i, "", -1.75 + 0.5 * i, -1, "white", "");
   }

   for (int i = 1; i <= 6; i++) {
       for (int j = 0; j < edges[i].size(); j++) {
           int next = edges[i][j];
           drawQ.addEdge(i, next, "black", true);
       }
   }

   dfs_topsort(1);
   reverse(topsort.begin(), topsort.end());
   drawQ.increaseTimer();
   for (int i = 1; i <= 6; i++) {
       drawQ.addRectangleNode(12 + i, to_string(topsort[i - 1]), -1.75 + 0.5 * i, -1, "lightgray", "draw");
   }
   drawQ.increaseTimer();
}

int main() {
    solve();

    drawQ.draw();
}
