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
///bold assumntion: no cycles

int findMax (int x, int y, vector<string>&v) {
	if (dp[x][y] != -1) return dp[x][y];
	//cout << x << " " << y << endl;
	//system("pause");
	if (x == v.size()-1 && y == v[0].size()-2) {
		dp[x][y] = 1;
		return 1;
	}
	
	active[x][y] = true;
	int maxVal = 0;
	if (v[x][y] == '.') {
		for (int i = 0; i < 4; i++) {
			int susx = x+dx[i];
			int susy = y+dy[i];
			
			if (!(0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size())) continue;
			if (active[susx][susy] || v[susx][susy] == '#') continue;
			
			maxVal = max(maxVal, findMax(susx, susy, v));
		}
		dp[x][y] = maxVal+1;
	}
	else {
		int susx = x, susy = y;
		if (v[x][y] == '>') susy++;
		if (v[x][y] == 'v') susx++;
		if (v[x][y] == '<') susy--;
		if (v[x][y] == '^') susx--;
		if ((0 <= susx && susx < v.size() && 0 <= susy && susy < v[0].size()) && !active[susx][susy] && v[susx][susy] != '#') {
			dp[x][y] = findMax(susx, susy, v)+1;
		}
	}
	active[x][y] = false;
	return dp[x][y];
}

void solve (vector<string>&v) {
	memset (dp, -1, sizeof(dp));
	//for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
	cout << findMax(0, 1, v)-1;
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

