#include "graph_theory.h"

void dfs_topsort(int v){
   used[v] = 1;

   for (int i = 0; i < edges[v].size(); i++){
       int next = edges[v][i];
       if (!used[next]) {
           dfs_topsort(next);
       }
   }

   topsort.push_back(v);
}

vector<int> redges[MAXN];
int color[MAXN];

void dfs_reverse(int v, int comp = 1){
   color[v] = comp;
   string vcolor = (comp == 1) ? "lightgray" : "darkgray";
   string vtext = (comp == 1) ? "" : ", text = white";
   drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = blue, thick" + vtext);
   drawQ.addRectangleNode(6 + v, to_string(comp), -1.75 + 0.5 * v, 0, "lightgray", "draw");
   drawQ.increaseTimer();

   for (int i = 0; i < redges[v].size(); i++){
       int next = redges[v][i];
       drawQ.addEdge(v, next, "blue", true);
       // drawQ.increaseTimer();

       if (!color[next]){
           color[next] = comp;
           drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = red, thick" + vtext);
           drawQ.addEdge(v, next, "red", true);
           dfs_reverse(next, comp);
           drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw = blue, thick" + vtext);
       }
       drawQ.addEdge(v, next, "black", true);
       // drawQ.increaseTimer();
   }
   drawQ.addCircleNode(v, to_string(v), x[v], y[v], vcolor, "draw" + vtext);
}
vector<int> color_comp;

void solve() {
    edges[1].push_back(2);
    edges[2].push_back(3);
    edges[2].push_back(5);
    edges[2].push_back(4);
    edges[5].push_back(6);
    edges[6].push_back(4);
    edges[3].push_back(1);
    edges[4].push_back(5);

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            redges[next].push_back(i);
        }
    }

    for (int i = 1; i <= 6; i++) {
        drawQ.addCircleNode(i, to_string(i), x[i], y[i], "white", "draw");
        drawQ.addRectangleNode(6 + i, "0", -1.75 + 0.5 * i, 0, "white", "draw");
        drawQ.addRectangleNode(12 + i, "", -1.75 + 0.5 * i, -1, "white", "");
        drawQ.addRectangleNode(18 + i, "", -1.75 + 0.5 * i, -2, "white", "");
    }

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            int next = edges[i][j];
            drawQ.addEdge(i, next, "black", true);
        }
    }
    drawQ.increaseTimer();

    dfs_topsort(1);
    reverse(topsort.begin(), topsort.end());
    for (int i = 1; i <= 6; i++) {
        drawQ.addRectangleNode(12 + i, to_string(topsort[i - 1]), -1.75 + 0.5 * i, -1, "white", "draw");
    }
    drawQ.increaseTimer();

    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < redges[i].size(); j++) {
            int next = redges[i][j];
            drawQ.removeEdge(next, i);
            drawQ.addEdge(i, next, "black", true);
        }
    }
    drawQ.increaseTimer();

    int colorcnt = 0;
    for (int i = 1; i <= 6; i++) {
        drawQ.addRectangleNode(12 + i, to_string(topsort[i - 1]), -1.75 + 0.5 * i, -1, "lightgray", "draw");
        if (!color[topsort[i - 1]]){
            color_comp.push_back(topsort[i - 1]);
            drawQ.addRectangleNode(18 + color_comp.size(), to_string(color_comp.back()), -1.75 + 0.5 * color_comp.size(), -2, "lightgray", "draw");
            dfs_reverse(topsort[i - 1], ++colorcnt);
        }
        // drawQ.increaseTimer();
    }
}

int main() {
    solve();

    drawQ.draw();
}
