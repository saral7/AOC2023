#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<string> &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();
}

bool inside (int x, int y, const vector<string> &v) {
	return (0 <= x && x < v.size() && 0 <= y && y < v[0].size());
}

pair<int, int> moveIt (pair<int, int> pos, const vector<string> &v, const vector<string> &been) {
	char z = v[pos.first][pos.second];
	int dx[] = {-1, 1, 0, 0, -1, 0, -1, 0, 1, 0, 1, 0};
	int dy[] = {0, 0, -1, 1, 0, 1, 0, -1, 0, -1, 0, 1};
	map<char, int>m;
	m['|'] = 0, m['-'] = 2, m['L'] = 4, m['J'] = 6, m['7'] = 8, m['F'] = 10;
	int x = pos.first, y = pos.second, susx, susy;
	if (z == 'S') {
		return {x+1, y};
		for (int i = 0; i < 4; i++) {
			susx = x+dx[i];
			susy = y+dy[i];
			if (!inside(susx, susy, v) || been[susx][susy] == '1' || v[susx][susy] == '.') continue;
			return {susx, susy};
		}
	}
	for (int i = m[z]; i < m[z]+2; i++) {
		susx = x+dx[i];
		susy = y+dy[i];
		if (!inside(susx, susy, v) || been[susx][susy] == '1' || v[susx][susy] == '.') continue;
		return {susx, susy};
	}
	return {-1, -1};
}

void dfs (pair<int, int>pos, const vector<string> &v, vector<string> &been, int& val) {
	if (been[pos.first][pos.second] == '1') return;
	//cout << pos.first << " " << pos.second << endl;
	//system("pause");
	been[pos.first][pos.second] = '1';
	val++;
	pair<int, int>nextPos = moveIt(pos, v, been);
	//cout << "next -> " << nextPos.first << " " << nextPos.second << endl;
	if (nextPos.first == nextPos.second && nextPos.first == -1) return;
	dfs (nextPos, v, been, val);
	return;
}

void solve (vector<string> &v) {
	vector<string>been;
	string pom = "";
	pair<int, int> pos;
	for (int i = 0; i < v.size(); i++) {
		//cout << v[i] << endl;
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == 'S') pos = {i, j};
		}
	}
	for (int j = 0; j < v[0].size(); j++) pom += "0";
	for (int i = 0; i < v.size(); i++) been.push_back(pom);
	int cycleLength = 0;
	dfs (pos, v, been, cycleLength);
	cout << (cycleLength+1)/2;
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

