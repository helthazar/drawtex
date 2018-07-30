#include "draw_object.h"

class drawNode : public drawObject {
	double x;
    double y;
    int v;
	string label;
	string shape;
    string color;
    string options;
    double scale;
	string textoptions;

public:
	drawNode(int startTime, int endTime, int v, string label, double x, double y, string shape, string color, string options, double scale, string textoptions) :
		drawObject(startTime, endTime), v(v), label(label), x(x), y(y), shape(shape), color(color), options(options), scale(scale), textoptions(textoptions) {}
  drawNode(int startTime, int v, string label, double x, double y, string shape, string color, string options, double scale, string textoptions) :
    drawNode(startTime, -1, v, label, x, y, shape, color, options, scale, textoptions) {}

	bool operator==(drawNode &o) {
		return o.v == v;
	}

	void draw() {
		if (endTime == -2)
			return;
        printf("\t\t\\tikzstyle{every node} = [scale=%0.1lf,", scale);
        if (shape != "")
            printf("shape = %s,", shape.c_str());
        if (color != "")
            printf("fill = %s,", color.c_str());
        printf("%s]\n", options.c_str());
        printf("\t\t\t\\node<%d-", startTime);
		if (endTime != -1)
			printf("%d", endTime);
		if (shape != "rectangle") {
        	printf("> (%d) at (%0.2lf, %0.2lf) {%s};\n", v, x, y, label.c_str());
		}
		else {
			printf("> (%d) at (%0.2lf, %0.2lf) {};\n", v, x, y);
			printf("\t\t\\tikzstyle{every node} = [%s]\n", textoptions.c_str());
	        printf("\t\t\t\\node<%d-", startTime);
			if (endTime != -1)
				printf("%d", endTime);
		    printf("> (%d) at (%0.2lf, %0.2lf) {%s};\n", v, x, y, label.c_str());
		}
	}
};
