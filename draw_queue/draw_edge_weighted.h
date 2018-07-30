#include "draw_edge.h"

class drawEdgeWeighted : public drawEdge {
	string weight;
    string weightDirection;

public:
	drawEdgeWeighted(int startTime, int endTime, int from, int to, string color, string weight, string weightDirection, bool oriented, string curve) :
		drawEdge(startTime, endTime, from, to, color, oriented, curve), weight(weight), weightDirection(weightDirection) {}
	drawEdgeWeighted(int startTime, int from, int to, string color, string weight, string weightDirection, bool oriented, string curve) :
		drawEdgeWeighted(startTime, -1, from, to, color, weight, weightDirection, oriented, curve) {}
	drawEdgeWeighted() {}

	bool operator==(drawEdgeWeighted &e) {
		return e.from == from && e.to == to;
	}

	void draw() {
		printf("\t\t\\tikzstyle{every node} = []\n");
		printf("\t\t\\draw<%d-", startTime);
		if (endTime != -1)
			printf("%d", endTime);
		printf("> [thick,");
		if (oriented) {
			printf("->,");
		}
		printf("color = %s] (%d) %s (%d) node [draw = none,%sfill = none] {%s};\n", color.c_str(), from, curve.c_str(), to, weightDirection.c_str(), weight.c_str());
	}
};
