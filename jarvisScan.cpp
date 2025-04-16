#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

int findOrientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

void findConvexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        cout << "Convex hull not possible with less than 3 points." << endl;
        return;
    }
    vector<Point> convexHull;
    int leftmostPointIndex = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmostPointIndex].x)
            leftmostPointIndex = i;
    }
    int p = leftmostPointIndex, q;
    do {
        convexHull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (findOrientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        p = q;
    } while (p != leftmostPointIndex);
    cout << "Points in the convex hull:\n";
    for (const auto& point : convexHull) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;
    vector<Point> points(n);
    cout << "Enter the coordinates of the points (x and y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Point " << i + 1 << ": ";
        cin >> points[i].x >> points[i].y;
    }
    findConvexHull(points);
    return 0;
}

