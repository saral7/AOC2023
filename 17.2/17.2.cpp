#include <bits/stdc++.h>

using namespace std;
#define lli long long int

void read (string name, vector<vector<int> > &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		vector<int>pom;
		for (int i = 0; i < line.size(); i++) {
			pom.push_back((line[i]-'0'));
		}
		v.push_back(pom);
	}
	file.close();
}

class Position {
public:
	int dist;
	int x, y;
	int dir;
	int step;
	
	Position(int dist, int x, int y, int dir, int step) {
		this->dir = dir;
		this->x = x;
		this->y = y;
		this->dist = dist;
		this->step = step;
	}
	
	/*friend bool operator < (Position &a, Position &b) {
		if (a.dist != b.dist) return a.dist < b.dist;
		return false; 
	} */
};

bool inside (int x, int y, int n, int m) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

const int N = 200, INF = 1e7;
int dist[4][N][N];

void debug (int n, int m, int k) {
	cout << k << ": " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dist[k][i][j] << " ";
		}
		cout << endl;
	}
}

void backtrack(int x, int y, int d, int dir, int n, int m, vector<vector<int> >&v) {
	if (x == 0 && y == 0) {
		cout << 0 << " " << 0 << endl;
		return;
	}
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};
	int val = 0;
	
	for (int k = 4; k <= 10; k++) {
		int susx = x+k*dx[dir];
		int susy = y+k*dy[dir];
		
		if (!inside(susx, susy, n, m)) continue;
		
		int val = 0;
		if (dx[dir]) {
			for (int j = 0; j < k; j++) {
				val += v[x+j*dx[dir]][y];
			}
		}
		else {
			for (int j = 0; j < k; j++) {
				val += v[x][y+j*dy[dir]];
			}
		}
		cout << val << endl;
		for (int i = 0; i < 4; i++) {
			if (i == dir) continue;
			if (d-val == dist[i][susx][susy]) {
				cout << susx << " " << susy << endl;
				backtrack(susx, susy, d-val, i, n, m, v);
				return;
			}
		}
	}
}

void solve (vector<vector<int> > &v) {
	set<pair<pair<int, int>, pair<int, int> > >s;
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};
	int n = v.size(), m = v[0].size();
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//cout << v[i][j];
			dist[0][i][j] = dist[1][i][j] = dist[2][i][j] = dist[3][i][j] = INF;
		}
		//cout << endl;
	}
	
	int valx = 0, valy = 0;
	for (int k = 1; k <= 10; k++) {
		valx += v[0][k];
		valy += v[k][0];
		if (k < 4) continue;
		dist[1][0][k] = valx;
		dist[2][k][0] = valy;
		s.insert({{valx, 1}, {0, k}});
		s.insert({{valy, 2}, {k, 0}});
	}
	
	
	while (s.size()) {
		pair<pair<int, int>, pair<int, int> > curr = *s.begin();
		s.erase(s.begin());
		
		int x = curr.second.first;
		int y = curr.second.second;
		int dir = curr.first.second;
		int d = curr.first.first;
		//cout << x << " " << y << " " << dir << ": " << d << endl;
		
		for (int k = 4; k <= 10; k++) {
			for (int i = 0; i < 4; i++) {
				if (i == dir || abs(i-dir) == 2) continue;
				int susx = x + k*dx[i];
				int susy = y + k*dy[i];
				
				if (!inside(susx, susy, n, m)) continue;
				int val = 0;
				if (dx[i]) {
					for (int j = 1; j <= k; j++) {
						val += v[x+j*dx[i]][y];
					}
				}
				else {
					for (int j = 1; j <= k; j++) {
						val += v[x][y+j*dy[i]];
					}
				}
				if (dist[i][susx][susy] > d+val) {
					//cout << "sus: " << susx << " " << susy << " " << i << endl;
					s.erase({{dist[i][susx][susy], i}, {susx, susy}});
					dist[i][susx][susy] = d+val;
					s.insert({{dist[i][susx][susy], i}, {susx, susy}});
				}
			}
		}//system("pause");
	}
	//debug (n, m, 0);
	//debug (n, m, 1);
	//debug (n, m, 2);
	//debug (n, m, 3);
	cout << min(dist[1][n-1][m-1], dist[2][n-1][m-1]);
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vector<int> >v;
    read ("input.txt", v);
	solve(v);

return 0;
}

