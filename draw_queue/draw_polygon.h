#include "draw_object.h"

struct point {
    double x, y;

    point() {}
    point(double x, double y) : x(x), y(y) {}
};

class drawPolygon : public drawObject {
    vector<point> v;
    string edgeColor;
	string fillColor;
    double fillOpacity;

public:
	drawPolygon(int startTime, int endTime, vector<point> v, string edgeColor, string fillColor, double fillOpacity) :
		drawObject(startTime, endTime), v(v), edgeColor(edgeColor), fillColor(fillColor), fillOpacity(fillOpacity) {}
	drawPolygon(int startTime, vector<point> v, string edgeColor, string fillColor, double fillOpacity) :
		drawPolygon(startTime, -1, v, edgeColor, fillColor, fillOpacity) {}
	drawPolygon() {}

	bool operator==(drawPolygon &p) {
		if (p.v.size() != v.size()) {
            return false;
        }
        for (int i = 0; i < v.size(); i++) {
            if (p.v[i].x != v[i].x || p.v[i].y != v[i].y) {
                return false;
            }
        }
        return true;
	}

	void draw() {
		printf("\t\t\\path<%d-", startTime);
		if (endTime != -1)
			printf("%d", endTime);
		printf("> [thick, fill = %s, fill opacity = %lf] ", edgeColor.c_str(), fillColor.c_str(), fillOpacity);
        for (int i = 0; i < v.size(); i++) {
            printf("(%lf, %lf)--", v[i].x, v[i].y);
        }
        if (!v.empty()) {
            printf("cycle;\n");
        }
	}
};
