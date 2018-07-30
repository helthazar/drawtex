#include "draw_node.h"
#include "draw_edge_weighted.h"
#include "draw_polygon.h"

class drawQueue {
	int timer;

	vector<pair<int, int> > indexQueue;

	vector<drawEdge> drawEdgeQueue;
	vector<drawEdgeWeighted> drawEdgeWeightedQueue;
	vector<drawNode> drawNodeQueue;
	vector<drawPolygon> drawPolygonQueue;

public:
	drawQueue() {
		timer = 1;
	}

	void addEdge(int from, int to, string color, bool oriented = false, string curve = "--") {
		drawEdge e(timer, from, to, color, oriented, curve);
		for (int i = drawEdgeQueue.size() - 1; i >= 0; i--) {
			drawEdge &ei = drawEdgeQueue[i];
			if (ei == e && ei.getEndTime() == -1) {
				ei.setEndTime(timer - 1);
				break;
			}
		}
		indexQueue.push_back(make_pair(1, (int) drawEdgeQueue.size()));
		drawEdgeQueue.push_back(e);
	}

	void removeEdge(int from, int to) {
		drawEdge e(timer, from, to, "", false, "");
		for (int i = drawEdgeQueue.size() - 1; i >= 0; i--) {
			drawEdge &ei = drawEdgeQueue[i];
			if (ei == e && ei.getEndTime() == -1) {
				ei.setEndTime(timer - 1);
				break;
			}
		}
	}

	void addEdgeWeighted(int from, int to, string color, string weight, string weightDirection, bool oriented = false, string curve = "--") {
		drawEdgeWeighted e(timer, from, to, color, weight, weightDirection, oriented, curve);
		for (int i = drawEdgeWeightedQueue.size() - 1; i >= 0; i--) {
			drawEdge &ei = drawEdgeWeightedQueue[i];
			if (ei == e && ei.getEndTime() == -1) {
				ei.setEndTime(timer - 1);
				break;
			}
		}
		indexQueue.push_back(make_pair(2, (int) drawEdgeWeightedQueue.size()));
		drawEdgeWeightedQueue.push_back(e);
	}

	void removeEdgeWeighted(int from, int to) {
		drawEdgeWeighted e(timer, from, to, "", "", "", false, "");
		for (int i = drawEdgeWeightedQueue.size() - 1; i >= 0; i--) {
			drawEdge &ei = drawEdgeWeightedQueue[i];
			if (ei == e && ei.getEndTime() == -1) {
				ei.setEndTime(timer - 1);
				break;
			}
		}
	}

	void addNode(int v, string label, double x, double y, string shape = "", string color = "", string options = "", double scale = 1.0, string textoptions = "") {
		drawNode n(timer, v, label, x, y, shape, color, options, scale, textoptions);
		for (int i = drawNodeQueue.size() - 1; i >= 0; i--) {
			drawNode &ni = drawNodeQueue[i];
			if (ni == n && ni.getStartTime() == n.getStartTime() && ni.getEndTime() != -2) {
				ni = n;
				return;
			}
			if (ni == n && ni.getEndTime() == -1) {
				ni.setEndTime(timer - 1);
				break;
			}
		}
		indexQueue.push_back(make_pair(3, (int) drawNodeQueue.size()));
		drawNodeQueue.push_back(n);
	}

	void addCircleNode(int v, string label, double x, double y, string color = "", string options = "", double scale = 0.8, string textoptions = "") {
		addNode(v, label, x, y, "circle", color, options, scale, textoptions);
	}

	void addRectangleNode(int v, string label, double x, double y, string color = "", string options = "", double scale = 2.0, string textoptions = "") {
		addNode(v, label, x, y, "rectangle", color, options, scale, textoptions);
	}

	void removeNode(int v) {
		drawNode n(timer, v, "", 0, 0, "", "", "", 1, "");
		for (int i = drawNodeQueue.size() - 1; i >= 0; i--) {
			drawNode &ni = drawNodeQueue[i];
			if (ni == n && ni.getEndTime() == -1) {
				ni.setEndTime(timer - 1);
				break;
			}
		}
	}

	void eraseNode(int v) {
		drawNode n(timer, v, "", 0, 0, "", "", "", 1, "");
		for (int i = drawNodeQueue.size() - 1; i >= 0; i--) {
			drawNode &ni = drawNodeQueue[i];
			if (ni == n && ni.getEndTime() == -1) {
				ni.setEndTime(-2);
				break;
			}
		}
	}

	void addPolygonNode(vector<point> v, string edgeColor, string fillColor, double fillOpacity) {
		drawPolygon p(timer, v, edgeColor, fillColor, fillOpacity);
		for (int i = drawPolygonQueue.size() - 1; i >= 0; i--) {
			drawPolygon &pi = drawPolygonQueue[i];
			if (pi == p && pi.getStartTime() == p.getStartTime()) {
				pi = p;
				return;
			}
			if (pi == p && pi.getEndTime() == -1) {
				pi.setEndTime(timer - 1);
				break;
			}
		}
		indexQueue.push_back(make_pair(4, (int) drawPolygonQueue.size()));
		drawPolygonQueue.push_back(p);
	}

	void increaseTimer() {
		timer++;
	}

	void decreaseTimer() {
		timer--;
	}

	void draw() {
		for (int i = 0; i < indexQueue.size(); i++) {
			int type = indexQueue[i].first;
			int position = indexQueue[i].second;
			if (type == 1) {
				drawEdgeQueue[position].draw();
			}
			else if (type == 2) {
				drawEdgeWeightedQueue[position].draw();
			}
			else if (type == 3) {
				drawNodeQueue[position].draw();
			}
			else if (type == 4) {
				drawPolygonQueue[position].draw();
			}
		}
	}
};
