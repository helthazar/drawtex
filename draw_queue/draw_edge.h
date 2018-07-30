#include "draw_object.h"

class drawEdge : public drawObject {
protected:
	string color;
	bool oriented;
	string curve;
	int from;
	int to;

public:
	drawEdge(int startTime, int endTime, int from, int to, string color, bool oriented, string curve) :
		drawObject(startTime, endTime), from(from), to(to), color(color), oriented(oriented), curve(curve) {}
	drawEdge(int startTime, int from, int to, string color, bool oriented, string curve) :
		drawEdge(startTime, -1, from, to, color, oriented, curve) {}
	drawEdge() {}

	bool operator==(drawEdge &e) {
		return e.from == from && e.to == to;
	}

	void draw() {
		printf("\t\t\\draw<%d-", startTime);
		if (endTime != -1)
			printf("%d", endTime);
		printf("> [thick,");
		if (oriented) {
			printf("->,");
		}
		printf("color = %s] (%d) %s (%d);\n", color.c_str(), from, curve.c_str(), to);
	}
};
