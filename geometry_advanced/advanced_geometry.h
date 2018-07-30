#include "draw_queue.h"

drawQueue drawQ;

vector<double> x = {1.3, 1.7, 3.7, 3.5, 3.9};
vector<double> y = {0, 1.7, 1.7, 1, 0.3};

const double PI = acos(-1.0);
const double eps = 1e-9;

double sqr(double a) {
    return a * a;
}

double point_dis(point a, point b) {
    return sqrt(sqr(b.x - a.x) + sqr(b.y - a.y));
}

double point_angle(point p) {
    double angle = atan2(p.y, p.x);

    return (angle >= 0) ? angle : (angle + 2 * PI);
}

double point_dot(point a, point b, point c) {
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

double point_angle(point a, point b, point c) {
    return acos(point_dot(a, b, c) / (point_dis(a, b) * point_dis(a, c)));
}

double point_cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double point_cw(point a, point b, point c) {
    return point_cross(a, b, c) <= 0;
}

double point_ccw(point a, point b, point c) {
    return point_cross(a, b, c) >= 0;
}

double triangle_area(point a, point b, point c) {
    return fabs(point_cross(a, b, c)) / 2.0;
}

struct line {
    double a, b, c;

    line() {}
    line(double a, double b, double c):  a(a), b(b), c(c) {}
};

line line_build(point p1, point p2) {
    line l;

    l.a = p2.y - p1.y;
    l.b = -(p2.x - p1.x);
    l.c = p1.y * p2.x - p1.x * p2.y;

    return l;
}

double line_val(line l, point p) {
    return l.a * p.x + l.b * p.y + l.c;
}

line line_normalize(line l) {
    double len = sqrt(sqr(l.a) + sqr(l.b));

    return line(l.a / len, l.b / len, l.c / len);
}

double line_dis(line l, point p) {
    l = line_normalize(l);

    return fabs(line_val(l, p));
}

double det(double a1, double b1, double a2, double b2) {
    return a1 * b2 - b1 * a2;
}

bool line_parallel(line l1, line l2) {
    return fabs(det(l1.a, l1.b, l2.a, l2.b)) < eps;
}

bool line_equivalent(line l1, line l2) {
    return fabs(det(l1.a, l1.b, l2.a, l2.b)) < eps &&
           fabs(det(l1.c, l1.b, l2.c, l2.b)) < eps &&
           fabs(det(l1.a, l1.c, l2.a, l2.c)) < eps;
}

bool line_intersect(line l1, line l2, point& p) {
    double val = det(l1.a, l1.b, l2.a, l2.b);

    if (fabs(val) < eps) {
        return false;
    }

    p.x = -det(l1.c, l1.b, l2.c, l2.b) / val;
    p.y = -det(l1.a, l1.c, l2.a, l2.c) / val;

    return true;
}

bool segment_intersect(int a1, int a2, int b1, int b2) {
    if (a1 > a2) {
        swap(a1, a2);
    }
    if (b1 > b2) {
        swap(b1, b2);
    }

    return max(a1, b1) <= min(a2, b2);
}

bool segment_intersect(point a1, point a2, point b1, point b2) {
    line la = line_build(a1, a2);
    line lb = line_build(b1, b2);

    return segment_intersect(a1.x, a2.x, b1.x, b2.x) &&
           segment_intersect(a1.y, a2.y, b1.y, b2.y) &&
           line_val(la, b1) * line_val(la, b2) <= 0 &&
           line_val(lb, a1) * line_val(lb, a2) <= 0;
}

double segment_dis(point a1, point a2, point p) {
    if (point_dot(a1, a2, p) >= -eps && point_dot(a2, a1, p) >= -eps) {
        line l = line_build(a1, a2);

        return line_dis(l, p);
    }

    return min(point_dis(a1, p), point_dis(a2, p));
}

double segment_dis(point a1, point a2, point b1, point b2) {
    if (segment_intersect(a1, a2, b1, b2)) {
        return 0;
    }

    return min(min(segment_dis(a1, a2, b1), segment_dis(a1, a2, b2)),
               min(segment_dis(b1, b2, a1), segment_dis(b1, b2, a2)));
}

bool segment_intersect(point a1, point a2, point b1, point b2, point &p) {
    line la = line_build(a1, a2);
    line lb = line_build(b1, b2);

    return segment_intersect(a1.x, a2.x, b1.x, b2.x) &&
           segment_intersect(a1.y, a2.y, b1.y, b2.y) &&
           line_val(la, b1) * line_val(la, b2) <= 0 &&
           line_val(lb, a1) * line_val(lb, a2) <= 0;
}
