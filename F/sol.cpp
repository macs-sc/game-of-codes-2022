#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-6;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }
};

pair<double, double> getSlope(Point a, Point b) {
    double m = (b.y - a.y) / (b.x - a.x);
    double bb  = b.y - m * b.x;
    return make_pair(m,bb);
}

Point getNextPoint(Point src, double y1, double y2, double alpha) {
    double dy = abs((alpha > 0 ? y2 : y1) - src.y);
    double dx = abs(dy / tan(alpha));
    return Point(src.x + dx, (alpha > 0 ? y2 : y1));
}

bool isEqual(double a, double b) {
    return abs(a - b) <= EPS;
}

double getPointInLine(Point a, Point b, double x) {
    auto slope = getSlope(a, b);
    double y_res = slope.first * x + slope.second;
    return y_res;
}

void solve() {
    double y1, y2;
    cin >> y1 >> y2;

    if (y1 > y2) {
        swap(y1, y2);
    }

    double xa, ya;
    cin >> xa >> ya;

    double alpha;
    cin >> alpha;

    alpha = alpha * PI / 180.0;

    double xb;
    cin >> xb;

    Point src(xa, ya);
    Point curr = getNextPoint(src, y1, y2, alpha);
    
    cout << setprecision(6) << fixed;

    if (isEqual(xb, curr.x)) {
        cout << curr.y << '\n';
        return;
    }

    if (xb <= curr.x) {
        cout << getPointInLine(src, curr, xb) << '\n';
        return;
    }

    Point nextt = getNextPoint(curr, y1, y2, -alpha);

    double y[2] = {y2, y1};
    if (alpha < 0) {
        swap(y[0], y[1]);
    }
    double step = nextt.x - curr.x;
    double dist = xb - curr.x;
    long long n = dist / step;

    // check if dst isBetween the n-th and n+1-th points
    Point prev(curr.x + n * step, y[n % 2]);
    Point last(curr.x + (n + 1) * step, y[(n + 1) % 2]);

    if (n == 0) {
        prev = curr;
        last = nextt;
    }

    cout << getPointInLine(prev, last, xb) << '\n';
}

int main() {
    solve();
}
