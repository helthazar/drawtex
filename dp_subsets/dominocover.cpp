#include "dp_subsets.h"

const int MAXM = 20;
long long dp[MAXN][1 << MAXM];

void dp_profile(int mask, int i, int nmask, int j, int m) {
	if (j == m) {
		dp[i + 1][nmask] += dp[i][mask];
		return;
	}

	if (mask & (1 << j)) {
		dp_profile(mask, i, nmask, j + 1, m);
	}
	else {
		dp_profile(mask, i, nmask | (1 << j), j + 1, m);
		if (j + 1 < m && !(mask & (1 << (j + 1)))) {
		   dp_profile(mask, i, nmask, j + 2, m);
		}
	}
}

void solve() {
	int n = 2, m = 3;
	dp[0][0] = 1;

	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < (1 << m); mask++) {
			dp_profile(mask, i, 0, 0, m);

            string color = (dp[i][mask] != 0) ? "lightgray" : "white";
            drawQ.addRectangleNode(i * (1 << m) + mask, to_string(dp[i][mask]), -1.75 + 0.5 * i, 2 - 0.5 * mask, color, "draw");
		}
	}
	for (int mask = 0; mask < (1 << m); mask++) {
		string s = "";
		for (int j = 0; j < m; j++) {
			s.push_back('0' + ((mask >> j) & 1));
		}
        reverse(s.begin(), s.end());
        drawQ.addNode((n + 1) * (1 << m) + mask, "\\tiny \\alert{" + s + "}",  -2.5, 2 - 0.5 * mask);

        string color = (dp[n][mask] != 0) ? "lightgray" : "white";
        drawQ.addRectangleNode(n * (1 << m) + mask, to_string(dp[n][mask]), -1.75 + 0.5 * n, 2 - 0.5 * mask, color, "draw");
	}
}

int main() {
    solve();

    drawQ.draw();
}
