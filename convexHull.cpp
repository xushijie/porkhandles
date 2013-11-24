/* 
 * File:   convexHull.cpp
 * Author: shijiex
 *
 * Created on November 23, 2013, 10:41 AM
 */

#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

class Point {
    int _x, _y;
public:

    Point(int x, int y) : _x(x), _y(y) {
    }

    Point(const Point& point) : _x(point._x), _y(point._y) {
    }

    Point() : _x(512), _y(512) {
    }

    bool operator<(const Point& point) const {
        return _y < point._y || (_y == point._y && _x < point._x);
    }

    bool operator==(const Point& point) const {
        return _x == point._x && _y == point._y;
    }

    bool operator=(const Point& point) {
        _x = point._x;
        _y = point._y;
    }

    inline const int getX() {
        return _x;
    }

    inline const int getY() {
        return _y;
    }

    inline void toString() {
        cout << _x << " " << _y << endl;
    }
};

/**  return true if point2 - base is on the left side of point1 - base. Otherwise return false. 
 *      y-y0        y1-y0
 *      ------   = -------  => f(x,y) = (y-y0)*(x1-x0) - (x-x0)*(y1-y0)
 *       x-x0        x1-x0
 * 
 *    f(x,y) > 0  if (x,y) on the left side of line.  else on the right side.
 *   Use this to avoid arctan float time-consuming computing
 *  a*b  right, or left.
 * @param base
 * @param point1
 * @param point2
 * @return 
 */
bool isLeftSide(Point& point, Point& point1, Point& point2) {
    Point p1(point1.getX() - point.getX(), point1.getY() - point.getY());
    Point p2(point2.getX() - point.getX(), point2.getY() - point.getY());
    return (p1.getX() * p2.getY() - p2.getX() * p1.getY()) > 0;

    //    if(point2.getX() == base.getX()) {
    //        return point1.getX() >= base.getX();
    //    }
    //    return ( point2.getY() - base.getY())*( point1.getX() - base.getX()) -
    //           ( point2.getX() - base.getX())*( point1.getY() - base.getY()) >=0;
    //    
}

void printPoint(Point& point) {
    point.toString();
}

class ConvexHull {
    std::stack<Point> _convexPoints;
    vector<Point> _output;
    Point _start;
public:

    ConvexHull(vector<Point>& points) {

        sort(points.begin(), points.end());
        //for_each(points.begin(), points.end(), printPoint);

        for (std::vector<Point>::iterator iter = points.begin();
                iter != points.end();
                iter++) {
            Point point = *iter;
            if (_convexPoints.size() != 0 && point == _convexPoints.top()) continue;
            while (_convexPoints.size() > 1) {
                Point point1 = _convexPoints.top();
                _convexPoints.pop();
                Point base = _convexPoints.top();
                //Point base = points.at(count-3);   //Use the point in the vector
                if (isLeftSide(base, point1, point)) {
                    _convexPoints.push(point1); //push poped point back
                    break;
                }
            }
            _convexPoints.push(point); //push current points
        }
        int minSize = _convexPoints.size();

        for (std::vector<Point>::reverse_iterator iter = points.rbegin();
                iter != points.rend(); iter++) {
            Point current = *iter;
            Point point1 = _convexPoints.top();
            //if(point1==current) continue;
            _convexPoints.pop();
            Point base = _convexPoints.top();
            while (_convexPoints.size() >= minSize && isLeftSide(base, point1, current) == false) {
                //cout<<"   pop ";  point1.toString();
                point1 = base;
                _convexPoints.pop();
                base = _convexPoints.top();
            }
            _convexPoints.push(point1);
            _convexPoints.push(current);
            //cout<<" push "<<_convexPoints.size()<<"  "; _convexPoints.top().toString();
        }

        //        points.clear();
        //        while(!_convexPoints.empty()){
        //            points.push_back(_convexPoints.top());
        //            _convexPoints.pop();
        //        }
        Point* end = &_convexPoints.top() + 1;
        Point* begin = end - _convexPoints.size();
        std::vector<Point> stack_contents(begin, end);
        cout << stack_contents.size() << endl;
        for_each(stack_contents.begin(), stack_contents.end(), printPoint);
    }

};

/*
 * 
 */
int main(int argc, char** argv) {
    int datasets = 0;
    cin >> datasets;
    cout << datasets << endl;
    while (datasets-- > 0) {
        int noPoints = 0;
        cin >> noPoints;
        if (noPoints < 3) continue; // Just skip if number of points is less than 3. 
        //priority_queue<Point, vector<Point>, std::greater<Point> > points;
        vector<Point> points;
        for (int i = 0; i < noPoints; i++) {
            int x = 0, y = 0;
            cin >> x;
            cin >> y;
            points.push_back(Point(x, y));
        }
        cin >> noPoints; //This should be -1, just discard it and then for next datasets
        ConvexHull builder(points);

        if (datasets != 0) cout << -1 << endl;
    }
    return 0;
}

