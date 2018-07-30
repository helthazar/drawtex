#include <bits/stdc++.h>

using namespace std;

#ifndef DRAW_OBJECT
#define DRAW_OBJECT

class drawObject {
protected:
	int startTime;
	int endTime;

public:
	drawObject(int startTime, int endTime) :
		startTime(startTime), endTime(endTime) {}
	drawObject() {}

    int getStartTime() {
        return startTime;
    }

	int getEndTime() {
		return endTime;
	}

	void setEndTime(int endTime) {
		this->endTime = endTime;
	}

	virtual void draw() {}
};

#endif
