typedef vector<POINT> POLYGON;

double area2(POINT a, POINT b, POINT c) { return a%b + b%c + c%a; }

// Perimeter
double perimeter(POLYGON p)
{
    double peri = 0;

    for(int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        peri += (p[j] - p[i]).len();
    }
    return peri;
}

// Area
double signed_area(POLYGON p)
{
    double area = 0;

    for(int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return area / 2.0;
}
double area(POLYGON p) { return fabs(signed_area(p)); }

bool isConvex(const POLYGON& p)
{
    int sz = p.size();
    if(sz <= 2) return false;

    int isLeft = ccw(p[0], p[1], p[2]);

    for(int i = 1; i < sz; i++)
        if(ccw(p[i], p[(i + 1) % sz], p[(i + 2) % sz]) * isLeft < 0)
            return false;
    return true;
}