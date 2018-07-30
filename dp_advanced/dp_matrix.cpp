#include "dp_advanced.h"

int n[] = {2, 3, 2};
int m[] = {3, 2, 5};

void solve() {
   for (int i = 0; i < 3; i++) {
       drawQ.addRectangleNode(20 + i, to_string(n[i]), -1.75 + 0.5 * i, -0.5, "lightgray", "draw");
       drawQ.addRectangleNode(25 + i, to_string(m[i]), -1.75 + 0.5 * i, -1.2, "lightgray", "draw");
   }

   for (int i = 0; i < 3; i++) {
       dp[i][i] = 0;
       drawQ.addRectangleNode(i * 3 + i, to_string(dp[i][i]), -1.75 + 0.5 * i, -2.5 - i * 0.5, "white", "draw");
   }
   for (int len = 1; len < 3; len++) {
       for (int i = 0; i + len < 3; i++) {
           int j = i + len;
           dp[i][j] = dp[i][i] + dp[i + 1][j] + n[i] * m[i] * m[j];
           for (int s = i + 1; s < j; s++) {
               dp[i][j] = min(dp[i][j], dp[i][s] + dp[s + 1][j] + n[i] * m[s] * m[j]);
           }
           if (dp[i][j] == 0) {
               drawQ.addRectangleNode(i * 3 + j, to_string(dp[i][j]), -1.75 + 0.5 * j, -2.5 - i * 0.5, "white", "draw");
           }
           else {
               drawQ.addRectangleNode(i * 3 + j, to_string(dp[i][j]), -1.75 + 0.5 * j, -2.5 - i * 0.5, "lightgray", "draw");
           }
       }
   }
   drawQ.addRectangleNode(0 * 3 + 2, to_string(dp[0][2]), -1.75 + 0.5 * 2, -2.5 - 0 * 0.5, "darkgray", "draw", 2, "text = white");
}

int main() {
    solve();

    drawQ.draw();
}
