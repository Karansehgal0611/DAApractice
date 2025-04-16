#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
};

bool onSegment(Point p, Point q, Point r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

int direction(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

bool segmentsIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = direction(p1, q1, p2);
    int o2 = direction(p1, q1, q2);
    int o3 = direction(p2, q2, p1);
    int o4 = direction(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}

int main() {
    Point p1, q1, p2, q2;
    cout << "Enter coordinates of first line segment (p1 and q1):\n";
    cout << "p1: ";
    cin >> p1.x >> p1.y;
    cout << "q1: ";
    cin >> q1.x >> q1.y;

    cout << "Enter coordinates of second line segment (p2 and q2):\n";
    cout << "p2: ";
    cin >> p2.x >> p2.y;
    cout << "q2: ";
    cin >> q2.x >> q2.y;

    if (segmentsIntersect(p1, q1, p2, q2))
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}

