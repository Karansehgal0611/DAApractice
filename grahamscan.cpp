#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point {
    int x, y;
};

Point referencePoint;

Point getNextToTop(stack<Point>& pointsStack) {
    Point topPoint = pointsStack.top();
    pointsStack.pop();
    Point nextToTopPoint = pointsStack.top();
    pointsStack.push(topPoint);
    return nextToTopPoint;
}

void swapPoints(Point& point1, Point& point2) {
    Point temp = point1;
    point1 = point2;
    point2 = temp;
}

int squareDistance(Point point1, Point point2) {
    return (point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}

int findOrientation(Point p, Point q, Point r) {
    int value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (value == 0) return 0; // Collinear
    return (value > 0) ? 1 : 2; // Clockwise or counterclockwise
}

int comparePoints(const void* vp1, const void* vp2) {
    Point* point1 = (Point*)vp1;
    Point* point2 = (Point*)vp2;
    int orientation = findOrientation(referencePoint, *point1, *point2);
    if (orientation == 0) {
        return (squareDistance(referencePoint, *point2) >= squareDistance(referencePoint, *point1)) ? -1 : 1;
    }
    return (orientation == 2) ? -1 : 1;
}

void findConvexHull(Point points[], int numPoints) {
    int minYIndex = 0;
    for (int i = 1; i < numPoints; i++) {
        if ((points[i].y < points[minYIndex].y) ||
            (points[i].y == points[minYIndex].y && points[i].x < points[minYIndex].x)) {
            minYIndex = i;
        }
    }

    swapPoints(points[0], points[minYIndex]);
    referencePoint = points[0];
    qsort(&points[1], numPoints - 1, sizeof(Point), comparePoints);

    int m = 1;
    for (int i = 1; i < numPoints; i++) {
        while (i < numPoints - 1 && findOrientation(referencePoint, points[i], points[i + 1]) == 0) {
            i++;
        }
        points[m++] = points[i];
    }

    if (m < 3) {
        cout << "Convex hull not possible." << endl;
        return;
    }

    stack<Point> pointsStack;
    pointsStack.push(points[0]);
    pointsStack.push(points[1]);
    pointsStack.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (pointsStack.size() > 1 && findOrientation(getNextToTop(pointsStack), pointsStack.top(), points[i]) != 2) {
            pointsStack.pop();
        }
        pointsStack.push(points[i]);
    }

    cout << "The points in the convex hull are:\n";
    while (!pointsStack.empty()) {
        Point point = pointsStack.top();
        cout << "(" << point.x << ", " << point.y << ")" << endl;
        pointsStack.pop();
    }
}

int main() {
    int numPoints;
    cout << "Enter the number of points: ";
    cin >> numPoints;

    Point* points = new Point[numPoints];
    cout << "Enter the coordinates of the points (x y):" << endl;
    for (int i = 0; i < numPoints; i++) {
        cout << "Point " << i + 1 << ": ";
        cin >> points[i].x >> points[i].y;
    }

    findConvexHull(points, numPoints);
    delete[] points;

    return 0;
}

