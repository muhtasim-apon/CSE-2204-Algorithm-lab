#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// Core (primary job, no instructor exact-spec given for this file):
// LC 797 All Paths From Source to Target — DAG given as adjacency list,
// enumerate every path from node 0 to node n-1.
// =====================================================================
static void lc797(vector<vector<int>>& graph, int node, int target, vector<int>& path, vector<vector<int>>& res)
{
    path.push_back(node);
    if (node == target) { res.push_back(path); }
    else {
        for (int nxt : graph[node]) lc797(graph, nxt, target, path, res);
    }
    path.pop_back();
}

// =====================================================================
// LC 79: Word Search — does `word` exist in a 2D board via adjacent cells?
// =====================================================================
static bool lc79Dfs(vector<vector<char>>& board, const string& word, int i, int j, int idx, vector<vector<bool>>& vis)
{
    if (idx == (int)word.size()) return true;
    if (i < 0 || j < 0 || i >= (int)board.size() || j >= (int)board[0].size()) return false;
    if (vis[i][j] || board[i][j] != word[idx]) return false;
    vis[i][j] = true;
    bool found = lc79Dfs(board, word, i+1, j, idx+1, vis) || lc79Dfs(board, word, i-1, j, idx+1, vis) ||
                 lc79Dfs(board, word, i, j+1, idx+1, vis) || lc79Dfs(board, word, i, j-1, idx+1, vis);
    vis[i][j] = false;
    return found;
}

// =====================================================================
// LC 51/52: N-Queens — 51 enumerates board layouts, 52 counts solutions.
// =====================================================================
static void nQueens(int n, int row, vector<int>& cols, vector<bool>& usedCol, vector<bool>& usedD1, vector<bool>& usedD2, int& count, vector<vector<int>>* boards)
{
    if (row == n) {
        count++;
        if (boards) boards->push_back(cols);
        return;
    }
    for (int c = 0; c < n; c++) {
        int d1 = row - c + n, d2 = row + c;
        if (usedCol[c] || usedD1[d1] || usedD2[d2]) continue;
        usedCol[c] = usedD1[d1] = usedD2[d2] = true;
        cols.push_back(c);
        nQueens(n, row + 1, cols, usedCol, usedD1, usedD2, count, boards);
        cols.pop_back();
        usedCol[c] = usedD1[d1] = usedD2[d2] = false;
    }
}

// =====================================================================
// LC 93: Restore IP Addresses
// =====================================================================
static void lc93(const string& s, int idx, int part, vector<string>& cur, vector<string>& res)
{
    if (part == 4) { if (idx == (int)s.size()) { string ip = cur[0]+"."+cur[1]+"."+cur[2]+"."+cur[3]; res.push_back(ip); } return; }
    for (int len = 1; len <= 3 && idx + len <= (int)s.size(); len++) {
        string seg = s.substr(idx, len);
        if (len > 1 && seg[0] == '0') break;      // no leading zero for multi-digit
        if (stoi(seg) > 255) break;
        cur.push_back(seg);
        lc93(s, idx + len, part + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 131: Palindrome Partitioning
// =====================================================================
static bool isPalin(const string& s, int l, int r) { while (l < r) if (s[l++] != s[r--]) return false; return true; }
static void lc131(const string& s, int idx, vector<string>& cur, vector<vector<string>>& res)
{
    if (idx == (int)s.size()) { res.push_back(cur); return; }
    for (int end = idx; end < (int)s.size(); end++) {
        if (isPalin(s, idx, end)) {
            cur.push_back(s.substr(idx, end - idx + 1));
            lc131(s, end + 1, cur, res);
            cur.pop_back();
        }
    }
}

// =====================================================================
// LC 980: Unique Paths III — enumerate all paths visiting every non-obstacle
// cell exactly once, from the single start (1) to the single end (2).
// =====================================================================
static int uniquePaths3Count = 0;
static void lc980(vector<vector<int>> grid, int i, int j, int remaining)
{
    int rows = grid.size(), cols = grid[0].size();
    if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == -1) return;
    if (grid[i][j] == 2) { if (remaining == 0) uniquePaths3Count++; return; }
    int backup = grid[i][j];
    grid[i][j] = -1; // mark visited
    lc980(grid, i+1, j, remaining - 1);
    lc980(grid, i-1, j, remaining - 1);
    lc980(grid, i, j+1, remaining - 1);
    lc980(grid, i, j-1, remaining - 1);
    grid[i][j] = backup;
}

void muhtasim()
{
    // ---------------- Core: LC 797 All Paths From Source to Target ----------------
    // Input: n (nodes 0..n-1), m (edges), then m pairs "u v" meaning u->v.
    // Prints every path from node 0 to node n-1.
    ll n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (ll i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    vector<int> path;
    vector<vector<int>> res;
    lc797(graph, 0, (int)n - 1, path, res);
    for (auto& p : res) {
        for (size_t i = 0; i < p.size(); i++) cout << p[i] << (i + 1 < p.size() ? ' ' : '\n');
    }

    // ---------------- Bundled LeetCode demo sections (run once) ----------------
    static bool demosShown = false;
    if (!demosShown) {
        demosShown = true;

        cout << "\n===== LC 79: Word Search (demo board, word=\"ABCCED\") =====\n";
        {
            vector<vector<char>> board = {
                {'A','B','C','E'},
                {'S','F','C','S'},
                {'A','D','E','E'}
            };
            vector<vector<bool>> vis(board.size(), vector<bool>(board[0].size(), false));
            bool found = false;
            for (int i = 0; i < (int)board.size() && !found; i++)
                for (int j = 0; j < (int)board[0].size() && !found; j++)
                    if (lc79Dfs(board, "ABCCED", i, j, 0, vis)) found = true;
            cout << (found ? "true" : "false") << "\n"; // expected true
        }

        cout << "\n===== LC 51/52: N-Queens (demo N=4 and N=8) =====\n";
        {
            for (int N : {4, 8}) {
                vector<int> cols;
                vector<bool> uc(N, false), ud1(2*N, false), ud2(2*N, false);
                int cnt = 0;
                vector<vector<int>> boards;
                nQueens(N, 0, cols, uc, ud1, ud2, cnt, N == 4 ? &boards : nullptr);
                cout << "N=" << N << " solutions=" << cnt << "\n"; // expected 2 (N=4), 92 (N=8)
                if (N == 4) {
                    cout << "  (LC51 sample layouts as column-index rows):\n";
                    for (auto& b : boards) {
                        cout << "  ";
                        for (int c : b) cout << c << ' ';
                        cout << "\n";
                    }
                }
            }
        }

        cout << "\n===== LC 93: Restore IP Addresses (demo \"25525511135\") =====\n";
        {
            vector<string> cur, res2;
            lc93("25525511135", 0, 0, cur, res2);
            for (auto& s : res2) cout << s << "\n";
        }

        cout << "\n===== LC 131: Palindrome Partitioning (demo \"aab\") =====\n";
        {
            vector<string> cur; vector<vector<string>> res2;
            lc131("aab", 0, cur, res2);
            for (auto& part : res2) {
                cout << "{ "; for (auto& s : part) cout << s << ' '; cout << "}\n";
            }
        }

        cout << "\n===== LC 980: Unique Paths III (demo grid) =====\n";
        {
            // 1 = start, 2 = end, 0 = walkable, -1 = obstacle
            vector<vector<int>> grid = {
                {1, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 2, -1}
            };
            int nonObstacle = 0, si = -1, sj = -1;
            for (int i = 0; i < (int)grid.size(); i++)
                for (int j = 0; j < (int)grid[0].size(); j++) {
                    if (grid[i][j] != -1) nonObstacle++;
                    if (grid[i][j] == 1) { si = i; sj = j; }
                }
            uniquePaths3Count = 0;
            lc980(grid, si, sj, nonObstacle - 1);
            cout << "path count = " << uniquePaths3Count << "\n"; // expected 2
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
