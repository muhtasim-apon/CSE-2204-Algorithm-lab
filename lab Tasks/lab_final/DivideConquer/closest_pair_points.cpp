#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// Core: classic Divide & Conquer closest pair of points, O(n log n).
// NOTE: this exact problem is rare as a DIRECT LeetCode problem — it is
// mostly a CLRS/GfG staple. (LC has only loosely related sweep-line
// problems, e.g. LC 1499 Max Value of Equation, noted for context only —
// not implemented here as it solves a different objective.)
// =====================================================================
struct Pt { double x, y; };

static double dist(const Pt& a, const Pt& b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

static double bruteForce(vector<Pt>& pts, int l, int r, pair<int,int>& bestPair)
{
    double best = numeric_limits<double>::max();
    for (int i = l; i <= r; i++)
        for (int j = i + 1; j <= r; j++) {
            double d = dist(pts[i], pts[j]);
            if (d < best) { best = d; bestPair = {i, j}; }
        }
    return best;
}

static double closestRec(vector<Pt>& px, vector<Pt>& py, int l, int r, pair<int,int>& bestPair)
{
    if (r - l <= 2) return bruteForce(px, l, r, bestPair);

    int m = (l + r) / 2;
    double midX = px[m].x;

    vector<Pt> pyl, pyr;
    // partition py by x-coordinate relative to midX while keeping y-order
    for (auto& p : py) {
        if (p.x <= midX && (int)pyl.size() < (m - l + 1)) pyl.push_back(p);
        else pyr.push_back(p);
    }

    pair<int,int> bpL, bpR;
    double dl = closestRec(px, pyl, l, m, bpL);
    double dr = closestRec(px, pyr, m + 1, r, bpR);
    double d = min(dl, dr);
    bestPair = (dl < dr) ? bpL : bpR;

    // build strip of points within d of midX, sorted by y (py already is)
    vector<Pt> strip;
    vector<int> stripIdx; // index into px for the pair reporting
    for (int i = l; i <= r; i++) if (fabs(px[i].x - midX) < d) { strip.push_back(px[i]); stripIdx.push_back(i); }
    sort(strip.begin(), strip.end(), [](const Pt&a, const Pt&b){ return a.y < b.y; });
    // stripIdx must be reordered along with strip; simplest: recompute by sorting pairs together
    vector<pair<Pt,int>> stripPair;
    for (int i = l; i <= r; i++) if (fabs(px[i].x - midX) < d) stripPair.push_back({px[i], i});
    sort(stripPair.begin(), stripPair.end(), [](const pair<Pt,int>&a, const pair<Pt,int>&b){ return a.first.y < b.first.y; });

    for (size_t i = 0; i < stripPair.size(); i++) {
        for (size_t j = i + 1; j < stripPair.size() && (stripPair[j].first.y - stripPair[i].first.y) < d; j++) {
            double dd = dist(stripPair[i].first, stripPair[j].first);
            if (dd < d) { d = dd; bestPair = {stripPair[i].second, stripPair[j].second}; }
        }
    }
    return d;
}

void muhtasim()
{
    // ---------------- Core: closest pair of points (primary job) ----------------
    ll n;
    cin >> n;
    vector<Pt> pts(n);
    for (ll i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;

    if (n < 2) {
        cout << "Need at least 2 points\n";
    } else {
        vector<Pt> px = pts, py = pts;
        sort(px.begin(), px.end(), [](const Pt&a, const Pt&b){ return a.x < b.x; });
        sort(py.begin(), py.end(), [](const Pt&a, const Pt&b){ return a.y < b.y; });
        pair<int,int> bestPair;
        double best = closestRec(px, py, 0, (int)n - 1, bestPair);
        cout << fixed << setprecision(4);
        cout << "(" << px[bestPair.first].x << "," << px[bestPair.first].y << ") - ("
             << px[bestPair.second].x << "," << px[bestPair.second].y << ") dist=" << best << "\n";
    }

    // ---------------- Bundled demo / context section (run once) ----------------
    static bool demosShown = false;
    if (!demosShown) {
        demosShown = true;
        cout << "\n===== Brute-force cross-check on a small hardcoded set =====\n";
        {
            vector<Pt> demo = {{0,0}, {3,4}, {1,1}, {-2,-2}};
            pair<int,int> bp;
            double d = bruteForce(demo, 0, (int)demo.size() - 1, bp);
            cout << fixed << setprecision(4);
            cout << "(" << demo[bp.first].x << "," << demo[bp.first].y << ") - ("
                 << demo[bp.second].x << "," << demo[bp.second].y << ") dist=" << d << "\n";
            // expected closest pair (0,0)-(1,1), dist = sqrt(2) ~= 1.4142
        }
    }
}
int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);
ll tests;
cin>>tests;
while(tests--)
{
muhtasim();
}
}
