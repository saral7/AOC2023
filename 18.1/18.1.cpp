#include <bits/stdc++.h>

using namespace std;
#define lli long long int

struct str {
	char z;
	int d;
	string col;
};

void parse (string line, char &z, int &d, string &col) {
	col = "";
	d = 0;
	int i;
	z = line[0];
	
	for (i = 2; i < line.size() && line[i] != ' '; i++) {
		d = 10*d+(line[i]-'0');
	}
	i+=2;
	for (; i < line.size() && line[i] != ')'; i++) {
		col += line[i];
	}
	return;
}

void read (string name, vector<str>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		str curr;
		parse (line, curr.z, curr.d, curr.col);
		v.push_back(curr);
	}
	
	file.close();
}

const int N = 407;
char grid[N][N];

bool inside (int x, int y, int n, int m) {
	if (x < 0 || y < 0 || x >= n || y >= m) return false;
	return true;
}

void bfs (queue<pair<int, int> >q, int n, int m) {
	int dx[] = {-1, 0, 0, 1};
	int dy[] = {0, -1, 1, 0};
	
	while (q.size()) {
		pair<int, int>curr = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int susx = curr.first+dx[k];
			int susy = curr.second+dy[k];
			
			if (inside(susx, susy, n, m) && grid[susx][susy] != '#') {
				grid[susx][susy] = '#';
				q.push({susx, susy});
			}
		}
	}
}

void solve (vector<str>&v) {
	int x = 0, y = 0;
	int dx, dy;
	int n = 0, m = 0;
	int minin = 1e7, minim = 1e7;
	for (int i = 0; i < v.size(); i++) {
		char z = v[i].z;
		dx = dy = 0;
		if (z == 'R') dy = 1;
		if (z == 'L') dy = -1;
		if (z == 'D') dx = 1;
		if (z == 'U') dx = -1;
		for (int k = 0; k < v[i].d; k++) {
			x += dx, y += dy;
			//grid[x][y] = '#';
		}
		//cout << x << " " << y << endl; 
		n = max(n, x);
		m = max(m, y);
		minin = min(minin, x);
		minim = min(minim, y);
	}
	n = n-minin+1;
	m = m-minim+1;
	int offx = -minin, offy = -minim;
	x = y = 0;
	grid[x+offx][y+offy] = '#';
	for (int i = 0; i < v.size(); i++) {
		char z = v[i].z;
		dx = dy = 0;
		if (z == 'R') dy = 1;
		if (z == 'L') dy = -1;
		if (z == 'D') dx = 1;
		if (z == 'U') dx = -1;
		for (int k = 0; k < v[i].d; k++) {
			x += dx, y += dy;
			grid[x+offx][y+offy] = '#';
		}
	}
	x = 1;
	y = 0;
	while (grid[x][y++] != '#');
	queue<pair<int, int> >q;
	q.push({x, y});
	bfs(q, n, m);
	int sol = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			sol += (grid[i][j] == '#');
		}
	}
	cout << sol << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<str>v;
    read ("input.txt", v);
	solve(v);

return 0;
}

