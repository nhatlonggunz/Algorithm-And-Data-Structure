#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_TO_RAD(double deg) { return deg * PI / 180.0; }
double RAD_TO_DEG(double rad) { return rad * 180.0 / PI; }

inline int cmp(double a, double b)  {
    return (a < b - EPS) ? -1 : (a > b + EPS ? 1 : 0);
}

struct POINT
{
    double x, y;
    POINT() { x = y = 0.0; }
    POINT(double X, double Y): x(X), y(Y) {}

    POINT operator +(const POINT& a) { return POINT(x + a.x, y + a.y); }
    POINT operator -(const POINT& a) { return POINT(x - a.x, y - a.y); }
    POINT operator *(double k) { return POINT(x*k, y*k); }
    POINT operator /(double k) { return POINT(x/k, y/k); }

    double operator *(const POINT& a) { return x*a.x + y*a.y; } // dot product
    double operator %(const POINT& a) { return x*a.y - y*a.x; } // cross product

    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    POINT rotate(double alpha) {
        double cosa = cos(alpha);
        double sina = sin(alpha);
        return POINT(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(POINT a, POINT b, POINT c) {
    return cmp((b - a) % (c - a), 0);
}

int RE_TRAI = ccw(POINT(0, 0), POINT(0, 1), POINT(-1, 1));
int RE_PHAI = ccw(POINT(0, 0), POINT(0, 1), POINT(1, 1));

double angle(POINT a, POINT o, POINT b) {
    a = a - o;
    b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

// angle AOB, in range [0, 2*PI)
double directed_angle(POINT a, POINT o, POINT b) {
    double t = -atan2(a.y - o.y, a.x - o.x)
               + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

istream& operator >>(istream& in, POINT& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator <<(ostream& out, POINT& p) {
    out << p.x << ' ' << p.y;
    return out;
}

// Distance from p to Line ab (closest Point --> c)
double distToLine(POINT p, POINT a, POINT b, POINT& c)
{
    POINT ap = p - a;
    POINT ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p - c).len();
}


// NOTE: will not work when a = b = 0;
struct LINE
{
    double a, b, c;

    LINE() { a = b = c = 0.0; }
    LINE(double A, double B, double C): a(A), b(B), c(C) {}
    LINE(POINT A, POINT B)
    {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    LINE(POINT A, double m)
    {
        a = -m;
        b = 1;
        c = -(a*A.x + b*A.y);
    }
    double f(POINT A) { return a*A.x + b*A.y + c; }
};

bool areParallel(LINE l1, LINE l2) {
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(LINE l1, LINE l2)
{
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0 &&
           cmp(l1.c*l2.b, l1.b*l2.c) == 0 &&
           cmp(l1.a*l2.c, l1.c*l2.a) == 0;
}

bool areIntersect(LINE l1, LINE l2, POINT &p)
{
    if(areParallel(l1, l2)) return false;

    double a1 = l1.a;       double a2 = l2.a;
    double b1 = l1.b;       double b2 = l2.b;
    double c1 = -l1.c;      double c2 = -l2.c;

    double D = a1*b2 - a2*b1;
    double Dx = c1*b2 - c2*b1;
    double Dy = a1*c2 - a2*c1;

    p = POINT(Dx/D, Dy/D);
    return true;
}

void closestPoint(LINE l, POINT p, POINT& ans)
{
    if(fabs(l.a) < EPS) {
        ans.x = p.x;    ans.y = -l.c / l.b;
        return;
    }
    if(fabs(l.b) < EPS) {
        ans.x = -l.c / l.a;     ans.y = p.y;
        return ;
    }
    LINE perp(l.b, -l.a, l.a * p.y - l.b * p.x);
    areIntersect(l, perp, ans);
}

void reflectionPoint(LINE l, POINT p, POINT& ans)
{
    POINT m;
    closestPoint(l, p, m);
    ans = POINT(2.0 * m.x - p.x, 2.0 * m.y - p.y);
}
