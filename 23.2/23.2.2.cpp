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
const int N = 157;
int dp[N][N];
bool active[N][N];
int intNum[N][N];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};


vector<pair<int, int> >graph[N];
int been[N];

pair<int, int> findIntersection(int x, int y, int parx, int pary, vector<string> &v) {
	if (intNum[x][y]) return {intNum[x][y], 0};
	
	for (int i = 0; i < 4; i++) {
		int susx = x+dx[i];
		int susy = y+dy[i];
		
		if (!(0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size())) continue;
		if (v[susx][susy] == '#') continue;
		if (susx == parx && susy == pary) continue;
		
		pair<int, int> pom = findIntersection(susx, susy, x, y, v);
		pom.second++;
		return pom;
	}
}

int sol = 0;

void findMax (int node, int n, int val) {
	if (node == n) {
		sol = max(sol, val);
		return;	
	}
	
	been[node] = 1;
	for (int i = 0; i < graph[node].size(); i++) {
		int sus = graph[node][i].first;
		if (been[sus]) continue;
		findMax(sus, n, val+graph[node][i].second+1);
	}
	been[node] = 0;
}

void solve (vector<string>&v) {
	memset (dp, -1, sizeof(dp));
	int n = 0;
	map<pair<int, int>, int>m;
	//cout << v.size() << endl;
	n++;
	intNum[0][1] = n;
	m[{0, 1}] = n;
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
				n++;
				intNum[i][j] = n;
				m[{i, j}] = n;
			}
		}	
	}
	n++;
	intNum[v.size()-1][v[0].size()-2] = n;
	m[{v.size()-1, v[0].size()-2}] = n;
	
	int cnt = 1;
	for (auto it = m.begin(); it != m.end(); it++) {
		int x = (it->first).first;
		int y = (it->first).second;
		
		for (int k = 0; k < 4; k++) {
			int x2 = x+dx[k];
			int y2 = y+dy[k];
			
			if (!(0 <= x2 && x2 < v.size() && 0 <= y2 && y2 < v[0].size())) continue;
			if (v[x2][y2] == '#') continue;
			graph[cnt].push_back(findIntersection(x2, y2, x, y, v));
		}
		cnt++;
	}
	/*for (int i = 1; i <= n; i++) {
		cout << i << ":" << endl;
		for (int j = 0; j < graph[i].size(); j++) {
			cout << "(" << graph[i][j].first << ", " << graph[i][j].second << ") ";
		}
		cout << endl;
	}*/
	findMax(1, n, 0);
	cout << sol << endl;
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

