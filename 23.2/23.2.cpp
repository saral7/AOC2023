#include <bits/stdc++.h>

using namespace std;
#define lli long long int

void read (string name, vector<string>&v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();
}
const int N = 507;
int dp[N][N];
bool active[N][N];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int findMax (int x, int y, vector<string>&v) {
	//if (dp[x][y] != -1) return dp[x][y];
	//cout << x << " " << y << endl;
	//system("pause");
	if (x == v.size()-1 && y == v[0].size()-2) {
		return 1;
	}
	
	active[x][y] = true;
	int maxVal = 0;
	
	for (int i = 0; i < 4; i++) {
		int susx = x+dx[i];
		int susy = y+dy[i];
		
		if (!(0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size())) continue;
		if (active[susx][susy] || v[susx][susy] == '#') continue;
		
		maxVal = max(maxVal, findMax(susx, susy, v));
	}
	
	active[x][y] = false;
	return maxVal+1;
}

vector<pair<int, int> >graph[N];

pair<int, int> findIntersection(int x, int y, int parx, int pary, vector<string> &v, map<pair<int, int>, int> &m) {
	if (m.count({x, y})) return {m[{x, y}], 0};
	
	for (int i = 0; i < 4; i++) {
		int susx = x+dx[i];
		int susy = y+dy[i];
		
		if (!(0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size())) continue;
		if (v[susx][susy] == '#') continue;
		if (susx == parx && susy == pary) continue;
		
		pair<int, int> pom = findIntersection(susx, susy, x, y, v, m);
		pom.second++;
		return pom;
	}
}

void solve (vector<string>&v) {
	memset (dp, -1, sizeof(dp));
	int sol = 0;
	map<pair<int, int>, int>m;
	cout << v.size() << endl;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[0].size(); j++) {
			int cnt = 0;
			if (v[i][j] == '#') continue;
			for (int k = 0; k < 4; k++) {
				int susx = i+dx[k];
				int susy = j+dy[k];
				if ((0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size())) {
					cnt += (v[susx][susy] != '#');
				}
			}
			if (cnt >= 3) {
				sol++;
				m[{i, j}] = sol;
			}
		}	
	}
	
	for (auto it = m.begin(); it != m.end(); it++) {
		int x = (it->first).first;
		int y = (it->first).second;
		int pos = it->second;
		
		for (int k = 0; k < 4; k++) {
			int susx = x+dx[k];
			int susy = y+dy[k];
			if ((0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size()) && v[susx][susy] != '#') {
				graph[pos].push_back(findIntersection(susx, susy, x, y, v, m));
			}
		}
	}
	
	for (int i = 1; i <= sol; i++) {
		cout << i << ":" << endl;
		for (int j = 0; j < graph[i].size(); j++) {
			cout << "(" << graph[i][j].first << ", " << graph[i][j].second << ") ";
		}
		cout << endl;
	}
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<string>v;
    read ("input.txt", v);
	solve(v);

return 0;
}

