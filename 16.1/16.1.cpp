#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 700;
int t, n, m;

void read (string name, vector<string>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	
	file.close();
}

int been[N][N];

bool inside (int x, int y, int n, int m) {
	if (x < 0 || y < 0 || x >= n || y >= m) return false;
	return true;
}

bool canGo (int x, int y, int dir, int n, int m) {
	if (!inside(x, y, n, m)) return false;
	if ((been[x][y]&dir) == 0) return true;
	return false;
}

void debug (int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << (been[i][j]!=0);
		}
		cout << endl;
	}
}

void solve (vector<string> &v) {
	int x = 0, y = 0;
	int dir = 1; // 1 >, 2 ¡, 4 <, 8 ^
	int dx[] = {-1, 0, 0, 1};
	int dy[] = {0, -1, 1, 0};
	
	queue<pair<pair<int, int>, int> >q;
	int n = v.size(), m = v[0].size();
	//for (int i = 0; i < n; i++) cout << v[i] << endl;
	q.push({{0, 0}, 1});
	been[0][0] = 1;
	
	while (q.size()) {
		pair<pair<int, int>, int> pos = q.front();
		q.pop();
		int x = pos.first.first;
		int y = pos.first.second;
		int dir = pos.second;
		char z = v[x][y];
		//debug(n, m);
		//cout << x << " " << y << " " << dir << endl;
		//system("pause");
		if (z == '.') {
			if (dir == 1) y++;
			if (dir == 2) x++;
			if (dir == 4) y--;
			if (dir == 8) x--;
			if (canGo(x, y, dir, n, m)) {
				been[x][y] |= dir;
				q.push({{x, y,}, dir});
			}
		}
		if (z == '\\') {
			if (dir == 1) x++;
			if (dir == 2) y++;
			if (dir == 4) x--;
			if (dir == 8) y--;
			if (dir <= 2) dir = 2/dir;
			if (dir >= 4) dir = 32/dir;
			if (canGo(x, y, dir, n, m)) {
				been[x][y] |= dir;
				q.push({{x, y}, dir});
			}
		}
		if (z == '/') {
			if (dir == 1) x--;
			if (dir == 2) y--;
			if (dir == 4) x++;
			if (dir == 8) y++;
			dir = 8/dir;
			if (canGo(x, y, dir, n, m)) {
				been[x][y] |= dir;
				q.push({{x, y}, dir});
			}
		}		
		if (z == '-') {	
			if (dir == 1) y++;
			if (dir == 4) y--;
			if ((dir == 1 || dir == 4) && canGo(x, y, dir, n, m)) {
				been[x][y] |= dir;
				q.push({{x, y}, dir});
				continue;
			}
			if (dir == 2 || dir == 8) {
				if (canGo(x, y+1, 1, n, m)) {
					been[x][y+1] |= 1;
					q.push({{x, y+1}, 1});
				}
				if (canGo(x, y-1, 4, n, m)) {
					been[x][y-1] |= 4;
					q.push({{x, y-1}, 4});
				}
			}
		}
		if (z == '|') {
			if (dir == 2) x++;
			if (dir == 8) x--;
			if ((dir == 2 || dir == 8) && canGo(x, y, dir, n, m)) {
				been[x][y] |= dir;
				q.push({{x, y}, dir});
				continue;
			}
			if (dir == 1 || dir == 4) {
				if (canGo(x+1, y, 2, n, m)) {
					been[x+1][y] |= 2;
					q.push({{x+1, y}, 2});
				}
				if (canGo(x-1, y, 8, n, m)) {
					been[x-1][y] |= 8;
					q.push({{x-1, y}, 8});
				}
			}
		}
	}
	int sol = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			sol += (been[i][j]!=0);
		}
	}
	cout << sol;
	
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
    read("input.txt", v);
	solve(v);

return 0;
}

